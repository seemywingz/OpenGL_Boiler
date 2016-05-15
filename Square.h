//
// Created by KevAdmin on 4/25/2015.
//

#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <stdio.h>
#include "Utils.h"

class Square {

protected:
    // GLContext Variables
    GLuint
            vertexBuffer,
            shaderProgram,
            vao,
            ebo;

    // Verticies
    float vertices[12] = {
            -0.5f,  0.5f, 0.0f, // Top-left
            0.5f,  0.5f, 0.0f, // Top-right
            0.5f, -0.5f, 0.0f, // Bottom-right
            -0.5f, -0.5f, 0.0f  // Bottom-left
    };


    // Elements
    GLuint elements[6] = {
            0, 1, 2,
            2, 3, 0
    };

    // Shader sources
    const GLchar* vertexSource =
            "#version 150 core\n"
                    "in vec3 position;"
                    "void main() {"
                    "   gl_Position = vec4(position, 1.0);"
                    "}";
    const GLchar* fragmentSource =
            "#version 150 core\n"
                    "out vec4 outColor;"
                    "void main() {"
                    "   outColor = vec4(1.0,0.0,1.0, 1.0);"
                    "}";

public:
    Square(){

        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
//        ckGLError("Create vertex array object");

        // Element Buffers

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


        // vertex buffers
        glGenBuffers(1, &vertexBuffer); // Generate 1 buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // make active buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//        ckGLError("VBO");

        GLuint vertexShader = compileShader(GL_VERTEX_SHADER,vertexSource,"Vertex");
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,fragmentSource,"Fragment");

        // Link the vertex and fragment shader into a shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
//        ckGLError("Link Shader Program");

//        color = glGetUniformLocation(shaderProgram, "triangleColor");
//        glUniform3f(color, .00f, 1.0f, 1.0f);


        // Specify the layout of the vertex data
        GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
//        ckGLError("Set vertex data layout");
    }//..

    void draw(){
        glPushMatrix();

        glUseProgram (shaderProgram);
        glBindVertexArray (vao);

//        glTranslated(10,1,1);
        // Draw a triangle from the 3 vertices
//        glDrawArrays(GL_TRIANGLES, 0,3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glPopMatrix();
    }//..
};

#endif //SQUARE_H
