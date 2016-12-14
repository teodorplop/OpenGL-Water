#include "StringUtils.h"

std::vector<std::string> StringUtils::Split(char* text, const char* delimiters) {
	std::vector<std::string> result;

	char *split = strtok(text, delimiters);
	while (split != NULL) {
		result.push_back(std::string(split));
		split = strtok(NULL, "_");
	}

	return result;
}

std::vector<std::string> StringUtils::Split(const std::string& text, const char* delimiters) {
	char *cstr = new char[text.size()];
	strcpy(cstr, text.c_str());

	return Split(cstr, delimiters);
}