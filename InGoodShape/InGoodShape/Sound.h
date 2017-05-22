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