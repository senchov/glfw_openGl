//
//  main.cpp
//  SimpleOpenGl
//
//  Created by Андрей Сеньчов on 3/10/17.
//  Copyright © 2017 Андрей Сеньчов. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL2/SOIL2.h"

#include "Shader.hpp"


const GLuint WIDTH = 512, HEIGHT = 512;

int main(int argc, const char * argv[]) {
    
    glfwInit();
    
   glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint (GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint (GLFW_RESIZABLE,GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LeardOpenGL", nullptr, nullptr);
    int screenWidth,screenHeight;
    
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed init GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
   /* GLuint vertexShader = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader (vertexShader);
    
    GLint succes;
    GLchar infoLog[512];
    
    glGetShaderiv (vertexShader, GL_COMPILE_STATUS, &succes);
    
    if (!succes)
    {
        glGetShaderInfoLog (vertexShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog <<std::endl;
    }
    
    GLuint fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader (fragmentShader);
    
    glGetShaderiv (fragmentShader, GL_COMPILE_STATUS,&succes);
    
    if (!succes)
    {
        glGetShaderInfoLog (fragmentShader,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<infoLog <<std::endl;
    }
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader (shaderProgram, vertexShader);
    glAttachShader (shaderProgram,fragmentShader);
    glLinkProgram (shaderProgram);
    
    glGetProgramiv (shaderProgram,GL_LINK_STATUS,&succes);
    
    
    if (!succes)
    {
        glGetProgramInfoLog (shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<infoLog <<std::endl;
    }
    
    glDeleteShader (vertexShader);
    glDeleteShader (fragmentShader);*/
    Shader ourShader ("resources/shader/core.vs","resources/shader/core.frag");
    
    GLfloat vertices[] =
    {
        //position                  //color                 // texture coordinates
        0.5f, 0.5f, 0.0,              1.0f,0.0f,0.0f,        0.0f,0.0f, //0
        0.5f, -0.5f, 0.0,             1.0f,1.0f,1.0f,        0.0f,1.0f, //1
        -0.5f,-0.5f, 0.0,             1.0f,0.0f,0.0f,        1.0f,1.0f, //2
        -0.5f,0.5f, 0.0,              1.0f,0.0f,1.0f,        1.0f,0.0f  //3
    };
    
    GLuint indices[] =
    {
        0,1,3,  // first triangle
        1,2,3   // second
    };
    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays (1, &VAO);
    glGenBuffers (1, &VBO);
    glGenBuffers (1, &EBO);
    
    glBindVertexArray (VAO);
    glBindBuffer (GL_ARRAY_BUFFER,VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer (0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray (0);
    
    //color atribute
    glVertexAttribPointer (1,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid *)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray (1);
    // texture coordinates attribute
    glVertexAttribPointer (2,2,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid *)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray (2);
    
    glBindBuffer (GL_ARRAY_BUFFER,0);
    glBindVertexArray (0);
    
    GLuint texture;
    
    int width,height;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    unsigned char *image = SOIL_load_image("resources/images/image_1.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap (GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
       // glUseProgram (shaderProgram);
        ourShader.Use();
        
        glActiveTexture (GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i (glGetUniformLocation (ourShader.Program, "ourTexture"),0);
        
        
        glBindVertexArray (VAO);
       // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);
        
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1,&VBO);
    glDeleteBuffers (1,&EBO);
    
    glfwTerminate();
    return EXIT_SUCCESS;
}
