#pragma once
#include <string>
#include "struct.h"
#include "avion.h"
#include "ccr.h"

class Avion;

class Aeroport{
private:
    std::string m_identifiant;
    std::thread m_thread;
    bool m_stop_thread;
    Position *m_position;
    int m_capacite;
    int m_placesDisponible;
    std::vector<Avion*> m_avions;

public:
    Aeroport();
    ~Aeroport();
    Aeroport(std::string, Position, int, bool&);
    Position* getPosition();
    std::string getIdentifiant();
    std::vector<Avion*>& getAvions();
    bool autorisationPourAtterrir() const;
    //bool atterrir(Avion*);
    void centreApproche(bool&);
    static void threadApp(Aeroport*, bool&);
};
