#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

using namespace std;

int main() {
	
	int width, height, nrChannels;
	//获取某个位置的RGB
	unsigned char *data = stbi_load("mipmaps.png", &width, &height, &nrChannels, 0);
	
	for (size_t i = 0; i < 50; i++)
	{
		cout << (int)data[i] << endl;
	}

	//释放内存
	stbi_image_free(data);

	while (true)
	{

	}

	return 0;
}