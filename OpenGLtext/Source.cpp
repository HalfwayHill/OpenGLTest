#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

int main2() {

	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 trans; // trans will be a identity 4X4 matrix.
	trans = glm::translate(trans, glm::vec3(2.0f, 0.0f, 0.0f));

	vec = trans * vec;

	std::cout << vec.x << vec.y << vec.z << std::endl;

	while (true)
	{

	}

	return 0;
}