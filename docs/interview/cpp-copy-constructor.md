?> 转载自：博客园 [AlanTu](https://www.cnblogs.com/alantu2018/p/8459250.html)

## 什么是拷贝构造函数
首先对于普通类型的对象来说，它们之间的复制是很简单的，例如：

```cpp
int a = 100;
int b = a;
```
而类对象与普通对象不同，类对象内部结构一般较为复杂，存在各种成员变量。  
下面看一个类对象拷贝的简单例子：

```cpp
#include <iostream>
using namespace std;
class CExample
{
private:
    int a;

public:
    //构造函数
    CExample(int b)
    {
        a = b;
        cout << "constructor is called" << endl;
    }
    //拷贝构造函数
    CExample(const CExample& c)
    {
        a = c.a;
        cout << "copy constructor is called" << endl;
    }
    //析构函数
    ~CExample()
    {
        cout << "destructor is called" << endl;
    }
    void Show()
    {
        cout << a << endl;
    }
};
int main()
{
    CExample A(100);
    CExample B(A);
    B.Show();
    return 0;
}
```

运行程序，屏幕输出 100。从以上代码的运行结果可以看出，系统为对象 B 分配了内存并完成了与对象 A 的复制过程。就类对象而言，相同类型的类对象是通过拷贝构造函数来完成整个复制过程的。

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200324122749.png" width="40%"/>

`CExample(const CExample& C)` 就是我们自定义的拷贝构造函数。可见，拷贝构造函数是一种**特殊的构造函数**，函数的名称必须和类名称一致，它必须的一个参数是本类型的一个**引用变量**。

## 拷贝构造函数的调用时机
### 1. 函数的参数为类的对象

```cpp
#include <iostream>
using namespace std;
class CExample
{
private:
    int a;

public:
    CExample(int b)
    {
        a = b;
        cout << "constructor is called" << endl;
    }
    CExample(const CExample& c)
    {
        a = c.a;
        cout << "copy constructor is called" << endl;
    }
    ~CExample()
    {
        cout << "destructor is called" << endl;
    }
    void Show()
    {
        cout << a << endl;
    }
};
void g_fun(CExample c)
{
    cout << "g_func" << endl;
}
int main()
{
    CExample A(100);
    CExample B(A);
    B.Show();
    g_fun(A);
    return 0;
}
```
调用 `g_fun()` 时，会产生以下几个重要步骤：
1. A 对象传入形参时，会先会产生一个临时变量，就叫 C 吧
2. 然后调用拷贝构造函数把 A 的值给 C。整个这两个步骤有点像：`CExample C(A)`
3. 等 `g_fun()` 执行完后, 析构掉 C 对象

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/1917068-20200324123730268-1899735070.png" width="40%"/>

### 2. 函数的返回值是类的对象

```cpp
#include <iostream>
using namespace std;
class CExample
{
private:
    int a;

public:
    //构造函数
    CExample(int b)
    {
        a = b;
        cout << "constructor is called" << endl;
    }
    //拷贝构造函数
    CExample(const CExample& c)
    {
        a = c.a;
        cout << "copy constructor is called" << endl;
    }
    //析构函数
    ~CExample()
    {
        cout << "destructor is called" << endl;
    }
    void Show()
    {
        cout << a << endl;
    }
};
CExample g_fun()
{
    CExample temp(0);
    return temp;
}
int main()
{
    g_fun();
    return 0;
}
```

当 `g_Fun()` 函数执行到 return 时，会产生以下几个重要步骤：
1. 先会产生一个临时变量，就叫 XXXX 吧
2. 然后调用拷贝构造函数把 temp 的值给 XXXX。整个这两个步骤有点像：`CExample XXXX(temp)`
3. 在函数执行到最后先析构 temp 局部变量
4. 等 `g_fun()` 执行完后再析构掉 XXXX 对象

**注**：当返回值为对象时，gcc 做了优化，不再产生临时对象，因而不再调用复制构造函数，需要加上参数 `-fno-elide-constructors`  
参考[这里](https://blog.csdn.net/sxhelijian/article/details/50977946)

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/1917068-20200324130526711-334949043.png" width="70%"/>

### 3. 对象需要通过另外一个对象进行初始化

```cpp
CExample A(100);
CExample B(A);
```

## 浅拷贝与深拷贝
### 默认拷贝构造函数
很多时候在我们都不知道拷贝构造函数的情况下，传递对象给函数参数或者函数返回对象都能很好的进行，这是因为编译器会给我们自动产生一个拷贝构造函数，这就是“默认拷贝构造函数”，这个构造函数很简单，仅仅使用“老对象”的数据成员的值对“新对象”的数据成员一一进行赋值，它一般具有以下形式：

```cpp
Rect::Rect(const Rect& r)
{
    width = r.width;
    height = r.height;
}
```

当然，以上代码不用我们编写，编译器会为我们自动生成。但是如果认为这样就可以解决对象的复制问题，那就错了，让我们来考虑以下一段代码：

```cpp
#include <iostream>
using namespace std;
class Rect
{
public:
    Rect()
    {
        count++;
    }
    ~Rect()
    {
        count--;
    }
    static int getCount()
    {
        return count;
    }

private:
    int width;
    int height;
    static int count;
};
int Rect::count = 0;
int main()
{
    Rect rect1;
    cout << "The count of Rect:" << Rect::getCount() << endl;
    Rect rect2(rect1);
    cout << "The count of Rect:" << Rect::getCount() << endl;
    return 0;
}
```

这段代码对前面的类，加入了一个静态成员，目的是进行计数。在主函数中，首先创建对象 rect1，输出此时的对象个数，然后使用 rect1 复制出对象 rect2，再输出此时的对象个数，按照理解，此时应该有两个对象存在，但实际程序运行时，输出的都是 1，反应出只有 1 个对象。此外，在销毁对象时，由于会调用销毁两个对象，类的析构函数会调用两次，此时的计数器将变为负数。  
说白了，就是拷贝构造函数没有处理静态数据成员。  
出现这些问题最根本就在于在复制对象时，计数器没有递增，我们重新编写拷贝构造函数，如下：

```cpp
#include <iostream>
using namespace std;
class Rect
{
public:
    Rect()
    {
        count++;
    }
    Rect(const Rect& r)
    {
        width = r.width;
        height = r.height;
        count++;
    }
    ~Rect()
    {
        count--;
    }
    static int getCount()
    {
        return count;
    }

private:
    int width;
    int height;
    static int count;
};
int Rect::count = 0;
int main()
{
    Rect rect1;
    cout << "The count of Rect:" << Rect::getCount() << endl;
    Rect rect2(rect1);
    cout << "The count of Rect:" << Rect::getCount() << endl;
    return 0;
}
```

### 浅拷贝
**浅拷贝**只是增加了一个指针指向已存在的内存地址；**深拷贝**是增加了一个指针并且申请了一个新的内存，使这个增加的指针指向这个新的内存。

大多情况下“浅拷贝”已经能很好地工作了，但是一旦对象存在了动态成员，那么浅拷贝就会出问题了，让我们考虑如下一段代码：

```cpp
#include <assert.h>
#include <iostream>
using namespace std;
class Rect
{
public:
    Rect()
    {
        p = new int(100);
    }

    ~Rect()
    {
        assert(p != nullptr);
        delete p;
        p = nullptr;
    }

private:
    int width;
    int height;
    int* p;
};
int main()
{
    Rect rect1;
    Rect rect2(rect1);
    return 0;
}
```

在这段代码运行结束之前，会出现一个运行错误。原因就在于在进行对象复制时，对于动态分配的内容没有进行正确的操作。我们来分析一下：  
在运行定义 `rect1` 对象后，由于在构造函数中有一个动态分配的语句，因此执行后的内存情况大致如下：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/1917068-20200324230227554-461166612.jpg" width="40%"/>

在使用 `rect1` 复制 `rect2` 时，由于执行的是浅拷贝，只是将成员的值进行赋值，这时 `rect1.p = rect2.p`，也即这两个指针指向了堆里的同一个空间，如下图所示：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145d10b36baf75.png" width="35%"/>

当然，这不是我们所期望的结果，在销毁对象时，两个对象的析构函数将对同一个内存空间释放两次，这就是错误出现的原因。我们需要的不是两个 p 有相同的值，而是两个 p 指向的空间有相同的值，解决办法就是使用“深拷贝”。

### 深拷贝
在“深拷贝”的情况下，对于对象中动态成员，就不能仅仅简单地赋值了，而应该重新动态分配空间，如上面的例子就应该按照如下的方式进行处理：

```cpp
#include <assert.h>
#include <iostream>
using namespace std;
class Rect
{
public:
    Rect()
    {
        p = new int(100);
    }

    Rect(const Rect& r)
    {
        width = r.width;
        height = r.height;
        p = new int(100);
        *p = *(r.p);
    }

    ~Rect()
    {
        assert(p != nullptr);
        delete p;
        p = nullptr;
    }

private:
    int width;
    int height;
    int* p;
};
int main()
{
    Rect rect1;
    Rect rect2(rect1);
    return 0;
}
```

此时，在完成对象的复制后，内存的一个大致情况如下：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145d1101a3f264.png" width="40%"/>

此时 `rect1` 的 `p` 和 `rect2` 的 `p` 各自指向一段内存空间，但它们指向的空间具有相同的内容，这就是所谓的“深拷贝”。

### 防止默认拷贝发生
通过对对象复制的分析，我们发现对象的复制大多在进行“值传递”时发生，这里有一个小技巧可以防止按值传递——声明一个**私有拷贝构造函数**。甚至不必去定义这个拷贝构造函数，这样因为拷贝构造函数是私有的，如果用户试图按值传递（情况 1）或函数返回该类对象（情况 2），将得到一个编译错误，从而可以避免按值传递或返回对象。

```cpp
//防止按值传递
class CExample
{
private:
    int a;

public:
    //构造函数
    CExample(int b)
    {
        a = b;
        cout << "create: " << a << endl;
    }

private:
    //拷贝构造函数，只是声明
    CExample(const CExample& C);

public:
    ~CExample()
    {
        cout << "delete: " << a << endl;
    }

    void Show()
    {
        cout << a << endl;
    }
};

void g_Fun(CExample C)
{
    cout << "test" << endl;
}

int main()
{
    CExample test(1);
    // g_Fun(test);   //按值传递将出错
    return 0;
}
```

**小结**：

> [!TIP|label: 深拷贝和浅拷贝]
>
> 当出现类的等号赋值时，会调用拷贝函数，在未定义显示拷贝构造函数的情况下，系统会调用默认的拷贝函数——即浅拷贝，它能够完成成员的一一复制。当数据成员中没有指针时，浅拷贝是可行的。但当数据成员中有指针时，如果采用简单的浅拷贝，则两类中的两个指针将指向同一个地址，当对象快结束时，会调用两次析构函数，而导致指针悬挂现象。所以这时必须采用深拷贝。
>
> 深拷贝与浅拷贝的区别就在于深拷贝会在堆内存中另外申请空间来储存数据，从而也就解决了指针悬挂的问题。简而言之，当数据成员中有指针时，必须要用深拷贝。

## 拷贝构造函数的几个细节
1. **为什么拷贝构造函数必须是引用传递，不能是值传递？**
    > 简单的回答是为了防止递归引用。
    >
    > 具体一些可以这么讲：一个对象需要以值方式传递时，编译器会调用它的拷贝构造函数以生成一个复本。若拷贝构造函数里的参数也是值传递，那么会继续调用拷贝构造函数以生成一个复本，继而陷入递归。

2. **一个类中可以存在多于一个的拷贝构造函数吗?**
    > 类中可以存在超过一个拷贝构造函数。
    >
    > 如果一个类中没有定义拷贝构造函数，那么编译器会自动产生一个默认的拷贝构造函数。这个默认的参数可能为 `X::X(const X&)` 或 `X::X(X&)`，由编译器根据上下文决定选择哪一个。

3. **C++ 构造函数以及析构函数的若干面试问题**
    > - Q1：构造函数能否重载，析构函数能否重载，为什么？  
    > A1：构造函数可以，析构函数不可以。
    > 
    > - Q2：析构函数为什么一般情况下要声明为虚函数？  
    > A2：虚函数是实现多态的基础，当我们通过基类的指针是析构子类对象时候，如果不定义成虚函数，那只调用基类的析构函数，子类的析构函数将不会被调用。如果定义为虚函数，则子类父类的析构函数都会被调用。
    >
    > - Q3：什么情况下必须定义拷贝构造函数？  
    > A3：当类的对象用于函数值传递时（值参数，返回类对象），拷贝构造函数会被调用。如果对象复制并非简单的值拷贝，那就必须定义拷贝构造函数。例如大的堆栈数据拷贝。如果定义了拷贝构造函数，那也必须重载赋值操作符。

## 相关

移动构造函数，[传送门](interview/cpp?id=移动语意)