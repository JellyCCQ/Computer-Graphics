#version 330 core

in  vec3 vPosition;
in  vec3 vColor;
in  vec3 vNormal;
in  vec2 vTexCoord;
in  vec3 vFaceIndecies;


uniform mat4 modelViewProjMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 rotationMatrix;//添加旋转矩阵
uniform mat4 matrix;

out vec3 N;
out vec3 V;

out vec4 color;
out vec2 texCoord;
out vec4 normal;

uniform vec3 theta;
uniform vec3 translation;
uniform vec3 rotation;
uniform vec3 scaletion;

void main()
{
	vec4 v1 = modelViewProjMatrix * modelViewMatrix * vec4(vPosition, 1.0);
	vec4 v2 = vec4(v1.xyz / v1.w, 1.0);
	gl_Position = v2;
	gl_Position = gl_Position * matrix;

	// TODO 将顶点变换到相机坐标系下
	vec4 vertPos_cameraspace = modelViewMatrix * vec4(vPosition, 1.0);
	
	// 对顶点坐标做透视投影
	V = vertPos_cameraspace.xyz / vertPos_cameraspace.w;
	
	// TODO 将法向量变换到相机坐标系下并传入片元着色器
	N = (modelViewMatrix * vec4(vNormal, 0.0)).xyz;

    color       = vec4(vColor, 0);
    texCoord    = vTexCoord;
    normal = vec4(vNormal, 0);
}
