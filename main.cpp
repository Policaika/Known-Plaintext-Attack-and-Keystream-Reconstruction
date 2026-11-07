#include <iostream>
#include <fstream>
#include <string>
#include "class.h"


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "Вы указали неверное количество аргументов" << std::endl;
        return -5;
    }
    std::string fileinput = argv[1];
    std::string fileoutput = argv[2];
    std::ifstream fint(fileinput);
    std::ofstream fout(fileoutput);

    if(!fint)
    {
        std::cerr << "Укажите верное название файла на вход" << std::endl;
        return -3;
    }

    if(!fout)
    {
        std::cerr << "Укажите верное название файла на выход" << std::endl;
        return -4;
    }

    Separator ObjSeparator(fint);
    WayToGamma ObjWayToGamma;
    CryptoKey ObjCryptoKey(ObjWayToGamma);
    ObjSeparator.SeparateInputNum(fint);
    ObjSeparator.HexToDec();
    ObjWayToGamma.GenerateCondidates();
    ObjCryptoKey.GetFirst128BitKey(ObjWayToGamma,ObjSeparator);
    ObjCryptoKey.GetAllBitKey(ObjSeparator);
    ObjCryptoKey.GetMessageInBits(ObjSeparator);
    ObjCryptoKey.SeparateMessage();

    int minute = ObjCryptoKey.CheckCorrectKey();
    if(minute == -1)
    {
        std::cerr << "Ключ не найден" << std::endl;
        return -6;
    }

    ObjCryptoKey.PrintMessage(fout);

    return 0;
}