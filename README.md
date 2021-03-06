Knight's_Tour
============

A divide and conquer solution for Knight's Tour Problem

A homework from 《计算机算法设计与分析》（王晓东编著）。

通过搜索一些资料，发现在 wikipedia上称马周游问题为[**Knight's Tour（骑士周游）**][Knight'sTour]问题，已经有不少研究，也有不少方法提 出。这个问题一般都是归结为图论中的**Hamilton问题**，该问题包括了走一个环路，和不用闭环的 路。

这个大问题其实还可以分为两类不同的子问题：

* 给定任意棋盘和任意骑士初始位置，找出所有可能的环路或回路。这个是一个NP-Hard问题，棋盘越大，越困难。一般用于验证一个算法能够在有限时间和空间下能够找到最大的棋盘是多大；

* 还有一类则是只需找出一条环路或回路即可，有[线性时间的方法,*"Solution of the Knight's Hamiltonian Path Problem on Chessboards"*][Solution]。

当然，以上两个问题都存在一个共同点，任意棋盘，并 不是都能够找到回路的。有文献证明，棋盘大小是奇数，是无解的。

这里有个事实是这样的，因为任意给定一个骑士的初始 位置，假如能够找到一个遍历且不重复其他位置的回路。那么骑士的初始位置在棋盘上的哪里都是无所谓的。所以，这个问题的求解不需要关心骑 士的初始位置，默认放在棋盘左上角。问题的输入就变成棋盘的大小，输出是一个从棋盘左上角开始的一个回路，或者返回无法找到回路。

[Knight'sTour]:http://en.wikipedia.org/wiki/Knight%27s_tour

[Solution]: http://www.sciencedirect.com/science/article/pii/0166218X9200170Q

###分治法求解

分治法的方法来自于王晓东编写的《计算机算法设计与分析》，里面有习题是这个，我找到了题解，见附件文件的54-61页。分治法思路好想，就是大棋盘的解是小棋盘的合并，难的就是题解中提 到的结构化的Hamilton回路。这是合并的关键。


关键文件如下：

* Knights.h/Knights.cpp 分治法求解一个任意大小棋盘的结构化Hamilton的实现

* boar\_path.txt 分治法的基础，6x6,6x8,8x6,8x8,8x10,10x8,10x10,10x12,12x10这几种基础解，都是结构化的解，更大棋盘的解都 是在这个基础上合并得到的。

* main.cpp 主程序入口

