#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <string>
#include <optional>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "struct.h"
#include "avion.h"
#include "aeroport.h"
#include "ccr.h"

#define WINDOW_SIZE_X 621
#define WINDOW_SIZE_Y 621
#define WORLD_LIMIT_X 10.0
#define WORLD_LIMIT_Y 10.0