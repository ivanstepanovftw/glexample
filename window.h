//
// Created by ivan on 12.01.2020.
//

#pragma once

#include "init.h"
#include "linmath.h"
#include "exceptions.h"
#include <string>
#include <utility>
#include <memory>

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class WindowSettings {
    // TODO: https://github.com/glfw/glfw/blob/master/examples/sharing.c
public:
    WindowSettings() = default;

    virtual ~WindowSettings() = default;

    void use() const {
      glfwDefaultWindowHints();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    }

    [[nodiscard]] GLFWmonitor *getMonitor() const {
      return m_monitor;
    }

    WindowSettings& setMonitor(GLFWmonitor *monitor) {
      m_monitor = monitor;
      return *this;
    }

    [[nodiscard]] int getWidth() const {
      return m_width;
    }

    WindowSettings &setWidth(int width) {
      m_width = width;
      return *this;
    }

    [[nodiscard]] int getHeight() const {
      return m_height;
    }

    WindowSettings &setHeight(int height) {
      m_height = height;
      return *this;
    }

    [[nodiscard]] const std::string &getTitle() const {
      return m_title;
    }

    WindowSettings &setTitle(const std::string &title) {
      m_title = title;
      return *this;
    }

private:
    GLFWmonitor *m_monitor = nullptr;
    int m_width = 640, m_height = 480;
    std::string m_title = "Window Title";
};

class Window : public WindowSettings {
public:
    Window() : Window(WindowSettings{}) {};

    explicit Window(const WindowSettings& settings)
    : window{std::unique_ptr<GLFWwindow, decltype(&GLFWwindow_destroyer)>(GLFWwindow_constructor(settings), &GLFWwindow_destroyer)} {
      std::cout << "Window::Window(const WindowSettings&)" << std::endl;
      if (!window) {
        const char *description = "No error";
        glfwGetError(&description);
        throw WindowException("Unable to create GL window: " + std::string(description));
      }

      glfwMakeContextCurrent(window.get());
      glfwSwapInterval(1);
    }

    // todo: надо ли?
    explicit Window(const Window& w)
    : window{w.window} {}

    Window(Window&& w) noexcept
    : window{std::move(w.window)} {}

    virtual ~Window() = default;

    [[nodiscard]] GLFWwindow *get() const {
      return window.get();
    };

    explicit operator bool() const {
      return !glfwWindowShouldClose(window.get());
    }

private:
    static GLFWwindow *GLFWwindow_constructor(const WindowSettings& settings) {
      std::cout << "! GLFWwindow_constructor" << std::endl;
      settings.use();
      return glfwCreateWindow(settings.getWidth(), settings.getHeight(),
                              settings.getTitle().c_str(), settings.getMonitor(), nullptr);
    }

    static void GLFWwindow_destroyer(GLFWwindow *window) {
      std::cout<<"! GLFWwindow_destroyer"<<std::endl;
      if (window)
        glfwDestroyWindow(window);
    }

    std::shared_ptr<GLFWwindow> window;
};
