
// cgClientUIDlg.h : 头文件
//

#pragma once
#include "..\cgNetwork\cgWinSocket.h"
#include <list>
#include "..\cgNetwork\cgNetworkDef.h"
#include "..\cgNetwork\cgProtocolDef.h"

typedef std::list<cgPaintTrace> cgPaintTraceList;

// CcgClientUIDlg 对话框
class CcgClientUIDlg : public CDialogEx,
	public cgSocketListener
{
// 构造
public:
	CcgClientUIDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CcgClientUIDlg();
// 对话框数据
	enum { IDD = IDD_CGCLIENTUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	// 创建和销毁
	virtual void OnCreate(int nID, int nError);
	virtual void OnClose(int nID, int nError);

	// 连接和断连
	virtual void OnConnect(int nID, int nError);

	// 收发数据
	virtual void OnSend(int nID, int nError);
	virtual void OnReceive(int nID, int nError);
protected:

	void ConnectServer();

	void DisplayMsg(const CString &strMsg);
	void ShowQuestionDesc(const CString & strMsg);
	void UpdateTimerString();
	void AddPointToMyTrace(int x, int y);

	void ClientPaint();
	void DrawTrace(CPaintDC & dc, const cgPaintTrace & kTrace);
	bool CanPaint();
	void ShowAttrs();
	void ShowName();

	void EnableBtn(int nID, bool bEnable);
	void EnablePaintBtns(bool bEnable);
	void EnableJudgeBtns(bool bEnable);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	int m_nLocalPlayerID;
	int m_nLocalPlayerScore;
	int m_nLocalPlayerFlower;
	int m_nLocalPlayerEggNum;
	int m_nLocalPlayerShoeNum;
	CString m_strLocalPlayerName;

	cgWinSocket * m_pkClientSocket;
	cgPaintTraceList m_kPaintTraceList;	// 收到的轨迹
	cgPaintTrace m_kMyTrace;		// 我的轨迹
	bool m_bIsPainting;
	
	cgGameStageNtf m_kGameStage;
	int m_nFinishTime;

	RECT m_kCanvasRect;
public:
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnIDOk();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	

protected:
	void OnSvrMsg(int nCmd, void * pBuff, int nLen);
	void ReqSendData(int nCmd, void * pDataBuff, int nLen);

protected:
	void OnLoginRsp(int nCmd, void * pBuff, int nLen);

	void OnSpeekRsp(int nCmd, void * pBuff, int nLen);
	void OnSpeekNtf(int nCmd, void * pBuff, int nLen);

	void OnPlayerAction(int nCmd, void * pBuff, int nLen);
	void OnPlayerPaintNtf(int nCmd, void * pBuff, int nLen);
	void OnBroadcastNtf(int nCmd, void * pBuff, int nLen);
	void OnGameStageNtf(int nCmd, void * pBuff, int nLen);
	void OnGameSimpleOperNtf(int nCmd, void * pBuff, int nLen);
	void OnPlayerAttrChangeNtf(int nCmd, void * pBuff, int nLen);

	void UpdateCanvas(bool bClear = true);

public:
	void ReqLogin();
	void ReqSpeek(int nChannel, const string & strMsg);
	void ReqSendTrace();


	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonShoe();
	afx_msg void OnBnClickedButtonEgg();
	afx_msg void OnBnClickedButtonFlower();
	afx_msg void OnBnClickedButtonGiveUp();
};
