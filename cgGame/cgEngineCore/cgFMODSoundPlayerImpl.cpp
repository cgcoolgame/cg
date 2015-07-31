#include "StdAfx.h"
#include "cgFMODSoundPlayerImpl.h"

cgFMODSoundPlayerImpl::cgFMODSoundPlayerImpl(void)
{
	m_pkFmodSystem = NULL;
	m_pkSoundStorage = NULL;
	m_pkChannelStorage = NULL;
}


cgFMODSoundPlayerImpl::~cgFMODSoundPlayerImpl(void)
{
	delete m_pkSoundStorage;
	delete m_pkChannelStorage;
	m_pkFmodSystem->release();
}

// -------------------------------------------------------------------
bool cgFMODSoundPlayerImpl::Initialize()
{
	FMOD_RESULT result = FMOD::System_Create(&m_pkFmodSystem);
	if (result != FMOD_OK)
		return false;

	result = m_pkFmodSystem->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
	if (result != FMOD_OK)
		return false;

	m_pkSoundStorage = new cgFMODSoundStorage(100);
	m_pkChannelStorage = new cgFMODChannelStorage(100);

	return true;
}

void cgFMODSoundPlayerImpl::Update( float fTime )
{
	m_pkFmodSystem->update();
}

cgID cgFMODSoundPlayerImpl::CreateSound( const char * path, bool bStream, bool bLoop )
{

	FMOD::Sound * pkSound = NULL;
	FMOD_RESULT result;
	FMOD_MODE mode = FMOD_DEFAULT;

	if (bLoop)
		mode |= FMOD_LOOP_NORMAL;
	if (bStream)
		mode |= FMOD_CREATESTREAM;

	result = m_pkFmodSystem->createSound(path, mode, NULL, &pkSound);

	if (result != FMOD_OK)
		return CG_INVALID_ID;

	return m_pkSoundStorage->Add(pkSound);
}


bool cgFMODSoundPlayerImpl::ReleaseSound( cgID sound )
{
	FMOD::Sound * pkSound = m_pkSoundStorage->Remove(sound);
	if (!pkSound)
		return false;

	pkSound->release();

	return true;
}

cgID cgFMODSoundPlayerImpl::PlaySound( cgID sound , float fVolume)
{
	FMOD::Sound * pkSound = m_pkSoundStorage->Find(sound);
	if (!pkSound)
		return CG_INVALID_ID;

	FMOD::Channel * pkChannel = NULL;
	m_pkFmodSystem->playSound(FMOD_CHANNEL_FREE, pkSound, true, &pkChannel);
	pkChannel->setVolume(fVolume);
	pkChannel->setPaused(false);

	FMOD_MODE mode;
	pkSound->getMode(&mode);
	if(mode & FMOD_LOOP_NORMAL)
		return m_pkChannelStorage->Add(pkChannel);

	return CG_INVALID_ID;
}


bool cgFMODSoundPlayerImpl::StopSoundChannel( cgID channel )
{
	FMOD::Channel * pkChannel = m_pkChannelStorage->Remove(channel);
	if (!pkChannel)
		return false;

	return pkChannel->stop();
}


bool cgFMODSoundPlayerImpl::SetVolume( cgID channel, float fVolume )
{
	FMOD::Channel * pkChannel = m_pkChannelStorage->Find(channel);
	if (!pkChannel)
		return false;

	pkChannel->setVolume(fVolume);

	return true;
}
