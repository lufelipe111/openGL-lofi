#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <vector>

#include "abcg.hpp"
#include "camera.hpp"
#include "model.hpp"

// struct Vertex {
//   glm::vec3 position;

//   bool operator==(const Vertex& other) const {
//     return position == other.position;
//   }
// };

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};

  int m_viewportWidth{};
  int m_viewportHeight{};

  glm::mat4 m_modelMatrix{1.0f};
  glm::mat4 m_viewMatrix{1.0f};
  glm::mat4 m_projMatrix{1.0f};

  Camera m_camera;
  float m_dollySpeed{0.0f};
  float m_truckSpeed{0.0f};
  float m_panSpeed{0.0f};

  Model m_floor;
  int m_floorTrianglesToDraw{};
  glm::mat4 m_floorMatrix{1.0f};

  Model m_oldBed;
  int m_oldBedTrianglesToDraw{};
  glm::mat4 m_oldBedMatrix{1.0f};

  Model m_studyDesk;
  int m_studyDeskTrianglesToDraw{};
  glm::mat4 m_studyDeskMatrix{1.0f};

  Model m_shelf;
  int m_shelfTrianglesToDraw{};
  glm::mat4 m_shelfMatrix{1.0f};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  void loadModelFromFile(std::string_view path);
  void update();

  glm::vec4 hexToColorLoc(int hex, float alpha = 1.0f) {
    glm::vec4 colorLoc;

    colorLoc.r = ((hex >> 16) & 0xFF) / 255.0;  // 16-bit shift and get 2 digits
    colorLoc.g = ((hex >> 8) & 0xFF) / 255.0;   // 8-bit shift and get 2 digits
    colorLoc.b = ((hex >> 0) & 0xFF) / 255.0;   // 0-bit shift and get 2 digits
    colorLoc.a = alpha;

    return colorLoc;
  }
};

#endif