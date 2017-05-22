#include "Sound.h"
using namespace std;

irrklang::ISoundEngine* engine;
irrklang::ISound* backgroundMusic;

void toggleBackgroundMusic() {
	backgroundMusic->setIsPaused(!backgroundMusic->getIsPaused());
}

void stopBackgroundMusic() {
	backgroundMusic->setIsPaused(true);
}

void soundInit()
{
	engine = createIrrKlangDevice();
	if (!engine) {
		cout << "Sound not working" << endl;
	}

	backgroundMusic = engine->play2D("MusicFiles/BackgroundMusic/africa!.mp3", true, false, true);
	backgroundMusic->setIsPaused(true);
}

void dropSoundEngine() {
	engine->drop();
}

void menuScrollSFX() {
	engine->play2D("MusicFiles/SoundEffects/rollover1.wav", false);
}