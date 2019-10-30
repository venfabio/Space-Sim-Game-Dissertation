#pragma once

#include<windows.h>

// https://cuboidzone.wordpress.com/2013/07/26/tutorial-implementing-fmod/

#include "fmod.hpp"
#include "fmod_errors.h" // Only if you want error checking

typedef FMOD::Sound* Sound;

class AudioPlayer
{
protected:
	FMOD::System* m_pSystem;	// Pointer to the FMOD instance

public:
	AudioPlayer();											// Initialize the device
	~AudioPlayer();
									
	void CreateSound(Sound* pSound, const char* pFile);		// Pointer to FMOD + file path of the audio file
	void PlaySound(Sound pSound, bool lopp);				// Play the sound + loop yes/no
	void ReleaseSound(Sound pSound);						// Clean
};

