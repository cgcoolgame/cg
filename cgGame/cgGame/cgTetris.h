#pragma once
#include <vector>
#include "cgGameApp.h"
#include "cgSingleton.h"
#include "cgImage.h"

using namespace std;

struct TetrisBlock
{
	TetrisBlock()
	{

	}
	TetrisBlock(int nColor, int nX, int nY)
	{
		this->nColor = nColor;
		this->nPosX = nX;
		this->nPosY = nY;
	}
	int nColor;
	int nPosX;
	int nPosY;
};

typedef vector<TetrisBlock* > TetrisBlockPtrList;

class TetrisShape
{
public:
	TetrisShape(int nShapeIndex, bool bNeedTrans = true);
	~TetrisShape();
public:
	int GetShapeIndex();

	void SetPos(int nPosX, int nPosY);
	int GetPosX();
	int GetPosY();

	bool Transform();

	void AddNewBlock(int nColor, int nPosX, int nPosY);
	
	TetrisShape & operator=(const TetrisShape& kShape);

	int GetBlockNum();
	TetrisBlock * GetBlockByIndex(unsigned index);

	bool NeedTransform();
private:
	void Clear();
private:
	int m_nShapeIndex;	// ��״���
	int m_nPosX;			// λ��
	int m_nPosY;			// λ��
	bool m_bNeedTrans;		// �Ƿ���Ҫ��ת
	TetrisBlockPtrList m_kBlockList;	// �����б�
};

//---------------------------------------------------------

typedef vector<TetrisShape*> TetrisShapePtrList;


#define TETRIS_MATRIX_LINE_NUM 20
#define TETRIS_MATRIX_BLOCK_NUM_PER_LINE 10

#define TETRIS_MAIN_DRAW_OFF_X 0
#define TETRIS_MAIN_DRAW_OFF_Y 0
#define TETRIS_BLOCK_WIDTH 32

#define TETRIS_NEXT_DRAW_OFF_X 700
#define TETRIS_NEXT_DRAW_OFF_Y 100

#define TETRIS_BASE_SCORE_PER_FULL_LINE 100 // һ�ж��ٷ�

#define TETRIS_QUICK_DOWN_TIMESPACE 0.02f	// �����½���ʱ����
#define TETRIS_H_MOVING_TIMESPACE 0.08f		// ˮƽ�ƶ�

#define TETRIS_BLOCK_COLOR_NUM 7
class cgTetris :
	public cgGameApp, public cgSingleton<cgTetris>
{
public:
	cgTetris(void);
	virtual ~cgTetris(void);

	virtual bool DoInitGame();

	virtual bool DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam) ;

	void Start();
	void Stop();
	void Pause();
	void Resume();

protected:
	virtual void DoUpdateGame(float fTime) ;
	virtual void DoRenderGame() ;

protected:
	enum enmGameState
	{
		running,
		stopped,
		paused,
	};

protected:
	void InitBlockShapes();
	void ClearBlockShapes();

	void InitBlockMatrix();
	
	void DrawBlock(TetrisBlock & kBlock, int nOffX, int nOffY);

	void DrawShape(TetrisShape & kShape, int nOffX, int nOffY);
	void DrawCurShape();
	void DrawBlockMatrix(int nOffX, int nOffY);

	void DrawNextShape();

	void DrawScore();

	unsigned GetBlockColor(int nColor);

	void NextShape();

	bool MergeCurShapeToMatrix();

	bool CheckMatrixLines();

	int CalcScoreOfOneShape(int nFullLine);

	int GetBlockNumInLine(int nLine);

	// �Ѵ��е���һ�������������ǵ���һ��
	void CoverLineWithOverHead(int nLine);

	// ���һ�����У��÷�
	void ClearFullLine(int nLine);

	// ���һ��
	void ClearLine(int nLine);

	void AddScore(int nAddedScore);

	TetrisBlock * GetBlockInMatrixOfPos(int nLine, int nOffset);
	bool OnKeyUp(DWORD dwKeyValue);
	bool OnKeyDown(DWORD dwKeyValue);

	void OnLvlUp();
private:
	bool CanCurShapeMove(int nXOff, int nYOff);
	bool CanTransform();
	bool CanBlockMoveTo(int nDestX, int nDestY);
	
	bool TryMoveLeft();
	bool TryMoveRight();
	bool TryMoveDown();
	bool TryTransform();

private:
	TetrisShapePtrList m_kShapePtrList;
	TetrisShape m_kCurShape;
	TetrisBlock m_kBlockMatrix[TETRIS_MATRIX_LINE_NUM][TETRIS_MATRIX_BLOCK_NUM_PER_LINE];
	int m_nNextShape;
	float m_fLastUpdateTime;
	float m_fDeltaTime;
	float m_fTimeSpace;

	int m_nScore;
	int m_nLvl;

	cgImagePtr m_spBackPic;
	cgImagePtr m_spColoredBlocks[TETRIS_BLOCK_COLOR_NUM];

	enmGameState m_enmState;

	bool m_bQuickDown;
	bool m_bMovingLeft;
	bool m_bMovingRight;
	float m_fMovingDeltaTime;

	cgID m_idBgm;
};

