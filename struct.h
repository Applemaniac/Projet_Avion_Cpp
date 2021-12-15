#pragma once
#include <cmath>

typedef struct position {
    float x;
    float y;
    float z;
}Position;

void setPosition(Position*, float, float, float);
Position* createPosition(float x, float y, float z);
void getTrajectoire(Position *, Position*, float , float);
float getDistance(Position*, Position*);
float getUniqueZ(std::string);