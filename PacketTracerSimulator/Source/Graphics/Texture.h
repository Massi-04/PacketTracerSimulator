#pragma once
#include "Core/Base.h"

class Texture
{
public:
	Texture(uchar* imageSource, uint imageWidth, uint imageHeight, uint imageNChannels);
	~Texture();

	void Bind(bool bind);

	static Texture* LoadTexture(const std::string& filePath);

private:
	uint ID;

};

