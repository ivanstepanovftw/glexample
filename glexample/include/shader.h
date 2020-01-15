//
// Created by ivan on 12.01.2020.
//
#pragma once

#include <epoxy/gl.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <glexample/assets.h>

// TODO: remove
namespace fs = std::filesystem;

class Shader {
public:
    Shader(const std::string& name) {

      //Get the file paths
      const fs::path frag = assetManager.find(name + ".frag");
      const fs::path vert = assetManager.find(name + ".vert");

      //Load the shaders from disk
      fragId = load(frag.c_str(), GL_FRAGMENT_SHADER);
      vertId = load(vert.c_str(), GL_VERTEX_SHADER);

      //Create the program
      progId = glCreateProgram();
      glAttachShader(progId, fragId);
      glAttachShader(progId, vertId);

      //Bind variables
      for (size_t i = 0; i < attribs.size(); i++) {
        glBindAttribLocation(progId, (GLuint) i, attribs[i].c_str());
      }

      //Link the program
      glLinkProgram(progId);

      //Check for linking errors
      GLint isLinked;
      glGetProgramiv(progId, GL_LINK_STATUS, &isLinked);
      if (!isLinked) {
        GLint logLength;
        glGetProgramiv(progId, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> log;
        log.resize(logLength);
        glGetProgramInfoLog(progId, logLength, &logLength, log.data());

        std::ofstream fout(std::string(vert) + ".link.log");
        fout.write(log.data(), logLength);

        progId = 0;
        return;
      }

      //Get global variable locations
      //mvpId = glGetUniformLocation(progId, "mvp");
      //mvId = glGetUniformLocation(progId, "mv");
    }

    ~Shader() {
      glDetachShader(progId, vertId);
      glDetachShader(progId, fragId);
      glDeleteProgram(progId);
      glDeleteShader(vertId);
      glDeleteShader(fragId);
    }

    [[nodiscard]] GLint uniform(const std::string &var) const {
      return glGetUniformLocation(progId, var.c_str());
    }

    [[nodiscard]] GLint attrib(const std::string& var) const {
      return glGetAttribLocation(progId, var.c_str());
    }

    void use() const {
      glUseProgram(progId);
    }

    //void SetMVP(const float *mvp, const float *mv) {
    //  if (mvp) glUniformMatrix4fv(mvpId, 1, GL_TRUE, mvp);
    //  if (mv) glUniformMatrix4fv(mvId, 1, GL_TRUE, mv);
    //}

protected:
    [[nodiscard]] GLuint load(const char *fname, GLenum type) {
      //Read shader source from disk
      std::ifstream fin(fname);
      std::stringstream buff;
      buff << fin.rdbuf();
      const std::string str = buff.str();
      const char *source = str.c_str();

      //Create and compile shader
      const GLuint id = glCreateShader(type);
      glShaderSource(id, 1, (const GLchar **) &source, nullptr);
      glCompileShader(id);

      //Check to make sure there were no errors
      GLint isCompiled;
      glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
      if (!isCompiled) {
        GLint logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> log;
        log.resize(logLength);
        glGetShaderInfoLog(id, logLength, &logLength, log.data());

        auto a = std::string(fname) + ".log";
        std::ofstream fout(std::string(fname) + ".log");
        fout.write(log.data(), logLength);
        return 0;
      }

      //Save variable bindings
      if (type == GL_VERTEX_SHADER) {
        size_t ix = 0;
        while (true) {
          ix = str.find("\nin ", ix);
          if (ix == std::string::npos) {
            break;
          }
          ix = str.find(";", ix);
          size_t start_ix = ix;
          while (str[--start_ix] != ' ');
          attribs.push_back(str.substr(start_ix + 1, ix - start_ix - 1));
        }

        //todo
        //std::cout<<"attribs: ";
        //for(auto& a : attribs) {
        //  std::cout << a << std::endl;
        //}
        //std::cout << std::endl;
      }

      //Return the shader id
      return id;
    }

private:
    std::vector<std::string> attribs;
    GLuint fragId;
    GLuint vertId;
    GLuint progId;
    //GLuint mvpId;
    //GLuint mvId;
};
