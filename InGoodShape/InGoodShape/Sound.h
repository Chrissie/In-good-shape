#pragma once
// Standard includes.
#include <iostream>

// irrKlang includes
#include "include/irrKlang.h"
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll



void soundInit();
void dropSoundEngine();
void toggleBackgroundMusic();
void stopBackgroundMusic();
void menuScrollSFX();
void setVolume(irrklang::ik_f32);

void SFXClick1();
void SFXClick2();
void SFXClick3();
void SFXClick4();
void SFXClick5();

void SFXSwitch1();
void SFXSwitch2();
void SFXSwitch3();
void SFXSwitch4();
void SFXSwitch5();
void SFXSwitch6();
void SFXSwitch7();
void SFXSwitch8();
void SFXSwitch9();