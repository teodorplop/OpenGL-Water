#pragma once

#include<vector>
#include<string>

class StringUtils {
public:
	static std::vector<std::string> Split(char* text, const char* delimiters);
	static std::vector<std::string> Split(const std::string& text, const char* delimiters);
};

