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

int main(){
  srand(time(NULL));
  bool threadLille = false;
  bool threadMarseille = false;
  bool threadCcr = false;
  auto *ccr = new Ccr(threadCcr);
  auto *lille = new Aeroport("Lille", {0, 0, 0}, 10, threadLille);
  auto *marseille = new Aeroport("Marseille", {10, 10, 0}, 10, threadMarseille);

  bool stop_thread = false;
  auto *avion = new Avion(lille, marseille, stop_thread);

  while (1)
  {
    std::string a;
    std::cin >> a;
    if(a == "0"){
      stop_thread = true;
      threadLille = true;
      threadMarseille = true;
      threadCcr = true;
      break;
    }

  }

  delete avion;
  delete lille;
  delete marseille;
  delete ccr;
  std::cout << "Finish\n";
}
