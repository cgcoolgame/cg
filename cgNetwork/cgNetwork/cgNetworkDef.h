#ifndef cgNetworkDef_h__
#define cgNetworkDef_h__

class cgNetworkDef
{
public:
	cgNetworkDef(void);
	~cgNetworkDef(void);

public:
	static bool NetworkInit();
	static void NetworkDestroy();
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define	CG_NETWORK_CMD_BEGIN	1000

// �˳���Ϸ
#define CG_NETWORK_CMD_LOGOUT_REQ	2020

// ��½
#define CG_NETWORK_CMD_LOGIN_REQ	1001
#define CG_NETWORK_CMD_LOGIN_RSP	1002

// ����
#define CG_NETWORK_CMD_SPEEK_REQ	1003
#define CG_NETWORK_CMD_SPEEK_RSP	1004
#define CG_NETWORK_CMD_SPEEK_NTF	1005

// ����ntf
#define CG_NETWORK_CMD_BROADCAST_NTF	1006

// ���롢�뿪����֪ͨ
#define CG_NETWORK_CMD_PLAYER_ACTION_NTF	1007

// ����Э��
#define CG_NETWORK_CMD_PAINT_REQ	1009
#define CG_NETWORK_CMD_PAINT_RSP	1010
#define CG_NETWORK_CMD_PAINT_NTF	1011

// ��Ϸ״̬֪ͨ
#define CG_NETWORK_CMD_GAME_STAGE_NTF 1012

// �򵥲���
#define CG_NETWORK_CMD_SIMPLE_OPER_REQ 1013
#define CG_NETWORK_CMD_SIMPLE_OPER_NTF 1014

// �����㲥
#define CG_NETWORK_CMG_ATTR_CHANGE_NTF 1015

/************************************************************************/
/*                                                                      */
/************************************************************************/

// ------------------------------------------------------------------------
// �򵥵�ͨ��Э��
#define CG_MAX_PROTOCAL_BUFF_LEN (1024*128)


// ------------------------------------------------------------------------
// ��½
#define CG_MAX_ACCOUNT_LEN	128
#define CG_MAX_PWD_LEN		32
#define CG_MAX_NAME_LEN		32


// ------------------------------------------------------------------------
// ����
#define CG_MAX_SPEEK_CONTENT_LEN	256

#define CG_SPEEK_CHANNEL_ALL	0			// ����Ƶ��
#define CG_SPEEK_CHANNEL_WHISPER	1		// ˽��


// ------------------------------------------------------------------------
// ����
#define CG_MAX_BROADCAST_CONTENT_LEN	512

// ------------------------------------------------------------------------
// �����Ϊ֪ͨ
#define CG_PLAYER_ACTION_REGISTER	0	// ע��
#define CG_PLAYER_ACTION_LOGIN		1	// ��½
#define CG_PLAYER_ACTION_LOGOUT		2	// ����
#define CG_PLAYER_ACTION_GUESS_RIGHT	3	// ���д�


// ------------------------------------------------------------------------
// ���ƹ켣
#define CG_MAX_PAINT_TRACE_POINT_NUM 32


// ------------------------------------------------------------------------
// ��Ϸ״̬֪ͨ
enum cgRoomGameStage
{
	cgRoomGameStage_TipObjectNameLen = 0, // ��ʾ���ֳ���
	cgRoomGameStage_TipObjectDesc = 1,	// ��ʾ���������
	cgRoomGameStage_TipObjectName = 2,	// ��ʾ����
	cgRoomGameStage_Waiting = 3,		// �ȴ���
};

static const int cgGameStageEndTimes[] = {15, 45, 8};


// ------------------------------------------------------------------------
// �򵥲���
#define CG_PLAYER_SIMPLE_OPER_UNDO_PAINT 0		// ����
#define CG_PLAYER_SIMPLE_OPER_CLEAR_PAINT	1	// ���

#define CG_PLAYER_SIMPLE_OPER_CHANGE_QUESTION	2	// ����
#define CG_PLAYER_SIMPLE_OPER_GIVE_UP			3	// ����

#define CG_PLAYER_SIMPLE_OPER_SEND_FLOWER	4	// �ͻ�
#define CG_PLAYER_SIMPLE_OPER_THROW_EGG		5	// �Ҽ���
#define CG_PLAYER_SIMPLE_OPER_THROW_SHOE		6	// ����Ь


// ------------------------------------------------------------------------
// ���Թ㲥
#define CG_GAME_ATTR_TYPE_SCORE	0	// ����
#define CG_GAME_ATTR_TYPE_FLOWER_NUM	1	// ����
#define CG_GAME_ATTR_TYPE_EGG_NUM	2	// ����
#define CG_GAME_ATTR_TYPE_SHOE_NUM	3	// ����

// �����仯��ԭ��
#define CG_PLAYER_SCORE_CHANGE_OPER_GUESS	0	// ����
#define CG_PLAYER_SCORE_CHANGE_OPER_PAINT	1	// �滭����

#define CG_PLAYER_SCORE_CHANGE_OPER_BE_SEND_FLOWER	2	// �����ʻ�
#define CG_PLAYER_SCORE_CHANGE_OPER_BE_THROWN_EGG	3	// ���Ӽ���
#define CG_PLAYER_SCORE_CHANGE_OPER_BE_THROWN_SHOE	4	// �����ʻ�

#endif // cgNetworkDef_h__

