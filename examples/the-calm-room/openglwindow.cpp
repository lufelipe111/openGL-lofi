#include "openglwindow.hpp"

#include <imgui.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>

void OpenGLWindow::initializeGL() {
  abcg::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Dark Pink

  // Enable depth buffering
  abcg::glEnable(GL_DEPTH_TEST);

  // Create program
  m_program = createProgramFromFile(getAssetsPath() + "normal.vert",
                                    getAssetsPath() + "normal.frag");

  // Load models
  m_floor.loadObj(getAssetsPath() + "old_parquet\\sp_old_parquet.obj");
  m_floorTrianglesToDraw = m_floor.getNumTriangles();
  m_oldBed.loadObj(getAssetsPath() + "old_bed\\old_bed.obj");
  m_oldBedTrianglesToDraw = m_oldBed.getNumTriangles();
  m_studyDesk.loadObj(getAssetsPath() + "desk\\medium_study_desk.obj");
  m_studyDeskTrianglesToDraw = m_studyDesk.getNumTriangles();
  m_shelf.loadObj(getAssetsPath() + "bookcase\\new_shelf.obj");
  m_shelfTrianglesToDraw = m_shelf.getNumTriangles();

  m_floor.setupVAO(m_program);
  m_oldBed.setupVAO(m_program);
  m_studyDesk.setupVAO(m_program);
  m_shelf.setupVAO(m_program);

  resizeGL(getWindowSettings().width, getWindowSettings().height);
}

void OpenGLWindow::paintGL() {
  // update();

  // // Clear color buffer and depth buffer
  // abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  // abcg::glUseProgram(m_program);

  // // Get location of uniform variables (could be precomputed)
  // const GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
  // const GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};
  // const GLint modelMatrixLoc{glGetUniformLocation(m_program, "modelMatrix")};
  // const GLint normalMatrixLoc{glGetUniformLocation(m_program,
  // "normalMatrix")}; const GLint colorLoc{glGetUniformLocation(m_program,
  // "color")};

  // // Set uniform variables used by every scene object
  // abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE,
  //                          &m_camera.m_viewMatrix[0][0]);
  // abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE,
  //                          &m_camera.m_projMatrix[0][0]);

  // abcg::glBindVertexArray(0);

  update();

  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  // Use currently selected program
  abcg::glUseProgram(m_program);

  // Get location of uniform variables
  const GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
  const GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};
  const GLint modelMatrixLoc{glGetUniformLocation(m_program, "modelMatrix")};
  const GLint normalMatrixLoc{glGetUniformLocation(m_program, "normalMatrix")};

  // Set uniform variables used by every scene object
  abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE,
                           &m_camera.m_viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE,
                           &m_camera.m_projMatrix[0][0]);

  // Set uniform variables of the current object
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

  const auto modelViewMatrix{glm::mat3(m_viewMatrix * m_modelMatrix)};
  const glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  abcg::glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

  // render floor
  m_floorMatrix = glm::mat4{1.0f};
  m_floorMatrix = glm::translate(m_floorMatrix, glm::vec3{1.2f, 0.0f, 0.0f});
  m_floorMatrix = glm::scale(m_floorMatrix, glm::vec3(0.0005f));
  m_floorMatrix =
      glm::rotate(m_floorMatrix, glm::radians(0.0f), glm::vec3(0, 1, 0));

  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_floorMatrix[0][0]);
  // abcg::glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
  m_floor.render(m_floorTrianglesToDraw);  // important to render model before
                                           // set new uniform variables

  // render old bed
  m_oldBedMatrix = glm::mat4{1.0f};
  m_oldBedMatrix =
      glm::translate(m_oldBedMatrix, glm::vec3{-0.6f, 0.0f, -0.2f});
  m_oldBedMatrix = glm::scale(m_oldBedMatrix, glm::vec3(10.0f));
  m_oldBedMatrix =
      glm::rotate(m_oldBedMatrix, glm::radians(-90.0f), glm::vec3(0, 1, 0));

  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_oldBedMatrix[0][0]);
  // abcg::glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
  m_oldBed.render(m_oldBedTrianglesToDraw);  // important to render model before
                                             // set new uniform variables

  // render study desk
  m_studyDeskMatrix = glm::mat4{1.0f};
  m_studyDeskMatrix =
      glm::translate(m_studyDeskMatrix, glm::vec3{0.8f, 0.0f, 1.35f});
  m_studyDeskMatrix = glm::scale(m_studyDeskMatrix, glm::vec3(0.47f));
  m_studyDeskMatrix =
      glm::rotate(m_studyDeskMatrix, glm::radians(-90.0f), glm::vec3(0, 1, 0));

  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE,
                           &m_studyDeskMatrix[0][0]);

  glm::vec4 studyDeskColor = hexToColorLoc(0x1F1F1F, 1.0f);
  // abcg::glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);

  m_studyDesk.render(
      m_studyDeskTrianglesToDraw);  // important to render model before set new
                                    // uniform variables

  // render shelf
  m_shelfMatrix = glm::mat4{1.0f};
  m_shelfMatrix = glm::translate(m_shelfMatrix, glm::vec3{-0.6f, 0.0f, 1.75f});
  m_shelfMatrix = glm::scale(m_shelfMatrix, glm::vec3(1.2f));
  m_shelfMatrix =
      glm::rotate(m_shelfMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));

  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_shelfMatrix[0][0]);

  glm::vec4 shelfColor = hexToColorLoc(0x1F1F1F, 1.0f);
  // abcg::glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);

  m_shelf.render(m_shelfTrianglesToDraw);  // important to render model before
                                           // set new uniform variables

  abcg::glUseProgram(0);
}

void OpenGLWindow::paintUI() { abcg::OpenGLWindow::paintUI(); }

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  m_camera.computeProjectionMatrix(width, height);
}

void OpenGLWindow::terminateGL() {
  m_floor.terminateGL();

  abcg::glDeleteProgram(m_program);
}

void OpenGLWindow::update() {
  const float deltaTime{static_cast<float>(getDeltaTime())};

  m_camera.computeViewMatrix();
}
