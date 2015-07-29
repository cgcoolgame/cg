#ifndef cgSvrRoom_h__
#define cgSvrRoom_h__
#include "cgPlayerInfoManager.h"



class cgSvrRoom
{
public:
	cgSvrRoom(void);
	~cgSvrRoom(void);

	void Update(int nTime);
	void Start();

	cgRoomGameStage GetStage();

	void AddPlayer(cgPlayerInfo * pkPlayer);

protected:
	int m_nRoomID;
	cgPlayerInfoMap m_kPlayerMap;
	cgPlayerInfo * m_pkCurPlayer;

	cgRoomGameStage m_enmGameStage;
};

#endif // cgSvrRoom_h__
