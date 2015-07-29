// cgLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cgClientUI.h"
#include "cgLoginDlg.h"
#include "afxdialogex.h"


// cgLoginDlg 对话框

IMPLEMENT_DYNAMIC(cgLoginDlg, CDialogEx)

cgLoginDlg::cgLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(cgLoginDlg::IDD, pParent)
{

}

cgLoginDlg::~cgLoginDlg()
{
}

void cgLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(cgLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &cgLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// cgLoginDlg 消息处理程序

BOOL cgLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TCHAR szText[MAX_PATH] = {0};

	CEdit * pkEdit = (CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT);
	if (pkEdit)
	{
		::GetPrivateProfileString(TEXT("Login"), TEXT("Account"), TEXT(""), szText, MAX_PATH, TEXT("./Login.ini"));
		pkEdit->SetWindowText(szText);
		m_strAccount = szText;
	}

	pkEdit = (CEdit *)GetDlgItem(IDC_EDIT_PWD);
	if (pkEdit)
	{
		pkEdit->SetWindowText(TEXT(""));
	}

	pkEdit = (CEdit *)GetDlgItem(IDC_EDIT_NAME);
	if (pkEdit)
	{
		::GetPrivateProfileString(TEXT("Login"), TEXT("Name"), TEXT(""), szText, MAX_PATH, TEXT("./Login.ini"));
		pkEdit->SetWindowText(szText);
		m_strName = szText;
	}

	return TRUE;
}

void cgLoginDlg::OnBnClickedOk()
{
	CEdit * pkEdit = (CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT);
	if (pkEdit)
	{
		pkEdit->GetWindowText(m_strAccount);
		WritePrivateProfileString(TEXT("Login"), TEXT("Account"), m_strAccount, TEXT("./Login.ini"));
	}

	pkEdit = (CEdit *)GetDlgItem(IDC_EDIT_PWD);
	if (pkEdit)
	{
		pkEdit->GetWindowText(m_strPwd);
	}

	pkEdit = (CEdit *)GetDlgItem(IDC_EDIT_NAME);
	if (pkEdit)
	{
		pkEdit->GetWindowText(m_strName);
		WritePrivateProfileString(TEXT("Login"), TEXT("Name"), m_strName, TEXT("./Login.ini"));
	}
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

