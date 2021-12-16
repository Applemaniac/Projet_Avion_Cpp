#include "main.h"

#include <utility>

using namespace std::chrono_literals;

struct Aeroport_avec_sprite : public Aeroport{

    sf::RectangleShape sprite_;

    Aeroport_avec_sprite(std::string identifiant, Position pos, int capacite, bool &stop_thread) : Aeroport(std::move(identifiant), pos, capacite, stop_thread){
      sprite_.setSize({10, 10});
      sprite_.setFillColor(sf::Color(0, 0, 0));
    }

    sf::RectangleShape update(){
      sprite_.setPosition((this->getPosition()->x / (float) WORLD_LIMIT_X) * WINDOW_SIZE_X, (this->getPosition()->y / (float) WORLD_LIMIT_Y) * WINDOW_SIZE_Y);
      return sprite_;
    }
};

struct Avion_avec_sprite : public Avion{

    sf::Sprite sprite_;
    Avion_avec_sprite(Aeroport *depart, Aeroport *arrive, bool &stop, sf::Texture &texture) : Avion(depart, arrive, stop){
      sprite_.setTexture(texture);
      auto scale = 0.25f;
      sprite_.setScale(sf::Vector2f(scale, scale));

    }
    sf::Sprite &update(){
      sprite_.setPosition((this->getPosition()->x / (float) WORLD_LIMIT_X) * WINDOW_SIZE_X, (this->getPosition()->y / (float) WORLD_LIMIT_Y) * WINDOW_SIZE_Y);
      /*Position *vecteurA = createVector(*this->getDepart()->getPosition(), *this->getDestination()->getPosition());
      Position *vecteurB = createVector(*this->getPosition(), {0, 0, 0});
      sprite_.setRotation(getAngle(*vecteurA, *vecteurB) * 180.0 / 3.14159265);*/
      return sprite_;
    }
};



void affichage(std::vector<Avion_avec_sprite*> &planes, std::vector<Aeroport_avec_sprite*> &aeroport, bool &stop_thread){

  // Fenêtre
  sf::RenderWindow app(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32), "Trafic aerien - V1.1");

  // Frames Per Second (FPS)
  app.setFramerateLimit(30); // limite la fenêtre à 60 images par seconde

  sf::Texture backgroundImage;

  if (!backgroundImage.loadFromFile( "../img/france.png")){
    std::cerr << "Cannot load image file !" << std::endl;
    return; // On ferme le programme
  }

  sf::Sprite backgroundSprite(backgroundImage);

    /********************************/


  while (app.isOpen()){ // Boucle principale
    sf::Event event{};
    while (app.pollEvent(event)){ // Boucle des évènements de la partie pause

      if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == sf::Event::Closed){
        app.close();
        break;
      }
    }

    // Affichages
    app.clear();
    app.draw(backgroundSprite);

    for (auto &plane : planes){
      app.draw(plane->update());
    }

    for (auto &a : aeroport){
      app.draw(a->update());
    }

    app.display();
  }
  stop_thread = true;
}


int main(){

  std::vector<Avion_avec_sprite*> planes;
  std::vector<Aeroport_avec_sprite*> aeroport;

  sf::Texture background;
  sf::Texture planeTexture;
  planeTexture.loadFromFile("../img/avion.png");


  bool threadLille = false;
  bool threadMarseille = false;
  bool threadMetz = false;
  bool threadBordeaux = false;
  bool threadCcr = false;

  auto *lille = new Aeroport_avec_sprite("Lille", {3, 3, 0}, 10, threadLille);
  auto *marseille = new Aeroport_avec_sprite("Marseille", {7, 7, 0}, 10, threadMarseille);
  auto *metz = new Aeroport_avec_sprite("Metz", {6.8, 3, 0}, 2, threadMetz);
  auto *bordeaux = new Aeroport_avec_sprite("Bordeaux", {3.3, 6, 0}, 5, threadBordeaux);

  aeroport.push_back(lille);
  aeroport.push_back(marseille);
  aeroport.push_back(metz);
  aeroport.push_back(bordeaux);

  bool stop_thread = false;

  auto *avion = new Avion_avec_sprite(lille, marseille, stop_thread, planeTexture);
  auto *avion1 = new Avion_avec_sprite(marseille, lille, stop_thread, planeTexture);
  auto *avion2 = new Avion_avec_sprite(metz, bordeaux, stop_thread, planeTexture);
  auto *avion3 = new Avion_avec_sprite(bordeaux, metz, stop_thread, planeTexture);

  planes.push_back(avion);
  planes.push_back(avion1);
  planes.push_back(avion2);
  planes.push_back(avion3);

  auto *ccr = new Ccr(threadCcr);

  std::thread UI(affichage, std::ref(planes), std::ref(aeroport), std::ref(stop_thread));

  while (!stop_thread){
    // BUY ETH (il fallait mettre quelque chose...)
  }

  UI.join();

  threadCcr = true;
  threadLille = true;
  threadMarseille = true;
  threadMetz = true;
  threadBordeaux = true;

  delete lille;
  delete marseille;
  delete ccr;
  std::cout << "Finish\n";
}
