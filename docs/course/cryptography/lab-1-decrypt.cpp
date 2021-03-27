#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 判断空格的门限值，可根据结果进行修改调整
const int THRESHOLD_VALUE = 5;
const int KEY_LENGTH = 400;
// 存储各条密文同一个位置的最大 count 值
static vector<int> countArray(KEY_LENGTH);

// 读取密文
void readText(const string& fileName, vector<string>& cip, string& targetCip)
{
    ifstream inFile(fileName);
    if(!inFile.is_open())
    {
        cout << "Can't open the file\n";
        exit(EXIT_FAILURE);
    }
    string temp;
    bool flag = false;
    while(getline(inFile, temp))
    {
        string::size_type idx = temp.find("Ciphertext");
        if(flag)
        {
            flag = false;
            cip.push_back(temp);
        }
        if(idx != string::npos)
        {
            flag = true;
        }
    }
    // 最后一条待解密的密文也放入 cip
    cip.push_back(temp);
    targetCip = temp;
}

int isAlphabet(int c)
{
    if(c >= 65 && c <= 90)
    {
        return 1;
    }
    if(c >= 97 && c <= 122)
    {
        return 1;
    }
    return 0;
}

int hexToDecimal(const string& hexStr)
{
    int decimal;
    stringstream ss;
    ss.str(hexStr);
    ss >> hex >> decimal;
    return decimal;
}

string decimalToHex(int decimal)
{
    stringstream ss;
    ss << hex << decimal;
    return ss.str();
}

// 计算可能的空格位置
vector<vector<int>> findSpace(vector<string>& ciphertext)
{
    vector<vector<int>> spacePos;

    // 对于给出的 10 条密文，计算对应明文中可能为空格的位置
    for(vector<int>::size_type i = 0; i != ciphertext.size(); i++)
    {
        string& cipher = ciphertext[i];
        string::size_type cipherLen = cipher.length();
        vector<int> space;

        // 每两个 16 进制字符代表明文的一个字符
        for(string::size_type j = 0; j < cipherLen; j = j + 2)
        {
            int tempI = hexToDecimal(cipher.substr(j, 2));
            int count = 0;

            // 位置 j 和 j + 1 上的字符与其余 10 条密文（包括待解密密文）该位置的字符进行异或
            for(vector<string>::size_type k = 0; k != ciphertext.size(); k++)
            {
                string& residueCipher = ciphertext[k];

                if(i == k || j > residueCipher.length())
                {
                    continue;
                }

                int tempK = hexToDecimal(residueCipher.substr(j, 2));
                // 若异或结果为字母，则 count++
                count += isAlphabet(tempI ^ tempK);
            }
            // 若超过 THRESHOLD_VALUE 条的异或结果为字母，那么我们可以认定这个位置对应的明文是空格
            if(count > THRESHOLD_VALUE)
            {
                space.push_back(j);
                // count 值越大，空格的可能性越大。存入位置 j 上最大的 count 和对应密文的序号，因为 j + 1
                // 位置是空的，刚好可以存密文的序号
                if(countArray[j] < count)
                {
                    countArray[j] = count;
                    countArray[j + 1] = i;
                }
            }
        }

        spacePos.push_back(space);
    }
    return spacePos;
}

// 计算密钥
vector<string> calculateKey(vector<string>& ciphertext)
{
    vector<string> key(KEY_LENGTH);
    vector<vector<int>> spacePos = findSpace(ciphertext);

    for(vector<string>::size_type i = 0; i != ciphertext.size(); i++)
    {
        string& cipher = ciphertext[i];
        vector<int>& space = spacePos[i];

        for(auto pos : space)
        {
            if(countArray[pos + 1] == (int)i)
            {
                // 该位置密文与空格进行异或，计算该位置的密钥
                // 32 是空格的 ASCII 码
                int k = 32 ^ hexToDecimal(cipher.substr(pos, 2));
                key[pos] = decimalToHex(k);
            }
        }
    }
    return key;
}

int main(int argc, char** argv)
{
    vector<string> ciphertext;
    string targetCiphertext;

    readText("./ciphertext.txt", ciphertext, targetCiphertext);

    vector<string> key = calculateKey(ciphertext);
    string message;

    // 解密目标密文
    for(string::size_type i = 0; i < targetCiphertext.length(); i = i + 2)
    {
        // 若对应位置上无密钥，则该位置统一放置 '0'
        if(key[i].empty())
        {
            message.push_back('0');
        }
        else
        {
            char m = hexToDecimal(targetCiphertext.substr(i, 2)) ^ hexToDecimal(key[i]);
            message.push_back(m);
        }
    }

    cout << message << endl;

    return 0;
}