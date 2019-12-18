#include"Mtree.h"


Triple Mtree::Search(const int& x) {

	Triple result;//记录搜索结果的三元组
	//GetNode(root);//从磁盘上读取位于根root的结点
	MtreeNode* p = root;//p是扫描指针
	MtreeNode* q = NULL;//q是父结点指针
	int temp = 0;//用来保存下面循环中内部变量i的值
	while (p != NULL) {//从根节点开始检测
		int i = 0; p->key[(p->n) + 1] = MaxValue;//为当前结点尾部设置监视哨
		while (p->key[i + 1] < x) i++; temp = i;//在结点内顺序搜索
		if (p->key[i + 1] == x) {//搜索成功，本结点中有x
			result.r = p;
			result.i = i + 1;
			result.tag = 0;
			return result;
		}
		q = p;//本结点中无x，q记下当前结点作为父结点
		p = p->ptr[i];//p下降到相应的子树，i从0开始
		//GetNode(p);//从磁盘中读取p结点
	}
	//x可能落入ki到ki+1的区间内
	result.r = q;//保存最后搜索到的结点的地址，即插入的位置
	result.i = temp;
	result.tag = 1;
	return result;//搜索失败返回插入位置
}