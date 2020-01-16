//
// Created by ivan on 12.01.2020.
//

#pragma once

#include <glexample/linmath.h>
#include <glexample/exceptions.h>
#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include <glexample/glfw/init.h>
#include <vector>

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class WindowHints {
    GLFWmonitor *m_monitor = nullptr;
    GLFWwindow *m_share = nullptr;
    int m_width = 640, m_height = 480;
    std::string m_title = "Window Title";
public:
    WindowHints() = default;

    virtual ~WindowHints() = default;

    void use() const {
      glfwDefaultWindowHints();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    }

    [[nodiscard]] GLFWmonitor *getMonitor() const {
      return m_monitor;
    }

    WindowHints& setMonitor(GLFWmonitor *monitor) {
      m_monitor = monitor;
      return *this;
    }

    [[nodiscard]] GLFWwindow *getShare() const {
      return m_share;
    }

    WindowHints& setShare(GLFWwindow *share) {
      m_share = share;
      return *this;
    }

    [[nodiscard]] int getWidth() const {
      return m_width;
    }

    WindowHints &setWidth(int width) {
      m_width = width;
      return *this;
    }

    [[nodiscard]] int getHeight() const {
      return m_height;
    }

    WindowHints &setHeight(int height) {
      m_height = height;
      return *this;
    }

    [[nodiscard]] const std::string &getTitle() const {
      return m_title;
    }

    WindowHints &setTitle(const std::string &title) {
      m_title = title;
      return *this;
    }
};


class Window {
    std::shared_ptr<GLFWwindow> window;

    static GLFWwindow *GLFWwindow_constructor(const WindowHints &hints) {
      hints.use();
      GLFWwindow *ret = glfwCreateWindow(hints.getWidth(), hints.getHeight(),
                                         hints.getTitle().c_str(), hints.getMonitor(), hints.getShare());
      return ret;
    }

    static void GLFWwindow_destroyer(GLFWwindow *window) {
      glfwDestroyWindow(window);
    }

public:
    Window()
    : Window(WindowHints{}) {};

    explicit Window(const WindowHints& hint)
    : window{std::unique_ptr<GLFWwindow, decltype(&GLFWwindow_destroyer)>(GLFWwindow_constructor(hint), &GLFWwindow_destroyer)} {
      if (!window) {
        const char *description = "No error";
        glfwGetError(&description);
        throw WindowException("Unable to create GL window: " + std::string(description));
      }

      glfwMakeContextCurrent(window.get());
      glfwSwapInterval(1);
    }

    virtual ~Window() = default;

    // move constructor
    Window(Window&& other) noexcept
    : window{std::move(other.window)} {}

    // copy constructor
    Window(const Window& other)
    : window{other.window} {}

    [[nodiscard]] GLFWwindow *get() const {
      return window.get();
    };

    explicit operator bool() const {
      return !glfwWindowShouldClose(window.get());
    }
};
