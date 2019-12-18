#ifndef BTREE_H
#define BTREE_H

#include"BTreeNode.h"

const int maxValue = 10000;

/////////////////////////////////////////////////
//Triple<T>�ṹ ������������õ���Ԫ��
/////////////////////////////////////////////////
template<class T>
struct Triple
{
    BTreeNode<T>* r;            //���ָ��
    int i;                      //�ؼ����ڵ�ǰ����е����
    int tag;                    //tag=0:�����ɹ�,tag=1:����ʧ��
};
////////////////////////////////Triple<T>�ṹ����

/////////////////////////////////////////////////
//BTree<T>  B���Ķ���;
//m��B���ĸ�����������������
//�����Ľ������Ӧ����int(m/2)+1������
//���е�ʧ�ܽ�㶼��һ�������
/////////////////////////////////////////////////
template<class T>
class BTree
{
private:
    BTreeNode<T>* root;         //�������ָ��
    int m;                      //��B���Ľ���
public:
    BTree(int x)                //�չ��캯��,����һ�ÿ�x·��������
    {
        root = NULL;m = x;
    };
    BTree(int x, BTreeNode<T>* r)
    {
        root = r;m = x;
    };              //��ָ������������ʼ����ǰ��m·������
    void Insert(                //����ָ������������²���һ�����
        BTreeNode<T>* pa,       //ָ��Ҫ�����λ�õĸ����
        BTreeNode<T>* subTree,  //Ҫ����Ľ���ָ��
        int i);                 //��ʾ���뵽pa�ĵ�i��������λ��

    Triple<T>                   //����ָ���ؼ���x��Ӧ�Ľ��
        Search(const T& x);
    void RootFirst(             //�ݹ�:���ȸ��ķ�ʽ������ǰ��������
        BTreeNode<T>* subTree);
    void RootFirst()            //��������ĵݹ麯��
    {
        RootFirst(root);
    };
    bool Insert(const T& x);    //B���Ĳ������
    void Display(BTreeNode<T>* p, int i); //�ݹ�:�������ĸ�ʽ��ʾ��ǰ��B��
    void Display()              //��������ĵݹ麯��
    {
        cout << "*****��ǰB���������ṹ��ʾ*****:" << endl;
        Display(root, 1);
    };
    void ParentAdjust(BTreeNode<T>* ptr);//���������

    bool Remove(const T& x);//ɾ��
    void LeftAdjust(BTreeNode<T>* p, BTreeNode<T>* q, int d, int j);//�����
    void RightAdjust(BTreeNode<T>* p, BTreeNode<T>* q, int d, int j);//�ҵ���
    void compress(BTreeNode<T>* p, int j);//ѹ������
    void merge(BTreeNode<T>* p, BTreeNode<T>* q, BTreeNode<T>* pl, int j);//�ϲ�


};
//////////////////////////////////////B����������

/////////////////////////////////////////////////
//RootFirst()���г�Ա���� 
//���ȸ��ķ�ʽ�ݹ������ǰB��
/////////////////////////////////////////////////
template<class T>
void BTree<T>::RootFirst(BTreeNode<T>* st)
{
    if (st != NULL)
    {
        int n = st->n;
        cout << "��ǰ�����" << n
            << "���ؼ���:" << endl;
        for (int k = 1;k <= n;k++)       //�����ǰ�������еĹؼ���
            cout << st->key[k] << " ";
        cout << endl << endl;
        for (int i = 0;i <= n;i++)       //�ݹ�������е�����
            RootFirst(st->subTree[i]);
    };
};
//////////////////////////////RootFirst()��������

/////////////////////////////////////////////////
//Search()���г�Ա����  ��������ָ���ؼ����
//�Ľ�㲢������Ԫ�����ʽ���з���,���û������
//�ɹ��ͰѸùؼ�����뵽��ǰפ���Ľ����ȥ
/////////////////////////////////////////////////
template<class T>
Triple<T> BTree<T>::Search(const T& x)
{
    Triple<T>  result;              //�����Ԫ��
    BTreeNode<T>* ptr = root;         //�Ӹ���㿪ʼ����
    BTreeNode<T>* pre = NULL;
    /*�Ӹ���㿪ʼ���²���*/
    int i=0;
    while (ptr != NULL)
    {
        for (i = 1;i <= ptr->n;i++)      //�ڽ���ڲ�����˳������
        {
            if (ptr->key[i] == x)      //����ҵ�
            {
                result.r = ptr;       //��ǰ����פ���Ľ��ָ��
                result.i = i;         //���ҳɹ��Ĺؼ���
                result.tag = 1;       //�Ƿ���ҳɹ�
                return result;
            };
            if (ptr->key[i] > x)       //����ʧ��
                break;
        };
        pre = ptr;
        ptr = ptr->subTree[i - 1];      //��ʧ��Ĺؼ�����ߵ�������������
    };
    /*�������ʧ��*/
    result.r = pre;
    result.i = i;                     //������i-1��i֮����в���
    result.tag = 0;                   //����ʧ�� 

    return result;
};
/////////////////////////////////Search()��������

/////////////////////////////////////////////////
//Insert()���г�Ա����  B���Ĳ������
//��ָ���Ĺؼ�����뵽B����,ʹ����Ȼ����B����Ҫ��
//���ȶ�B����������,����ؼ����Ѿ����������ʧ��,
//����ִ�в��룬����B��Ҫ����е���
//һ����˵,ִ�в���Ŀ϶�����Ҷ�ӽ���Ͻ���
//����������ҳɹ��Ļ�,�����ڷ�Ҷ�ӽ���Ͼͽ�����
/////////////////////////////////////////////////
template<class T>
bool BTree<T>::Insert(const T& x)
{
    /*�����ǰ��B���ǿյ�,���½�֮*/
    if (root == NULL)                  //�����ǰ��B���ǿյ�
    {
        root = new BTreeNode<T>(m);   //�½�һ�����
        root->Insert(x, NULL);            //�ѹؼ�����뵽key[]�����һ��λ��
        return true;
    };

    /*�����ǰ��B������,����������*/
    Triple<T> Tp;                   //���ҽ����Ԫ��
    Tp = Search(x);
    int IsIn = Tp.tag;
    if (IsIn == 1)                     //�ؼ����Ѿ�����
    {
        cout << "�ؼ���"<<x<<"�Ѵ���!" << endl;
        return false;               //����ʧ��
    };

    /*����ؼ���ֱ�����ؼ��벻���Ϊֹ*/
    BTreeNode<T>* ptr = Tp.r;         //����ʧ�ܶ�פ���Ľ��
    int loc = Tp.i - 1;                 //��k[loc]����в���
    int pkey = x;
    BTreeNode<T>* p = NULL;           //��ؼ���һ��Ҫ������������ĸ����
    do
    {
        ptr->Insert(pkey, p);        //�ѹؼ������ص��·��ѵ��ҽ����뵱ǰ���
        if (ptr->n > m - 1)              //����ؼ������,����Ҫ���е���
        {
            /*���´�����ķ���*/
            int k = ptr->key[m / 2 + 1];  //��ȡ��Ҫ����Ĺؼ���
            BTreeNode<T>* right     //�������Ѻ��ұߵĽ��
                = new BTreeNode<T>(m);
            right->n = ptr->n - m / 2 - 1;  //�ҽ��Ĺؼ������
            
            for (int i = m / 2 +2;i <= ptr->n;i++)//key[0]û��ʹ�ã����subtree�����Ĳ�����һ
                right->key[i - m / 2 - 1] //���Ұ�ߵĹؼ��븴�ƽ����ҽ��
                = ptr->key[i];

            for (int i = m / 2 + 1;i <= ptr->n;i++)
            {
                right->subTree[i - m / 2 - 1] //����Ӧ�ķ��Ѻ���ҽ������ָ�븴�����½��
                    = ptr->subTree[i];  
            }
            
            /*��������*/   //û���޸���Ӧ�ĸ�����ָ��ָ�����㣬�������㶪ʧ
            ptr->n = m / 2;             //�޸�ԭ���ʹ֮��Ϊ����
            
            right->parent
                = ptr->parent;       //�·��ѵĽ��
            p = right;                //p����kһ��������½������ҽ��ָ��
            pkey = k;
           // ParentAdjust(ptr->parent);///////// �����������ĸ�ָ��
            /*�����ǰ�Ľ��û�и����*/
            if (ptr->parent == NULL)   //�����ǰ���û�и����,���½������
            {
                BTreeNode<T>* newp  //�½�һ�������
                    = new BTreeNode<T>(m);
                newp->key[1] = k;     //�����¹ؼ���
                newp->subTree[0]    //�¹ؼ�����ߵ�����
                    = ptr;
                newp->subTree[1]    //�¹ؼ����ұߵ�����
                    = right;
                newp->n = 1;          //�¹ؼ������Ϊ1
                ptr->parent = newp;   //���ø����ָ��
                right->parent = newp;
                root = newp;
                return true;        //����ɹ�������
            }
            else                    //����и�������
                ptr = ptr->parent;    //������Ĺؼ���������븸���
        }
        else                        //����������ɹ�
            return true;
    } while (ptr != NULL);

    return true;
};
/////////////////////////Insert()���г�Ա��������

/////////////////////////////////////////////////
//Display()���г�Ա����  
//�ݹ�:��ʾ��ǰB����������ʽ
/////////////////////////////////////////////////
template<class T>
void BTree<T>::Display(BTreeNode<T>* p, int k)
{
    if (p != NULL)
    {       
            Display(p->subTree[(p->n)], k + 1);//�ݹ���ʾ���ҽ��
            for (int i = 0; i < k - 1; i++) cout << "            ";//k���ƿո�
            if (p->n > 0) {
                cout << ">>>>" << "n:" << p->n << " ";
                for (int i = 1;i <= p->n;i++)//��ʾ��ǰ������йؼ���
                    cout << p->key[i] << " ";
                cout << endl;        
            }
            if(p->n>=2) Display(p->subTree[p->n-1], k + 1);
            if(p->n >= 3) Display(p->subTree[p->n - 2], k + 1);
            Display(p->subTree[0], k + 1);
            

    }
};

/*
void print_tree(BTreeNode<T>* p, int n) {
    //���뷨��ӡ������
    if (p == NULL) return; //��������ӡ 
    print_tree(t->rightchild, n + 1); //�ݹ��ӡ������ 
    for (int i = 0; i < n - 1; i++) cout << "      ";
    if (n > 0) {
        cout << ">>>>";
        cout << p->key[0]<< endl; //��ʾ���� 
    }
    print_tree(t->leftchild, n + 1); //�ݹ��ӡ������
}
*/

//���������
template<class T>
void BTree<T>::ParentAdjust(BTreeNode<T>* ptr)
{
    if (ptr != NULL)
    {
        for (int i = 0;i <= ptr->n;i++)
        {
            if (ptr->subTree[i] != NULL)
            {
                ptr->subTree[i]->parent = ptr;
                ParentAdjust(ptr->subTree[i]);
            }
        }
    }
};


#endif
#pragma once





