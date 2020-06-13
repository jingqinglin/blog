<style>
    h1, .app-nav, .crisp-client {
        display: none;
    }
    #main {
        margin-top: -50px;
        max-width: 95%;
    }
</style>

本实验拟采用 C++ 作为编程语言，并调用 Crypto++ 对 AES 进行基本实现。

> [!TIP]
> Crypto++ 下载地址：https://www.cryptopp.com/#download


由于 Crypto++ 的编译版本是使用 MSVC 构建的，我们用 Visual Studio 打开解决方案 cryptest.sln，并将 cryptlib 设为启动项目，然后按下 <kbd>Ctrl</kbd> + <kbd>B</kbd> 生成 cryptlib。此时路径 `./Win32/Output/Debug` 下会输出 cryptlib.lib 文件。

接着，新建一个项目测试可用性。

首先需要引入头文件和库文件：打开 `项目 - *** 属性 - VC++ 目录`，把 Crypto++ 头文件所在路径和先前输出的库文件路径分别添加到**包含目录**和**库目录**。

![](_images/lab-3-3.png)

然后在属性页的 `链接器 - 输入 - 附加依赖项` 中添加 cryptlib.lib。

![](_images/lab-3-4.png ':class=image-70')

最后，在属性页的 `C/C++ - 代码生成 - 运行库` 中选择 `多线程调试（/MTD）`。

![](_images/lab-3-5.png ':class=image-60')

运行测试代码：

```cpp
#include <iostream>
#include <aes.h>

using namespace std;
using namespace CryptoPP;

int main()
{
    cout << "Hello Crypto++" << endl;
    cout << "Aes block size is " << AES::BLOCKSIZE << endl;
    return 0;
}
```

并有如下输出：

```
Hello Crypto++
Aes block size is 16
```

> Crypto++ 的安装和使用参考了[这篇文章](https://blog.csdn.net/qq_32261191/article/details/78855651)