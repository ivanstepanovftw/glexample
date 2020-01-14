#include "window.h"

class Game {
public:
    Game()
    : Game{Window{}} {
      std::cout << "Game::Game()" << std::endl;
    }

    explicit Game(const Window& window)
    : window(window) {
      std::cout << "Game::Game(Window)" << std::endl;
    }

    explicit Game(Window&& window)
    : window(std::move(window)) {
      std::cout << "Game::Game(Window)" << std::endl;
    }

    virtual ~Game() = default;

    virtual int run() {
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
