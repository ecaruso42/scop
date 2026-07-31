#version 330 core

in vec3 vertexColor;
in vec3 Normal;

out vec4 FragColor;

uniform bool useLighting;

void main()
{
	if(useLighting)
	{
		vec3 lightDir = normalize(vec3(0.4, 0.6, 1.0));

		float diffuse = max(dot(normalize(Normal), lightDir), 0.0);
		float gray = 0.35 + diffuse * 0.45;

		FragColor = vec4(gray, gray, gray, 1.0);
	}
	else
	{
    	FragColor = vec4(vertexColor, 1.0);
	}
}