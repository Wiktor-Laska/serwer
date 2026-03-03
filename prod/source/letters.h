#ifndef LETTERS_H
#define LETTERS_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include "../glm/glm.hpp"

void initLetters(GLuint shaderProgram);
void drawLetter(char letter, glm::vec3 position, GLuint shaderProgram, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
void drawText(const char* text, glm::vec3 startPosition, GLuint shaderProgram, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
void deleteLeters();

#endif