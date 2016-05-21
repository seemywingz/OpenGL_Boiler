
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Square.h"

// Window controls
GLFWwindow * window;
bool fullScreen = false;

// Objects
Square * square;

// Function Declarations
void keyHandler();
void draw();

void keyHandler(){
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}//..

void draw(){
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    square->draw();

    glfwSwapBuffers(window);
}//..

int main(){

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  if(!fullScreen)
   window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
  else
    window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

  if (!window) {
   fprintf (stderr, "ERROR: could not open window with GLFW3\n");
   glfwTerminate();
   return 1;
  }

  glfwMakeContextCurrent(window);
  ckGLError("GLFW context");

  glewExperimental = GL_TRUE;
  glewInit();
  ckGLError("init GLEW");

//  tell GL to only draw onto a pixel if the shape is closer to the viewer
//  glEnable (GL_DEPTH_TEST); // enable depth-testing
//  glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

  square = new Square();

  while(!glfwWindowShouldClose(window)){
    keyHandler();
    draw();
  }

  glfwTerminate();
  return 0;
}//..