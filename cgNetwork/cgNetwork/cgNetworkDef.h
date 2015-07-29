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

// 退出游戏
#define CG_NETWORK_CMD_LOGOUT_REQ	2020

// 登陆
#define CG_NETWORK_CMD_LOGIN_REQ	1001
#define CG_NETWORK_CMD_LOGIN_RSP	1002

// 讲话
#define CG_NETWORK_CMD_SPEEK_REQ	1003
#define CG_NETWORK_CMD_SPEEK_RSP	1004
#define CG_NETWORK_CMD_SPEEK_NTF	1005

// 公告ntf
#define CG_NETWORK_CMD_BROADCAST_NTF	1006

// 进入、离开房间通知
#define CG_NETWORK_CMD_PLAYER_ACTION_NTF	1007

// 绘制协议
#define CG_NETWORK_CMD_PAINT_REQ	1009
#define CG_NETWORK_CMD_PAINT_RSP	1010
#define CG_NETWORK_CMD_PAINT_NTF	1011

// 游戏状态通知
#define CG_NETWORK_CMD_GAME_STAGE_NTF 1012

// 简单操作
#define CG_NETWORK_CMD_SIMPLE_OPER_REQ 1013
#define CG_NETWORK_CMD_SIMPLE_OPER_NTF 1014

// 分数广播
#define CG_NETWORK_CMG_ATTR_CHANGE_NTF 1015

/************************************************************************/
/*                                                                      */
/************************************************************************/

// ------------------------------------------------------------------------
// 简单的通信协议
#define CG_MAX_PROTOCAL_BUFF_LEN (1024*128)


// ------------------------------------------------------------------------
// 登陆
#define CG_MAX_ACCOUNT_LEN	128
#define CG_MAX_PWD_LEN		32
#define CG_MAX_NAME_LEN		32


// ------------------------------------------------------------------------
// 聊天
#define CG_MAX_SPEEK_CONTENT_LEN	256

#define CG_SPEEK_CHANNEL_ALL	0			// 大厅频道
#define CG_SPEEK_CHANNEL_WHISPER	1		// 私聊


// ------------------------------------------------------------------------
// 公告
#define CG_MAX_BROADCAST_CONTENT_LEN	512

// ------------------------------------------------------------------------
// 玩家行为通知
#define CG_PLAYER_ACTION_REGISTER	0	// 注册
#define CG_PLAYER_ACTION_LOGIN		1	// 登陆
#define CG_PLAYER_ACTION_LOGOUT		2	// 下线
#define CG_PLAYER_ACTION_GUESS_RIGHT	3	// 猜中答案


// ------------------------------------------------------------------------
// 绘制轨迹
#define CG_MAX_PAINT_TRACE_POINT_NUM 32


// ------------------------------------------------------------------------
// 游戏状态通知
enum cgRoomGameStage
{
	cgRoomGameStage_TipObjectNameLen = 0, // 提示名字长度
	cgRoomGameStage_TipObjectDesc = 1,	// 提示事物的描述
	cgRoomGameStage_TipObjectName = 2,	// 提示名字
	cgRoomGameStage_Waiting = 3,		// 等待中
};

static const int cgGameStageEndTimes[] = {15, 45, 8};


// ------------------------------------------------------------------------
// 简单操作
#define CG_PLAYER_SIMPLE_OPER_UNDO_PAINT 0		// 撤销
#define CG_PLAYER_SIMPLE_OPER_CLEAR_PAINT	1	// 清空

#define CG_PLAYER_SIMPLE_OPER_CHANGE_QUESTION	2	// 换题
#define CG_PLAYER_SIMPLE_OPER_GIVE_UP			3	// 放弃

#define CG_PLAYER_SIMPLE_OPER_SEND_FLOWER	4	// 送花
#define CG_PLAYER_SIMPLE_OPER_THROW_EGG		5	// 砸鸡蛋
#define CG_PLAYER_SIMPLE_OPER_THROW_SHOE		6	// 扔拖鞋


// ------------------------------------------------------------------------
// 属性广播
#define CG_GAME_ATTR_TYPE_SCORE	0	// 分数
#define CG_GAME_ATTR_TYPE_FLOWER_NUM	1	// 分数
#define CG_GAME_ATTR_TYPE_EGG_NUM	2	// 分数
#define CG_GAME_ATTR_TYPE_SHOE_NUM	3	// 分数

// 分数变化的原因
#define CG_PLAYER_SCORE_CHANGE_OPER_GUESS	0	// 猜中
#define CG_PLAYER_SCORE_CHANGE_OPER_PAINT	1	// 绘画被猜

#define CG_PLAYER_SCORE_CHANGE_OPER_BE_SEND_FLOWER	2	// 被送鲜花
#define CG_PLAYER_SCORE_CHANGE_OPER_BE_THROWN_EGG	3	// 被扔鸡蛋
#define CG_PLAYER_SCORE_CHANGE_OPER_BE_THROWN_SHOE	4	// 被送鲜花

#endif // cgNetworkDef_h__

