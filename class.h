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