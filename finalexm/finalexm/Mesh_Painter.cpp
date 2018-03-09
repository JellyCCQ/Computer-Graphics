#include "Mesh_Painter.h"
#include "FreeImage.h"

GLfloat left = -5, right = 5;
GLfloat bottom = -5.0, top = 5;
GLfloat zNear = -5, zFar = 5;

//////////////////////////////////////////////////////////////////////////
// �����������

namespace Camera
{
	mat4 modelMatrix(1.0);
	mat4 viewMatrix(1.0);
	//mat4 projMatrix= Ortho(-0.10,0.10,-0.10,0.10,-0.10,0.10);
	mat4 projMatrix(1.0);
}

Mesh_Painter::Mesh_Painter()
{
}


Mesh_Painter::~Mesh_Painter()
{
}


void Mesh_Painter::draw_robot()
{
	model_view ;//���ɱ任����
	draw_body();//���ɻ���
	mvstack.push(model_view);//�������ɱ任����
	model_view = RotateY(0)*model_view;
	draw_head();//ͷ������
	model_view = mvstack.top();//�ָ����ɱ任����
	mvstack.pop();

	mvstack.push(model_view); //�������ɱ任����
	model_view = RotateZ(rotate.z)*model_view;
	draw_leftarm(); //���ϱۻ���
	model_view = mvstack.top();//�ָ����ɱ任����
	mvstack.pop();

	mvstack.push(model_view); //�������ɱ任����
	model_view = RotateZ(-rotate.z)*model_view;
	draw_rightarm();//���ϱۻ���
	model_view = mvstack.top();//�ָ����ɱ任����
	mvstack.pop();

	mvstack.push(model_view); //�������ɱ任����
	model_view = RotateZ(-rotate.z)*model_view;
	draw_leftleg();//�����Ȼ���
	model_view = mvstack.top();//�ָ����ɱ任����
	mvstack.pop();

	mvstack.push(model_view); //�������ɱ任����
	model_view = RotateZ(rotate.z)*RotateZ(kick)*model_view;
	draw_rightleg();//�����Ȼ���
	model_view = mvstack.top();//�ָ����ɱ任����
	mvstack.pop();
}

void Mesh_Painter::draw_head()
{
	mvstack.push(model_view);//���游�ڵ����
	glUseProgram(this->program_all[0]);//ָ��ʹ����Ⱦ������ͬ��ģ�Ϳ���ָ����ͬ����Ⱦ������������ʹ�õ���Ⱦ��������ͬ���ļ���ѧ�����Ը����Լ��İ��öԲ�ͬ��ģ���趨��ͬ����Ⱦ��
	glBindVertexArray(this->vao_all[0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures_all[0]);//�������룬����ֻʹ��ͬһ��������л���
	float x, y, z;
	this->m_my_meshes_[0]->get_trans(x, y, z);
	GLfloat  vTranslation[3] = { x, y, z };
	glUniform3fv(trans_all[0], 1, vTranslation);
	mat4 m;
	m = m*Translate(0, -0.05, 0)*RotateX(rotateangle.x)*RotateY(rotateangle.y)*RotateZ(rotateangle.z)*Scale(1, 1, 1);
	mat4 viewMatrix(1.0);
	mat4 modelViewMatrix = viewMatrix *model_view;
	mat4 projMatrix = Ortho(left, right, bottom, top, zNear, zFar);
	projMatrix = projMatrix*modelViewMatrix;

	glUniformMatrix4fv(matrixLocation_all[0], 1, GL_TRUE, m);//����������ͼ��ı仯
	glUniformMatrix4fv(modelViewMatrix_all[0], 1, GL_TRUE, modelViewMatrix);
	glUniformMatrix4fv(modelViewProjMatrix_all[0], 1, GL_TRUE, projMatrix);
	glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[0]->num_faces() * 3);
	model_view = mvstack.top();//�ָ����ڵ����
	mvstack.pop();
}

void Mesh_Painter::draw_body()
{
	mvstack.push(model_view);//���游�ڵ����
	glUseProgram(this->program_all[1]);//ָ��ʹ����Ⱦ������ͬ��ģ�Ϳ���ָ����ͬ����Ⱦ������������ʹ�õ���Ⱦ��������ͬ���ļ���ѧ�����Ը����Լ��İ��öԲ�ͬ��ģ���趨��ͬ����Ⱦ��
	glBindVertexArray(this->vao_all[1]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures_all[1]);//�������룬����ֻʹ��ͬһ��������л���
	float x, y, z;
	this->m_my_meshes_[1]->get_trans(x, y, z);
	GLfloat  vTranslation[3] = { x, y, z };
	glUniform3fv(trans_all[1], 1, vTranslation);
	mat4 m;
	m = m*Translate(0, 0, 0)*RotateX(rotateangle.x)*RotateY(rotateangle.y)*RotateZ(rotateangle.z)*Scale(1.8, 1.8, 1.8);
	mat4 viewMatrix(1.0);
	mat4 modelViewMatrix = viewMatrix *model_view;
	mat4 projMatrix = Ortho(left, right, bottom, top, zNear, zFar);
	projMatrix = projMatrix*modelViewMatrix;

	glUniformMatrix4fv(matrixLocation_all[1], 1, GL_TRUE, m);//����������ͼ��ı仯
	glUniformMatrix4fv(modelViewMatrix_all[1], 1, GL_TRUE, modelViewMatrix);
	glUniformMatrix4fv(modelViewProjMatrix_all[1], 1, GL_TRUE, projMatrix);
	glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[1]->num_faces() * 3);
	model_view = mvstack.top();//�ָ����ڵ����
	mvstack.pop();
}

void Mesh_Painter::draw_leftarm()
{
	mvstack.push(model_view);//���游�ڵ����
	glUseProgram(this->program_all[2]);//ָ��ʹ����Ⱦ������ͬ��ģ�Ϳ���ָ����ͬ����Ⱦ������������ʹ�õ���Ⱦ��������ͬ���ļ���ѧ�����Ը����Լ��İ��öԲ�ͬ��ģ���趨��ͬ����Ⱦ��
	glBindVertexArray(this->vao_all[2]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures_all[2]);//�������룬����ֻʹ��ͬһ��������л���
	float x, y, z;
	this->m_my_meshes_[2]->get_trans(x, y, z);
	GLfloat  vTranslation[3] = { x, y, z };
	glUniform3fv(trans_all[2], 1, vTranslation);
	mat4 m;
	m = m*Translate(0, 0.45, 0)*RotateX(rotateangle.x)*RotateY(rotateangle.y)*RotateZ(180+ rotateangle.z)*Scale(1.1, 1.1, 1.1);
	mat4 viewMatrix(1.0);
	mat4 modelViewMatrix = viewMatrix *model_view;
	mat4 projMatrix = Ortho(left, right, bottom, top, zNear, zFar);
	projMatrix = projMatrix*modelViewMatrix;

	glUniformMatrix4fv(matrixLocation_all[2], 1, GL_TRUE, m);//����������ͼ��ı仯
	glUniformMatrix4fv(modelViewMatrix_all[2], 1, GL_TRUE, modelViewMatrix);
	glUniformMatrix4fv(modelViewProjMatrix_all[2], 1, GL_TRUE, projMatrix);
	glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[2]->num_faces() * 3);
	model_view = mvstack.top();//�ָ����ڵ����
	mvstack.pop();
}

void Mesh_Painter::draw_rightarm()
{
	mvstack.push(model_view);//���游�ڵ����
	glUseProgram(this->program_all[3]);//ָ��ʹ����Ⱦ������ͬ��ģ�Ϳ���ָ����ͬ����Ⱦ������������ʹ�õ���Ⱦ��������ͬ���ļ���ѧ�����Ը����Լ��İ��öԲ�ͬ��ģ���趨��ͬ����Ⱦ��
	glBindVertexArray(this->vao_all[3]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures_all[3]);//�������룬����ֻʹ��ͬһ��������л���
	float x, y, z;
	this->m_my_meshes_[3]->get_trans(x, y, z);
	GLfloat  vTranslation[3] = { x, y, z };
	glUniform3fv(trans_all[3], 1, vTranslation);
	mat4 m;
	m = m*Translate(0, 0.45, 0)*RotateX(rotateangle.x)*RotateY(rotateangle.y)*RotateZ(180 + rotateangle.z)*Scale(1.1, 1.1, 1.1);
	mat4 viewMatrix(1.0);
	mat4 modelViewMatrix = viewMatrix *model_view;
	mat4 projMatrix = Ortho(left, right, bottom, top, zNear, zFar);
	projMatrix = projMatrix*modelViewMatrix;

	glUniformMatrix4fv(matrixLocation_all[3], 1, GL_TRUE, m);//����������ͼ��ı仯
	glUniformMatrix4fv(modelViewMatrix_all[3], 1, GL_TRUE, modelViewMatrix);
	glUniformMatrix4fv(modelViewProjMatrix_all[3], 1, GL_TRUE, projMatrix);
	glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[3]->num_faces() * 3);
	model_view = mvstack.top();//�ָ����ڵ����
	mvstack.pop();
}

void Mesh_Painter::draw_leftleg()
{
	mvstack.push(model_view);//���游�ڵ����
	glUseProgram(this->program_all[4]);//ָ��ʹ����Ⱦ������ͬ��ģ�Ϳ���ָ����ͬ����Ⱦ������������ʹ�õ���Ⱦ��������ͬ���ļ���ѧ�����Ը����Լ��İ��öԲ�ͬ��ģ���趨��ͬ����Ⱦ��
	glBindVertexArray(this->vao_all[4]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures_all[4]);//�������룬����ֻʹ��ͬһ��������л���
	float x, y, z;
	this->m_my_meshes_[4]->get_trans(x, y, z);
	GLfloat  vTranslation[3] = { x, y, z };
	glUniform3fv(trans_all[4], 1, vTranslation);
	mat4 m;
	m = m*Translate(0,0.215,0)*RotateX(rotateangle.x)*RotateY(rotateangle.y)*RotateZ(180 + rotateangle.z)*Scale(1.5, 1.5, 1.5);
	mat4 viewMatrix(1.0);
	mat4 modelViewMatrix = viewMatrix *model_view;
	mat4 projMatrix = Ortho(left, right, bottom, top, zNear, zFar);
	projMatrix = projMatrix*modelViewMatrix;

	glUniformMatrix4fv(matrixLocation_all[4], 1, GL_TRUE, m);//����������ͼ��ı仯
	glUniformMatrix4fv(modelViewMatrix_all[4], 1, GL_TRUE, modelViewMatrix);
	glUniformMatrix4fv(modelViewProjMatrix_all[4], 1, GL_TRUE, projMatrix);
	glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[4]->num_faces() * 3);
	model_view = mvstack.top();//�ָ����ڵ����
	mvstack.pop();
}

void Mesh_Painter::draw_rightleg()
{
	mvstack.push(model_view);//���游�ڵ����
	glUseProgram(this->program_all[5]);//ָ��ʹ����Ⱦ������ͬ��ģ�Ϳ���ָ����ͬ����Ⱦ������������ʹ�õ���Ⱦ��������ͬ���ļ���ѧ�����Ը����Լ��İ��öԲ�ͬ��ģ���趨��ͬ����Ⱦ��
	glBindVertexArray(this->vao_all[5]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textures_all[5]);//�������룬����ֻʹ��ͬһ��������л���
	float x, y, z;
	this->m_my_meshes_[5]->get_trans(x, y, z);
	GLfloat  vTranslation[3] = { x, y, z };
	glUniform3fv(trans_all[5], 1, vTranslation);
	mat4 m;
	m = m*Translate(0,0.215,0)*RotateX(rotateangle.x)*RotateY(rotateangle.y)*RotateZ(180 + rotateangle.z)*Scale(1.5, 1.5, 1.5);
	mat4 viewMatrix(1.0);
	mat4 modelViewMatrix = viewMatrix *model_view;
	mat4 projMatrix = Ortho(left, right, bottom, top, zNear, zFar);
	projMatrix = projMatrix*modelViewMatrix;

	glUniformMatrix4fv(matrixLocation_all[5], 1, GL_TRUE, m);//����������ͼ��ı仯
	glUniformMatrix4fv(modelViewMatrix_all[5], 1, GL_TRUE, modelViewMatrix);
	glUniformMatrix4fv(modelViewProjMatrix_all[5], 1, GL_TRUE, projMatrix);
	glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[5]->num_faces() * 3);
	model_view = mvstack.top();//�ָ����ڵ����
	mvstack.pop();
}


void Mesh_Painter::draw_meshes()
{
	for (unsigned int i = 0; i < this->m_my_meshes_.size(); i++)
	{
		glUseProgram(this->program_all[i]);//ָ��ʹ����Ⱦ������ͬ��ģ�Ϳ���ָ����ͬ����Ⱦ������������ʹ�õ���Ⱦ��������ͬ���ļ���ѧ�����Ը����Լ��İ��öԲ�ͬ��ģ���趨��ͬ����Ⱦ��
		glBindVertexArray(this->vao_all[i]);

 		glActiveTexture(GL_TEXTURE0);
 		glBindTexture(GL_TEXTURE_2D, this->textures_all[i]);//�������룬����ֻʹ��ͬһ��������л���
		
		float x, y, z;
		this->m_my_meshes_[i]->get_trans(x, y, z);
		GLfloat  vTranslation[3] = { x, y, z };
		glUniform3fv(trans_all[i], 1, vTranslation);
		// ���ɱ任����
		mat4 m(1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		// @TODO: �ڴ˴��޸ĺ���������任����
		this->m_my_meshes_[i]->get_translate(x, y, z);
		m = m*Translate(x, y, z);//����ƽ�Ʊ任
		this->m_my_meshes_[i]->get_rotate(x, y, z);
		m = m*RotateX(x)*RotateY(y)*RotateZ(z);//������ת�任
		this->m_my_meshes_[i] ->get_scale(x,y,z);
		m = m*Scale(x, y, z);//�������ű任
																// ��ָ��λ���д���任����
		glUniformMatrix4fv(matrixLocation_all[i], 1, GL_TRUE, m);//����������ͼ��ı仯
		// TODO ��������۲�����ͶӰ���󣬲����붥����ɫ��
		Camera::viewMatrix = LookAt(eye, at, up);
		mat4 modelViewMatrix = Camera::viewMatrix * Camera::modelMatrix;
		mat4 projMatrix = Camera::projMatrix*modelViewMatrix;

		glUniformMatrix4fv(modelViewMatrix_all[i], 1, GL_TRUE, &modelViewMatrix[0][0]);
		glUniformMatrix4fv(modelViewProjMatrix_all[i], 1, GL_TRUE, &Camera::projMatrix[0][0]);
		// ������ת����
		mat4 rotationMatrix = RotateX(rotationAngle);
		glUniformMatrix4fv(rotationMatrix_all[i], 1, GL_TRUE, &rotationMatrix[0][0]);

		// ����Դλ�ô��붥����ɫ��
		glUniform3fv(lightPos_all[i], 1, &lightPos[0]);
		glUniform1i(shadow_all[i], 0);// fshader�������Ƿ�Ϊ��Ӱѡ��ֱ���ɫ


		glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[i]->num_faces() * 3);

		// ������ӰͶӰ���󣬲����붥����ɫ��
		float lx = lightPos.x;
		float ly = lightPos.y;
		float lz = lightPos.z;
		mat4 shadowProjMatrix(
			-ly, 0.0, 0.0, 0.0,
			 lx, 0.0, lz, 1.0,
			0.0, 0.0, -ly, 0.0,
			0.0, 0.0, 0.0, -ly);
		shadowProjMatrix = shadowProjMatrix * modelViewMatrix;
		glUniformMatrix4fv(modelViewMatrix_all[i], 1, GL_TRUE, &shadowProjMatrix[0][0]);
		glUniform1i(shadow_all[i], 1);// fshader�������Ƿ�Ϊ��Ӱѡ��ֱ���ɫ

		glDrawArrays(GL_TRIANGLES, 0, this->m_my_meshes_[i]->num_faces() * 3);
		glUseProgram(0);
	}
};


void Mesh_Painter::update_texture()
{
	this->textures_all.clear();

	for (unsigned int i = 0; i < this->m_my_meshes_.size(); i++)
	{
		//ʵ���������͸�ֵ
		GLuint textures;

		glGenTextures(1, &textures);
		//����FreeImage��������
		load_texture_FreeImage(this->m_my_meshes_[i]->get_texture_file(), textures);

		//ָ�������С���˷����������д��������ӣ������޷���ʾ����
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//�����ɵ�������shader
		glBindTexture(GL_TEXTURE_2D, textures);
		glUniform1i(glGetUniformLocation(this->program_all[i], "texture"), 0);
		this->textures_all.push_back(textures);
	}


};


void Mesh_Painter::load_texture_FreeImage(std::string file_name, GLuint& m_texName)
{
	//1 ��ȡͼƬ��ʽ
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(file_name.c_str(), 0);

	//2 ����ͼƬ
	FIBITMAP *dib = FreeImage_Load(fifmt, file_name.c_str(), 0);

	//3 ת��Ϊrgb 24ɫ;
	dib = FreeImage_ConvertTo24Bits(dib);

	//4 ��ȡ����ָ��
	BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

	int width = FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);

	/**
	* ����һ������Id,������Ϊ��������������Ĳ����������������id
	*/

	/**
	* ʹ���������id,���߽а�(����)
	*/
	glBindTexture(GL_TEXTURE_2D, m_texName);
	/**
	* ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ
	*/
	/**
	* ��ͼƬ��rgb�����ϴ���opengl.
	*/
	glTexImage2D(
		GL_TEXTURE_2D, //! ָ���Ƕ�άͼƬ
		0, //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
		GL_RGB, //! �����ʹ�õĴ洢��ʽ
		width, //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
		height, //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
		0, //! �Ƿ�ı�
		GL_BGR_EXT, //! ���ݵĸ�ʽ��bmp�У�windows,����ϵͳ�д洢��������bgr��ʽ
		GL_UNSIGNED_BYTE, //! ������8bit����
		pixels
		);
	/**
	* �ͷ��ڴ�
	*/
	FreeImage_Unload(dib);
};



void Mesh_Painter::update_vertex_buffer()
{
	this->vao_all.clear();
	this->buffer_all.clear();
	this->vPosition_all.clear();
	this->vColor_all.clear();
	this->vTexCoord_all.clear();
	this->vNormal_all.clear();

	for (unsigned int m_i = 0; m_i < this->m_my_meshes_.size(); m_i++)
	{
		//��������Ӵ���ʵ�ֶ������꣬���ߣ���ɫ���������굽shader��ӳ��
		int num_face = this->m_my_meshes_[m_i]->num_faces();
		int num_vertex = this->m_my_meshes_[m_i]->num_vertices();
		
		const VertexList& vertex_list = this->m_my_meshes_[m_i]->get_vertices();
		const NormalList& normal_list = this->m_my_meshes_[m_i]->get_normals();
		const FaceList&  face_list = this->m_my_meshes_[m_i]->get_faces();
		const STLVectorf& color_list = this->m_my_meshes_[m_i]->get_colors();
		const VtList& vt_list = this->m_my_meshes_[m_i]->get_vts();

		// Create a vertex array object
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(vec3)*num_face * 3
			+ sizeof(vec3)*num_face * 3
			+ sizeof(vec3)*num_face * 3
			+ sizeof(vec2)*num_face * 3
			,
			NULL, GL_STATIC_DRAW);
		
		vec3* points = new vec3[num_face * 3];
		point3f  p_center_ = this->m_my_meshes_[m_i]->get_center();
		point3f p_min_box_, p_max_box_;
		this->m_my_meshes_[m_i]->get_boundingbox(p_min_box_, p_max_box_);
		float d = p_min_box_.distance(p_max_box_);

		for (int i = 0; i < num_face; i++)
		{
			int index = 3 * i;
			points[3 * i] = vec3(
				(vertex_list[index * 3 + 0] - p_center_.x) / (1 * d),
				(vertex_list[index * 3 + 1] - p_center_.y) / (1 * d),
				(vertex_list[index * 3 + 2] - p_center_.z) / (1 * d)
			);
			index = 3 * i + 1;
			points[3 * i + 1] = vec3(
				(vertex_list[index * 3 + 0] - p_center_.x) / (1 * d),
				(vertex_list[index * 3 + 1] - p_center_.y) / (1 * d),
				(vertex_list[index * 3 + 2] - p_center_.z) / (1 * d)
			);
			index = 3 * i + 2;
			points[3 * i + 2] = vec3(
				(vertex_list[index * 3 + 0] - p_center_.x) / (1 * d),
				(vertex_list[index * 3 + 1] - p_center_.y) / (1 * d),
				(vertex_list[index * 3 + 2] - p_center_.z) / (1 * d)
			);
		}
		GLintptr offset = 0;
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vec3)*num_face * 3, points);
		//�������괫��shader
		offset += sizeof(vec3)*num_face * 3;
		delete[] points;
		points = new vec3[num_face * 3];
		for (int i = 0; i < num_face; i++)
		{
			int index = face_list[3 * i];
			points[3 * i] = vec3(
				(normal_list[index * 3 + 0]),
				(normal_list[index * 3 + 1]),
				(normal_list[index * 3 + 2])
			);
			index = face_list[3 * i + 1];
			points[3 * i + 1] = vec3(
				(normal_list[index * 3 + 0]),
				(normal_list[index * 3 + 1]),
				(normal_list[index * 3 + 2])
			);

			index = face_list[3 * i + 2];
			points[3 * i + 2] = vec3(
				(normal_list[index * 3 + 0]),
				(normal_list[index * 3 + 1]),
				(normal_list[index * 3 + 2])
			);
		}
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vec3) * num_face * 3, points);
		offset += sizeof(vec3) * num_face * 3;
		delete[] points;
		//���ߴ���shader

		points = new vec3[num_face * 3];
		for (int i = 0; i < num_face; i++)
		{
			int index = face_list[3 * i];
			points[3 * i] = vec3(
				(color_list[index * 3 + 0]),
				(color_list[index * 3 + 1]),
				(color_list[index * 3 + 2])
			);

			index = face_list[3 * i + 1];
			points[3 * i + 1] = vec3(
				(color_list[index * 3 + 0]),
				(color_list[index * 3 + 1]),
				(color_list[index * 3 + 2])
			);

			index = face_list[3 * i + 2];
			points[3 * i + 2] = vec3(
				(color_list[index * 3 + 0]),
				(color_list[index * 3 + 1]),
				(color_list[index * 3 + 2])
			);
		}
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vec3) * num_face * 3, points);
		//��ɫ����shader
		offset += sizeof(vec3) * num_face * 3;
		delete[] points;

		vec2* points_2 = new vec2[num_face * 3];
		for (int i = 0; i < num_face; i++)
		{
			points_2[i * 3] = vec2(vt_list[i * 6 + 0], vt_list[i * 6 + 1]);
			points_2[i * 3 + 1] = vec2(vt_list[i * 6 + 2], vt_list[i * 6 + 3]);
			points_2[i * 3 + 2] = vec2(vt_list[i * 6 + 4], vt_list[i * 6 + 5]);
		}
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vec2) * num_face * 3, points_2);
		offset += sizeof(vec2) * num_face * 3;
		delete points_2;
		offset = 0;
		GLuint vPosition;
		vPosition = glGetAttribLocation(this->program_all[m_i], "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(offset));
		offset += sizeof(vec3) * num_face * 3;
		GLuint vNormal;
		vNormal = glGetAttribLocation(this->program_all[m_i], "vNormal");
		glEnableVertexAttribArray(vNormal);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(offset));
		offset += sizeof(vec3) * num_face * 3;
		GLuint vColor;
		vColor = glGetAttribLocation(this->program_all[m_i], "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(offset));
		offset += sizeof(vec3) * num_face * 3;
		GLuint vTexCoord;
		vTexCoord = glGetAttribLocation(this->program_all[m_i], "vTexCoord");
		glEnableVertexAttribArray(vTexCoord);
		glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(offset));
		

		this->vao_all.push_back(vao);
		this->buffer_all.push_back(buffer);
		this->vPosition_all.push_back(vPosition);
		this->vColor_all.push_back(vColor);
		this->vTexCoord_all.push_back(vTexCoord);
		this->vNormal_all.push_back(vNormal);
	}
};
void Mesh_Painter::init_shaders(std::string vs, std::string fs)
{
	this->program_all.clear();
	this->theta_all.clear();
	this->trans_all.clear();
	for (unsigned int i = 0; i < this->m_my_meshes_.size(); i++)
	{
		GLuint program = InitShader(vs.c_str(), fs.c_str());
		glUseProgram(program);
		this->program_all.push_back(program);


		GLuint modelViewMatrixID = glGetUniformLocation(program, "modelViewMatrix");
		GLuint modelViewProjMatrixID = glGetUniformLocation(program, "modelViewProjMatrix");
		GLuint rotationMatrixID = glGetUniformLocation(program, "rotationMatrix");//��ת�任����
		GLuint lightPosID = glGetUniformLocation(program, "lightPos");
		GLuint shadowID = glGetUniformLocation(program, "isShadow");//������Ӱ���ж�

		GLuint 	theta = glGetUniformLocation(program, "theta");
		GLuint  trans = glGetUniformLocation(program, "translation");
		GLuint  matrixLocation = glGetUniformLocation(program, "matrix");


		theta_all.push_back(theta);
		trans_all.push_back(trans);
		matrixLocation_all.push_back(matrixLocation);
		modelViewMatrix_all.push_back(modelViewMatrixID);
		modelViewProjMatrix_all.push_back(modelViewProjMatrixID);
		rotationMatrix_all.push_back(rotationMatrixID);
		lightPos_all.push_back(lightPosID);
		shadow_all.push_back(shadowID);
	}
};
void Mesh_Painter::add_mesh(My_Mesh* m)
{
	this->m_my_meshes_.push_back(m);
};
void Mesh_Painter::clear_mehs()
{
	this->m_my_meshes_.clear();

	this->textures_all.clear();
	this->program_all.clear();
	this->vao_all.clear();
	this->buffer_all.clear();
	this->vPosition_all.clear();
	this->vColor_all.clear();
	this->vTexCoord_all.clear();
	this->vNormal_all.clear();
}
My_Mesh * Mesh_Painter::return_mesh(int i)
{
	return m_my_meshes_[i];
}
void Mesh_Painter::setLightPos(vec3 l)
{
	lightPos = l;
}
void Mesh_Painter::setRotationAngle(float r)
{
	rotationAngle = r;
}
void Mesh_Painter::seteye(vec4 e)
{
	eye = e;
}
void Mesh_Painter::setat(vec4 a)
{
	at = a;
}
void Mesh_Painter::setup(vec4 u)
{
	up = u;
}
;
