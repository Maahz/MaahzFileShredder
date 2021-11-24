#include<Windows.h>
#include<wincrypt.h>
#include "FileHandling.h"

using namespace std;


/// <summary>
/// Return filesize in bytes
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
std::ifstream::pos_type FileHandling::filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

/// <summary>
/// Write data to a file
/// </summary>
/// <param name="filename"></param>
/// <param name="fileSize"></param>

int FileHandling::Overwrite(char* filename, streamoff fileSize)
{
    if (!F_Exists(filename))
        return 1;
    ofstream daFile;
    daFile.open(filename,std::fstream::app);
    
    char* result = GetRandData((int64_t)fileSize);
    if (result == NULL)
        return 1;
    daFile << result;

    free(result);                   //Freedom!!!!!!!!

    daFile.close();
    //Testing code cout << filename << " : " << fileSize << endl;
    return 0;
}

/// <summary>
/// Check if file exists
/// </summary>
/// <param name="fileName"></param>
int FileHandling::F_Exists(char* fileName)
{
    ifstream file(fileName);
    if (file.fail())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


//Function to get pseudo random data for file overwriting
char* FileHandling::GetRandData(int64_t fileSize)
{
    DWORD dataSize = (DWORD)fileSize;
    HCRYPTPROV hProv = 0;                       //        !!!!!!POSSIBLE BUFFER OVERFLOW!!!!!!!!!!

    //char* data = (char*)malloc(sizeof(char) * dataSize);  //!!!!!!MAKE SURE DATA SIZE CANT BE TOO LARGE!!!!!!!!!!
    char* data = new char();
                                                          //Test that data isnt NULL...so that compiler wont get angry
    if (data == NULL) return (char*)"Error";


    if(!CryptGenRandom(hProv, dataSize, (unsigned char*)data))
    {
        return (char*)data;
    }
    else
        return (char*)"Error\n";
}