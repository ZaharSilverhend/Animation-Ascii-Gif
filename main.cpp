#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <commdlg.h>

int main()
{
    setlocale(LC_ALL, "rus");

    OPENFILENAMEA ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = sizeof(szFileName);
    ofn.Flags = OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
    {
        std::string path = ofn.lpstrFile;

        std::string str, line;
        std::vector<std::string> arr;
        std::ifstream file(path);

        if (file.is_open()) {
            std::getline(file, str, '\0');
            file.close();

            for (size_t i = 0; i < str.length() - 3; i++)
            {
                if (str[i] != '\\' && str[i + 1] != 'f')
                {
                    line += str[i];
                }
                else
                {
                    i = i + 2;
                    arr.push_back(line);
                    line = "";
                }
            }

            for (size_t i = 0; i < arr.size(); i++)
            {
                std::cout << arr[i];
                printf("\x1b[H");
            }
        }
        else {
            std::cout << "Error opening file!!!";
        }
    }
    else {
        std::cout << "File dialog canceled!";
    }

    return 0;
}