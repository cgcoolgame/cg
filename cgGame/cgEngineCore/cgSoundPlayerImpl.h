#ifndef cgSoundPlayerImpl_h__
#define cgSoundPlayerImpl_h__
#include "cgDefine.h"

class cgSoundPlayerImpl
{
public:
	virtual ~cgSoundPlayerImpl(void){};
	virtual bool Initialize() = NULL;
	virtual void Update(float fTime) = NULL;
	virtual cgID CreateSound(const char * path, bool bStream, bool bLoop) = NULL;
	virtual bool ReleaseSound(cgID sound) = NULL;
	virtual cgID PlaySound(cgID sound, float fVolume) = NULL;
	virtual bool StopSoundChannel(cgID channel) = NULL;
	virtual bool SetVolume(cgID channel, float fVolume) = NULL;
};

#endif // cgSoundPlayerImpl_h__
