#include <iostream>
#include <sstream>
#include <string>

#include "default.h"

using namespace std;
using namespace CryptoPP;

// https://www.cnblogs.com/YZFHKMS-X/p/11829021.html
string strToHex(string str)
{
    const string hex = "0123456789abcdef";
    stringstream ss;

    for(string::size_type i = 0; i < str.length(); ++i) {
        ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf];
    }

    return ss.str();
}

string hexToStr(string hexStr)
{
    string str;

    for(string::size_type i = 0; i < hexStr.length(); i = i + 2) {
        stringstream ss;
        string tempHexStr = hexStr.substr(i, 2);
        int tempDecimal;
        ss.str(tempHexStr);
        ss >> hex >> tempDecimal;
        str.push_back((char)tempDecimal);
    }

    return str;
}

// 填充
string padding(string plaintext)
{
    string lastBlock;
    int len = plaintext.length();
    int paddingNum = AES::BLOCKSIZE - len % AES::BLOCKSIZE;
    int quotient = len / AES::BLOCKSIZE;

    lastBlock = plaintext.substr(AES::BLOCKSIZE * quotient, len % AES::BLOCKSIZE);
    for(int i = 0; i < AES::BLOCKSIZE - len % AES::BLOCKSIZE; i++) {
        lastBlock.push_back((char)paddingNum);
    }

    return plaintext.substr(0, AES::BLOCKSIZE * quotient) + lastBlock;
}

string encrypt(string plaintext, string key, string vi, string ciphertext)
{
    plaintext = padding(plaintext);
    ciphertext += vi;
    key = hexToStr(key);
    vi = hexToStr(vi);
    int multiple = plaintext.length() / AES::BLOCKSIZE;

    AESEncryption aesEncryptor;
    aesEncryptor.SetKey((byte*)key.c_str(), key.length());

    for(int i = 0; i < multiple; i++) {
        string plaintextBlock = plaintext.substr(i * AES::BLOCKSIZE, AES::BLOCKSIZE);
        string xorBlock;
        unsigned char outBlock[AES::BLOCKSIZE];
        memset(outBlock, 0, AES::BLOCKSIZE);

        for(int j = 0; j < AES::BLOCKSIZE; j++) {
            xorBlock.push_back(plaintextBlock[j] ^ vi[j]);
        }

        aesEncryptor.ProcessBlock((byte*)xorBlock.c_str(), outBlock);
        vi = "";

        // unsigned char[] 转 string 不要通过这个方式：vi = (char *) outBlock
        for(int j = 0; j < AES::BLOCKSIZE; j++) {
            vi.push_back(outBlock[j]);
        }
        vi = vi.substr(0, AES::BLOCKSIZE);
        ciphertext += strToHex(vi);
    }

    return ciphertext;
}

string decrypt(string ciphertext, string key, string plaintext)
{
    // 原始 key 为 16 进制形式，需按字节转换为 char
    key = hexToStr(key);
    ciphertext = hexToStr(ciphertext);
    // 密文的前 16 个字节为 vi
    string vi = ciphertext.substr(0, AES::BLOCKSIZE);
    ciphertext = ciphertext.substr(AES::BLOCKSIZE, ciphertext.length() - AES::BLOCKSIZE);
    int multiple = ciphertext.length() / AES::BLOCKSIZE;

    AESDecryption aesDecryptor;
    aesDecryptor.SetKey((byte*)key.c_str(), key.length());

    for(int i = 0; i < multiple; i++) {
        // 密文分组
        string ciphertextBlock = ciphertext.substr(i * AES::BLOCKSIZE, AES::BLOCKSIZE);
        unsigned char outBlock[AES::BLOCKSIZE];
        memset(outBlock, 0, AES::BLOCKSIZE);

        // AES 加密函数
        aesDecryptor.ProcessBlock((byte*)ciphertextBlock.c_str(), outBlock);

        // AES 输出结果与上组密文或 vi 异或，得到明文
        for(int j = 0; j < AES::BLOCKSIZE; j++) {
            plaintext.push_back(outBlock[j] ^ vi[j]);
        }

        vi = ciphertextBlock;
    }

    // 解密后，最后一组明文单独处理
    string lastBlock = plaintext.substr((multiple - 1) * AES::BLOCKSIZE, AES::BLOCKSIZE);
    // 从字符串最后一个字符获取填充字符
    int paddingNum = (char)lastBlock[AES::BLOCKSIZE - 1];

    // 把填充字符从明文中去掉
    for(int i = 0; i < paddingNum; i++) {
        // 若填充字符出现不同，则说明给定密文有误
        if(plaintext.back() != paddingNum) {
            return "Ciphertext is invalid!";
        }
        plaintext.pop_back();
    }

    return plaintext;
}

int main(int argc, char** argv)
{
    string plaintext = "";
    string ciphertext = "4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1d"
                        "aafb94ffe0c5da05d9476be028ad7c1d81";
    string key = "140b41b22a29beb4061bda66b6747e14";
    string vi = "";

    plaintext = decrypt(ciphertext, key, plaintext);

    cout << "plaintext: " << plaintext << endl;

    return 0;
}
