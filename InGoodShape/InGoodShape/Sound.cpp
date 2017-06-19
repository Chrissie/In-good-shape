#include "Sound.h"
using namespace std;

irrklang::ISoundEngine* engine;
irrklang::ISound* backgroundMusic;

/* Function to toggle the background music (pause) */
void toggleBackgroundMusic() {
	backgroundMusic->setIsPaused(!backgroundMusic->getIsPaused());
}

/* Function to stop playing background music */
void stopBackgroundMusic() {
	backgroundMusic->setIsPaused(true);
}

/* Initialize the sound in the game. Start playing default background music */
void soundInit()
{
	engine = createIrrKlangDevice();
	if (!engine) {
		cout << "Sound not working" << endl;
		return;
	}

	backgroundMusic = engine->play2D("MusicFiles/BackgroundMusic/sandstorm.mp3", true, false, true);
	backgroundMusic->setVolume(1);
	backgroundMusic->setIsPaused(true);
}

/* Change the volume of the sound (value between 0 and 1) */
void setVolume(irrklang::ik_f32 volume) {
	engine->setSoundVolume(volume);
}

/* Remove sound engine and clear memory */
void dropSoundEngine() {
	engine->drop();
}

// Predefined menu scroll sound effect
void menuScrollSFX() {	engine->play2D("MusicFiles/SoundEffects/rollover1.wav", false); }

// Predefined click sound effects
void SFXClick1() { engine->play2D("MusicFiles/SoundEffects/click1.wav", false); }
void SFXClick2() { engine->play2D("MusicFiles/SoundEffects/click2.wav", false); }
void SFXClick3() { engine->play2D("MusicFiles/SoundEffects/click3.wav", false); }
void SFXClick4() { engine->play2D("MusicFiles/SoundEffects/click4.wav", false); }
void SFXClick5() { engine->play2D("MusicFiles/SoundEffects/click5.wav", false); }

// Predefined sound effects
void SFXSwitch1() { engine->play2D("MusicFiles/SoundEffects/levelComplete.mp3", false); }
void SFXSwitch2() { backgroundMusic->stop(); engine->play2D("MusicFiles/SoundEffects/Complete.mp3", false); backgroundMusic = engine->play2D("MusicFiles/BackgroundMusic/sandstorm.mp3", true, false, true); }
void SFXSwitch3() { engine->play2D("MusicFiles/SoundEffects/switch3.wav", false); }
void SFXSwitch4() { engine->play2D("MusicFiles/SoundEffects/switch4.wav", false); }
void SFXSwitch5() { engine->play2D("MusicFiles/SoundEffects/switch5.wav", false); }
void SFXSwitch6() { engine->play2D("MusicFiles/SoundEffects/switch6.wav", false); }
void SFXSwitch7() { engine->play2D("MusicFiles/SoundEffects/switch7.wav", false); }
void SFXSwitch8() { engine->play2D("MusicFiles/SoundEffects/switch8.wav", false); }
void SFXSwitch9() { engine->play2D("MusicFiles/SoundEffects/switch9.wav", false); }