
// cgClientUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cgClientUI.h"
#include "cgClientUIDlg.h"
#include "afxdialogex.h"
#include "..\cgNetwork\cgNetworkDef.h"
#include "..\cgNetwork\cgNetworkString.h"
#include "cgLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcgClientUIDlg 对话框




CcgClientUIDlg::CcgClientUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcgClientUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pkClientSocket = NULL;
	m_nLocalPlayerID = -1;

	m_nLocalPlayerScore = 0;
	m_nLocalPlayerFlower = 0;
	m_nLocalPlayerEggNum = 0;
	m_nLocalPlayerShoeNum = 0;

	m_kMyTrace.nNum = 0;
	m_bIsPainting = false;
}

void CcgClientUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcgClientUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CcgClientUIDlg::OnBnClickedButtonSend)
	ON_COMMAND(IDOK, &CcgClientUIDlg::OnIDOk)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CcgClientUIDlg::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CcgClientUIDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CcgClientUIDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_SHOE, &CcgClientUIDlg::OnBnClickedButtonShoe)
	ON_BN_CLICKED(IDC_BUTTON_EGG, &CcgClientUIDlg::OnBnClickedButtonEgg)
	ON_BN_CLICKED(IDC_BUTTON_FLOWER, &CcgClientUIDlg::OnBnClickedButtonFlower)
	ON_BN_CLICKED(IDC_BUTTON_GIVE_UP, &CcgClientUIDlg::OnBnClickedButtonGiveUp)
END_MESSAGE_MAP()


// CcgClientUIDlg 消息处理程序

BOOL CcgClientUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ConnectServer();
	
	memset(&m_kGameStage, NULL, sizeof(m_kGameStage));
	m_kGameStage.nStage = cgRoomGameStage_Waiting;
	m_nFinishTime = 0;

	m_kCanvasRect.left=5;
	m_kCanvasRect.top = 15;
	m_kCanvasRect.right=m_kCanvasRect.left+764;
	m_kCanvasRect.bottom=m_kCanvasRect.top+548;

	SetTimer(NULL, 1000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcgClientUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcgClientUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		ClientPaint();

		CDialogEx::OnPaint();
	}
}


void CcgClientUIDlg::ClientPaint()
{
	CPaintDC cg(this);
	cg.SetDCPenColor(0xff000000);
	cgPaintTraceList::iterator it = m_kPaintTraceList.begin();
	for (; it != m_kPaintTraceList.end(); ++it)
	{
		cgPaintTrace & kTrace = *it;
		DrawTrace(cg, kTrace);
	}
	DrawTrace(cg, m_kMyTrace);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcgClientUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ----------------------------------------------------------------------------------------------------

void CcgClientUIDlg::ConnectServer()
{
	// TODO: 在此添加额外的初始化代码
	cgNetworkDef::NetworkInit();
	m_pkClientSocket = new cgWinSocket;
	m_pkClientSocket->SetID(-1);
	m_pkClientSocket->SetListener(this);
	m_pkClientSocket->CreateSocket();

	UINT uPort = 0;
	TCHAR szAddr[MAX_PATH] = {0};
	::GetPrivateProfileString(TEXT("Login"), TEXT("Address"), TEXT("localhost"), szAddr, MAX_PATH, TEXT("./Login.ini"));
	uPort = ::GetPrivateProfileInt(TEXT("Login"), TEXT("Port"), 22001, TEXT("./Login.ini"));

	m_pkClientSocket->ConnectServer(szAddr, uPort);
}

// ---------------------------------------------------------------------------------
void CcgClientUIDlg::OnCreate( int nID, int nError )
{
	DisplayMsg(TEXT("[系统] 客户端网络初始化成功！"));
}

void CcgClientUIDlg::OnClose( int nID, int nError )
{
	AfxMessageBox(TEXT("客户端网络关闭！"));
	PostQuitMessage(0);
}

void CcgClientUIDlg::OnConnect( int nID, int nError )
{
	if (nError == 0)
	{
		ReqLogin();
	}else
	{
		CString strMsg;
		strMsg.Format(TEXT("服务器连接失败：%d"), nError);
		AfxMessageBox(strMsg);
		PostQuitMessage(0);
	}
	
}

void CcgClientUIDlg::OnSend( int nID, int nError )
{

}

void CcgClientUIDlg::OnReceive( int nID, int nError )
{
	const static int MAX_BUFF_LEN = 1024*1024;
	static char szBuff[MAX_BUFF_LEN];
	memset(szBuff, NULL, MAX_BUFF_LEN);

	int nBuffOffset = 0;
	int nBuffLen = m_pkClientSocket->ReceiveData(szBuff, MAX_BUFF_LEN);
	
	while (nBuffLen > sizeof(cgProtocolHeader))
	{
		cgProtocolHeader * pkHeader = (cgProtocolHeader*)(szBuff+nBuffOffset);
		nBuffLen -= sizeof(cgProtocolHeader);
		nBuffOffset += sizeof(cgProtocolHeader);

		if (pkHeader->nHeaderFlag != CG_PROTOCOL_HEADER_FLAG 
			|| nBuffLen < pkHeader->nBuffLen)
			break;

		OnSvrMsg(pkHeader->nCmd, szBuff+nBuffOffset, pkHeader->nBuffLen);
		nBuffOffset += pkHeader->nBuffLen;
		nBuffLen -= pkHeader->nBuffLen;
	}
}


void CcgClientUIDlg::OnSvrMsg( int nCmd, void * pBuff, int nLen )
{
	switch (nCmd)
	{
	case CG_NETWORK_CMD_LOGIN_RSP:
		OnLoginRsp(nCmd, pBuff, nLen);
		break;
	case CG_NETWORK_CMD_SPEEK_NTF:
		OnSpeekNtf(nCmd, pBuff, nLen);
		break;
	case CG_NETWORK_CMD_PLAYER_ACTION_NTF:
		OnPlayerAction(nCmd, pBuff, nLen);
		break;
	case CG_NETWORK_CMD_PAINT_NTF:
		OnPlayerPaintNtf(nCmd, pBuff, nLen);
		break;
	case CG_NETWORK_CMD_BROADCAST_NTF:
		OnBroadcastNtf(nCmd, pBuff, nLen);
		break;
	case CG_NETWORK_CMD_GAME_STAGE_NTF:
		OnGameStageNtf(nCmd, pBuff, nLen);
		break;
	case CG_NETWORK_CMD_SIMPLE_OPER_NTF:
		OnGameSimpleOperNtf(nCmd, pBuff, nLen);
		break;
	case CG_NETWORK_CMG_ATTR_CHANGE_NTF:
		OnPlayerAttrChangeNtf(nCmd, pBuff, nLen);
		break;
	}
}

void CcgClientUIDlg::ReqSendData(int nCmd, void * pDataBuff, int nLen )
{
	if (nLen + sizeof(cgProtocolHeader) > CG_MAX_PROTOCAL_BUFF_LEN)
		return ;

	static char szSendBuff[CG_MAX_PROTOCAL_BUFF_LEN];
	memset(szSendBuff, NULL, CG_MAX_PROTOCAL_BUFF_LEN);

	cgProtocolHeader * pkHeader = (cgProtocolHeader *)szSendBuff;
	pkHeader->nHeaderFlag = CG_PROTOCOL_HEADER_FLAG;
	pkHeader->nCmd = nCmd;
	pkHeader->nPlayerID = m_nLocalPlayerID;
	pkHeader->nBuffLen = nLen;

	memcpy(szSendBuff+sizeof(cgProtocolHeader), pDataBuff, nLen);

	m_pkClientSocket->SendData(szSendBuff, sizeof(cgProtocolHeader)+nLen);
}


// -------------------------------------------------------------------------------------------------


void CcgClientUIDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_MSG);
	if (pkEdit)
	{
		CString strMsg;
		pkEdit->GetWindowText(strMsg);
		pkEdit->SetWindowText(TEXT(""));

		if (strMsg.GetLength() > 0)
		{
			string strContent = Unicode2UTF8(strMsg);
			ReqSpeek(0, strContent);
		}
	}
}

void CcgClientUIDlg::DisplayMsg( const CString &strMsg )
{
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_PANEL);
	if (pkEdit)
	{
		CString strOld;
		pkEdit->GetWindowText(strOld);
		strOld += strMsg;
		strOld += TEXT("\r\n");

		pkEdit->SetWindowText(strOld);
		pkEdit->LineScroll(pkEdit->GetLineCount(), 0);
	}
}

void CcgClientUIDlg::ShowQuestionDesc( const CString & strMsg )
{
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_Desc);
	if (pkEdit)
	{
		pkEdit->SetWindowText(strMsg);
	}
}

void CcgClientUIDlg::UpdateTimerString()
{
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_TIMER);
	if (pkEdit)
	{
		CString strMsg;
		if (m_kGameStage.nStage != cgRoomGameStage_Waiting && m_kGameStage.nStage != cgRoomGameStage_TipObjectName)
		{
			strMsg.Format(TEXT("剩余时间：%d"), (m_nFinishTime-GetTickCount())/1000);
		}else if (m_kGameStage.nStage == cgRoomGameStage_TipObjectName)
		{
			strMsg.Format(TEXT("下轮时间：%d"), (m_nFinishTime-GetTickCount())/1000);
		}
		pkEdit->SetWindowText(strMsg);
	}
}


void CcgClientUIDlg::ShowAttrs()
{
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_SCORE);
	if (pkEdit)
	{
		CString strMsg;
		strMsg.Format(TEXT("积分:%d 鲜花:%d 鸡蛋:%d 拖鞋:%d"), 
			m_nLocalPlayerScore, 
			m_nLocalPlayerFlower,
			m_nLocalPlayerEggNum,
			m_nLocalPlayerShoeNum);

		pkEdit->SetWindowText(strMsg);
	}
}

void CcgClientUIDlg::ShowName()
{
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_LOCAL_NAME);
	if (pkEdit)
	{
		pkEdit->SetWindowText(m_strLocalPlayerName);
	}
}


void CcgClientUIDlg::OnIDOk()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonSend();
}

// --------------------------------------------------------------------------------

void CcgClientUIDlg::ReqLogin( )
{
	cgLoginDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		cgLoginReq kReq;

		string strText = Unicode2UTF8(dlg.GetAccount());
		kReq.nAccountLen = strText.length()+1;
		memcpy(kReq.szAccount, strText.c_str(), kReq.nAccountLen);

		strText = Unicode2UTF8(dlg.GetPwd());
		kReq.nPwdLen = strText.length()+1;
		memcpy(kReq.szPwd, strText.c_str(), kReq.nPwdLen);

		strText = Unicode2UTF8(dlg.GetName());
		kReq.nNameLen = strText.length()+1;
		memcpy(kReq.szName, strText.c_str(), kReq.nNameLen);

		ReqSendData(CG_NETWORK_CMD_LOGIN_REQ, &kReq, sizeof(kReq));
	}
}

void CcgClientUIDlg::OnLoginRsp( int nCmd, void * pBuff, int nLen )
{
	cgLoginRsp * pkRsp = (cgLoginRsp*)pBuff;
	if (pkRsp->nResult == 0)
	{
		m_nLocalPlayerID = pkRsp->nID;
		m_nLocalPlayerScore = pkRsp->nScore;
		m_nLocalPlayerFlower = pkRsp->nFlowerNum;
		m_nLocalPlayerEggNum = pkRsp->nEggNum;
		m_nLocalPlayerShoeNum = pkRsp->nShoeNum;

		m_strLocalPlayerName = UTF8ToUnicode(pkRsp->szName);

		DisplayMsg(TEXT("[系统] 游戏登陆成功！"));
		CString strMsg;
		strMsg.Format(TEXT(">>角色名字：%s\r\n>>角色ID：%d\r\n>>积分：%d"), 
			(LPCTSTR)m_strLocalPlayerName, pkRsp->nID, pkRsp->nScore);

		DisplayMsg(strMsg);
		ShowAttrs();
		ShowName();

		EnableJudgeBtns(false);
		EnablePaintBtns(false);

	}else
	{
		AfxMessageBox(TEXT("游戏登陆失败！"));
		PostQuitMessage(0);
	}
}

void CcgClientUIDlg::ReqSpeek( int nChannel, const string & strMsg )
{
	cgSpeekReq kReq;
	kReq.nChannel = nChannel;
	kReq.nContentLen = strMsg.length()+1;
	strcpy_s(kReq.szContent, CG_MAX_SPEEK_CONTENT_LEN, strMsg.c_str());
	kReq.nNameLen = 0;

	ReqSendData(CG_NETWORK_CMD_SPEEK_REQ, &kReq, sizeof(kReq));
}

void CcgClientUIDlg::OnSpeekRsp( int nCmd, void * pBuff, int nLen )
{

}

void CcgClientUIDlg::OnSpeekNtf( int nCmd, void * pBuff, int nLen )
{
	cgSpeekNtf * pkNtf = (cgSpeekNtf *)pBuff;

	CString strName = UTF8ToUnicode(pkNtf->szName);
	CString strContent = UTF8ToUnicode(pkNtf->szContent);
	CString strMsg;
	strMsg.Format(TEXT("[聊天] <%s>%s"), (LPCTSTR)strName, (LPCTSTR)strContent);

	DisplayMsg(strMsg);
}

void CcgClientUIDlg::OnPlayerAction( int nCmd, void * pBuff, int nLen )
{
	cgPlayerActionNtf * pkNtf = (cgPlayerActionNtf *)pBuff;

	CString strMsg;
	CString strName = UTF8ToUnicode(pkNtf->szName);
	switch (pkNtf->nAction)
	{
	case CG_PLAYER_ACTION_LOGIN:
		strMsg.Format(TEXT("[系统] 欢迎<%s>进入游戏！"), (LPCTSTR)strName);
		break;
	case CG_PLAYER_ACTION_LOGOUT:
		strMsg.Format(TEXT("[系统] <%s>下线了！"), (LPCTSTR)strName);
		break;
	case CG_PLAYER_ACTION_GUESS_RIGHT:
		strMsg.Format(TEXT("[系统] <%s>猜中了答案！"), (LPCTSTR)strName);
		break;
	}

	DisplayMsg(strMsg);
}


void CcgClientUIDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (CanPaint() && m_bIsPainting)
	{
		AddPointToMyTrace(point.x, point.y);
	}
	__super::OnMouseMove(nFlags, point);
}


void CcgClientUIDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (CanPaint())
	{
		m_bIsPainting = true;
		AddPointToMyTrace(point.x, point.y);
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	__super::OnLButtonDown(nFlags, point);
}

void CcgClientUIDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (CanPaint() && m_bIsPainting)
	{
		m_bIsPainting = false;
		ReqSendTrace();
	}
	__super::OnLButtonUp(nFlags, point);
}

void CcgClientUIDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (CanPaint() && m_kPaintTraceList.size() > 0)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_UNDO_PAINT;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));
	}
	__super::OnRButtonDown(nFlags, point);
}
void CcgClientUIDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (CanPaint() && m_kPaintTraceList.size() > 0 && GetKeyState(VK_SHIFT) < 0)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_CLEAR_PAINT;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));
	}
	__super::OnRButtonDblClk(nFlags, point);
}


void CcgClientUIDlg::ReqSendTrace()
{
	if (m_kMyTrace.nNum > 0)
	{
		cgPaintReq kReq;
		kReq.kTrace = m_kMyTrace;

		ReqSendData(CG_NETWORK_CMD_PAINT_REQ, &kReq, sizeof(kReq));
		m_kMyTrace.nNum = 0;
	}
}

void CcgClientUIDlg::AddPointToMyTrace( int x, int y )
{
	//if (m_kMyTrace.nNum > 0)
	//{
	//	cgPoint & kPoint = m_kMyTrace.kPoints[m_kMyTrace.nNum-1];
	//	if (abs(x-kPoint.x) < 10 && abs(y-kPoint.y) < 10)
	//		return ;
	//}
	cgPoint & kPoint = m_kMyTrace.kPoints[m_kMyTrace.nNum++];
	kPoint.x = x;
	kPoint.y = y;

	
	if (m_kMyTrace.nNum >= CG_MAX_PAINT_TRACE_POINT_NUM)
	{
		ReqSendTrace();
		cgPoint & kPoint = m_kMyTrace.kPoints[m_kMyTrace.nNum++];
		kPoint.x = x;
		kPoint.y = y;
	}
	UpdateCanvas(false);
}

void CcgClientUIDlg::DrawTrace(CPaintDC & dc,  const cgPaintTrace & kTrace )
{
	if (kTrace.nNum <= 0)
		return ;
	dc.MoveTo(kTrace.kPoints[0].x, kTrace.kPoints[0].y);
	for (int i = 0; i < kTrace.nNum; ++i)
	{
		dc.LineTo(kTrace.kPoints[i].x, kTrace.kPoints[i].y);
		//dc.SetPixel(kTrace.kPoints[i].x, kTrace.kPoints[i].y, 0xff000000);
	}
}

void CcgClientUIDlg::OnPlayerPaintNtf( int nCmd, void * pBuff, int nLen )
{
	cgPaintTraceNtf * pkNtf = (cgPaintTraceNtf *)pBuff;

	m_kPaintTraceList.push_back(pkNtf->kTrace);
	UpdateCanvas(false);
}

void CcgClientUIDlg::OnBroadcastNtf( int nCmd, void * pBuff, int nLen )
{
	cgBroadcastNtf *pkNtf = (cgBroadcastNtf*)pBuff;
	CString strMsg;
	strMsg.Format(TEXT("[公告] %s"), UTF8ToUnicode(pkNtf->szContent));
	DisplayMsg(strMsg);
}

void CcgClientUIDlg::OnGameStageNtf( int nCmd, void * pBuff, int nLen )
{
	cgGameStageNtf * pkNtf = (cgGameStageNtf*)pBuff;
	m_kGameStage = *pkNtf;
	switch (pkNtf->nStage)
	{
	case cgRoomGameStage_TipObjectNameLen:
		{
			m_nFinishTime = ::GetTickCount()+(cgGameStageEndTimes[cgRoomGameStage_TipObjectDesc]+cgGameStageEndTimes[cgRoomGameStage_TipObjectNameLen])*1000;
		
			if (m_nLocalPlayerID != pkNtf->nCurPlayerID)
			{
				CString strName = UTF8ToUnicode(pkNtf->szPlayerName);
				CString strMsg;
				strMsg.Format(TEXT("[系统] 现在由<%s>开始画图！"), (LPCTSTR)strName);
				DisplayMsg(strMsg);

				strMsg.Format(TEXT("[你来猜！] %d 个字！"), pkNtf->nObjectNameLenTip);
				//	DisplayMsg(strMsg);
				ShowQuestionDesc(strMsg);
				EnablePaintBtns(false);

			}else
			{
				CString strName = UTF8ToUnicode(pkNtf->szObjectName);
				CString strMsg;
				strMsg.Format(TEXT("[系统] 现在由你开始画图！"));
				DisplayMsg(strMsg);

				strMsg.Format(TEXT("[你来画！] 你的题目为：%s"), (LPCTSTR)strName);
				//	DisplayMsg(strMsg);
				ShowQuestionDesc(strMsg);
				EnablePaintBtns(true);
			}

			m_kPaintTraceList.clear();
			m_kMyTrace.nNum = 0;
			m_bIsPainting = false;
			EnableJudgeBtns(false);
			UpdateCanvas(true);
		}
		break;
	case cgRoomGameStage_TipObjectDesc:
		{
			m_nFinishTime = ::GetTickCount()+(cgGameStageEndTimes[cgRoomGameStage_TipObjectDesc])*1000;
			if (pkNtf->nCurPlayerID != m_nLocalPlayerID)
			{
				CString strDesc = UTF8ToUnicode(pkNtf->szObjectDesc);
				CString strMsg;

				strMsg.Format(TEXT("[你来猜！] %d 个字，%s"), pkNtf->nObjectNameLenTip, (LPCTSTR)strDesc);
				ShowQuestionDesc(strMsg);
			}
			EnableJudgeBtns(false);
			EnableBtn(IDC_BUTTON_CHANGE, false);
		}
		break;
	case cgRoomGameStage_TipObjectName:
		{
			m_nFinishTime = ::GetTickCount()+1000*(cgGameStageEndTimes[cgRoomGameStage_TipObjectName]);
			CString strDesc = UTF8ToUnicode(pkNtf->szObjectDesc);
			CString strObjectName = UTF8ToUnicode(pkNtf->szObjectName);
			CString strMsg;

			strMsg.Format(TEXT("[公布答案] 答案：%s(%d 个字，%s)"), (LPCTSTR)strObjectName,
				pkNtf->nObjectNameLenTip, (LPCTSTR)strDesc);
			ShowQuestionDesc(strMsg);
			m_bIsPainting = false;

			EnableBtn(IDC_BUTTON_CHANGE, false);
			EnableJudgeBtns(m_nLocalPlayerID != pkNtf->nCurPlayerID);
			EnablePaintBtns(false);
			AfxMessageBox(strMsg);
		}
		break;
	case cgRoomGameStage_Waiting:
		{
			m_bIsPainting = false;
			ShowQuestionDesc(TEXT("人数不足，请等待！"));
			EnableJudgeBtns(false);
			EnablePaintBtns(false);
		}
		break;
	}
}

bool CcgClientUIDlg::CanPaint()
{
	if (m_kGameStage.nStage == cgRoomGameStage_Waiting
		|| m_kGameStage.nStage == cgRoomGameStage_TipObjectName)
	{
		return false;
	}
	if (m_kGameStage.nCurPlayerID != m_nLocalPlayerID)
		return false;

	return true;
}

void CcgClientUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateTimerString();
	__super::OnTimer(nIDEvent);
}

void CcgClientUIDlg::OnGameSimpleOperNtf( int nCmd, void * pBuff, int nLen )
{
	cgGameSimpleOperNtf * pkNtf = (cgGameSimpleOperNtf*)pBuff;

	CString strMsg;
	switch (pkNtf->nOperType)
	{
	case CG_PLAYER_SIMPLE_OPER_UNDO_PAINT:
		{
			if (!m_kPaintTraceList.empty())
			{
				m_kPaintTraceList.pop_back();
				UpdateCanvas(true);
			}

			strMsg.Format(TEXT("[系统] <%s>撤消了上一步绘制！"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_CLEAR_PAINT:
		{
			if (!m_kPaintTraceList.empty())
			{
				m_kPaintTraceList.clear();
				UpdateCanvas(true);
			}
			strMsg.Format(TEXT("[系统] <%s>清空了画板！"), UTF8ToUnicode(pkNtf->szName) );
		}break;

	case CG_PLAYER_SIMPLE_OPER_CHANGE_QUESTION:
		{
			// 换题
			strMsg.Format(TEXT("[系统] <%s>更换了题目！"), UTF8ToUnicode(pkNtf->szName) );
			EnableBtn(IDC_BUTTON_CHANGE, false);
		}break;
	case CG_PLAYER_SIMPLE_OPER_GIVE_UP:
		{
			// 放弃
			strMsg.Format(TEXT("[系统] <%s>放弃了绘制，马上开始下一轮！"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_SEND_FLOWER:
		{
			// 鲜花
			strMsg.Format(TEXT("[系统] <%s>为绘画者献上一朵鲜花！"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_THROW_EGG:
		{
			// 扔鸡蛋
			strMsg.Format(TEXT("[系统] <%s>向绘画者扔了一颗臭鸡蛋！"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_THROW_SHOE:
		{
			// 扔拖鞋
			strMsg.Format(TEXT("[系统] <%s>向绘画者扔了一只破拖鞋！"), UTF8ToUnicode(pkNtf->szName) );
		}break;

	}
	DisplayMsg(strMsg);

}

void CcgClientUIDlg::OnPlayerAttrChangeNtf( int nCmd, void * pBuff, int nLen )
{
	cgPlayerAttrChangeNtf * pkNtf = (cgPlayerAttrChangeNtf*)pBuff;
	
	// 暂时只关心自己的属性
	if (pkNtf->nPlayerID != m_nLocalPlayerID)
		return ;

	CString strMsg;

	switch (pkNtf->nAttrType)
	{
	case CG_GAME_ATTR_TYPE_SCORE:
		{
			m_nLocalPlayerScore += pkNtf->nChangeValue;

			if (pkNtf->nOperType == CG_PLAYER_SCORE_CHANGE_OPER_PAINT)
			{
				strMsg.Format(TEXT("[系统] 积分 +%d ! 画得不错，有人猜中了！"), pkNtf->nChangeValue);
			}else if (pkNtf->nOperType == CG_PLAYER_SCORE_CHANGE_OPER_GUESS)
			{
				strMsg.Format(TEXT("[系统] 积分 +%d ! 够机智，这样都可以猜中！"), pkNtf->nChangeValue);
			}
		}break;
	case CG_GAME_ATTR_TYPE_FLOWER_NUM:
		{
			m_nLocalPlayerFlower += pkNtf->nChangeValue;
			strMsg.Format(TEXT("[系统] 鲜花 +%d"), pkNtf->nChangeValue);
		}break;
	case CG_GAME_ATTR_TYPE_EGG_NUM:
		{
			m_nLocalPlayerEggNum += pkNtf->nChangeValue;
			strMsg.Format(TEXT("[系统] 臭鸡蛋 +%d"), pkNtf->nChangeValue);
		}break;
	case CG_GAME_ATTR_TYPE_SHOE_NUM:
		{
			m_nLocalPlayerShoeNum += pkNtf->nChangeValue;
			strMsg.Format(TEXT("[系统] 破拖鞋 +%d"), pkNtf->nChangeValue);
		}break;
	}
	ShowAttrs();
	DisplayMsg(strMsg);

}




void CcgClientUIDlg::OnBnClickedButtonUndo()
{
	if (CanPaint() && m_kPaintTraceList.size() > 0)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_UNDO_PAINT;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));
	}
}


void CcgClientUIDlg::OnBnClickedButtonClear()
{
	if (CanPaint() && m_kPaintTraceList.size() > 0)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_CLEAR_PAINT;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));
	}
}


void CcgClientUIDlg::OnBnClickedButtonChange()
{
	if (CanPaint() && m_kGameStage.nStage == cgRoomGameStage_TipObjectNameLen)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_CHANGE_QUESTION;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));

		EnableBtn(IDC_BUTTON_CHANGE, false);
	}
}

void CcgClientUIDlg::OnBnClickedButtonGiveUp()
{
	if (CanPaint())
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_GIVE_UP;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));
	}
}

void CcgClientUIDlg::OnBnClickedButtonShoe()
{
	if (m_kGameStage.nStage == cgRoomGameStage_TipObjectName
		&& m_kGameStage.nCurPlayerID != m_nLocalPlayerID)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_THROW_SHOE;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));

		EnableJudgeBtns(false);
	}
}


void CcgClientUIDlg::OnBnClickedButtonEgg()
{
	if (m_kGameStage.nStage == cgRoomGameStage_TipObjectName
		&& m_kGameStage.nCurPlayerID != m_nLocalPlayerID)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_THROW_EGG;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));

		EnableJudgeBtns(false);
	}
}


void CcgClientUIDlg::OnBnClickedButtonFlower()
{
	if (m_kGameStage.nStage == cgRoomGameStage_TipObjectName
		&& m_kGameStage.nCurPlayerID != m_nLocalPlayerID)
	{
		cgGameSimpleOperReq kReq;
		kReq.nOperType = CG_PLAYER_SIMPLE_OPER_SEND_FLOWER;
		kReq.nParam1 = 0;
		kReq.nParam2 = 0;

		ReqSendData(CG_NETWORK_CMD_SIMPLE_OPER_REQ, &kReq, sizeof(kReq));

		EnableJudgeBtns(false);
	}
}

void CcgClientUIDlg::EnableBtn( int nID, bool bEnable )
{
	CButton * pkBtn = (CButton*)GetDlgItem(nID);
	if (pkBtn)
	{
		pkBtn->EnableWindow(bEnable);
	}
}

void CcgClientUIDlg::EnablePaintBtns( bool bEnable )
{
	EnableBtn(IDC_BUTTON_UNDO, bEnable);
	EnableBtn(IDC_BUTTON_CLEAR, bEnable);
	EnableBtn(IDC_BUTTON_CHANGE, bEnable);
	EnableBtn(IDC_BUTTON_GIVE_UP, bEnable);
}

void CcgClientUIDlg::EnableJudgeBtns( bool bEnable )
{
	EnableBtn(IDC_BUTTON_FLOWER, bEnable);
	EnableBtn(IDC_BUTTON_SHOE, bEnable);
	EnableBtn(IDC_BUTTON_EGG, bEnable);

}

void CcgClientUIDlg::UpdateCanvas( bool bClear /*= true*/ )
{
	InvalidateRect(&m_kCanvasRect, bClear?TRUE:FALSE);
}


