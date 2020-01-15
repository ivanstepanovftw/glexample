//
// Created by ivan on 12.01.2020.
//

#pragma once

#include <epoxy/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

class GLFWInit {
public:
    GLFWInit() noexcept {
      glfwSetErrorCallback([](int error, const char *description) -> void {
          std::cerr << "GLFW error: " << description << std::endl;
      });
      if (!glfwInit()) {
        exit(EXIT_FAILURE);
      }
    }

    ~GLFWInit() {
      glfwTerminate();
    }
};
