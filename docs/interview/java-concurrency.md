?> 摘录自 [CS-Notes](https://cyc2018.github.io/CS-Notes/#/notes/Java%20%E5%B9%B6%E5%8F%91)

## 并发与并行
- **并发：** 同一时间段，多个任务都在执行 (单位时间内不一定同时执行)
- **并行：** 单位时间内，多个任务同时执行

## 为什么要使用多线程呢?
- **从计算机底层来说：** 线程可以比作是轻量级的进程，是**程序执行的最小单位**，线程间的切换和调度的**成本**远远小于进程。另外，多核 CPU 时代意味着多个线程可以同时运行，这减少了线程上下文切换的开销
- **从当代互联网发展趋势来说：** 现在的系统动不动就要求百万级甚至千万级的并发量，而多线程并发编程正是开发高并发系统的基础，利用好多线程机制可以大大提高系统整体的并发能力以及性能

## 使用多线程可能带来什么问题?
内存泄漏、上下文切换、死锁还有受限于硬件和软件的资源闲置问题

## 什么是上下文切换?
当一条线程的时间片用完后，操作系统会暂停该线程，并保存该线程相应的信息，然后再随机选择一条新线程去执行，这个过程就称为“线程的上下文切换”。**任务从保存到再加载的过程就是一次上下文切换**。这可能是操作系统中时间消耗最大的操作

### 上下文切换的过程
1. 暂停正在执行的线程
2. 保存该线程的相关信息（如：执行到哪一行、程序计算的中间结果等）
3. 从就绪队列中随机选一条线程
4. 读取该线程的上下文信息，继续执行

## ⭐ 为什么我们调用 start() 方法时会执行 run() 方法，为什么我们不能直接调用 run() 方法？

new 一个 Thread，线程进入了新建状态；调用 start() 方法，会启动一个线程并使线程进入了就绪状态，当分配到时间片后就可以开始运行了。 start() 会执行线程的相应准备工作，然后自动执行 run() 方法的内容，这是真正的多线程工作。 而直接执行 run() 方法，会把 run 方法当成一个 main 线程下的普通方法去执行，并不会在某个线程中执行它，所以这并不是多线程工作

**总结： 调用 start 方法方可<span style="color: red;">启动线程</span>并使线程进入就绪状态，而 run 方法只是 thread 的一个普通方法调用，还是在主线程里执行**


<span style="font-size: 18px">**注**：</span><a href="https://cyc2018.github.io/CS-Notes/#/notes/Java 并发" target="_blank">CS-Notes</a> 中有许多好的代码示例

---
## 使用线程的三种方法
多对象多线程 和 一个对象多线程

- 实现 Runnable 接口：使用 Runnable 实例再创建一个 Thread 实例，然后调用 Thread 实例的 start() 方法来启动线程

```java
public class MyRunnable implements Runnable {
    @Override
    public void run() {
        // ...
    }
}
public static void main(String[] args) {
    MyRunnable instance = new MyRunnable();
    Thread thread = new Thread(instance);
    thread.start();
}
```

- 实现 Callable 接口：与 Runnable 相比，Callable 可以有返回值，返回值通过 FutureTask 进行封装
- 继承 Thread 类：同样也是需要实现 run() 方法，因为 Thread 类也实现了 Runable 接口

```java
public class MyThread extends Thread {
    public void run() {
        // ...
    }
}
public static void main(String[] args) {
    MyThread mt = new MyThread();
    mt.start();
}
```

### 实现接口 VS 继承 Thread
实现接口会更好一些，因为：
- Java 不支持多重继承，因此继承了 Thread 类就无法继承其它类，但是可以实现多个接口
- 类可能只要求可执行就行，继承整个 Thread 类开销过大
- 两者都能实现资源共享，因为 Thread 实现了 Runnable 接口，当然也能做了

## 基础线程机制
### Executor
Executor **管理多个异步任务的执行**，而无需程序员**显式地**管理线程的生命周期。这里的异步是指多个任务的执行互不干扰，不需要进行同步操作。除此之外，还有助于避免 this 逃逸问题

> 补充：this 逃逸是指在构造函数返回之前其他线程就持有该对象的引用。调用尚未构造完全的对象的方法可能引发令人疑惑的错误

Executor 框架不仅包括了线程池的管理，还提供了线程工厂、队列以及拒绝策略等，Executor 框架让并发编程变得更加简单

主要有三种 Executor：

- CachedThreadPool：一个任务创建一个线程
- FixedThreadPool：所有任务只能使用固定大小的线程
- SingleThreadExecutor：相当于大小为 1 的 FixedThreadPool

#### 线程池的好处 
> 池化技术相比大家已经屡见不鲜了，线程池、数据库连接池、Http 连接池等等都是对这个思想的应用。池化技术的思想主要是为了减少每次获取资源的消耗，提高对资源的利用率。

**线程池**提供了一种限制和管理资源（包括执行一个任务）。 每个**线程池**还维护一些基本统计信息，例如已完成任务的数量。

这里借用《Java 并发编程的艺术》提到的来说一下**使用线程池的好处**：

- **降低资源消耗**。通过*重复利用*已创建的线程降低线程创建和销毁造成的消耗。
- **提高响应速度**。当任务到达时，任务可以不需要的等到线程创建就能立即执行。
- **提高线程的可管理性**。线程是稀缺资源，如果无限制的创建，不仅会消耗系统资源，还会降低系统的稳定性，使用线程池可以进行统一的分配，调优和监控

### Daemon
守护线程是程序运行时在后台提供服务的线程，不属于程序中不可或缺的部分。当所有非守护线程结束时，程序也就终止，同时会杀死所有守护线程。main() 属于非守护线程

Daemon 的作用是为其他线程的运行提供便利服务，守护线程最典型的应用就是 GC，它就是一个很称职的守护者
### sleep()
Thread.sleep(millisec) 方法会休眠当前正在执行的线程  
sleep() 可能会抛出 InterruptedException，因为异常不能跨线程传播回 main() 中，因此必须在本地进行处理

```java
public void run() {
    try {
        Thread.sleep(3000);
    } catch (InterruptedException e) {
        e.printStackTrace();
    }
}
```

### yield()
对静态方法 Thread.yield() 的调用声明了当前线程已经完成了生命周期中最重要的部分，可以切换给其它线程来执行。使用 yield() 的目的是让**相同优先级**的线程之间能适当地轮转执行

**区别**：线程执行 sleep() 方法后转入阻塞（blocked）状态，而执行 yield() 方法后转入就绪（ready）状态

```java
public class TestYield {
    public static void main(String[] args) {
        MyThread t1 = new MyThread("t1");
        MyThread t2 = new MyThread("t2");
        t1.start();
        t2.start();
    }
}

class MyThread extends Thread {
    MyThread(String s) {
        super(s);
    }
    public void run() {
        for (int i = 1; i <= 100; i++) {
            System.out.println(getName() + ":" + i);

            if (i == 0) {
                yield();
            }
        }
    }
}
```

## 中断
### InterruptedException
通过调用一个线程的 interrupt() 来中断该线程，如果该线程处于**阻塞**、**限期等待**或者**无限期等待**状态，那么就会抛出 InterruptedException，从而提前结束该线程。但是不能中断 I/O 阻塞和 synchronized 锁阻塞
### interrupted()
调用 interrupt() 方法会设置线程的中断标记，此时调用 interrupted() 方法会返回 true  
可以在循环体中使用 interrupted() 方法来判断线程是否处于中断状态，从而提前结束线程
### Executor 的中断操作
调用 Executor 的 shutdown() 方法会等待线程都执行完毕之后再关闭，但是如果调用的是 shutdownNow() 方法，则相当于调用每个线程的 interrupt() 方法

## 互斥同步
Java 提供了两种**锁机制**来控制多个线程对<span style="color: red;font-weight: 500;font-size: 16px">共享资源的互斥访问</span>，第一个是 JVM 实现的 synchronized，而另一个是 JDK 实现的 ReentrantLock

synchronized 可以保证被它修饰的方法或者代码块在任意时刻只能有一个线程执行

### synchronized
#### 同步一个代码块
多个线程作用于同一个对象才会起效，[例子](https://cyc2018.github.io/CS-Notes/#/notes/Java%20%E5%B9%B6%E5%8F%91?id=synchronized)

```java
public void func() {
    synchronized (this) {
        // ...
    }
}
```

#### 同步一个方法
```java
public synchronized void func() {
    // ...
}
```
它和同步代码块一样，作用于同一个对象

#### 同步一个类
**不同点**：作用于整个类，也就是说两个线程调用同一个类的不同对象上的这种同步语句，也会进行同步

```java
public class SynchronizedExample {
    public void func2() {
        synchronized (SynchronizedExample.class) {
            for (int i = 0; i < 10; i++) {
                System.out.print(i + " ");
            }
        }
    }
}
```

#### 同步一个静态方法
作用于一个类

### ReentrantLock
```java
public class LockExample {
    private Lock lock = new ReentrantLock();

    public void func() {
        lock.lock();
        try {
            for (int i = 0; i < 10; i++) {
                System.out.print(i + " ");
            }
        } finally {
            lock.unlock(); // 确保释放锁，从而避免发生死锁。
        }
    }
}
```

### 比较
- 都是可重入锁（又名递归锁）：可重入锁指的是可重复可递归调用的锁，在外层使用锁之后，在内层仍然可以使用，并且不发生死锁（前提得是同一个对象或者 class）。  
即，当线程请求一个由其它线程持有的对象锁时，该线程会阻塞，而当线程请求由自己持有的对象锁时，如果该锁是重入锁，请求就会成功，否则阻塞

```java
public class WhatReentrant {
    public static void main(String[] args) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                synchronized (this) {
                    System.out.println("第1次获取锁，这个锁是：" + this);
                    int index = 1;
                    while (true) {
                        synchronized (this) {
                            System.out.println("第" + (++index) + "次获取锁，这个锁是：" + this);
                        }
                        if (index == 10) {
                            break;
                        }
                    }
                }
            }
        }).start();
    }
}
```


- 锁的实现  
synchronized 是 JVM 实现的，而 ReentrantLock 是 JDK 实现的

- 性能  
新版本 Java 对 synchronized 进行了很多优化，例如自旋锁等，synchronized 与 ReentrantLock 大致相同

- **等待可中断**  
当持有锁的线程长期不释放锁的时候，正在等待的线程可以选择放弃等待，改为处理其他事情。  
ReentrantLock 可中断，而 synchronized 不行。

- **公平锁**  
公平锁是指多个线程在等待同一个锁时，必须按照**申请锁的时间顺序**来依次获得锁。  
synchronized 中的锁是非公平的，ReentrantLock 默认情况下也是非公平的（为什么？），但是也可以是公平的

- 锁绑定多个条件  
一个 ReentrantLock 可以同时绑定多个 Condition 对象

### 使用选择
除非需要使用 ReentrantLock 的高级功能，否则优先使用 synchronized。这是因为 synchronized 是 JVM 实现的一种锁机制，JVM 原生地支持它，而 ReentrantLock 不是所有的 JDK 版本都支持。并且使用 synchronized 不用担心没有释放锁而导致死锁问题，因为 JVM 会确保锁的释放

## 线程之间的协作
当多个线程可以一起工作去解决某个问题时，如果某些部分必须在其它部分之前完成，那么就需要对线程进行协调（同步？）

### join()
把指定的线程加入到当前线程。在线程中调用另一个线程的 join() 方法，会将当前线程挂起，而不是忙等待，直到目标线程结束

### wait() notify() notifyAll()

调用 wait() 使得线程等待某个条件满足，线程在等待时会被挂起，当其他线程的运行使得这个条件满足时，**其它线程**会调用 notify() 或者 notifyAll() 来唤醒挂起的线程

它们都属于 Object 的一部分，而不属于 Thread

只能用在同步方法或者同步控制块中使用，否则会在运行时抛出 IllegalMonitorStateException

使用 wait() 挂起期间，**线程会释放锁**。这是因为，如果没有释放锁，那么其它线程就无法进入对象的同步方法或者同步控制块中，那么就无法执行 notify() 或者 notifyAll() 来唤醒挂起的线程，造成死锁

#### wait() 和 sleep() 的区别
本质区别 Thread.sleep 只会让出 CPU，不会导致锁行为的改变 Object.wait 不仅让出 CPU，还会释放已经占有的同步资源锁

- wait 属于 Object 类，sleep 属于 Thread 类
- wait 会释放对象锁，而 sleep 不会
- wait 需要在同步块中使用，sleep 可以在任何地方使用
- sleep 需要捕获异常、wait 不需要


### await() signal() signalAll()
java.util.concurrent 类库中提供了 Condition 类来实现线程之间的协调，可以在 Condition 上调用 await() 方法使线程等待，其它线程调用 signal() 或 signalAll() 方法唤醒等待的线程

相比于 wait() 这种等待方式，await() 可以**指定等待的条件**，因此更加灵活

使用 Lock 来获取一个 Condition 对象

## 线程状态
<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/v2-20edff079dc147b795e08261be1161f4_r.jpg" width="90%"/>

一个线程只能处于一种状态，并且这里的线程状态特指 Java 虚拟机的线程状态，不能反映线程在特定操作系统下的状态

### 新建（New）
创建后尚未启动

### 可运行（Runnable）
可能正在运行，也可能正在等待 CPU 时间片。

包含了操作系统线程状态中的 Running 和 Ready

### 阻塞（Blocked）
等待获取一个排它锁，如果其线程释放了锁就会结束此状态

### 无限期等待（Waiting）
等待其它线程**显式地**唤醒，否则不会被分配 CPU 时间片

| 进入方法                                   | 退出方法                             |
| ------------------------------------------ | ------------------------------------ |
| 没有设置 Timeout 参数的 Object.wait() 方法 | Object.notify() / Object.notifyAll() |
| 没有设置 Timeout 参数的 Thread.join() 方法 | 被调用的线程执行完毕                 |
| LockSupport.park() 方法                    | LockSupport.unpark(Thread)           |

### 限期等待（Timed Waiting）
无需等待其它线程显式地唤醒，在一定时间之后会被系统自动唤醒。

- 调用 Thread.sleep() 方法使线程进入限期等待状态时，常常用“使一个线程睡眠”进行描述。  
调用 Object.wait() 方法使线程进入限期等待或者无限期等待时，常常用“挂起一个线程”进行描述

- **阻塞和等待**的区别在于，阻塞是被动的，它是在等待获取一个排它锁。而等待是主动的，通过调用 Thread.sleep() 和 Object.wait() 等方法进入

| 进入方法                                 | 退出方法                                        |
| ---------------------------------------- | ----------------------------------------------- |
| Thread.sleep() 方法                      | 时间结束                                        |
| 设置了 Timeout 参数的 Object.wait() 方法 | 时间结束 / Object.notify() / Object.notifyAll() |
| 设置了 Timeout 参数的 Thread.join() 方法 | 时间结束 / 被调用的线程执行完毕                 |
| LockSupport.parkNanos() 方法             | LockSupport.unpark(Thread)                      |
| LockSupport.parkUntil() 方法             | LockSupport.unpark(Thread)                      |

### 死亡（Terminated）
可以是线程结束任务之后自己结束，或者产生了异常而结束

## J.U.C - AQS
java.util.concurrent（J.U.C）大大提高了并发性能，AQS 被认为是 J.U.C 的核心

### CountDownLatch
允许一个或多个线程一直等待直到其他线程执行完毕才开始执行。

维护了一个计数器 cnt，每次调用 countDown() 方法会让计数器的值减 1，减到 0 的时候，那些因为调用 await() 方法而在等待的线程就会被唤醒

### CyclicBarrier
用来控制多个线程互相等待，只有当多个线程都到达时，这些线程才会继续执行。

线程执行 await() 方法之后计数器会减 1，并进行等待，直到计数器为 0

CyclicBarrier 的计数器通过调用 reset() 方法可以循环使用，所以它才叫做循环屏障

### Semaphore

Semaphore 类似于操作系统中的信号量，可以控制**对互斥资源的访问线程数**

## J.U.C - 其它组件
看 <a href="https://cyc2018.github.io/CS-Notes/#/notes/Java%20%E5%B9%B6%E5%8F%91?id=%e5%85%ab%e3%80%81juc-%e5%85%b6%e5%ae%83%e7%bb%84%e4%bb%b6" target="_blank">Cyc 2018</a>
### FutureTask
FutureTask 可用于异步获取执行结果或取消执行任务的场景

### BlockingQueue
java.util.concurrent.BlockingQueue 接口有以下阻塞队列的实现：

-  **FIFO 队列** ：LinkedBlockingQueue、ArrayBlockingQueue（固定长度）
-  **优先级队列** ：PriorityBlockingQueue

提供了阻塞的 take() 和 put() 方法：如果队列为空 take() 将阻塞，直到队列中有内容；如果队列为满 put() 将阻塞，直到队列有空闲位置

### ForkJoin
主要用于并行计算中，和 MapReduce 原理类似，都是把大的计算任务拆分成多个小任务并行计算

## Java 内存模型
Java 内存模型试图屏蔽各种硬件和操作系统的内存访问差异，以实现让 Java 程序在各种平台下都能达到**一致的内存访问效果**

### 主内存与工作内存
所有的变量都存储在主内存中，每个线程还有自己的工作内存，工作内存存储在高速缓存或者寄存器中，保存了该线程使用的变量的主内存副本拷贝

线程只能直接操作工作内存中的变量，不同线程之间的变量值传递需要通过主内存来完成

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200322164546.png" width="70%">

### 内存间交互操作
Java 内存模型定义了 8 个操作来完成主内存和工作内存的交互操作

- read：把一个变量的值从主内存传输到工作内存中
- load：在 read 之后执行，把 read 得到的值放入工作内存的变量副本中
- use：把工作内存中一个变量的值传递给执行引擎
- assign：把一个从执行引擎接收到的值赋给工作内存的变量
- store：把工作内存的一个变量的值传送到主内存中
- write：在 store 之后执行，把 store 得到的值放入主内存的变量中
- lock：作用于主内存的变量
- unlock

### 内存模型三大特性
#### 原子性
Java 内存模型保证了 read、load、use、assign、store、write、lock 和 unlock 操作具有原子性，例如对一个 int 类型的变量执行 assign 赋值操作，这个操作就是原子性的。但是 Java 内存模型允许虚拟机将没有被 volatile 修饰的 64 位数据（long，double）的读写操作划分为两次 32 位的操作来进行，即 load、store、read 和 write 操作可以不具备原子性

单个操作的原子性不能保证线程安全。而 AtomicInteger 能保证多个线程修改的原子性，除了使用原子类之外，也可以使用 synchronized 互斥锁来保证操作的原子性

#### 可见性
可见性指当一个线程修改了共享变量的值，其它线程能够立即得知这个修改。Java 内存模型是通过在变量修改后将新值**立刻**同步回主内存（而不是工作内存），在变量读取前从主内存刷新了变量值

主要有三种实现可见性的方式：

- <span style="color: red">volatile</span> 修饰变量
- synchronized，对一个变量执行 unlock 操作之前，必须把变量值同步回主内存（对性能影响大）
- final，被 final 关键字修饰的字段在构造器中一旦初始化完成，并且没有发生 this 逃逸（其它线程通过 this 引用访问到初始化了一半的对象），那么其它线程就能看见 final 字段的值

#### 有序性
有序性是指：在线程内观察，所有操作都是有序的。在一个线程观察另一个线程，所有操作都是无序的，无序是因为发生了指令重排序

### volatile
看程序员小灰的<a href="https://blog.csdn.net/bjweimengshu/article/details/78769623" target="_blank">文章</a>

volatile 可以保证可见性，不保证原子性。volatile 可以禁止指令重排，在一个变量被 volatile 修饰后，JVM 会插入内存屏障指令

### 指令重排
指令重排是指 JVM 在编译 Java 代码的时候，或者 CPU 在执行机器码的时候，对现有的指令顺序进行重新排序

指令重排的目的是为了在不改变程序执行结果的前提下，优化程序的运行效率。需要注意的是，这里所说的不改变执行结果，指的是不改变**单线程**下的程序执行结果

看程序员小灰的<a href="https://blog.csdn.net/bjweimengshu/article/details/78830258" target="_blank">文章</a>

### 先行发生原则
可以用 volatile 和 synchronized 来保证有序性。除此之外，JVM 还规定了先行发生原则，让一个操作无需控制就能先于另一个操作完成

[Cyc2018 有图解](https://cyc2018.github.io/CS-Notes/#/notes/Java%20%E5%B9%B6%E5%8F%91?id=%e5%85%88%e8%a1%8c%e5%8f%91%e7%94%9f%e5%8e%9f%e5%88%99)

-  单一线程原则
> Single Thread rule

在**一个线程内**，在程序前面的操作先行发生于后面的操作

- 管程锁定规则
> Monitor Lock Rule

一个 unlock 操作先行发生于后面对同一个锁的 lock 操作

- volatile 变量规则
> Volatile Variable Rule

对一个 volatile 变量的写操作先行发生于后面对这个变量的读操作


- 线程启动规则
> Thread Start Rule

Thread 对象的 start() 方法调用先行发生于此线程的每一个动作


- 线程加入规则
> Thread Join Rule

Thread 对象的结束先发生于 join() 方法返回

- 线程中断规则
> Thread Interruption Rule

对线程 interrupt() 方法的调用先行发生于被中断线程的代码检测到中断事件的发生，可以通过 interrupted() 方法检测到是否有中断发生

- 对象终结规则
> Finalizer Rule

一个对象的初始化完成（构造函数执行结束）先行发生于它的 finalize() 方法的开始

- 传递性
> Transitivity

如果操作 A 先行发生于操作 B，操作 B 先行发生于操作 C，那么操作 A 先行发生于操作 C


## 线程安全

多个线程不管以何种方式访问某个类，并且在主调代码中**不需要进行同步**，都能表现正确的行为。

线程安全有以下几种实现方式：

### 不可变
不可变（Immutable）的对象一定是线程安全的，不需要再采取任何的线程安全保障措施。只要一个不可变的对象被正确地构建出来，永远也不会看到它在多个线程之中处于不一致的状态。多线程环境下，应当尽量使对象成为不可变，来满足线程安全

不可变的类型：
- final 关键字修饰的基本数据类型
- String
- 枚举类型
- Number 部分子类，如 Long 和 Double 等数值包装类型，BigInteger 和 BigDecimal 等大数据类型。但同为 Number 的原子类 AtomicInteger 和 AtomicLong 则是可变的

### 互斥同步（悲观锁）
synchronized 和 ReentrantLock

互斥同步最主要的问题就是线程阻塞和唤醒所带来的**性能**（涉及用户态和内核态的转换）问题，因此这种同步也称为阻塞同步

互斥同步属于一种**悲观**的并发策略，悲观锁认为自己在使用数据的时候一定有别的线程来修改数据，因此在获取数据的时候会先加锁，确保数据不会被别的线程修改（认为只要不去做正确的同步措施，那就肯定会出现问题）。

无论共享数据是否真的会出现竞争，它都要进行加锁（这里讨论的是概念模型，实际上虚拟机会优化掉很大一部分不必要的加锁）、用户态核心态转换、维护锁计数器和检查是否有被阻塞的线程需要唤醒等操作

### 非阻塞同步（乐观锁）
#### CAS
看程序员小灰的<a href="https://blog.csdn.net/bjweimengshu/article/details/78949435" target="_blank">文章</a>

随着硬件指令集的发展，我们可以使用基于冲突检测的**乐观并发策略**：先进行操作，如果没有其它线程争用共享数据，那操作就成功了，否则采取补偿措施（不断地重试，直到成功为止，这个过程叫**自旋**）。这种乐观的并发策略的许多实现都不需要将线程阻塞，因此这种同步操作称为非阻塞同步

乐观锁需要操作和冲突检测这两个步骤具备原子性，这里就不能再使用互斥同步来保证了，只能靠硬件来完成。硬件支持的原子性操作最典型的是：比较并交换（Compare-and-Swap，CAS）。CAS 指令需要有 3 个操作数，分别是内存地址 V、旧的预期值 A 和新值 B。当执行操作时，只有当 V 的值等于 A，才将 V 的值更新为 B

CAS 机制所保证的只是一个变量的原子性操作，而不能保证整个代码块的原子性

#### AtomicInteger

J.U.C 包里面的整数原子类 AtomicInteger 的方法调用了 <span style="color: red">Unsafe 类</span>的 CAS 操作

代码看 <a href="https://cyc2018.github.io/CS-Notes/#/notes/Java%20%E5%B9%B6%E5%8F%91?id=_2-atomicinteger" target="_blank">Cyc2018</a>

#### ABA

如果一个变量初次读取的时候是 A 值，它的值被改成了 B，后来又被改回为 A，那 CAS 操作就会误认为它从来没有被改变过

J.U.C 包提供了一个带有标记的原子引用类 AtomicStampedReference 来解决这个问题，它可以通过控制变量值的版本来保证 CAS 的正确性。大部分情况下 ABA 问题不会影响程序并发的正确性，如果需要解决 ABA 问题，改用传统的互斥同步可能会比原子类更高效

### 无同步方案
要保证线程安全，并不是一定就要进行同步。如果一个方法本来就不涉及共享数据，那它自然就无须任何同步措施去保证正确性

#### 栈封闭
多个线程访问同一个**方法**的局部变量时，不会出现线程安全问题，因为局部变量存储在虚拟机栈中，属于线程私有的

```java
public class StackClosedExample {
    public void add100() {
        int cnt = 0;
        for (int i = 0; i < 100; i++) {
            cnt++;
        }
        System.out.println(cnt);
    }
}
public static void main(String[] args) {
    StackClosedExample example = new StackClosedExample();
    ExecutorService executorService = Executors.newCachedThreadPool();
    executorService.execute(() -> example.add100());
    executorService.execute(() -> example.add100());
    executorService.shutdown();
}
output: 100 100
```

#### 线程本地存储（Thread Local Storage）
如果一段代码中所需要的数据必须与其他代码共享，那就看看这些共享数据的代码是否能保证在同一个线程中执行。如果能保证，我们就可以把共享数据的可见范围限制在同一个线程之内，这样，无须同步也能保证线程之间不出现数据争用的问题

<img src="https://i.loli.net/2020/03/23/AiN2wy7eJS3dWKE.png" width="70%">

**ThreadLocal 从理论上讲并不是用来解决多线程并发问题的，因为根本不存在多线程竞争**

尽可能在每次使用 ThreadLocal 后手动调用 remove()，避免内存泄漏

#### 可重入代码（Reentrant Code）：可以被中断的函数
这种代码也叫做纯代码（Pure Code），可以在代码执行的任何时刻**中断**它，转而去执行另外一段代码（包括递归调用它本身），而在控制权返回后，原来的程序不会出现任何错误

可重入代码有一些共同的特征，例如不依赖存储在堆上的数据和公用的系统资源、用到的状态量都由参数中传入、不调用非可重入的方法等。  
不可重入的函数由于使用了一些系统资源，比如全局变量区，中断向量表等，所以它如果被中断的话，可能会出现问题，这类函数是不能运行在多任务环境下的

可重入函数未必是线程安全的；线程安全函数未必是可重入的

## 锁优化
这里的锁优化主要是指 JVM 对 synchronized 的优化

### 自旋锁
互斥同步进入阻塞状态（进入内核态）的开销都很大，应该尽量避免。在许多应用中，共享数据的锁定状态只会持续很短的一段时间。自旋锁的思想是让一个线程在请求一个共享数据的锁时**执行忙循环**（不断地判断锁是否能够被成功获取，直到获取到锁才会退出循环）一段时间，如果在这段时间内能获得锁，就可以避免进入阻塞状态。

自旋锁虽然能避免进入阻塞状态从而减少开销，但是它需要进行忙循环操作占用 CPU 时间，它只适用于共享数据的**锁定状态很短的场景**。

在 JDK 1.6 中引入了自适应的自旋锁。自适应意味着自旋的次数不再固定了，而是由前一次在同一个锁上的自旋次数及锁的拥有者的状态来决定

### 锁消除
锁消除是指对于被检测出不可能存在竞争的共享数据的锁进行消除，锁消除主要是通过逃逸分析来支持

### 锁粗化
如果一系列的连续操作都对同一个对象反复加锁和解锁，频繁的加锁操作就会导致性能损耗。

如果虚拟机探测到一串零碎的操作都对同一个对象加锁，将会把加锁的范围扩展（粗化）到整个操作序列的外部

### 无锁 VS 偏向锁 VS 轻量级锁 VS 重量级锁
锁存在对象头里。对象头里有 Mark Word（标记字段）、Klass Pointer（类型指针）

具体看下面的<a class="esa-anchor" href="#more" style="opacity: 1">美团文章</a>

-  无锁

无锁没有对资源进行锁定，所有的线程都能访问并修改同一个资源，但同时只有一个线程能修改成功。

无锁的特点就是修改操作在循环内进行，线程会不断的尝试修改共享资源。如果没有冲突就修改成功并退出，否则就会继续循环尝试。如果有多个线程修改同一个值，必定会有一个线程能修改成功，而其他修改失败的线程会不断重试直到修改成功。上面我们介绍的 CAS 原理及应用即是无锁的实现。无锁无法全面代替有锁，但无锁在某些场合下的性能是非常高的

-  偏向锁

是指当锁是偏向锁的时候，被另外的线程所访问，偏向锁就会升级为轻量级锁，其他线程会通过自旋的形式尝试获取锁，不会阻塞，从而提高性能

-  轻量级锁

多个线程竞争同步资源时，没有获取资源的线程自旋等待锁释放

当锁是偏向锁的时候，被另外的线程所访问，偏向锁就会升级为轻量级锁，其他线程会通过自旋的形式尝试获取锁，不会阻塞，从而提高性能

-  重量级锁

多个线程竞争同步资源时，没有获取资源的线程阻塞等待唤醒


### <span id="more">关于锁的更多</span>
[美团文章](https://tech.meituan.com/2018/11/15/java-lock.html)

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200323164343.png" width="70%"/>