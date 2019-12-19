#pragma   once 
#ifndef HH
#define HH

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define KeyType int
#define MAX 0
#define Record Book
const int m = 4;
using namespace std;

typedef struct Book {
    int id;//书号
    string name;
    string auther;
    int pstock;//现存量，借还变化
    int tstock;//总量
    Book() {
        id = -1;
        pstock = 0;
        tstock = 0;
        name = "null";
        auther = "null";
    }
}Book;

typedef struct BTNode {
    int keynum;             //节点当前关键字个数
    KeyType key[m + 1];       //关键字数组，key[0]未用
    struct BTNode* parent;  //双亲结点指针
    struct BTNode* ptr[m + 1]; //孩子结点指针数组
    Record* recptr[m + 1];
    
    BTNode() {
        keynum = 0;
        parent = NULL;
        for (int i = 0;i < m + 1;i++)
        {
            ptr[i] = NULL;
            recptr[i] = NULL;
        }
    }
}BTNode, * BTree;

BTree T = NULL;//全局变量


typedef struct {
    BTree pt;               //指向找到的结点
    int i;                  //1<=i<=m,在结点中的关键字位序
    int tag;                //1：查找成功，0：查找失败
}result;                    //B树的查找结果类型

typedef struct date {
    int year;
    int month;
    int day;
    date() {
        year = 2019;
        month = 12;
        day = 19;
    }
}date;

typedef struct broow {
    int broow_id;
    date date;
    broow() {
        broow_id = 0;
    }
};


int Search(BTree p, int k);
void SearchBTree(BTree t, int k, result& r);

void ParentAdjust(BTNode* p);
void split(BTree& q, int s, BTree& ap, Book* b);
void newRoot(BTree& t, BTree p, int x, BTree ap, Book* b);
void Insert(BTree& q, int i, int x, BTree ap, Book* b);
void InsertBTree(BTree& t, int k, BTree q, int i,Book* b);

void Remove(BTree& p, int i);
void Successor(BTree& p, int i);
void Restore(BTree& p, int i, BTree& T);
void DeleteBTree(BTree& p, int i, BTree& T);

void show_Btree(BTree& p);
void show_Btree2(BTree& p, int deep);
void Destory(BTree& t);
void creat_btree();
void insert_keytype();
void find_keytype();
void delete_keytype();

void book_insert(KeyType temp, Book* b,int k);
void book_ruku();
void book_show(Book* b);
void book_delete(KeyType temp);
void book_qingchu();
void book_broow();
void book_find(KeyType temp);
void book_return();
void RootFirst(BTree st, string ar);//查找作者所有的著作



void RootFirst(BTree st,string ar)//前序查找作者的信息
{
    if (st != NULL)
    {
        int n = st->keynum;      
        for (int k = 1;k <= n;k++)       //输出当前结点的所有的关键码
            if (st->recptr[k]->auther == ar)
            {               
                book_find(st->recptr[k]->id);
                cout << endl;
            }
        for (int i = 0;i <= n;i++)       //递归输出所有的子树
            RootFirst(st->ptr[i],ar);
    };
}

void book_author() {
    cout << "请输入你要查询的著者：" << endl;
    string ar;
    cin >> ar;
    cout << "*著作信息如下：*" << endl << endl;
    RootFirst(T, ar);
    cout << "*查询完成*" << endl;

}


void book_return() {
    cout << "请输入你要归还的书籍号及图书证号：" << endl;
    int temp;
    broow bw;
    cin >> temp >> bw.broow_id;
    result q;
    SearchBTree(T, temp, q);
    if (q.tag == 0) cout << "没有借书咋还书呢？？？" << endl;
    else {
        if (q.pt) q.pt->recptr[q.i]->pstock++;//现存量增加   
        cout << "图书证号：" << bw.broow_id << endl << "应归还日期："
            << bw.date.year << "年" << (bw.date.month + 1) % 12 << "月" << (bw.date.day)%30 << "日" << endl;
        cout << "*归还成功*" << endl;
        book_find(temp);
    }


}


void book_broow() {
    cout << "请输入你要借阅的书籍号、图书证号：" << endl;
    int temp;
    broow bw;
    cin >> temp>>bw.broow_id;
    result q;
    SearchBTree(T,temp,q);
    if (q.tag == 0) cout << "书籍不存在呀！" << endl;
    else {
        
        cout << "图书证号：" << bw.broow_id << endl << "归还日期："
            << bw.date.year<< "年" << (bw.date.month+1)%12 << "月" << (bw.date.day) % 30 << "日" << endl;
        if (q.pt->recptr[q.i]->pstock > 0)
        {
            q.pt->recptr[q.i]->pstock--;//现存量减少
           
            cout << "*借阅成功*" << endl;
        }
        else cout << "*借阅失败*" << endl << "该书太抢手啦！！！" << endl;
        book_find(temp);
    }
}

void book_insert(KeyType temp, Book* b,int k)
{                
        result p,q;
        SearchBTree(T, temp, p);
        if (p.tag == 0)
        {
            
            InsertBTree(T, temp,p.pt, p.i,b);
            
            SearchBTree(T, temp, q);//查找新插入元素的最新位置,查找成功           
            //q.pt->recptr[q.i] = b;//把记录信息和书号关联起来,先插后关联
            
            q.pt->recptr[q.i]->pstock+=k;
            q.pt->recptr[q.i]->tstock+=k;
            cout << "*" << temp << "号书籍入库成功*" << endl ;
            cout << endl;
        }
        else
        {    
            SearchBTree(T, temp, q);//查找新插入元素的最新位置
            q.pt->recptr[q.i]->pstock+=k;
            q.pt->recptr[q.i]->tstock+=k;
            delete b;
            cout << "*书籍已存在库中*" << endl;
        }

}
void book_ruku() {
    cout << "请输入要采编入库的书籍信息（书号、书名、著者、数量）：" << endl;
    Book* b = new Book;
    int k;
    cin >> b->id >> b->name >> b->auther>>k;
    book_insert(b->id,b,k);
}

void book_delete(KeyType temp)
{   
    result p;
    SearchBTree(T, temp, p);
    if (p.tag)
    {
        delete p.pt->recptr[p.i];//先删记录
        DeleteBTree(p.pt, p.i, T);//再删元素
        cout << "*删除成功*" << endl;       
    }
    else cout << "*书籍不在库中*" << endl;
}
void book_qingchu() {
    cout << "请输入要清除的书号：" << endl;
    KeyType temp;
    cin >> temp;
    book_delete(temp);
}

void book_show(Book* b) {
    cout << "书号：" << b->id << endl;
    cout << "书名：" << b->name << endl;
    cout << "著者：" << b->auther << endl;
    cout << "现存量：" << b->pstock << endl;
    cout << "总存量：" << b->tstock << endl;
}


void book_find(KeyType temp)
{
    result p;
    SearchBTree(T, temp, p);
    if (p.tag)
    {
        //cout << "*查找成功*" << endl;
        book_show(p.pt->recptr[p.i]);
       // cout<<p.pt->recptr[p.i]<<endl;
    }
    else cout << "*查找失败*" << endl;
}


void book_chazhao() {
    cout << "请输入要查找的书号：" << endl;
    KeyType temp;
    cin >> temp;
    book_find(temp);

}








void Display(BTree p, int k=1)
{
    if (p != NULL)
    {
        Display(p->ptr[(p->keynum)], k + 1);//递归显示靠右结点
        if (p->keynum == 3) Display(p->ptr[p->keynum - 1], k + 1);
        for (int i = 0; i < k - 1; i++) cout << "            ";//k控制空格
        if (p->keynum > 0) {
            cout << ">>>>" << "n:" << p->keynum << " ";
            for (int i = 1;i <= p->keynum;i++)//显示当前结点所有关键码
                cout << p->key[i] << " ";
            cout << endl;
        }
        if (p->keynum == 2) Display(p->ptr[p->keynum - 1], k + 1);      
        if (p->keynum == 3) Display(p->ptr[p->keynum - 2], k + 1);

        Display(p->ptr[0], k + 1);
        if (p&&p->parent&&p==p->parent->ptr[0]) cout << endl;//保证不连在一块

    }
};


int Search(BTree p, int k) {  //在p->key[1..p->keynum]找k
    int i = 1;
    while (i <= p->keynum && k > p->key[i]) i++;
    return i;
}
void SearchBTree(BTree t, int k, result& r) {
    //在m阶B树t上查找关键字k，用r返回(pt,i,tag).
    //若查找成功，则标记tag=1，指针pt所指结点中第i个关键字等于k；
    //否则tag=0，若要插入关键字为k的记录，应位于pt结点中第i-1个和第i个关键字之间
    int i = 0, found = 0;
    BTree p = t, q = NULL;//初始，p指向根节点，p将用于指向待查找结点，q指向其双亲
    while (p != NULL && 0 == found) {
        i = Search(p, k);
        if (i <= p->keynum && p->key[i] == k) found = 1;
        else { q = p;p = p->ptr[i - 1]; }//指针下移
    }
    if (1 == found) {//查找成功，返回k的位置p及i
        r = { p,i,1 };
    }
    else {//查找不成功，返回k的插入位置q及i
        r = { q,i,0 };
    }
}
//调整父结点
void ParentAdjust(BTNode* p)
{
    if (p != NULL)
    {
        for (int i = 0;i <= p->keynum;i++)
        {
            if (p->ptr[i] != NULL)
            {
                p->ptr[i]->parent = p;
                ParentAdjust(p->ptr[i]);
            }
        }
    }
};

void split(BTree& q, int s, BTree& ap, Book* b) {//将q结点分裂成两个结点，前一半保留在原结点，后一半移入ap所指新结点
    int i, j, n = q->keynum;
    ap = (BTNode*)malloc(sizeof(BTNode));//生成新结点
    ap->ptr[0] = q->ptr[s];
    for (i = s + 1, j = 1;i <= n;i++, j++) {    //后一半移入ap结点
        ap->key[j] = q->key[i];
        ap->recptr[j] = q->recptr[i];//TMDDDDDDDDD
        ap->ptr[j] = q->ptr[i];
    }
    ap->keynum = n - s;
    ap->parent = q->parent;

    for (i = 0;i <= n - s;i++)
        if (ap->ptr[i] != NULL) ap->ptr[i]->parent = ap;
    q->keynum = s - 1;
    ParentAdjust(q);
    ParentAdjust(ap);

}
void newRoot(BTree& t, BTree p, int x, BTree ap, Book* b) {//生成新的根结点
    t = (BTNode*)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;t->ptr[1] = ap;
    t->key[1] = x;
    t->recptr[1] = b;//记录关联
   
    if (p != NULL) p->parent = t;
    if (ap != NULL) ap->parent = t;
    t->parent = NULL;
    
}

void Insert(BTree& q, int i, int x, BTree ap, Book* b) {//关键字x和新结点指针ap分别插到q->key[i]和q->ptr[i]
    int j, n = q->keynum;
    for (j = n;j >= i;j--) {
        q->key[j + 1] = q->key[j];
        q->recptr[j + 1] = q->recptr[j];
        q->ptr[j + 1] = q->ptr[j];
    }
    q->key[i] = x;
    q->recptr[i] = b;
    q->ptr[i] = ap;
    if (ap != NULL) ap->parent = q;
    q->keynum++;
}
void InsertBTree(BTree& t, int k, BTree q, int i,Book* b) {
    //在B树中q结点的key[i-1]和key[i]之间插入关键字k
    //若插入后结点关键字个数等于b树的阶，则沿着双亲指针链进行结点分裂，使得t仍是m阶B树
    int x, s, finished = 0, needNewRoot = 0;
    BTree ap;
    if (NULL == q) newRoot(t, NULL, k, NULL,b);
    else {
        x = k;ap = NULL;
        Record* temp = b;
        while (0 == needNewRoot && 0 == finished) 
        {
            Insert(q, i, x, ap,temp);//x和ap分别插到q->key[i]和q->ptr[i]
            //q->recptr[i] = temp;
            if (q->keynum < m) finished = 1;//插入完成
            else {
                s = (m + 1) / 2;//中点往上提
                x = q->key[s];//下次循环时插入父结点中
                temp=q->recptr[s];
                
                split(q, s, ap,b);             
                if (q->parent != NULL) {
                    q = q->parent;//结点上移
                    i = Search(q, x);//在双亲结点中查找x的插入位置
                }
                else
                {
                    needNewRoot = 1;//t是空树或者根结点已经分裂成为q和ap结点
                    newRoot(t, q, x, ap,temp);          
                
                }
                
            }
        }       

           
    }
}
void Remove(BTree& p, int i)
{
    int j, n = p->keynum;
    for (j = i;j < n;j++) {
        p->key[j] = p->key[j + 1];
        p->recptr[j] = p->recptr[j + 1];
        p->ptr[j] = p->ptr[j + 1];
    }
    p->keynum--;
}
void Successor(BTree& p, int i) {//由后继最下层非终端结点的最小关键字代替结点中关键字key[i]
    BTree child = p->ptr[i];
    while (child->ptr[0] != NULL) child = child->ptr[0];
    p->key[i] = child->key[1];
    p->recptr[i] = child->recptr[1];
    p = child;
}
void Restore(BTree& p, int i, BTree& T) {//对B树进行调整
    int j;
    BTree ap = p->parent;
    if (ap == NULL) //若调整后出现空的根结点，则删除该根结点，树高减1
    {
        T = p; //根结点下移
        p = p->parent;
        return;
    }
    BTree lc, rc, pr;
    int finished = 0, r = 0;
    while (!finished)
    {
        r = 0;
        while (ap->ptr[r] != p) r++; //确定p在ap子树中的位置
        if (r == 0)
        {
            r++;
            lc = NULL, rc = ap->ptr[r];
        }
        else if (r == ap->keynum)
        {
            rc = NULL;lc = ap->ptr[r - 1];
        }
        else
        {
            lc = ap->ptr[r - 1];rc = ap->ptr[r + 1];
        }
        if (r > 0 && lc != NULL && (lc->keynum > (m - 1) / 2))//向左兄弟借关键字
        {
            p->keynum++;
            for (j = p->keynum;j > 1;j--)//结点关键字右移
            {
                p->key[j] = p->key[j - 1];
                p->recptr[j] = p->recptr[j - 1];
                p->ptr[j] = p->ptr[j - 1];
            }
            p->key[1] = ap->key[r];//父亲插入到结点
            p->recptr[1] = ap->recptr[r];
            p->ptr[1] = p->ptr[0];
            p->ptr[0] = lc->ptr[lc->keynum];
            if (NULL != p->ptr[0])//修改p中的子女的父结点为p
            {
                p->ptr[0]->parent = p;
            }
            ap->key[r] = lc->key[lc->keynum];//左兄弟上移到父亲位置
            ap->recptr[r] = lc->recptr[lc->keynum];
            lc->keynum--;
            finished = 1;
            break;
        }
        else if (ap->keynum > r&& rc != NULL && (rc->keynum > (m - 1) / 2)) //向右兄弟借关键字
        {
            p->keynum++;
            p->key[p->keynum] = ap->key[r]; //父亲插入到结点
            p->recptr[p->keynum] = ap->recptr[r];
            p->ptr[p->keynum] = rc->ptr[0];
            if (NULL != p->ptr[p->keynum]) //修改p中的子女的父结点为p
                p->ptr[p->keynum]->parent = p;
            ap->key[r] = rc->key[1]; //右兄弟上移到父亲位置
            ap->recptr[r] = rc->recptr[1];
            rc->ptr[0] = rc->ptr[1];
            for (j = 1;j < rc->keynum;j++)  //右兄弟结点关键字左移
            {
                rc->key[j] = rc->key[j + 1];
                rc->recptr[j] = rc->recptr[j + 1];
                rc->ptr[j] = rc->ptr[j + 1];
            }
            rc->keynum--;
            finished = 1;
            break;
        }
        r = 0;
        while (ap->ptr[r] != p) //重新确定p在ap子树的位置
            r++;
        if (r > 0 && (ap->ptr[r - 1]->keynum <= (m - 1) / 2)) //与左兄弟合并      
        {
            lc = ap->ptr[r - 1];
            p->keynum++;
            for (j = p->keynum;j > 1;j--) //将p结点关键字和指针右移1位
            {
                p->key[j] = p->key[j - 1];
                p->recptr[j] = p->recptr[j - 1];
                p->ptr[j] = p->ptr[j - 1];
            }
            p->key[1] = ap->key[r]; //父结点的关键字与p合并
            p->recptr[1] = ap->recptr[r];
            p->ptr[1] = p->ptr[0]; //将p结点剩余的指针继续右移

            p->ptr[0] = lc->ptr[lc->keynum];//从左兄弟右移一个指针,并不使用
            ap->ptr[r] = lc;//指针指向合并后要保留的结点
            for (j = 1;j <= lc->keynum + p->keynum;j++) //将结点p中关键字和指针移到p左兄弟中
            {
                lc->key[lc->keynum + j] = p->key[j];
                lc->recptr[lc->keynum + j] = p->recptr[j];
                lc->ptr[lc->keynum + j] = p->ptr[j];
            }
            //修改p中的子女的父结点为lc          
            for (j = 1;j <= p->keynum;j++)//p->ptr[0]和 lc->ptr[lc->keynum]相同，不考虑          
                if (lc->ptr[lc->keynum + j])   lc->ptr[lc->keynum + j]->parent = lc;
            //p结点的父指针指向父结点？       

            lc->keynum = lc->keynum + p->keynum;  //合并后关键字的个数
            for (j = r;j < ap->keynum;j++)//将父结点中关键字和指针左移
            {
                ap->key[j] = ap->key[j + 1];
                ap->recptr[j] = ap->recptr[j + 1];
                ap->ptr[j] = ap->ptr[j + 1];
            }
            ap->keynum--;
            pr = p;free(pr);
            pr = NULL;
            p = lc;
        }
        else//与右兄弟合并
        {
            rc = ap->ptr[r + 1];
            if (r == 0)
                r++;
            p->keynum++;
            p->key[p->keynum] = ap->key[r]; //父结点的关键字与p合并
            p->recptr[p->keynum] = ap->recptr[r];
            p->ptr[p->keynum] = rc->ptr[0]; //从右兄弟左移一个指针
            rc->keynum = p->keynum + rc->keynum;//合并后关键字的个数
            ap->ptr[r - 1] = rc;//多余？无用！指针改指向合并后指向的结点
            for (j = 1;j <= (rc->keynum - p->keynum);j++)//将p右兄弟关键字和指针右移
            {
                rc->key[p->keynum + j] = rc->key[j];
                rc->recptr[p->keynum + j] = rc->recptr[j];
                rc->ptr[p->keynum + j] = rc->ptr[j];
            }
            for (j = 1;j <= p->keynum;j++)//将结点p中关键字和指针移到p右兄弟
            {
                rc->key[j] = p->key[j];
                rc->recptr[j] = p->recptr[j];
                rc->ptr[j] = p->ptr[j];
            }
            rc->ptr[0] = p->ptr[0];
            //修改p中的子女的父结点为rc       
            for (j = 0;j <= p->keynum;j++)
                if (rc->ptr[j])   rc->ptr[j]->parent = rc;

            for (j = r;j < ap->keynum;j++)//将父结点中关键字和指针左移
            {
                ap->key[j] = ap->key[j + 1];
                ap->recptr[j] = ap->recptr[j + 1];
                ap->ptr[j] = ap->ptr[j + 1];
            }
            ap->keynum--;//父结点的关键字个数减1
            pr = p;
            free(pr);
            pr = NULL;
            p = rc;
        }
        ap = ap->parent;
        if (p->parent->keynum >= (m - 1) / 2 || (NULL == ap && p->parent->keynum > 0))
            finished = 1;
        else if (ap == NULL) //若调整后出现空的根结点，则删除该根结点，树高减1
        {
            pr = T;
            T = p; //根结点下移
            free(pr);
            pr = NULL;
            finished = 1;
        }
        p = p->parent;
    }
}
void DeleteBTree(BTree& p, int i, BTree& T) {//删除B树上p结点的第i个关键字
    if (p->ptr[i] != NULL) {//若不是在最下层非终端结点
        Successor(p, i);//在Ai子树中找出最下层非终端结点的最小关键字替代ki
        DeleteBTree(p, 1, T);//转换为删除最下层非终端结点的最小关键字
    }
    else {//若是最下层非终端结点
        Remove(p, i);
        if (p->keynum < (m - 1) / 2)//删除后关键字个数小于(m-1)/2
            Restore(p, i, T);//调整B树
    }
}

void show_Btree(BTree& p)
{
    if (p == NULL) { cout << "B树不存在呀！" << endl;return; }
    bool have_child = false;
    printf("[");
    for (int i = 1;i <= p->keynum;i++)
    {
        if (i == 1);
        else printf(" ");

        printf("%d", p->key[i]);
    }
    printf("]");
    for (int i = 0;i <= p->keynum;i++)
    {
        if (p->ptr[i] != NULL)
        {
            if (i == 0) printf("<");
            else printf(",");
            show_Btree(p->ptr[i]);
            have_child = true;
        }
    }
    if (have_child) printf(">");   
}

void show_Btree2(BTree& p, int deep)
{
    if (p == NULL) { return; }
    int i;
    for (i = 0; i < p->keynum;i++)
    {
        show_Btree2(p->ptr[i], deep + 1);
        for (int i = 0;i < deep;i++)
        {
            printf("\t");
        }
        printf("%d\n", p->key[i + 1]);
    }
    show_Btree2(p->ptr[i], deep + 1);
}
void Destory(BTree& t)
{
    int i = 0;
    if (t != NULL)
    {
        while (i < t->keynum)
        {
            Destory(t->ptr[i]);
            free(t->ptr[i]);
     
            i++;
        }
    }
    free(t);
    t = NULL;
}
void creat_btree()
{
    T = new BTNode;
    T->keynum = 0;
    cout << "New success！" << endl;
}



void insert_keytype()
{
    cout << "请输入要插入的元素：" << endl;
    KeyType temp=-1;
    while (temp != MAX)
    {
        cin >> temp;
        if (temp == MAX) break;
        result p;
        SearchBTree(T, temp, p);
        if (p.tag == 0)
        {
            InsertBTree(T, temp, p.pt, p.i,NULL);
            cout << "*" << temp << "插入成功*" << endl<<"B-Tree：";show_Btree(T);
            cout <<endl;
        }
        else cout << "*元素已存在于B树中*" << endl;
    }
}
void find_keytype()
{
    cout << "请输入要查找的元素：" << endl;
    KeyType temp;
    cin >> temp;
    result p;
    SearchBTree(T, temp, p);
    if (p.tag)
    {
        cout << "*查找成功*" << endl;
        //cout<<p.pt->recptr[p.i]<<endl;
    }
    else cout << "Lookup failure" << endl;
}

void delete_keytype()
{
    cout << "请输入要删除的元素：" << endl;
    KeyType temp;
    cin >> temp;
    result p;
    SearchBTree(T, temp, p);
    if (p.tag)
    {
        DeleteBTree(p.pt, p.i, T);
        cout << "*删除成功*" << endl;show_Btree(T);
        cout << "";
    }
    else cout << "*元素不存在于B树中*" << endl;
}



#endif
#pragma once
