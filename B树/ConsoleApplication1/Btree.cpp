#include <windows.h> //加上这一句，注意头文件的顺序
#include"Btree.h"

bool Btree::Insert(const int& x) {
	//将关键码x插入到一个驻留在磁盘上的m阶B树中
	Triple loc = Search(x);//在树中搜索x插入的位置
	if (!loc.tag) return false;//x已存在树中，不再插入
	MtreeNode* p = loc.r, * q;//r是x要插入的结点地址，q为父结点
	MtreeNode* ap = NULL, * t;//ap是插入关键码的右邻指针，t为父结点
	int K = x; int j = loc.i;//(K,ap)形成插入二元组
	while (1)
	{
		if (p->n < m - 1) {//结点关键码个数未超出
			//insertkey(p, j, K, ap);//K，ap插入到j位置，且p->n加1
			//PutNode(p); return true;//输出结点到磁盘，返回调用程序
		}
		int s = (m + 1) / 2;//准备分裂结点，s是m/2取上整位置
		//insertkey(p, j, K, ap);//先插入结点中p->n到达m
		q = new MtreeNode;//建立新结点q
		//move(p, q, s, m);
		//将p的key[s+1...m]和ptr[s...m]移到q的key[1...s-1]和ptr[0...s-1],p->n改为s-1,q->改为m-s
		K = p->key[s]; ap = q;//(K,ap）形成向上插入二元组
		if (p->parent != NULL)
		{//从下向上调整：原来的p不为根
			t = p->parent;
			//GetNode(t);//磁盘上读取t
			j = 0;
			//在父结点内顺序搜索插入的位置
			t->key[(t->n) + 1] = MaxValue;//监视哨,
			while (t->key[j + 1] < K) j++;//搜索，找到大于K的关键码停
			q->parent = p->parent;//新结点的父指针赋值
			//PutNode(p);PutNode(q);//输出到磁盘
			p = t;//p上升到父结点，向上调整
		}
		else {//原来的p是根，则要产生新的根
			root = new MtreeNode;
			root->n = 1; root->parent = NULL;//创建新根
			root->key[1] = K;
			root->ptr[0] = p; root->ptr[1] = ap;//新根指向两个子树结点
			q->parent = p->parent = root;//为新结点的父指针赋值
			//PutNode(p); PutNode(q); PutNode(root);//输出到磁盘
			return true;
		}
	}





	};
