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
