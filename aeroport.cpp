#include "aeroport.h"

Aeroport::Aeroport() : m_identifiant("Lille"),
                       m_stopThreadAeroport(true),
                       m_stopThreadTourDeControle(true),
                       m_position(createPosition(0, 0, 0)),
                       m_capacite(10),
                       m_placesDisponible(10){
  this->m_tourDeControle = new TourDeControle(this, std::ref(m_stopThreadTourDeControle));
  TourDeControle::createThread(m_tourDeControle, m_stopThreadTourDeControle);
}

Aeroport::Aeroport(std::string identifiant, Position pos, int capacite, bool &stop_thread) : m_identifiant(std::move(identifiant)),
                                                                                             m_stopThreadAeroport(stop_thread),
                                                                                             m_stopThreadTourDeControle(stop_thread),
                                                                                             m_position(createPosition(pos.x, pos.y, pos.z)),
                                                                                             m_capacite(capacite),
                                                                                             m_placesDisponible(capacite){
  this->m_thread = std::thread(threadApp, this, std::ref(m_stopThreadAeroport));
  this->m_tourDeControle = new TourDeControle(this, stop_thread);

}

Position* Aeroport::getPosition() {
  return this->m_position;
}

std::string Aeroport::getIdentifiant() {
  return this->m_identifiant;
}

/*bool Aeroport::autorisationPourAtterrir() const {
  bool retour = true;
  if (this->m_placesDisponible <= 0){
      retour = false;
  }
  return retour;
}*/

void Aeroport::centreApproche(bool &stop_thread) {
  Ccr::coutMutex.lock();
  std::cout << "Centre de contrôle d'approche de " << this->m_identifiant << " -> ALL : je prends mon service." << std::endl;
  Ccr::coutMutex.unlock();
  while (!stop_thread){
    if(!this->m_avions.empty()){
      for(int i = 0; i < this->m_avions.size(); i++){
        if (this->m_avions[i]->getApp()){
          std::cout << "APP de " << this->m_identifiant << " -> " << this->m_avions[i]->getIdentifiant() << " : Je vous prends en charge !" << std::endl;
          this->m_avions[i]->setApp(false);
          this->m_avions[i]->setFaireDesRonds(true);
          this->m_tourDeControle->getQueuexAtterissage().push_back(this->m_avions[i]);
          this->m_avions.erase(this->m_avions.begin() + i);
        }
      }
    }
  }
  Ccr::coutMutex.lock();
  std::cout << "Centre de contrôle d'approche de " << this->m_identifiant << " -> ALL : je finis mon service." << std::endl;
  Ccr::coutMutex.unlock();
}

Aeroport::~Aeroport() {
  this->m_stopThreadAeroport = true;
  this->m_thread.join();

  delete m_position;
}

void Aeroport::threadApp(Aeroport *aeroport, bool &stop) {
  aeroport->centreApproche(stop);
}

std::vector<Avion*>& Aeroport::getAvions() {
  return this->m_avions;
}

int Aeroport::getCapacite() const {
  return this->m_capacite;
}

int Aeroport::getplaceDisponible() const {
  return this->m_placesDisponible;
}

void Aeroport::setplaceDisponible(int value) {
  this->m_placesDisponible = value;
}