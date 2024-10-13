#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
	vec4 color1 = texture(texture2, TexCoord);
    vec4 color2 = texture(texture3, TexCoord);
    FragColor = mix(texture(texture2, TexCoord), texture(texture3, TexCoord), 0.3); // non rainbow , mixing background
    // FragColor = mix(color1, color2, 0.2) * vec4(ourColor, 1.0); //rainbow layering
}
