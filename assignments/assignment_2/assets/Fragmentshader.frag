#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 color1 = texture(texture1, TexCoord);
    vec4 color2 = texture(texture2, TexCoord);
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2); // non rainbow
    FragColor = mix(color1, color2, 0.2) * vec4(ourColor, 1.0); //rainbow layering
}
