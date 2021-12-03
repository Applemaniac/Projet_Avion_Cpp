#include<iostream>
#include <utility>
#include "aeroport.h"

Aeroport::Aeroport() : m_identifiant("Lille"),
                       m_position(createPosition(0, 0, 0)),
                       m_capacite(10),
                       m_placesDisponible(10){
}

Aeroport::Aeroport(std::string identifiant, Position pos, int capacite) : m_identifiant(std::move(identifiant)),
                                                                          m_position(createPosition(pos.x, pos.y, pos.z)),
                                                                          m_capacite(capacite),
                                                                          m_placesDisponible(capacite){
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

bool Aeroport::atterrir(Avion *avion) {
  bool atterri = false;
  if(autorisationPourAtterrir()){
    this->m_placesDisponible--;
    this->m_avions.push_back(avion);
    avion->atterrirDansAeroport(this);
    atterri = true;
  }else{
    std::cout << "/!\\ AUTORISATION REFUSÉE D'ATTERRIR POUR " << avion->getIdentifiant() << " PAR L'AEROPORT DE " << this->m_identifiant << std::endl;
  }
  return atterri;
}

void Aeroport::tourDeControle(bool &stop) {
  std::cout << "ICI tour de contrôle de " << this->m_identifiant << ", je prends mon service." << std::endl;
  while (stop){
    if(!this->m_avions.empty()){
      Avion *avion = this->m_avions.front();
      //avion->faireDecoller();
    }else{
      // do stuff
    }
  }
  std::cout << "ICI tour de contrôle de " << this->m_identifiant << ", je finis mon service." << std::endl;
}

Aeroport::~Aeroport() {
  delete m_position;
}

