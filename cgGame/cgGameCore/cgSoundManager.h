
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
	cgEnumSoundChannelGroup_Bgm = 0, // 背景音乐
	cgEnumSoundChannelGroup_Scene,	//	场景
	cgEnumSoundChannelGroup_Effect , // 效果音乐
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
	cgSoundChannelGroupID m_id;	// 一个播放通道组的id
	float m_fVolume;			// 此播放通道的默认声音
	std::vector<cgSoundChannelID> m_kChannels;
};


typedef std::map<cgSoundConfigID, cgSoundConfig*> cgSoundConfigPtrMap;
typedef std::map<cgSoundConfigID, cgSoundID> cgSoundIDMap;
typedef std::map<cgSoundChannelGroupID, cgSoundChannelGroup*> cgSoundChannelGroupPtrMap;

// 音效的处理还是很纠结啊！！！！！！！
class cgSoundManager :
	public cgSingleton<cgSoundManager>
{
public:
	cgSoundManager(void);
	~cgSoundManager(void);

public:
	bool Initialize();

	// 查找配置
	cgSoundConfig * FindConfig(cgSoundConfigID id);

	// 通过id来播放一个声音
	cgSoundChannelID PlaySound(cgSoundConfigID id);

	// 关闭一个声音播放通道
	bool StopSoundChannel(cgSoundChannelID channel);

	// 设置一个组的声音
	bool SetSoundChannelGroupVolume(cgSoundChannelGroupID id, float fVolume);

	// 获取一个组的声音
	float GetSoundChannelGroupVolume(cgSoundChannelGroupID id);
private:
	// 加载配置
	bool LoadConfig();

	// 查找已经缓存好的声音
	cgSoundID FindSound(cgSoundConfigID id);

	// 查找对应的声道组
	cgSoundChannelGroup * FindChannelGroup(cgSoundChannelGroupID id);

	// 初始化声道组
	bool InitChannelGroups();
	// 清空声音
	void ClearConfigs();

	// 清空所有的声音数据
	void ClearSounds();

	// 清空声道组信息
	void ClearChannelGroups();
private:
	cgSoundConfigPtrMap m_kConfigPtrMap;
	cgSoundIDMap m_kSoundMap;
	cgSoundChannelGroupPtrMap m_kChannelGroupPtrMap;
};

#endif // cgSoundManager_h__
