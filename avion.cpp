#include <map>
#include <chrono>
#include <iostream>

#include "avion.h"


using namespace std::chrono_literals;

Avion::Avion() : m_callApp(true),
                 m_stop_thread(true),
                 m_faireDesRonds(false),
                 m_voler(false),
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
                                                   m_callApp(false),
                                                   m_faireDesRonds(false),
                                                   m_stop_thread(stop),
                                                   m_voler(true),
                                                   m_position(createPosition(depart->getPosition()->x, depart->getPosition()->y, depart->getPosition()->z)),
                                                   m_depart(depart),
                                                   m_arrive(arrive),
                                                   m_vitesse(900),
                                                   m_dateDebut(time(0)),
                                                   m_deltaDate(time(0)),
                                                   m_distance(getDistance(depart->getPosition(), arrive->getPosition())),
                                                   m_essence(100){
  this->m_thread = std::thread(flyThread, this, std::ref(m_stop_thread));
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
  if (!Ccr::avions.empty()) {
    for (Avion *avion : Ccr::avions){
      if (id == avion->getIdentifiant()){
        Avion::createIdentifiant();
      }
    }
    Ccr::avions.push_back(this);
    return id;
  }else{
    Ccr::avions.push_back(this);
    return id;
  }
}

std::string Avion::getIdentifiant() {
  return this->m_identifiant;
}

Position *Avion::getPosition() {
  return this->m_position;
}

void Avion::atterrir(Aeroport *aeroport) {
  std::cout << this->m_identifiant << " a atterri à " << aeroport->getIdentifiant() << std::endl;
  setPosition(this->m_position, this->m_arrive->getPosition()->x, this->m_arrive->getPosition()->y, this->m_arrive->getPosition()->z);
  this->m_stop_thread = false;
  this->m_faireDesRonds = false;
  this->m_voler = false;
}

void Avion::fly(bool &stop_thread) {
  while (!stop_thread){
    std::time_t now = time(0);
    std::time_t duree = now - this->m_deltaDate; //en s
    float deltaDistance = (this->m_vitesse * duree) / 1000;
    this->m_deltaDate = now;
    this->m_position->z = getUniqueZ(this->getIdentifiant());

    if (abs(this->m_arrive->getPosition()->x - this->m_position->x) < RADIUS_APP && abs(this->getPosition()->y - this->m_position->y) < RADIUS_APP && this->m_voler && !this->m_callApp){
      Ccr::coutMutex.lock();
      std::cout << this->m_identifiant << " -> APP de " << this->m_arrive->getIdentifiant() << " : Je rentre dans votre zone." << std::endl;
      Ccr::coutMutex.unlock();
      this->m_callApp = true;
    }else if (this->m_faireDesRonds){ // Si on est dans la zone de l'aéroport et que l'on attend d'atterrir
      // CE CODE EST POURRI MAIS JE NE SAIS COMMENT FAIRE AUTREMENT
      Position *direction = createPosition(this->m_arrive->getPosition()->x + 10, this->m_arrive->getPosition()->y + 10,  this->m_position->z);
      if (this->m_arrive->getPosition()->x - this->m_position->x < RADIUS_APP && this->getPosition()->y - this->m_position->y < RADIUS_APP && this->getPosition()->z - this->m_position->z < RADIUS_APP){
        // On fait sortir l'avion s'il est dans la zone
        getTrajectoire(this->m_position, direction, deltaDistance, this->m_distance - 10);
      }else{
        // On le fait rentrer s'il n'est plus dans la zone
        getTrajectoire(this->m_position, this->m_arrive->getPosition(), deltaDistance, this->m_distance);
      }
    }else if (m_voler){
      getTrajectoire(this->m_position, this->m_arrive->getPosition(), deltaDistance, this->m_distance);
      Ccr::coutMutex.lock();
      std::cout << "x : " << this->m_position->x << " y = " << this->m_position->y << " z = " << this->m_position->z << std::endl;
      Ccr::coutMutex.unlock();
    }else{
      // Zone de standby, pour ne pas tuer le thread...
    }

    std::this_thread::sleep_for(1s);
  }
}

void Avion::flyThread(Avion *avion, bool &stop_thread) {
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

bool Avion::getApp() const {
  return this->m_callApp;
}

Aeroport *Avion::getDestination() {
  return this->m_arrive;
}

void Avion::setApp(bool value) {
  this->m_callApp = value;
  int a = 0;
}

void Avion::decoler(Aeroport *aeroport) {
  if (this->m_arrive == aeroport){
    // On inverse le trajet : Lille -> Paris devient Lille <- Paris
    Aeroport *tmp = this->m_depart;
    this->m_depart = aeroport;
    this->m_arrive = tmp;
  }
  Ccr::coutMutex.lock();
  std::cout << this->m_depart->getIdentifiant() << " -> APP de " << this->m_depart->getIdentifiant() << " : " << this->getIdentifiant() << " vient de décoler." << std::endl;
  Ccr::coutMutex.unlock();
  this->m_stop_thread = false;
  this->m_callApp = false;
  this->m_voler = true;
}

bool Avion::getFaireDesRonds() const{
  return m_faireDesRonds;
}

void Avion::setFaireDesRonds(bool value) {
  this->m_faireDesRonds = value;
}
