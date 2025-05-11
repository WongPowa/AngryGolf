#pragma once
#include "fmod.hpp"
class AudioManager
{
public:
	void initializeAudio();
	void playGolfSwing();
	void playGolfCollide();
	void playSoundTrack();
	void playWin();
	void playLose();
	void loadSounds();
	void updateSound();
	void playWoodHit();

	AudioManager();
	~AudioManager();

private:
	FMOD::System* system;
	FMOD::Sound* golf_swing, * ball_collide,
		* nature_soundtrack, * win_sound, * wood_hit, * lose_sound;
	FMOD::Channel* channel = 0;
	FMOD_RESULT		result;
	void* extradriverdata = 0;
};

