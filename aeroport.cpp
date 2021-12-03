#include<iostream>
#include <utility>
#include "aeroport.h"

Aeroport::Aeroport() : m_identifiant("Lille"),
                       m_stop_thread(true),
                       m_position(createPosition(0, 0, 0)),
                       m_capacite(10),
                       m_placesDisponible(10){
}

Aeroport::Aeroport(std::string identifiant, Position pos, int capacite, bool &stop) : m_identifiant(std::move(identifiant)),
                                                                          m_stop_thread(stop),
                                                                          m_position(createPosition(pos.x, pos.y, pos.z)),
                                                                          m_capacite(capacite),
                                                                          m_placesDisponible(capacite){
  this->m_thread = std::thread(threadApp, this, std::ref(stop));

}

Position* Aeroport::getPosition() {
  return this->m_position;
}

std::string Aeroport::getIdentifiant() {
  return this->m_identifiant;
}

bool Aeroport::autorisationPourAtterrir() const {
  bool retour = true;
  if (this->m_placesDisponible <= 0){
      retour = false;
  }
  return retour;
}

/*bool Aeroport::atterrir(Avion *avion) {
  bool atterri = false;
  if(autorisationPourAtterrir()){
    this->m_placesDisponible--;
    Avion::avions.e(avion);
    avion->atterrirDansAeroport(this);
    atterri = true;
  }else{
    std::cout << "/!\\ AUTORISATION REFUSÉE D'ATTERRIR POUR " << avion->getIdentifiant() << " PAR L'AEROPORT DE " << this->m_identifiant << std::endl;
  }
  return atterri;
}*/

void Aeroport::centreApproche(bool &stop) {
  Ccr::ccrMutex.lock();
  std::cout << "ICI le centre de contrôle d'approche de " << this->m_identifiant << ", je prends mon service." << std::endl;
  Ccr::ccrMutex.unlock();
  while (stop){
  /*  if (!Ccr::avions.empty()) {
      for (const auto&[key, value]: Ccr::avions) {
        if (key != "") {
          if (value->getApp() && value->getDestination() == this) {
            Ccr::ccrMutex.lock();
            std::cout << "APP de " << this->m_identifiant << " -> " << key << " : Bien reçu, je vous prends en charge."
                      << std::endl;
            std::cout << "APP de " << this->m_identifiant << " -> CCR : " << key
                      << " rentre dans ma zone de contrôle, je prends le relais !" << std::endl;
            Ccr::ccrMutex.unlock();
            m_avions.insert({key, value});
            Ccr::avions.erase(key);
          }
        }
        std::cout << "C'est vide" << std::endl;
      }
    }*/
  }
  Ccr::ccrMutex.lock();
  std::cout << "ICI le centre de contrôle d'approche de " << this->m_identifiant << ", je finis mon service." << std::endl;
  Ccr::ccrMutex.unlock();
}

Aeroport::~Aeroport() {
  this->m_stop_thread = true;
  this->m_thread.join();

  delete m_position;
}

void Aeroport::threadApp(Aeroport *aeroport, bool &stop) {
  aeroport->centreApproche(stop);
}

std::vector<Avion *> Aeroport::getAvions() {
  return this->m_avions;
}

