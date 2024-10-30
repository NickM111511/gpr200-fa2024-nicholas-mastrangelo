#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() 
{
	// this part is for ambience
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// this part is for diffusion
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// this part is for specular
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectDirection = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  

	// adding them up to give the final lighting color
	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
} 