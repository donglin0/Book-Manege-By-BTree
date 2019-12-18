#include<iostream>
using namespace std;

const int MaxValue = 100;
const int m = 4;
struct MtreeNode
{
	int n;//关键码个数
	MtreeNode* parent;//父结点指针
	int key[m + 1];//工作单元兼监视哨，key[0]未使用
	MtreeNode* ptr[m + 1];//子树结点 指针数组，ptr[m]再溢出时使用
	int recptr[m + 1];//每个索引项中 指向数据区相应记录 起始地址的指针
};

struct Triple//搜索结果三元组定义
{
	MtreeNode* r;//结点地址指针
	int i;//结点中关键码序号i
	int tag;//tag=0,表示搜索成功；
};

class Mtree
{//m路搜索树类定义(基类)
public:
	Triple Search(const int& x);//搜索函数
	Mtree();
	~Mtree();

protected:
	MtreeNode* root;//根指针
	int m;//路数
};

#pragma once
