//
//  GL_Game.h
//  Engine
//
//  Created by Sravan Karuturi on 10/24/17.
//


#ifndef GL_Game_h
#define GL_Game_h

#include "GenericGame.h"
#include "Entity.h"
#include <vector>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

// GLFW
#include <GLFW/glfw3.h>

class GL_Game : public  GenericGame {
    
    GLuint WIDTH, HEIGHT;
    
    GLFWwindow * window;
    
	GL_Shader playerShader;
	GL_Shader blockShader;

	GL_Mesh * playerMesh;
	GL_Mesh * blockMesh;

	std::vector<GL_Mesh *> meshes;

	Entity * playerEntity;
	std::vector<Entity * > platformEntites;

	void CreateMeshes();
    
    void Draw();

	void processInput(GLFWwindow *window);

	int joyStickNumber;
    
public:
    
    GL_Game();
    
    bool Init();
    
    void Update();
    
    void Cleanup();
    
    void handleUserEvents();
    
    ~GL_Game() { };
    
};

#endif /* GL_Game_h */
