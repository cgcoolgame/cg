
// cgClientUIDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CcgClientUIDlg �Ի���




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


// CcgClientUIDlg ��Ϣ�������

BOOL CcgClientUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ConnectServer();
	
	memset(&m_kGameStage, NULL, sizeof(m_kGameStage));
	m_kGameStage.nStage = cgRoomGameStage_Waiting;
	m_nFinishTime = 0;

	m_kCanvasRect.left=5;
	m_kCanvasRect.top = 15;
	m_kCanvasRect.right=m_kCanvasRect.left+764;
	m_kCanvasRect.bottom=m_kCanvasRect.top+548;

	SetTimer(NULL, 1000, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcgClientUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcgClientUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ----------------------------------------------------------------------------------------------------

void CcgClientUIDlg::ConnectServer()
{
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	DisplayMsg(TEXT("[ϵͳ] �ͻ��������ʼ���ɹ���"));
}

void CcgClientUIDlg::OnClose( int nID, int nError )
{
	AfxMessageBox(TEXT("�ͻ�������رգ�"));
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
		strMsg.Format(TEXT("����������ʧ�ܣ�%d"), nError);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			strMsg.Format(TEXT("ʣ��ʱ�䣺%d"), (m_nFinishTime-GetTickCount())/1000);
		}else if (m_kGameStage.nStage == cgRoomGameStage_TipObjectName)
		{
			strMsg.Format(TEXT("����ʱ�䣺%d"), (m_nFinishTime-GetTickCount())/1000);
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
		strMsg.Format(TEXT("����:%d �ʻ�:%d ����:%d ��Ь:%d"), 
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
	// TODO: �ڴ���������������
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

		DisplayMsg(TEXT("[ϵͳ] ��Ϸ��½�ɹ���"));
		CString strMsg;
		strMsg.Format(TEXT(">>��ɫ���֣�%s\r\n>>��ɫID��%d\r\n>>���֣�%d"), 
			(LPCTSTR)m_strLocalPlayerName, pkRsp->nID, pkRsp->nScore);

		DisplayMsg(strMsg);
		ShowAttrs();
		ShowName();

		EnableJudgeBtns(false);
		EnablePaintBtns(false);

	}else
	{
		AfxMessageBox(TEXT("��Ϸ��½ʧ�ܣ�"));
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
	strMsg.Format(TEXT("[����] <%s>%s"), (LPCTSTR)strName, (LPCTSTR)strContent);

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
		strMsg.Format(TEXT("[ϵͳ] ��ӭ<%s>������Ϸ��"), (LPCTSTR)strName);
		break;
	case CG_PLAYER_ACTION_LOGOUT:
		strMsg.Format(TEXT("[ϵͳ] <%s>�����ˣ�"), (LPCTSTR)strName);
		break;
	case CG_PLAYER_ACTION_GUESS_RIGHT:
		strMsg.Format(TEXT("[ϵͳ] <%s>�����˴𰸣�"), (LPCTSTR)strName);
		break;
	}

	DisplayMsg(strMsg);
}


void CcgClientUIDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	__super::OnLButtonDown(nFlags, point);
}

void CcgClientUIDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (CanPaint() && m_bIsPainting)
	{
		m_bIsPainting = false;
		ReqSendTrace();
	}
	__super::OnLButtonUp(nFlags, point);
}

void CcgClientUIDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	strMsg.Format(TEXT("[����] %s"), UTF8ToUnicode(pkNtf->szContent));
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
				strMsg.Format(TEXT("[ϵͳ] ������<%s>��ʼ��ͼ��"), (LPCTSTR)strName);
				DisplayMsg(strMsg);

				strMsg.Format(TEXT("[�����£�] %d ���֣�"), pkNtf->nObjectNameLenTip);
				//	DisplayMsg(strMsg);
				ShowQuestionDesc(strMsg);
				EnablePaintBtns(false);

			}else
			{
				CString strName = UTF8ToUnicode(pkNtf->szObjectName);
				CString strMsg;
				strMsg.Format(TEXT("[ϵͳ] �������㿪ʼ��ͼ��"));
				DisplayMsg(strMsg);

				strMsg.Format(TEXT("[��������] �����ĿΪ��%s"), (LPCTSTR)strName);
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

				strMsg.Format(TEXT("[�����£�] %d ���֣�%s"), pkNtf->nObjectNameLenTip, (LPCTSTR)strDesc);
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

			strMsg.Format(TEXT("[������] �𰸣�%s(%d ���֣�%s)"), (LPCTSTR)strObjectName,
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
			ShowQuestionDesc(TEXT("�������㣬��ȴ���"));
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

			strMsg.Format(TEXT("[ϵͳ] <%s>��������һ�����ƣ�"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_CLEAR_PAINT:
		{
			if (!m_kPaintTraceList.empty())
			{
				m_kPaintTraceList.clear();
				UpdateCanvas(true);
			}
			strMsg.Format(TEXT("[ϵͳ] <%s>����˻��壡"), UTF8ToUnicode(pkNtf->szName) );
		}break;

	case CG_PLAYER_SIMPLE_OPER_CHANGE_QUESTION:
		{
			// ����
			strMsg.Format(TEXT("[ϵͳ] <%s>��������Ŀ��"), UTF8ToUnicode(pkNtf->szName) );
			EnableBtn(IDC_BUTTON_CHANGE, false);
		}break;
	case CG_PLAYER_SIMPLE_OPER_GIVE_UP:
		{
			// ����
			strMsg.Format(TEXT("[ϵͳ] <%s>�����˻��ƣ����Ͽ�ʼ��һ�֣�"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_SEND_FLOWER:
		{
			// �ʻ�
			strMsg.Format(TEXT("[ϵͳ] <%s>Ϊ�滭������һ���ʻ���"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_THROW_EGG:
		{
			// �Ӽ���
			strMsg.Format(TEXT("[ϵͳ] <%s>��滭������һ�ų�������"), UTF8ToUnicode(pkNtf->szName) );
		}break;
	case CG_PLAYER_SIMPLE_OPER_THROW_SHOE:
		{
			// ����Ь
			strMsg.Format(TEXT("[ϵͳ] <%s>��滭������һֻ����Ь��"), UTF8ToUnicode(pkNtf->szName) );
		}break;

	}
	DisplayMsg(strMsg);

}

void CcgClientUIDlg::OnPlayerAttrChangeNtf( int nCmd, void * pBuff, int nLen )
{
	cgPlayerAttrChangeNtf * pkNtf = (cgPlayerAttrChangeNtf*)pBuff;
	
	// ��ʱֻ�����Լ�������
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
				strMsg.Format(TEXT("[ϵͳ] ���� +%d ! ���ò������˲����ˣ�"), pkNtf->nChangeValue);
			}else if (pkNtf->nOperType == CG_PLAYER_SCORE_CHANGE_OPER_GUESS)
			{
				strMsg.Format(TEXT("[ϵͳ] ���� +%d ! �����ǣ����������Բ��У�"), pkNtf->nChangeValue);
			}
		}break;
	case CG_GAME_ATTR_TYPE_FLOWER_NUM:
		{
			m_nLocalPlayerFlower += pkNtf->nChangeValue;
			strMsg.Format(TEXT("[ϵͳ] �ʻ� +%d"), pkNtf->nChangeValue);
		}break;
	case CG_GAME_ATTR_TYPE_EGG_NUM:
		{
			m_nLocalPlayerEggNum += pkNtf->nChangeValue;
			strMsg.Format(TEXT("[ϵͳ] ������ +%d"), pkNtf->nChangeValue);
		}break;
	case CG_GAME_ATTR_TYPE_SHOE_NUM:
		{
			m_nLocalPlayerShoeNum += pkNtf->nChangeValue;
			strMsg.Format(TEXT("[ϵͳ] ����Ь +%d"), pkNtf->nChangeValue);
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


