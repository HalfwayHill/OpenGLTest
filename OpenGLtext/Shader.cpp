#include "Shader.h"
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//�����Ͳ���ʹ��std::ifstream vertexFile;������ʹ��ifstream vertexFile;
using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//fileBuffer
	/*ifstream vertexFile;
	ifstream fragmentFile;*/
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	//stringBuffer,����fileBuffer
	stringstream vertexSStream;
	stringstream fragmentSStream;

	//����
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	//�ж������쳣��1���߼��ϲ��ܿ��� 2������
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	//�ж��Ƿ񿪵��ɹ�
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("open file error");
		}
		// Ӳ�� -> FileBuffer -> StringBuffer ��һ��������
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;

		//vertexshader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		// ��ȡԴ����  ������1.shader���� 2.�����ִ�������� 3.�ַ������飨����ֻ��һ����������&�� 4.����
		glShaderSource(vertex, 1, &vertexSource, NULL);
		//��Դ����ת��Ϊ�����ơ�
		glCompileShader(vertex);

		//fragmentshader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);

		//��vertex��fragment���������ϳ�program�����ܶ�ȡ��
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		//�����Ѿ����������ˣ����Կ��Խ�����ɾ����

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

//Shader::~Shader()
//{
//}

