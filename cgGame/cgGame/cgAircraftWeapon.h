
#ifndef cgAircraftWeapon_h__
#define cgAircraftWeapon_h__
#include "cgILoveShootingDef.h"
#include "..\cgEngineCore\cgRefObject.h"

class cgAircraft;

class cgAircraftWeapon:
	public cgRefObject
{
public:
	cgAircraftWeapon(int nWeaponID, int nWeaponLvl);
	~cgAircraftWeapon(void);

	// ËùÊô·ÉÐÐÆ÷
	void SetAircaft(cgAircraft * spAircraft);
	cgAircraftPtr GetAircraft();

	int GetWeaponID();
	int GetWeaponLvl();

	bool CanLevelup();
	bool Levelup();
	bool LevelDown();

	virtual void Update(float fDeltaTime);

protected:
	virtual bool Fire();

protected:
	int m_nConfigID;
	int m_nLvl;
	float m_fCD;
	cgWeaponConfig * m_pkConfig;
	cgAircraft * m_pkAircraft;
};

#endif // cgAircraftWeapon_h__
