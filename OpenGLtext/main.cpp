#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//triangle�Ķ�������,ÿ��ǰ3��������Ϊ�������꣬��3��������Ϊ�������ɫ
float vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - ��������(UVֵ) -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};
//ʹ��EBO��IBO�����л��ƣ���Ҫ�������������
unsigned int indices[] = {
	//��ʱ���������
	0,1,2,
	2,3,0
};

/*
//Ӳ����
const char* vertexShaderSource =
"#version 330 core                                           \n"
"layout(location = 0) in vec3 aPos;                           \n"
"layout(location = 1) in vec3 aColor;                          \n"
"out vec4 vertexColor;                                        \n"//ΪƬ����ɫ����framentShader��ָ��һ����ɫ���,vertexShaderһ��Ҫ�����ĳ������gl_Position,����vertexShader��ָ�����񣬶�vertexColorʵ�ʾ��Ǽд���һС�����ݡ�
"void main(){\n                                                "
"          gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);   \n"
"          vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0); \n"
"} \n";
//һ��Shader����Ҫ������������framentShader
const char* fragmentShaderSource =
"#version 330 core                                  \n	  "
"in vec4 vertexColor;                               \n   "//����,һ��Ҫ�����洫�����ı�����һ��
"uniform vec4 ourColor;                             \n   "//��CPUֱ�Ӵ���uniform��framentShader
"out vec4 FragColor;                                \n	  "
"void main(){\n									    	  "
"		FragColor = vertexColor;}  \n    ";
*/


//ʹ�ð�ESC���������ڡ�
//C++ ���������ڷ�������ǰ����ǰ��������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	//��ӡ������
	//printf("Hello World");
	/*
	while (true)
	{
		//��������̨��ʾHello World
		//do nothing
	}
	*/

	//��ʼ��glfw,�汾��3.3
	//����ĵ�Ҫ�Ķ���
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//Open GLFW Window
	//C++��*����������ʶ�������ַ��ָ��
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGl Game", NULL, NULL);
	//������ʧ�������һ�λ���������γ��򣬷���-1
	if (window == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();
		return -1;
	}
	//�������ɹ�����󶨣��Ѵ�window��Ϊ��Ҫ������ 
	glfwMakeContextCurrent(window);


	//Init GLEW
	glewExperimental = true;
	//������һ�����������ʧ�������һ�����֣�ֹͣ���򣬷���-1.
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW faild.");
		glfwTerminate();
		return -1;
	}

	//����λ�á�
	glViewport(0, 0, 800, 600);
	//�������޳����ܡ�OpenGL�Զ������ʱ���γɵ�����Ϊ����
	//glEnable(GL_CULL_FACE);
	////�����޳�����
	//glCullFace(GL_BACK);
	//�߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader* testShader = new Shader("vertexSource.txt", "fragmentSource.txt");

	//����VAO
	unsigned int VAO;
	//����һ��VAO������1��������һ��id����������VAO�У�����2��,"&"��������Ϊ�ʹ���1����
	glGenVertexArrays(1, &VAO);
	//�������÷�
	//unsigned int VAO[10];
	//glGenVertexArrays(10, VAO);

	//��
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//�󶨣�������buffer�����͡�
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//������buffer���ͣ����鳤�ȣ���������,��δ������Ƿ��͵Ķ������ꡣ
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////vertexShader
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	////fragmentShader
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	////Shader program
	////��vertexShader��fragmentShader��������
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);


	//��ȡλ��
	//����vertexattrib 0����λ������1�� ÿ3����λ����һ�����ϣ�����2�� ÿ����λ����һ��������������3�������Ƿ����滯������4�� ÿ�λ�ȡ���Ҫ���������ȥ��ȡ������4�� ��һ������Ҫƫ�ƶ��ٻ�ȡ������5��  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//��vertexattrib 0
	glEnableVertexAttribArray(0);
	//��ȡ��ɫ����Ϊ������ɫRGB����������������Ҫ��6��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//UVֵ
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//����������ȡ�������ԣ���������
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	//������A����0����λ
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("ourTexture.jpg", &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//ʹ�ö�������Mipmap��
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed.");
	}
	stbi_image_free(data);
	//����B
	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	//������A����3����λ
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);

	unsigned char *data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		//ʹ�ö�������Mipmap��
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed.");
	}
	stbi_image_free(data2);

	//Ready your engines
	//�ж�window�Ƿ񱻹رգ�������Ⱦ��
	//����ĵ�Ҫ�Ķ���
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering commands here
		//��������Ҫ����������ɫ
		glClearColor(0, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Ӧ������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//��CPU�õ�ʱ�䣬����ͨ��uniform���ݵ���ɫ���ϣ�ʹ����ɫ��ʱ��任��
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUseProgram(shaderProgram);

		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);*/

		testShader->use();

		glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 3);

		//VBO һ�������Σ�3�����㣬���������ı��Σ�������������Ҫ���»��ƣ�������Ҫ����6�����㣬���˷����ܣ����Կ���ʹ��EBO
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//ʹ��EBO/IBO����
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		//��ȡ�û�����
		glfwPollEvents();
	}

	//last a thing
	glfwTerminate();
	return 0;
}
