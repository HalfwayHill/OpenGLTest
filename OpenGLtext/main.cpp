#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//C++ ���Ե����ԣ�ǰ�ã�����ᷢ������
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
	//C++ ����������ָ������� *
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("open window faild.");
		glfwTerminate();
		return -1;
	}
	//��window���
	glfwMakeContextCurrent(window);

	//Init GLEW.
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW faild.");
		glfwTerminate();
		return -1;
	}
	//�ӿڡ�
	glViewport(0, 0, 800, 600);
	//׼�����档
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		//��ȡ��������
		glfwPollEvents();
	}
	//��Ⱦ��������ȷ����/ɾ��֮ǰ�����������Դ��
	glfwTerminate();
	return 0;
}