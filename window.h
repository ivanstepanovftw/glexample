//
// Created by ivan on 12.01.2020.
//

#pragma once

#include "init.h"
#include "linmath.h"
#include "exceptions.h"
#include <string>
#include <utility>

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class WindowSettings {
    // TODO: https://github.com/glfw/glfw/blob/master/examples/sharing.c
public:
    WindowSettings() {
      std::cout << "WindowSettings::WindowSettings()" << std::endl;
    }

    ~WindowSettings() {
      std::cout << "WindowSettings::~WindowSettings()" << std::endl;
    }

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

    void setWidth(int width) {
      m_width = width;
    }

    [[nodiscard]] int getHeight() const {
      return m_height;
    }

    void setHeight(int height) {
      m_height = height;
    }

    [[nodiscard]] const std::string &getTitle() const {
      return m_title;
    }

    void setTitle(const std::string &title) {
      m_title = title;
    }

private:
    GLFWmonitor *m_monitor = nullptr;
    int m_width = 640, m_height = 480;
    std::string m_title = "Window Title";
};

class Window : public WindowSettings {
public:
    Window()
    : Window(WindowSettings())
    {
      std::cout << "Window::Window()" << std::endl;
    }

    explicit Window(const WindowSettings& settings) {
      std::cout << "Window::Window(const WindowSettings&)" << std::endl;

      settings.use();
      window = glfwCreateWindow(settings.getWidth(), settings.getHeight(),
                                settings.getTitle().c_str(), settings.getMonitor(), nullptr);
      if (!window) {
        const char *description = "No error";
        glfwGetError(&description);
        throw WindowException("Unable to create GL window: " + std::string(description));
      }

      glfwMakeContextCurrent(window);
      glfwSwapInterval(1);
    }

    ~Window() {
      std::cout<<"Window::~Window()"<<std::endl;
      if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
      }
    }

    [[nodiscard]] GLFWwindow *get() const {
      return window;
    };

    explicit operator bool() const {
      return !glfwWindowShouldClose(window);
    }

private:
    GLFWwindow *window = nullptr;
};
