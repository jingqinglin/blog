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

> [!TIP|label:MinGW Installer 下载地址]
> https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe

接着开始安装。需要注意的是，安装过程对网络环境要求较高（尽量避免使用中国移动宽带）。若网络连接失败，可以使用学校提供的 [VPN](http://openvpn.ustc.edu.cn/index.php) 或开启科学上网后再安装；若网络没有问题仍无法安装，可能是 MinGW Installer 的版本不是最新。

安装完成后，可以看到 MinGW Installer Manager 已经打开。

![](_images/lab-2-2.png ':class=resizedImage')

接着，在 *Basic Setup* 中勾选 mingw32-base-bin 和 mingw32-gcc-g++-bin，在 *MinGW Libraries* 中勾选 mingw32-gmp-dev、mingw32-gmp-dev-info 和 mingw32-gmp-dev-lic 并 Apply Changes，等待安装完成。

![](_images/lab-2-3.png ':class=resizedImage')
![](_images/lab-2-4.png ':class=resizedImage')

安装完成后设置环境变量：

![](_images/lab-2-5.png ':class=resizedImage')

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

![](_images/lab-2-7.png ':class=resizedImage')

> [!TIP|label:使用 mpz_class]
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

> [!TIP|label:IDE 中运行]
> 如果在 IDE 中运行代码，记得在链接器（Linker）中添加 GMP 的库文件 `libgmp.dll.a;libgmpxx.dll.a`，以我所使用的 CodeLite 为例：
>
> ![](_images/lab-2-8.png ':class=resizedImage')
>
> 添加后，即可运行。
>
> ![](_images/lab-2-9.png ':class=resizedImage')

> GMP 的安装参考了 👉 [这篇文章](https://www.cnblogs.com/ECJTUACM-873284962/p/8350320.html)

## 实验分析

### 实验要求

从附件 [EXP2-Doc.pdf](course/cryptography/lab-2-EXP2-Doc.pdf ':ignore') 中可知。此次实验需要写一个程序来计算模素数 $p$ 的离散对数。

其中 $p$ 是一个素数，$g$ 是有限乘法群 $\mathbb{Z}_{p}^{*}$ 上的一个原根，然后给定一个 $\mathbb{Z}_{p}^{*}$ 上的 $h$ 满足 $h = g^x$，其中 $1 \leq x \leq 2^{40}$，目的是找到 $x$。也就是说，编写程序，以 $p$，$g$，$h$ 作为输入，然后输出 $x$。

[test.txt](course/cryptography/lab-2-test.txt ':ignore') 中提供了三个输入 $p$，$g$，$h$，该问题最直接的算法就是对 $x$ 的可能值逐个进行尝试，由于 $g$ 是原根，$x$ 的可能值会有 $p$ 个，而本实验规定 $x$ 的范围为 $1 \leq x \leq 2^{40}$，降低了求解难度（$p$ 的值远大于 $2^{40}$）。

我们知道，上述的暴力法需要 $2^{40}$ 次乘法运算。本实验要求在此基础上使用中间相遇攻击，将时间代价减少到约为 $\sqrt{2^{40}}=2^{20}$。

### 思路

按照附件中提供的思路，我们令 $B = \lceil\sqrt{x}\rceil = 2^{20}$，$x = x_0B + x_1$，其中 $x_0, x_1 \in [0, B)$。可以得到：
$$
g^{Bx_0 + x_1} \equiv h \quad(\bmod\ p)
$$

两边同时乘以 $g^{x_1}$ 的逆元，可得到：

$$
(g^B)^{x_0} \equiv hg^{-x_1} \quad(\bmod\ p)
$$

通过上式，我们发现可以使用中间相遇攻击来找到一个解：

1. 为等式右边 $hg^{-x_1}$ 的所有可能值创建一个哈希表，其中 $x_1 = 0, 1,\cdots, 2^{20}$
2. 对于每个 $x_0 = 0, 1,\cdots, 2^{20}$，检查 $(g^B)^{x_0}$ 是否在哈希表中，如果是，便找到了解 $x_0$、$x_1$，即 $x = x_0B + x_1$

> [!TIP]
> 为等式右边 $hg^{-x_1}$ 的可能值创建哈希表时，涉及到求逆运算。可以使用 gmp 中的  
> `int mpz_invert(mpz_t rop, const mpz_t op1, const mpz_t op2)`，其中 `rop` 为运算结果，`op1` 为 $g^{x_1}$，`op2` 为 $p$。代码如下：
>
> ```cpp
> unordered_map<string, int> hashMap;
> for(int i = 0; i < B; i++)
> {
>     mpz_class x_1 = i;
>     mpz_class powm;
>     mpz_powm(powm.get_mpz_t(), g.get_mpz_t(), x_1.get_mpz_t(), p.get_mpz_t());
>     mpz_class inv;
>     mpz_invert(inv.get_mpz_t(), powm.get_mpz_t(), p.get_mpz_t());
>     mpz_class key = h * inv % p;
>     hashMap[key.get_str()] = i;
> }
> ```

以上方法中，创建哈希表的时间代价为 $\sqrt{x}$，哈希表查找的时间复杂度为 $O(1)$。

### 优化

[这篇文章](http://blog.miskcoo.com/2015/05/discrete-logarithm-problem)中提到了代码实现时的一个可优化的点。

我们令 $x = x_0B - x_1$，其中 $x_0 \in (0, B]$、$x_1 \in [0, B)$，化简等式 $h = g^x$ 可得到：

$$
(g^B)^{x_0} \equiv hg^{x_1} \quad(\bmod\ p)
$$

这样，将等式右边 $hg^{x_1}$ 的所有可能值存入哈希表时，就无需在每个循环内都进行幂运算和求逆运算（每个循环内仅有一次乘法运算和模运算）。代码如下：

```cpp
unordered_map<string, int> hashMap;
// x1 = 0, 1, 2...。将等式右边的结果 h * g^x1 % p 存入哈希表，key = h * g^x1 % p，value = x1
mpz_class productRight = h;
for(int i = 0; i < B; i++)
{
    hashMap[productRight.get_str()] = i;
    productRight = productRight * g % p;
}
```

> 实验思路参考了附件 [EXP2-Doc.pdf](course/cryptography/lab-2-EXP2-Doc.pdf ':ignore') 以及 👉 [这篇文章](http://blog.miskcoo.com/2015/05/discrete-logarithm-problem)

## 代码

结合上述思路及优化，给出如下代码：

```cpp
#include <gmpxx.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

mpz_class p("134078079299425970995740249982058461274793658205923933777235614437217640300735469768018742981669034276"
            "90031858186486050853753882811946569946433649006084171");
mpz_class g("117178298803662070095161175963353670885580849999989522055999794590639294997365837466705721764714603129"
            "28594829675428279466566527115212748467589894601965568");
mpz_class h("323947510405045044356526437872806578864909752095244952783479245297198197614329255807385693795855318053"
            "2878928001494706097394108577585732452307673444020333");
mpz_class B("1048576");

void solve2()
{
    mpz_class x0("0"), x1("0"), x("-1");
    unordered_map<string, int> hashMap;

    // x1 = 0, 1, 2...。将等式右边的结果 h * g^x1 % p 存入哈希表，key = h * g^x1 % p，value = x1
    mpz_class productRight = h;
    for(int i = 0; i < B; i++)
    {
        hashMap[productRight.get_str()] = i;
        productRight = productRight * g % p;
    }
    cout << "----- Without inverse -----" << endl << "Hash map saved!" << endl;

    // 等式左边的底数 baseLeft = g^B % p
    mpz_class baseLeft;
    // 幂取模运算
    mpz_powm(baseLeft.get_mpz_t(), g.get_mpz_t(), B.get_mpz_t(), p.get_mpz_t());
    //    for(int i = 0; i < B; i++)
    //    {
    //        baseLeft = baseLeft * g % p;
    //    }

    // x0 = 0, 1, 2...。判断等式左边的结果 (g^B % p)^x0 % p 是否在哈希表中
    mpz_class productLeft("1");
    for(int i = 1; i <= B; i++)
    {
        productLeft = productLeft * baseLeft % p;
        if(hashMap.find(productLeft.get_str()) != hashMap.end())
        {
            x0 = i;
            x1 = hashMap[productLeft.get_str()];
            break;
        }
    }

    x = B * x0 - x1;
    if(x == -1)
    {
        cout << "There is no solution!" << endl;
        return;
    }
    cout << "x0:\t" << x0 << endl;
    cout << "x1:\t" << x1 << endl;
    cout << "x:\t" << x << endl;
    return;
}

int main()
{
    solve2();
    return 0;
}
```

👉 两种方法的[完整代码](course/cryptography/lab-2-solution ':target=_blank')

## 实验结果

运行完整代码，输出：

```cpp
----- With inverse -----
Hash map saved!
x0:     357984
x1:     787046
x:      375374217830
----- Without inverse -----
Hash map saved!
x0:     357985
x1:     261530
x:      375374217830
```

可得到：$x = 375374217830$