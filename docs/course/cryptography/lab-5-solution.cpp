#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "default.h"
#include "filter.h"

using namespace std;
using namespace CryptoPP;

string strToHex(const string& str)
{
    stringstream ss;
    ss << hex << setfill('0');

    for(auto ch : str)
    {
        // setw(2) 占两位，setfill('0') 空位填充 0
        ss << setw(2) << (int)(unsigned char)ch;
    }

    return ss.str();
}

// 以下两种方法均可实现 SHA256
// string SHA256Hash(const string& data)
//{
//	string digest;
//	SHA256 hash;
//	StringSource ss(data, true, new HashFilter(hash, new StringSink(digest)));
//
//	return digest;
//}

string SHA256Hash(const string& data)
{
    int len = data.length();
    byte digest[SHA256::DIGESTSIZE];
    SHA256().CalculateDigest(digest, (byte*)data.c_str(), len);

    return string((char*)digest, SHA256::DIGESTSIZE);
}

// 本地读取文件代替文件下载过程
bool verifyVideo(const string& fileTransferred, const vector<string>& hash)
{
    ifstream file(fileTransferred, ios::binary);
    streampos len;
    int blockNum;

    file.seekg(0, ios::end);
    len = file.tellg();
    blockNum = (int)len / 1024;

    if(file.is_open())
    {
        string blockTransferred;
        blockTransferred.resize(1024);

        for(int i = 0; i < blockNum; i++)
        {
            int blockStart = i * 1024;
            file.seekg(blockStart);
            file.read(&blockTransferred[0], 1024);
            // 验证 h[i] == sha256(block[i] + h[i + 1])
            if(hash[i] != SHA256Hash(blockTransferred + hash[i + 1]))
            {
                cout << "Block " << i << " transmission error." << endl;
                return false;
            }
        }

        int lastBlockLen = (int)len - blockNum * 1024;
        blockTransferred.resize(lastBlockLen);
        file.seekg((int)len - lastBlockLen);
        file.read(&blockTransferred[0], lastBlockLen);
        if(hash[blockNum] != SHA256Hash(blockTransferred))
        {
            cout << "Block " << blockNum << " transmission error." << endl;
            return false;
        }
    }
    else
    {
        cout << "Can't open the file\n";
        exit(EXIT_FAILURE);
    }

    cout << "Transmission complete." << endl;
    return true;
}

vector<string> calculateHash(const string& fileName)
{
    ifstream file(fileName, ios::binary);
    streampos len;
    int blockNum;

    file.seekg(0, ios::end);
    len = file.tellg();
    blockNum = (int)len / 1024;
    vector<string> hash(blockNum + 1);

    if(file.is_open())
    {
        int lastBlockLen = (int)len - blockNum * 1024;
        string block;
        block.resize(lastBlockLen);
        file.seekg((int)len - lastBlockLen);
        file.read(&block[0], lastBlockLen);
        hash[blockNum] = SHA256Hash(block);

        block.resize(1024);
        for(int i = blockNum - 1; i >= 0; i--)
        {
            int blockStart = i * 1024;
            file.seekg(blockStart);
            file.read(&block[0], 1024);
            hash[i] = SHA256Hash(block + hash[i + 1]);
        }
    }
    else
    {
        cout << "Can't open the file\n";
        exit(EXIT_FAILURE);
    }

    return hash;
}

string getH0(const string& fileName, vector<string>& hash)
{
    hash = calculateHash(fileName);
    return strToHex(hash[0]);
}

int main()
{
    string fileName = "lab-5-video.mp4";
    vector<string> hash;
    string h0 = getH0(fileName, hash);
    cout << h0 << endl;
    verifyVideo(fileName, hash);
    return 0;
}