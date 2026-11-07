#include <fstream>
#include <string>

class WayToGamma
{
    private:
        size_t size;
        std::string* DateTimeString;
        std::string* DateTimeStringAdditional;
    public:
        WayToGamma() : size(60)
        {
            DateTimeString = new std::string[size];
            DateTimeStringAdditional = new std::string[size];
        }

        void GenerateCondidates();
        unsigned char GetBits(int, int);
        size_t GetSize();

        ~WayToGamma()
        {
            delete[] DateTimeString;
            delete[] DateTimeStringAdditional;
            DateTimeString = nullptr;
            DateTimeStringAdditional = nullptr;
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
        Separator(std::ifstream& in)
        {
            char size_mass;
            size = 0;
            while(in.get(size_mass))
            {
                if(size_mass != ' ')
                {
                    ++size;
                }
            }
            in.clear();
            in.seekg(0);
            SeparateNum = new char[size];
            SeparateNumAdditional = new std::size_t[size];
            BoolSeparatedNum = new unsigned char[size];
            BoolSeparatedNumAdditional = new std::string[size/2];
        }

        void SeparateInputNum(std::ifstream&);
        void HexToDec();
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
        CryptoKey(WayToGamma& GammaObj)
        {
            size = GammaObj.GetSize();
            KeyBits = new std::string[size];
            text = new std::string[size];
            gamma = new std::string[size];
        }

        void GetFirst128BitKey(WayToGamma&, Separator&);
        void GetAllBitKey(Separator&);
        void GetMessageInBits(Separator&);
        void SeparateMessage();

        ~CryptoKey()
        {
            delete[] text;
            delete[] KeyBits;
            delete[] gamma;
            KeyBits = nullptr;
            gamma = nullptr;
        }
};