#include "letters.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <iostream>


//define A vao, vbo
GLuint vao_A;
GLuint vbo_pos_A;
GLuint vbo_col_A;

GLfloat pos_A[] = { //define A pos matrix
    -0.25f, -0.5f, 0.0f,     -0.1f,  -0.5f, 0.0f,     -0.1f,   0.5f, 0.0f,
    -0.1f,  -0.5f, 0.0f,     -0.1f,   0.5f, 0.0f,      0.0f,   0.5f, 0.0f,

     0.1f,  -0.5f, 0.0f,      0.25f, -0.5f, 0.0f,      0.1f,   0.5f, 0.0f,
     0.1f,  -0.5f, 0.0f,      0.1f,   0.5f, 0.0f,      0.0f,   0.5f, 0.0f,

    -0.1f,   0.3f, 0.0f,      0.1f,   0.3f, 0.0f,      0.1f,   0.5f, 0.0f,
    -0.1f,   0.3f, 0.0f,      0.1f,   0.5f, 0.0f,     -0.1f,   0.5f, 0.0f,

    -0.1f,  -0.2f, 0.0f,      0.1f,  -0.2f, 0.0f,      0.1f,   0.0f, 0.0f,
    -0.1f,  -0.2f, 0.0f,      0.1f,   0.0f, 0.0f,     -0.1f,   0.0f, 0.0f
};

GLfloat col_A[24*3]; //define A col matrix

//define B vao, vbo
GLuint vao_B;
GLuint vbo_pos_B;
GLuint vbo_col_B;

GLfloat pos_B[] = { //define B pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

    //dolne
    -0.1f,  -0.5f,  0.0f,     -0.1f,  -0.35f, 0.0f,      0.1f,  -0.45f, 0.0f,
    -0.1f,  -0.35f, 0.0f,      0.1f,  -0.45f, 0.0f,      0.1f,  -0.3f,  0.0f,

     0.1f,  -0.45f, 0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,
     0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,      0.25f, -0.2f,  0.0f,

     0.1f,  -0.3f,  0.0f,      0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,
     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.1f,  -0.05f, 0.0f,

     0.1f,  -0.2f,  0.0f,      0.1f,  -0.05f, 0.0f,     -0.1f,  -0.1f,  0.0f,
     0.1f,  -0.05f, 0.0f,     -0.1f,  -0.1f,  0.0f,      0.0f,   0.0f,  0.0f,

    //gorne
    -0.1f,   0.5f,  0.0f,     -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,
    -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,

     0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.25f,  0.2f,  0.0f,

     0.1f,   0.3f,  0.0f,      0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,
     0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,      0.1f,   0.05f, 0.0f,

     0.1f,   0.2f,  0.0f,      0.1f,   0.05f, 0.0f,     -0.1f,   0.15f, 0.0f,
     0.1f,   0.05f, 0.0f,     -0.1f,   0.15f, 0.0f,     -0.02f, 0.02f, 0.0f,

     //dziura
    -0.1f,  -0.1f,  0.0f,     -0.1f,   0.15f, 0.0f,      0.0f,   0.0f,  0.0f
};

GLfloat col_B[57*3]; //define B col matrix



void init_A(GLuint shaderProgram) {
        glGenVertexArrays(1, &vao_A);
    glBindVertexArray(vao_A);

    for (int i = 0; i < 24 * 3; i += 3) {
        col_A[i]    = 1.0f; //red
        col_A[i+1]  = 0.0f; //green
        col_A[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_A);
    glGenBuffers(1, &vbo_col_A);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_A); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_A), pos_A, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_A);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_A), col_A, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}
//fix node number
void init_B(GLuint shaderProgram) {
        glGenVertexArrays(1, &vao_B);
    glBindVertexArray(vao_B);

    for (int i = 0; i < 57 * 3; i += 3) {
        col_B[i]    = 1.0f; //red
        col_B[i+1]  = 0.0f; //green
        col_B[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_B);
    glGenBuffers(1, &vbo_col_B);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_B); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_B), pos_B, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_B);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_B), col_B, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void initLetters(GLuint shaderProgram) {
    init_A(shaderProgram);
    init_B(shaderProgram);
}


void drawLetter(char letter, glm::vec3 position, GLuint shaderProgram, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 transformMatrix = projectionMatrix * viewMatrix * translationMatrix;

    GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");
    glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));

    switch (letter){
    case 'A':
    glBindVertexArray(vao_A);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    break;
    case 'B':
    glBindVertexArray(vao_B);
    glDrawArrays(GL_TRIANGLES, 0, 57);
    break;
    }
}

void drawText(const char* text, glm::vec3 startPosition, GLuint shaderProgram, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    float offset = 0.0f;

    for (int i = 0; text[i] != '\0'; i++) {
        glm::vec3 currentPos = glm::vec3(startPosition.x + offset, startPosition.y, startPosition.z);
        drawLetter(text[i], currentPos, shaderProgram, projectionMatrix, viewMatrix);
        offset += 0.6f;
    }
}

void deleteLeters() {
    glDeleteBuffers(1, &vbo_pos_A);
    glDeleteBuffers(1, &vbo_col_A);
    glDeleteVertexArrays(1, &vao_A);
}