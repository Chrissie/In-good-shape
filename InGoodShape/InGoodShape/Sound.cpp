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
		return;
	}

	backgroundMusic = engine->play2D("MusicFiles/BackgroundMusic/Worldwar3.mp3", true, false, true);
	backgroundMusic->setVolume(0.32);
	backgroundMusic->setIsPaused(true);
}

void setVolume(irrklang::ik_f32 volume) {
	engine->setSoundVolume(volume);
}

void dropSoundEngine() {
	engine->drop();
}

void menuScrollSFX() {	engine->play2D("MusicFiles/SoundEffects/rollover1.wav", false); }

void SFXClick1() { engine->play2D("MusicFiles/SoundEffects/click1.wav", false); }
void SFXClick2() { engine->play2D("MusicFiles/SoundEffects/click2.wav", false); }
void SFXClick3() { engine->play2D("MusicFiles/SoundEffects/click3.wav", false); }
void SFXClick4() { engine->play2D("MusicFiles/SoundEffects/click4.wav", false); }
void SFXClick5() { engine->play2D("MusicFiles/SoundEffects/click5.wav", false); }

void SFXSwitch1() { engine->play2D("MusicFiles/SoundEffects/switch1.wav", false); }
void SFXSwitch2() { engine->play2D("MusicFiles/SoundEffects/switch2.wav", false); }
void SFXSwitch3() { engine->play2D("MusicFiles/SoundEffects/switch3.wav", false); }
void SFXSwitch4() { engine->play2D("MusicFiles/SoundEffects/switch4.wav", false); }
void SFXSwitch5() { engine->play2D("MusicFiles/SoundEffects/switch5.wav", false); }
void SFXSwitch6() { engine->play2D("MusicFiles/SoundEffects/switch6.wav", false); }
void SFXSwitch7() { engine->play2D("MusicFiles/SoundEffects/switch7.wav", false); }
void SFXSwitch8() { engine->play2D("MusicFiles/SoundEffects/switch8.wav", false); }
void SFXSwitch9() { engine->play2D("MusicFiles/SoundEffects/switch9.wav", false); }