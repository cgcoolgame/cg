
// cgServerUIDlg.h : 头文件
//

#pragma once
#include "..\cgNetwork\cgWinSocket.h"
#include <list>
#include <map>
#include "cgPlayerInfoManager.h"
#include <vector>

typedef std::map<int ,cgWinSocket * > cgWinSocketMap;

typedef std::list<cgPlayerInfo* > cgPlayerInfoList;

struct cgQuestionConfig
{
	string strName;
	int nNameLen;
	string strDesc;
};

typedef std::vector<cgQuestionConfig*> cgQuestionConfigList; 


struct cgSingleAnswerRecord
{
	cgSingleAnswerRecord()
	{
		bHasGainScore = false;
		bHasChangedQuestion = false;
		bHasJudged = false;
		bHasAddedTime = false;
	}

	bool bHasGainScore;
	bool bHasChangedQuestion;
	bool bHasJudged;
	bool bHasAddedTime;
};

// CcgServerUIDlg 对话框
class CcgServerUIDlg : public CDialogEx,
	cgSocketListener
{
// 构造
public:
	CcgServerUIDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CcgServerUIDlg();
// 对话框数据
	enum { IDD = IDD_CGSERVERUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	// 创建和销毁
	virtual void OnCreate(int nID, int nError);
	virtual void OnClose(int nID, int nError);

	// 收发数据
	virtual void OnSend(int nID, int nError);
	virtual void OnReceive(int nID, int nError);

	virtual void OnAccept(int nID, int nError);

protected:
	cgWinSocket * FindConnection(int nID);
	bool CloseConnectionByID(int nID);

	cgPlayerInfo * FindOnlinePlayerByID(int nPlayerID);
	cgPlayerInfo * AddPlayerToOnlineMap(cgPlayerInfo * pkPlayer);
	cgPlayerInfo * DelOnlinePlayerByID(int nPlayerID);
	cgPlayerInfo * DelOnlinePlayerByConnectionID(int nConnection);

	void DisplayLog(const CString& strLog);

	cgPlayerInfo * NextPlayer();
	cgQuestionConfig * NextQuestion();

	void Update(float fTime);

	void TurnToStage(cgRoomGameStage enmStage, bool bChangePlayer = true);

	void LoadQuestions();

	bool IsSpeekFitQuestion(const string & str);
	int GetCurrentAddingScore();

	void ChangePlayerAttr(cgPlayerInfo * pkPlayer, int nAttrType, int nChangeValue, int nOper);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonCreate();

private:
	int m_nTopSocketSerial;
	cgWinSocket * m_pkSvrSocket;
	cgWinSocketMap	m_kConnectionMap;

	cgPlayerInfoManager * m_pkPlayerMgr;
	cgPlayerInfoMap m_kOnlinePlayerMap;
	cgPlayerInfoList m_kPlayerInfoList;
	cgPlayerInfo * m_pkCurPlayer;

	cgQuestionConfigList m_kQuestionConfigList;
	cgQuestionConfig * m_pkCurQuestion;
	std::map<int , cgSingleAnswerRecord > m_kAnswerRecordMap;
	int m_nRightPlayerNum;

	int m_nGameStage;
	float m_fStartTime;

public:
	afx_msg void OnBnClickedButtonSend();

protected:
	void OnClientMsg(int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID);
	void SendMsgToClient(cgWinSocket * pkConnection, int nCmd, void * pBuff, int nBuffLen);
	void NtfMsgToPlayers(int nCmd, void * pBuff, int nBuffLen);

protected:
	void OnSpeekReq(int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID);
	void OnLoginReq(int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID);
	void NftBroadCast(const string & strMsg);
	void OnPlayerPaintReq(int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID);
	void OnPlayerSimpleOperReq(int nConnectionID, int nCmd, void * pBuff, int nBuffLen, int nPlayerID);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
