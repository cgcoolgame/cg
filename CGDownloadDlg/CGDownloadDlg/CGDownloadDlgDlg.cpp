
// CGDownloadDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CGDownloadDlg.h"
#include "CGDownloadDlgDlg.h"
#include "afxdialogex.h"

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


// CCGDownloadDlgDlg �Ի���




CCGDownloadDlgDlg::CCGDownloadDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCGDownloadDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCGDownloadDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCGDownloadDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CCGDownloadDlgDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCGDownloadDlgDlg ��Ϣ�������

BOOL CCGDownloadDlgDlg::OnInitDialog()
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

	m_strWorkDir = TEXT("F:\\download");
	
	int nRet = SHCreateDirectoryEx(this->m_hWnd, m_strWorkDir, NULL);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_kDownloadMgr.SetDownloadListener(this);

	/*m_kDownloadMgr.DownloadFile(TEXT("bbs.sf-express.com"),
	TEXT("forum/data/attachment/forum/201202/11/203915vrc2xgi5xkpbkz92.jpg"),
	TEXT("download/203915vrc2xgi5xkpbkz92.jpg"));*/

	/*m_kDownloadMgr.DownloadFile(TEXT("wdl.cache.ijinshan.com"),
	TEXT("wps/download/special/WPS2013.12012.exe"),
	TEXT("download/WPS2013.12012.exe"), 1);*/

	/*m_kDownloadMgr.DownloadFile(TEXT("wdl.cache.ijinshan.com"),
		TEXT("wps/download/special/WPS2013.12012.exe"),
		TEXT("download/WPS2013.12012-ex.exe"), 2);*/
	/*m_kDownloadMgr.DownloadFile(TEXT("sgwebsite.1kyou.com:8062"),
		TEXT("download/1.0.2.0001-1.0.2.0002.zip"),
		TEXT("download/1.0.2.0001-1.0.2.0002.zip"), 2);*/
	
	//DownloadFile(TEXT("sgwebsite.1kyou.com:8062/download/1.0.2.0001-1.0.2.0002.zip"));
	//DownloadFile(TEXT("http://c1.cr173.com//soft1/VisualLeakDetector.zip"));
	//DownloadFile(TEXT("http://pic2.desk.chinaz.com/file/201211/5/shierybizi7_p.jpg"));

	UINT_PTR uID = SetTimer(3, 30, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCGDownloadDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCGDownloadDlgDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCGDownloadDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CCGDownloadDlgDlg::OnDownloadProcess( const cgDownloadTask * pkDownloader )
{
	if (!pkDownloader )
		return false;

	DWORD dwTotalSize = pkDownloader->GetTotalSize();
	DWORD dwDownloadedSize = pkDownloader->GetDownloadedSize();
	DWORD dwSpeed = pkDownloader->GetSpeed();
	LPCTSTR lpctPath = pkDownloader->GetSavePath();
	float fTotalTime = 0;

	if ( dwTotalSize > 0)
	{
		CProgressCtrl * pkCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
		if (pkCtrl)
		{
			pkCtrl->SetRange(0, 100);
			pkCtrl->SetPos((int)(dwDownloadedSize*1.0/dwTotalSize*100));
		}

		CStatic * pkLabel = (CStatic*)GetDlgItem(IDC_STATIC);
		if (pkLabel)
		{
			CString str ;
			str.Format( TEXT("Downloading...\nFile = %s\nTime = %0.2f s\nSpeed = %uk/s\nTotalSpeed = %uk/s\nSize = %u/%u\nProcess = %d%%"), 
				StrRChr(lpctPath, NULL, TEXT('/'))+1, fTotalTime, dwSpeed/1000, 
				m_kDownloadMgr.GetTotalSpeed()/1000,
				dwDownloadedSize, dwTotalSize, (int)(dwDownloadedSize*1.0/dwTotalSize*100));
			pkLabel->SetWindowText(str);
		}
	}
	
	return true;
}


bool CCGDownloadDlgDlg::OnDownloadFinished(const cgDownloadTask * pkDownloader)
{
	if (!pkDownloader )
		return false;

	if (m_kDownloadMgr.GetDownloadNum() <= 0)
	{
		AfxMessageBox(TEXT("All Download Finished !"));
	}

	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	if (pkEdit)
		pkEdit->EnableWindow(TRUE);

	CButton * pkBtn = (CButton*)GetDlgItem(IDC_BUTTON1);
	if (pkBtn)
		pkBtn->EnableWindow(TRUE);

	return true;
}

bool CCGDownloadDlgDlg::OnDownloadFailed( const cgDownloadTask * pkDownloader )
{
	AfxMessageBox(TEXT("File Download Failed, please check carefully !"));

	return true;
}

// -------------------------------------------------------------------------------------------

void CCGDownloadDlgDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_kDownloadMgr.Update((float)(GetTickCount()*1.0/1000) );
	__super::OnTimer(nIDEvent);
}

bool CCGDownloadDlgDlg::DownloadFile( LPCTSTR lpctUrl )
{
	TCHAR szSavePath[MAX_PATH] = {0};

	LPCTSTR lpctSub = StrRChr(lpctUrl, NULL, TEXT('/'));
	if (lpctSub)
	{
		// ������ļ�����
		TSprintf_S(szSavePath, MAX_PATH, TEXT("%s/%s"), m_strWorkDir, lpctSub+1);
	}

	m_kDownloadMgr.DownloadFile(lpctUrl, szSavePath);


	return true;
}


void CCGDownloadDlgDlg::OnBnClickedButton1()
{
	CEdit * pkEdit = (CEdit*)GetDlgItem(IDC_EDIT1);

	if (pkEdit)
	{
		CString str;
		pkEdit->GetWindowText(str);
		if (DownloadFile(str))
		{
			pkEdit->EnableWindow(FALSE);

			CButton * pkBtn = (CButton*)GetDlgItem(IDC_BUTTON1);
			if (pkBtn)
			{
				pkBtn->EnableWindow(FALSE);
			}
		}
	}
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

