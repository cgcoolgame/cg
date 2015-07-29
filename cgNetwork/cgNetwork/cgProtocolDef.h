
#ifndef cgProtocolDef_h__
#define cgProtocolDef_h__
#include "cgNetworkDef.h"

// ------------------------------------------------------------------------
#define CG_PROTOCOL_HEADER_FLAG	19880621
// 最基本的协议
struct cgProtocolHeader
{
	int nHeaderFlag;
	int nCmd;
	int nPlayerID;
	int nBuffLen;
	//char szBuff[CG_MAX_PROTOCAL_BUFF_LEN];
};

// 通用的回包
struct cgCommonRsp
{
	int nResult;
};
// ------------------------------------------------------------------------
// 登陆
struct cgLoginReq
{
	int nAccountLen;
	char szAccount[CG_MAX_ACCOUNT_LEN];

	int nPwdLen;
	char szPwd[CG_MAX_PWD_LEN];

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];
};
struct cgLoginRsp
{
	int nResult;	// 是否成功

	int nID;		// id

	int nScore;
	int nFlowerNum;
	int nEggNum;
	int nShoeNum;

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];
};
// ------------------------------------------------------------------------
// 聊天
struct cgSpeekReq
{
	int nChannel;

	int nContentLen;
	char szContent[CG_MAX_SPEEK_CONTENT_LEN];

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];
};
// 回包用通用的

// 通知
struct cgSpeekNtf
{
	int nChannel;
	int nSpeekerID;

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];

	int nContentLen;
	char szContent[CG_MAX_SPEEK_CONTENT_LEN];
};
// ------------------------------------------------------------------------
// 游戏内公告
struct cgBroadcastNtf
{
	int nType;

	int nContentLen;
	char szContent[CG_MAX_BROADCAST_CONTENT_LEN];
};
// ------------------------------------------------------------------------
struct cgPlayerActionNtf
{
	int nPlayerID;

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];

	int nAction;
};

// ------------------------------------------------------------------------
// 绘制
struct cgPoint
{
	int x;
	int y;
};
struct cgPaintTrace
{
	int nNum;
	cgPoint kPoints[CG_MAX_PAINT_TRACE_POINT_NUM];
};

struct cgPaintReq
{
	cgPaintTrace kTrace;
};

struct cgPaintTraceNtf
{
	int nPainterID;

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];

	cgPaintTrace kTrace;
};
// ------------------------------------------------------------------------
// 游戏状态通知
struct cgGameStageNtf
{
	int nStage;

	int nCurPlayerID;

	int nPlayerNameLen;
	char szPlayerName[CG_MAX_NAME_LEN];

	int nObjectNameLenTip;	// 名字长度提示

	int nObjectDescLen;
	char szObjectDesc[CG_MAX_NAME_LEN];	// 描述

	int nObjectNameLen;
	char szObjectName[CG_MAX_NAME_LEN];
};

// -------------------------------------------------------------------------------------
// 游戏操作
struct cgGameSimpleOperReq
{
	int nOperType;
	int nParam1;
	int nParam2;
};

// 游戏操作通知
struct cgGameSimpleOperNtf
{
	int nOperType;
	int nParam1;
	int nParam2;

	int nPlayerID;

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];
};

// ------------------------------------------------------------------------
// 分数广播
// 分数变化的原因
struct cgGameScoreChangeNtf
{
	int nPlayerID;
	int nChangedScore;
	int nOperType;
};

struct cgPlayerAttrChangeNtf
{
	int nPlayerID;

	int nAttrType;
	int nChangeValue;

	int nOperType;
};

#endif // cgProtocolDef_h__
