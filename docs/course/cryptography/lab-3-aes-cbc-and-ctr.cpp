#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "aes.h"
#include "default.h"

using namespace std;
using namespace CryptoPP;

enum AESKeyLength { AES_KEY_LENGTH_16 = 16, AES_KEY_LENGTH_24 = 24, AES_KEY_LENGTH_32 = 32 };

string strIv;

string strToHex(string str)
{
    stringstream ss;
    ss << hex << setfill('0');

    for(auto ch : str) {
        ss << setw(2) << (int)(unsigned char)ch;
    }

    return ss.str();
}

string hexToStr(string hex)
{
    string str;

    for(string::size_type i = 0; i < hex.length(); i += 2) {
        string tempStr = hex.substr(i, 2);
        // string to int
        unsigned char ch = (unsigned char)stoi(tempStr, nullptr, 16);
        str.push_back(ch);
    }

    return str;
}

int encryptAesCbc(const string& inData, const string& strKey, string& outData, string& errMsg)
{
    outData = "";
    errMsg = "";

    if(inData.empty() || strKey.empty()) {
        errMsg = "indata or key is empty!!";
        return -1;
    }

    unsigned int keyLen = strKey.length();

    if(keyLen != AES_KEY_LENGTH_16 && keyLen != AES_KEY_LENGTH_24 && keyLen != AES_KEY_LENGTH_32) {
        errMsg = "aes key invalid!!";
        return -2;
    }

    byte* iv = (byte*)strIv.c_str();
    int statusCode = 0;

    try {
        CBC_Mode<AES>::Encryption e;
        e.SetKeyWithIV((byte*)strKey.c_str(), keyLen, iv);
        StringSource ss(inData, true, new StreamTransformationFilter(e, new StringSink(outData)));
    } catch(const CryptoPP::Exception& e) {
        errMsg = "Encryptor throw exception!!";
        statusCode = -3;
    }

    return statusCode;
}

int decryptAesCbc(const string& inData, const string& strKey, string& outData, string& errMsg)
{
    outData = "";
    errMsg = "";

    if(inData.empty() || strKey.empty()) {
        errMsg = "indata or key is empty!!";
        return -1;
    }

    unsigned int keyLen = strKey.length();

    if(keyLen != AES_KEY_LENGTH_16 && keyLen != AES_KEY_LENGTH_24 && keyLen != AES_KEY_LENGTH_32) {
        errMsg = "aes key invalid!!";
        return -2;
    }

    byte* iv = (byte*)strIv.c_str();
    int statusCode = 0;

    try {
        CBC_Mode<AES>::Decryption d;
        d.SetKeyWithIV((byte*)strKey.c_str(), keyLen, iv);
        StringSource ss(inData, true, new StreamTransformationFilter(d, new StringSink(outData)));
    } catch(const CryptoPP::Exception& e) {
        errMsg = "Decryptor throw exception";
        statusCode = -3;
    }

    return statusCode;
}

int encryptAesCtr(const string& inData, const string& strKey, string& outData, string& errMsg)
{
    outData = "";
    errMsg = "";

    if(inData.empty() || strKey.empty()) {
        errMsg = "indata or key is empty!!";
        return -1;
    }

    unsigned int keyLen = strKey.length();

    if(keyLen != AES_KEY_LENGTH_16 && keyLen != AES_KEY_LENGTH_24 && keyLen != AES_KEY_LENGTH_32) {
        errMsg = "aes key invalid!!";
        return -2;
    }

    byte* iv = (byte*)strIv.c_str();
    int statusCode = 0;

    try {
        CTR_Mode<AES>::Encryption e;
        e.SetKeyWithIV((byte*)strKey.c_str(), keyLen, iv);
        StringSource ss(inData, true, new StreamTransformationFilter(e, new StringSink(outData)));
    } catch(const CryptoPP::Exception& e) {
        errMsg = "Encryptor throw exception!!";
        statusCode = -3;
    }

    return statusCode;
}

int decryptAesCtr(const string& inData, const string& strKey, string& outData, string& errMsg)
{
    outData = "";
    errMsg = "";

    if(inData.empty() || strKey.empty()) {
        errMsg = "indata or key is empty!!";
        return -1;
    }

    unsigned int keyLen = strKey.length();

    if(keyLen != AES_KEY_LENGTH_16 && keyLen != AES_KEY_LENGTH_24 && keyLen != AES_KEY_LENGTH_32) {
        errMsg = "aes key invalid!!";
        return -2;
    }

    byte* iv = (byte*)strIv.c_str();
    int statusCode = 0;

    try {
        CTR_Mode<AES>::Decryption d;
        d.SetKeyWithIV((byte*)strKey.c_str(), keyLen, iv);
        StringSource ss(inData, true, new StreamTransformationFilter(d, new StringSink(outData)));
    } catch(const CryptoPP::Exception& e) {
        errMsg = "Decryptor throw exception";
        statusCode = -3;
    }

    return statusCode;
}

int main(int argc, char** argv)
{
    string strCipher = hexToStr("4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c68"
                                "22236e1daafb94ffe0c5da05d9476be028ad7c1d81");
    string strKey = hexToStr("140b41b22a29beb4061bda66b6747e14");
    string strErrMsg;
    string strPlainText;

    int keyLen = strKey.length();
    strIv = strCipher.substr(0, keyLen);
    strCipher = strCipher.substr(16, strCipher.length() - keyLen);

    int statusCode = decryptAesCbc(strCipher, strKey, strPlainText, strErrMsg);
    if(statusCode) {
        cout << "Decrypt failed, errMsg: " << strErrMsg;
        return -2;
    }

    cout << strPlainText << endl;

    return 0;
}
