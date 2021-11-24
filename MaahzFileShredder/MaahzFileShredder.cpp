//----------------------------------------------------
// Project: MaahzFileShredder
// Author: Markku Sjöblom
// Date: 20.11.2021
// 
// Description:
// Secure file deleteion program that 
// overwrites files before deleting them.
//
//----------------------------------------------------

#include <iostream>
#include <stdio.h>
#include "FileHandling.h"
#include "Log.h"


using namespace std;

FileHandling FileHandler;
Log LogHandler;

//-----TODO------
// -Add functionality to remove file after overwrite
//
//---------------


const int _sanityCheck = 0;  //Check if user really does want to remove file

void sanityCheck(char* fileName)
{
    cout << "You are about to overwrite\n" << fileName << "\nPress ENTER to continue" << endl;
    cin.get();
}

int main(int argc, char *argv[])
{
    enum PathLenght
    {
        Minimum = 0,
        MaximumLenght = sizeof(char) * 50

    };

    //Error checking
    if (argv[1] == NULL)
    {
        cout << "Error! No file specified" << endl;
        return 1;
    }


    streamoff fileSize = 0;
    char* fileName = argv[1];
    if (_sanityCheck)
        sanityCheck(fileName);

    //make sure user doesnt pass a book into this fuction as command line argument.
    if (strnlen_s(argv[1], MaximumLenght) > 0 && strnlen_s(argv[1], MaximumLenght) <= 50)
    {
        fileName = argv[1];
        fileSize = FileHandler.filesize(fileName);  //Get the file size
    }

    if (fileName != "" && fileName != NULL)
    {
        //Return error if file doesnt exist
        if (FileHandler.Overwrite(fileName, fileSize))
        {
            LogHandler.Error((char*)"ERROR!File doesn't exist or is inaccessible.");
            return 1;
        }
    }
    else
    {
        LogHandler.Error((char*)"ERROR!No file specified.");
        return 1;
    }
    
    return 0;
}




