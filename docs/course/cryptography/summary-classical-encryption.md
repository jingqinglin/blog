> 教材第三章

可汗学院公开课「[古典密码学](http://open.163.com/newview/movie/courseintro?newurl=%2Fspecial%2FKhan%2Fancientcryptography.html)」

## 对称密码模型
五个基本成分：明文、加密算法、密钥、密文、解密算法。

### 密码编码学（Cryptography）

![](_images/summary-classical-encryption-1.png ':class=image-80')

### 密码分析学（Cryptanalysis）和穷举攻击

攻击传统的密码体制有两种通用的方法：
- 密码分析学
- 穷举攻击

## 代替技术

### 单表代替加密

代表技术：凯撒密码（移位也属于单表代替）。

> 单表代替密码较容易被攻破，因为它带有原始字母使用频率的一些**统计学特征**。一种对策是对每个字母提供多种代替，称为同音词（就像一个读音可以代表多个单词的同音词一样），一个明文单元也可以变换成不同的密文单元。比如字母 e 可以替换成 16，74，35 和 21

### 多表代替加密

代表技术：
- PlayFair：双字母音节作为一个单元，具体加密方式在教材 P56
- Hill 密码：涉及矩阵变换，将 $m$ 个连续的明文字母（字母可被指定为一个数值，如 $a=0$，$b=1$...）替换成 $m$ 个密文字母，$m = 3$ 时可描述为：
  $$\left(c_{1} c_{2} c_{3}\right)=\left(p_{1} p_{2} p_{3}\right)\left(\begin{array}{lll}k_{11} & k_{12} & k_{13} \\ k_{21} & k_{22} & k_{23} \\ k_{31} & k_{32} & k_{33}\end{array}\right) \bmod 26$$
- Vigenère 密码：流密码（示例如下），可通过转化为多个单表替换进行攻击
  ```
  明文：ATTACKATDAWN
  密钥：LEMONLEMONLE
  密文：LXFOPVEFRNHR
  ```

![](_images/summary-classical-encryption-3.png ':class=image-80')

PlayFair 和 Vigenère 密码都保留了许多频率信息，而 Hill 密码完全隐藏了单字母频率特性。

### 一次一密

- 使用与消息一样长且无重复的随机密钥来加密消息，且密钥只对一个消息进行加解密，之后丢弃不用（多次使用同一个密钥存在风险，见[实验一](course/cryptography/lab-1.md)）
- 和 Vigenère 密码一样，也是通过异或操作进行加解密
- 由于密钥的产生、分配和保护问题存在困难，一次一密实际上很少使用

## 置换技术

![](_images/summary-classical-encryption-4.png ':class=image-80')

## 转轮机

进行多次代替

## 隐写术