#include"Mtree.h"

class Btree :public Mtree//公共地继承m路搜索树的属性和操作
{//B树类定义
public:
	//Search从Mtree继承而来
	bool Insert(const int& x);//插入关键码
	bool Remove(int x);//删除关键码
	Btree();//构造函数
	~Btree();
};
//B树的每个结点中包含一组指针recptr[m]，指向实际的存放地址。key[i]与recptr[i](1<=i<=n<m)形成一个索引项（key[i],recptr[i]）,
//通过key[i]可找到某个存储地址recptr[i]。
#pragma once
