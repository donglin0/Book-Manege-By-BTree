#include"Mtree.h"


Triple Mtree::Search(const int& x) {

	Triple result;//��¼�����������Ԫ��
	//GetNode(root);//�Ӵ����϶�ȡλ�ڸ�root�Ľ��
	MtreeNode* p = root;//p��ɨ��ָ��
	MtreeNode* q = NULL;//q�Ǹ����ָ��
	int temp = 0;//������������ѭ�����ڲ�����i��ֵ
	while (p != NULL) {//�Ӹ��ڵ㿪ʼ���
		int i = 0; p->key[(p->n) + 1] = MaxValue;//Ϊ��ǰ���β�����ü�����
		while (p->key[i + 1] < x) i++; temp = i;//�ڽ����˳������
		if (p->key[i + 1] == x) {//�����ɹ������������x
			result.r = p;
			result.i = i + 1;
			result.tag = 0;
			return result;
		}
		q = p;//���������x��q���µ�ǰ�����Ϊ�����
		p = p->ptr[i];//p�½�����Ӧ��������i��0��ʼ
		//GetNode(p);//�Ӵ����ж�ȡp���
	}
	//x��������ki��ki+1��������
	result.r = q;//��������������Ľ��ĵ�ַ���������λ��
	result.i = temp;
	result.tag = 1;
	return result;//����ʧ�ܷ��ز���λ��
}