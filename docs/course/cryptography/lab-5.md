?> 视频大文件验证

## 实验内容

> 【时间】6 月 20 号（周六）晚上
> 
> 【地点】待定
> 
> 【编程语言】Python（推荐）或者 C/C++
>
> 【实验目的】
> 1. 掌握数据完整性、哈希函数、MAC 等概念；
> 2. 了解如何使用 MAC 来确保数据的完整性；
> 3. 通过使用 Python（推荐）或者 C，利用 SHA-256 对视频大文件进行认证，学习如何使用哈希链来的实现大文件的分块认证。
>
> 【实验内容】
> 实验内容和要求请见附件 [EXP5-Doc.pdf](course/cryptography/lab-5-EXP5-Doc.pdf ':ignore')

## 实验准备

本实验拟采用 C++ 作为编程语言。同实验三，本实验也需要配置 Crypto++ 库，详细配置过程见[实验三](course/cryptography/lab-3?id=实验准备)相应部分或以下网页片段。

[实验二配置 GMP](https://jingqinglin.github.io/Blog/#/course/cryptography/cryptopp-config ':include :type=iframe width=100% height=600px')

## 实验分析

> [!NOTE|label:实验要求]
> 编码计算 [video.mp4](course/cryptography/lab-5-video.mp4 ':ignore') 的哈希值 $h_0$，并完成对文件块的验证过程。
>
> 要求不计算整个文件的散列值，而是将文件分成 1 KB 的块。首先计算最后一个块的哈希值，并将值附加到倒数第二个块末尾。然后，计算扩充后的倒数第二个块的哈希值，并将结果哈希值追加到第三个块的末尾。以此类推，直到处理完所有的块，如下图所示：
>
> ![](_images/lab-5-1.png ':class=image-60')

按照 PDF 中给出的要求以及实现思路，写出以下代码片段：

```cpp
// 调用 Crypto++ 库实现 SHA-256
string SHA256Hash(string data)
{
    int len = data.length();
    byte digest[SHA256::DIGESTSIZE];
    SHA256().CalculateDigest(digest, (byte*)data.c_str(), len);

    return string((char*)digest, SHA256::DIGESTSIZE);
}

vector<string> calculateHash(string fileName)
{
    // 二进制模式读取
    ifstream file(fileName, ios::binary);
    int len;
    int blockNum;

    // 定位到文件末尾并得到文件长度
    file.seekg(0, ios::end);
    len = file.tellg();
    blockNum = len / 1024;
    vector<string> hash(blockNum + 1);

    if(file.is_open()) {
        // 最后一个块单独处理
        int lastBlockLen = len - blockNum * 1024;
        string block;
        block.resize(lastBlockLen);
        // 定位到最后一块的起始位置并输入到 block
        file.seekg(len - lastBlockLen);
        file.read(&block[0], lastBlockLen);
        hash[blockNum] = SHA256Hash(block);

        // 倒序处理其他块
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
```

> [!NOTE]
> 在按照正确的思路编码后，一直没有算对 [test.mp4](course/cryptography/lab-5-test.mp4 ':ignore') 的 $h_0$。调试后发现源文件没有被正确地输到变量中，原因是没有以二进制模式打开文件。默认情况下，文件以文本模式被打开，这种情况下可能会发生字符转换，例如将回车转换为新的一行。但是，在二进制模式下不会发生这样的字符转换。因此定义输入文件流时需要加上参数 `ios::binary`。

完整代码 👉 [传送门](course/cryptography/lab-5-solution ':target=_blank')。

## 实验结果

运行完整代码，可得到 video.mp4 的 $h_0$ 为：

```
5b96aece304a1422224f9a41b228416028f9ba26b0d1058f400200f06a589949
```

> [!NOTE|label:参考]
>
> https://stackoverflow.com/questions/18009287/get-file-content-from-specific-position-to-another-specific-position  
> https://blog.csdn.net/sffofn/article/details/5062094  
> https://books.google.com.hk/books?id=uI7BZgKPvO8C&pg=PA483#v=onepage&q&f=false