#include <iostream>
#include <fstream>
#include <string>
#include "ciphertext.txt"


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "Вы указали неверное количество аргументов" << std::endl;
    }
    std::string fileinput = argv[1];
    std::string fileoutput = argv[2];
    std::ifstream fint(fileinput);
    std::ofstream fout(fileoutput);

    if(!fint)
    {
        std::cerr << "Укажите верное название файла на вход" << std::endl;
    }

    if(!fout)
    {
        std::cerr << "Укажите верное название файла на выход" << std::endl;
    }

    return 0;
}