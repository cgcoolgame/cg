#include "StdAfx.h"
#include "cgSoundPlayer.h"
#include "cgSoundPlayerImpl.h"
#include "cgPlatform.h"

cgSoundPlayer::cgSoundPlayer()
{
	m_pkPlayerImpl = NULL;
}

cgSoundPlayer::~cgSoundPlayer()
{
	delete m_pkPlayerImpl;
}

bool cgSoundPlayer::Initialize()
{
	m_pkPlayerImpl = cgPlatform::Instance()->CreateSoundPlayerImpl();

	return m_pkPlayerImpl->Initialize();
}

void cgSoundPlayer::Update( float fTime )
{
	m_pkPlayerImpl->Update(fTime);
}


cgID cgSoundPlayer::CreateSound( const char * path, bool bStream, bool bLoop )
{
	return m_pkPlayerImpl->CreateSound(path, bStream, bLoop);
}

bool cgSoundPlayer::ReleaseSound( cgID id )
{
	return m_pkPlayerImpl->ReleaseSound(id);
}

cgID cgSoundPlayer::PlaySound( cgID sound, float fVolume )
{
	return m_pkPlayerImpl->PlaySound(sound, fVolume);
}

bool cgSoundPlayer::SetVolume( cgID channel, float fVolume )
{
	return m_pkPlayerImpl->SetVolume(channel, fVolume);
}

bool cgSoundPlayer::StopSoundChannel( cgID channel )
{
	return m_pkPlayerImpl->StopSoundChannel(channel);
}

