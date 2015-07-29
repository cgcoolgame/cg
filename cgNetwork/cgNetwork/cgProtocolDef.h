
#ifndef cgProtocolDef_h__
#define cgProtocolDef_h__
#include "cgNetworkDef.h"

// ------------------------------------------------------------------------
#define CG_PROTOCOL_HEADER_FLAG	19880621
// �������Э��
struct cgProtocolHeader
{
	int nHeaderFlag;
	int nCmd;
	int nPlayerID;
	int nBuffLen;
	//char szBuff[CG_MAX_PROTOCAL_BUFF_LEN];
};

// ͨ�õĻذ�
struct cgCommonRsp
{
	int nResult;
};
// ------------------------------------------------------------------------
// ��½
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
	int nResult;	// �Ƿ�ɹ�

	int nID;		// id

	int nScore;
	int nFlowerNum;
	int nEggNum;
	int nShoeNum;

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];
};
// ------------------------------------------------------------------------
// ����
struct cgSpeekReq
{
	int nChannel;

	int nContentLen;
	char szContent[CG_MAX_SPEEK_CONTENT_LEN];

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];
};
// �ذ���ͨ�õ�

// ֪ͨ
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
// ��Ϸ�ڹ���
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
// ����
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
// ��Ϸ״̬֪ͨ
struct cgGameStageNtf
{
	int nStage;

	int nCurPlayerID;

	int nPlayerNameLen;
	char szPlayerName[CG_MAX_NAME_LEN];

	int nObjectNameLenTip;	// ���ֳ�����ʾ

	int nObjectDescLen;
	char szObjectDesc[CG_MAX_NAME_LEN];	// ����

	int nObjectNameLen;
	char szObjectName[CG_MAX_NAME_LEN];
};

// -------------------------------------------------------------------------------------
// ��Ϸ����
struct cgGameSimpleOperReq
{
	int nOperType;
	int nParam1;
	int nParam2;
};

// ��Ϸ����֪ͨ
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
// �����㲥
// �����仯��ԭ��
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
