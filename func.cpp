#include "class.h"

// Для Separator

void Separator::SeparateInputNum(std::ifstream& in)
{
    for(int i = 0; i<size; ++i)
    {
        in >> *(SeparateNum+i);
    }
}

void Separator::HexToDec()
{
    for(int i = 0; i<size; ++i)
    {
        if(*(SeparateNum+i) >= '0' && *(SeparateNum+i) <= '9')
        {
            *(SeparateNumAdditional+i) = *(SeparateNum+i) - '0';
        }
        else if(*(SeparateNum+i) >= 'A' && *(SeparateNum+i) <= 'F')
        {
            *(SeparateNumAdditional+i) = *(SeparateNum+i) - 'A' + 10;
        }
        else if(*(SeparateNum+i) >= 'a' && *(SeparateNum+i) <= 'f')
        {
            *(SeparateNumAdditional+i) = *(SeparateNum+i) - 'a' + 10;
        }
    }
}

unsigned char Separator::DecToBool(int condidate, int byte)
{ 
    int bytesize = size/2;
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
    for(int i = 0; i<60; ++i)
    {
        *(DateTimeString+i) = "2026-10-16T12:";
        if(i<10)
        {
            *(DateTimeString+i) += "0";
        }
        *(DateTimeString+i) += std::to_string(i);
    }
}

unsigned char WayToGamma::GetBits(int candidate, int byte)
{
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
    int count;
    int byte;
    for(int i = 0; i<size; ++i)
    {
        count = 0;
        byte = 0;
        for(int j = 0; j<128; ++j)
        {
            if(count == 8)
            {
                count = 0;
                ++byte;
            }
            *(KeyBits+i) += char('0' + (GammaObj.GetBits(i,j) ^ SeparatorObj.DecToBool(byte,count)));
            ++count;
        }
    }
}

void CryptoKey::GetAllBitKey(Separator& SeparatorObj)
{
    int temp_size = SeparatorObj.GetSize() * 4;
    for(int i = 0; i<size; ++i)
    {
        gamma[i] = KeyBits[i];
        gamma[i].resize(temp_size);
        for(int j = 0; j<temp_size-128; ++j)
        {
            gamma[i][j+128] = char('0' + (gamma[i][j] ^ gamma[i][j+1] ^ gamma[i][j+2] ^ gamma[i][j+7]));
        }
    }
}

void CryptoKey::GetMessageInBits(Separator& SeparatorObj)
{
    int count;
    int byte;
    int sizebyte = SeparatorObj.GetSize() * 4;
    for(int i = 0; i<size; ++i)
    {
        count = 0;
        byte = 0;
        text[i].resize(sizebyte);
        for(int j = 0; j<sizebyte; ++j)
        {
            if(count == 8)
            {
                count = 0;
                ++byte;
            }
            text[i][j] = char('0' + (SeparatorObj.DecToBool(byte,count) ^ gamma[i][j]));
            ++count;
        }
    }
}

void CryptoKey::SeparateMessage()
{
    
}