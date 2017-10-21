#include <iostream>

#define GLEW_STATIC
#include <glew.h>
#include <GLFW/glfw3.h>

const GLint width = 800, height = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main(){

    glfwInit();
    
    // Try to set the OpenGL version to 3.3 if the GPU supports it.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Needed for MAC.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow * window = glfwCreateWindow(width, height, "Learn Open Gl", nullptr, nullptr);
    
    int screenWidth, screnHeight;
    
    // Needed to deal with Retina Display.
    glfwGetFramebufferSize(window, &screenWidth, &screnHeight);
    
    if ( nullptr == window ){
        printf("Failed to create window. \n");
        glfwTerminate();
        return  -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // This is not exactly experimental...
    glewExperimental = GL_TRUE;
    
    if ( GLEW_OK != glewInit()){
        printf("Failed to Init GLEW. \n");
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screnHeight);
    
    
    // Build and compile our shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader( vertexShader );
    
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Fragment shader
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader );
    
    // Check for compile time errors
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    
    if ( !success )
    {
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Link shaders
    GLuint shaderProgram = glCreateProgram( );
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );
    
    // Check for linking errors
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    
    if ( !success )
    {
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
    
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f, // Left
        0.5f, -0.5f, 0.0f, // Right
        0.0f,  0.5f, 0.0f  // Top
    };
    
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray( 0 ); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
    
    
    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
        
        // Clear the color Buffer.
        
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Traingle Draw Call
        
        // Draw our first triangle
        glUseProgram( shaderProgram );
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );
        
        glfwSwapBuffers(window);
        
    }
    
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    
    glfwTerminate();
    
    return EXIT_SUCCESS;

}

