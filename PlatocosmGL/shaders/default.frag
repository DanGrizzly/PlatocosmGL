#version 330 core

//in vec2 texCoord;
//uniform sampler2D tex0;

out vec4 FragColor;
float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

in vec3 viewPosition;
in vec3 objectposition;


uniform float planetScale;
uniform vec3 planetColor;

// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

vec4 pointLight()
{	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.01;
	float b = 0.7;
	float inten = min(1.0f, max(1.0f / (a * dist * dist), 0.05f));

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	//return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
	return ((diffuse * inten)) * vec4(color, 1.0f) * lightColor;
}

vec4 flatPointLight()
{	
    vec3 xTangent = dFdx( viewPosition );
    vec3 yTangent = dFdy( viewPosition );
    vec3 faceNormal = normalize( cross( xTangent, yTangent ) );
	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.01;
	float b = 0.7;
	float inten = min(1.0f, max(1.0f / (a * dist * dist), 0.05f));

	// diffuse lighting
	vec3 normal = normalize(faceNormal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	return (diffuse * inten) * vec4(color, 1.0f) * lightColor;
}

void main()
{
   //FragColor = lightColor*vec4(color, 1.0f);
   //float lowerbound = 0.98f * planetScale;
   float tolerance = 0.019f * planetScale;


   //float ground = (distance(viewPosition, objectposition)-lowerbound)/0.04f;
   //float ocean = 1.0f - (distance(viewPosition, objectposition)-lowerbound)/0.04f;
   //bool booly = bool(int(distance(viewPosition, objectposition)));
   //vec3 thecolor = booly ? vec3(1.0f, 0.0f, 0.0f) : vec3(0.0f, 0.0f, 1.0f);

   bool booly1 = bool(int( (distance(viewPosition, objectposition) + tolerance) / planetScale ));
   bool booly2 = bool(int( (distance(viewPosition, objectposition) - tolerance) / planetScale ));

   vec3 lowercolor = booly1 ? vec3(1.0f, 1.0f*236/255, 1.0f*188/255) : vec3(0.0f, 0.0f, 1.0f);
   vec3 highercolor = booly2 ? planetColor : lowercolor;
   //FragColor = vec4(ground, ground/2, ocean, 1.0f) * pointLight();
   FragColor = vec4(highercolor, 1.0f) * flatPointLight();
}