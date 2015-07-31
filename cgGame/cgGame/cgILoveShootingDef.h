#ifndef _cgILoveShootingDef_h__
#define _cgILoveShootingDef_h__
#include "cgGameMessage.h"
#include "cgSmartPointer.h"

/**
*	�����������Ӫ�����ڵ����жϣ���Ӫ˵����
*	������Ӫ��ֻ����������
*	�����Ӫ������������Ӫ�ͻ�����
*	������Ӫ�����������Ӫ�ͻ�����
*	��������Ӫ���������е���Ӫ��������������Ӫ
**/
enum cgFlyObjectCamp
{
	cgFlyObjectCamp_None = 0,	// ����������Ӫ
	cgFlyObjectCamp_Self = 1,	// �����Ӫ���Լ���
	cgFlyObjectCamp_Enemy = 2,	// �з���Ӫ������
	cgFlyObjectCamp_Destroyer = 3,// ��������Ӫ
};


/**
*	���������״̬��״̬˵����
*	��״̬����ʹ��
*	����״̬�������ļ���״̬���ɼ����ɲ������ɹ���
*	����״̬�������󲻻��������������Ҫ����һ�����ʱ���������״̬
*	��Ч״̬��������һ��ʱ�䣬�ͻ�ת�����Ч״̬��Ϊ������׼��
**/
enum cgFlyObjectState
{
	cgFlyObjectState_None = 0,			// ��״̬
	cgFlyObjectState_Active = 1,		// ����״̬
	cgFlyObjectState_Dead = 2,		// ����
	cgFlyObjectState_Invalid = 3,	// ��Ч
};
// ---------------------------------------------------------------------------------
// ��Ϸ�ڲ���Ϣ����
static const cgGameMessage cgGameMessage_AircraftOutOfScreen = cgUserGameMessageBegin+1;
static const cgGameMessage cgGameMessage_AircraftBeKilled = cgUserGameMessageBegin+2;


// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// �ӵ�����
// �ӵ�������ֻ�Ǳ�ʾ���ı���
// �ӵ���ʵ�ʹ���= �ӵ�������+��������
// ����ֻ����ͨ�ӵ�������
// �߼��ӵ�����������������
struct cgBulletConfig
{
	int nID;				// �ӵ�������id
	int nAttack;			// �ӵ�������
	int nSpeed;				// �ӵ����ٶ�
	int nHitSoundID;		// �ӵ��Ļ�����Ч
	int nBoundW;
	int nBoundH;		

	cgString strName;		// �ӵ�����
	cgString strModel;		// �ӵ���ģ��
	cgString strDesc;		// �ӵ�����

	int nAreaFlag;				// �Ƿ�ȫ����ɱ
};


// ��������Ϣ
// һ�������Ͽ����ж��������
struct cgWeaponLauncher
{
	int nBulletID;		// �ӵ�id
	int nXOff;			// ƫ��
	int nYOff;			// ƫ��
	int nXDir;			// ������X����
	int nYDir;			// ������Y����
};

// һ��������������������
const int MAX_AIRCRAFT_WEAPON_LUANCER_NUM = 5;

// ��������
// ���������󣬹������ӣ�ͬʱ������ӵ�Ҳ��������
// cd���

struct cgWeaponConfig
{
	int nID;				// ����id
	int nLvl;				// �����ȼ�
	float fFireCD;		// ����CD
	int nMaxLvl;			// ��ߵȼ�,�ﵽ�󲻿�������
	int nFireSoundID;			// ��������

	int nLauncherNum;		// һ�η�����ӵ�����
	cgWeaponLauncher kLauncherList[MAX_AIRCRAFT_WEAPON_LUANCER_NUM];	// �������б�

	cgString strName;		// ��������
	cgString strModel;		// ����ģ��·��
	cgString strDesc;		// ��������
};

// ����������
// �������Ĺ���������������
// ��ͬ���������䲻ͬ���ӵ���
struct cgAircraftConfig
{
	int nID;				// id,������
	int nBasicSpeed;		// �����ٶ�ֵ�����ֵ
	int nBoundWidth;		// ��Χ�п�
	int nBoundHeight;		// ��Χ�и�
	int	nBasicMaxHp;		// ��ʼ���Ѫ��

	int nMainWeaponID;		// ������ID
	int nMainWeaponLvl;		// ��������ʼ�ȼ�

	cgString strName;		// ����
	cgString strModel;		// ģ��·��
	cgString strDesc;		// ����
};

// �ռ�Ư��������
//	���������䣺��������
//	�����������ҽӵ�����������
//	����װ�ף��ҽӵ����������ϣ�����װ��
//	�����䣺��Ѫ
//	װ�������䣺װ������
//	��ң����ӽ�ң����Թ�����ս�������������͸���װ��
//	ѫ�£����ӷ���

// ------------------------------------------------------------------------------------
struct cgAircraftUnity
{
	int nPosY;			// ����ʱ��
	int nPosX;			// λ��

	int nTypeID;		// ����id
	int nBornID;		// ����id
	int nBornHp;		// ����Ѫ��
	int nBornSpeed;		// �����ٶ�
	int nDropID;		// ����id
	// ����ID
};
// ------------------------------------------------------------------------------------

// ս���Ļ�������
struct cgBattleConfig
{
	int nID;				// �ؿ�id
	int nNextBattle;			// ��һ��id
	cgString strName;			// �ؿ�����
	cgString strBkImage;		// �ؿ�����
	cgString strDesc;			// �ؿ�����
	string strCraftConfig;	// �������б�����
	int nBossID;			// boss
	int nScrollSpeed;				// �����ٶ�
	// ��������
};
// ------------------------------------------------------------------------------------
// ��������
enum cgFlyBoxType
{
	cgFlyBoxType_None,		// �Ҿ���һ�����ӣ���ɶ������
	cgFlyBoxType_Weapon,	// ����һ������ϻ��,����������Ӧ������
	cgFlyBoxType_Engine,	// ����һ������������������װ��
	cgFlyBoxType_Coin,		// ��ң�
	cgFlyBoxType_Bomb,		// ը������ɱ
	cgFlyBoxType_Toolkit,	// �����䣬�ָ�hp
	cgFlyBoxType_AssWeapon,	// ��������
};

struct cgFlyBoxConfig
{
	int				nID;				// id
	cgFlyBoxType	enmType;			// ��������
	int				nParam1;			// �����ֶΣ���ͬ�����ͽ����ɲ�ͬ������
	int				nParam2;			
	int				nParam3;
	int				nParam4;
	cgString		strModel;			// ģ�Ͷ�Ӧ��·��
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