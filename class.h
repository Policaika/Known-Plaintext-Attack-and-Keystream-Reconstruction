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