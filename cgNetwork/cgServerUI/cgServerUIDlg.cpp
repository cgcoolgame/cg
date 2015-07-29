
// cgServerUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cgServerUI.h"
#include "cgServerUIDlg.h"
#include "afxdialogex.h"
#include "cgNetworkDef.h"
#include "..\cgNetwork\cgProtocolDef.h"
#include "..\cgNetwork\cgNetworkString.h"
#include "cgTxtDataReader.h"

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


// CcgServerUIDlg 对话框




CcgServerUIDlg::CcgServerUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcgServerUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pkSvrSocket = NULL;
	m_pkPlayerMgr = NULL;
	m_nTopSocketSerial = 0;
	m_pkCurPlayer = NULL;
	m_nGameStage = cgRoomGameStage_Waiting;
	m_fStartTime = 0;
	m_pkCurQuestion = NULL;
	m_nRightPlayerNum = 0;
}

void CcgServerUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcgServerUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CcgServerUIDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CcgServerUIDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CcgServerUIDlg::OnBnClickedButtonSend)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CcgServerUIDlg 消息处理程序

BOOL CcgServerUIDlg::OnInitDialog()
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

	m_pkPlayerMgr = new cgPlayerInfoManager;

	// TODO: 在此添加额外的初始化代码
	cgNetworkDef::NetworkInit();
	m_pkSvrSocket = new cgWinSocket;
	m_pkSvrSocket->SetID(-1);
	m_pkSvrSocket->SetListener(this);

	CEdit * pkPortEdit = (CEdit*)GetDlgItem(IDC_EDIT_PORT);
	if (pkPortEdit)
	{
		pkPortEdit->SetWindowText(TEXT("22001"));
	}

	SetTimer(NULL, 100, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


CcgServerUIDlg::~CcgServerUIDlg()
{
	m_pkPlayerMgr->Save();

	delete m_pkPlayerMgr;

	delete m_pkSvrSocket;
	cgNetworkDef::NetworkDestroy();
}

void CcgServerUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcgServerUIDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcgServerUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcgServerUIDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CcgServerUIDlg::OnBnClickedButtonCreate()
{
	m_pkPlayerMgr->Load();

	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_PORT);
	if (pkEdit)
	{
		CString str;
		pkEdit->GetWindowText(str);
		UINT uPort = _wtoi(str.GetBuffer());
		m_pkSvrSocket->CreateSocket(uPort, TEXT("localhost"));
		m_pkSvrSocket->ListenConnection();

		LoadQuestions();
	}
	// TODO: 在此添加控件通知处理程序代码
}

// ----------------------------------------------------------
void CcgServerUIDlg::OnCreate( int nID, int nError )
{
	if (nError && nID == -1)
	{
		AfxMessageBox(TEXT("服务器创建成功！"));
		CButton * pkBtn = (CButton*)GetDlgItem(IDC_BUTTON_CREATE);
		if (pkBtn)
			pkBtn->EnableWindow(FALSE);
	}
}

void CcgServerUIDlg::OnClose( int nID, int nError )
{
	CloseConnectionByID(nID);

	cgPlayerInfo * pkPlayer = DelOnlinePlayerByConnectionID(nID);
	if (pkPlayer)
	{
		if (pkPlayer == m_pkCurPlayer)
		{
			m_pkCurPlayer = NULL;
			TurnToStage(cgRoomGameStage_Waiting);
		}
		CString strLog;
		strLog.Format(TEXT("%s Logout！"), UTF8ToUnicode(pkPlayer->szName) );
		DisplayLog(strLog);

		cgPlayerActionNtf kNtf;
		kNtf.nPlayerID = pkPlayer->nPlayerID;
		kNtf.nNameLen = pkPlayer->nNameLen;
		memcpy(kNtf.szName, pkPlayer->szName, kNtf.nNameLen);
		kNtf.nAction = CG_PLAYER_ACTION_LOGOUT;
		NtfMsgToPlayers(CG_NETWORK_CMD_PLAYER_ACTION_NTF, &kNtf, sizeof(kNtf));
	}
}


void CcgServerUIDlg::OnSend( int nID, int nError )
{
	//DisplayLog(TEXT("向客户端发消息成功！"));
}

void CcgServerUIDlg::OnReceive( int nID, int nError )
{
	const static int MAX_BUFF_LEN = 1024*1024;
	static char szBuff[MAX_BUFF_LEN];
	memset(szBuff, NULL, MAX_BUFF_LEN);

	cgWinSocket * pkFind = FindConnection(nID);
	if (!pkFind)
		return;

	int nBuffOffset = 0;
	int nBuffLen = pkFind->ReceiveData(szBuff, MAX_BUFF_LEN);

	while (nBuffLen > sizeof(cgProtocolHeader))
	{
		cgProtocolHeader * pkProtocol = (cgProtocolHeader*)(szBuff+nBuffOffset);
		nBuffLen -= sizeof(cgProtocolHeader);
		nBuffOffset += sizeof(cgProtocolHeader);

		// 如果包头标记出错，或者剩余缓冲区太小了，则丢弃
		if (pkProtocol->nHeaderFlag != CG_PROTOCOL_HEADER_FLAG 
			|| nBuffLen < pkProtocol->nBuffLen)
			break;

		OnClientMsg(pkFind->GetID(),
			pkProtocol->nCmd, 
			szBuff+nBuffOffset,
			pkProtocol->nBuffLen, 
			pkProtocol->nPlayerID);

		nBuffLen -= pkProtocol->nBuffLen;
		nBuffOffset += pkProtocol->nBuffLen;
	}
}

void CcgServerUIDlg::OnAccept( int nID, int nError )
{
	cgWinSocket * pkWinSocket = (cgWinSocket *)m_pkSvrSocket->AcceptConnection();

	pkWinSocket->SetListener(this);
	pkWinSocket->SetID(m_nTopSocketSerial++);
	m_kConnectionMap[pkWinSocket->GetID()] = pkWinSocket;

	DisplayLog(TEXT("收到来自客户端的连接！"));
}

void CcgServerUIDlg::OnClientMsg(int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID )
{
	switch (nCmd)
	{
	case CG_NETWORK_CMD_SPEEK_REQ:
		OnSpeekReq(nConnectionID, nCmd, pBuff, nBuffLen, nPlayerID);
		break;
	case CG_NETWORK_CMD_LOGIN_REQ:
		OnLoginReq(nConnectionID, nCmd, pBuff, nBuffLen, nPlayerID);
		break;
	case CG_NETWORK_CMD_PAINT_REQ:
		OnPlayerPaintReq(nConnectionID, nCmd, pBuff, nBuffLen, nPlayerID);
		break;
	case CG_NETWORK_CMD_SIMPLE_OPER_REQ:
		OnPlayerSimpleOperReq(nConnectionID, nCmd, pBuff, nBuffLen, nPlayerID);
		break;
	}
}

void CcgServerUIDlg::SendMsgToClient( cgWinSocket * pkConnection, 
	int nCmd, void * pMsgBuff, int nBuffLen )
{
	if (!pkConnection)
		return ;

	if (nBuffLen + sizeof(cgProtocolHeader) > CG_MAX_PROTOCAL_BUFF_LEN)
		return ;

	static char szSendBuff[CG_MAX_PROTOCAL_BUFF_LEN];
	memset(szSendBuff, NULL, CG_MAX_PROTOCAL_BUFF_LEN);

	cgProtocolHeader * pkHeader = (cgProtocolHeader *)szSendBuff;
	pkHeader->nHeaderFlag = CG_PROTOCOL_HEADER_FLAG;
	pkHeader->nCmd = nCmd;
	pkHeader->nPlayerID = -1;
	pkHeader->nBuffLen = nBuffLen;

	memcpy(szSendBuff+sizeof(cgProtocolHeader), pMsgBuff, nBuffLen);

	pkConnection->SendData(szSendBuff, sizeof(cgProtocolHeader)+nBuffLen);
}

// ----------------------------------------------------------------------------------------------------
cgWinSocket * CcgServerUIDlg::FindConnection( int nID )
{
	cgWinSocketMap::iterator it = m_kConnectionMap.find(nID);
	if ( it != m_kConnectionMap.end())
	{
		return it->second;
	}
	return NULL;
}
bool CcgServerUIDlg::CloseConnectionByID( int nID )
{
	cgWinSocketMap::iterator it = m_kConnectionMap.find(nID);
	if ( it != m_kConnectionMap.end())
	{
		delete it->second;
		m_kConnectionMap.erase(it);
		return true;
	}

	return false;
}


void CcgServerUIDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_MSG);
	if (pkEdit)
	{
		CString strMsg;
		pkEdit->GetWindowText(strMsg);

		string str = Unicode2UTF8(strMsg);
		NftBroadCast(str);

		strMsg = TEXT("[公告]: ")+strMsg;
		DisplayLog(strMsg);
	}
}


void CcgServerUIDlg::DisplayLog( const CString& strLog )
{
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_LOG);
	if (pkEdit)
	{
		CString strOld;
		pkEdit->GetWindowText(strOld);
		strOld += strLog;
		strOld += TEXT("\r\n");

		pkEdit->SetWindowText(strOld);
		pkEdit->LineScroll(pkEdit->GetLineCount(), 0);
	}
}


void CcgServerUIDlg::OnSpeekReq( int nConnectonID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID )
{
	cgPlayerInfo * pkSpeeker = FindOnlinePlayerByID(nPlayerID);
	if (!pkSpeeker)
		return;

	cgSpeekReq * pkReq = (cgSpeekReq*)pBuff;

	if (IsSpeekFitQuestion(pkReq->szContent))
	{
		if (nPlayerID != m_pkCurPlayer->nPlayerID && !m_kAnswerRecordMap[nPlayerID].bHasGainScore )
		{
			m_kAnswerRecordMap[nPlayerID].bHasGainScore = true;
			++m_nRightPlayerNum;

			cgPlayerActionNtf kNtf;
			kNtf.nAction = CG_PLAYER_ACTION_GUESS_RIGHT;
			kNtf.nPlayerID = nPlayerID;
			kNtf.nNameLen = pkSpeeker->nNameLen;
			memcpy(kNtf.szName, pkSpeeker->szName, kNtf.nNameLen);
			NtfMsgToPlayers(CG_NETWORK_CMD_PLAYER_ACTION_NTF, &kNtf, sizeof(kNtf));

			int nAddingScore = GetCurrentAddingScore();

			ChangePlayerAttr(pkSpeeker, CG_GAME_ATTR_TYPE_SCORE, nAddingScore, CG_PLAYER_SCORE_CHANGE_OPER_GUESS);
			ChangePlayerAttr(m_pkCurPlayer, CG_GAME_ATTR_TYPE_SCORE, nAddingScore, CG_PLAYER_SCORE_CHANGE_OPER_PAINT);

			if (m_nRightPlayerNum >= m_kPlayerInfoList.size()-1)
			{
				TurnToStage(cgRoomGameStage_TipObjectName);
			}
		}
	}else
	{
		cgSpeekNtf kNtf;
		kNtf.nSpeekerID = pkSpeeker->nPlayerID;

		kNtf.nNameLen = pkSpeeker->nNameLen;
		memcpy(kNtf.szName, pkSpeeker->szName, kNtf.nNameLen);

		kNtf.nContentLen = pkReq->nContentLen;
		memcpy(kNtf.szContent, pkReq->szContent, pkReq->nContentLen);

		kNtf.nChannel = pkReq->nChannel;

		NtfMsgToPlayers(CG_NETWORK_CMD_SPEEK_NTF, &kNtf, sizeof(kNtf));
	}
	

	CString strMsg;
	CString strName = UTF8ToUnicode(pkSpeeker->szName);
	CString strContent = UTF8ToUnicode(pkReq->szContent);
	strMsg.Format(TEXT("[聊天]<%s>%s"), (LPCTSTR)strName, (LPCTSTR)strContent);
	DisplayLog(strMsg);
}

void CcgServerUIDlg::OnLoginReq( int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID )
{
	cgLoginReq * pkReq = (cgLoginReq*)pBuff;

	cgLoginRsp kRsp;

	cgPlayerInfo * pkPlayer = m_pkPlayerMgr->AddPlayerInfo(pkReq->szAccount, pkReq->szPwd, pkReq->szName);
	if (pkPlayer)
	{
		AddPlayerToOnlineMap(pkPlayer);

		pkPlayer->nConnectionID = nConnectionID;
		kRsp.nResult = 0;
		kRsp.nID = pkPlayer->nPlayerID;

		kRsp.nScore = pkPlayer->nScore;
		kRsp.nFlowerNum = pkPlayer->nFlowerNum;
		kRsp.nEggNum = pkPlayer->nEggNum;
		kRsp.nShoeNum = pkPlayer->nShoeNum;

		kRsp.nNameLen = pkPlayer->nNameLen;
		memcpy(kRsp.szName, pkPlayer->szName, kRsp.nNameLen);

	}else
	{
		kRsp.nResult = -1;
	}

	cgWinSocket * pkReqConnection = FindConnection(nConnectionID);
	SendMsgToClient(pkReqConnection, CG_NETWORK_CMD_LOGIN_RSP, &kRsp, sizeof(kRsp));

	if (kRsp.nResult == 0)
	{

		cgPlayerActionNtf kNtf;
		kNtf.nAction = CG_PLAYER_ACTION_LOGIN;
		kNtf.nPlayerID = kRsp.nID;
		kNtf.nNameLen = pkPlayer->nNameLen;
		memcpy(kNtf.szName, pkPlayer->szName, kNtf.nNameLen);

		NtfMsgToPlayers( CG_NETWORK_CMD_PLAYER_ACTION_NTF, &kNtf, sizeof(kNtf) );

		CString strMsg;
		strMsg.Format(TEXT("<%s>进入了游戏！"), UTF8ToUnicode(pkPlayer->szName) );
		DisplayLog(strMsg);
	}
}

void CcgServerUIDlg::NtfMsgToPlayers( int nCmd, void * pBuff, int nBuffLen )
{
	cgPlayerInfoList::iterator it = m_kPlayerInfoList.begin();
	for (; it != m_kPlayerInfoList.end(); ++it)
	{
		cgPlayerInfo * pkPlayer = *it;
		cgWinSocket * pkConnection = FindConnection(pkPlayer->nConnectionID);

		if (pkConnection)
		{
			SendMsgToClient(pkConnection, nCmd, pBuff, nBuffLen);
		}
	}
}

void CcgServerUIDlg::OnPlayerPaintReq( int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID )
{
	if (m_pkCurPlayer == NULL || nPlayerID != m_pkCurPlayer->nPlayerID)
		return ;

	cgPaintReq * pkReq = (cgPaintReq*)pBuff;

	cgPaintTraceNtf kNtf;
	kNtf.nPainterID = 0;
	kNtf.nNameLen = 0;
	kNtf.kTrace = pkReq->kTrace;
	NtfMsgToPlayers(CG_NETWORK_CMD_PAINT_NTF, &kNtf, sizeof(kNtf) );
}

void CcgServerUIDlg::NftBroadCast( const string & strMsg )
{
	static cgBroadcastNtf kNtf;
	memset(&kNtf, NULL, sizeof(kNtf));
	kNtf.nType = 0;
	kNtf.nContentLen = strMsg.length()+1;
	memcpy(kNtf.szContent, strMsg.c_str(), kNtf.nContentLen);

	NtfMsgToPlayers(CG_NETWORK_CMD_BROADCAST_NTF, &kNtf, sizeof(kNtf));
}

// -------------------------------------------------------------------------------------------
cgPlayerInfo * CcgServerUIDlg::FindOnlinePlayerByID( int nPlayerID )
{
	cgPlayerInfoMap::iterator it = m_kOnlinePlayerMap.find(nPlayerID);
	if (it != m_kOnlinePlayerMap.end())
	{
		return it->second;
	}
	return NULL;
}

cgPlayerInfo * CcgServerUIDlg::AddPlayerToOnlineMap( cgPlayerInfo * pkPlayer )
{
	if (!FindOnlinePlayerByID(pkPlayer->nPlayerID))
	{
		m_kOnlinePlayerMap[pkPlayer->nPlayerID] = pkPlayer;
		m_kPlayerInfoList.push_back(pkPlayer);
	}
	return pkPlayer;
}

cgPlayerInfo * CcgServerUIDlg::DelOnlinePlayerByID( int nPlayerID )
{
	{
		cgPlayerInfoList::iterator it = m_kPlayerInfoList.begin();
		for (; it != m_kPlayerInfoList.end(); ++it)
		{
			cgPlayerInfo* pkPlayer = *it;
			if (pkPlayer->nPlayerID == nPlayerID)
			{
				m_kPlayerInfoList.erase(it);
				break;
			}
		}
	}

	cgPlayerInfoMap::iterator it = m_kOnlinePlayerMap.find(nPlayerID);
	if (it != m_kOnlinePlayerMap.end())
	{
		cgPlayerInfo * pkPlayer = it->second;
		m_kOnlinePlayerMap.erase(it);
		return pkPlayer;
	}
	
	return NULL;
}


cgPlayerInfo * CcgServerUIDlg::DelOnlinePlayerByConnectionID( int nConnection )
{
	{
		cgPlayerInfoList::iterator it = m_kPlayerInfoList.begin();
		for (; it != m_kPlayerInfoList.end(); ++it)
		{
			cgPlayerInfo* pkPlayer = *it;
			if (pkPlayer->nConnectionID == nConnection)
			{
				m_kPlayerInfoList.erase(it);
				break;
			}
		}
	}

	{
		cgPlayerInfoMap::iterator it = m_kOnlinePlayerMap.begin();
		for (;it != m_kOnlinePlayerMap.end();++it)
		{
			cgPlayerInfo * pkPlayer = it->second;
			if (pkPlayer->nConnectionID == nConnection)
			{
				m_kOnlinePlayerMap.erase(it);
				return pkPlayer;
			}
		}
	}

	return NULL;
}

cgPlayerInfo * CcgServerUIDlg::NextPlayer()
{
	cgPlayerInfo * pkPlayer = NULL;

	cgPlayerInfoList::iterator it = m_kPlayerInfoList.begin();
	if (it != m_kPlayerInfoList.end())
	{
		pkPlayer = *it;
	}

	m_kPlayerInfoList.erase(it);
	m_kPlayerInfoList.push_back(pkPlayer);

	return pkPlayer;
}

// ---------------------------------------------------------------------------------
void CcgServerUIDlg::Update( float fTime )
{
	if (m_nGameStage == cgRoomGameStage_Waiting)
	{
		if (m_kOnlinePlayerMap.size() > 1)
		{
			TurnToStage(cgRoomGameStage_TipObjectNameLen);
		}
	}else if (m_nGameStage == cgRoomGameStage_TipObjectNameLen)
	{
		if (fTime - m_fStartTime > cgGameStageEndTimes[m_nGameStage])
		{
			TurnToStage(cgRoomGameStage_TipObjectDesc);
		}
	}else if (m_nGameStage == cgRoomGameStage_TipObjectDesc)
	{
		if (fTime-m_fStartTime > cgGameStageEndTimes[m_nGameStage])
		{
			TurnToStage(cgRoomGameStage_TipObjectName);
		}
	}else if (m_nGameStage == cgRoomGameStage_TipObjectName)
	{
		if (fTime - m_fStartTime > cgGameStageEndTimes[m_nGameStage])
		{
			if (m_kPlayerInfoList.size() < 2)
				TurnToStage(cgRoomGameStage_Waiting);
			else
			{
				TurnToStage(cgRoomGameStage_TipObjectNameLen);
			}
		}
	}
}

void CcgServerUIDlg::TurnToStage( cgRoomGameStage enmStage, bool bChangePlayer /*= true*/ )
{
	m_fStartTime = ::GetTickCount()/1000.0f;

	m_nGameStage = enmStage;
	switch (enmStage)
	{
	case cgRoomGameStage_TipObjectNameLen:
		{
			if (bChangePlayer)
				m_pkCurPlayer = NextPlayer();

			m_pkCurQuestion = NextQuestion();
			m_kAnswerRecordMap.clear();
			m_nRightPlayerNum = 0;

			CString strMsg;
			strMsg.Format(TEXT("新的题目：%s"), UTF8ToUnicode(m_pkCurQuestion->strName.c_str()));
			DisplayLog(strMsg);

		}
	case cgRoomGameStage_TipObjectDesc:
	case cgRoomGameStage_TipObjectName:
		{
			cgGameStageNtf kNtf;
			memset(&kNtf, NULL, sizeof(kNtf));

			kNtf.nStage = enmStage;
			kNtf.nCurPlayerID = m_pkCurPlayer->nPlayerID;
			kNtf.nPlayerNameLen = m_pkCurPlayer->nNameLen;
			memcpy(kNtf.szPlayerName, m_pkCurPlayer->szName, kNtf.nPlayerNameLen);

			kNtf.nObjectNameLenTip = m_pkCurQuestion->nNameLen;

			kNtf.nObjectDescLen = m_pkCurQuestion->strDesc.length()+1;
			memcpy(kNtf.szObjectDesc, m_pkCurQuestion->strDesc.c_str(), kNtf.nObjectDescLen);

			kNtf.nObjectNameLen = m_pkCurQuestion->strName.length()+1;
			memcpy(kNtf.szObjectName, m_pkCurQuestion->strName.c_str(), kNtf.nObjectNameLen);

			NtfMsgToPlayers(CG_NETWORK_CMD_GAME_STAGE_NTF, &kNtf, sizeof(kNtf));
		}break;

	case cgRoomGameStage_Waiting:
		{
			cgGameStageNtf kNtf;
			memset(&kNtf, NULL, sizeof(kNtf));
			m_pkCurPlayer = NULL;

			kNtf.nStage = enmStage;

			NtfMsgToPlayers(CG_NETWORK_CMD_GAME_STAGE_NTF, &kNtf, sizeof(kNtf));
		}break;
	}
}

void CcgServerUIDlg::LoadQuestions()
{
	cgTxtDataReader kReader;

	if (!kReader.Open("./server/questions.txt"))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgQuestionConfig * pkConfig = new cgQuestionConfig;

		int nIndex = 0;
		pkConfig->strName = (pkRecord->GetField(nIndex++));
		pkConfig->nNameLen = atoi(pkRecord->GetField(nIndex++));
		pkConfig->strDesc = (pkRecord->GetField(nIndex++));

		m_kQuestionConfigList.push_back(pkConfig);
	}
}

cgQuestionConfig * CcgServerUIDlg::NextQuestion()
{
	int nNum = m_kQuestionConfigList.size();
	if (nNum < 1)
		return NULL;

	srand(GetTickCount());
	int nIndex = rand()%nNum;
	return m_kQuestionConfigList[nIndex];
}

void CcgServerUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Update(::GetTickCount()/1000.0f);
	__super::OnTimer(nIDEvent);
}

bool CcgServerUIDlg::IsSpeekFitQuestion( const string & str )
{
	if (!m_pkCurPlayer)
		return false;

	if (m_nGameStage != cgRoomGameStage_TipObjectNameLen 
		&& m_nGameStage != cgRoomGameStage_TipObjectDesc)
		return false;

	if (m_pkCurQuestion && str == m_pkCurQuestion->strName)
		return true;

	return false;
}

void CcgServerUIDlg::OnPlayerSimpleOperReq( int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID )
{
	cgPlayerInfo * pkOperPlayer = FindOnlinePlayerByID(nPlayerID);
	if (!pkOperPlayer )
		return ;

	cgGameSimpleOperReq * pkReq = (cgGameSimpleOperReq*)pBuff;

	cgGameSimpleOperNtf kNtf;
	kNtf.nOperType = pkReq->nOperType;
	kNtf.nParam1 = pkReq->nParam1;
	kNtf.nParam2 = pkReq->nParam2;
	kNtf.nPlayerID = nPlayerID;
	kNtf.nNameLen = pkOperPlayer->nNameLen;
	memcpy(kNtf.szName, pkOperPlayer->szName, kNtf.nNameLen);

	switch (pkReq->nOperType)
	{
	case CG_PLAYER_SIMPLE_OPER_UNDO_PAINT:
	case CG_PLAYER_SIMPLE_OPER_CLEAR_PAINT:
		{
			if (m_pkCurPlayer == NULL || pkOperPlayer != m_pkCurPlayer)
				return ;

			NtfMsgToPlayers(CG_NETWORK_CMD_SIMPLE_OPER_NTF, &kNtf, sizeof(kNtf));
		}
		break;
	case CG_PLAYER_SIMPLE_OPER_CHANGE_QUESTION:
		{
			// 只有画画的玩家在第一阶段可以换题
			if (m_pkCurPlayer == NULL || pkOperPlayer != m_pkCurPlayer 
				|| m_nGameStage != cgRoomGameStage_TipObjectNameLen)
				return ;

			if (!m_kAnswerRecordMap[m_pkCurPlayer->nPlayerID].bHasChangedQuestion)
			{

				TurnToStage(cgRoomGameStage_TipObjectNameLen, false);

				m_kAnswerRecordMap[m_pkCurPlayer->nPlayerID].bHasChangedQuestion = true;

				NtfMsgToPlayers(CG_NETWORK_CMD_SIMPLE_OPER_NTF, &kNtf, sizeof(kNtf));
			}

			
		}break;

	case CG_PLAYER_SIMPLE_OPER_GIVE_UP:
		{
			// 全程可放弃
			if (m_pkCurPlayer == NULL || pkOperPlayer != m_pkCurPlayer )
				return ;

			NtfMsgToPlayers(CG_NETWORK_CMD_SIMPLE_OPER_NTF, &kNtf, sizeof(kNtf));

			TurnToStage(cgRoomGameStage_TipObjectName);
		}break;

	case CG_PLAYER_SIMPLE_OPER_SEND_FLOWER:
		{
			// 非画画玩家可送花
			if (m_pkCurPlayer == NULL || pkOperPlayer == m_pkCurPlayer )
				return ;

			if (!m_kAnswerRecordMap[pkOperPlayer->nPlayerID].bHasJudged)
			{
				NtfMsgToPlayers(CG_NETWORK_CMD_SIMPLE_OPER_NTF, &kNtf, sizeof(kNtf));

				ChangePlayerAttr(m_pkCurPlayer, CG_GAME_ATTR_TYPE_FLOWER_NUM, 1, 
					CG_PLAYER_SCORE_CHANGE_OPER_BE_SEND_FLOWER);
				m_kAnswerRecordMap[pkOperPlayer->nPlayerID].bHasJudged = true;
			}
			
		}break;
	case CG_PLAYER_SIMPLE_OPER_THROW_EGG:
		{
			// 非画画玩家可扔鸡蛋
			if (m_pkCurPlayer == NULL || pkOperPlayer == m_pkCurPlayer )
				return ;

			if (!m_kAnswerRecordMap[pkOperPlayer->nPlayerID].bHasJudged)
			{
				NtfMsgToPlayers(CG_NETWORK_CMD_SIMPLE_OPER_NTF, &kNtf, sizeof(kNtf));

				ChangePlayerAttr(m_pkCurPlayer, CG_GAME_ATTR_TYPE_EGG_NUM, 1, 
					CG_PLAYER_SCORE_CHANGE_OPER_BE_THROWN_EGG);

				m_kAnswerRecordMap[pkOperPlayer->nPlayerID].bHasJudged = true;
			}
			

		}break;
	case CG_PLAYER_SIMPLE_OPER_THROW_SHOE:
		{
			// 非画画玩家可扔拖鞋
			if (m_pkCurPlayer == NULL || pkOperPlayer == m_pkCurPlayer )
				return ;

			if (!m_kAnswerRecordMap[pkOperPlayer->nPlayerID].bHasJudged)
			{
				NtfMsgToPlayers(CG_NETWORK_CMD_SIMPLE_OPER_NTF, &kNtf, sizeof(kNtf));

				ChangePlayerAttr(m_pkCurPlayer, CG_GAME_ATTR_TYPE_SHOE_NUM, 1, 
					CG_PLAYER_SCORE_CHANGE_OPER_BE_THROWN_SHOE);

				m_kAnswerRecordMap[pkOperPlayer->nPlayerID].bHasJudged = true;
			}
			
		}break;
	}
}

int CcgServerUIDlg::GetCurrentAddingScore()
{
	if (m_nGameStage == cgRoomGameStage_TipObjectNameLen)
	{
		return 2;
	}else if (m_nGameStage == cgRoomGameStage_TipObjectDesc)
	{
		return 1;
	}
	return 0;
}

void CcgServerUIDlg::ChangePlayerAttr( cgPlayerInfo * pkPlayer, int nAttrType, int nChangeValue, int nOper )
{
	CString strMsg;

	switch (nAttrType)
	{
	case CG_GAME_ATTR_TYPE_SCORE:
		{
			pkPlayer->nScore += nChangeValue;
			strMsg.Format(TEXT("<%s> 积分 +%d！"), UTF8ToUnicode(pkPlayer->szName), nChangeValue);
		}
		break;
	case CG_GAME_ATTR_TYPE_FLOWER_NUM:
		{
			pkPlayer->nFlowerNum += nChangeValue;
			strMsg.Format(TEXT("<%s> 鲜花 +%d！"), UTF8ToUnicode(pkPlayer->szName), nChangeValue);
		}break;
	case CG_GAME_ATTR_TYPE_EGG_NUM:
		{
			pkPlayer->nEggNum += nChangeValue;
			strMsg.Format(TEXT("<%s> 臭鸡蛋 +%d！"), UTF8ToUnicode(pkPlayer->szName), nChangeValue);
		}break;
	case CG_GAME_ATTR_TYPE_SHOE_NUM:
		{
			pkPlayer->nShoeNum += nChangeValue;
			strMsg.Format(TEXT("<%s> 破拖鞋 +%d！"), UTF8ToUnicode(pkPlayer->szName), nChangeValue);
		}break;
	}

	cgPlayerAttrChangeNtf kNtf;
	kNtf.nPlayerID = pkPlayer->nPlayerID;
	kNtf.nAttrType = nAttrType;
	kNtf.nChangeValue = nChangeValue;
	kNtf.nOperType = nOper;

	NtfMsgToPlayers(CG_NETWORK_CMG_ATTR_CHANGE_NTF, &kNtf, sizeof(kNtf));

}
