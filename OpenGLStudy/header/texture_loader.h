#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

#include <iostream>

class TextureLoader
{
public:
	static TextureLoader* getInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new TextureLoader();
		}

		return m_pInstance;
	};

	void load_img(unsigned int &texture, const char* img_path, int &width, int &height, int &nr_channels, int hasAlpha, int arg = 0) {
		// texture
		// ---------
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps

		stbi_set_flip_vertically_on_load(true);
		// tell stb_image.h to flip loaded texture's on the y-axis.
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char *data = stbi_load(img_path, &width, &height, &nr_channels, arg);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, hasAlpha, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture  res/" << img_path << std::endl;
		}
		stbi_image_free(data);
	};

private:
	TextureLoader() {};
	~TextureLoader() {};

	static TextureLoader* m_pInstance;
};

TextureLoader * TextureLoader::m_pInstance = nullptr;

#endif // !TEXTURE_LOADER_H

