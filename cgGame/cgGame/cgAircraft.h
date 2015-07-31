#ifndef cgAircraft_h__
#define cgAircraft_h__
#include "cgAircraftWeapon.h"
#include "cgSmartPointer.h"
#include "cgActor.h"
#include <cgGameObject.h>
#include <cgGameText.h>
#include <cgGameSprite.h>

/**
*	飞行器
**/

enum cgAircraftState
{
	cgAircraftState_Normal,
	cgAircraftState_Dead,
	cgAircraftState_Invalid,
};

class cgAircraft:
	public cgGameObject
{
public:
	
	virtual ~cgAircraft();
	
	// 直接创建一个飞行器
	static cgAircraftPtr CreateAircraft(int nConfigId, int nEntityID);
public:


	void SetID(int id);
	int GetID();
	
	void SetCurHp(int hp);
	int GetCurHp();

	void SetMaxHp(int maxHp);
	int GetMaxHp();

	void SetModel(const cgString & path);

//	void SetWeapon(cgAircraftWeaponPtr spWeapon);
	void SetInvalid(bool bInvalid);
	bool IsInvalid();

	// 是否还活着
	bool IsAlive();
	void SetAlive(bool bAlive);

	// 阵营
	void SetCamp(cgFlyObjectCamp enmCamp);
	cgFlyObjectCamp GetCamp();

	// 武器
	void SetMainWeapon(cgAircraftWeaponPtr spWeapon);
	cgAircraftWeaponPtr GetMainWeapon();

	// 配置也保存一份吧
	cgAircraftConfig * GetConfig();
	void SetConfig(cgAircraftConfig * pkConfig);

	// 状态
	void SetState(cgAircraftState enmState);
	cgAircraftState GetState();

	// 
	void OnHurt(int nHp);
	void OnRecover(int nHp);

	void UpdateCraft(float fDeltaTime);

private:

	cgAircraft();
private:
	
	cgGameSpiritPtr m_spActor;	// 飞机模型
	cgGameTextPtr m_spText;	// 字符串。

	// 基本属性
	int m_nID;

	cgAircraftConfig * m_pkConfig;
	cgAircraftWeaponPtr m_spMainWeapon;

	// 战斗属性，个体属性
	int m_nCurHp;	// 当前血量
	int m_nMaxHp;	// 最大血量

	cgFlyObjectCamp	m_enmCamp;

	cgAircraftState m_enmState;
	float m_fAliveTime;
	float m_fDeadTime;

	bool m_bInvalid; // 是否无效了
	bool m_bAlive;
};

//
//class cgAircraftEffectAction:
//	public cgSpiritAction
//{
//public:
//	cgAircraftEffectAction(const cgString & path, float fTime, float xOff, float yOff);
//
//	virtual bool Start(cgSpirit * pkSpirit);
//
//	virtual void Update(float fDeltaTime);
//
//private:
//	cgImageSequencePtr m_spSequence;
//	cgString m_strPath;
//	float m_fTime;
//	float m_fXOff;
//	float m_fYOff;
//};
#endif // cgAircraft_h__
