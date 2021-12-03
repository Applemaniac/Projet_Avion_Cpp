#pragma once
#include "string"
#include <ctime>
#include <map>
#include <cstdlib>
#include <thread>
#include "aeroport.h"

#define RADIUS_APP 10

class Aeroport;

class Avion {
private:
    static std::map<std::string, Avion*> avions;
    std::thread m_thread;
    bool m_stop_thread;
    std::string m_identifiant;
    Position *m_position;
    Aeroport *m_depart;
    Aeroport *m_arrive;
    float m_vitesse; // en m/s
    time_t m_dateDebut;
    time_t m_deltaDate;
    float m_distance; // en km/h
    float m_essence;
public:
    Avion();
    ~Avion();
    Avion(Aeroport*, Aeroport*, bool&);
    std::string createIdentifiant();
    std::string getIdentifiant();
    Position* getPosition();
    void atterrirDansAeroport(Aeroport*);
    void fly(bool&);
};

void flyThread(Avion*, bool&);
