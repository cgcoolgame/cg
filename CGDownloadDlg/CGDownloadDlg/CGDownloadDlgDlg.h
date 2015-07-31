
// CGDownloadDlgDlg.h : 头文件
//

#pragma once
#include "..\..\CGGame\CGDownload\CGDownloadManager.h"


// CCGDownloadDlgDlg 对话框
class CCGDownloadDlgDlg : public CDialogEx, cgDownloadListener
{
// 构造
public:
	CCGDownloadDlgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CGDOWNLOADDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	bool DownloadFile(LPCTSTR lpctUrl);

	virtual bool OnDownloadProcess(const cgDownloadTask * pkDownloader );
	virtual bool OnDownloadFinished(const cgDownloadTask * pkDownloader);
	virtual bool OnDownloadFailed(const cgDownloadTask * pkDownloader);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
