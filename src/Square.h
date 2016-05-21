//
// Created by Kevin Jayne on 4/25/2015.
//

#ifndef SQUARE_H
#define SQUARE_H

#include "GL/glew.h"
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

    // gl shader data locations
    const GLint
            vPos = 0,
            vColor =1;

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
            "#version 430 core\n"
                    "layout(location = 0) in vec3 vPos;"
                    "layout(location = 1) uniform vec4 vColor;"
                    "out vec4 color;"
                    "void main() {"
                    "  color = vColor;"
                    "  gl_Position = vec4(vPos, 1.0f);"
                    "}";
    const GLchar* fragmentSource =
            "#version 430 core\n"
                    "in vec4 color;"
                    "out vec4 fcolor;"
                    "void main() {"
                    "   fcolor = color;"
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
        ckGLError("VBO");

        GLuint vertexShader = compileShader(GL_VERTEX_SHADER,vertexSource,"Vertex");
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,fragmentSource,"Fragment");

        // Link the vertex and fragment shader into a shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        ckGLError("Link Shader Program");

        // Specify the layout of the vertex data
        glEnableVertexAttribArray(vPos);
        glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
        ckGLError("Set vertex data layout");

        glEnableVertexAttribArray(vColor);
        glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
      ckGLError("Set color data layout");
    }//..

    void draw(){
//        GLboolean transpose = GL_TRUE;
//        const GLfloat *matx = { ... };
//        glUniformMatrix4fv(vColor, 3, transpose, matx);

//      std::cout << "x: " << (pos->x) << std::endl;

      glPushMatrix();

        glUniform4f( vColor , 1.0, 1.0, 1.0, 1.0);
        glUseProgram (shaderProgram);
        glBindVertexArray (vao);


//        glTranslated(10,1,1);
        // Draw a triangle from the 3 vertices
//        glDrawArrays(GL_TRIANGLES, 6, 12);
//        glDrawArrays(GL_TRIANGLES, 6, 3);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glPopMatrix();
    }//..
};

#endif //SQUARE_H
