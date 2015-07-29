
#ifndef cgPlayerInfoManager_h__
#define cgPlayerInfoManager_h__
#include "..\cgNetwork\cgNetworkDef.h"
#include <map>

struct cgPlayerInfo
{
	int nPlayerID;

	int nNameLen;
	char szName[CG_MAX_NAME_LEN];

	int nAccountLen;
	char szAccount[CG_MAX_ACCOUNT_LEN];

	int nPwdLen;
	char szPwd[CG_MAX_PWD_LEN];

	int nScore;
	int nFlowerNum;
	int nEggNum;
	int nShoeNum;

	int nConnectionID;
};

typedef std::map<int , cgPlayerInfo*> cgPlayerInfoMap;


class cgPlayerInfoManager
{
public:
	cgPlayerInfoManager(void);
	~cgPlayerInfoManager(void);

	void Load();
	void Save();

	size_t GetPlayerNum();

	// 根据id查找
	cgPlayerInfo * FindPlayerByID(int nID);

	// 根据名字查找
	cgPlayerInfo * FindPlayerByAccount(const char * szAccount);

	// 添加一个玩家信息，算是注册了
	cgPlayerInfo * AddPlayerInfo(const char * szAccount, const char * szPwd, const char * szName);

	// 遍历
	void Iterate();

	int CreatePlayerID();
protected:

	cgPlayerInfoMap m_kPlayerInfoMap;
	int m_nTopPlayerID;
};



#endif // cgPlayerInfoManager_h__
