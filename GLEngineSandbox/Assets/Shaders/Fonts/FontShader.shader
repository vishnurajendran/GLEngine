#shadertype vertex
#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texture;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(vertex.xy,0, 1.0f);
    TexCoords = texture;
}

#shadertype fragment
#version 330 core
varying vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text, TexCoords).r);
    color = vec4(textColor.rgb,1) * sampled;
} 