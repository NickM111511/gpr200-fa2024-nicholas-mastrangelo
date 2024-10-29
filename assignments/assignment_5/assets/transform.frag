#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2; // for new textures

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1); // currently alpha is one because I don't want to blend right now
	// FragColor = (texture(texture1,TexCoord)); // one texture only
}