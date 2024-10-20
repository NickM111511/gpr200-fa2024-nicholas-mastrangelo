#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	vec4 color = texture(texture1, TexCoord);
    FragColor = color, 0.5;
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.1); // non rainbow , mixing background
    // FragColor = mix(color1, color2, 0.2) * vec4(ourColor, 1.0); //rainbow layering
}
