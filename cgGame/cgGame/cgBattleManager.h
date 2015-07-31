#ifndef cgBattleManager_h__
#define cgBattleManager_h__
#include "..\cgEngineCore\cgSingleton.h"
#include <list>
#include <map>
#include "cgILoveShootingDef.h"
#include "..\cgGameCore\cgGameMessageListenerManager.h"

typedef std::list<cgAircraftUnity> cgAircraftUnityList;

class cgBattleManager:
	public cgSingleton<cgBattleManager>,
	public cgGameMessageListener
{
public:
	cgBattleManager(void);
	~cgBattleManager(void);

	bool Initialize();

	void SetCurBattle(int nBattleID);
	cgBattleConfig* GetCurBattleConfig();
	void Update(float fDeltaTime);

	virtual bool OnGameMessage(cgGameMessage msg, void * pData, int nLen);
protected:
	void LoadBattle();
	void LoadCrafts();
	void StartBattle();
	void AddCraft(cgAircraftUnity& kUnity);

protected:
	float m_fBattleTime;
	float m_fScrolledMiles;			// 总共行进了多远，以像素为单位
	int m_nCurBattleID;
	cgBattleConfig * m_pkConfig;
	cgAircraftUnityList m_kCraftUnityList;
	cgAircraftUnityList::iterator m_iterCraft;
	std::map<int , int> m_kDropList;
};

#endif // cgBattleManager_h__
