
#ifndef cgFMODSoundPlayerImpl_h__
#define cgFMODSoundPlayerImpl_h__
#include <fmod.hpp>
#include "cgsoundplayerimpl.h"
#include "cgStorage.h"

typedef cgStorage<FMOD::Sound> cgFMODSoundStorage;
typedef cgStorage<FMOD::Channel> cgFMODChannelStorage;

class cgFMODSoundPlayerImpl :
	public cgSoundPlayerImpl
{
public:
	cgFMODSoundPlayerImpl(void);
	virtual ~cgFMODSoundPlayerImpl(void);

public:
	virtual bool Initialize() ;
	virtual void Update(float fTime) ;
	virtual cgID CreateSound(const char * path, bool bStream, bool bLoop) ;
	virtual bool ReleaseSound(cgID sound);
	virtual cgID PlaySound(cgID sound, float fVolume);
	virtual bool StopSoundChannel(cgID channel);
	virtual bool SetVolume(cgID channel, float fVolume);

private:
	FMOD::System * m_pkFmodSystem;
	cgFMODSoundStorage * m_pkSoundStorage;
	cgFMODChannelStorage * m_pkChannelStorage;
};


#endif // cgFMODSoundPlayerImpl_h__
