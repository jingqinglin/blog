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

    for(string::size_type i = 0; i < str.size(); i++) {
        ss << hex << (int)(unsigned char)str[i];
    }

    return ss.str();
}

string hexToStr(string hexStr)
{
    string str;

    for(string::size_type i = 0; i < hexStr.size(); i = i + 2) {
        stringstream ss;
        string tempHexStr = hexStr.substr(i, 2);
        int tempDecimal;
        ss.str(tempHexStr);
        ss >> hex >> tempDecimal;
        str.push_back((char)tempDecimal);
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
    string strCipher =
        hexToStr("770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451");
    string strKey = hexToStr("36f18357be4dbd77f050515c73fcf9f2");
    string strResult;
    string strErrMsg;
    string strPlainText;

    int keyLen = strKey.length();
    strIv = strCipher.substr(0, keyLen);
    strCipher = strCipher.substr(16, strCipher.length() - keyLen);

    int statusCode = decryptAesCtr(strCipher, strKey, strPlainText, strErrMsg);
    if(statusCode) {
        cout << "Decrypt failed, errMsg: " << strErrMsg;
        return -2;
    }

    cout << "PlainText: " << strPlainText << endl;
}
