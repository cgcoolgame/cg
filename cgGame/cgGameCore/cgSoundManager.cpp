#include "StdAfx.h"
#include "cgSoundManager.h"
#include "cgTxtDataReader.h"
#include "cgSoundPlayer.h"


cgSoundManager::cgSoundManager(void)
{
}


cgSoundManager::~cgSoundManager(void)
{
	ClearChannelGroups();
	ClearSounds();
	ClearConfigs();
}


bool cgSoundManager::Initialize()
{
	if (!LoadConfig())
		return false;

	if (!InitChannelGroups())
		return false;

	return true;
}


bool cgSoundManager::LoadConfig()
{
	cgTxtDataReader kReader;
	if (!kReader.Open("./config/sounds.txt"))
		return false;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgSoundConfig * pkConfig = new cgSoundConfig;
		memset(pkConfig, 0, sizeof(cgSoundConfig));

		int index = 0;
		pkConfig->id = atoi(pkRecord->GetField(index++));
		pkConfig->group_id = atoi(pkRecord->GetField(index++));
		pkConfig->bLoop = atoi(pkRecord->GetField(index++)) == 1;
		pkConfig->bStream = atoi(pkRecord->GetField(index++)) == 1;
		pkConfig->path = pkRecord->GetField(index++);

		m_kConfigPtrMap[pkConfig->id] = pkConfig;
	}
	return true;
}

cgSoundConfig * cgSoundManager::FindConfig( cgSoundConfigID id )
{
	cgSoundConfigPtrMap::iterator it = m_kConfigPtrMap.find(id);
	if (it != m_kConfigPtrMap.end())
		return it->second;

	return NULL;
}

cgSoundChannelID cgSoundManager::PlaySound( cgSoundConfigID id )
{
	// 找不到配置，返回
	cgSoundConfig * pkConfig = FindConfig(id);
	if (!pkConfig)
		return CG_INVALID_ID;

	// 声音是否已经存在
	cgSoundID sound = FindSound(id);

	// 不存在用找到的配置创建之
	if (sound == CG_INVALID_ID)
	{
		sound = cgSoundPlayer::Get()->CreateSound(pkConfig->path.c_str(), pkConfig->bStream, pkConfig->bLoop);
		if (CG_INVALID_ID != sound)
			m_kSoundMap[id] = sound;
		else
			return CG_INVALID_ID;
	}
	// 找到所属的声道组
	cgSoundChannelGroup * pkGroup = FindChannelGroup(pkConfig->group_id);

	// 找不到就用默认的音量播放
	if (!pkGroup)
		return cgSoundPlayer::Get()->PlaySound(sound);

	// 如果channel不是非法的，说明需要保存
	cgSoundChannelID channel = cgSoundPlayer::Get()->PlaySound(sound, pkGroup->GetVolume());
	if (channel != CG_INVALID_ID)
		pkGroup->AddChannel(channel);

	return channel;
}


bool cgSoundManager::StopSoundChannel( cgSoundChannelID channel )
{
	cgSoundPlayer::Get()->StopSoundChannel(channel);

	bool bRet = false;
	cgSoundChannelGroupPtrMap::iterator it = m_kChannelGroupPtrMap.begin();
	for (; it != m_kChannelGroupPtrMap.end(); ++it)
	{
		bRet = bRet||it->second->DelChannel(channel);
	}

	return bRet;
}


cgSoundID cgSoundManager::FindSound( cgID id )
{
	cgSoundIDMap::iterator it = m_kSoundMap.find(id);
	if (it != m_kSoundMap.end())
		return it->second;

	return CG_INVALID_ID;
}

cgSoundChannelGroup * cgSoundManager::FindChannelGroup( cgSoundChannelGroupID id )
{
	cgSoundChannelGroupPtrMap::iterator it = m_kChannelGroupPtrMap.find(id);
	if (it != m_kChannelGroupPtrMap.end())
		return it->second;

	return NULL;
}


bool cgSoundManager::SetSoundChannelGroupVolume( cgSoundChannelGroupID id, float fVolume )
{
	cgSoundChannelGroup * pkGroup = FindChannelGroup(id);
	if (pkGroup)
		return pkGroup->SetVolume(fVolume);

	return false;
}
float cgSoundManager::GetSoundChannelGroupVolume( cgSoundChannelGroupID id )
{
	cgSoundChannelGroup * pkGroup = FindChannelGroup(id);
	if (pkGroup)
		return pkGroup->GetVolume();

	return 0.0f;
}


void cgSoundManager::ClearConfigs()
{
	cgSoundConfigPtrMap::iterator it = m_kConfigPtrMap.begin();
	for (; it != m_kConfigPtrMap.end(); ++it)
		delete it->second;

	m_kConfigPtrMap.clear();
}

void cgSoundManager::ClearSounds()
{
	cgSoundIDMap::iterator it = m_kSoundMap.begin();
	for (; it != m_kSoundMap.end(); ++it)
		cgSoundPlayer::Get()->ReleaseSound(it->second);
	
	m_kSoundMap.clear();
}

void cgSoundManager::ClearChannelGroups()
{
	cgSoundChannelGroupPtrMap::iterator it = m_kChannelGroupPtrMap.begin();
	for (; it != m_kChannelGroupPtrMap.end(); ++it)
		delete it->second;
	
	m_kChannelGroupPtrMap.clear();
}

bool cgSoundManager::InitChannelGroups()
{
	for (unsigned i = 0; i < cgEnumSoundChannelGroupMax; ++i)
	{
		m_kChannelGroupPtrMap[i] = new cgSoundChannelGroup(i);
	}
	return true;
}


// -----------------------------------------------------------------------------------


cgSoundChannelGroup::cgSoundChannelGroup(cgSoundChannelGroupID id)
{
	m_id = id;
	m_fVolume = 1.0f;
}

cgSoundChannelGroup::~cgSoundChannelGroup()
{
	std::vector<cgSoundChannelID>::iterator it = m_kChannels.begin();
	for (; it != m_kChannels.end(); ++it)
		cgSoundPlayer::Get()->StopSoundChannel(*it);

	m_kChannels.clear();
}

cgSoundChannelGroupID cgSoundChannelGroup::GetID()
{
	return m_id;
}

float cgSoundChannelGroup::GetVolume()
{
	return m_fVolume;
}

bool cgSoundChannelGroup::SetVolume( float fVolume )
{
	if (fVolume < 0.0f)
		fVolume = 0.0f;
	if (fVolume > 1.0f)
		fVolume = 1.0f;

	std::vector<cgSoundChannelID>::iterator it = m_kChannels.begin();
	for (; it != m_kChannels.end(); ++it)
		cgSoundPlayer::Get()->SetVolume(*it, fVolume);

	m_fVolume = fVolume;

	return true;
}

void cgSoundChannelGroup::AddChannel( cgSoundChannelID channel )
{
	m_kChannels.push_back(channel);
}

bool cgSoundChannelGroup::DelChannel( cgSoundChannelID channel )
{
	std::vector<cgSoundChannelID>::iterator it = m_kChannels.begin();
	for (; it != m_kChannels.end(); ++it)
	{
		if (*it == channel)
		{
			m_kChannels.erase(it);
			return true;
		}
	}

	return false;
}
