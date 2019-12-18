#include<iostream>
using namespace std;

const int MaxValue = 100;
const int m = 4;
struct MtreeNode
{
	int n;//�ؼ������
	MtreeNode* parent;//�����ָ��
	int key[m + 1];//������Ԫ������ڣ�key[0]δʹ��
	MtreeNode* ptr[m + 1];//������� ָ�����飬ptr[m]�����ʱʹ��
	int recptr[m + 1];//ÿ���������� ָ����������Ӧ��¼ ��ʼ��ַ��ָ��
};

struct Triple//���������Ԫ�鶨��
{
	MtreeNode* r;//����ַָ��
	int i;//����йؼ������i
	int tag;//tag=0,��ʾ�����ɹ���
};

class Mtree
{//m·�������ඨ��(����)
public:
	Triple Search(const int& x);//��������
	Mtree();
	~Mtree();

protected:
	MtreeNode* root;//��ָ��
	int m;//·��
};

#pragma once
