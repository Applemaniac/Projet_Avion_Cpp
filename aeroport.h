#pragma once
#include <string>
#include <vector>
#include "struct.h"
#include "avion.h"

class Avion;

class Aeroport{
private:
    std::string m_identifiant;
    Position *m_position;
    int m_capacite;
    int m_placesDisponible;
    std::vector<Avion*> m_avions;

public:
    Aeroport();
    ~Aeroport();
    Aeroport(std::string, Position, int);
    Position* getPosition();
    std::string getIdentifiant();
    bool autorisationPourAtterrir() const;
    bool atterrir(Avion*);
    void tourDeControle(bool&);
};
