<style>
    h1, .app-nav, .crisp-client {
        display: none;
    }
    #main {
        margin-top: -50px;
        max-width: 95%;
    }
</style>

<p style="font-size: 1.5rem;font-weight: 600">Windows 下配置 GMP</p>

在 Windows 上安装 C++ 编译器和 GMP 比较方便的方法是通过 MinGW Installer 安装，MinGW 是 Windows 版本的 GCC 和 GNU Binutils。

> [!TIP]
> MinGW Installer 下载地址：https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe

接着开始安装。需要注意的是，安装过程对网络环境要求较高（尽量避免使用中国移动宽带）。若网络连接失败，可以使用学校提供的 [VPN](http://openvpn.ustc.edu.cn/index.php) 或开启科学上网后再安装；若网络没有问题仍无法安装，可能是 MinGW Installer 的版本不是最新。

安装完成后，可以看到 MinGW Installer Manager 已经打开。

![](_images/lab-2-2.png ':class=image-90')

接着，在 *Basic Setup* 中勾选 mingw32-base-bin 和 mingw32-gcc-g++-bin，在 *MinGW Libraries* 中勾选 mingw32-gmp-dev、mingw32-gmp-dev-info 和 mingw32-gmp-dev-lic 并 Apply Changes，等待安装完成。

![](_images/lab-2-3.png ':class=image-49')
![](_images/lab-2-4.png ':class=image-49')

安装完成后设置环境变量：

![](_images/lab-2-5.png ':class=image-40')

接着测试以下代码：

```cpp
#include <gmp.h>

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

在命令行中编译并链接，`g++ gmpTest.cpp -lgmp -lm -o gmpTest`，再执行 exe 文件，可以看到如下输出：

![](_images/lab-2-7.png ':class=image-50')

> [!TIP]
> 头文件 `gmp.h` 支持纯 C 环境。而对于 C++ 来说，可以调用 `gmpxx.h`，它封装了 `mpz_class` 类，并在 `mpz_class` 中重载了一些运算符，使用更加方便，代码如下：
>
> ```cpp
> #include <gmpxx.h>
> #include <iostream>
> 
> using namespace std;
> 
> int main()
> {
>     mpz_class a("100");
>     mpz_class b("99");
>     cout << a + b << endl;
> 
>     return 0;
> }
> ```

> [!TIP]
> 如果在 IDE 中运行代码，记得在链接器（Linker）中添加 GMP 的库文件 `libgmp.dll.a;libgmpxx.dll.a`，以我所使用的 CodeLite 为例：
>
> ![](_images/lab-2-8.png ':class=image-90')
>
> 添加后，即可运行。
>
> ![](_images/lab-2-9.png ':class=image-40')

> GMP 的安装参考了 👉 [这篇文章](https://www.cnblogs.com/ECJTUACM-873284962/p/8350320.html)