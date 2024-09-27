#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}

/*
#version 330 core
out vec4 FragColor;
in vec4 Color;
uniform float uTime = 1.0;
uniform vec4 uColor = vec4(1.0);
void main() 
{
   FragColor = Color * (sin(uTime) * 0.5 + 0.5);
}

*/