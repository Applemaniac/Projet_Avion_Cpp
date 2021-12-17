#pragma once
#include <iostream>
#include <vector>
#include "aeroport.h"
#include "avion.h"

class Avion;
class Aeroport;

class TourDeControle{
private:
    std::thread m_thread;
    std::mutex m_mutex;
    bool m_stopThread;
    Aeroport *m_aeroport;
    std::vector<Avion*> m_queuxDecolage;
    std::vector<Avion*> m_queuxAtterissage;
    void tourDeControle(bool&);
public:
    TourDeControle();
    TourDeControle(Aeroport*, bool&);
    ~TourDeControle();
    static void createThread(TourDeControle*, bool&);
    std::vector<Avion*>& getQueuexAtterissage();
};