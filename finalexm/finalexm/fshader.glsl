#version 330 core

in vec4 color;
in vec2 texCoord;
in vec4 normal;
in vec3 faceIndecies;

in vec3 N;
in vec3 V;
uniform vec3 lightPos;
uniform int isShadow;

out vec4 fColor;
out vec4 fNormal;

uniform sampler2D texture;

void main()
{
	// TODO ������ά����Ĳ�������
	vec3 ambiColor = vec3(0.5, 0.5, 0.5);
	vec3 diffColor = vec3(0.5, 0.5, 0.5);
	vec3 specColor = vec3(0.3, 0.3, 0.3);

	// TODO ����N��L��V��R�ĸ���������һ��
	vec3 N_norm = normalize(N);
	vec3 L_norm = normalize(lightPos - V);
	vec3 V_norm = normalize(-V);
	vec3 R_norm = reflect(L_norm, N_norm);

	// TODO ����������ϵ���;��淴��ϵ��
	float lambertian = clamp(dot(L_norm, N_norm), 0.0, 1.0);
	float specular = clamp(dot(R_norm, V_norm), 0.0, 1.0);
	
	float shininess = 10.0;

	// TODO ��������ÿ��ƬԪ�������ɫ
	if (isShadow == 1) 
	{
		fColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else 
	{ 
		//fColor = texture2D( texture, texCoord );
		//phong
		fColor = texture2D( texture, texCoord )*vec4(ambiColor + diffColor * lambertian + specColor * pow(specular, shininess), 1.0);

	}
    
    fNormal = normal;
}

