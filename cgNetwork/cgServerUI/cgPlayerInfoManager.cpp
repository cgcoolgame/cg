#include "StdAfx.h"
#include "cgPlayerInfoManager.h"
#include "cgTxtDataReader.h"


cgPlayerInfoManager::cgPlayerInfoManager(void)
{
}


cgPlayerInfoManager::~cgPlayerInfoManager(void)
{
}

void cgPlayerInfoManager::Load()
{
	m_nTopPlayerID = 0;

	cgTxtDataReader kReader;

	if (!kReader.Open("./server/players.txt"))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgPlayerInfo * pkPlayer = new cgPlayerInfo;

		int nIndex = 0;
		pkPlayer->nPlayerID = atoi(pkRecord->GetField(nIndex++));

		strcpy(pkPlayer->szName, pkRecord->GetField(nIndex++));
		pkPlayer->nNameLen = strlen(pkPlayer->szName)+1;

		strcpy(pkPlayer->szAccount, pkRecord->GetField(nIndex++));
		pkPlayer->nAccountLen = strlen(pkPlayer->szAccount)+1;

		strcpy(pkPlayer->szPwd, pkRecord->GetField(nIndex++));
		pkPlayer->nPwdLen = strlen(pkPlayer->szPwd)+1;

		pkPlayer->nScore = atoi(pkRecord->GetField(nIndex++));
		pkPlayer->nFlowerNum = atoi(pkRecord->GetField(nIndex++));
		pkPlayer->nEggNum = atoi(pkRecord->GetField(nIndex++));
		pkPlayer->nShoeNum = atoi(pkRecord->GetField(nIndex++));

		pkPlayer->nConnectionID = -1;

		m_kPlayerInfoMap[pkPlayer->nPlayerID] = pkPlayer;

		if (m_nTopPlayerID < pkPlayer->nPlayerID)
			m_nTopPlayerID = pkPlayer->nPlayerID;
	}
}

void cgPlayerInfoManager::Save()
{
	FILE * pkFile = fopen("./server/players.txt", "w");
	if (!pkFile)
		return ;
	fprintf_s(pkFile, "ID\tName\tAccount\tPassword\tScore\tFlowerNum\tEggNum\tShoeNum\n");

	cgPlayerInfoMap::iterator it = m_kPlayerInfoMap.begin();
	for (; it != m_kPlayerInfoMap.end(); ++it)
	{
		cgPlayerInfo * pkPlayer = it->second;
		if (pkPlayer)
		{
			fprintf_s(pkFile,
				"%d\t\"%s\"\t\"%s\"\t\"%s\"\t%d\t%d\t%d\t%d\n",
				pkPlayer->nPlayerID,
				pkPlayer->szName,
				pkPlayer->szAccount,
				pkPlayer->szPwd,
				pkPlayer->nScore,
				pkPlayer->nFlowerNum,
				pkPlayer->nEggNum,
				pkPlayer->nShoeNum);
		}
	}
}

size_t cgPlayerInfoManager::GetPlayerNum()
{
	return m_kPlayerInfoMap.size();
}

cgPlayerInfo * cgPlayerInfoManager::FindPlayerByID( int nID )
{
	cgPlayerInfoMap::iterator it = m_kPlayerInfoMap.find(nID);
	if (it != m_kPlayerInfoMap.end())
	{
		return it->second;
	}

	return NULL;
}

cgPlayerInfo * cgPlayerInfoManager::FindPlayerByAccount( const char * szAccount )
{
	cgPlayerInfoMap::iterator it = m_kPlayerInfoMap.begin();
	for(; it != m_kPlayerInfoMap.end(); ++it)
	{
		cgPlayerInfo * pkPlayer = it->second;
		if (pkPlayer && strcmp(pkPlayer->szAccount, szAccount) == 0)
		{
			return pkPlayer;
		}
	}

	return NULL;
}

cgPlayerInfo * cgPlayerInfoManager::AddPlayerInfo( const char * szAccount, const char * szPwd, const char * szName )
{
	cgPlayerInfo * pkPlayer = FindPlayerByAccount(szAccount);
	if (pkPlayer)
	{
		if (strcmp(szPwd, pkPlayer->szPwd) != 0)
			return NULL;
		if (strcmp(szName, pkPlayer->szName) != 0)
			return NULL;

		return pkPlayer;
	}

	pkPlayer = new cgPlayerInfo;

	pkPlayer->nAccountLen = strlen(szAccount)+1;
	memcpy(pkPlayer->szAccount, szAccount, pkPlayer->nAccountLen);

	pkPlayer->nNameLen = strlen(szName)+1;
	memcpy(pkPlayer->szName, szName, pkPlayer->nNameLen);

	pkPlayer->nPwdLen = strlen(szPwd)+1;
	memcpy(pkPlayer->szPwd, szPwd, pkPlayer->nPwdLen);

	pkPlayer->nPlayerID = CreatePlayerID();
	pkPlayer->nConnectionID = 0;

	pkPlayer->nScore = 0;
	pkPlayer->nFlowerNum = 0;
	pkPlayer->nEggNum = 0;
	pkPlayer->nShoeNum = 0;

	m_kPlayerInfoMap[pkPlayer->nPlayerID] = pkPlayer;

	return pkPlayer;
}

void cgPlayerInfoManager::Iterate()
{

}

int cgPlayerInfoManager::CreatePlayerID()
{
	return ++m_nTopPlayerID;
}

