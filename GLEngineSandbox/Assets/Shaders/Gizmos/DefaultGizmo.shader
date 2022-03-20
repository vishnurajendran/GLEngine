#shadertype vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

#shadertype fragment
#version 330 core
out vec4 FragColor;
uniform vec4 lineColor;

void main()
{
    FragColor = lineColor;
} 