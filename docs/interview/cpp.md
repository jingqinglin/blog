<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145ecf552295da.jpg" width="50%"/>

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145ecf6c897404.jpg" width="50%"/>

- 预处理：头文件、宏定义插入与替换
- 编译：语法分析...翻译成汇编代码（Java 是字节码）
- 汇编：汇编语言转为机器语言
- 链接：将有关的目标文件和库文件彼此连接

http://m.elecfans.com/article/663750.html  
https://www.cnblogs.com/magicsoar/p/3760201.html

## 面向对象与面向过程

面向过程：以步骤划分问题  
面向对象：以功能划分问题

以上课的过程作为例子：

- 面向过程：同学们走进教室坐下来，老师走进来，铃声响了，老师开始讲话，同学开始听课……
- 面向对象：上课要有教室，要有一个老师，要有很多学生，或者有电脑，他们有很多属性（功能）和关系，比如老师可以发出声音，学生可以记笔记，电脑可以放课件

## C++ 和 Java 区别

- Java 不提供指针来直接访问内存，程序内存更加安全（C++ 指针可以做运算）
- Java 的类是单继承的，C++ 支持多重继承；虽然 Java 的类不可以多继承，但是接口可以多继承
- Java 有自动内存管理机制，不需要程序员手动释放无用内存

### ⭐ Java 引用和 C++ 指针区别

Java 的引用在本质上是一个**指针**（受限的指针），只不过对指针进行了封装，**使其不能直接对内存进行操作**，Java 的引用只能指向对象，不能指向基本数据类型

- Java 引用不会产生内存泄露，C++ 指针容易产生内存泄露
- C++ 指针可以做运算

### C++ 中引用与指针区别

- 引用初始化以后不能被改变，指针可以改变所指的对象
- 引用必须指向某个对象（是某个对象的别名），指针可以不指向任何对象（nullptr）
- 指针可以做运算，因为指针有具体类型，int \* 型的指针可以做加减，自增自减运算

## 内存管理

一个由 C/C++ 编译的程序占用的内存分为以下几个部分：

1. 栈区（stack）— 由编译器自动分配释放，存放**函数的参数值**，**局部变量**的值等
2. 堆区（heap） — 由程序员分配和释放，若程序员不释放，程序结束时可能由 OS 回收。会有内存碎片问题
3. 全局区 / 静态区存储区（static）— 分为 DATA 段和 BSS 段。DATA 段（全局初始化区）存放初始化的全局变量和静态变量；BSS 段（全局未初始化区）存放未初始化的全局变量和静态变量。其中 BBS 段在程序执行之前会被系统自动清 0，所以未初始化的全局变量和静态变量值为 0
   https://www.runoob.com/w3cnote/cpp-static-usage.html
4. 文字常量区 — 常量字符串就是放在这里的
5. **程序代码区** — 存放函数体的二进制代码

## 内联函数

> 编译时期展开函数

https://interview.huihut.com/#/?id=inline-%e5%86%85%e8%81%94%e5%87%bd%e6%95%b0

- 相当于把内联函数里面的内容写在调用内联函数处；
- 相当于不用执行进入函数的步骤，直接执行函数体；
- 相当于宏，却比宏多了**类型检查**，真正具有函数特性；
- 编译器一般不内联包含循环、递归、switch 等复杂操作的内联函数；
- 在类声明中定义的函数，除了虚函数的其他函数都会自动隐式地当成内联函数

**虚函数可以是内联函数**，但是当虚函数表现多态性的时候不能内联，因为虚函数表现多态是在运行期绑定的。当编译器知道所调用的对象是哪个类（如 `Base::who()`）才行

## struct / class

### C 和 C++ 中 struct 的区别

首先，在面向 C 过程中，这里的 struct 是一种数据类型，那么里面肯定不能定义函数，否则报错，C++ 可以包含函数

### struct 和 class 的区别

- 默认访问权限和默认继承权限不同，前者 public 后者 private
- class 可用于定义模板参数，而 struct 不可以

一个 union 可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值：https://blog.csdn.net/firefly_2002/article/details/7954458

### 内存对齐

按最宽数据类型对齐（如果下一个元素能摆下，就继续放；摆不下，就从头开始摆。下方例子）

**优点**：内存对齐主要是为了提高程序的性能，数据结构特别是栈，应尽可能的在自然边界上对齐，经对齐后 CPU 的内存访问速度大大提升（未对齐可能需要两次访存）

```cpp
// 按 4 对齐
class Data {
    char c;
    // int 摆不下了，要从头开始
    int a;
    char d;
};
cout << sizeof(Data) << endl;   12

class Data {
    char c;
    // 第二个 char 仍然能摆下
    char d;
    int a;
};
cout << sizeof(Data) << endl;   8
```

## static

1. 修饰普通变量，修改变量的存储区域和**生命周期**（延长生命周期），使变量存储在静态区，在 main 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它
2. 修饰普通函数，表明函数的作用范围，仅在定义该**函数的文件内**才能使用。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 static
3. 修饰成员变量，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员。静态成员变量的初始化不能省略（类体外）

   ```cpp
   class A {
   public:
   	//声明但未定义
       static int a;
    };
   //此处定义了静态成员变量，同时初始化，不能省略
   int A::a = 3;
   int main() {
       printf("%d", A::a);
       return 0;
   }
   ```

4. 修饰成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在 static 函数内**不能访问非静态成员**

- 关于 static 的**内存分配**和**初始化**问题：
  - 内存分配：由于 static 对象都是存储在全局区的数据段，这些对象的内存都是在编译时就已经分配好了
  - 初始化：C 与 C++ 表现得不同
    - C：由于 C 没有构造函数，因此初始化其实在编译时候已经完成
    - C++：
      - 对于全局变量、文件域的静态变量和类的静态成员变量这些都是在 **main 函数执行前**进行初始化（具体是编译期还是运行期视情况定，参考自[这篇](https://blog.csdn.net/hueru/article/details/89504059)博客）
      - 局部静态变量（一般为函数内的静态变量）在第一次使用时初始化

## const

- 修饰变量，修饰指针
- 修饰引用，指向常量的引用（reference to const），用于形参类型，即避免了拷贝，又避免了函数对值的修改
- 修饰成员函数（const 写在函数名后面），该函数不能修改成员变量的值（静态成员变量除外），也不能调用同类的非常量成员函数（静态成员函数除外）
- const 也可以写在函数名前，表示返回值（一般为指针或引用）不能作为左值（被修改）

```cpp
// const int *max() 或 int const *max() 都会使 *max(&a, &b) = 20 报错
int *max(int *x, int *y)
{
    if(*x > *y)
    {
        return x;
    }
    return y;
}
int main()
{
    int a = 33, b = 44;
    cout << *max(&a, &b) << endl;
    // *max(&a, &b) 返回了指向数 b（b 比较大）地址的指针，赋值运算把指向地址的内容改为 20
    *max(&a, &b) = 20;
    cout << *max(&a, &b) << endl;
    // b = 20
    cout << b << endl;
    return 0;
}
```

const 可用于对重载函数的区分

### 指针常量和常量指针

const 后边的内容为“常量”，英文更好理解  
https://blog.csdn.net/qq_36132127/article/details/81940015

```cpp
int const *p1 = &b; //const 在前，定义为常量指针
int *const p2 = &c; // * 在前，定义为指针常量
```

- 常量指针（pointer to const / 指向常量的指针）：不能修改指向地址的内容

```cpp
int main()
{
    int a = 2;
    int const *b = &a;
    // 报错
    *b = 3;
    printf("albert:%d\n",a);
}
```

- 指针常量（const pointer）：指针指向的地址不可以修改，但内容可以改变

```cpp
int main()
{
    int a = 2;
    int b = 3;
    int *const c = &a;
    printf("albert:%p\n", c);
    // 报错
    c = &b;
    printf("albert:%p\n",c);
}
```

## this

1. **`this` 指针是一个隐含于每一个<span style="color: red;">非静态成员函数</span>中的特殊指针。它指向调用该成员函数的那个对象**
2. 当对一个对象调用成员函数时，编译程序先将对象的地址赋给 `this` 指针，然后调用成员函数，每次成员函数存取数据成员时，都隐式使用 `this` 指针
3. `this` 指针被隐含地声明为： `ClassName *const this`，这意味着不能给 `this` 指针赋值
4. `this` 并不是一个常规变量，而是个右值，所以不能取得 `this` 的地址（不能 `&this`）

## 继承

继承可以使得子类具有父类别的各种属性和方法，而不需要再次编写相同的代码

https://blog.csdn.net/scottly1/article/details/24354489

## 多态

好处：可以使程序有良好的扩展性（打印机的例子）

多态可以分为**静态多态**和**动态多态**，所谓静态多态就是通过函数重载、模板、强制类型转换实现的，静态多态是在函数编译阶段就决定调用的机制，即在编译链接截断将函数的入口地址给出，而动态多态是在程序运行时刻才决定调用机制，而在 C++ 中动态多态是通过虚函数实现的（还有一些注意点[看这里](https://interview.huihut.com/#/?id=%e5%a4%9a%e6%80%81)）

### 动态多态（virtual）

- 通过 virtual 动态绑定，要通过指针或引用？

```cpp
A a;
B b;
a = b;
```

这样是不行的，因为 b 的 vtable（ 有几个基类就有几个虚函数表） 没有赋给 a（对象无法访问虚函数表），而是要 `A *a = &b`

虚函数的调用关系：this -> vptr -> vtable -> virtual function

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145d10b04eb7ee.png" width="70%"/>

- 父类指针或引用指向子类对象

- 子类虚函数会在虚函数表中对父类虚函数进行覆盖，[参考](https://songlee24.github.io/2014/09/02/cpp-virtual-table/)

- 析构函数也要 virtual，不然只调用父类的析构（没有 virtual 就不会发生动态绑定，默认调用父类函数）。

- 那又有另一个问题，析构函数在虚函数表中吗，如果在，那意味着父类析构被**覆盖**了，为什么又能调用父类析构呢？

  - 因为子类的析构函数中包含着对父类析构函数的调用，参考了这篇[文章](https://blog.csdn.net/F_cff/article/details/79690470)

- Java 默认就动态绑定

## 纯虚函数、虚继承等

纯虚函数（即 Java 中的接口）是一种特殊的虚函数，在基类中不能对虚函数给出有意义的实现，而把它声明为纯虚函数，它的实现留给该基类的派生类去做

```cpp
virtual int A() = 0;
```

具体：https://interview.huihut.com/#/?id=%e7%ba%af%e8%99%9a%e5%87%bd%e6%95%b0

- 虚函数指针（占用类的空间）、虚函数表（不占用类的空间）：https://songlee24.github.io/2014/09/02/cpp-virtual-table/

- 虚继承：用于解决多继承条件下的菱形继承问题（浪费存储空间、存在**二义性**）。一般通过虚基类指针和虚基类表实现，每个虚继承的子类都有一个虚基类指针和虚基类表

- **带纯虚函数的类叫抽象类**，这种类不能直接生成对象，而只有被继承，并重写其虚函数后，才能使用。抽象类被继承后，子类可以继续是抽象类，也可以是普通类

- 抽象类含有纯虚函数，接口类仅含有纯虚函数

## 拷贝构造函数

https://www.cnblogs.com/jingqinglin/articles/12557560.html

### 拷贝构造函数的调用时机

1. 函数的参数为类的对象
2. 函数的返回值是类的对象
3. 对象需要通过另外一个对象进行初始化

默认拷贝构造函数仅仅使用“老对象”的数据成员的值对“新对象”的数据成员一一进行赋值（指针则是复制地址）。默认拷贝构造函数没有处理静态成员变量

### 浅拷贝、深拷贝

**浅拷贝**只是增加了一个指针指向已存在的内存地址

**深拷贝**是增加了一个指针并且申请了一个新的内存，使这个增加的指针指向这个新的内存

#### 浅拷贝

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145d10b36baf75.png" width="70%"/>

在销毁对象时，两个对象的析构函数将对同一个内存空间释放两次，出现错误

#### 深拷贝

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145d1101a3f264.png" width="70%"/>

此时 rect1 的 p 和 rect2 的 p 各自指向一段内存空间，但它们指向的空间具有相同的内容，这就是“深拷贝”

### 参数为什么必须是引用

> 为了防止递归引用

一个对象需要以值方式传递时，编译器会调用它的拷贝构造函数以生成一个复本。若拷贝构造函数里的参数也是值传递，那么会继续调用拷贝构造函数以生成一个复本，继而陷入递归

## 重载运算符

```cpp
class Integer {
public:
    Integet(int n = 0) : i(n) {}
    // 若没有第一个 const 则返回值可以作为左值，类似：a + b = c，我们的原意是 c = a + b
    // 第二个 const 代表操作数不能被修改
    // 第三个 const 使成员函数变为常量成员函数，不能修改成员变量的值（静态成员变量除外），也不能调用同类的非常量成员函数（静态成员函数除外）
    const Integer operator+(const Integer &n) const {
    	return Integer(n.i + i);
    }

private:
    int i;
};
```

- 类型转换

重载运算符 `()` 和拷贝构造函数都可以实现

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145d10bb0738f6.png" width="50%"/>

上述代码中 `f(a)` 会出错，因为写了两种类型转换的方法，编译器不知道用哪个。可以通过在拷贝构造函数前加上 `explicit` 来关闭隐式类型转换

## volatile

```cpp
volatile int i = 10;
```

- volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素（操作系统、硬件、其它线程等）更改。所以使用 volatile 告诉编译器不应对这样的对象进行优化。
- volatile 关键字声明的变量，每次访问时都必须从内存中取出值（没有被 volatile 修饰的变量，可能由于编译器的优化，从 CPU 寄存器中取值）
- const 可以是 volatile （如只读的状态寄存器）
- 指针可以是 volatile

## friend 友元类和友元函数

- 能访问私有成员
- 破坏封装性
- 友元关系不可传递、具有单向性
- 友元声明的形式及数量不受限制
- 友元函数没有 this 指针

例子：https://www.runoob.com/cplusplus/cpp-friend-functions.html

## 模板（template）

模板是创建泛型类或函数的蓝图或公式。库容器，比如迭代器和算法，都是泛型编程的例子，它们都使用了模板的概念

### 函数模板

当我们调用一个函数模板时，编译器通常用函数实参来为我们推断模板实参

### 类模板

与函数模板的不同之处是，编译器不能为类模板推断模板参数类型。为了使用类模板，我们必须在模板名后的尖括号中提供额外信息

模板优缺点：https://www.cnblogs.com/shines77/p/3179022.html

## new、delete

- new / new[]：完成两件事，先底层调用 malloc 分配了内存，然后调用构造函数（创建对象）
- delete/delete[]：也完成两件事，先调用析构函数（清理资源），然后底层调用 free 释放空间
- 🚀new 在申请内存时会自动计算所需字节数，而 malloc 则需我们自己输入申请内存空间的字节数

- 用 free 来释放 new 出来的东西会发生什么？  
  答：对于简单数据类型，和 delete 一样；对对象来说，free 不会调用析构函数

## C++ 函数调用的过程

https://blog.csdn.net/HDong99/article/details/86102944  
https://www.cnblogs.com/sddai/p/9762968.html

- 为什么参数是从右到左入栈的？  
  因为存在不定长参数的函数，如 printf，编译器通过 format 参数中的 % 占位符的个数来确定参数的个数，现在我们假设参数的压栈顺序是从左到右的，由于 format 先进栈了，上面压着未知个数的参数，想要知道参数的个数，必须找到 format，而要找到 format，必须要知道参数的个数。

- 再问，不是有 EBP 栈底指针吗？  
  看这张图（这张图栈顶在下方），

  <img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145ecfd81b9f12.png" width="50%"/>

  参数是属于调用者的栈帧

## ⭐ 四种强制类型转换

### dynamic_cast

- 用于**多态**类型（要有虚函数）的转换
- 执行运行时类型检查
- 只适用于指针或引用
- 对不明确的指针的转换将失败（返回 nullptr），但不引发异常
- 可以在整个类层次结构中移动指针，包括向上转换、向下转换（基类对象指针（或引用）转换到继承类指针）

### static_cast

- 用于非多态类型的转换
- 不执行运行时类型检查（转换安全性不如 dynamic_cast）
- 通常用于转换数值数据类型（如 float -> int）
- 可以在整个类层次结构中移动指针，子类转化为父类安全（向上转换），父类转化为子类不安全（因为子类可能有不在父类的字段或方法）

### const_cast

用于删除 const 和 volatile 关键字

### reinterpret_cast

- 允许将任何指针转换为任何其他指针类型（如 `char*` 到 `int*` 或 `One_class*` 到 `Unrelated_class*` 之类的转换，但其本身并不安全）
- 也允许将任何整数类型转换为任何指针类型以及反向转换

## 静态库和动态库区别

静态库：在链接阶段，会将汇编生成的目标文件 .o 与引用到的库一起链接打包到可执行文件中。

静态链接器主要完成以下两个任务：

- 符号解析：每个符号对应于一个函数、一个全局变量或一个静态变量，符号解析的目的是将每个符号引用与一个符号定义关联起来
- 重定位：链接器通过把每个符号定义与一个内存位置关联起来，然后修改所有对这些符号的引用，使得它们指向这个内存位置

静态库缺点：

- 空间浪费。多个程序都用到某个静态库，则静态库在内存存在多份拷贝
- 如果静态库 libxx.lib 更新了，所有使用它的应用程序都需要重新编译、发布给用户（全量更新）

动态库在程序编译时并不会被链接到目标代码中，而是在**程序运行时**才被载入。不同的应用程序如果调用相同的库，那么在内存里只需要有**一份**该共享库的实例，规避了空间浪费问题。动态库在程序运行时才被载入，也解决了静态库对程序的更新、部署和发布页会带来麻烦。用户只需要更新动态库即可，**增量更新**

## 智能指针

智能指针自动释放所指向的对象。标准库提供的两种智能指针的区别在于管理底层指针的方法不同，shared_ptr 允许多个指针指向同一个对象， unique_ptr 则“独占”所指向的对象。标准库还定义了一种名为 weak_ptr 的伴随类，它是一种弱引用，指向 shared_ptr 所管理的对象，这三种智能指针都定义在 memory 头文件中

### shared_ptr

创建智能指针时必须提供额外的信息，指针可以指向的类型

```cpp
shared_ptr<string> p1;
shared_ptr<list<int>> p2;
```

当进行拷贝和赋值时，每个 shared_ptr 都会记录有多少个其他 shared_ptr 指向相同的对象（数据结构在下方）

```cpp
auto p = make_shared<int>(42); // make_shared 函数在动态内存中分配一个对象并初始化它，返回指向此对象的 shared_ptr
auto q(p); // p 和 q 指向相同的对象，此对象有两个引用者
```

当指向一个对象的最后一个 shared_ptr 被销毁时，shared_ptr 类会自动销毁此对象，它是通过析构函数完成销毁工作的

#### 线程安全性

摘自：https://blog.csdn.net/solstice/article/details/8547547

shared_ptr 的引用计数本身是安全且无锁的（多个 shared_ptr 对象可以同时修改引用计数？）

> 评论区：shared_ptr 对象本身的线程安全性已经不是 shared_ptr 的责任了，他也无法自己控制，而在于使用 shared_ptr 的人。就当 shared_ptr 对象和内置对象 int 一样对待。 shared_ptr 的线程安全应该指的是他对其所管理的指针的引用计数不会因多线程环境而出现破坏

shared_ptr 对象提供与内置类型（int 之类的）相同级别的线程安全性。

1. 同一个 shared_ptr 对象可以被多线程同时读取
2. 不同的 shared_ptr 对象可以被多线程同时修改（即使这些 shared_ptr 对象管理着同一个对象的指针）
3. 任何其他并发访问的结果都是无定义的

#### shared_ptr 的数据结构

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/1715ca277c00d1cf.png" width="70%"/>

shared_ptr 是引用计数型（reference counting）智能指针，几乎所有的实现都采用在堆（heap）上放个计数值（count）的办法。具体来说，shared_ptr<Foo> 包含两个成员，一个是指向 Foo 的指针 ptr，另一个是 ref_count 指针（其类型不一定是原始指针，有可能是 class 类型），指向堆上的 ref_count 对象。ref_count 对象有多个成员，具体如上图，<span style="color: gray">其中 deleter 和 allocator 是可选的</span>

<!-- 接下来回到线程安全性上，为了简化并突出重点，后面只画出 use_count 的值：

<img src="https://user-gold-cdn.xitu.io/2020/4/9/1715cab1d4b47fee?w=225&h=95&f=png&s=2071" width="40%"/>

以上是 `shared_ptr<Foo> x(new Foo)` 对应的内存数据结构，如果再执行 `shared_ptr<Foo> y = x` 那么对应的数据结构如下：

<img src="https://user-gold-cdn.xitu.io/2020/4/9/1715cacf8baa4994?w=369&h=95&f=png&s=3109" width="50%"/>

 `y = x` 涉及两个成员的复制，这两步拷贝不会同时（原子）发生，如果没有 mutex 保护，那么在多线程里就有 race condition<span style="color: gray">（由于两个或者多个进程竞争使用不能被同时访问的资源，使得这些进程有可能因为时间上推进的先后原因而出现问题）</span> -->

### weak_ptr

解决 shared_ptr 循环引用的问题：https://blog.csdn.net/albertsh/article/details/82286999

- weak_ptr 接受 shared_ptr 类型的变量赋值，但是反过来是行不通的，需要使用 lock 函数
- 不增加引用计数

### unique_ptr

一个 unique_ptr “拥有“他所指向的对象。与 shared_ptr 不同，某个时刻只能有一个 unique_ptr 指向一个给定的对象。当 unique_ptr 被销毁时，它所指向的对象也被销毁

### auto_ptr

## STL 容器

### 顺序容器

是一种各元素之间有顺序关系的线性表，是一种线性结构的可序群集。顺序性容器中的每个元素均有固定的位置，除非用删除或插入的操作改变这个位置。顺序容器的元素排列次序与元素值无关，而是由元素添加到容器里的次序决定。顺序容器包括：vector、list、deque

- vector 通过一个连续的数组存放元素，（**扩容**）如果集合已满，在新增数据的时候，就要分配一块更大的内存，将原来的数据复制过来，释放之前的内存，再插入新增的元素。VS 扩容 1.5 倍，GCC 2 倍

- list 底层数据结构为双向链表

#### vector 迭代器失效

https://www.cnblogs.com/blueoverflow/p/4923523.html

##### push_back/insert

根据 vector 扩容的特性，指向原空间的迭代器就成了类似于“悬垂指针”

##### erase

当删除元素时，指向被删除元素以后的任何元素的迭代器都将失效。因为 vetor，deque 使用了连续分配的内存，删除一个元素导致后面所有的元素会向前移动一个位置。erase 方法可以返回下一个有效的 iterator，因此使用了 erase 的那次迭代不需要 it++

```cpp
vector<int>::iterator it = l.begin();
while(it != l.end()) {
    if(删除条件) {
        it = l.erase(it);
    } else {
        cout << *it << " ";
        ++it;
    }
}
```

### 关联容器

关联式容器是非线性的树结构，更准确的说是**红黑树结构**。各元素之间没有严格的物理上的顺序关系，也就是说元素在容器中并没有保存元素置入容器时的逻辑顺序。但是关联式容器提供了另一种根据元素特点排序的功能，这样迭代器就能根据元素的特点“顺序地”获取元素。元素是**有序的集合**，默认在插入的时候按升序排列。关联容器包括：map（按 key 大小存储）、set、multimap、multiset

map 的所有元素都是 pair，同时拥有 key & value。**map 如何按值排序**？pair 存储 key 和 value，再存到 vector 里 sort

容器类自动申请和释放内存，因此无需 new 和 delete 操作

**在 C++ 11 中新出 4 个关联式容器**：unordered_map/unordered_set/unordered_multimap/unordered_multiset

unordered_set（hash_map） 的实现：https://www.jianshu.com/p/56bb01df8ac7

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145ecf5e6b768c.png" width="70%"/>

## C++ 11 新特性

https://blog.csdn.net/jiange_zh/article/details/79356417

### nullptr（空指针常量）

解决 NULL 的二义性

```cpp
# if defined(__cplusplus)
# define NULL 0 /* C++ 中使用 0 作为 NULL 的值 */
# else
# define NULL ((void *)0) /* C中使用 ((void *)0) 作为 NULL 的值 */
# endif
```

调用 `func` 函数，编译器会把 NULL 当作 0

```cpp
void func(int) {}
void func(int *) {}
```

### 类型推导

#### auto

使用 auto 进行类型推导的一个最为常见而且显著的例子就是迭代器

但是：

- auto 不能用于函数形参类型
- 对于结构体来说，非静态成员变量的类型不能是 auto 的
- auto 能不声明数组类型
- 在实例化模版的时候不能使用 auto 作为模版参数

#### decltype

decltype 关键字是为了解决 auto 关键字**只能对变量**进行类型推导的缺陷而出现的

decltype 计算**某个表达式的类型**

```cpp
auto x = 1;
auto y = 2;
decltype(x+y) z;
```

拖尾返回类型，利用 auto 关键字将返回类型后置，详见：https://blog.csdn.net/jiange_zh/article/details/79356417

### 区间迭代

和 Java 中的 foreach 一样

例子： std::vector 的遍历

```cpp
// 初始化 5 个值为 100 的元素
std::vector<int> arr(5, 100);
for(std::vector<int>::iterator i = arr.begin(); i != arr.end(); ++i) {
    std::cout << *i << std::endl;
}
```

可以写成这样

```cpp
// & 启用了引用
for(auto &i : arr) {
    std::cout << i << std::endl;
}
```

### 初始化列表

C++ 11 提供的列表初始化作为统一的初始化方式，用花括号初始化

### Lambda 表达式

底层是一个类的对象，函数体重载 operator()：https://www.zhihu.com/question/25740516

lambda 表达式是一种**匿名函数**，即没有函数名的函数；该匿名函数是由数学中的 λ 演算而来的。通常情况下，lambda 函数的语法定义为：  
[capture](params) opt ->ret {body}

1. capture 是捕获列表
2. params 是参数表（选填）
3. opt 是函数选项；可以填 mutable，exception，attribute（选填）
   - mutable 说明 lambda 表达式体内的**代码可以修改被捕获的变量**（<span style="color: red">当 capture 为 = 时，能修改拷贝，但不修改函数外原来的值；& 原本就能修改捕获的变量，加上 mutable 也无意义</span>），并且可以访问被捕获的对象的 non-const 方法
   - exception 说明 lambda 表达式是否抛出异常以及何种异常
   - attribute 用来声明属性
4. ->ret 是返回值类型（拖尾返回类型）（选填）
5. body 是函数体

**捕获列表**：lambda 表达式的捕获列表精细控制了 lambda 表达式能够访问的**外部变量**，以及如何访问这些变量。**注**：`[=]` 和 `[&]` 都能捕获 Lambda 所在类的 this，若仅仅想捕获 this，也能这么写 `[this]`

https://blog.csdn.net/lixiaogang_theanswer/article/details/80905445

### 右值引用

lvalue 要么是指”可以放在赋值运算符左侧的表达式“，要么是指”有确定内存地址的表达式“；rvalue 被定义为”所有其他表达式“，即”不在内存中占有确定位置的表达式“

C++ 11 中的右值引用使用的符号是 &&，右值引用可以延长右值的生命周期，实质上就是将不具名（匿名）变量取了个别名

```cpp
int& b = 1;     // 编译错误! 1 是右值，不能够使用左值引用
int&& b = 1;    // 实质上就是将不具名（匿名）变量取了个别名
```

总结：其中 `T` 是一个具体类型：

- 左值引用， 使用 `T&`, 只能绑定左值
- 右值引用， 使用 `T&&`， 只能绑定右值
- 常量左值， 使用 `const T&`, 既可以绑定左值又可以绑定右值
- _已命名的右值引用，编译器会认为是个左值_

右值引用的两大用途：**移动语意**、**完美转发**

#### 移动语意

https://zhuanlan.zhihu.com/p/85668787

首先介绍什么是移动构造函数，

```cpp
class myVector
{
    int size;
    double* array;

public:
    // 复制构造函数
    myVector(const myVector& rhs)
    {
        std::cout << "Copy Construct\n";
        size = rhs.size;
        array = new double[size];
        for(int i = 0; i < size; i++)
        {
            array[i] = rhs.array[i];
        }
    }

    myVector(int n)
    {
        size = n;
        array = new double[n];
    }
};

void foo(myVector v)
{
    /* Do something */
}

// 假设有一个函数，返回值是一个 MyVector
myVector createMyVector();

int main()
{
    // createMyVector 会返回一个临时的右值
    // 传参过程中会调用拷贝构造函数
    // 多余地被复制一次
    // 虽然大部分情况下会被编译器优化掉
    foo(createMyVector());
}
```

解决方法，添加一个移动构造函数

```cpp
// 移动构造函数
myVector(myVector&& rhs)
{
    std::cout << "Move Constructor\n";
    size = rhs.size;
    array = rhs.array;
    rhs.size = 0;
    rhs.array = nullptr;
}
```

那么，`foo(createMyVector())` 就不会调用拷贝构造函数，而会调用移动构造函数

再介绍移动语意（`std::move`）。移动语义可以将左值转化为右值引用

```cpp
int a = 1; // 左值
int &b = a; // 左值引用

// 移动语意: 转换左值为右值引用
int &&c = std::move(a);

void printInt(int& i) {
    cout << "lval ref: " << i << endl;
}
void printInt(int&& i) {
    cout << "rval ref: " << i << endl;
}

int main() {
    int i = 1;

    // 调用 printInt(int&), i是左值
    printInt(i);

    // 调用 printInt(int&&), 6是右值
    printInt(6);

    // 调用 printInt(int&&)，移动语意
    printInt(std::move(i));
}
```

为什么需要移动语意？

- **避免无谓的复制，提高程序性能**

假如 reusable 在调用 `foo` 之后就不再被使用了，可以使用移动语意。**移动语义可以将左值转化为右值引用，右值引用可以调用移动构造函数**

```cpp
int main()
{
    myVector reusable = createMyVector();
    // 这里会调用 myVector 的移动构造函数
    foo(std::move(reusable));
    // No use of reusable anymore
}
```

#### 完美转发

完美转发，就是为了让我们在传递参数的时候，保持原来的参数类型（左引用保持左引用，右引用保持右引用）

参数转发：

```cpp
void foo(myVector& v) {}

void foo(myVector&& v) {}

// relay 函数中对 arg 进行了参数转发
template <typename T> void relay(T arg)
{
    foo(arg);
}

int main()
{
    myVector reusable = reateMyVector();

    // 拷贝构造函数
    relay(reusable);

    // 移动构造函数
    relay(createMyVector());
}
```

无论 `relay` 中 arg 为左值还是右值，普通传参都会将参数作为左值进行转发，所以 `foo` 总会接受到一个左值

所以，我们需要改写上文的 `relay` 函数，借助 `std::forward`

```cpp
template <typename T> void relay(T&& arg)
{
    foo(std::forward<T>(arg));
}
```

于是，`relay(reusable)` 调用 `foo(myVector&)`；`relay(createMyVector())` 调用 `foo(myVector&&)`

<span style="color: gray;">引用折叠原则没看</span>

## 一些注意点

- 对象使用 new 和不使用 new 的区别：https://blog.csdn.net/cscmaker/article/details/7019977
  - 堆空间还是栈空间

- 构造函数要写成 public，private 只能被成员函数和友元访问，否则创建对象时，对象无法访问构造函数

- 编译只对一个文件进行编译，生成 `.s` 文件（汇编代码）；汇编阶段把汇编代码变可执行文件 `.o`

- 当使用 `extern` 关键字修饰变量（未初始化），表示变量声明。当在另一个文件中，为 `extern` 关键字修饰的变量赋值时，表示变量定义。**声明可以拷贝 n 次，但是定义只能定义一次**

- `include` 双引号表当前目录找，尖括号表示引用标准库头文件，在系统目录

- 初始化列表（**构造函数中进行的是赋值**）：

  - 更高效，可以少调用一次默认构造函数
  - 哪些必须要用初始化列表初始化：https://blog.csdn.net/sinat_20265495/article/details/53670644
  - 初始化列表在构造函数执行前执行，他不能初始化静态成员，静态成员的初始化见上方。
  - 初始化方式不是按照列表的的顺序，而是按照变量声明的顺序

- C++ 中子类隐藏父类同名函数（只需同名，参数、返回值无关）、变量；Java 中必须参数、返回值相同才能隐藏父类方法  
  **指的是子类引用指向子类对象（不是动态绑定）**  
  <img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/17145ecf5c2950d4-1.png" width="70%"/>

- 静态成员函数没有 this 指针，因为 this 指向调用该成员函数的那个对象，而静态成员函数属于整个类拥有

- \#ifdef \#endif （一般写在头文件里）作用：防止头文件被多次引用，https://blog.csdn.net/fly_yr/article/details/39964035

- extern "C"：`extern "C"` 的作用是让 C++ 编译器将 `extern "C"` 声明的代码当作 C 语言代码处理，可以避免 C++ 因符号修饰导致代码不能和 C 语言库中的符号进行链接的问题。`void foo(int x, int y)` 函数被 C 编译器修饰后在符号库中的名字是 `_foo`，而 C++ 编译器则会产生像 `_foo_int_int` 之类的名字。https://interview.huihut.com/#/?id=extern-quotcquot

  一般用于混合编程中，C++ 代码调用 C 语言代码

- 调试宏：https://blog.csdn.net/u011192270/article/details/47622311

- explicit：修饰单参数的构造函数时，可以防止隐式转换和赋值初始化

  ```cpp
  class A
  {
  public:
      explicit A(int a)
      {
          cout << "A(int a)" << endl;
      }
      A(const A& a)
      {
          cout << "A(const A& a)" << endl;
      }

  private:
      int _a;
  };

  void doA(A a) {}

  int main()
  {
      A a1(1);
      // 赋值初始化不通过
      A a2 = 1;
      // explicit 修饰构造函数的对象不可以从 int 到 A 的隐式转换
      doA(1);
  }
  ```

- assert：断言，是宏，而非函数。用于判断一个表达式，在表达式条件为 false 的时候触发异常

- sizeof()

  - 对数组，得到整个数组所占空间大小
  - 对指针，得到指针本身所占空间大小

- 命名空间：可作为附加信息来区分不同库中相同名称的函数、类、变量等。https://www.runoob.com/cplusplus/cpp-namespaces.html

- using：using 声明和指示。https://interview.huihut.com/#/?id=using

- :: 范围解析运算符，例子：https://interview.huihut.com/#/?id=-%e8%8c%83%e5%9b%b4%e8%a7%a3%e6%9e%90%e8%bf%90%e7%ae%97%e7%ac%a6
  1. 全局作用域符（`::name`）：用于类型名称（类、类成员、成员函数、变量等）前，表示作用域为全局命名空间
  2. 类作用域符（`class::name`）：用于表示指定类型的作用域范围是具体某个类的
  3. 命名空间作用域符（`namespace::name`）:用于表示指定类型的作用域范围是具体某个命名空间的

- ⭐ 为何 static / const 成员函数不能为 virtual？
  - static 成员函数没有 this 指针，而 vptr 是通过 this 指针访问的
  - const 修饰符用于表示函数不能修改成员变量的值，该函数必须是含有 this 指针的类成员函数

- ⭐ 如何定义一个只能在堆上（栈上）生成对象的类？https://interview.huihut.com/#/?id=%e5%a6%82%e4%bd%95%e5%ae%9a%e4%b9%89%e4%b8%80%e4%b8%aa%e5%8f%aa%e8%83%bd%e5%9c%a8%e5%a0%86%e4%b8%8a%ef%bc%88%e6%a0%88%e4%b8%8a%ef%bc%89%e7%94%9f%e6%88%90%e5%af%b9%e8%b1%a1%e7%9a%84%e7%b1%bb%ef%bc%9f

- **定位 new**（placement new）允许我们向 new 传递额外的地址参数，从而在预先指定的内存区域创建对象。相关问题：如何在指定内存上调用类的构造函数

  ```cpp
  new (place_address) type
  new (place_address) type (initializers)
  new (place_address) type [size]
  new (place_address) type [size] { braced initializer list }
  ```

- 成员函数不占用类空间，存在代码区。https://blog.csdn.net/fuzhongmin05/article/details/59112081

- ⭐ 参数列表变量计算顺序：https://blog.csdn.net/xidiancoder/article/details/49160317 需要注意几点：

  - 在将参数入栈前，编译器会先把参数的的表达式都处理掉，哪怕这些运算会改变其中某些参数的值
  - 对于 a++ 操作，编译器会开辟一个缓冲区来保存当前 a 的值，然后再对 a 操作，取值时是从缓冲区取，而不是直接从 a 的内存地址里取
  - 参数从右到左入栈  
    <img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/1715f67c6aace7e7.png" width="50%"/>

- main 函数执行前后会做什么？

  - 全局对象的构造函数会在 main 函数之前执行，全局对象的析构函数会在 main 函数之后执行
  - 一些全局变量、对象和静态变量、对象的初始化在 main 函数之前执行，<font color=gray>而 main 函数执行完后，还要去执行一些诸如释放空间、释放资源使用权等操作</font>

- strlen(char\*) 用于求 char\* 类型字符串的长度，string 类型字符串用 string.size() 求。sizeof(type) 用于求数据类型所占用空间的字节数

- strcpy(char *dest, const char *src)：把 src 所指向的字符串复制到 dest，若 dest 长度不够，会造成缓冲溢出（可能会覆盖其他变量？）。memcpy 可以指定拷贝长度

- 指针存在哪里？

  - 指针就是一个普通的变量，若在 main 函数中，指针和 int 型变量一样，是一个局部变量，那就存在栈里；在 new 出来的类对象中，指针是一个成员变量，存在堆里

- const 和 define 不同点：https://www.cnblogs.com/xumaomao/articles/11049541.html
  - 编译器处理不同
  - 定义域不同
  - 存储方式不同
  - 类型和安全检查不同
  - 是否可以做函数参数

- sizeof 空类为 1。那是被编译器插进去的一个 char ，使得这个 class 的不同实体（object）在内存中配置独一无二的地址

- `char *c = "1224"` 这样得到的是 `const char*`，不能改变。而 `char temp[] = "1224"; char *c = temp` 得到的才是`char*`

经典面试题：
https://www.cnblogs.com/yjd_hycf_space/p/7495640.html
