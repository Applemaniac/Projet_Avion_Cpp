#include "ccr.h"
#include <iostream>

std::mutex Ccr::coutMutex;
std::mutex Ccr::avionsMutex;
std::vector<Avion*> Ccr::avions;

Ccr::Ccr(){
  this->m_thread = std::thread(CcrThread, this, std::ref(m_stopThread));
}

Ccr::Ccr(bool &stop_thread) : m_stopThread(stop_thread){
  this->m_thread = std::thread(CcrThread, this, std::ref(m_stopThread));
}

Ccr::~Ccr(){
  this->m_stopThread = true;
  this->m_thread.join();
}

void Ccr::thread(bool &stop_thread){
  coutMutex.lock();
  std::cout << "Centre de contrôle régional -> ALL : Je prends mon service." << std::endl;
  coutMutex.unlock();

  while (!stop_thread){
    for (int i = 0; i < Ccr::avions.size(); i++){
      if(Ccr::avions[i]->getApp()){
        // Ajouts de l'élément dans le tableau de l'aeroport
        Ccr::avions[i]->getDestination()->getAvions().push_back(Ccr::avions[i]);
        // Suppression de l'avion de le tableau du CCR
        Ccr::avions.erase(Ccr::avions.begin() + i);
      }
    }
  }

  coutMutex.lock();
  std::cout << "Centre de contrôle régional -> ALL : Je quitte mon service." << std::endl;
  coutMutex.unlock();

}

void Ccr::CcrThread(Ccr *ccr, bool &stop_thread){
  ccr->thread(stop_thread);
}