#pragma once

#include <glexample/glfw/window.h>

class Game {
    size_t m_limit_fps = 0;

    static void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
      Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
      that->framebuffer_size_callback(w, h);
    }

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
      Game *that = static_cast<Game *>(glfwGetWindowUserPointer(window));
      that->key_callback(key, scancode, action, mods);
    }

    static void cursor_enter_callback(GLFWwindow *window, int key) {

    }

public:
    Game()
    : Game{Window{}} {}

    explicit Game(Window&& other) noexcept
    : window(std::move(other)) {
      glfwSetWindowUserPointer(window.get(), this);
      //glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
      glfwSetKeyCallback(window.get(), key_callback);
      // TODO:
      //glfwSetCursorEnterCallback(window.get(), cursor_enter_callback);
      //glfwSetJoystickCallback(window.get(), joystick_callback);
      //glfwSetScrollCallback(window.get(), scroll_callback);
      //glfwSetMouseButtonCallback(window.get(), button_callback);
      //glfwSetWindowCloseCallback(window.get(), close_callback);
      //glfwSetWindowFocusCallback(window.get(), focus_callback);
      //glfwSetWindowIconifyCallback(window.get(), iconify_callback));
      //glfwSetWindowMaximizeCallback(window.get(), maximize_callback);
      //glfwSetWindowPosCallback(window.get(), pos_callback);
      //glfwSetWindowRefreshCallback(window.get(), refresh_callback);
      //glfwSetWindowContentScaleCallback(window.get(), content_scale_callback);
    }

    virtual ~Game() = default;

    int run() {
      while (window) {
        render();
        glfwPollEvents();
      }
      return 0;
    }

protected:
    //std::vector<Window> windows;
    Window window;

    virtual void render() = 0;

    virtual void framebuffer_size_callback(int w, int h) {
      glViewport(0, 0, (GLsizei) w, (GLsizei) h);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glMatrixMode(GL_MODELVIEW);
    };

    virtual void key_callback(int key, int scancode, int action, int mods) {};

};
