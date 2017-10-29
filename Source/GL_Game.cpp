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
    ourShader = Shader();

	window = nullptr;

    Init();

}

bool GL_Game::Init(){
    
    //// Set up vertex data (and buffer(s)) and attribute pointers
    BasicVertex bVertices[] =
    {
        // Positions         // Colors
        BasicVertex(0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f),  // Bottom Right
        BasicVertex(-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f), // Bottom Left
        BasicVertex(-0.5f,  0.5f, 0.0f,   0.5f, 0.0f, 1.0f), // Top Left
        BasicVertex(0.5f,  0.5f, 0.0f,   0.0f, 0.5f, 1.0f)   // Top Right
    };

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
    
    ourShader.Init("Shaders/core.vs", "Shaders/core.frag" );

	std::vector<BasicVertex> vertices;
	vertices.push_back(bVertices[0]);
	vertices.push_back(bVertices[1]);
	vertices.push_back(bVertices[2]);
	vertices.push_back(bVertices[3]);

	std::vector<uint32_t> bindices = { 0 , 1, 3, 1, 2, 3 };

	GL_Mesh * mesh = new GL_Mesh(vertices, bindices);
	meshes.push_back(mesh);

	entity = new Entity(meshes, vec3(0.3f, 0.2f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.2f, 1.0f, 1.0f));
   
    return EXIT_SUCCESS;
    
}

void GL_Game::Update(){
    
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		ourShader.Use();

		//entity->RotateZ(1.0f);

		entity->GLDraw(ourShader);

		//entity->MoveRight(1.0f);

		// Swap the screen buffers
		glfwSwapBuffers(window);

		processInput(window);
	}
    
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

		entity->MoveRight(axes[0]);

		int buttonCount;
		const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		//for (int i = 0; i < buttonCount; i++) {

		//	if (GLFW_PRESS == buttons[i]) {
		//		std::cout << "Button " << i << " : Pressed" << std::endl;
		//	}

		//}

		// Press B to Close the Application for Now.
		if (GLFW_PRESS == buttons[1]) {
			glfwSetWindowShouldClose(window, true);
		}

	}
	
}

void GL_Game::handleUserEvents(){
    
}

void GL_Game::Cleanup(){

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

	delete entity;

	for (std::vector<GL_Mesh *>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		delete (*it);
	}
    
    //    return EXIT_SUCCESS;
    
}