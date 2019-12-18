#ifndef BTREE_H
#define BTREE_H

#include"BTreeNode.h"

const int maxValue = 10000;

/////////////////////////////////////////////////
//Triple<T>结构 返回搜索结果用的三元组
/////////////////////////////////////////////////
template<class T>
struct Triple
{
    BTreeNode<T>* r;            //结点指针
    int i;                      //关键码在当前结点中的序号
    int tag;                    //tag=0:搜索成功,tag=1:搜索失败
};
////////////////////////////////Triple<T>结构结束

/////////////////////////////////////////////////
//BTree<T>  B树的定义;
//m阶B树的根至少有两个子树，
//其他的结点至少应该有int(m/2)+1个子树
//所有的失败结点都在一个层次上
/////////////////////////////////////////////////
template<class T>
class BTree
{
private:
    BTreeNode<T>* root;         //树根结点指针
    int m;                      //即B树的阶数
public:
    BTree(int x)                //空构造函数,构造一棵空x路的搜索树
    {
        root = NULL;m = x;
    };
    BTree(int x, BTreeNode<T>* r)
    {
        root = r;m = x;
    };              //用指定的树根来初始化当前的m路搜索树
    void Insert(                //在树指定父结点的情况下插入一个结点
        BTreeNode<T>* pa,       //指定要出入的位置的父结点
        BTreeNode<T>* subTree,  //要插入的结点的指针
        int i);                 //表示插入到pa的第i个子树的位置

    Triple<T>                   //搜索指定关键码x对应的结点
        Search(const T& x);
    void RootFirst(             //递归:以先根的方式遍历当前的搜索树
        BTreeNode<T>* subTree);
    void RootFirst()            //调用上面的递归函数
    {
        RootFirst(root);
    };
    bool Insert(const T& x);    //B树的插入操作
    void Display(BTreeNode<T>* p, int i); //递归:以缩进的格式显示当前的B树
    void Display()              //调用上面的递归函数
    {
        cout << "*****当前B树的缩进结构显示*****:" << endl;
        Display(root, 1);
    };
    void ParentAdjust(BTreeNode<T>* ptr);//调整父结点

    bool Remove(const T& x);//删除
    void LeftAdjust(BTreeNode<T>* p, BTreeNode<T>* q, int d, int j);//左调整
    void RightAdjust(BTreeNode<T>* p, BTreeNode<T>* q, int d, int j);//右调整
    void compress(BTreeNode<T>* p, int j);//压缩调整
    void merge(BTreeNode<T>* p, BTreeNode<T>* q, BTreeNode<T>* pl, int j);//合并


};
//////////////////////////////////////B树声明结束

/////////////////////////////////////////////////
//RootFirst()公有成员函数 
//以先根的方式递归遍历当前B树
/////////////////////////////////////////////////
template<class T>
void BTree<T>::RootFirst(BTreeNode<T>* st)
{
    if (st != NULL)
    {
        int n = st->n;
        cout << "当前结点有" << n
            << "个关键码:" << endl;
        for (int k = 1;k <= n;k++)       //输出当前结点的所有的关键码
            cout << st->key[k] << " ";
        cout << endl << endl;
        for (int i = 0;i <= n;i++)       //递归输出所有的子树
            RootFirst(st->subTree[i]);
    };
};
//////////////////////////////RootFirst()函数结束

/////////////////////////////////////////////////
//Search()公有成员函数  搜索具有指定关键码的
//的结点并且以三元组的形式进行返回,如果没有搜索
//成功就把该关键码插入到当前驻留的结点中去
/////////////////////////////////////////////////
template<class T>
Triple<T> BTree<T>::Search(const T& x)
{
    Triple<T>  result;              //结果三元组
    BTreeNode<T>* ptr = root;         //从根结点开始搜索
    BTreeNode<T>* pre = NULL;
    /*从根结点开始往下查找*/
    int i=0;
    while (ptr != NULL)
    {
        for (i = 1;i <= ptr->n;i++)      //在结点内部进行顺序搜索
        {
            if (ptr->key[i] == x)      //如果找到
            {
                result.r = ptr;       //当前查找驻留的结点指针
                result.i = i;         //查找成功的关键码
                result.tag = 1;       //是否查找成功
                return result;
            };
            if (ptr->key[i] > x)       //查找失败
                break;
        };
        pre = ptr;
        ptr = ptr->subTree[i - 1];      //从失配的关键码左边的子树继续查找
    };
    /*如果查找失败*/
    result.r = pre;
    result.i = i;                     //可以在i-1和i之间进行插入
    result.tag = 0;                   //查找失败 

    return result;
};
/////////////////////////////////Search()函数结束

/////////////////////////////////////////////////
//Insert()公有成员函数  B树的插入操作
//把指定的关键码插入到B树中,使得仍然满足B树的要求
//首先对B树进行搜索,如果关键码已经存在则插入失败,
//否则执行插入，并按B树要求进行调整
//一般来说,执行插入的肯定是在叶子结点上进行
//但是如果查找成功的话,可能在非叶子结点上就结束了
/////////////////////////////////////////////////
template<class T>
bool BTree<T>::Insert(const T& x)
{
    /*如果当前的B树是空的,就新建之*/
    if (root == NULL)                  //如果当前的B树是空的
    {
        root = new BTreeNode<T>(m);   //新建一个结点
        root->Insert(x, NULL);            //把关键码插入到key[]数组第一个位置
        return true;
    };

    /*如果当前的B树不空,就搜索该树*/
    Triple<T> Tp;                   //查找结果三元组
    Tp = Search(x);
    int IsIn = Tp.tag;
    if (IsIn == 1)                     //关键码已经存在
    {
        cout << "关键码"<<x<<"已存在!" << endl;
        return false;               //插入失败
    };

    /*插入关键码直到结点关键码不溢出为止*/
    BTreeNode<T>* ptr = Tp.r;         //查找失败而驻留的结点
    int loc = Tp.i - 1;                 //在k[loc]后进行插入
    int pkey = x;
    BTreeNode<T>* p = NULL;           //随关键码一起要插入的右子树的根结点
    do
    {
        ptr->Insert(pkey, p);        //把关键码和相关的新分裂的右结点插入当前结点
        if (ptr->n > m - 1)              //如果关键码溢出,则需要进行调整
        {
            /*以下处理结点的分裂*/
            int k = ptr->key[m / 2 + 1];  //提取出要上提的关键码
            BTreeNode<T>* right     //建立分裂后右边的结点
                = new BTreeNode<T>(m);
            right->n = ptr->n - m / 2 - 1;  //右结点的关键码个数
            
            for (int i = m / 2 +2;i <= ptr->n;i++)//key[0]没有使用，会比subtree【】的参数大一
                right->key[i - m / 2 - 1] //把右半边的关键码复制进入右结点
                = ptr->key[i];

            for (int i = m / 2 + 1;i <= ptr->n;i++)
            {
                right->subTree[i - m / 2 - 1] //把相应的分裂后的右结点子树指针复制入新结点
                    = ptr->subTree[i];  
            }
            
            /*关于左结点*/   //没有修改相应的父结点的指针指向左结点，导致左结点丢失
            ptr->n = m / 2;             //修改原结点使之成为左结点
            
            right->parent
                = ptr->parent;       //新分裂的结点
            p = right;                //p是随k一起上提的新建分裂右结点指针
            pkey = k;
           // ParentAdjust(ptr->parent);///////// 调整子树结点的父指针
            /*如果当前的结点没有父结点*/
            if (ptr->parent == NULL)   //如果当前结点没有父结点,就新建父结点
            {
                BTreeNode<T>* newp  //新建一个父结点
                    = new BTreeNode<T>(m);
                newp->key[1] = k;     //插入新关键码
                newp->subTree[0]    //新关键码左边的子树
                    = ptr;
                newp->subTree[1]    //新关键码右边的子树
                    = right;
                newp->n = 1;          //新关键码个数为1
                ptr->parent = newp;   //设置父结点指针
                right->parent = newp;
                root = newp;
                return true;        //插入成功并结束
            }
            else                    //如果有父结点存在
                ptr = ptr->parent;    //把上提的关键码继续插入父结点
        }
        else                        //不溢出则插入成功
            return true;
    } while (ptr != NULL);

    return true;
};
/////////////////////////Insert()公有成员函数结束

/////////////////////////////////////////////////
//Display()公有成员函数  
//递归:显示当前B树的缩进格式
/////////////////////////////////////////////////
template<class T>
void BTree<T>::Display(BTreeNode<T>* p, int k)
{
    if (p != NULL)
    {       
            Display(p->subTree[(p->n)], k + 1);//递归显示靠右结点
            for (int i = 0; i < k - 1; i++) cout << "            ";//k控制空格
            if (p->n > 0) {
                cout << ">>>>" << "n:" << p->n << " ";
                for (int i = 1;i <= p->n;i++)//显示当前结点所有关键码
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
    //凹入法打印二叉树
    if (p == NULL) return; //空树不打印 
    print_tree(t->rightchild, n + 1); //递归打印右子树 
    for (int i = 0; i < n - 1; i++) cout << "      ";
    if (n > 0) {
        cout << ">>>>";
        cout << p->key[0]<< endl; //显示内容 
    }
    print_tree(t->leftchild, n + 1); //递归打印左子树
}
*/

//调整父结点
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





