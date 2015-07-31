
// CGDownloadDlgDlg.h : ͷ�ļ�
//

#pragma once
#include "..\..\CGGame\CGDownload\CGDownloadManager.h"


// CCGDownloadDlgDlg �Ի���
class CCGDownloadDlgDlg : public CDialogEx, cgDownloadListener
{
// ����
public:
	CCGDownloadDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CGDOWNLOADDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	bool DownloadFile(LPCTSTR lpctUrl);

	virtual bool OnDownloadProcess(const cgDownloadTask * pkDownloader );
	virtual bool OnDownloadFinished(const cgDownloadTask * pkDownloader);
	virtual bool OnDownloadFailed(const cgDownloadTask * pkDownloader);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	cgDownloadManager m_kDownloadMgr;
	CString m_strWorkDir;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
};
