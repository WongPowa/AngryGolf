#include "AudioManager.h"
#include <iostream>
using namespace std;

void AudioManager::initializeAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void AudioManager::playGolfSwing()
{
	result = system->playSound(golf_swing, 0, true, &channel);
	channel->setVolume(1);
	//channel->setPan(-1);
	channel->setPosition(650, FMOD_TIMEUNIT_MS);
	//channel->setDelay(FMOD_DSP_TYPE_DELAY, 827, true);
	channel->setPaused(false);
	channel->setFrequency(44100); //Nyquist Theorem, all files should be sampled at 44100hz or  44100/2 or 44100*2. because it will sample the high and low of any amplitude of sound;
}

void AudioManager::playGolfCollide()
{
	result = system->playSound(ball_collide, 0, true, &channel);
	channel->setVolume(1);
	//channel->setPan(-1);
	channel->setPaused(false);
	channel->setFrequency(44100); //Nyquist Theorem, all files should be sampled at 44100hz or  44100/2 or 44100*2. because it will sample the high and low of any amplitude of sound;
}

void AudioManager::playWin()
{
	result = system->playSound(win_sound, 0, false, &channel);
	channel->setFrequency(44100);
}

void AudioManager::playLose()
{
	result = system->playSound(lose_sound, 0, false, &channel);
	channel->setFrequency(44100);
}

void AudioManager::playWoodHit()
{
	result = system->playSound(wood_hit, 0, false, &channel);
	channel->setPosition(300, FMOD_TIMEUNIT_MS);
	channel->setFrequency(44100);
}

void AudioManager::playSoundTrack()
{
	result = system->playSound(nature_soundtrack, 0, false, &channel);
	channel->setVolume(0.1);
}

void AudioManager::loadSounds()
{
	result = system->createSound("Audio/golf_swing.wav", FMOD_DEFAULT, 0, &golf_swing);
	result = golf_swing->setMode(FMOD_LOOP_OFF);

	result = system->createStream("Audio/ball_collide.wav", FMOD_DEFAULT, 0, &ball_collide);
	result = ball_collide->setMode(FMOD_LOOP_OFF);

	result = system->createStream("Audio/ambiance_nature.wav", FMOD_DEFAULT, 0, &nature_soundtrack);
	result = nature_soundtrack->setMode(FMOD_LOOP_NORMAL);

	result = system->createStream("Audio/win.mp3", FMOD_DEFAULT, 0, &win_sound);
	result = win_sound->setMode(FMOD_LOOP_OFF);

	result = system->createStream("Audio/wood_hit.wav", FMOD_DEFAULT, 0, &wood_hit);
	result = wood_hit->setMode(FMOD_LOOP_OFF);

	result = system->createStream("Audio/lose.wav", FMOD_DEFAULT, 0, &lose_sound);
	result = lose_sound->setMode(FMOD_LOOP_OFF);
}

void AudioManager::updateSound()
{
	result = system->update();
}

AudioManager::AudioManager()
{
	
}

AudioManager::~AudioManager()
{
	result = channel->stop();
	golf_swing->release();
	ball_collide->release();
	nature_soundtrack->release();
	win_sound->release();
	wood_hit->release();
	lose_sound->release();
	system->release();
}
