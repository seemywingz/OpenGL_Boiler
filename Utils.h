#ifndef UTILS_H


#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <thread>
#include <chrono>


//    void sleepMills(int mills){
//     	std::this_thread::sleep_for (std::chrono::milliseconds(mills));
//    }//..

//    class Logic{
//        public:
//          virtual ~Logic(){}
//          virtual void apply() = 0;
//    };
//
//    void applyLogic(Logic * logic){
//        try {
//            logic->apply();
//        }catch(...){
//            std::cout<<"BLAMO!: exception occured"<<std::endl;
//        }
//    }//..

//    void startThread(Logic * logic){
//        std::thread t(applyLogic,logic);
//        t.join();
//    }//..

    static void checkCompilation(GLuint shader,char const * type){
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if(status == GL_TRUE){
            printf("%s %s",type,"Shader Compiled Successfully\n");
        }
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        printf("%s",buffer);
    }//..

    static GLuint compileShader(GLint shaderType,const GLchar*shaderSource, char const* type){

        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        checkCompilation(shader,type);
        return shader;

    }//..

    static void ckGLError(const char* msg){
        int err = glGetError();
        printf("%s %s %d %s",msg,"GLError: ",err,"\n");
    }//..

#endif