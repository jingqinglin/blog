#### 🔬 实验一

?> Many Time Pad

<details>
<summary>实验内容</summary>

> 【时间】 暂定 5 月 23 号（周六）晚上
> 
> 【编程语言】 Python（推荐）或者 C/C++
> 
> 【实验目的】
> 
> 1. 了解流密码的结构特点；
> 2. 掌握 One-time Pad 的一般具体实现；
> 3. 通过使用 Python（推荐）或者 C，编程实现一个流密码加密示例的破解，进一步认识在流密码加密中多次使用相同密钥导致的问题。
> 
> 【实验内容】
> 
> 在掌握流密码结构的基础上，通过本实验观察使用相同流密码密钥加密多个明文导致的严重后果。
> 
> 附件 [ciphertext.txt](course/cryptography/lab-1-ciphertext.txt ':ignore') 有 11 个十六进制编码的密文，它们是使用流密码加密 11 个明文的结果，所有密文都使用相同的流密码密钥。
> 
> 实验的目标是解密最后一个密文，并提交明文消息。
> 
>   
> 提示：
> 
> 1. 对密文进行异或，并考虑当空格与 [a ~ z, A ~ Z] 中的字符进行异或时会发生什么。
> 2. 附件 [encrypt.py](course/cryptography/lab-1-encrypt.py ':ignore') 是用于生成密文的 Python 示例程序（不影响实验，仅供参考）。 

</details>

- [实验报告](course/cryptography/lab-1.md)

#### 🔬 实验二

?> 离散对数求解

<details>
<summary>实验内容</summary>

> 【时间】5 月 30 号（周六）晚上
> 
> 【编程语言】Python（推荐）或者 C/C++
> 
> 【实验目的】
> 
> 1. 掌握与密码学相关的基础数论知识；
> 2. 通过使用 Python（推荐）或者 C，利用中间相遇攻击来编程实
>  
> 【实验内容】
> 实验内容和要求请见附件 [EXP2-Doc.pdf](course/cryptography/lab-2-EXP2-Doc.pdf ':ignore')
> 
> ```pdf
> course/cryptography/lab-2-EXP2-Doc.pdf
> ```

<!-- <font color=gray>docsify 的文档嵌入（嵌入多个 iframe）还有一点问题，修复 bug 前先使用 docsify-pdf-embed 插件来显示 </font> -->

</details>

- [实验报告](course/cryptography/lab-2.md)