// rotating cube with two texture objects
// change textures with 1 and 2 keys

#include "Angel.h"
#include "mesh.h"
#include "FreeImage.h"
#include "Mesh_Painter.h"
#include <mmsystem.h>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "FreeImage.lib")

int mainWindow;

const double DELTA_DELTA = 0.01;
const double DEFAULT_DELTA = 0.1;

vec3 scaleTheta(1.0, 1.0, 1.0);
vec3 rotateTheta(0.0, 0.0, 0.0);
vec3 translateTheta(0.0, 0.0, 0.0);
vec3 robotscaleTheta(1.0, 1.0, 1.0);
vec3 robotrotateTheta(0.0, 0.0, 0.0);
vec3 robottranslateTheta(0.0, 0.0, 0.0);
vec3 Rotateangle(0, 0, 0);

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

//----------------------------------------------------------------------------

std::vector<My_Mesh*> my_meshs;
Mesh_Painter* mp_;
Mesh_Painter* mp_1;
Mesh_Painter* mp_2;
Mesh_Painter* mp_3;

vec3 lightPos(30, 40, 100);

int direction;
float rotationAngle = 35.0;
float x, y, z;
float moveleft_right = 0;
float movefront_back = 0;
float footballleft_right = 0;
float footballfront_back = 0;
vec4 eye = vec4(0.1, 0, 0.09);
vec4 at = vec4(0, 0, 0, 0);
vec4 up = vec4(0, 1, 0, 0);
//更改视点位置的参数

point4 color_torso = point4(0, 0, 1, 1);
point4 color_head = point4(0, 0, 0, 1);
point4 color_up = point4(0, 1, 0, 1);
point4 color_low = point4(1, 0, 0, 1);

// Set up menu item indices, which we can alos use with the joint angles
enum {
	left_right,
	front_back,
	Quit
};

GLint angle = front_back;

void
init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);//设置背景颜色为灰色
	mp_ = new Mesh_Painter;
	mp_1 = new Mesh_Painter;
	mp_2 = new Mesh_Painter;

	My_Mesh* my_mesh1 = new My_Mesh;
	my_mesh1->load_obj("texture/footballplane.obj");
	my_mesh1->set_texture_file("texture/footballplane.jpg");
	my_meshs.push_back(my_mesh1);
	mp_->add_mesh(my_mesh1);
	My_Mesh* my_mesh2 = new My_Mesh;
	my_mesh2->load_obj("texture/skybox.obj");
	my_mesh2->set_texture_file("texture/skybox.jpg");
	my_meshs.push_back(my_mesh2);
	mp_->add_mesh(my_mesh2);

	My_Mesh* my_mesh3 = new My_Mesh;
	my_mesh3->load_obj("texture/football.obj");
	my_mesh3->set_texture_file("texture/football.jpg");
	my_meshs.push_back(my_mesh3);
	mp_1->add_mesh(my_mesh3);

	My_Mesh* my_mesh4 = new My_Mesh;
	my_mesh4->load_obj("texture/head.obj");
	my_mesh4->set_texture_file("texture/head.jpg");
	my_meshs.push_back(my_mesh4);
	mp_2->add_mesh(my_mesh4);
	My_Mesh* my_mesh5 = new My_Mesh;
	my_mesh5->load_obj("texture/body.obj");
	my_mesh5->set_texture_file("texture/body.jpg");
	my_meshs.push_back(my_mesh5);
	mp_2->add_mesh(my_mesh5);
	My_Mesh* my_mesh6 = new My_Mesh;
	my_mesh6->load_obj("texture/leftarm.obj");
	my_mesh6->set_texture_file("texture/arm.jpg");
	my_meshs.push_back(my_mesh6);
	mp_2->add_mesh(my_mesh6);
	My_Mesh* my_mesh7 = new My_Mesh;
	my_mesh7->load_obj("texture/rightarm.obj");
	my_mesh7->set_texture_file("texture/arm.jpg");
	my_meshs.push_back(my_mesh7);
	mp_2->add_mesh(my_mesh7);
	My_Mesh* my_mesh8 = new My_Mesh;
	my_mesh8->load_obj("texture/leftleg.obj");
	my_mesh8->set_texture_file("texture/arm.jpg");
	my_meshs.push_back(my_mesh8);
	mp_2->add_mesh(my_mesh8);
	My_Mesh* my_mesh9 = new My_Mesh;
	my_mesh9->load_obj("texture/rightleg.obj");
	my_mesh9->set_texture_file("texture/arm.jpg");
	my_meshs.push_back(my_mesh9);
	mp_2->add_mesh(my_mesh9);

	mp_->init_shaders("v_texture.glsl", "f_texture.glsl");
	mp_->update_vertex_buffer();
	mp_->update_texture();
	mp_1->init_shaders("vshader.glsl", "fshader.glsl");
	mp_1->update_vertex_buffer();
	mp_1->update_texture();
	mp_2->init_shaders("vshader82.glsl", "fshader82.glsl");
	mp_2->update_vertex_buffer();
	mp_2->update_texture();

	// OpenGL相应状态设置
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LESS);
}

void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	mp_->return_mesh(0)->set_scale(vec3(1,1,1));
	mp_->return_mesh(0)->set_rotate(vec3(0,0,0));
	mp_->return_mesh(0)->set_translate(vec3(0, 0, -3));
	mp_->return_mesh(1)->set_scale(vec3(1.1,1.1,1.1));
	mp_->return_mesh(1)->set_rotate(vec3(0, 0, 0));
	mp_->return_mesh(1)->set_translate(vec3(0, 0, -3));

	mp_1->return_mesh(0)->set_scale(vec3(0.2,0.2,0.2));
	mp_1->return_mesh(0)->set_rotate(vec3(0, 0, 0));
	mp_1->return_mesh(0)->set_trans(footballleft_right, footballfront_back, 0);

	mp_2->return_mesh(0)->set_trans(moveleft_right, movefront_back, 0);
	mp_2->return_mesh(1)->set_trans(moveleft_right, movefront_back, 0);
	mp_2->return_mesh(2)->set_trans(moveleft_right, movefront_back, 0);
	mp_2->return_mesh(3)->set_trans(moveleft_right, movefront_back, 0);
	mp_2->return_mesh(4)->set_trans(moveleft_right, movefront_back, 0);
	mp_2->return_mesh(5)->set_trans(moveleft_right, movefront_back, 0);
	mp_2->seteye(eye);
	mp_2->setat(at);
	mp_2->setup(up);
	mp_2->trans = robottranslateTheta;
	mp_2->rotate = robotrotateTheta;
	mp_2->scale = robotscaleTheta;
	mp_2->rotateangle = Rotateangle;
	mp_2->kick = x;
	
	mp_2->draw_robot();
	mp_->seteye(eye);
	mp_->setat(at);
	mp_->setup(up);
	mp_->draw_meshes();
	mp_1->setLightPos(lightPos);
	mp_1->setRotationAngle(rotationAngle);
	mp_1->seteye(eye);
	mp_1->setat(at);
	mp_1->setup(up);
	mp_1->draw_meshes();
	
	glutSwapBuffers();
};
//////////////////////////////////////////////////////////////////////////
// 重新设置窗口

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void
idle(void)
{
	glutPostRedisplay();
}
void idlefunction()
{
	if (direction == 0) {
		footballfront_back += 0.1;
	}
	else if (direction == 1) {
		footballleft_right += 0.1;
	}
	else if (direction == 2) {
		footballfront_back -= 0.1;
	}
	else if (direction == 3) {
		footballleft_right -= 0.1;
	}
	if (footballfront_back >= 3) {
		glutIdleFunc(NULL);
	}
	if (footballfront_back <= -3) {
		glutIdleFunc(NULL);
	}
	if (footballleft_right >= 3) {
		glutIdleFunc(NULL);
	}
	if (footballleft_right <= -3) {
		glutIdleFunc(NULL);
	}
	glutPostWindowRedisplay(mainWindow);
}
void idleFunction()
{
	x += 0.1;
	if (x >= 30) { 
		x = 0;
		glutIdleFunc(idlefunction);
	}
	glutPostWindowRedisplay(mainWindow);
}
//----------------------------------------------------------------------------
void
mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& angle==left_right) {
		direction = 1;
		glutIdleFunc(idleFunction);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN&& angle == left_right) {
		direction = 3;
		glutIdleFunc(idleFunction);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& angle == front_back) {
		direction = 0;
		glutIdleFunc(idleFunction);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN&& angle == front_back) {
		direction = 2;
		glutIdleFunc(idleFunction);
	}
	glutPostRedisplay();
}
void
keyboard( unsigned char key, int mousex, int mousey )
{
	switch (key) {
	case 'r':
		eye.x += 1* DELTA_DELTA;
		break;
	case 'f':
		eye.x -=1 * DELTA_DELTA;
		break;
	case 't':
		eye.y += 1 * DELTA_DELTA;
		break;
	case 'g':
		eye.y -= 1 * DELTA_DELTA;
		break;
	case 'y':
		eye.z += 1 * DELTA_DELTA;
		break;
	case 'h':
		eye.z -= 1 * DELTA_DELTA;
		break;
	case 'q':
		Rotateangle.y += 90;
		break;
	case 'e':
		Rotateangle.y -= 90;
		break;
	case 'a':
		moveleft_right -= 0.1 * DEFAULT_DELTA;
		robotrotateTheta.z += 1;
		if (robotrotateTheta.z >= 20.0)
			robotrotateTheta.z = 0;
		break;
	case 'd':
		moveleft_right += 0.1 * DEFAULT_DELTA;
		robotrotateTheta.z += 1;
		if (robotrotateTheta.z >= 20.0)
			robotrotateTheta.z = 0;
		break;
	case 'w':
		movefront_back += 0.1 * DEFAULT_DELTA;
		robotrotateTheta.z += 1;
		if (robotrotateTheta.z >= 20.0)
			robotrotateTheta.z = 0;
		break;
	case 's':
		movefront_back -= 0.1 * DEFAULT_DELTA;
		robotrotateTheta.z += 1;
		if (robotrotateTheta.z >= 20.0)
			robotrotateTheta.z = 0;
		break;

	}
    glutPostRedisplay();
}
void clean()
{
	for (unsigned int i = 0; i < my_meshs.size(); i++)
	{
		delete my_meshs[i];
	}
	delete mp_;
}
//----------------------------------------------------------------------------
void
menu(int option)
{
	if (option == Quit) {
		exit(EXIT_SUCCESS);
	}
	angle = option;
}

	
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // 窗口支持双重缓冲和深度测试
    glutInitWindowSize( 560,  720);
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
	mainWindow=glutCreateWindow( "2016154091_陈超钦" );
	glewExperimental = GL_TRUE;
    glewInit();

    init();
    glutDisplayFunc( display );
	glutReshapeFunc(reshape);
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );
    glutIdleFunc( idle );

	glutCreateMenu(menu);
	glutAddMenuEntry("left_right", left_right);
	glutAddMenuEntry("front_back", front_back);
	glutAddMenuEntry("quit", Quit);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glEnable(GL_DEPTH_TEST);// 启用深度测试
    glutMainLoop();

	clean();

    return 0;
}
