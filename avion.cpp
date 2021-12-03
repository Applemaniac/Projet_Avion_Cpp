#include <map>
#include <chrono>
#include <iostream>

#include "avion.h"


using namespace std::chrono_literals;

std::map<std::string, Avion*> Avion::avions;

Avion::Avion() : m_stop_thread(true),
                 m_identifiant(Avion::createIdentifiant()),
                 m_position(new Position),
                 m_depart(new Aeroport),
                 m_arrive(new Aeroport),
                 m_vitesse(100),
                 m_dateDebut(time(0)),
                 m_deltaDate(time(0)),
                 m_distance(0),
                 m_essence(100){

  setPosition(this->m_position, m_depart->getPosition()->x, m_depart->getPosition()->y, m_depart->getPosition()->z);
}

Avion::Avion(Aeroport *depart, Aeroport *arrive, bool &stop) :
                                                   m_identifiant(Avion::createIdentifiant()),
                                                   m_position(createPosition(depart->getPosition()->x, depart->getPosition()->y, depart->getPosition()->z)),
                                                   m_depart(depart),
                                                   m_arrive(arrive),
                                                   m_vitesse(900),
                                                   m_dateDebut(time(0)),
                                                   m_deltaDate(time(0)),
                                                   m_distance(getDistance(depart->getPosition(), arrive->getPosition())),
                                                   m_essence(100){
  this->m_thread = std::thread(flyThread, this, std::ref(stop));
}


std::string Avion::createIdentifiant() {
  int nb = rand() % 899 + 100;
  int aleatoire = rand() % 10 + 1;
  std::string code;

  switch (aleatoire) {
    case 1:
      code = "ZI";
      break;
    case 2:
      code = "3S";
      break;
    case 3:
      code = "UU";
      break;
    case 4:
      code = "TX";
      break;
    case 5:
      code = "XK";
      break;
    case 6:
      code = "AF";
      break;
    case 7:
      code = "VT";
      break;
    case 8:
      code = "SS";
      break;
    case 9:
      code = "TO";
      break;
    case 10:
      code = "SE";
      break;
    default:
      break;
  }

  std::string id = code + std::to_string(nb);
  if (!Avion::avions.empty()) {
    if (Avion::avions.find(id) == Avion::avions.end()) {
      Avion::avions.insert({id, this});
    }else{
      Avion::createIdentifiant();
    }
    return id;
  }else{
    Avion::avions.insert({id, this});
    return id;
  }
}

std::string Avion::getIdentifiant() {
  return this->m_identifiant;
}

Position *Avion::getPosition() {
  return this->m_position;
}

void Avion::atterrirDansAeroport(Aeroport *aeroport) {
  std::cout << this->m_identifiant << "a atterri à " << aeroport->getIdentifiant() << std::endl;
  setPosition(this->m_position, aeroport->getPosition()->x, aeroport->getPosition()->y, aeroport->getPosition()->z);
  setPosition(this->m_depart->getPosition(), aeroport->getPosition()->x, aeroport->getPosition()->y, aeroport->getPosition()->z);
  setPosition(this->m_arrive->getPosition(), aeroport->getPosition()->x, aeroport->getPosition()->y, aeroport->getPosition()->z);
}

void Avion::fly(bool &stop) {
  while (!stop){
    std::time_t now = time(0);
    std::time_t duree = now - this->m_deltaDate; //en s
    float deltaDistance = (this->m_vitesse * duree) / 1000;
    getTrajectoire(this->m_position, this->m_arrive->getPosition(), deltaDistance, this->m_distance);
    this->m_deltaDate = now;
    std::cout << "x : " << this->m_position->x << " y = " << this->m_position->y << " z = " << this->m_position->z << std::endl;

    if (this->m_arrive->getPosition()->x - this->m_position->x < RADIUS_APP && this->getPosition()->y - this->m_position->y < RADIUS_APP && this->getPosition()->z - this->m_position->z < RADIUS_APP){
      std::cout << this->m_identifiant << " POUR APP DE " << this->m_arrive->getIdentifiant() << std::endl;
      stop = true;
    }

    std::this_thread::sleep_for(1s);
  }
}

void flyThread(Avion *avion, bool &stop_thread) {
  while (!stop_thread)
  {
    avion->fly(stop_thread);
  }
}

Avion::~Avion() {
  this->m_stop_thread = true;
  this->m_thread.join();

  delete m_position;
}


