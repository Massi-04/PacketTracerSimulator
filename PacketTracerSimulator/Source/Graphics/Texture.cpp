#include "Texture.h"
#include "Libs/GL/glew.h"
#include "Libs/STB/StbImage.h"
#include "Utils/FileManager.h"

Texture::Texture(uchar* imageSource, uint imageWidth, uint imageHeight, uint imageNChannels) : 
	ID(0)
{
	LOG("Texture object created\n");
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	Bind(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageSource);
	Bind(false);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
	LOG("Texture object destroyed\n");
}

void Texture::Bind(bool bind)
{
	glBindTexture(GL_TEXTURE_2D, bind ? ID : 0);
}

Texture* Texture::LoadTexture(const std::string& filePath)
{
	Texture* texture;
	int imageWidth, imageHeight, imageNChannels;
	stbi_set_flip_vertically_on_load(1);
	uchar* imageSource = stbi_load((FileManager::assetDirectory + filePath).c_str(), &imageWidth, &imageHeight, &imageNChannels, 4); // 4 = RGBA
	if (imageSource == nullptr)
	{
		LOG("Error: unable to open texture file");
		return nullptr;
	}
	texture = new Texture(imageSource, imageWidth, imageHeight, imageNChannels);
	stbi_image_free(imageSource);
	return texture;
}
