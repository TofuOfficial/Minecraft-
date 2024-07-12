#version 330 core
layout(location = 0) out vec4 FragColor;

uniform vec4 triColor;

void main()
{
    FragColor = triColor;
    // FragColor = texture(ourTexture, TexCoord);
}