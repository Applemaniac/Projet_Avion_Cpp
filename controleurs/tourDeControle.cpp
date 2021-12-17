#include "../headers/tourDeControle.h"

using namespace std::chrono_literals;

TourDeControle::TourDeControle() : m_stopThread(true) {
  Aeroport *aeroport = new Aeroport();
  this->m_aeroport = aeroport;
}

TourDeControle::TourDeControle(Aeroport *aeroport, bool &stop_thread) : m_aeroport(aeroport),
                                                                        m_stopThread(stop_thread){
  this->m_thread = std::thread(createThread, this, std::ref(stop_thread));
}

TourDeControle::~TourDeControle() {
  this->m_stopThread = true;
  this->m_thread.join();

  delete this->m_aeroport;
}

void TourDeControle::tourDeControle(bool &stop_thread) {
  Ccr::coutMutex.lock();
  std::cout << "Tour de contrôle de " << this->m_aeroport->getIdentifiant() << " -> ALL :  je prends mon service." << std::endl;
  Ccr::coutMutex.unlock();

  while(!stop_thread){
    if(!this->m_queuxDecolage.empty()){
      this->m_mutex.lock();
      this->m_aeroport->setplaceDisponible(this->m_aeroport->getplaceDisponible() + 1 <= this->m_aeroport->getCapacite() ? this->m_aeroport->getplaceDisponible() + 1 : this->m_aeroport->getplaceDisponible());
      this->m_queuxDecolage[0]->decoler(this->m_aeroport);
      std::this_thread::sleep_for(5s); // On attends 5s entre chaque décolage
      this->m_mutex.unlock();
      Ccr::avions.push_back(this->m_queuxDecolage[0]);
      this->m_queuxDecolage.erase(this->m_queuxDecolage.begin());
    }
    if(!this->m_queuxAtterissage.empty() && this->m_aeroport->getplaceDisponible() - 1 >= 0){
      this->m_mutex.lock();
      this->m_aeroport->setplaceDisponible(this->m_aeroport->getplaceDisponible() - 1);
      this->m_queuxAtterissage[0]->atterrir(this->m_aeroport);
      std::this_thread::sleep_for(5s); // On attends 5s entre chaque atterrissage
      this->m_mutex.unlock();

      this->m_queuxDecolage.push_back(this->m_queuxAtterissage[0]);
      this->m_queuxAtterissage.erase(this->m_queuxAtterissage.begin());
    }
  }

  Ccr::coutMutex.lock();
  std::cout << "Tour de contrôle de " << this->m_aeroport->getIdentifiant() << " -> ALL : je finis mon service." << std::endl;
  Ccr::coutMutex.unlock();
}

void TourDeControle::createThread(TourDeControle *tourDeControle, bool &stop_thread) {
  tourDeControle->tourDeControle(stop_thread);
}

std::vector<Avion *> &TourDeControle::getQueuexAtterissage() {
  return this->m_queuxAtterissage;
}
