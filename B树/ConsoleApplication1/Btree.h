#include"Mtree.h"

class Btree :public Mtree//�����ؼ̳�m·�����������ԺͲ���
{//B���ඨ��
public:
	//Search��Mtree�̳ж���
	bool Insert(const int& x);//����ؼ���
	bool Remove(int x);//ɾ���ؼ���
	Btree();//���캯��
	~Btree();
};
//B����ÿ������а���һ��ָ��recptr[m]��ָ��ʵ�ʵĴ�ŵ�ַ��key[i]��recptr[i](1<=i<=n<m)�γ�һ�������key[i],recptr[i]��,
//ͨ��key[i]���ҵ�ĳ���洢��ַrecptr[i]��
#pragma once
