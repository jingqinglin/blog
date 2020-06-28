容器主要包括 Collection 和 Map 两种，Collection 存储着对象的集合，而 Map 存储着键值对（两个对象）的映射表

## Collection
<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/image-20191208220948084.png" width="70%"/>

### Set（和数学中的集合一样，元素唯一）
- **HashSet（无序）:** 基于 HashMap 实现的，底层采用 HashMap 来保存元素
- **LinkedHashSet（遍历序和插入序一致）：** 存储结构是一个双向链表
- **TreeSet（会对元素进行排序）：** 红黑树（自平衡的排序二叉树）

带 "Hash" 的查找时间都是 $O(1)$，TreeSet 则为 $O(logN)$
### List（遍历序和插入序一致）
- ArrayList：基于动态数组实现，支持**随机访问**
- Vector：和 ArrayList 类似，但它是线程安全的
- LinkedList：基于双向链表实现，只能**顺序访问**，但是可以快速地在链表中间插入和删除元素（虽然插入和删除操作是 $O(1)$，但是找到插入或删除的位置还是需要 $O(n)$，所以**插、删操作相对于 ArrayList 并无优势**）。不仅如此，LinkedList 还可以用作栈、队列和双向队列

#### ArrayList 的动态数组
- System.arraycopy() 和 Arrays.copyOf() 的区别：copyOf() 调用了 arraycopy()
  - arraycopy() 参数里要写目标数组，将原数组拷贝到你自己定义的数组里，而且可以选择拷贝的起点和长度以及放入新数组中的位置
  - copyOf() 是系统自动在内部新建一个数组，并返回该数组

- 扩容的时候做的是右移操作，大数据的 2 进制运算，位移运算符比那些普通运算符的运算要快很多，`int newCapacity = oldCapacity + (oldCapacity >> 1)`

### Queue
- LinkedList：可以用它来实现双向队列。上图可以看到，它即实现了 List 接口，又实现了 Queue 接口
- PriorityQueue：基于堆结构实现，可以用它来实现优先队列

阻塞队列（BlockingQueue）被广泛使用在“生产者-消费者”问题中（在 [Java 并发](https://www.cnblogs.com/jingqinglin/articles/12577266.html)里有提到）

## Map
<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/image-20191208224757855.png" width="70%"/>

- **HashMap：** JDK1.8 之前 HashMap 由数组+链表组成的，数组是 HashMap 的主体，链表则是主要为了解决哈希冲突而存在的（“拉链法”解决冲突）。JDK1.8 以后在解决哈希冲突时有了较大的变化，当链表长度大于阈值（默认为 8）时，将链表转化为红黑树，以减少搜索时间
- LinkedHashMap（遍历序和插入序一致）：LinkedHashMap 继承自 HashMap，所以它的底层仍然是基于拉链式散列结构即由数组和链表或红黑树组成。另外，LinkedHashMap 在上面结构的基础上，增加了一条双向链表，保存了记录的插入顺序。同时通过对链表进行相应的操作，实现了访问顺序相关逻辑
- Hashtable：数组+链表组成的，数组是 HashMap 的主体，链表则是主要为了解决哈希冲突而存在的
- TreeMap：红黑树（自平衡的排序二叉树）

### Collection 与 Collections 的区别
- Collection 是一个接口，它提供了对集合对象进行基本操作的通用接口方法
- Collections 是集合类的一个工具类/帮助类，其中提供了一系列**静态方法**，用于对集合中元素进行排序、搜索以及线程安全等各种操作

### Collections.sort()
Collections.sort 方法底层就是调用的 Arrays.sort 方法，而 Arrays.sort 使用了两种排序方法，快速排序和优化的归并排序。

快速排序主要是对那些基本类型数据（int, short, long等）排序， 而归并排序用于对 Object 类型进行排序

### ArrayList 与 Vector 区别
1. Vector 线程安全。同步操作比较耗时
2. Arraylist 不是同步的
  
### HashMap 和 Hashtable 的区别
1. **线程是否安全：** HashMap 是非线程安全的，HashTable 是线程安全的；HashTable 内部的方法基本都经过 `synchronized` 修饰。（如果你要保证线程安全的话就使用 ConcurrentHashMap 吧！）
2. **效率：** 因为线程安全的问题，HashMap 要比 HashTable 效率高一点。另外，<span style="color :red;">HashTable 基本被淘汰</span>，不要在代码中使用它
3. 对 Null key 和 Null value 的支持：在 HashTable 中 put 进的键值只要有一个 null，直接抛出 NullPointerException，HashMap 允许 null
4. **初始容量大小和每次扩充容量大小的不同：** ①创建时如果不指定容量初始值，HashTable 默认的初始大小为 11，之后每次扩充，容量变为原来的 2n+1。HashMap 默认的初始化大小为 16。之后每次扩充，容量变为原来的 2 倍。②创建时如果给定了容量初始值，那么 HashTable 会直接使用你给定的大小，而 HashMap 会将其扩充为 2 的幂次方大小。也就是说 HashMap 总是使用 2 的幂作为哈希表的大小，<a class="esa-anchor" href="#HashMap" style="opacity: 1">后面</a>会介绍到为什么是 2 的幂次方
5. **底层数据结构：** JDK1.8 以后的 HashMap 在解决哈希冲突时有了较大的变化，当链表长度大于阈值（默认为 8）时，将链表转化为红黑树，以减少搜索时间。Hashtable 没有这样的机制

### HashMap 和 HashSet 区别
HashSet 底层是基于 HashMap 实现的

|                HashMap                 |                 HashSet                 |
| :------------------------------------: | :-------------------------------------: |
|            实现了 Map 接口             |              实现 Set 接口              |
|               存储键值对               |               仅存储对象                |
|     调用 `put()`向 map 中添加元素      |    调用 `add()`方法向 Set 中添加元素    |
| HashMap 使用**键（key）**计算 hashcode | HashSet 使用**成员对象**来计算 hashcode |

**如何检查重复**：先检查 hashcode，如果没有相同的值，那么无重复元素，可插入；如果发现有相同 hashcode 值的对象，这时会调用 equals() 方法来检查 hashcode 相等的对象是否真的相同

### <span id="HashMap">HashMap 的底层实现</span>
JDK1.8 之前 HashMap 底层是 **数组和链表** 结合在一起使用也就是 **链表散列**。HashMap 通过 key 的 hashCode 经过<a href="https://www.zhihu.com/question/20733617/answer/111577937" target="_blank">扰动函数</a>（减小碰撞率）处理过后得到 hash 值，然后通过 `(n - 1) & hash` 判断当前元素存放的位置（这里的 n 指的是数组的长度，而 & 相当于取余（%）操作。⭐在取余操作中，如果除数是 2 的幂次方则等价于被除数与除数减一的与（&）操作），如果当前位置存在元素的话，就判断该元素与要存入的元素的 hash 值以及 key 是否相同，如果相同的话，直接覆盖，不相同就通过拉链法解决冲突

JDK1.8 之后在解决哈希冲突时有了较大的变化，当链表长度大于阈值（默认为 8）时，将链表转化为红黑树，以减少搜索时间

<img src="https://i.loli.net/2020/03/13/Xsm7OZ1ix6RnMkh.png" width="70%"/>

#### 为什么 HashMap 不用 B+ 或其他平衡二叉树？
B+ 树适用于数据量较大的场景，数据量大就要存在磁盘上，B+ 树一个结点有多个关键字，可以减少磁盘 IO

### ConcurrentHashMap 和 Hashtable 的区别

ConcurrentHashMap 和 Hashtable 的区别主要体现在实现线程安全的方式上不同。

- **底层数据结构：** JDK1.7 的 ConcurrentHashMap 底层采用分段的数组+链表实现，JDK1.8 采用的数据结构跟 HashMap 的结构一样，数组+链表/红黑树。HashTable 和 JDK1.8 之前的 HashMap 的底层数据结构类似都是采用数组+链表的形式，数组是 HashMap 的主体，链表则是主要为了解决哈希冲突而存在的；
- 实现线程安全的方式（<span style="color :red;">重要</span>）

对比图：  
锁住整个 HashTable，效率低  
<img src="https://i.loli.net/2020/03/13/PgTqunRzKbsCa73.png" width="50%"/>  
JDK 1.7：  
<img src="https://i.loli.net/2020/03/13/ef2rt7cpEzP3X6Z.png" width="50%"/>  
JDK 1.8:  
<img src="https://i.loli.net/2020/03/13/EAdONCYrpUqS35h.png" width="50%">  

### ConcurrentHashMap 线程安全的实现方式
#### JDK1.7
首先将数据分为一段一段地存储，然后给每一段数据配一把锁，当一个线程占用锁访问其中一个段数据时，其他段的数据也能被其他线程访问。

**ConcurrentHashMap 是由 Segment 数组结构和 HashEntry 数组结构组成**

一个 ConcurrentHashMap 里包含一个 Segment 数组。Segment 的结构和 HashMap 类似，是一种数组和链表结构，一个 Segment 包含一个 HashEntry 数组，每个 HashEntry 是一个链表结构的元素，每个 Segment 守护着一个HashEntry数组里的元素，当对 HashEntry 数组的数据进行修改时，必须首先获得对应的 Segment 的锁

#### JDK1.8
ConcurrentHashMap 取消了 Segment 分段锁，采用 <a href="https://www.jianshu.com/p/d10256f0ebea" target="_blank" style="font-weight: bold;">CAS 和  synchronized</a> 来保证并发安全。数据结构跟 HashMap1.8 的结构类似，数组+链表/红黑树

synchronized 只锁定当前链表或红黑二叉树的首节点，这样只要 hash 不冲突，就不会产生并发，效率又提升 N 倍

CAS 操作用于无锁添加数组上的结点
- tabAt() 该方法用来获取数组中索引为 i 的 Node 元素
- casTabAt() 利用 CAS 操作设置数组中索引为 i 的元素
- setTabAt() 该方法用来设置数组中索引为 i 的元素

CAS 部分代码，具体分析见上述链接：

```java
// 通过 hash 定位 Node[] 数组的索引坐标，若该位置为空则使用 CAS 进行添加（即链表的头结点，添加失败则进入下次循环）
// no lock when adding to empty bin
else if ((f = tabAt(tab, i = (n - 1) & hash))== null) {
    if (casTabAt(tab, i, null,
                 new Node<K,V>(hash, key, value, null)))
        break;
}
```