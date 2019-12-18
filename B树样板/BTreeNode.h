#include<iostream>
#include<stdlib.h>
using namespace std;
/////////////////////////////////////////////////
//BTreeNode<T>B���Ľ��Ķ���
/////////////////////////////////////////////////
template<class T>
struct BTreeNode
{
    int n;                      //����йؼ���ĸ���
    BTreeNode<T>* parent;       //��ǰ���ĸ�����ָ��

    T* key;                     //m+1��Ԫ�ش�Źؼ���,����key[0]��key[m]û����
    BTreeNode<T>**              //����ָ��Ľ������(һ����m������),m+1��Ԫ��
        subTree;                //���һ��Ԫ��subTree[m]�ڲ��������ʱ��ʹ��
    int** recptr;               //ÿ����������ָ����������Ӧ��¼��ʼ��ַ��ָ������
    BTreeNode(int m)            //���캯��
    {
        n = 0;                    //�ؼ��������ʼ��Ϊ0
        parent = NULL;            //�����ָ���ʼ��Ϊ��
        key = new T[m + 1];         //���ٹؼ�������Ŀռ�
        subTree = new             //����������ָ��������ڴ�ռ�
            BTreeNode<T> * [m + 1]; //��p0,p1,p2,...p(m-1)��m������,pm���ʱʹ��
        for (int i = 0;i <= m;i++)
            subTree[i] = NULL;    //����������ȫ����ʼ��Ϊ��
    };
    bool Insert(const T& x      //��һ���ؼ�����뵽��ǰ��B�������
        , BTreeNode<T>* p)       //Ҳ�Ѹ������½�����������ָ�����subTree[]��
    {
        int i;
        for (i = 1;i <= n;i++)   //Ѱ�Ҳ���ؼ����λ��
        {
            if (x < key[i])
                break;
        };

        int j;
        for (j = n;j >= i;j--)   //Ų���µĲ���λ����
            key[j + 1] = key[j];
        key[i] = x;               //������
        n++;//�ؼ�����Ŀ��1

        for (j = n;j >= i;j--)       //���·��ѿ�����������������subTree[]��
            subTree[j + 1] = subTree[j];
        subTree[i] = p;
        return true;
    };

    void Display()              //��ʾ��ǰ������йؼ���
    {
        for (int i = 1;i <= n;i++)
            cout << key[i] << " ";
    };
};
/////////////////////////////////BTree<T>�������

#pragma once
