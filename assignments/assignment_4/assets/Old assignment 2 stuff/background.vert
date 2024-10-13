#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float uTime;

void main()
{
    gl_Position = vec4(aPos * 2, 1.0);
    ourColor = aColor;
    TexCoord = 7 * aTexCoord; // to do the fracting, multiply
    TexCoord.x += sin(uTime); // make the animation here
    TexCoord.y += sin(15 * aTexCoord.x);
}