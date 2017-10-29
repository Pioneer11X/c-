//
//  GL_Game.h
//  Engine
//
//  Created by Sravan Karuturi on 10/24/17.
//


#ifndef GL_Game_h
#define GL_Game_h

#include "GenericGame.h"

#include <vector>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

// GLFW
#include <GLFW/glfw3.h>

#include "Entity.h"

class GL_Game : public  GenericGame {
    
    GLFWwindow * window;

	std::vector<GL_Mesh *> meshes;

	void CreateMeshes();
    
    void Draw();

	void processInput(GLFWwindow *window);

	int joyStickNumber;
    
public:

	GLuint WIDTH, HEIGHT;

	GL_Shader playerShader;
	GL_Shader blockShader;

	GL_Mesh * playerMesh;
	GL_Mesh * blockMesh;

	Entity * playerEntity;
	std::vector<Entity * > platformEntites;
    
    GL_Game();
    
    bool Init();
    
    void Update();
    
    void Cleanup();
    
    void handleUserEvents();
    
    ~GL_Game() { };
    
};

#endif /* GL_Game_h */
