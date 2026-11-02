```C++
#include <iostream>
#include <fstream>

class Gamma
{
    private:
        size_t size;
        std::string* DateTimeString;
        std::string* DateTimeStringAdditional;
        size_t* DateTimeBits;
    public:
        Gamma()
        {
            DateTimeString = nullptr;
        }

        void GenerateCondidates();
        void GetBits();

        ~Gamma()
        {
            delete[] DateTimeString;
            DateTimeString = nullptr;
        }
};

class Separator
{
    private:
        size_t size;
        char* SeparateNum;
        std::size_t* SeparateNumAdditional;
        std::size_t* BoolSeparatedNum;
    public:
        Separator()
        {
            size = 0;
            SeparateNum = nullptr;
            SeparateNumAdditional = nullptr;
            BoolSeparatedNum = nullptr;
        }

        void SeparateNumF(std::ifstream&);
        void SeparateInputNum(std::ifstream&);
        void HexToDec(char*&);
        void DecToBool(char*&, char*&);
        void Print();

        ~Separator()
        {
            delete[] SeparateNum;
            delete[] SeparateNumAdditional;
            delete[] BoolSeparatedNum;
            SeparateNum = nullptr;
            SeparateNumAdditional = nullptr;
            BoolSeparatedNum = nullptr;
        }
};

class CryptoKey
{
    private:
        char* KeyBits;
    public:
        CryptoKey()
};

#include "class.h"

// Для Separator

void Separator::SeparateNumF(std::ifstream& in)
{
    char temp_variable;
    size_t count = 0;
    while(in.get(temp_variable))
    {
        if(temp_variable != ' ')
        {
            ++count;
        }
    }
    size = count;
}

void Separator::SeparateInputNum(std::ifstream& in)
{
    SeparateNum = new char[size];
    for(int i = 0; i<size; ++i)
    {
        in >> *(SeparateNum+i);
    }
}

void Separator::HexToDec(char*& massive)
{
    SeparateNumAdditional = new std::size_t[size];
    for(int i = 0; i<size; ++i)
    {
        if(*(massive+i) >= '0' && *(massive+i) <= '9')
        {
            *(SeparateNumAdditional+i) = *(massive+i) - '0';
        }
        else if(*(massive+i) >= 'A' && *(massive+i) <= 'F')
        {
            *(SeparateNumAdditional+i) = *(massive+i) - 'A' + 10;
        }
        else if(*(massive+i) >= 'a' && *(massive+i) <= 'f')
        {
            *(SeparateNumAdditional+i) = *(massive+i) - 'a' + 10;
        }
    }
}

void Separator::DecToBool(char*& AdditionalSeparate, char*& BoolSeparate)
{
    int bytesize = size/2;
    AdditionalSeparate = new char[bytesize];
    for(int i = 0; i<bytesize; ++i)
    {
        int first = *(AdditionalSeparate+i*2);
        int second = *(AdditionalSeparate+i*2+1);
        *(BoolSeparate+i) = first * 16 + second;
    } // Переписать под char, см GetBits

}


// Для Gamma

void Gamma::GenerateCondidates()
{
    size = 60;
    DateTimeString = new std::string[size];
    for(int i = 0; i<60; ++i)
    {
        *(DateTimeString+i) = "2026-10-16T";
        if(i<10)
        {
            *(DateTimeString+i) += "0";
        }
        *(DateTimeString+i) += std::to_string(i);
    }
}

void Gamma::GetBits()
{
    size = 60;
    DateTimeStringAdditional = new std::string[size];
    DateTimeBits = new size_t[size];
    for(int i = 0; i<size; ++i)
    {
        std::string temp_string_variable = *(DateTimeString+i);
        for(std::string::iterator it = temp_string_variable.begin(); it != temp_string_variable.end(); ++it)
        {
            char byte = static_cast<char>(*it);
            for(int j = 7; j>=0; --j)
            {
                int bit = (byte >> j) & 1;
                if(bit == 0)
                {
                    *(DateTimeStringAdditional+i) += "0";
                }
                else if(bit == 1)
                {
                    *(DateTimeStringAdditional+i) += "1";
                }
            }
        }
    }
}

#include <iostream>
#include <fstream>
#include <string>
#include "ciphertext.txt"
#include "class.h"


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
}```
