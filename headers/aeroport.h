#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include<iostream>
#include "struct.h"
#include "avion.h"
#include "tourDeControle.h"
#include "ccr.h"

#define WINDOW_SIZE_X 621
#define WINDOW_SIZE_Y 621
#define WORLD_LIMIT_X 10.0
#define WORLD_LIMIT_Y 10.0


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
    [[nodiscard]] int getCapacite() const;
    [[nodiscard]] int getplaceDisponible() const;
    void setplaceDisponible(int);
    //bool autorisationPourAtterrir() const;
    void centreApproche(bool&);
    static void threadApp(Aeroport*, bool&);
};