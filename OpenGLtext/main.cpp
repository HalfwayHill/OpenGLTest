#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//C++ 语言的特性，前置，否则会发生错误
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window,GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(){

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create GLFW window.
	//C++ 特性声明、指针或引用 *
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("open window faild.");
		glfwTerminate();
		return -1;
	}
	//将window添加
	glfwMakeContextCurrent(window);

	//Init GLEW.
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW faild.");
		glfwTerminate();
		return -1;
	}
	//视口。
	glViewport(0, 0, 800, 600);
	//准备引擎。
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		//获取键盘输入
		glfwPollEvents();
	}
	//渲染结束后正确清理/删除之前分配的所有资源。
	glfwTerminate();
	return 0;
}