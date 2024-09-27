#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
uniform float uTime;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x * abs(sin(uTime)), aTexCoord.y* abs(sin(uTime)));
}
/*
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color; // Varying
uniform float uTime;
void main() 
{
   Color = aColor; //Pass-through
   vec3 pos = aPos;
   pos.y += abs(sin(uTime * 4 + 8)) / 3.0; // use "pos.x" for assignment 1, use "+ 8" for assignment 2.	
   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); 
}
*/