#version 150 

in  vec4 vPosition;
in  vec4 vColor;
in  vec3 vNormal;
in  vec2 vTexCoord;
in  vec3 vFaceIndecies;

out vec4 color;
out vec2 texCoord;
out vec4 normal;

uniform mat4 modelViewProjMatrix;
uniform mat4 modelViewMatrix;
uniform  vec4 draw_color;
uniform mat4 matrix;
uniform vec3 translation;
void main() 
{

    gl_Position =matrix* modelViewProjMatrix * modelViewMatrix * vPosition+vec4(translation, 1.0);

	color       = vColor;
    texCoord    = vTexCoord;
    normal = vec4(vNormal, 0);
} 
