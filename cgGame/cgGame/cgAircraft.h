#ifndef cgAircraft_h__
#define cgAircraft_h__
#include "cgAircraftWeapon.h"
#include "cgSmartPointer.h"
#include "cgActor.h"
#include <cgGameObject.h>
#include <cgGameText.h>
#include <cgGameSprite.h>

/**
*	������
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
	
	// ֱ�Ӵ���һ��������
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

	// �Ƿ񻹻���
	bool IsAlive();
	void SetAlive(bool bAlive);

	// ��Ӫ
	void SetCamp(cgFlyObjectCamp enmCamp);
	cgFlyObjectCamp GetCamp();

	// ����
	void SetMainWeapon(cgAircraftWeaponPtr spWeapon);
	cgAircraftWeaponPtr GetMainWeapon();

	// ����Ҳ����һ�ݰ�
	cgAircraftConfig * GetConfig();
	void SetConfig(cgAircraftConfig * pkConfig);

	// ״̬
	void SetState(cgAircraftState enmState);
	cgAircraftState GetState();

	// 
	void OnHurt(int nHp);
	void OnRecover(int nHp);

	void UpdateCraft(float fDeltaTime);

private:

	cgAircraft();
private:
	
	cgGameSpiritPtr m_spActor;	// �ɻ�ģ��
	cgGameTextPtr m_spText;	// �ַ�����

	// ��������
	int m_nID;

	cgAircraftConfig * m_pkConfig;
	cgAircraftWeaponPtr m_spMainWeapon;

	// ս�����ԣ���������
	int m_nCurHp;	// ��ǰѪ��
	int m_nMaxHp;	// ���Ѫ��

	cgFlyObjectCamp	m_enmCamp;

	cgAircraftState m_enmState;
	float m_fAliveTime;
	float m_fDeadTime;

	bool m_bInvalid; // �Ƿ���Ч��
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
