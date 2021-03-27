#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "default.h"

using namespace std;
using namespace CryptoPP;

string strToHex(const string& str)
{
    stringstream ss;
    ss << hex << setfill('0');

    for(auto ch : str)
    {
        ss << setw(2) << (int)(unsigned char)ch;
    }

    return ss.str();
}

string hexToStr(const string& hex)
{
    string str;

    for(string::size_type i = 0; i < hex.length(); i += 2)
    {
        string tempStr = hex.substr(i, 2);
        unsigned char ch = (unsigned char)stoi(tempStr, nullptr, 16);
        str.push_back(ch);
    }

    return str;
}

// 计数器自增
string counterIncrement(const string& counter, int n)
{
    string res = counter;
    int addend = n;

    for(int i = counter.length() - 1; i >= 0; i--)
    {
        unsigned char tempChar = counter[i];
        if((int)tempChar + addend > 255)
        {
            tempChar = tempChar + addend;
            addend = 1;
        }
        else
        {
            tempChar = tempChar + addend;
            addend = 0;
        }
        res[i] = tempChar;
    }
    return res;
}

string encrypt(const string& strPlaintext, const string& strKey, const string& strCounter)
{
    string ciphertext = strCounter;
    string key = hexToStr(strKey);
    string counter = hexToStr(strCounter);
    int multiple = strPlaintext.length() / AES::BLOCKSIZE;

    AESEncryption aesEncryptor;
    aesEncryptor.SetKey((byte*)key.c_str(), key.length());

    for(int i = 0; i < multiple; i++)
    {
        string plaintextBlock = strPlaintext.substr(i * AES::BLOCKSIZE, AES::BLOCKSIZE);
        string xorBlock;
        unsigned char outBlock[AES::BLOCKSIZE];
        memset(outBlock, 0, AES::BLOCKSIZE);

        aesEncryptor.ProcessBlock((byte*)counter.c_str(), outBlock);

        for(int j = 0; j < AES::BLOCKSIZE; j++)
        {
            xorBlock.push_back(outBlock[j] ^ (unsigned char)plaintextBlock[j]);
        }

        ciphertext += strToHex(xorBlock);
        counter = counterIncrement(counter, 1);
    }

    int residueLen = strPlaintext.length() - multiple * AES::BLOCKSIZE;
    string residuePlaintext = strPlaintext.substr(multiple * AES::BLOCKSIZE, residueLen);
    string xorBlock;
    unsigned char outBlock[AES::BLOCKSIZE];
    memset(outBlock, 0, AES::BLOCKSIZE);

    aesEncryptor.ProcessBlock((byte*)counter.c_str(), outBlock);

    for(int j = 0; j < residueLen; j++)
    {
        xorBlock.push_back(outBlock[j] ^ (unsigned char)residuePlaintext[j]);
    }

    ciphertext += strToHex(xorBlock);

    return ciphertext;
}

string decrypt(const string& strCiphertext, const string& strKey)
{
    string plaintext = "";
    string key = hexToStr(strKey);
    string ciphertext = hexToStr(strCiphertext);
    // 密文的前 16 个字节为计数器的初始值
    string counter = ciphertext.substr(0, AES::BLOCKSIZE);
    ciphertext = ciphertext.substr(AES::BLOCKSIZE, ciphertext.length() - AES::BLOCKSIZE);
    int multiple = ciphertext.length() / AES::BLOCKSIZE;

    AESEncryption aesEncryptor;
    aesEncryptor.SetKey((byte*)key.c_str(), key.length());

    for(int i = 0; i < multiple; i++)
    {
        string ciphertextBlock = ciphertext.substr(i * AES::BLOCKSIZE, AES::BLOCKSIZE);
        string xorBlock;
        unsigned char outBlock[AES::BLOCKSIZE];
        memset(outBlock, 0, AES::BLOCKSIZE);

        aesEncryptor.ProcessBlock((byte*)counter.c_str(), outBlock);

        // 密文和 AES 加密结果异或，得到明文
        for(int j = 0; j < AES::BLOCKSIZE; j++)
        {
            xorBlock.push_back(outBlock[j] ^ (unsigned char)ciphertextBlock[j]);
        }

        plaintext += xorBlock;
        // 计数器自增
        counter = counterIncrement(counter, 1);
    }

    // 最后的分组可能不完整，单独输出
    int residueLen = ciphertext.length() - multiple * AES::BLOCKSIZE;
    string residueCiphertext = ciphertext.substr(multiple * AES::BLOCKSIZE, residueLen);
    string xorBlock;
    unsigned char outBlock[AES::BLOCKSIZE];
    memset(outBlock, 0, AES::BLOCKSIZE);

    aesEncryptor.ProcessBlock((byte*)counter.c_str(), outBlock);

    for(int j = 0; j < residueLen; j++)
    {
        xorBlock.push_back(outBlock[j] ^ (unsigned char)residueCiphertext[j]);
    }

    plaintext += xorBlock;

    return plaintext;
}

int main(int argc, char** argv)
{
    string plaintext = "";
    string ciphertext = "69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88"
                        "d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329";
    string key = "36f18357be4dbd77f050515c73fcf9f2";
    string counter = "";

    plaintext = decrypt(ciphertext, key);
    cout << "plaintext: " << plaintext << endl;

    return 0;
}