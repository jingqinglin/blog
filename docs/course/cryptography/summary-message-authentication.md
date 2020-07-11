> 教材第十二章

- 解决消息有没有被篡改的问题
- 两类消息认证码：HMAC（基于哈希函数）、CMAC（基于对称加密）
- HMAC 是带密钥的哈希函数
- 基于**密码原语**（加密、哈希函数、数字签名）的组合
- 当无需保证机密性时，应该避免对整个消息进行加密
- 对 MAC 的穷举攻击由于需要知道 <消息 - MAC> 对，所以这种攻击会比对 Hash 函数的攻击更难


## 消息认证函数

- Hash 函数：它是将任意长的消息映射为定长的 Hash 值的函数，以该 Hash 值作为认证符
- 消息加密：对整个消息加密后的密文作为认证符
- 消息认证码（MAC）：它是消息和密钥的函数，它产生定长的值，以该值作为认证符

上面三种函数对安全性的保障不同。

利用对称加密进行消息认证存在一些问题：如果消息 $M$ 可以是任何的位模式，那么接收方无法确定接收到的消息是合法明文的密文。（也就是说，随便伪造一个密文发给接收方，接收方也能解密，但解密出来的消息可能是没有意义的，所以只能说在一定程度上提供消息认证）。


## 基于哈希函数的 MAC：HMAC

![](_images/summary-message-authentication-1.png ':size=40%')
<font size="2" color="#8590a6">$IV$ 为 Hash 函数输入的初始值</font>


$\mathrm{HMAC}(K, M)=\mathrm{H}\left[\left(K^{+} \oplus \mathrm{opad}\right)\left\|\mathrm{H}\left[\left(K^{+} \oplus \mathrm{ipad}\right) \| M\right]\right]\right.$

可以预计算以下两部分：

$\mathrm{f}\left(IV,\left(K^{+} \oplus \mathrm{ipad}\right)\right)$  
$\mathrm{f}\left(IV,\left(K^{+} \oplus \mathrm{opad}\right)\right)$

## 基于分组密码的 MAC: DAA 和 CMAC

### 数据认证算法（DAA）

DAA 采用 DES 运算的密文块链接（CBC）方式。

![](_images/summary-message-authentication-2.png ':size=70%')

DAA 有如下的限制：仅能处理固定长度为 $mn$ 的消息，其中 $n$ 是密文分组的长度，$m$ 是一个固定的正整数。例如，给定一个消息分组 $X$ 的 CBC MAC 码，如 $T=MAC(K,x)$，则攻击者马上就知道两个消息分组 $X||(X \oplus T)$ 的 CBC MAC 码，因为这还是 $T$。

### 基于密码的消息认证码（CMAC）

DAA 的限制可以使用三个密钥来克服: 一个长度为 $k$ 的密钥 $K$，用在密文分组链接的每一步，两个长度为 $b$ 的密钥，其中 $b$ 是密钥长度。

![](_images/summary-message-authentication-3.png ':size=70%')