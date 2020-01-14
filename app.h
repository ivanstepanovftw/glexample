#include "window.h"

class Game {
public:
    Game()
    : Game{Window{}} // crashes because somewhere Window destructor called
    //: window{} // works
    {
      std::cout << "Game::Game()" << std::endl;
    }

    explicit Game(Window&& window)
    : window(std::move(window))
    {
      std::cout << "Game::Game(Window)" << std::endl;
    }

    virtual ~Game() {
      std::cout << "Game::~Game()" << std::endl;
    };

    int run() {
      std::cout << "Game::run()" << std::endl;
      while (window) {
        update();
      }
      return 0;
    }

protected:
    virtual void update() = 0;

    virtual void physics_update() {};

protected:
    Window window;
};
