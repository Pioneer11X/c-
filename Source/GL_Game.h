//
//  GL_Game.h
//  Engine
//
//  Created by Sravan Karuturi on 10/24/17.
//

#ifndef GL_Game_h
#define GL_Game_h

#include "GenericGame.h"

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"

class GL_Game : public  GenericGame {
    
    GLuint WIDTH, HEIGHT;
    
    GLuint VBO, VAO, EBO;
    
    GLFWwindow * window;
    
    Shader ourShader;
    
    void Draw();
    
public:
    
    GL_Game();
    
    bool Init();
    
    void Update();
    
    
    
    void Cleanup();
    
    void handleUserEvents();
    
    ~GL_Game() { };
    
};

#endif /* GL_Game_h */
