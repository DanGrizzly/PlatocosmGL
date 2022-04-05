#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;
out vec3 objectposition;

out vec3 viewPosition;

uniform float frame;

uniform mat4 camMatrix;
uniform mat4 model;

uniform vec3 objpos;

void main()
{
   crntPos = vec3(model*vec4(aPos, 1.0f));
   Normal = vec3(model*vec4(aNormal, 1.0f));
   color = aColor;
   texCoord = aTex;

   objectposition = objpos;
   
   //objectposition = vec3(model*vec4(objpos, 1.0f));

   viewPosition = (crntPos).xyz;

   //gl_Position = camMatrix * vec4(crntPos*(1+sin(frame)/20), 1.0);
   gl_Position = camMatrix * vec4(crntPos, 1.0);

   gl_PointSize = 10.0;
}