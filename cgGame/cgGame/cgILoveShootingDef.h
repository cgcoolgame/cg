#ifndef _cgILoveShootingDef_h__
#define _cgILoveShootingDef_h__
#include "cgGameMessage.h"
#include "cgSmartPointer.h"

/**
*	飞行物体的阵营，用于敌我判断，阵营说明：
*	中立阵营：只攻击毁灭者
*	玩家阵营：攻击电脑阵营和毁灭者
*	电脑阵营：攻击玩家阵营和毁灭者
*	毁灭者阵营：攻击所有的阵营，包括毁灭者阵营
**/
enum cgFlyObjectCamp
{
	cgFlyObjectCamp_None = 0,	// 中立，无阵营
	cgFlyObjectCamp_Self = 1,	// 玩家阵营，自己方
	cgFlyObjectCamp_Enemy = 2,	// 敌方阵营，电脑
	cgFlyObjectCamp_Destroyer = 3,// 毁灭者阵营
};


/**
*	飞行物体的状态，状态说明：
*	无状态：不使用
*	激活状态：正常的激活状态，可见、可操作、可攻击
*	死亡状态：死亡后不会立马清除，而是要保留一阵，这个时候就是死亡状态
*	无效状态：死亡后一段时间，就会转变成无效状态，为清理做准备
**/
enum cgFlyObjectState
{
	cgFlyObjectState_None = 0,			// 无状态
	cgFlyObjectState_Active = 1,		// 激活状态
	cgFlyObjectState_Dead = 2,		// 死亡
	cgFlyObjectState_Invalid = 3,	// 无效
};
// ---------------------------------------------------------------------------------
// 游戏内部消息定义
static const cgGameMessage cgGameMessage_AircraftOutOfScreen = cgUserGameMessageBegin+1;
static const cgGameMessage cgGameMessage_AircraftBeKilled = cgUserGameMessageBegin+2;


// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// 子弹配置
// 子弹的配置只是表示它的表现
// 子弹的实际攻击= 子弹自身攻击+武器攻击
// 下面只是普通子弹的配置
// 高级子弹包括：导弹、激光
struct cgBulletConfig
{
	int nID;				// 子弹的类型id
	int nAttack;			// 子弹自身攻击
	int nSpeed;				// 子弹的速度
	int nHitSoundID;		// 子弹的击中声效
	int nBoundW;
	int nBoundH;		

	cgString strName;		// 子弹名字
	cgString strModel;		// 子弹的模型
	cgString strDesc;		// 子弹描述

	int nAreaFlag;				// 是否全屏秒杀
};


// 发射器信息
// 一个武器上可以有多个发射器
struct cgWeaponLauncher
{
	int nBulletID;		// 子弹id
	int nXOff;			// 偏移
	int nYOff;			// 偏移
	int nXDir;			// 发射器X方向
	int nYDir;			// 发射器Y方向
};

// 一个武器最多有五个发射器
const int MAX_AIRCRAFT_WEAPON_LUANCER_NUM = 5;

// 武器配置
// 武器升级后，攻击增加，同时发射的子弹也可能增加
// cd变短

struct cgWeaponConfig
{
	int nID;				// 武器id
	int nLvl;				// 武器等级
	float fFireCD;		// 攻击CD
	int nMaxLvl;			// 最高等级,达到后不可再升级
	int nFireSoundID;			// 开火声音

	int nLauncherNum;		// 一次发射的子弹数量
	cgWeaponLauncher kLauncherList[MAX_AIRCRAFT_WEAPON_LUANCER_NUM];	// 发射器列表

	cgString strName;		// 武器名字
	cgString strModel;		// 武器模型路径
	cgString strDesc;		// 武器描述
};

// 飞行器配置
// 飞行器的攻击由武器来决定
// 不同的武器发射不同的子弹，
struct cgAircraftConfig
{
	int nID;				// id,不解释
	int nBasicSpeed;		// 基础速度值，相对值
	int nBoundWidth;		// 包围盒宽
	int nBoundHeight;		// 包围盒高
	int	nBasicMaxHp;		// 初始最大血量

	int nMainWeaponID;		// 主武器ID
	int nMainWeaponLvl;		// 主武器初始等级

	cgString strName;		// 名字
	cgString strModel;		// 模型路径
	cgString strDesc;		// 描述
};

// 空间漂浮物设想
//	武器升级箱：武器升级
//	辅助武器：挂接到飞行器身上
//	辅助装甲：挂接到飞行器身上，增加装甲
//	补给箱：回血
//	装甲升级箱：装甲升级
//	金币：增加金币，可以购买新战机、辅助武器和辅助装甲
//	勋章：增加分数

// ------------------------------------------------------------------------------------
struct cgAircraftUnity
{
	int nPosY;			// 出现时间
	int nPosX;			// 位置

	int nTypeID;		// 类型id
	int nBornID;		// 个体id
	int nBornHp;		// 出生血量
	int nBornSpeed;		// 出生速度
	int nDropID;		// 爆落id
	// 爆落ID
};
// ------------------------------------------------------------------------------------

// 战斗的基本配置
struct cgBattleConfig
{
	int nID;				// 关卡id
	int nNextBattle;			// 下一关id
	cgString strName;			// 关卡名字
	cgString strBkImage;		// 关卡背景
	cgString strDesc;			// 关卡描述
	string strCraftConfig;	// 飞行器列表配置
	int nBossID;			// boss
	int nScrollSpeed;				// 滚动速度
	// 还有其他
};
// ------------------------------------------------------------------------------------
// 箱子类型
enum cgFlyBoxType
{
	cgFlyBoxType_None,		// 我就是一个箱子，我啥都不做
	cgFlyBoxType_Weapon,	// 我是一个武器匣子,可以升级响应的武器
	cgFlyBoxType_Engine,	// 我是一个发动机，可以升级装备
	cgFlyBoxType_Coin,		// 金币，
	cgFlyBoxType_Bomb,		// 炸弹，必杀
	cgFlyBoxType_Toolkit,	// 工具箱，恢复hp
	cgFlyBoxType_AssWeapon,	// 辅助武器
};

struct cgFlyBoxConfig
{
	int				nID;				// id
	cgFlyBoxType	enmType;			// 箱子类型
	int				nParam1;			// 附加字段，不同的类型解析成不同的意义
	int				nParam2;			
	int				nParam3;
	int				nParam4;
	cgString		strModel;			// 模型对应的路径
};
// ------------------------------------------------------------------------------------
class cgBullet;
typedef cgSmartPointer<cgBullet> cgBulletPtr;

class cgAircraftWeapon;
typedef cgSmartPointer<cgAircraftWeapon> cgAircraftWeaponPtr;

class cgFlyBox;
typedef cgSmartPointer<cgFlyBox> cgFlyBoxPtr;

class cgAircraft;
typedef cgSmartPointer<cgAircraft> cgAircraftPtr;




#endif