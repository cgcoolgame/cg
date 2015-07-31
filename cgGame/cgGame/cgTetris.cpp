#include "StdAfx.h"
#include "cgTetris.h"
#include <complex>
#include <iostream>
//#include <mmsystem.h>
#include "cgSoundPlayer.h"
#include "cgRender.h"
#include "cgSrcImageManager.h"
#include "cgIDImageManager.h"
#include "cgSoundManager.h"
using namespace std;
/************************************************************************/
/*                                                                      */
/************************************************************************/
cgTetris::cgTetris(void):m_kCurShape(-1)
{
	m_spBackPic = NULL;
	m_idBgm = CG_INVALID_ID;
}

cgTetris::~cgTetris(void)
{
	ClearBlockShapes();
	if (CG_INVALID_ID != m_idBgm)
		cgSoundManager::Get()->StopSoundChannel(m_idBgm);

}
//---------------------------------------------------------

bool cgTetris::DoInitGame()
{
	m_nNextShape = -1;
	m_fLastUpdateTime = 0.0f;
	m_fDeltaTime = 0.0f;
	m_fTimeSpace = 0.0f;
	m_fMovingDeltaTime = 0.0f;
	m_nScore = 0;
	m_nLvl = 1;
	m_enmState = stopped;
	m_bQuickDown = false;
	m_bMovingLeft = false;
	m_bMovingRight = false;

	m_spBackPic = cgSrcImageManager::Get()->LoadImage(TEXT("./res/back.jpg"));
	
	TCHAR szBlockPath[CG_MAX_IMAGE_PATH_LEN];
	for (int i = 0; i < TETRIS_BLOCK_COLOR_NUM; ++i)
	{
		cgSprintf(szBlockPath, CG_MAX_IMAGE_PATH_LEN, TEXT("./res/block%d.bmp"), (i+1));
		m_spColoredBlocks[i] = cgSrcImageManager::Get()->LoadImage(szBlockPath, true);
	}
	
	cgSoundManager::Get()->SetSoundChannelGroupVolume(cgEnumSoundChannelGroup_Bgm, 0.1f);
	cgSoundManager::Get()->SetSoundChannelGroupVolume(cgEnumSoundChannelGroup_Effect, 0.2f);

	m_idBgm = cgSoundManager::Get()->PlaySound(10000001);

	Start();
	return true;
}


void cgTetris::InitBlockShapes()
{
	ClearBlockShapes();
	//---------------------------------------------
	TetrisShape * pkShape = new TetrisShape(0);
	pkShape->AddNewBlock(0, -1, 0);
	pkShape->AddNewBlock(0, 0, 0);
	pkShape->AddNewBlock(0, 1, 0);
	pkShape->AddNewBlock(0, 2, 0);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
	pkShape = new TetrisShape(1);
	pkShape->AddNewBlock(1, -1, 0);
	pkShape->AddNewBlock(1, 0, 0);
	pkShape->AddNewBlock(1, 1, 0);
	pkShape->AddNewBlock(1, -1, 1);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
	pkShape = new TetrisShape(2, false);
	pkShape->AddNewBlock(2, 0, 0);
	pkShape->AddNewBlock(2, 1, 0);
	pkShape->AddNewBlock(2, 0, 1);
	pkShape->AddNewBlock(2, 1, 1);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
	pkShape = new TetrisShape(3);
	pkShape->AddNewBlock(3, -1, 0);
	pkShape->AddNewBlock(3, 0, 0);
	pkShape->AddNewBlock(3, 1, 0);
	pkShape->AddNewBlock(3, 0, 1);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
	pkShape = new TetrisShape(4);
	pkShape->AddNewBlock(4, 0, 0);
	pkShape->AddNewBlock(4, 1, 0);
	pkShape->AddNewBlock(4, -1, 1);
	pkShape->AddNewBlock(4, 0, 1);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
	pkShape = new TetrisShape(5);
	pkShape->AddNewBlock(5, -1, 0);
	pkShape->AddNewBlock(5, 0, 0);
	pkShape->AddNewBlock(5, 1, 0);
	pkShape->AddNewBlock(5, 1, 1);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
	pkShape = new TetrisShape(6);
	pkShape->AddNewBlock(6, 0, 0);
	pkShape->AddNewBlock(6, -1, 0);
	pkShape->AddNewBlock(6, 0, 1);
	pkShape->AddNewBlock(6, 1, 1);
	m_kShapePtrList.push_back(pkShape);

	return ;
	//-------------------------------------------
	pkShape = new TetrisShape(7);
	pkShape->AddNewBlock(7, -1, 0);
	pkShape->AddNewBlock(7, 0, 1);
//	pkShape->AddNewBlock(7, 0, 1);
	pkShape->AddNewBlock(7, 1, 0);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
	pkShape = new TetrisShape(8);
	pkShape->AddNewBlock(8, 0, 0);
	pkShape->AddNewBlock(8, -1, -1);
	pkShape->AddNewBlock(8, 1, -1);
	pkShape->AddNewBlock(8, 0, 1);
	m_kShapePtrList.push_back(pkShape);
	//-------------------------------------------
}

void cgTetris::ClearBlockShapes()
{
	TetrisShapePtrList::iterator it = m_kShapePtrList.begin();
	for (; it != m_kShapePtrList.end(); ++it)
	{
		delete *it;
	}
	m_kShapePtrList.clear();
}

void cgTetris::InitBlockMatrix()
{
	for (int i = 0; i < TETRIS_MATRIX_LINE_NUM; ++i)
	{
		for (int k = 0; k < TETRIS_MATRIX_BLOCK_NUM_PER_LINE; ++k)
		{
			m_kBlockMatrix[i][k].nColor = -1;
			m_kBlockMatrix[i][k].nPosX = k;
			m_kBlockMatrix[i][k].nPosY = i;
		}
	}
}

//-------------------------------------------------------------------------
void cgTetris::DoUpdateGame( float fTime )
{
	static float fTetrisTime = 0.0;
	fTetrisTime += fTime;

	fTime = fTetrisTime;

	m_fDeltaTime += (fTime-m_fLastUpdateTime);

	if (m_enmState == running)
	{
		// 快速下降和非快速下降用不同的下降时间间隔
		float fFinalTimeSpace = m_bQuickDown?TETRIS_QUICK_DOWN_TIMESPACE:m_fTimeSpace;
		if (m_fDeltaTime > fFinalTimeSpace)
		{
			if (!TryMoveDown())
			{
				// 如果可以向下移动，则移动
				// 不能移动，则把当前图形合并到矩阵中
				MergeCurShapeToMatrix();
				CheckMatrixLines();
				NextShape();
			}
			m_fDeltaTime -= fFinalTimeSpace;
			if (m_fDeltaTime > fFinalTimeSpace)
			{
				m_fDeltaTime = fFinalTimeSpace;
			}
		}
		// 如果是按下了左右键
		if (m_bMovingLeft || m_bMovingRight)
		{
			m_fMovingDeltaTime += fTime-m_fLastUpdateTime;
			if (m_fMovingDeltaTime > TETRIS_H_MOVING_TIMESPACE)
			{
				if (m_bMovingLeft)
				{
					TryMoveLeft();
				}
				else if (m_bMovingRight)
				{
					TryMoveRight();
				}
				m_fMovingDeltaTime -= TETRIS_H_MOVING_TIMESPACE;
			}
		}else
		{
			m_fMovingDeltaTime = 0.0f;
		}
	}else
	{
		m_fDeltaTime = 0.0f;
	}

	m_fLastUpdateTime = fTime;

	
}

void cgTetris::DoRenderGame()
{
	for (int i = 0 ;i < 1; ++i)
	{
		m_spBackPic->DrawToPoint(0, 0);

		cgRender::Get()->FillRect(cgRectF(TETRIS_MAIN_DRAW_OFF_X,
			TETRIS_MAIN_DRAW_OFF_Y,
			TETRIS_BLOCK_WIDTH*TETRIS_MATRIX_BLOCK_NUM_PER_LINE,
			TETRIS_MATRIX_LINE_NUM*TETRIS_BLOCK_WIDTH), 0x8f000000);

		DrawBlockMatrix(TETRIS_MAIN_DRAW_OFF_X, TETRIS_MAIN_DRAW_OFF_Y);
		DrawCurShape();
		DrawNextShape();
		DrawScore();
	}

	//for (int i = 0; i < 16; ++i)
	//{
	//	cgImagePtr ptr = cgIDImageManager::Get()->GetImage(i);
	//	ptr->DrawToPoint(10+i%4*100, 100+i/4*100);
	//}

	//cgUIManager::Get()->Draw();
}

bool cgTetris::DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_enmState != stopped)
	{
		switch (message)
		{
		case WM_KEYDOWN:
			{
				OnKeyDown(wParam);
			}break;
		case WM_KEYUP:
			{
				OnKeyUp(wParam);
			}break;
		default:
			break;
		}
	}

	return false;
}

bool cgTetris::OnKeyDown(DWORD dwKeyValue)
{
	switch(dwKeyValue)
	{
	case VK_DOWN:
		{
			//TryMoveDown();
			m_bQuickDown = true;
		}break;
	case VK_LEFT:
		{	
			if (!m_bMovingLeft)
			{
				TryMoveLeft();
				m_bMovingLeft = true;
				m_fMovingDeltaTime = -0.04f;
			}
			m_bMovingRight = false;
			
		}break;
	case VK_RIGHT:
		{
			if (!m_bMovingRight)
			{
				TryMoveRight();
				m_bMovingRight = true;
				m_fMovingDeltaTime = -0.04f;
			}

			m_bMovingLeft = false;
		
		}break;
	case VK_UP:
		{
			TryTransform();
		}break;
	case VK_F1:
		{
			float fV = cgSoundManager::Get()->GetSoundChannelGroupVolume(0);
			cgSoundManager::Get()->SetSoundChannelGroupVolume(0, fV+0.1f);
		}break;
	case VK_F2:
		{
			float fV = cgSoundManager::Get()->GetSoundChannelGroupVolume(0);
			cgSoundManager::Get()->SetSoundChannelGroupVolume(0, fV-0.1f);
		}break;
	case VK_F3:
		{
			float fV = cgSoundManager::Get()->GetSoundChannelGroupVolume(2);
			cgSoundManager::Get()->SetSoundChannelGroupVolume(2, fV+0.1f);
		}break;
	case VK_F4:
		{
			float fV = cgSoundManager::Get()->GetSoundChannelGroupVolume(2);
			cgSoundManager::Get()->SetSoundChannelGroupVolume(2, fV-0.1f);
		}break;
	case VK_F5:
		{
			cgSoundManager::Get()->StopSoundChannel(m_idBgm);
			
			m_idBgm = cgSoundManager::Get()->PlaySound(5);

		}break;
	case VK_F6:
		{
			cgSoundManager::Get()->StopSoundChannel(m_idBgm);

			m_idBgm = cgSoundManager::Get()->PlaySound(4);

		}break;
	default:
		break;
	}
	return true;
}


bool cgTetris::OnKeyUp( DWORD dwKeyValue )
{
	switch(dwKeyValue)
	{
	case VK_PAUSE:
		{
			if (m_enmState == running)
			{
				Pause();
			}else if (m_enmState == paused)
			{
				Resume();
			}

		}break;
	case VK_HOME:
		{
			Start();
		}break;
	case VK_END:
		{
			Stop();
		}break;
	case VK_DOWN:
		{
			m_bQuickDown = false;
		}break;
	case VK_LEFT:
		{	
			m_bMovingLeft = false;
		}break;
	case VK_RIGHT:
		{
			m_bMovingRight = false;
		}break;
	case 'P':
		{
			cgRender::Get()->ScreenShot(TEXT("Tetris.png"), cgScreenShotImageFormat_PNG);
		}break;
#ifdef  _DEBUG
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
#endif
	default:
		break;
	}
	return true;
}

//-------------------------------------------------

void cgTetris::Start()
{
	InitBlockShapes();
	InitBlockMatrix();

	m_fLastUpdateTime = cgTime::GetTime();
	m_fDeltaTime = 0.0f;
	m_fTimeSpace = 1.0f;// 初始时间间隔

	m_nScore = 0;
	m_nLvl = 1;
	m_enmState = running;

	srand(GetTickCount());
	m_nNextShape = rand()%(m_kShapePtrList.size());
	NextShape();

}
void cgTetris::Stop()
{
	m_enmState = stopped;
}

void cgTetris::Pause()
{
	if (m_enmState == running)
	{
		m_enmState = paused;
	}
}

void cgTetris::Resume()
{
	if (m_enmState == paused)
	{
		m_enmState = running;
	}
}

// --------------------------------------------------

void cgTetris::DrawBlock( TetrisBlock & kBlock, int nOffX, int nOffY )
{
	if (kBlock.nColor < 0 )
	{
		return ;
	}
	/*pkRender->FillRect(CGRECT(nOffX+kBlock.nPosX*TETRIS_BLOCK_WIDTH,
	nOffY+kBlock.nPosY*TETRIS_BLOCK_WIDTH,
	TETRIS_BLOCK_WIDTH-1, TETRIS_BLOCK_WIDTH-1),
	GetBlockColor(kBlock.nColor));*/

	cgImagePtr spBlockImg = m_spColoredBlocks[kBlock.nColor%TETRIS_BLOCK_COLOR_NUM];
	if (spBlockImg)
	{
		spBlockImg->Draw( cgRectF(0, 0, spBlockImg->GetWidth(), spBlockImg->GetHeight()),
			cgRectF(nOffX+kBlock.nPosX*TETRIS_BLOCK_WIDTH,
			nOffY+kBlock.nPosY*TETRIS_BLOCK_WIDTH,
			TETRIS_BLOCK_WIDTH-1, TETRIS_BLOCK_WIDTH-1) );
	}
}

void cgTetris::DrawShape( TetrisShape & kShape, int nOffX, int nOffY )
{
	nOffX += kShape.GetPosX()*TETRIS_BLOCK_WIDTH;
	nOffY += kShape.GetPosY()*TETRIS_BLOCK_WIDTH;
	for (int i = 0; i < kShape.GetBlockNum(); ++i)
	{
		TetrisBlock * pkBlock = kShape.GetBlockByIndex(i);
		if (pkBlock)
		{
			DrawBlock( *pkBlock, nOffX, nOffY);
		}
	}
}

void cgTetris::DrawBlockMatrix( int nOffX, int nOffY )
{
	for (int i = 0; i < TETRIS_MATRIX_LINE_NUM; ++i)
	{
		for (int k = 0; k < TETRIS_MATRIX_BLOCK_NUM_PER_LINE; ++k)
		{
			DrawBlock( m_kBlockMatrix[i][k], nOffX, nOffY);
		}
	}
}


void cgTetris::DrawCurShape( )
{
	int nOffX = m_kCurShape.GetPosX()*TETRIS_BLOCK_WIDTH+TETRIS_MAIN_DRAW_OFF_X;
	int nOffY = m_kCurShape.GetPosY()*TETRIS_BLOCK_WIDTH+TETRIS_MAIN_DRAW_OFF_Y;
	for (int i = 0; i < m_kCurShape.GetBlockNum(); ++i)
	{
		TetrisBlock * pkBlock = m_kCurShape.GetBlockByIndex(i);
		if (pkBlock && nOffY+pkBlock->nPosY >= TETRIS_MAIN_DRAW_OFF_Y)
		{
			// 出去的就不画了
			DrawBlock( *pkBlock, nOffX, nOffY);
		}
	}
}

void cgTetris::DrawNextShape()
{
	cgRender * pkRender = cgRender::Get();

	pkRender->FillRect(cgRectF(TETRIS_MAIN_DRAW_OFF_X+TETRIS_BLOCK_WIDTH*TETRIS_MATRIX_BLOCK_NUM_PER_LINE+2,
		TETRIS_MAIN_DRAW_OFF_Y,
		TETRIS_BLOCK_WIDTH*5,
		5*TETRIS_BLOCK_WIDTH), 0x8f000000);

	DrawShape( *m_kShapePtrList[m_nNextShape],
		TETRIS_MAIN_DRAW_OFF_X+TETRIS_BLOCK_WIDTH*TETRIS_MATRIX_BLOCK_NUM_PER_LINE+TETRIS_BLOCK_WIDTH*2,
		TETRIS_MAIN_DRAW_OFF_Y+TETRIS_BLOCK_WIDTH*2 );
}

void cgTetris::DrawScore(  )
{
	cgRender * pkRender = cgRender::Get();

	static TCHAR szScoreTxt[CG_SHORT_TEXT_BUFF_LEN];
	cgSprintf(szScoreTxt, CG_SHORT_TEXT_BUFF_LEN, TEXT("总分数：%d"), m_nScore);
	pkRender->RenderString(szScoreTxt, cgStrLen(szScoreTxt), 
		TETRIS_MAIN_DRAW_OFF_X+TETRIS_BLOCK_WIDTH*TETRIS_MATRIX_BLOCK_NUM_PER_LINE,
		TETRIS_MAIN_DRAW_OFF_Y+TETRIS_BLOCK_WIDTH*5+10, 2, 0xff008f00);

	cgSprintf(szScoreTxt, CG_SHORT_TEXT_BUFF_LEN, TEXT("总等级：%d"), m_nLvl);
	pkRender->RenderString(szScoreTxt, cgStrLen(szScoreTxt), 
		TETRIS_MAIN_DRAW_OFF_X+TETRIS_BLOCK_WIDTH*TETRIS_MATRIX_BLOCK_NUM_PER_LINE,
		TETRIS_MAIN_DRAW_OFF_Y+TETRIS_BLOCK_WIDTH*5+40,
		 2, 0xff008f00);
}
//---------------------------------------------------------------
void cgTetris::NextShape()
{
	m_kCurShape = *m_kShapePtrList[m_nNextShape];
	m_kCurShape.SetPos(TETRIS_MATRIX_BLOCK_NUM_PER_LINE/2, 0);
	m_nNextShape = rand()%(m_kShapePtrList.size());

	if (!CanCurShapeMove(0, 1))
	{
		cgSoundManager::Get()->PlaySound(0);

		Stop();

		//cgComponentPtr ptrRoot = cgUIManager::Get()->GetUIRoot();
		//cgComponent * pkDlg = new cgComponent("dlg");
		//pkDlg->SetBackImage(new cgSrcImage(TEXT("./res/block1.bmp")));
		//pkDlg->SetLocalRect(100, 100, 200, 100);
		//pkDlg->SetText(TEXT("Game Over 了！"));
		//pkDlg->SetVisible(true);
		//ptrRoot->AddChild(pkDlg);
	}
}


bool cgTetris::CheckMatrixLines()
{
	int nTotalFullLine = 0;
	// 先实现功能，再做优化
	for (int i = TETRIS_MATRIX_LINE_NUM-1; i >= 0; )
	{
		int nNum = GetBlockNumInLine(i);
		if (nNum == TETRIS_MATRIX_BLOCK_NUM_PER_LINE)
		{
			// 清空一行后，上面一行会掉下来，所以不用--i
			ClearFullLine(i);
			++nTotalFullLine;
		}else if (nNum == 0)
		{
			// 从下到上，找到空行，说明往上就没有了，不用再检测了。
			break;
		}else
		{
			--i;
		}
	}

	if (nTotalFullLine > 0)
	{
		AddScore(CalcScoreOfOneShape(nTotalFullLine));
	}

	return false;
}

int cgTetris::GetBlockNumInLine( int nLine )
{
	int nNum = 0;
	for (int i = 0; i < TETRIS_MATRIX_BLOCK_NUM_PER_LINE; ++i)
	{
		if (m_kBlockMatrix[nLine][i].nColor >= 0)
		{
			++nNum;
		}
	}
	return nNum;
}

TetrisBlock * cgTetris::GetBlockInMatrixOfPos( int nLine, int nOffset )
{
	if (nLine > -1 && nLine < TETRIS_MATRIX_LINE_NUM 
		&& nOffset > -1 && nOffset < TETRIS_MATRIX_BLOCK_NUM_PER_LINE)
	{
		return &m_kBlockMatrix[nLine][nOffset];
	}

	return NULL;
}

bool cgTetris::MergeCurShapeToMatrix()
{
	int nShapePosX = m_kCurShape.GetPosX();
	int nShapePosY = m_kCurShape.GetPosY();

	int nNum = m_kCurShape.GetBlockNum();
	for (int i = 0; i < nNum; ++i)
	{
		TetrisBlock * pkBlock = m_kCurShape.GetBlockByIndex(i);
		if (!pkBlock)
		{
			continue;
		}
		TetrisBlock * pkBlockInMatrix = 
			GetBlockInMatrixOfPos(nShapePosY+pkBlock->nPosY, nShapePosX+pkBlock->nPosX);
		if (pkBlockInMatrix)
		{
			pkBlockInMatrix->nColor = pkBlock->nColor;
		}
	}

	m_bQuickDown = false;

	cgSoundManager::Get()->PlaySound(0);

	return true;
}

void cgTetris::ClearLine( int nLine )
{
	int nNum = 0;
	for (int i = 0; i < TETRIS_MATRIX_BLOCK_NUM_PER_LINE; ++i)
	{
		m_kBlockMatrix[nLine][i].nColor = -1;
	}
}

void cgTetris::ClearFullLine( int nLine )
{
	for (int i = nLine; i >= 0; --i)
	{
		CoverLineWithOverHead(i);
	}
}

void cgTetris::CoverLineWithOverHead( int nLine )
{
	if (nLine > 0)
	{
		for (int i = 0; i < TETRIS_MATRIX_BLOCK_NUM_PER_LINE; ++i)
		{
			m_kBlockMatrix[nLine][i].nColor = m_kBlockMatrix[nLine-1][i].nColor;
		}
	}else
	{
		// 如果是最上面一行，则直接清空
		ClearLine(0);
	}
}
//--------------------------------------------------------------------

bool cgTetris::TryMoveLeft()
{
	if (CanCurShapeMove(-1, 0))
	{
		m_kCurShape.SetPos(m_kCurShape.GetPosX()-1, m_kCurShape.GetPosY());
		cgSoundManager::Get()->PlaySound(0);

		return true;
	}
	return false;
}

bool cgTetris::TryMoveRight()
{
	if (CanCurShapeMove(1, 0))
	{
		m_kCurShape.SetPos(m_kCurShape.GetPosX()+1, m_kCurShape.GetPosY());
		cgSoundManager::Get()->PlaySound(0);

		return true;
	}
	return false;
}

bool cgTetris::TryMoveDown()
{
	if (CanCurShapeMove(0, 1))
	{

		m_kCurShape.SetPos(m_kCurShape.GetPosX(), m_kCurShape.GetPosY()+1);
		cgSoundManager::Get()->PlaySound(0);

		return true;
	}
	return false;
}

bool cgTetris::TryTransform()
{
	cgSoundManager::Get()->PlaySound(0);

	if (m_kCurShape.NeedTransform() && CanTransform())
	{
		return m_kCurShape.Transform();
	}

	return false;
}


bool cgTetris::CanCurShapeMove( int nXOff, int nYOff )
{
	nXOff += m_kCurShape.GetPosX();
	nYOff += m_kCurShape.GetPosY();

	int nNum = m_kCurShape.GetBlockNum();
	for (int i = 0; i < nNum; ++i)
	{
		TetrisBlock * pkBlock = m_kCurShape.GetBlockByIndex(i);
		if (!pkBlock)
		{
			continue;
		}
		int nDestX = pkBlock->nPosX+nXOff;
		int nDestY = pkBlock->nPosY+nYOff;

		if (!CanBlockMoveTo(nDestX, nDestY))
		{
			return false;
		}
	}
	return true;
}



//-------------------------------------------------------------

bool cgTetris::CanTransform()
{
	if (m_enmState != running)
	{
		return false;
	}
	int nPosX = m_kCurShape.GetPosX();
	int nPosY = m_kCurShape.GetPosY();

	int nNum = m_kCurShape.GetBlockNum();
	for (int i = 0; i < nNum; ++i)
	{
		TetrisBlock * pkBlock =  m_kCurShape.GetBlockByIndex(i);
		int nDestX = -pkBlock->nPosY ;
		int nDestY = pkBlock->nPosX;

		if (!CanBlockMoveTo(nPosX+nDestX, nPosY+nDestY))
		{
			return false;
		}
	}

	return true;
}

bool cgTetris::CanBlockMoveTo( int nDestX, int nDestY )
{
	if (nDestX < 0 || nDestX >= TETRIS_MATRIX_BLOCK_NUM_PER_LINE
		|| nDestY >= TETRIS_MATRIX_LINE_NUM)
	{
		// 只有左右、下出界，才判定不无法移动，上面出界则不管
		return false;
	}
	TetrisBlock * pkBlockInMatrix = 
		GetBlockInMatrixOfPos(nDestY,
		nDestX);
	if (pkBlockInMatrix != NULL && pkBlockInMatrix->nColor > -1)
	{
		// 找每个格子的下一个
		// 找不到说明到达了边界
		// 找到了，且这个格子颜色不为非法，
		// 说明这个位置有，不能继续下移
		return false;
	}

	return true;
}


//-------------------------------------------------------------------------------------------
void cgTetris::AddScore( int nAddedScore )
{
	const int nBaseScore = 1000;

	cgSoundManager::Get()->PlaySound(1);

	m_nScore += nAddedScore;
	cout<<"增加分数："<<nAddedScore<<endl;
	// 升级经验按100递增
	int nNextLvlScore = nBaseScore*m_nLvl+m_nLvl*(m_nLvl-1)*100;
	if (m_nScore >= nNextLvlScore)
	{
		++m_nLvl;
		OnLvlUp();
		cout<<"恭喜你升级了！！"<<endl;

	}
}

void cgTetris::OnLvlUp()
{
	m_fTimeSpace = pow(0.85f, m_nLvl-1);
	
	cgSoundManager::Get()->PlaySound(2);

	{
		/*CCGScreenElementImage * pkImage = new CCGScreenElementImage(TEXT("./res/LevelUp.png"));
		pkImage->SetPos(425, 300);
		pkImage->SetLifeTime(4);
		pkImage->SetScale(0.5);

		CCGScreenElemActionScale * pkScale = new CCGScreenElemActionScale(1.5);
		pkScale->SetLifeTime(0.1);
		pkImage->AddAciton(pkScale);

		CCGScreenElemActionMoveTo * pkMoveTo = new CCGScreenElemActionMoveTo(425, 100);
		pkMoveTo->SetLifeTime(2);
		pkMoveTo->SetDelayTime(0.5);
		pkImage->AddAciton(pkMoveTo);

		CCGScreenElemActionFade * pkFade = new CCGScreenElemActionFade(0.0f);
		pkFade->SetDelayTime(0.5);
		pkFade->SetLifeTime(3.5);

		CCGGameApp::Get()->GetScreenElemManager()->AddElement(pkImage);*/
	}
}

int cgTetris::CalcScoreOfOneShape( int nFullLine )
{
	switch (nFullLine)
	{
	case 1:
		return TETRIS_BASE_SCORE_PER_FULL_LINE;
	case 2:
		return TETRIS_BASE_SCORE_PER_FULL_LINE*3;
	case 3:
		return TETRIS_BASE_SCORE_PER_FULL_LINE*5;
	case 4:
		return TETRIS_BASE_SCORE_PER_FULL_LINE*8;
	}
	return 0;
}

unsigned cgTetris::GetBlockColor( int nColor )
{
	switch (nColor)
	{
	case 0:
		return 0xffff0000;
	case 1:
		return 0xffff1f00;
	case 2:
		return 0xffffff00;
	case 3:
		return 0xffff00ff;
	case 4:
		return 0xffff000f;
	case 5:
		return 0xff0000ff;
	case 6:
		return 0xffff00ff;
	}
	return 0;
}


//-----------------------------------------------------------------------
TetrisShape::TetrisShape( int nShapeIndex, bool bNeedTrans )
{
	m_nShapeIndex = nShapeIndex;
	m_nPosX = 0;
	m_nPosY = 0;
	m_bNeedTrans = bNeedTrans;
}

TetrisShape::~TetrisShape()
{
	Clear();
}
int TetrisShape::GetShapeIndex()
{
	return m_nShapeIndex;
}


void TetrisShape::SetPos( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

int TetrisShape::GetPosX()
{
	return m_nPosX;
}

int TetrisShape::GetPosY()
{
	return m_nPosY;
}

bool TetrisShape::Transform()
{
	TetrisBlockPtrList::iterator it = m_kBlockList.begin();
	for (; it != m_kBlockList.end(); ++it)
	{
		TetrisBlock * pkBlock =  *it;
		int nTmp = pkBlock->nPosX ;
		pkBlock->nPosX = -pkBlock->nPosY;
		pkBlock->nPosY = nTmp;
	}
	
	return true;
}

void TetrisShape::AddNewBlock( int nColor, int nPosX, int nPosY )
{
	TetrisBlock * pkBlock = new TetrisBlock(nColor, nPosX, nPosY);
	m_kBlockList.push_back(pkBlock);
}

TetrisShape & TetrisShape::operator=( const TetrisShape& kShape )
{
	Clear();
	m_nShapeIndex = kShape.m_nShapeIndex;
	m_nPosX = kShape.m_nPosX;
	m_nPosY = kShape.m_nPosY;
	m_bNeedTrans = kShape.m_bNeedTrans;

	TetrisBlockPtrList::const_iterator it = kShape.m_kBlockList.begin();
	for (; it != kShape.m_kBlockList.end(); ++it)
	{
		const TetrisBlock * pkBlock = *it;
		AddNewBlock(pkBlock->nColor, pkBlock->nPosX, pkBlock->nPosY);
	}
	return *this;
}

void TetrisShape::Clear()
{
	TetrisBlockPtrList::iterator it = m_kBlockList.begin();
	for (; it != m_kBlockList.end(); ++it)
	{
		delete *it;
	}
	m_kBlockList.clear();
}

int TetrisShape::GetBlockNum()
{
	return m_kBlockList.size();
}

TetrisBlock * TetrisShape::GetBlockByIndex( unsigned index )
{
	if (index < m_kBlockList.size())
	{
		return m_kBlockList[index];
	}
	return NULL;
}

bool TetrisShape::NeedTransform()
{
	return m_bNeedTrans;
}



