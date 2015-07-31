#ifndef cgGameMessage_h__
#define cgGameMessage_h__


// 游戏内部消息，和OnMessage和OnWinMessage的消息不一样
// 专用于OnGameMessage，游戏内部消息和系统消息《暂时》分开处理

typedef int cgGameMessage;

// -------------------------------------------------------------------------------

//	这里定义框架消息
static const cgGameMessage cgGameMessage_GameAppInitialized = 1;
static const cgGameMessage cgGameMessage_LogoStarted = 2;
static const cgGameMessage cgGameMessage_LogoFinished = 3;

// -------------------------------------------------------------------------------

// 给具体游戏使用的消息从10000开始，
// 小于这个值的消息只能框架来使用
// 为了防止id冲突，请不要乱用
static const cgGameMessage cgUserGameMessageBegin = 10000;	


// -------------------------------------------------------------------------------



#endif // cgGameMessage_h__
