#include "window.h"

class Game {
public:
    Game()
    : Game{Window{}} // crashes because somewhere Window destructor called
    //: window{} // works
    {
      std::cout << "Game::Game()" << std::endl;
    }

    explicit Game(const Window& window)
    : window(window)
    {
      std::cout << "Game::Game(const Window&)" << std::endl;
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
