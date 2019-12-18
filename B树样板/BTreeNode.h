#include<iostream>
#include<stdlib.h>
using namespace std;
/////////////////////////////////////////////////
//BTreeNode<T>B树的结点的定义
/////////////////////////////////////////////////
template<class T>
struct BTreeNode
{
    int n;                      //结点中关键码的个数
    BTreeNode<T>* parent;       //当前结点的父结点的指针

    T* key;                     //m+1个元素存放关键码,其中key[0]和key[m]没有用
    BTreeNode<T>**              //子树指针的结点数组(一共有m棵子树),m+1个元素
        subTree;                //最后一个元素subTree[m]在插入溢出的时候使用
    int** recptr;               //每个索引项中指向数据区相应记录起始地址的指针数组
    BTreeNode(int m)            //构造函数
    {
        n = 0;                    //关键码个数初始化为0
        parent = NULL;            //父结点指针初始化为空
        key = new T[m + 1];         //开辟关键码数组的空间
        subTree = new             //开辟子树的指针数组的内存空间
            BTreeNode<T> * [m + 1]; //从p0,p1,p2,...p(m-1)共m棵子树,pm溢出时使用
        for (int i = 0;i <= m;i++)
            subTree[i] = NULL;    //子树数组先全部初始化为空
    };
    bool Insert(const T& x      //把一个关键码插入到当前的B树结点中
        , BTreeNode<T>* p)       //也把附带的新建的右子树的指针插入subTree[]中
    {
        int i;
        for (i = 1;i <= n;i++)   //寻找插入关键码的位置
        {
            if (x < key[i])
                break;
        };

        int j;
        for (j = n;j >= i;j--)   //挪出新的插入位置来
            key[j + 1] = key[j];
        key[i] = x;               //插入结点
        n++;//关键码数目加1

        for (j = n;j >= i;j--)       //把新分裂开来的右子树结点插入subTree[]中
            subTree[j + 1] = subTree[j];
        subTree[i] = p;
        return true;
    };

    void Display()              //显示当前结点所有关键码
    {
        for (int i = 1;i <= n;i++)
            cout << key[i] << " ";
    };
};
/////////////////////////////////BTree<T>定义结束

#pragma once
