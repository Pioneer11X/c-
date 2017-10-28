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
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    BasicVertex bVertices[] =
    {
        // Positions         // Colors
        BasicVertex(0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f),  // Bottom Right
        BasicVertex(-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f),  // Bottom Left
        BasicVertex(-0.5f,  0.5f, 0.0f,   0.5f, 0.0f, 1.0f),   // Top Left
        BasicVertex(0.5f,  0.5f, 0.0f,   0.0f, 0.5f, 1.0f)   // Top Right
    };

	
    
    uint32_t indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
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
    
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(bVertices), bVertices, GL_STATIC_DRAW );
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    // Color attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );
    
    glBindVertexArray( 0 ); // Unbind VAO
    

    
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
		glBindVertexArray(VAO);

		// glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
    
}

void GL_Game::Draw(){
    
}

void GL_Game::handleUserEvents(){
    
}

void GL_Game::Cleanup(){
    
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    glDeleteBuffers( 1, &EBO );


    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    
    //    return EXIT_SUCCESS;
    
}
