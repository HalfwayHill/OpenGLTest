#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//triangle的顶点坐标,每行前3个浮点数为顶点坐标，后3个浮点数为顶点的颜色
float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标(UV值) -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
//使用EBO（IBO）进行绘制，需要顶点坐标的索引
unsigned int indices[] = {
	//逆时针才是正面
	0,1,2,
	2,3,0
};

/*
//硬编码
const char* vertexShaderSource =
"#version 330 core                                           \n"
"layout(location = 0) in vec3 aPos;                           \n"
"layout(location = 1) in vec3 aColor;                          \n"
"out vec4 vertexColor;                                        \n"//为片段着色器（framentShader）指定一个颜色输出,vertexShader一定要向后面的程序输出gl_Position,这是vertexShader的指定任务，而vertexColor实际就是夹带的一小段数据。
"void main(){\n                                                "
"          gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);   \n"
"          vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0); \n"
"} \n";
//一般Shader的主要操作都集中在framentShader
const char* fragmentShaderSource =
"#version 330 core                                  \n	  "
"in vec4 vertexColor;                               \n   "//输入,一定要和上面传过来的变量名一致
"uniform vec4 ourColor;                             \n   "//从CPU直接传递uniform到framentShader
"out vec4 FragColor;                                \n	  "
"void main(){\n									    	  "
"		FragColor = vertexColor;}  \n    ";
*/


//使用按ESC键结束窗口。
//C++ 函数必须在方法声明前。（前置声明）
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	//打印方法。
	//printf("Hello World");
	/*
	while (true)
	{
		//锁死控制台显示Hello World
		//do nothing
	}
	*/

	//初始化glfw,版本号3.3
	//这段文档要阅读。
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//Open GLFW Window
	//C++中*是声明的意识，对象地址，指针
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGl Game", NULL, NULL);
	//若开窗失败则输出一段话，结束这段程序，返回-1
	if (window == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();
		return -1;
	}
	//若开窗成功则将其绑定，把此window作为主要上下文 
	glfwMakeContextCurrent(window);


	//Init GLEW
	glewExperimental = true;
	//和上面一样，如果创建失败则输出一段文字，停止程序，返回-1.
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW faild.");
		glfwTerminate();
		return -1;
	}

	//开窗位置。
	glViewport(0, 0, 800, 600);
	//启动面剔除功能。OpenGL以顶点的逆时针形成的面作为正面
	//glEnable(GL_CULL_FACE);
	////背面剔除功能
	//glCullFace(GL_BACK);
	//线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader* testShader = new Shader("vertexSource.txt", "fragmentSource.txt");

	//创建VAO
	unsigned int VAO;
	//创建一个VAO（参数1），返还一个id放入声明的VAO中（参数2）,"&"符号是因为就创建1个。
	glGenVertexArrays(1, &VAO);
	//真正的用法
	//unsigned int VAO[10];
	//glGenVertexArrays(10, VAO);

	//绑定
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//绑定，参数是buffer的类型。
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//参数，buffer类型，数组长度，顶点数组,如何处理我们发送的顶点坐标。
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
	////将vertexShader和fragmentShader连接起来
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);


	//获取位置
	//设置vertexattrib 0号栏位（参数1） 每3个栏位当成一份资料（参数2） 每个栏位都是一个浮点数（参数3）设置是否正规化（参数4） 每次获取完后要间隔多少再去获取（参数4） 第一笔资料要偏移多少获取（参数5）  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//打开vertexattrib 0
	glEnableVertexAttribArray(0);
	//获取颜色，因为有了颜色RGB三个浮点数，所以要跳6个
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//UV值
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//加载纹理，获取纹理属性，进行设置
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	//将纹理A放入0号栏位
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("ourTexture.jpg", &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//使用多层次纹理（Mipmap）
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed.");
	}
	stbi_image_free(data);
	//纹理B
	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	//将纹理A放入3号栏位
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);

	unsigned char *data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		//使用多层次纹理（Mipmap）
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed.");
	}
	stbi_image_free(data2);

	//Ready your engines
	//判断window是否被关闭，进行渲染。
	//这段文档要阅读。
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering commands here
		//先清屏，要设置清屏颜色
		glClearColor(0, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//应用纹理
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//从CPU拿到时间，让其通过uniform传递到着色器上，使其颜色随时间变换。
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUseProgram(shaderProgram);

		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);*/

		testShader->use();

		glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 3);

		//VBO 一个三角形，3个顶点，如果想绘制四边形，其中两个顶点要重新绘制，这样就要绘制6个顶点，会浪费性能，所以可以使用EBO
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//使用EBO/IBO绘制
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		//获取用户输入
		glfwPollEvents();
	}

	//last a thing
	glfwTerminate();
	return 0;
}
