#include <string>
#include "struct.h"

void setPosition(Position *pos, float x, float y, float z){
  pos->x = x;
  pos->y = y;
  pos->z = z;
}

Position* createPosition(float x, float y, float z){
  Position *pos = new Position;
  pos->x = x;
  pos->y = y;
  pos->z = z;
  return pos;
}

float getDistance(Position *a, Position *b){
  return sqrt( (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) + (b->z - a->z) * (b->z - a->z));
}

void getTrajectoire(Position *posActuel, Position *destination, float distance, float distanceTotal){

  posActuel->x = posActuel->x + (distance/distanceTotal) * (destination->x - posActuel->x);
  posActuel->y = posActuel->y + (distance/distanceTotal) * (destination->y - posActuel->y);
  posActuel->z = posActuel->z + (distance/distanceTotal) * (destination->z - posActuel->z);
}

float getUniqueZ(std::string id){
  float retour = 0;
  for (char i : id){
    retour += (float) i;
  }
  return retour;
}
