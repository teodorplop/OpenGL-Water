#pragma once

#include<string>
#include<iostream>
#include<fstream>
using namespace std;

class FileIO {
public:
	static string GetFileContents(const char* filePath);
	static void ClearFileContent(const char* filePath);
	static void WriteContent(const char* filePath, const std::string& content);
	static void WriteContent(const char* filePath, const char* content);
};