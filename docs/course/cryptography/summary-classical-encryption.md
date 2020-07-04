> 教材第三章

可汗学院公开课「[古典密码学](http://open.163.com/newview/movie/courseintro?newurl=%2Fspecial%2FKhan%2Fancientcryptography.html)」

### 对称密码模型
五个基本成分：明文、加密算法、密钥、密文、解密算法。

#### 密码编码学（Cryptography）

![](_images/summary-classical-encryption-1.png ':class=image-80')

#### 密码分析学（Cryptanalysis）和穷举攻击

攻击传统的密码体制有两种通用的方法：
- 密码分析学
- 穷举攻击

### 代替技术

#### 单表代替加密

凯撒密码

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200506151154.png" width="70%"/>


单表代替密码较容易被攻破，因为它带有原始字母使用频率的一些统计学特征。一种对策是对每个字母提供多种代替，称为同音词（就像一个读音可以代表多个单词的同音词一样），一个明文单元也可以变换成不同的密文单元。比如字母 e 可以替换成 16，74，35 和 21。

- 如何挫败基于统计方法的密码分析？（第四章中）
  - 扩散（diffusion）：扩散指使明文的统计特征消散在密文中，可以让每个明文数字尽可能地影响多个密文数字获得，等价于说每个密文数字被许多明文数字影响
  - 混淆（confusion）：其目的在于使作用于明文的密钥和密文之间的关系复杂化，是明文和密文之间、密文和密钥之间的统计相关特性极小化，从而使统计分析攻击不能奏效

#### 多表代替加密

PlayFair、Hill 密码、Vigenère 密码（流密码）

#### 一次一密

### 置换技术
<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200507232234.png" width="70%"/>

### 转轮机

### 隐写术