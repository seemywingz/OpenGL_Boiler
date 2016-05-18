//
// Created by KevAdmin on 4/25/2015.
//

#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <stdio.h>
#include "Utils.h"
#include "Position.h"

class Square {

protected:
    // GLContext Variables
    GLuint
            vertexBuffer,
            shaderProgram,
            vao,
            ebo;

    GLint posAttrib;

    Position * pos = new Position(0 ,0 ,0);

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
            "#version 400 core\n"
                    "layout(location = 0) in vec3 position;"
                    "uniform mat4 model;"
                    "uniform mat4 view;"
                    "uniform mat4 projection;"
                    "void main() {"
                    "  gl_Position = vec4(position, 1.0f);"
//                    "  gl_Position = projection * view * model * vec4(position, 1.0f);"
                    "}";
    const GLchar* fragmentSource =
            "#version 400 core\n"
                    "out vec4 outColor;"
                    "void main() {"
                    "   outColor = vec4(1.0, 0.0, 1.0, 1.0);"
                    "}";

public:
    Square(){

        // Create Vertex Array Object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        ckGLError("Create vertex array object");

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
//        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
        ckGLError("Link Shader Program");

//        color = glGetUniformLocation(shaderProgram, "triangleColor");
//        glUniform3f(color, .00f, 1.0f, 1.0f);

        // Specify the layout of the vertex data
      posAttrib = glGetAttribLocation(shaderProgram, "position");
      std::cout << "posAttrib: " << posAttrib << std::endl;
      glEnableVertexAttribArray(posAttrib);
      glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
      ckGLError("Set vertex data layout");
      posAttrib = glGetAttribLocation(shaderProgram, "position");
    }//..

    void draw(){

//      std::cout << "posAttrib: ";
//      posAttrib == -1 ? std::cout << "Not Found\n" : std::cout << posAttrib << std::endl;
      glUniform3f( posAttrib , pos->x += 0.1f, pos->y, pos->z);
//      std::cout << (pos->x += 0.1) << std::endl;

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
