#define LETTERS_H

#include <GL/gl.h>
#include "../glm/glm.hpp"

void initLetters();
void drawLetter(char letter, glm::vec3 position);
void drawText(const char* text, glm::vec3 startPosition);

