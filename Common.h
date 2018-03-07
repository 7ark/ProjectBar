#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "GameSettings.h"

enum class Scenes { SceneAll, SceneRight, SceneLeft, UI, Length };

enum class Drinks
{
	Water,
	Beer,
	Arsenic,
	Cyanide
};