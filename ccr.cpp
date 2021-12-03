#include "ccr.h"
#include <iostream>

std::mutex Ccr::ccrMutex;
std::vector<Avion*> Ccr::avions;

Ccr::Ccr(){
  this->m_thread = std::thread(CcrThread, this, std::ref(m_stopThread));
}

Ccr::~Ccr(){
  this->m_stopThread = true;
  this->m_thread.join();
}

void Ccr::thread(bool &stop_thread){
  ccrMutex.lock();
  std::cout << "Centre de contrôle régional -> ALL : Je prends mon service." << std::endl;
  ccrMutex.unlock();

  while (!stop_thread){
    for (Avion *avion : avions){
      if(avion->getApp()){
        // Ajouts de l'élément dans le tableau de l'aeroport
        avion->getDestination()->getAvions().push_back(avion);
        // Suppression de l'avion de le tableau du CCR
      }
    }
  }

  ccrMutex.lock();
  std::cout << "Centre de contrôle régional -> ALL : Je quitte mon service." << std::endl;
  ccrMutex.unlock();

}

void Ccr::CcrThread(Ccr *ccr, bool &stop_thread){
  ccr->thread(stop_thread);
}