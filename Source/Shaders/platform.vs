#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;

uniform mat4 transform;
uniform mat4 view; // Camera

out vec3 ourColor;

void main()
{
    gl_Position = view * transform * vec4(position, 1.0f);
	// gl_Position = vec4(position, 1.0f);
    ourColor = color;
}
