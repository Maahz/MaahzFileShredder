#include<Windows.h>
#include<wincrypt.h>
#include "FileHandling.h"

using namespace std;

class settings
{
public:
    const static int m_overwrites = 3; //How many times the file is overwriten 
};

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

    //Write over file multiple times
    for (int i = 0; i < settings::m_overwrites; i++)
    {
        daFile.open(filename, std::fstream::binary);
        char* result = NewRandom(fileSize);//GetRandData((int64_t)fileSize);
        if (result == NULL)
            return 1;
        daFile << result;

        delete(result);                   //Freedom!!!!!!!!
        daFile.close();
    }
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

//Generate random data
char* FileHandling::NewRandom(const streamoff fileSize)
{
    char* data = new char[fileSize];

    for (int i = 0; i < fileSize - 1; i++)
    {
        data[i] = rand() % 9 + 1;
    }

    return data;
}

///Function to get pseudo random data for file overwriting
char* FileHandling::GetRandData(int64_t fileSize)
{
    /*
    DWORD dataSize = (DWORD)fileSize;
    HCRYPTPROV hProv = 0;                       //        !!!!!!POSSIBLE BUFFER OVERFLOW!!!!!!!!!!

    //char* data = (char*)malloc(sizeof(char) * dataSize);  //!!!!!!MAKE SURE DATA SIZE CANT BE TOO LARGE!!!!!!!!!!
    //char* data = new char();
    BYTE data[sizeof(char) * 4816] = {};
                                                          //Test that data isnt NULL...so that compiler wont get angry
    if (data == NULL) return (char*)"Error";


    if(!::CryptGenRandom(hProv, 4816, data))
    {
        return (char*)data;
    }
    else
    */
        return (char*)"Error\n";
}