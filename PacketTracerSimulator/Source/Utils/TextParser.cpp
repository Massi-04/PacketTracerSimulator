#include "TextParser.h"

bool TextParser::ParseInt(const std::string& string, int& result)
{
	int localResult = 0;
	try
	{
		localResult = std::stoi(string);
	}
	catch (...)
	{
		return false;
	}
	result = localResult;
	return true;
}
