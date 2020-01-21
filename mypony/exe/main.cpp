#include <glexample/game.h>
#include <glexample/assets.h>
#include <glexample/shader.h>
#include <GLFW/glfw3.h>

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] =
  {
    {-0.6f, -0.4f, 1.f, 0.f, 0.f},
    {0.6f,  -0.4f, 0.f, 1.f, 0.f},
    {0.f,   0.6f,  0.f, 0.f, 1.f}
  };

class PonyGame : public Game {
public:
    PonyGame()
    : PonyGame{Window{}} {}

    explicit PonyGame(Window&& w)
    : Game(std::move(w)) {
      GLuint vertex_buffer;
      glGenBuffers(1, &vertex_buffer);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      s = new Shader("triangle");

      mvp_location = s->uniform("MVP");
      vpos_location = s->attrib("vPos");
      vcol_location = s->attrib("vCol");

      glEnableVertexAttribArray(vpos_location);
      glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                            sizeof(vertices[0]), (void *) nullptr);
      glEnableVertexAttribArray(vcol_location);
      glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                            sizeof(vertices[0]), (void *) (sizeof(float) * 2));
    }

    ~PonyGame() override = default;

    void render() override {
      float ratio;
      int width, height;
      mat4x4 m, p, mvp;

      glfwGetFramebufferSize(window.get(), &width, &height);
      ratio = width / (float) height;

      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);

      mat4x4_identity(m);
      mat4x4_rotate_Z(m, m, (float) glfwGetTime());
      mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      mat4x4_mul(mvp, p, m);

      s->use();
      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(window.get());
      glfwPollEvents();
    }

private:
    GLint mvp_location, vpos_location, vcol_location;
    Shader *s;
};


int main(int argc, char *argv[]) {

  {
    PonyGame myPony;
    myPony.run();
  }
  std::cout << "------------------------" << std::endl;
  std::cout << std::endl;
  //return 0;

  //{
  //  WindowHints ws;
  //  ws.setTitle("Hello world")
  //    .setWidth(900);
  //  Window w(ws);
  //  ws.setHeight(2);
  //  PonyGame myPony(std::move(w));
  //  myPony.run();
  //}
  //std::cout << "------------------------" << std::endl;
  //std::cout << std::endl;
  ////return 0;

  //WindowHints ws;
  //ws.setMonitor(nullptr)
  //  .setTitle("Window Title");
  //std::cout << std::endl;
  //
  //Window w(ws);
  //std::cout << std::endl;
  //
  //PonyGame myPony(w);
  //std::cout << std::endl;
  //
  //myPony.run();
  //std::cout << std::endl;
}
