#include <windows.h> //������һ�䣬ע��ͷ�ļ���˳��
#include"Btree.h"

bool Btree::Insert(const int& x) {
	//���ؼ���x���뵽һ��פ���ڴ����ϵ�m��B����
	Triple loc = Search(x);//����������x�����λ��
	if (!loc.tag) return false;//x�Ѵ������У����ٲ���
	MtreeNode* p = loc.r, * q;//r��xҪ����Ľ���ַ��qΪ�����
	MtreeNode* ap = NULL, * t;//ap�ǲ���ؼ��������ָ�룬tΪ�����
	int K = x; int j = loc.i;//(K,ap)�γɲ����Ԫ��
	while (1)
	{
		if (p->n < m - 1) {//���ؼ������δ����
			//insertkey(p, j, K, ap);//K��ap���뵽jλ�ã���p->n��1
			//PutNode(p); return true;//�����㵽���̣����ص��ó���
		}
		int s = (m + 1) / 2;//׼�����ѽ�㣬s��m/2ȡ����λ��
		//insertkey(p, j, K, ap);//�Ȳ�������p->n����m
		q = new MtreeNode;//�����½��q
		//move(p, q, s, m);
		//��p��key[s+1...m]��ptr[s...m]�Ƶ�q��key[1...s-1]��ptr[0...s-1],p->n��Ϊs-1,q->��Ϊm-s
		K = p->key[s]; ap = q;//(K,ap���γ����ϲ����Ԫ��
		if (p->parent != NULL)
		{//�������ϵ�����ԭ����p��Ϊ��
			t = p->parent;
			//GetNode(t);//�����϶�ȡt
			j = 0;
			//�ڸ������˳�����������λ��
			t->key[(t->n) + 1] = MaxValue;//������,
			while (t->key[j + 1] < K) j++;//�������ҵ�����K�Ĺؼ���ͣ
			q->parent = p->parent;//�½��ĸ�ָ�븳ֵ
			//PutNode(p);PutNode(q);//���������
			p = t;//p����������㣬���ϵ���
		}
		else {//ԭ����p�Ǹ�����Ҫ�����µĸ�
			root = new MtreeNode;
			root->n = 1; root->parent = NULL;//�����¸�
			root->key[1] = K;
			root->ptr[0] = p; root->ptr[1] = ap;//�¸�ָ�������������
			q->parent = p->parent = root;//Ϊ�½��ĸ�ָ�븳ֵ
			//PutNode(p); PutNode(q); PutNode(root);//���������
			return true;
		}
	}





	};
