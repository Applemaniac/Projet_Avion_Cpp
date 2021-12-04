#pragma once
#include "string"
#include <ctime>
#include <map>
#include <cstdlib>
#include <thread>
#include <mutex>
#include "aeroport.h"
#include "ccr.h"

#define RADIUS_APP 10

class Aeroport;

class Avion {
private:
    std::thread m_thread;
    std::mutex globalMutex;
    bool m_stop_thread;
    bool m_callApp;
    std::string m_identifiant;
    Position *m_position;
    Aeroport *m_depart;
    Aeroport *m_arrive;
    float m_vitesse; // en m/s
    time_t m_dateDebut;
    time_t m_deltaDate;
    float m_distance; // en km/h
    float m_essence;
    void fly(bool&);
public:
    Avion();
    ~Avion();
    Avion(Aeroport*, Aeroport*, bool&);
    std::string createIdentifiant();
    std::string getIdentifiant();
    Position* getPosition();
    Aeroport* getDestination();
    void atterrirDansAeroport(Aeroport*);
    static void flyThread(Avion*, bool&);
    bool getApp();
    void setApp(bool);
};

