<style>
    .crisp-client {
        display: none;
    }
</style>

### 📝 作业一  {docsify-ignore}

?> 码农的自我修养之必备技能

<details>
<summary>作业内容</summary>

> ![作业内容](https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200316105640.png)

</details>

- [作业报告](course/software-engineering/task-1.md)

### 📝 作业二  {docsify-ignore}

?> 工程化编程实战 callback 接口

<details>
<summary>作业内容</summary>

> - 在 VS Code 下编译运行 [lab5-1.tar.gz](http://pan.baidu.com/s/1pJ0qAIv)
> - 通过 VS Code + GDB 调试程序找出 quit 命令无法运行的 bug 产生的原因
> - 分析 callback 接口的运行机制，总结 callback 接口设计的方法

</details>

- [作业报告](course/software-engineering/task-2.md)

### 📝 作业三  {docsify-ignore}

?> Windows 下基于 VS Code 的 C++ 编程语言的构建调试环境搭建指南

- [作业报告](course/software-engineering/task-3.md)

### 📝 作业四  {docsify-ignore}

?> 交互式多媒体图书平台的设计与实现

<details>
<summary>作业内容</summary>

> 参照码农的自我修养之从需求分析到软件设计——一种从需求分析到软件设计的基本建模方法，按如下交互式多媒体图书平台的需求，首先按需求类型分类，然后完成概念原型设计（应具有用例图 + 数据模型），并选择一个关键用例进行深入分析和设计（应具有分析和设计序列图），最终给出一个设计方案（应具有设计类图或者微服务架构图）。交互式多媒体图书平台的需求如下：
> 
> - 交互式多媒体图书平台包括读者端和作者端；
> - 作者可以编排图书的目录结构、章节内容，章节内容中包括图片、视频、文字、和集成第三方软件边学边练，能定义常见练习题比如问答题、选择题；作者编辑时可以预览读者端的效果，手机效果、Web 和桌面软件效果，作者可以限制只在某一种或几种终端上使用；
> - 读者端可以通过手机、浏览器或桌面软件使用交互式多媒体图书，可以搜索图书，查看图书目录，根据作者设定可以顺序解锁阅读，或随意跳跃阅读，或部分章节内部必须顺序阅读；
> - 软件能集成或调用第三方软件，比如阅读过程中能直接调出 VS Code 或 linux shell 等第三方软件进行实际操作，并对操作做基本正误判断，然后回到图书继续阅读。调出第三方软件应该通过统一的插件模型调用，第三方软件与图书之间的相互转换要自动流畅完成，不需要读者操作；
> - 读者端的手机 App、Web 或桌面软件使用统一的代码实现，优先考虑前后端为 JS + Node.js + MongoDB；作者端独立部署，只有在作者发布图书时才将数据导入到读者端系统，以避免作者端的操作对读者端系统的影响；
> - 以上需求的不足可以适当补充和调整。
> 
> 如果您有创新性的项目或者您实际的工程实践项目也可以作为本次作业的需求替代以上需求，但从需求分析到软件设计的基本建模方法的要求不变。

</details>

- [作业报告](course/software-engineering/task-4.md)