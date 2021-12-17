#pragma once
#include <mutex>
#include <thread>
#include "vector"
#include "avion.h"
#include "aeroport.h"

class Avion;

class Ccr{
private:
    std::thread m_thread;
    bool m_stopThread;
    static void thread(bool&);
public:
    Ccr();
    explicit Ccr(bool&);
    ~Ccr();
    static std::mutex coutMutex;
    static std::vector<Avion*> avions;
    static void CcrThread(Ccr*, bool&);
};


