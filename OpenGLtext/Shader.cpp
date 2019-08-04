#include "Shader.h"
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//这样就不用使用std::ifstream vertexFile;，可以使用ifstream vertexFile;
using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//fileBuffer
	/*ifstream vertexFile;
	ifstream fragmentFile;*/
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	//stringBuffer,引用fileBuffer
	stringstream vertexSStream;
	stringstream fragmentSStream;

	//开档
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	//判断两个异常：1，逻辑上不能开档 2，坏档
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	//判断是否开档成功
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("open file error");
		}
		// 硬盘 -> FileBuffer -> StringBuffer 这一串操作。
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;

		//vertexshader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		// 读取源代码  参数：1.shader番号 2.引用字串数组个数 3.字符串数组（由于只有一个，所以用&） 4.长度
		glShaderSource(vertex, 1, &vertexSource, NULL);
		//从源代码转换为二进制。
		glCompileShader(vertex);

		//fragmentshader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);

		//将vertex和fragment连接起来合成program，才能读取。
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		//由于已经连接起来了，所以可以将两者删除。

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

