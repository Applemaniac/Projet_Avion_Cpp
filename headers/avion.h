#pragma once
#include "string"
#include <ctime>
#include <map>
#include <cstdlib>
#include <thread>
#include <mutex>
#include "aeroport.h"
#include "ccr.h"

#define RADIUS_APP 0.1

class Aeroport;

class Avion {
private:
    std::thread m_thread;
    bool m_stop_thread;
    bool m_callApp;
    bool m_faireDesRonds;
    bool m_voler;
    std::string m_identifiant;
    Position *m_position;
    Aeroport *m_depart;
    Aeroport *m_arrive;
    float m_vitesse; // en m/s
    time_t m_deltaDate;
    float m_distance; // en km/h
    void fly(bool&);
public:
    Avion();
    ~Avion();
    Avion(Aeroport*, Aeroport*, bool&);
    std::string createIdentifiant();
    std::string getIdentifiant();
    Position* getPosition();
    Aeroport* getDestination();
    void atterrir(Aeroport*);
    void decoler(Aeroport*);
    static void flyThread(Avion*, bool&);
    [[nodiscard]] bool getApp() const;
    void setApp(bool);
    void setFaireDesRonds(bool);
};

