#include "FileManager.h"
#include <fstream>

const std::string FileManager::assetDirectory = "Assets/";

std::string FileManager::ReadFile(const std::string& path)
{
    std::ifstream myfile(assetDirectory + path);
    std::string result;
    if (myfile.is_open())
    {
        std::string line;
        while (getline(myfile, line))
            result += line + '\n';
        myfile.close();
    }
    else
        LOG("[ERROR:] File: " << path << " not found\n");
	return result;
}
