#include <string>
#include "../headers/struct.h"

void setPosition(Position *pos, float x, float y, float z){
  pos->x = x;
  pos->y = y;
  pos->z = z;
}

Position* createPosition(float x, float y, float z){
  auto *pos = new Position;
  pos->x = x;
  pos->y = y;
  pos->z = z;
  return pos;
}

float getDistance(Position *a, Position *b){
  return std::sqrt( (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) + (b->z - a->z) * (b->z - a->z));
}

void getTrajectoire(Position *posActuel, Position *destination, float distance, float distanceTotal){

  posActuel->x = posActuel->x + (distance/distanceTotal) * (destination->x - posActuel->x);
  posActuel->y = posActuel->y + (distance/distanceTotal) * (destination->y - posActuel->y);
  posActuel->z = posActuel->z + (distance/distanceTotal) * (destination->z - posActuel->z);
}

float getUniqueZ(const std::string& id){
  float retour = 0;
  for (char i : id){
    retour += (float) i;
  }
  return retour;
}

/*float getAngle(Position u, Position v){
  float normeU = std::sqrt(u.x * u.x + u.y * u.y);
  float normeV = std::sqrt(v.x * v.x + v.y * v.y);
  float produitScalaire = u.x * v.y + v.x * u.y;
  float angle = std::acos(produitScalaire/(normeU * normeV));
  return angle;
}

Position* createVector(Position u, Position v){
  Position *retour = createPosition(v.x - u.x, v.y - u.y, 0);
  return retour;
}*/
