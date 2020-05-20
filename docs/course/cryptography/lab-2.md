?> 离散对数求解

## 实验内容

> 【时间】5 月 30 号（周六）晚上
> 
> 【编程语言】Python（推荐）或者 C/C++
> 
> 【实验目的】
> 
> 1. 掌握与密码学相关的基础数论知识；
> 2. 通过使用 Python（推荐）或者 C，利用中间相遇攻击来编程实现离散对数的求解。
>  
> 【实验内容】
> 实验内容和要求请见附件 [EXP2-Doc.pdf](course/cryptography/lab-2-EXP2-Doc.pdf ':ignore')

## 实验准备

本实验拟采用 C++ 作为编程语言，而实验需要支持多精度和模运算的环境，因此需要配置 [GNU 多重精度运算库](https://gmplib.org/)（GNU Multiple Precision Arithmetic Library，简称 GMP 或 gmpal）。

### Windows 下配置 GMP

在 Windows 上安装 C++ 编译器和 GMP 比较方便的方法是通过 MinGW Installer 安装，MinGW 是 Windows 版本的 GCC 和 GNU Binutils。

> [!TIP]
> MinGW Installer 的下载地址：https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe

接着开始安装。需要注意的是，安装过程需要保持网络通畅（尽量避免使用移动宽带，挂学校 VPN 或梯子开全局代理都可），若网络没有问题仍无法安装，可能是 MinGW Installer 的版本不是最新。

安装完成后，可以看到 MinGW Installer Manager 已经打开。

![](_images/lab-2-2.png ':class=image-90')

接着，在 Basic Setup 中勾选 mingw32-base-bin 和 mingw32-gcc-g++-bin，在 MinGW Libraries 中勾选 mingw32-gmp-dev/info/lic 并 Apply Changes，等待安装完成。

![](_images/lab-2-3.png ':class=image-45')
![](_images/lab-2-4.png ':class=image-45')

安装完成后设置环境变量：

![](_images/lab-2-5.png ':class=image-40')

接着测试以下代码：

```cpp
#include <gmp.h>
#include <iostream>

using namespace std;

int main()
{
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);
    mpz_set_ui(a, 100);
    mpz_set_ui(b, 99);
    mpz_t c;
    mpz_init(c);
    mpz_add(c, a, b);
    gmp_printf("%Zd\n", c);
    return 0;
}
```

在命令行中编译并链接，`g++ gmpTest.cpp -lgmp -lm -o gmpTest`，最后执行 exe 文件，可以看到如下输出：

![](_images/lab-2-7.png ':class=image-50')

> [!TIP]
> 如果在 IDE 中运行代码，记得在链接器（Linker）中添加 GMP 的库文件 `libgmp.dll.a;libgmpxx.dll.a`，以我所使用的 CodeLite 为例：
>
> ![](_images/lab-2-8.png ':class=image-90')
>
> 添加后，即可运行。
>
> ![](_images/lab-2-9.png ':class=image-50')

> GMP 的安装参考了 👉 [这篇文章](https://www.cnblogs.com/ECJTUACM-873284962/p/8350320.html)