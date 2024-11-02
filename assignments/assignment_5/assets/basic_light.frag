#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TextCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform sampler2D texture1;
uniform bool blinn = true;

uniform float ambientStrength;
// uniform float diff = max(dot(norm, lightDir), 0.0);
uniform float u_diffuse;
uniform float u_specular; 
uniform float shininess;

void main() 
{
	//for the texture coordinates
	vec3 objectColor = texture(texture1, TextCoords).rgb;

	// this part is for ambience
	vec3 ambient = ambientStrength * lightColor;

	// this part is for diffusion
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	float diff = max(dot(norm, lightDir), u_diffuse);
	vec3 diffuse = diff * lightColor;

	// this part is for specular
	vec3 viewDirection = normalize(viewPos - FragPos);
	float spec = 1.0f;
	// blinn phong part
	if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDirection);  
        spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    }
    else
    {
       vec3 reflectDirection = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
    }
	vec3 specular = vec3(u_specular) * spec; 
	
	
	// adding them up to give the final lighting color
	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
} 