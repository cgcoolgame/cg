////////////////////////////////////////////////
//	FileName:		CGSoundPlayer.h
//	Author:			Master
//	Date:			2013.09.18
//	Description:	һ���򵥵�����������
//	mark:			��װ̫�ͼ��ˣ�Ҫ��
////////////////////////////////////////////////

// ����ļ�ͷ [9/19/2013 Master]

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
	// ��ʼ��
	bool Initialize();

	// ���£�����Ǳ����
	void Update(float fTime);

	// ����һ����������id
	cgID CreateSound(const char * path, bool bStream, bool bLoop);

	// �ͷ�һ����������
	bool ReleaseSound(cgID id);

	// ���ţ�����һ����������ͨ��id
	// �����ֱ�����������id��Ŀ�겥��ͨ����id
	cgID PlaySound(cgID sound, float fVolume = 1.0f);

	// �趨ĳ����������
	bool SetVolume(cgID channel, float fVolume);

	// ֹͣ����
	bool StopSoundChannel(cgID channel);

private:
	cgSoundPlayerImpl * m_pkPlayerImpl;
};

#endif // CGSoundPlayer_h__

