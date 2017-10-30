//
//  GL_Game.cpp
//  Engine
//
//  Created by Sravan Karuturi on 10/24/17.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include "GL_Game.h"


using namespace std;

GL_Game::GL_Game(){
    
    // Window dimensions
    WIDTH = 800;
    HEIGHT = 600;
    
    // Build and compile our shader program
	playerShader = GL_Shader();
	blockShader = GL_Shader();

	window = nullptr;

    Init();
    
    gameCamera = Camera(vec3(0.0f, 0.0f, 3.0f));


}

bool GL_Game::Init(){
   
    // Init calls for OpenGL.
    
    // Init GLFW
    glfwInit( );
    
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    if ( nullptr == window ){
        // Create a GLFWwindow object that we can use for GLFW's functions
        window = glfwCreateWindow( WIDTH, HEIGHT, "Engine", nullptr, nullptr );
    }
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, screenWidth, screenHeight );

	glDepthRangef(0.1f, 10.0f);
    
	playerShader.Init("../Source/Shaders/core.vs", "../Source/Shaders/core.frag" );
	blockShader.Init("../Source/Shaders/platform.vs", "../Source/Shaders/platform.frag");

	CreateMeshes();
   
    return EXIT_SUCCESS;
    
}

void GL_Game::Update(){
    
	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// gameCamera.ProcessKeyboard(Camera_Movement::BACKWARD, 0.1f);

		// Draw the triangle
		playerShader.Use();

		//entity->RotateZ(1.0f);

		playerEntity->GLDraw(playerShader, this->gameCamera);
		// std::cout << playerEntity->translation.x << " " << playerEntity->translation.y << std::endl;

		for (std::vector<Entity *>::iterator it = platformEntites.begin(); it != platformEntites.end(); it++) {
			(*it)->GLDraw(blockShader, this->gameCamera);
		}

		//entity->MoveRight(1.0f);

		// Swap the screen buffers
		glfwSwapBuffers(window);

		processInput(window);
	}
    
}

void GL_Game::CreateMeshes()
{

	// Setup Player Mesh
	BasicVertex playerVerts[] = {
		BasicVertex(0.2f, -0.25f, 0.0f,   1.0f, 0.2f, 0.2f),  // Bottom Right
		BasicVertex(0.0f, -0.25f, 0.0f,   1.0f, 0.2f, 0.2f), // Bottom Left
		BasicVertex(0.0f,  0.25f, 0.0f,   1.0f, 0.2f, 0.2f), // Top Left
		BasicVertex(0.2f,  0.25f, 0.0f,    1.0f, 0.2f, 0.2f)   // Top Right
	};

	//// Set up vertex data (and buffer(s)) and attribute pointers

	std::vector<BasicVertex> vertices;

	// For a Square.
	std::vector<uint32_t> bindices = { 0 , 1, 3, 1, 2, 3 };

	vertices.clear();
	for (int i = 0; i < sizeof(playerVerts) / sizeof(playerVerts[0]); i++) {
		vertices.push_back(playerVerts[i]);
	}

	playerMesh = new GL_Mesh(vertices, bindices);

	// Setup Platform Mesh
	BasicVertex platformVerts[] = {
		BasicVertex(0.2f, -0.2f, 0.0f,   1.0f, 0.5f, 0.2f),  // Bottom Right
		BasicVertex(0.0f, -0.2f, 0.0f,   1.0f, 0.5f, 0.2f), // Bottom Left
		BasicVertex(0.0f,  0.0f, 0.0f,   1.0f, 0.5f, 0.2f), // Top Left
		BasicVertex(0.2f,  0.0f, 0.0f,   1.0f, 0.5f, 0.2f)   // Top Right
	};

	vertices.clear();
	for (int i = 0; i < sizeof(platformVerts) / sizeof(platformVerts[0]); i++) {
		vertices.push_back(platformVerts[i]);
	}

	blockMesh = new GL_Mesh(vertices, bindices);

	// playerEntity = new Entity(meshes, vec3(0.3f, 0.2f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.2f, 1.0f, 1.0f));
	playerEntity = new Entity(playerMesh, vec3(0.3f, 0.2f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));

	Entity * e = new Entity(blockMesh, vec3(0.3f, -0.2f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));
	platformEntites.push_back(e);

}

void GL_Game::Draw(){
    
}

void GL_Game::processInput(GLFWwindow * window)
{
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	joyStickNumber = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// std::cout << joyStickNumber << std::endl;

	if (joyStickNumber != 0) {

		int axesCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

		playerEntity->MoveRight(axes[0]);
        
        int buttonCount;
        const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
        
#ifdef _WIN32
		playerEntity->MoveUp(axes[1]);
		
		if (axes[3] > 0.2f) {
			gameCamera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		}
		else if (axes[3] < -0.2f) {
			gameCamera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		}

		gameCamera.ProcessMouseMovement(axes[2] * 5.0f, 0, GL_FALSE);

        // Press B to Close the Application for Now.
        if (GLFW_PRESS == buttons[1]) {
            glfwSetWindowShouldClose(window, true);
        }
#endif
        
#ifdef __APPLE__
        playerEntity->MoveUp( -1.0f * axes[1]);
        // Press 'O' to Close the Application for Now.
        if (GLFW_PRESS == buttons[2]) {
            glfwSetWindowShouldClose(window, true);
        }
#endif




	}
	
}

void GL_Game::handleUserEvents(){
    
}

void GL_Game::Cleanup(){

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

	delete playerEntity;

	for (std::vector<Entity *>::iterator it = platformEntites.begin(); it != platformEntites.end(); it++) {
		delete (*it);
	}

	for (std::vector<GL_Mesh *>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		delete (*it);
	}

	if (playerMesh)
		delete playerMesh;

	if (blockMesh)
		delete blockMesh;
    
    //    return EXIT_SUCCESS;
    
}
