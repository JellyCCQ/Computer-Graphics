#pragma once
#include "mesh.h"
#include <stack>
//机器人身体比例
#define TORSO_HEIGHT 3.6
#define TORSO_WIDTH 1.6
#define UPPER_ARM_HEIGHT 1.8
#define LOWER_ARM_HEIGHT 2.1
#define UPPER_ARM_WIDTH  0.4
#define LOWER_ARM_WIDTH  0.3
#define UPPER_LEG_WIDTH  0.4
#define LOWER_LEG_WIDTH  0.3
#define LOWER_LEG_HEIGHT 2.4
#define UPPER_LEG_HEIGHT 1.8
#define HEAD_HEIGHT 1.2
#define HEAD_WIDTH 1
class Mesh_Painter
{
public:
	vec3 lightPos;
	float rotationAngle;
	vec4 eye;
	vec4 at;
	vec4 up;
	vec3 trans;
	vec3 scale;
	vec3 rotate;

	Mesh_Painter();
	~Mesh_Painter();

	void draw_robot();
	void draw_head();
	void draw_body();
	void draw_leftarm();
	void draw_rightarm();
	void draw_leftleg();
	void draw_rightleg();

	void draw_meshes();
	void update_vertex_buffer();
	void update_texture();

	void init_shaders(std::string vs, std::string fs);
	void add_mesh(My_Mesh*);
	void clear_mehs();
	My_Mesh* return_mesh(int i);

	void setLightPos(vec3 l);
	void setRotationAngle(float r);
	void seteye(vec4 e);
	void setat(vec4 a);
	void setup(vec4 u);
private:

	void load_texture_FreeImage(std::string file_name, GLuint& m_texName);

	std::vector<GLuint> textures_all;
	std::vector<GLuint> program_all;
	std::vector<GLuint> vao_all;
	std::vector<GLuint> buffer_all;
	std::vector<GLuint> vPosition_all;
	std::vector<GLuint> vColor_all;
	std::vector<GLuint> vTexCoord_all;
	std::vector<GLuint> vNormal_all;
	std::vector<GLuint>  theta_all;
	std::vector<GLuint>  trans_all;
	std::vector<GLuint>  rotate_all;
	std::vector<GLuint>  scale_all;
	std::vector<GLuint> matrixLocation_all;
	std::vector<GLuint> modelViewMatrix_all;
	std::vector<GLuint> modelViewProjMatrix_all;
	std::vector<GLuint> rotationMatrix_all;
	std::vector<GLuint> lightPos_all;
	std::vector<GLuint> shadow_all;

	std::vector<My_Mesh*> m_my_meshes_;
	std::stack<mat4> mvstack;
	mat4 model_view;
public:
	vec3 rotateangle;
	float kick;
};

