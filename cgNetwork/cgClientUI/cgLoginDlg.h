#pragma once


// cgLoginDlg �Ի���

class cgLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(cgLoginDlg)

public:
	cgLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~cgLoginDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

	const CString & GetAccount(){return m_strAccount;}
	const CString & GetPwd(){return m_strPwd;}
	const CString & GetName(){return m_strName;}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CString m_strAccount;
	CString m_strPwd;
	CString m_strName;
public:
	afx_msg void OnBnClickedOk();
};
