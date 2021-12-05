#pragma once
#include <string>
#include "struct.h"
#include "avion.h"
#include "tourDeControle.h"
#include "ccr.h"

class Avion;
class TourDeControle;

class Aeroport{
private:
    std::string m_identifiant;
    std::thread m_thread;
    bool m_stopThreadAeroport;
    bool m_stopThreadTourDeControle;
    TourDeControle *m_tourDeControle;
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
    int getCapacite() const;
    int getplaceDisponible() const;
    void setplaceDisponible(int);
    bool autorisationPourAtterrir() const;
    //bool atterrir(Avion*);
    void centreApproche(bool&);
    static void threadApp(Aeroport*, bool&);
};
