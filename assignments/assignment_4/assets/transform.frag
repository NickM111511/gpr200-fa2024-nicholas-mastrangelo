#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2; // for new textures

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.8); // if i use more than one texture
	// FragColor = (texture(texture1,TexCoord)); // one texture only
}