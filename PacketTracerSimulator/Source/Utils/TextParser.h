#pragma once
#include "Core/Base.h"

class TextParser
{
public:
	TextParser() = delete;

	static bool ParseInt(const std::string& string, int& result);
};