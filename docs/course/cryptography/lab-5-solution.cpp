#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "default.h"
#include "filter.h"

using namespace std;
using namespace CryptoPP;

string strToHex(string str)
{
    stringstream ss;
    ss << hex << setfill('0');

    for(auto ch : str) {
        // setw(2) 占两位，setfill('0') 空位填充 0
        ss << setw(2) << (int)(unsigned char)ch;
    }

    return ss.str();
}

// 以下两种方法均可实现 SHA256
// string SHA256Hash(string data)
//{
//	string digest;
//	SHA256 hash;
//	StringSource ss(data, true, new HashFilter(hash, new StringSink(digest)));
//
//	return digest;
//}

string SHA256Hash(string data)
{
    int len = data.length();
    byte digest[SHA256::DIGESTSIZE];
    SHA256().CalculateDigest(digest, (byte*)data.c_str(), len);

    return string((char*)digest, SHA256::DIGESTSIZE);
}

bool verifyBlock(string blockTransferred, int blockNum, vector<string> hash)
{
    // blockTransferred 尾部带哈希
    return hash[blockNum] == SHA256Hash(blockTransferred);
}

vector<string> calculateHash(string fileName)
{
    ifstream file(fileName, ios::binary);
    streampos len;
    int blockNum;

    file.seekg(0, ios::end);
    len = file.tellg();
    blockNum = (int)len / 1024;
    vector<string> hash(blockNum + 1);

    if(file.is_open()) {
        int lastBlockLen = (int)len - blockNum * 1024;
        string block;
        block.resize(lastBlockLen);
        file.seekg((int)len - lastBlockLen);
        file.read(&block[0], lastBlockLen);
        hash[blockNum] = SHA256Hash(block);

        block.resize(1024);
        for(int i = blockNum - 1; i >= 0; i--) {
            int blockStart = i * 1024;
            file.seekg(blockStart);
            file.read(&block[0], 1024);
            hash[i] = SHA256Hash(block + hash[i + 1]);
        }
    } else {
        cout << "Can't open the file\n";
        exit(EXIT_FAILURE);
    }

    return hash;
}

string getH0(string fileName)
{
    return strToHex(calculateHash(fileName)[0]);
}

int main()
{
    string fileName = "lab-5-test.mp4";
    string h0 = getH0(fileName);
    cout << h0 << endl;
    return 0;
}