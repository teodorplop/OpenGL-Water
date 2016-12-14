#include "FileUtils.h"

string FileUtils::GetFileContents(const char* filePath) {
	ifstream fileStream(filePath, ios::in);
	string content = "";
	if (fileStream.is_open()) {
		string line = "";
		while (getline(fileStream, line)) {
			content += line + "\n";
		}
		fileStream.close();
	}
	return content;
}

void FileUtils::WriteContent(const char* filePath, const std::string& content) {
	ofstream fileStream(filePath, ios::out);
	if (fileStream.is_open()) {
		fileStream << content;
		fileStream.close();
	}
}
void FileUtils::WriteContent(const char* filePath, const char* content) {
	ofstream fileStream(filePath, ios::out);
	if (fileStream.is_open()) {
		fileStream << content;
		fileStream.close();
	}
}

void FileUtils::ClearFileContent(const char* filePath) {
	WriteContent(filePath, "");
}