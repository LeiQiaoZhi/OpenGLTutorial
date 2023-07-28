#version 330 core

out vec4 FragColor;

in vec3 color; // the input variable from the vertex shader (same name and same type)
in vec2 texCoord;
in vec3 normal;
in vec3 pos; // world pos of the frag

uniform sampler2D tex0; // texture from texture unit 0
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.2f;
	// diffuse
	vec3 n = normalize(normal);
	vec3 posToLight = normalize(lightPos - pos);
	float diffuse = max(dot(posToLight, n), 0.0f);

	// specular
	float specularAmount = 0.5f;
	vec3 posToCam = normalize(camPos - pos);
	vec3 reflectPosToLight = reflect(-posToLight, n);
	float specular = pow(max(dot(reflectPosToLight, n), 0.0f),8) * specularAmount;

	FragColor = texture(tex0, texCoord) * lightColor * (ambient + diffuse + specular);
}
