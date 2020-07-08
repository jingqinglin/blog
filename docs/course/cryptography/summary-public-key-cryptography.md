> 教材第九章，第十章

## 公钥密码系统原理

1976, the concept of public-key cryptographyis developed by Diffie and Hellman.

- 对称加密比较慢，公钥加密更慢。往往用对称加密保护明文，用公钥加密保护对称密钥
- 公钥加密可解决「不可否认性」问题
- 三种用途：加解密（实现数据保密性和认证），**数字签名**，**密钥交换**（不是所有的公钥算法都有这三个用途）
- 公钥密码的一些误解和事实：  
  ![](_images/summary-public-key-cryptography-1.png ':size=70%')
- 对公钥密码的要求（三个容易两个不可行）：
  1. B 产生一对密钥（公钥 $\mathrm{PU}_{b}$，私钥 $\mathrm{PR}_{b}$）在计算上是容易的
  2. 已知公钥和要加密的消息 $M$，发送方 A 产生相应的密文在计算上是容易的
    $$C=\mathrm{E}\left(\mathrm{PU}_{b}, M\right)$$
  3. 接收方 B 使用其私钥对接收的密文解密以恢复明文在计算上是容易的
    $$M=\mathrm{D}\left(\mathrm{PR}_{b}, C\right)=\mathrm{D}\left[\mathrm{PR}_{b}, \mathrm{E}\left(\mathrm{PU}_{b}, M\right)\right]$$
  4. 已知公钥 $\mathrm{PU}_{b}$ 时，攻止者要确定私钥 $\mathrm{PR}_{b}$ 在计算上是不可行的
  5. 已知公钥 $\mathrm{PU}_{b}$ 和密文 $C$，攻击者要恢复明文 $M$ 在计算上是不可行的

## RSA 算法

知道处理过程：
1. 公钥私钥对怎么生成，加解密怎么做
2. 数学难题是什么
3. 如何提升速率，保证安全性

中国剩余定理，解密提速

## ⭐ 密钥管理

公钥真实性如何保证？证书

## 椭圆曲线密码

!> 椭圆曲线不会考，但是怎么做加法、做乘法需要理解

RSA Diffie-Hellman 椭圆曲线区别 PPT P99

分数取模



