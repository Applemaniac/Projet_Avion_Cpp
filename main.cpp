#include "main.h"

using namespace std::chrono_literals;


void add_plane_sometimes(bool &stop_thread)
{
  while (!stop_thread)
  {
    Avion avion;
    std::cout << avion.getIdentifiant() << std::endl;
    std::this_thread::sleep_for(3s);
  }
}

int main() {

  auto *lille = new Aeroport("Lille", {10, 0, 0}, 10);
  auto *marseille = new Aeroport("Marseille", {20, 20, 0}, 10);

  bool stop_thread = false;
  auto *avion = new Avion(lille, marseille, stop_thread);

  //std::thread avion_thread(add_plane_sometimes, std::ref(stop_thread));
  //std::thread avion_thread(&Avion::fly, avion, std::ref(stop_thread));

  while (1)
  {
    if(stop_thread){
      break;
    }

  }

  //avion_thread.join();
  delete avion;
  delete lille;
  delete marseille;
  std::cout << "Finish\n";
}