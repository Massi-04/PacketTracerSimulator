#pragma once
#include "Core/Base.h"

class FileManager
{
public:
	FileManager() = delete;
	
	static const std::string assetDirectory;

	static std::string ReadFile(const std::string& path);
};

