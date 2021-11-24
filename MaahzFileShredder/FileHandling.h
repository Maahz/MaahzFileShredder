#pragma once
#include<iostream>
#include<fstream>

using namespace std;

class FileHandling
{
public:

	//Function to get size of the file
	std::ifstream::pos_type filesize(const char* filename);

	//Check if file exists
	int F_Exists(char* fileName);

	//Function to overwrite the exsisting file
	int Overwrite(char* filename, streamoff fileSize);

	//Function to get pseudo random data for file overwriting
	char* GetRandData(int64_t dataSize);
};


