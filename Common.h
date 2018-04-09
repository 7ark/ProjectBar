#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "HelperFunctions.h"

enum class Scenes { SceneAll, SceneRight, SceneLeft, UI, Beverages, Length };
enum class FillMode { None, BottomToTop, TopToBottom, LeftToRight, RightToLeft };

enum class DialogueOptions { Happy, Travel, Ask, Career, Expose, Length };
enum class CustomerReaction { Liked, Neutral, Disliked, Dead, Length };