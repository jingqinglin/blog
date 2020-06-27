<style>
    .crisp-client, .edit-document {
        display: none;
    }
</style>

<!-- <div align="center">
<svg class="icon" aria-hidden="true"><use xlink:href="#icon-githubblack"></use></svg> <a href="https://github.com/JingqingLin/Blog" target="_blank">Github</a>
&emsp; | &emsp;
<embed class="icon" src="//cdn.jsdelivr.net/gh/JingqingLin/Blog/docs/_media/docsify.svg" type="image/svg+xml" style="width: 1.3em;height: 1.3em;" /> Docsify
</div>
<br> -->

[![Made with Markdown](https://img.shields.io/badge/Made%20with-Markdown-42b983?logo=markdown&style=flat)](https://commonmark.org)
[![Powered by docsify](https://img.shields.io/badge/Powered%20by-docsify-42b983?logo=data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4KPHN2ZyB3aWR0aD0iMTIycHgiIGhlaWdodD0iOTRweCIgdmlld0JveD0iMCAwIDEyMiA5NCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIj4KICAgIDwhLS0gR2VuZXJhdG9yOiBTa2V0Y2ggNDEuMiAoMzUzOTcpIC0gaHR0cDovL3d3dy5ib2hlbWlhbmNvZGluZy5jb20vc2tldGNoIC0tPgogICAgPHRpdGxlPmljb248L3RpdGxlPgogICAgPGRlc2M+Q3JlYXRlZCB3aXRoIFNrZXRjaC48L2Rlc2M+CiAgICA8ZGVmcz4KICAgICAgICA8cGF0aCBkPSJNMTQ0LjQ1MzI4NiwxMDQgQzE3Ny4wMzgwODYsMTA0IDIwMy40NTMyODYsNzcuNTg0ODAwMiAyMDMuNDUzMjg2LDQ1IEMyMDMuNDUzMjg2LDEyLjQxNTE5OTggMTc3LjAzODA4NiwtMTQgMTQ0LjQ1MzI4NiwtMTQgQzExMS44Njg0ODYsLTE0IDExNC42MDMyMDcsMTMuNjc1NDg0NiAxMTQuNjAzMjA3LDQ2LjI2MDI4NDggQzExNC42MDMyMDcsNzguODQ1MDg1IDExMS44Njg0ODYsMTA0IDE0NC40NTMyODYsMTA0IFoiIGlkPSJwYXRoLTEiPjwvcGF0aD4KICAgICAgICA8ZmlsdGVyIHg9Ii01MCUiIHk9Ii01MCUiIHdpZHRoPSIyMDAlIiBoZWlnaHQ9IjIwMCUiIGZpbHRlclVuaXRzPSJvYmplY3RCb3VuZGluZ0JveCIgaWQ9ImZpbHRlci0yIj4KICAgICAgICAgICAgPGZlT2Zmc2V0IGR4PSI3IiBkeT0iLTEwIiBpbj0iU291cmNlQWxwaGEiIHJlc3VsdD0ic2hhZG93T2Zmc2V0SW5uZXIxIj48L2ZlT2Zmc2V0PgogICAgICAgICAgICA8ZmVDb21wb3NpdGUgaW49InNoYWRvd09mZnNldElubmVyMSIgaW4yPSJTb3VyY2VBbHBoYSIgb3BlcmF0b3I9ImFyaXRobWV0aWMiIGsyPSItMSIgazM9IjEiIHJlc3VsdD0ic2hhZG93SW5uZXJJbm5lcjEiPjwvZmVDb21wb3NpdGU+CiAgICAgICAgICAgIDxmZUNvbG9yTWF0cml4IHZhbHVlcz0iMCAwIDAgMCAwICAgMCAwIDAgMCAwICAgMCAwIDAgMCAwICAwIDAgMCAwLjEgMCIgdHlwZT0ibWF0cml4IiBpbj0ic2hhZG93SW5uZXJJbm5lcjEiPjwvZmVDb2xvck1hdHJpeD4KICAgICAgICA8L2ZpbHRlcj4KICAgIDwvZGVmcz4KICAgIDxnIGlkPSJQYWdlLTEiIHN0cm9rZT0ibm9uZSIgc3Ryb2tlLXdpZHRoPSIxIiBmaWxsPSJub25lIiBmaWxsLXJ1bGU9ImV2ZW5vZGQiPgogICAgICAgIDxnIGlkPSJpY29uIiB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtOTguMDAwMDAwLCAyLjAwMDAwMCkiPgogICAgICAgICAgICA8ZyBpZD0iYm9keSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoMTU5LjAwMDAwMCwgNDUuMDAwMDAwKSByb3RhdGUoLTkwLjAwMDAwMCkgdHJhbnNsYXRlKC0xNTkuMDAwMDAwLCAtNDUuMDAwMDAwKSAiPgogICAgICAgICAgICAgICAgPHVzZSBmaWxsPSIjMkVDRTUzIiBmaWxsLXJ1bGU9ImV2ZW5vZGQiIHhsaW5rOmhyZWY9IiNwYXRoLTEiPjwvdXNlPgogICAgICAgICAgICAgICAgPHVzZSBmaWxsPSJibGFjayIgZmlsbC1vcGFjaXR5PSIxIiBmaWx0ZXI9InVybCgjZmlsdGVyLTIpIiB4bGluazpocmVmPSIjcGF0aC0xIj48L3VzZT4KICAgICAgICAgICAgICAgIDx1c2Ugc3Ryb2tlPSIjMEUxMzIwIiBzdHJva2Utd2lkdGg9IjQiIHhsaW5rOmhyZWY9IiNwYXRoLTEiPjwvdXNlPgogICAgICAgICAgICA8L2c+CiAgICAgICAgICAgIDxjaXJjbGUgaWQ9ImxlZnQtZXllIiBmaWxsPSIjMDAwMDAwIiBjeD0iMTM5IiBjeT0iMzgiIHI9IjciPjwvY2lyY2xlPgogICAgICAgICAgICA8Y2lyY2xlIGlkPSJyaWdodC1leWUiIGZpbGw9IiMwMDAwMDAiIGN4PSIxODMiIGN5PSIzOCIgcj0iNyI+PC9jaXJjbGU+CiAgICAgICAgICAgIDxnIGlkPSJsaWdodCIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoMTEyLjAwMDAwMCwgMTAuMDAwMDAwKSIgZmlsbD0iI0ZGRkZGRiI+CiAgICAgICAgICAgICAgICA8Y2lyY2xlIGN4PSIyIiBjeT0iMjgiIHI9IjIiPjwvY2lyY2xlPgogICAgICAgICAgICAgICAgPHBhdGggZD0iTTEyLjI1NTE1MjgsLTEuNjUwMTY2NjYgQzEyLjExNTQ1MzcsLTIuMTc2ODQ5ODYgMTIuNDQ1NTU4MywtMi42MDM4MTA5NiAxMy4wMTE1NzQsLTIuNjAzODEwOTYgTDE0Ljk5MjgzNjMsLTIuNjAzODEwOTYgQzE1LjU1MDI5NTMsLTIuNjAzODEwOTYgMTYuMTIxNDY1NCwtMi4xNjU2NjQ4NyAxNi4yNTk0NjU3LC0xLjY0MjY4Nzc2IEMxNi4yNTk0NjU3LC0xLjY0MjY4Nzc2IDE3LjQyODAxNTIsMi40ODY2ODU5NCAxNy45MDMwNzM5LDYuNDU3ODY2NDcgQzE4LjM3ODEzMjcsMTAuNDI5MDQ3IDE4LjMxNzEzNTksMTAuNDY1MjkwMSAxOC4zMTcxMzU5LDEyLjE3ODI1NjkgQzE4LjMxNzEzNTksMTYuOTQxMzUyMyAxNi4yMDc2Mzk4LDI2LjQzODkxNjQgMTYuMjA3NjM5OCwyNi40Mzg5MTY0IEMxNi4wOTQxODE0LDI2Ljk2NzYwMzUgMTUuNTU4ODUyLDI3LjM5NjE4OSAxNC45OTI4MzYzLDI3LjM5NjE4OSBMMTMuMDExNTc0LDI3LjM5NjE4OSBDMTIuNDU0MTE1LDI3LjM5NjE4OSAxMi4xMTY2NjQyLDI2Ljk2OTE3NTcgMTIuMjU2ODM2NiwyNi40MzAxMTc3IEMxMi4yNTY4MzY2LDI2LjQzMDExNzcgMTMuNDI2MDU3NSwyMi4yMjg4NzY4IDEzLjk2NDA3NTksMTcuOTg1OTE0OCBDMTQuNTAyMDk0MywxMy43NDI5NTI5IDE0LjMwOTU5NCwxNS4yOTgyNjI5IDE0LjU2MjY2MDksMTIuMzcyMzk3OCBDMTQuOTM1NTMzNyw4LjA2MTM4MDQ3IDEyLjI1NTE1MjgsLTEuNjUwMTY2NjYgMTIuMjU1MTUyOCwtMS42NTAxNjY2NiBaIiBpZD0ibGlnaHQtbGluZSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoMTUuMjcxNDMzLCAxMi4zOTYxODkpIHNjYWxlKC0xLCAxKSByb3RhdGUoLTQ4LjAwMDAwMCkgdHJhbnNsYXRlKC0xNS4yNzE0MzMsIC0xMi4zOTYxODkpICI+PC9wYXRoPgogICAgICAgICAgICA8L2c+CiAgICAgICAgICAgIDxwYXRoIGQ9Ik0xNTkuNSw3OC4zMDUwMTA4IEMxNjkuMTY0OTgzLDc4LjMwNTAxMDggMTc3LDcwLjQ2OTk5MzkgMTc3LDYwLjgwNTAxMDggQzE3Nyw1MS4xNDAwMjc3IDE2OS42ODg3MjgsNTYuNDYxNjg0MSAxNjAuMDIzNzQ1LDU2LjQ2MTY4NDEgQzE1MC4zNTg3NjIsNTYuNDYxNjg0MSAxNDIsNTEuMTQwMDI3NyAxNDIsNjAuODA1MDEwOCBDMTQyLDcwLjQ2OTk5MzkgMTQ5LjgzNTAxNyw3OC4zMDUwMTA4IDE1OS41LDc4LjMwNTAxMDggWiIgaWQ9Im1vdXRoIiBmaWxsPSIjMDAwMDAwIj48L3BhdGg+CiAgICAgICAgPC9nPgogICAgPC9nPgo8L3N2Zz4=&style=flat)](https://docsify.js.org)
[![GitHub](https://img.shields.io/badge/Repo-@JingqingLin/blog-42b983?logo=github&style=flat)](https://github.com/JingqingLin/blog)

> <span style="font-weight: 400;color: #34495e"><b style="font-size: 30px;color: #42b983;">Hi</b>，我是 Jingqing，我在这个网站记录我的学习心得。受 [Huihut](https://interview.huihut.com) 的启发 💡，用 [docsify](https://docsify.js.org/#/) 生成了这个网站</span>

## 👉 **剑指 Offer**

> 此部分记录我所做的剑指 Offer 题目

- [剑指 Offer](lcof/lcof.md)

<br>

---

## <svg class="icon" aria-hidden="true"><use xlink:href="#icon-LeetCode"></use></svg> **LeetCode**

> 此部分记录我所做的力扣题，按照 [CS-Notes](https://cyc2018.github.io/CS-Notes/#/notes/Leetcode%20%E9%A2%98%E8%A7%A3%20-%20%E7%9B%AE%E5%BD%951) 的分类进行做题

### 👍 前 n 题

按顺序做了 20 多道题之后，转向了 [CS-Notes](https://cyc2018.github.io/CS-Notes/#/notes/Leetcode%20%E9%A2%98%E8%A7%A3%20-%20%E7%9B%AE%E5%BD%951) 做题。

- [1 - 10 题](leetcode/1-10.md)
- [11 - 20 题](leetcode/11-20.md)
- [21 - 30 题](leetcode/21-30.md)

### 🔐 算法思想

- [双指针](leetcode/双指针.md)
- [排序](leetcode/排序.md)
- [贪心思想](leetcode/贪心思想.md)
- [二分查找](leetcode/二分查找.md)
- [分治](leetcode/分治.md)
- [搜索](leetcode/搜索.md)
- [动态规划](leetcode/动态规划.md)
- [数学](leetcode/数学.md)

### 🔢 数据结构相关

- [链表](leetcode/链表.md)
- [树](leetcode/树.md)

### 🌞 每日一题

2020 年三月开始，力扣推出了「每日 1 题」打卡刷题活动，👉 [传送门](https://datayi.cn/w/noqw6arR)。

- [x] [三月](leetcode/march-2020.md)
- [x] [四月](leetcode/april-2020.md)
- [x] [五月](leetcode/may-2020.md)
- [ ] [六月](leetcode/june-2020.md)

<br>

---

## 📝 **面试相关**

> 在准备面试的过程中，参考了许多资料，但主要来源于 [CS-Notes](https://cyc2018.github.io/CS-Notes/#/) 和 [Huihut](https://interview.huihut.com)。在这些资料的基础上，我针对自己的情况做了一些记录和总结

### 💻 C++

- [C++ 基础](interview/cpp.md)
- [拷贝构造函数](interview/cpp-copy-constructor.md)

### ☕ Java

- [Java 基础](interview/java.md)
- [Java 容器](interview/java-container.md)
- [Java 并发](interview/java-concurrency.md)
- [Java 虚拟机](interview/java-jvm.md)


### 📚 计算机基础

- [数据结构](interview/data-structure.md)
- [计算机网络](interview/computer-network.md)
- [操作系统](interview/os.md)

<br>

---

## 💯 **课程相关**

> 2019 - 2020 学年第二学期的部分课程

### 🔑 现代密码学与应用

- 实验：[传送门](course/cryptography/)

- 课程资料：[传送门](https://github.com/JingqingLin/Cryptography)

### 👷 高级软件工程

- 作业：[传送门](course/software-engineering/)

### 🔐 算法设计与分析

- 作业和实验：[传送门](course/introduction-to-algorithms/)

<!-- <br>

---

## 🎨 **OpenGL**

> 这部分是 OpenGL 学习笔记

### 📖 LearnOpenGL

[LearnOpenGL](https://learnopengl.com/) 是一个可以从零开始学习 OpenGL 的网站，有同学把这个网站翻译成了中文 👉 [中文版](https://learnopengl-cn.github.io/)。

- 入门
- 光照
- 模型加载
- 高级 OpenGL
- 高级光照
- PBR
- 实战 -->