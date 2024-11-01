#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TextCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform bool blinn;

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
	vec3 viewDirection = normalize(viewPos - FragPos);
	float spec = 0.0f;
	// blinn phong part
	if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDirection);  
        spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    }
    else
    {
       vec3 reflectDirection = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 8.0);
    }
	vec3 specular = vec3(0.3) * spec; 
	
	// adding them up to give the final lighting color
	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
} 