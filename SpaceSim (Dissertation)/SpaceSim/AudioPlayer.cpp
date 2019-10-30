#include "AudioPlayer.h"


AudioPlayer::AudioPlayer()
{
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		// Report Error
		return;
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// Report Error
		return;
	}

	// Initialize our Instance with 36 Channels
	m_pSystem->init(36, FMOD_INIT_NORMAL, nullptr);
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::CreateSound(Sound* pSound, const char* pFile)
{
	m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
}

void AudioPlayer::PlaySound(Sound pSound, bool loop)
{
	if (!loop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	m_pSystem->playSound(pSound, nullptr, false, 0);
}

void AudioPlayer::ReleaseSound(Sound pSound)
{
	pSound->release();
}