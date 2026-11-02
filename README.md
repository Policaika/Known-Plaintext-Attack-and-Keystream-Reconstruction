```C++
#include <iostream>
#include <fstream>
#include <string>

class WayToGamma
{
    private:
        size_t size;
        std::string* DateTimeString;
        std::string* DateTimeStringAdditional;
    public:
        WayToGamma()
        {
            DateTimeString = nullptr;
        }

        void GenerateCondidates();
        unsigned char GetBits(int, int);
        size_t GetSize();

        ~WayToGamma()
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
        unsigned char* BoolSeparatedNum;
        std::string* BoolSeparatedNumAdditional;
    public:
        Separator()
        {
            size = 0;
            SeparateNum = nullptr;
            SeparateNumAdditional = nullptr;
            BoolSeparatedNum = nullptr;
            BoolSeparatedNumAdditional = nullptr;
        }

        size_t SeparateNumF(std::ifstream&);
        void SeparateInputNum(std::ifstream&);
        void HexToDec(char*&);
        unsigned char DecToBool(int, int);
        size_t GetSize();

        ~Separator()
        {
            delete[] SeparateNum;
            delete[] SeparateNumAdditional;
            delete[] BoolSeparatedNum;
            delete[] BoolSeparatedNumAdditional;
            SeparateNum = nullptr;
            SeparateNumAdditional = nullptr;
            BoolSeparatedNum = nullptr;
            BoolSeparatedNumAdditional = nullptr;
        }
};

class CryptoKey
{
    private:
        size_t size;
        std::string* KeyBits;
        std::string* gamma;
        std::string* text;
    public:
        CryptoKey()
        {
            KeyBits = nullptr;
            gamma = new std::string[size];
            text = new std::string[size/2];
        }

        void GetFirst128BitKey(WayToGamma&, Separator&);
        void GetAllBitKey(Separator&, std::ifstream& in);
        void GetMessage(Separator&);

        ~CryptoKey()
        {
            delete[] KeyBits;
            delete[] gamma;
            KeyBits = nullptr;
            gamma = nullptr;
        }
};

#include "class.h"

// Для Separator

size_t Separator::SeparateNumF(std::ifstream& in)
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
    return size;
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

unsigned char Separator::DecToBool(int condidate, int byte)
{ 
    int bytesize = size/2;
    BoolSeparatedNum = new unsigned char[bytesize];                 //Выделение памяти перенести в конструктор!!!!!!!!!!!!!!!!!!!!!!!!!
    BoolSeparatedNumAdditional = new std::string[bytesize];
    for(int i = 0; i<bytesize; ++i)
    {
        int first = *(SeparateNumAdditional+i*2);
        int second = *(SeparateNumAdditional+i*2+1);
        *(BoolSeparatedNum+i) = first * 16 + second;
    }
    for(int i = 0; i<bytesize; ++i)
    {
        for(int j = 7; j>=0; --j)
        {
            int bit = (*(BoolSeparatedNum+i) >> j) & 1;
            if(bit == 0)
            {
                *(BoolSeparatedNumAdditional+i) += '0';
            }
            else if(bit == 1)
            {
                *(BoolSeparatedNumAdditional+i) += '1';
            }
        }
        
    }
    return BoolSeparatedNumAdditional[condidate][byte];
}

size_t Separator::GetSize()
{
    return size;
}


// Для WayToGamma

void WayToGamma::GenerateCondidates()
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

unsigned char WayToGamma::GetBits(int candidate, int byte)
{
    size = 60;
    DateTimeStringAdditional = new std::string[size];
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
    return DateTimeStringAdditional[candidate][byte];
}

size_t WayToGamma::GetSize()
{
    return size;
}

// Для CryproKey

void CryptoKey::GetFirst128BitKey(WayToGamma& GammaObj, Separator& SeparatorObj)
{
    size = GammaObj.GetSize();
    KeyBits = new std::string[size];
    gamma = new std::string[size];
    int count = 0;
    int byte = 0;
    for(int i = 0; i<size; ++i)
    {
        if(byte = 16)
        {
            byte = 0;
        }
        for(int j = 0; j<128; ++j)
        {
            if(count = 8)
            {
                count = 0;
            }
            *(KeyBits+i) = GammaObj.GetBits(i,j) ^ SeparatorObj.DecToBool(byte,count);
            ++count;
        }
        ++byte;
    }
}

void CryptoKey::GetAllBitKey(Separator& SeparatorObj, std::ifstream& in)
{
    int temp_size = SeparatorObj.GetSize() * 4;
    for(int i = 0; i<size; ++i)
    {
        for(int j = 0; j<128; ++j)
        {
            gamma[i][j] = KeyBits[i][j];
        }
        gamma[i].resize(temp_size);
        for(int j = 0; j<temp_size-128; ++j)
        {
            gamma[i][j+128] = gamma[i][j] ^ gamma[i][j+1] ^ gamma[i][j+2] ^ gamma[i][j+7];
        }
    }
}

void CryptoKey::GetMessage(Separator& SeparatorObj)
{
    int sizebyte = size/2;
    for(int i = 0; i<size; ++i)
    {
        for(int j = 0; j<sizebyte; ++j)
        {
            text[i][j] ^= gamma[i][j];
        }
    }
}

#include <iostream>
#include <fstream>
#include <string>
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
