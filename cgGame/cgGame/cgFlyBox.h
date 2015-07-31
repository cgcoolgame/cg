#ifndef cgFlyBox_h__
#define cgFlyBox_h__
#include "cgILoveShootingDef.h"
#include "cgAircraft.h"
#include <cgGameSprite.h>
// �й��ܵ����Ư������ӵ�
class cgAircraft;

class cgFlyBox:
	public cgGameObject
{
public:
	cgFlyBox();
	~cgFlyBox(void);

	void SetID(int nID);
	int GetID();

	void SetConfig(cgFlyBoxConfig * pkConfig);
	cgFlyBoxConfig* GetConfig();

	void SetModel(const cgString & strPath);

	void Affect(cgAircraftPtr spAircraft);

	bool IsInvalid();
	void SetInvalid(bool bInvalid);

	static cgFlyBoxPtr CreateFlyBox(int nID);

protected:
	int m_nID;
	cgFlyBoxConfig * m_pkConfig;
	cgGameSpiritPtr m_spModel;
	bool m_bInvalid;
};

#endif // cgFlyBox_h__
