#include "mesh.h"
#include<sstream>
#include <fstream>
#include <iosfwd>
#include <algorithm>
#include <gl/GL.h>
#include <math.h>
#include <algorithm>


My_Mesh::My_Mesh()
{

	vTranslation[0] = Trans[0] = 0;
	vTranslation[1] = Trans[1] = 0;
	vTranslation[2] = Trans[2] = 0;
}


My_Mesh::~My_Mesh()
{
	
}


void My_Mesh::load_obj(std::string obj_File)
{
	//请在此添加代码实现对含有UV坐标的obj文件的读取
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<vec3> temp_vertices;
	std::vector<vec2> temp_uvs;
	std::vector<vec3> temp_normals;
	std::vector<vec3> temp_faces;

	if (obj_File.empty()) return;
	std::ifstream f;
	f.open(obj_File.c_str(), std::ios::in);
	while (!f.eof()) {
		std::string lineheader;//用来识别数据是v,vt,vn,f中的哪一种
		f >> lineheader;
		if (lineheader == "v") {
			vec3 vertex;
			f >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (lineheader == "vt") {
			vec2 uv;
			f >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (lineheader == "vn") {
			vec3 normal;
			f >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (lineheader == "f") {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			char ch;
			f >> vertexIndex[0] >> ch >> uvIndex[0] >> ch >> normalIndex[0] 
				>> vertexIndex[1] >> ch >> uvIndex[1] >> ch >> normalIndex[1] 
				>> vertexIndex[2] >> ch >> uvIndex[2] >> ch >> normalIndex[2];

			m_faces_.push_back(vertexIndex[0]);
			m_faces_.push_back(vertexIndex[1]);
			m_faces_.push_back(vertexIndex[2]);
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	auto min=std::min_element(temp_normals.begin(),temp_normals.end(), [](const vec3& lhs, const vec3& rhs) {
		return lhs.y < rhs.y;
	});
	
	this->m_center_ = point3f(0, 0, 0);
	float min_x, max_x, min_y, max_y, min_z, max_z;
	auto min_max = std::minmax_element(
		temp_vertices.begin(), temp_vertices.end(),
		[](const vec3& lhs, const vec3& rhs) {
		return lhs.x < rhs.x;
	});
	min_x = (*min_max.first).x;
	max_x = (*min_max.second).x;
	min_max = std::minmax_element(
		temp_vertices.begin(), temp_vertices.end(),
		[](const vec3& lhs, const vec3& rhs) {
		return lhs.y < rhs.y;
	});
	min_y = (*min_max.first).y;
	max_y = (*min_max.second).y;
	min_max = std::minmax_element(
		temp_vertices.begin(), temp_vertices.end(),
		[](const vec3& lhs, const vec3& rhs) {
		return lhs.z < rhs.z;
	});
	min_z = (*min_max.first).z;
	max_z = (*min_max.second).z;
	m_min_box_ = point3f(min_x, min_y, min_z);
	m_max_box_ = point3f(max_x, max_y, max_z);
	// 把顶点坐标存到对应的位置上
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		vec3 vertex = temp_vertices[vertexIndex - 1];
		vec2 uv = temp_uvs[uvIndex - 1];
		vec3 normal = temp_normals[normalIndex - 1];
		m_vertices_.push_back(vertex.x);
		m_vertices_.push_back(vertex.y);
		m_vertices_.push_back(vertex.z);
		m_vt_list_.push_back(uv.x);
		m_vt_list_.push_back(uv.y);
		m_normals_.push_back(normal.x);
		m_normals_.push_back(normal.y-(*min).y);
		m_normals_.push_back(normal.z);
		float r, g, b;
		normal_to_color(normal.x, normal.y, normal.z, r, g, b);
		m_color_list_.push_back(r);
		m_color_list_.push_back(g);
		m_color_list_.push_back(b);
	}
	f.close();
	std::cout << "readfinish" << std::endl;
};

void My_Mesh::normal_to_color(float nx, float ny, float nz, float& r, float& g, float& b)
{
	r = float(std::min(std::max(0.5 * (nx + 1.0), 0.0), 1.0));
	g = float(std::min(std::max(0.5 * (ny + 1.0), 0.0), 1.0));
	b = float(std::min(std::max(0.5 * (nz + 1.0), 0.0), 1.0));
};

const VtList&  My_Mesh::get_vts()
{
	return this->m_vt_list_;
};
void My_Mesh::clear_data()
{
	m_vertices_.clear();
	m_normals_.clear();
	m_faces_.clear();
	m_color_list_.clear();
	m_vt_list_.clear();
};
void My_Mesh::get_boundingbox(point3f& min_p, point3f& max_p) const
{
	min_p = this->m_min_box_;
	max_p = this->m_max_box_;
};
const STLVectorf&  My_Mesh::get_colors()
{
	return this->m_color_list_;
};
const VertexList& My_Mesh::get_vertices()
{
	return this->m_vertices_;
};
const NormalList& My_Mesh::get_normals()
{
	return this->m_normals_;
};
const FaceList&   My_Mesh::get_faces()
{
	return this->m_faces_;
};

int My_Mesh::num_faces()
{
	return this->m_faces_.size()/3;
};
int My_Mesh::num_vertices()
{
	return this->m_vertices_.size()/3;
};

const point3f& My_Mesh::get_center()
{
	return this->m_center_;
};


void My_Mesh::generate_cylinder(int num_division, float height)
{
	this->clear_data();
	this->m_center_ = point3f(0, 0, 0);
	this->m_min_box_ = point3f(-1, -1, -height);
	this->m_max_box_ = point3f(1, 1, height);

	int num_samples = num_division;
	float z = -height;
	float pi = 3.14159265;
	float step = 1.0 * 360 / num_samples;
	float rr = pi / 180;
	//圆柱体Z轴向上，按cos和sin生成x，y坐标
	for (int i = 0; i < num_samples; i++)
	{
		float r_r_r = i * step * rr;
		float x = cos(r_r_r);
		float y = sin(r_r_r);
		m_vertices_.push_back(x);
		m_vertices_.push_back(y);
		m_vertices_.push_back(z);

		m_normals_.push_back(x);
		m_normals_.push_back(y);
		m_normals_.push_back(0);
		//法线由里向外
		float r;
		float g;
		float b;
		My_Mesh::normal_to_color(x, y, z, r, g, b);
		//这里采用法线来生成颜色，学生可以自定义自己的颜色生成方式
		m_color_list_.push_back(r);
		m_color_list_.push_back(g);
		m_color_list_.push_back(b);
	}

	z = height;
	//圆柱体Z轴向上，按cos和sin生成x，y坐标，
	for (int i = 0; i < num_samples; i++)
	{
		float r_r_r = i * step * rr;
		float x = cos(r_r_r);
		float y = sin(r_r_r);
		m_vertices_.push_back(x);
		m_vertices_.push_back(y);
		m_vertices_.push_back(z);

		m_normals_.push_back(x);
		m_normals_.push_back(y);
		m_normals_.push_back(0);
		//法线由里向外
		float r;
		float g;
		float b;
		My_Mesh::normal_to_color(x, y, z, r, g, b);
		m_color_list_.push_back(r);
		m_color_list_.push_back(g);
		m_color_list_.push_back(b);
		//这里采用法线来生成颜色，学生可以自定义自己的颜色生成方式
	}

	for (int i = 0; i < num_samples; i++)
	{
		m_faces_.push_back(i);
		m_faces_.push_back((i + 1) % num_samples);
		m_faces_.push_back((i + num_samples) % (num_samples)+num_samples);

		m_faces_.push_back((i + num_samples) % (num_samples)+num_samples);
		m_faces_.push_back((i + 1) % num_samples);
		m_faces_.push_back((i + num_samples + 1) % (num_samples)+num_samples);
		//生成三角面片

		m_vt_list_.push_back(1.0 * i / num_samples);
		m_vt_list_.push_back(0.0);
		//纹理坐标
		m_vt_list_.push_back(1.0 * ((i + 1)) / num_samples);
		m_vt_list_.push_back(0.0);
		//纹理坐标
		m_vt_list_.push_back(1.0 * i / num_samples);
		m_vt_list_.push_back(1.0);
		//纹理坐标

		m_vt_list_.push_back(1.0 * i / num_samples);
		m_vt_list_.push_back(1.0);
		//纹理坐标
		m_vt_list_.push_back(1.0 * ((i + 1)) / num_samples);
		m_vt_list_.push_back(0.0);
		//纹理坐标
		m_vt_list_.push_back(1.0 * ((i + 1)) / num_samples);
		m_vt_list_.push_back(1.0);
		//纹理坐标
	}

};


void My_Mesh::set_texture_file(std::string s)
{
	this->texture_file_name = s;
};
std::string My_Mesh::get_texture_file()
{
	return this->texture_file_name;
};

void My_Mesh::set_translate(vec3 translate)
{
	vTranslation[0] = translate.x;
	vTranslation[1] = translate.y;
	vTranslation[2] = translate.z;

};
void My_Mesh::get_translate(float& x, float& y, float& z)
{
	x = vTranslation[0];
	y = vTranslation[1];
	z = vTranslation[2];
}
void My_Mesh::set_scale(vec3 scale)
{
	vScale[0] = scale.x;
	vScale[1] = scale.y;
	vScale[2] = scale.z;
}
void My_Mesh::get_scale(float & x, float & y, float & z)
{
	x = vScale[0];
	y = vScale[1];
	z = vScale[2];
}
void My_Mesh::set_rotate(vec3 rotate)
{
	vRotate[0] = rotate.x;
	vRotate[1] = rotate.y;
	vRotate[2] = rotate.z;
}
void My_Mesh::get_rotate(float & x, float & y, float & z)
{
	x = vRotate[0];
	y = vRotate[1];
	z = vRotate[2];
}
void My_Mesh::set_trans(float x, float y, float z)
{
	Trans[0] = x;
	Trans[1] = y;
	Trans[2] = z;
}
void My_Mesh::get_trans(float & x, float & y, float & z)
{
	x = Trans[0];
	y = Trans[1];
	z = Trans[2];
}
;


void My_Mesh::set_theta_step(float x, float y, float z)
{
	Theta_step[0] = x;
	Theta_step[1] = y;
	Theta_step[2] = z;
};

