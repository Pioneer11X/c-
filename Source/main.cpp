#include <iostream>
#include <stdio.h>

#include "GL_Game.h"

// The MAIN function, from here we start the application and run the game loop
int main( )
{
//    // Init GLFW
//    glfwInit( );
//
//    // Set all the required options for GLFW
//    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
//    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
//    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
//    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
//
//    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
//
//    // Create a GLFWwindow object that we can use for GLFW's functions
//    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Engine", nullptr, nullptr );
//
//    int screenWidth, screenHeight;
//    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
//
//    if ( nullptr == window )
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate( );
//
//        return EXIT_FAILURE;
//    }
//
//    glfwMakeContextCurrent( window );
//
//    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
//    glewExperimental = GL_TRUE;
//    // Initialize GLEW to setup the OpenGL Function pointers
//    if ( GLEW_OK != glewInit( ) )
//    {
//        std::cout << "Failed to initialize GLEW" << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    // Define the viewport dimensions
//    glViewport( 0, 0, screenWidth, screenHeight );
//
//    // Build and compile our shader program
//    Shader ourShader;
//    ourShader.Init( "Shaders/core.vs", "Shaders/core.frag" );
//
//
//    // Set up vertex data (and buffer(s)) and attribute pointers
//    GLfloat vertices[] =
//    {
//        // Positions         // Colors
//        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
//        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
//        -0.5f,  0.5f, 0.0f,   0.5f, 0.0f, 1.0f,   // Top Left
//        0.5f,  0.5f, 0.0f,   0.0f, 0.5f, 1.0f   // Top Right
//    };
//
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,  // first Triangle
//        1, 2, 3   // second Triangle
//    };
//
//    GLuint VBO, VAO, EBO;
//    glGenVertexArrays( 1, &VAO );
//    glGenBuffers( 1, &VBO );
//    glGenBuffers(1, &EBO);
//    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    glBindVertexArray( VAO );
//
//    glBindBuffer( GL_ARRAY_BUFFER, VBO );
//    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//    // Position attribute
//    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * ) 0 );
//    glEnableVertexAttribArray( 0 );
//    // Color attribute
//    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
//    glEnableVertexAttribArray( 1 );
//
//    glBindVertexArray( 0 ); // Unbind VAO
//
//    // Game loop
//    while ( !glfwWindowShouldClose( window ) )
//    {
//        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
//        glfwPollEvents( );
//
//        // Render
//        // Clear the colorbuffer
//        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
//        glClear( GL_COLOR_BUFFER_BIT );
//
//        // Draw the triangle
//        ourShader.Use( );
//        glBindVertexArray( VAO );
//
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        glBindVertexArray(0);
//
//        // Swap the screen buffers
//        glfwSwapBuffers( window );
//    }
//
//    // Properly de-allocate all resources once they've outlived their purpose
//    glDeleteVertexArrays( 1, &VAO );
//    glDeleteBuffers( 1, &VBO );
//
//    // Terminate GLFW, clearing any resources allocated by GLFW.
//    glfwTerminate( );
//
//    return EXIT_SUCCESS;
    
    GL_Game glGame;
    
    glGame.Init();
    
    glGame.Update();
    
    glGame.Cleanup();
    
    return EXIT_SUCCESS;
    
}




