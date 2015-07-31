////////////////////////////////////////////////
//	FileName:		CGSoundPlayer.h
//	Author:			Master
//	Date:			2013.09.18
//	Description:	一个简单的声音播放器
//	mark:			封装太低级了，要改
////////////////////////////////////////////////

// 添加文件头 [9/19/2013 Master]

#ifndef CGSoundPlayer_h__
#define CGSoundPlayer_h__
#include "cgSingleton.h"

class cgSoundPlayerImpl;

class cgSoundPlayer: public cgSingleton<cgSoundPlayer>
{
public:
	cgSoundPlayer();
	virtual ~cgSoundPlayer();

public:
	// 初始化
	bool Initialize();

	// 更新，这个是必须的
	void Update(float fTime);

	// 返回一个声音数据id
	cgID CreateSound(const char * path, bool bStream, bool bLoop);

	// 释放一个声音数据
	bool ReleaseSound(cgID id);

	// 播放，返回一个声音播放通道id
	// 参数分别是声音数据id和目标播放通道组id
	cgID PlaySound(cgID sound, float fVolume = 1.0f);

	// 设定某个声音音量
	bool SetVolume(cgID channel, float fVolume);

	// 停止声音
	bool StopSoundChannel(cgID channel);

private:
	cgSoundPlayerImpl * m_pkPlayerImpl;
};

#endif // CGSoundPlayer_h__

