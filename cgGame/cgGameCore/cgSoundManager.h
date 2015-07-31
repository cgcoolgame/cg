
#ifndef cgSoundManager_h__
#define cgSoundManager_h__

#include "cgsingleton.h"
#include <map>
#include <vector>

typedef cgID cgSoundConfigID;
typedef cgID cgSoundID;
typedef cgID cgSoundChannelID;
typedef cgID cgSoundChannelGroupID;

enum cgEnumSoundChannelGroup
{
	cgEnumSoundChannelGroup_Bgm = 0, // ��������
	cgEnumSoundChannelGroup_Scene,	//	����
	cgEnumSoundChannelGroup_Effect , // Ч������
	cgEnumSoundChannelGroup_UI,		//	UI
	cgEnumSoundChannelGroupMax,
};

typedef struct tagSoundConfig
{
	cgID id;
	cgID group_id;
	std::string path;
	bool bLoop;
	bool bStream;
}cgSoundConfig;

class cgSoundChannelGroup
{
public:
	cgSoundChannelGroup(cgSoundChannelGroupID id);
	~cgSoundChannelGroup();

public:
	cgSoundChannelGroupID GetID();

	float GetVolume();
	bool SetVolume(float fVolume);

	void AddChannel(cgSoundChannelID channel);
	bool DelChannel(cgSoundChannelID channel);

private:
	cgSoundChannelGroupID m_id;	// һ������ͨ�����id
	float m_fVolume;			// �˲���ͨ����Ĭ������
	std::vector<cgSoundChannelID> m_kChannels;
};


typedef std::map<cgSoundConfigID, cgSoundConfig*> cgSoundConfigPtrMap;
typedef std::map<cgSoundConfigID, cgSoundID> cgSoundIDMap;
typedef std::map<cgSoundChannelGroupID, cgSoundChannelGroup*> cgSoundChannelGroupPtrMap;

// ��Ч�Ĵ����Ǻܾ��ᰡ��������������
class cgSoundManager :
	public cgSingleton<cgSoundManager>
{
public:
	cgSoundManager(void);
	~cgSoundManager(void);

public:
	bool Initialize();

	// ��������
	cgSoundConfig * FindConfig(cgSoundConfigID id);

	// ͨ��id������һ������
	cgSoundChannelID PlaySound(cgSoundConfigID id);

	// �ر�һ����������ͨ��
	bool StopSoundChannel(cgSoundChannelID channel);

	// ����һ���������
	bool SetSoundChannelGroupVolume(cgSoundChannelGroupID id, float fVolume);

	// ��ȡһ���������
	float GetSoundChannelGroupVolume(cgSoundChannelGroupID id);
private:
	// ��������
	bool LoadConfig();

	// �����Ѿ�����õ�����
	cgSoundID FindSound(cgSoundConfigID id);

	// ���Ҷ�Ӧ��������
	cgSoundChannelGroup * FindChannelGroup(cgSoundChannelGroupID id);

	// ��ʼ��������
	bool InitChannelGroups();
	// �������
	void ClearConfigs();

	// ������е���������
	void ClearSounds();

	// �����������Ϣ
	void ClearChannelGroups();
private:
	cgSoundConfigPtrMap m_kConfigPtrMap;
	cgSoundIDMap m_kSoundMap;
	cgSoundChannelGroupPtrMap m_kChannelGroupPtrMap;
};

#endif // cgSoundManager_h__
