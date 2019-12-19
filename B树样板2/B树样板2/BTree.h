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
    int id;//���
    string name;
    string auther;
    int pstock;//�ִ������軹�仯
    int tstock;//����
    Book() {
        id = -1;
        pstock = 0;
        tstock = 0;
        name = "null";
        auther = "null";
    }
}Book;

typedef struct BTNode {
    int keynum;             //�ڵ㵱ǰ�ؼ��ָ���
    KeyType key[m + 1];       //�ؼ������飬key[0]δ��
    struct BTNode* parent;  //˫�׽��ָ��
    struct BTNode* ptr[m + 1]; //���ӽ��ָ������
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

BTree T = NULL;//ȫ�ֱ���


typedef struct {
    BTree pt;               //ָ���ҵ��Ľ��
    int i;                  //1<=i<=m,�ڽ���еĹؼ���λ��
    int tag;                //1�����ҳɹ���0������ʧ��
}result;                    //B���Ĳ��ҽ������

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
void RootFirst(BTree st, string ar);//�����������е�����



void RootFirst(BTree st,string ar)//ǰ��������ߵ���Ϣ
{
    if (st != NULL)
    {
        int n = st->keynum;      
        for (int k = 1;k <= n;k++)       //�����ǰ�������еĹؼ���
            if (st->recptr[k]->auther == ar)
            {               
                book_find(st->recptr[k]->id);
                cout << endl;
            }
        for (int i = 0;i <= n;i++)       //�ݹ�������е�����
            RootFirst(st->ptr[i],ar);
    };
}

void book_author() {
    cout << "��������Ҫ��ѯ�����ߣ�" << endl;
    string ar;
    cin >> ar;
    cout << "*������Ϣ���£�*" << endl << endl;
    RootFirst(T, ar);
    cout << "*��ѯ���*" << endl;

}


void book_return() {
    cout << "��������Ҫ�黹���鼮�ż�ͼ��֤�ţ�" << endl;
    int temp;
    broow bw;
    cin >> temp >> bw.broow_id;
    result q;
    SearchBTree(T, temp, q);
    if (q.tag == 0) cout << "û�н���զ�����أ�����" << endl;
    else {
        if (q.pt) q.pt->recptr[q.i]->pstock++;//�ִ�������   
        cout << "ͼ��֤�ţ�" << bw.broow_id << endl << "Ӧ�黹���ڣ�"
            << bw.date.year << "��" << (bw.date.month + 1) % 12 << "��" << (bw.date.day)%30 << "��" << endl;
        cout << "*�黹�ɹ�*" << endl;
        book_find(temp);
    }


}


void book_broow() {
    cout << "��������Ҫ���ĵ��鼮�š�ͼ��֤�ţ�" << endl;
    int temp;
    broow bw;
    cin >> temp>>bw.broow_id;
    result q;
    SearchBTree(T,temp,q);
    if (q.tag == 0) cout << "�鼮������ѽ��" << endl;
    else {
        
        cout << "ͼ��֤�ţ�" << bw.broow_id << endl << "�黹���ڣ�"
            << bw.date.year<< "��" << (bw.date.month+1)%12 << "��" << (bw.date.day) % 30 << "��" << endl;
        if (q.pt->recptr[q.i]->pstock > 0)
        {
            q.pt->recptr[q.i]->pstock--;//�ִ�������
           
            cout << "*���ĳɹ�*" << endl;
        }
        else cout << "*����ʧ��*" << endl << "����̫������������" << endl;
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
            
            SearchBTree(T, temp, q);//�����²���Ԫ�ص�����λ��,���ҳɹ�           
            //q.pt->recptr[q.i] = b;//�Ѽ�¼��Ϣ����Ź�������,�Ȳ�����
            
            q.pt->recptr[q.i]->pstock+=k;
            q.pt->recptr[q.i]->tstock+=k;
            cout << "*" << temp << "���鼮���ɹ�*" << endl ;
            cout << endl;
        }
        else
        {    
            SearchBTree(T, temp, q);//�����²���Ԫ�ص�����λ��
            q.pt->recptr[q.i]->pstock+=k;
            q.pt->recptr[q.i]->tstock+=k;
            delete b;
            cout << "*�鼮�Ѵ��ڿ���*" << endl;
        }

}
void book_ruku() {
    cout << "������Ҫ�ɱ������鼮��Ϣ����š����������ߡ���������" << endl;
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
        delete p.pt->recptr[p.i];//��ɾ��¼
        DeleteBTree(p.pt, p.i, T);//��ɾԪ��
        cout << "*ɾ���ɹ�*" << endl;       
    }
    else cout << "*�鼮���ڿ���*" << endl;
}
void book_qingchu() {
    cout << "������Ҫ�������ţ�" << endl;
    KeyType temp;
    cin >> temp;
    book_delete(temp);
}

void book_show(Book* b) {
    cout << "��ţ�" << b->id << endl;
    cout << "������" << b->name << endl;
    cout << "���ߣ�" << b->auther << endl;
    cout << "�ִ�����" << b->pstock << endl;
    cout << "�ܴ�����" << b->tstock << endl;
}


void book_find(KeyType temp)
{
    result p;
    SearchBTree(T, temp, p);
    if (p.tag)
    {
        //cout << "*���ҳɹ�*" << endl;
        book_show(p.pt->recptr[p.i]);
       // cout<<p.pt->recptr[p.i]<<endl;
    }
    else cout << "*����ʧ��*" << endl;
}


void book_chazhao() {
    cout << "������Ҫ���ҵ���ţ�" << endl;
    KeyType temp;
    cin >> temp;
    book_find(temp);

}








void Display(BTree p, int k=1)
{
    if (p != NULL)
    {
        Display(p->ptr[(p->keynum)], k + 1);//�ݹ���ʾ���ҽ��
        if (p->keynum == 3) Display(p->ptr[p->keynum - 1], k + 1);
        for (int i = 0; i < k - 1; i++) cout << "            ";//k���ƿո�
        if (p->keynum > 0) {
            cout << ">>>>" << "n:" << p->keynum << " ";
            for (int i = 1;i <= p->keynum;i++)//��ʾ��ǰ������йؼ���
                cout << p->key[i] << " ";
            cout << endl;
        }
        if (p->keynum == 2) Display(p->ptr[p->keynum - 1], k + 1);      
        if (p->keynum == 3) Display(p->ptr[p->keynum - 2], k + 1);

        Display(p->ptr[0], k + 1);
        if (p&&p->parent&&p==p->parent->ptr[0]) cout << endl;//��֤������һ��

    }
};


int Search(BTree p, int k) {  //��p->key[1..p->keynum]��k
    int i = 1;
    while (i <= p->keynum && k > p->key[i]) i++;
    return i;
}
void SearchBTree(BTree t, int k, result& r) {
    //��m��B��t�ϲ��ҹؼ���k����r����(pt,i,tag).
    //�����ҳɹ�������tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���k��
    //����tag=0����Ҫ����ؼ���Ϊk�ļ�¼��Ӧλ��pt����е�i-1���͵�i���ؼ���֮��
    int i = 0, found = 0;
    BTree p = t, q = NULL;//��ʼ��pָ����ڵ㣬p������ָ������ҽ�㣬qָ����˫��
    while (p != NULL && 0 == found) {
        i = Search(p, k);
        if (i <= p->keynum && p->key[i] == k) found = 1;
        else { q = p;p = p->ptr[i - 1]; }//ָ������
    }
    if (1 == found) {//���ҳɹ�������k��λ��p��i
        r = { p,i,1 };
    }
    else {//���Ҳ��ɹ�������k�Ĳ���λ��q��i
        r = { q,i,0 };
    }
}
//���������
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

void split(BTree& q, int s, BTree& ap, Book* b) {//��q�����ѳ�������㣬ǰһ�뱣����ԭ��㣬��һ������ap��ָ�½��
    int i, j, n = q->keynum;
    ap = (BTNode*)malloc(sizeof(BTNode));//�����½��
    ap->ptr[0] = q->ptr[s];
    for (i = s + 1, j = 1;i <= n;i++, j++) {    //��һ������ap���
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
void newRoot(BTree& t, BTree p, int x, BTree ap, Book* b) {//�����µĸ����
    t = (BTNode*)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;t->ptr[1] = ap;
    t->key[1] = x;
    t->recptr[1] = b;//��¼����
   
    if (p != NULL) p->parent = t;
    if (ap != NULL) ap->parent = t;
    t->parent = NULL;
    
}

void Insert(BTree& q, int i, int x, BTree ap, Book* b) {//�ؼ���x���½��ָ��ap�ֱ�嵽q->key[i]��q->ptr[i]
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
    //��B����q����key[i-1]��key[i]֮�����ؼ���k
    //���������ؼ��ָ�������b���Ľף�������˫��ָ�������н����ѣ�ʹ��t����m��B��
    int x, s, finished = 0, needNewRoot = 0;
    BTree ap;
    if (NULL == q) newRoot(t, NULL, k, NULL,b);
    else {
        x = k;ap = NULL;
        Record* temp = b;
        while (0 == needNewRoot && 0 == finished) 
        {
            Insert(q, i, x, ap,temp);//x��ap�ֱ�嵽q->key[i]��q->ptr[i]
            //q->recptr[i] = temp;
            if (q->keynum < m) finished = 1;//�������
            else {
                s = (m + 1) / 2;//�е�������
                x = q->key[s];//�´�ѭ��ʱ���븸�����
                temp=q->recptr[s];
                
                split(q, s, ap,b);             
                if (q->parent != NULL) {
                    q = q->parent;//�������
                    i = Search(q, x);//��˫�׽���в���x�Ĳ���λ��
                }
                else
                {
                    needNewRoot = 1;//t�ǿ������߸�����Ѿ����ѳ�Ϊq��ap���
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
void Successor(BTree& p, int i) {//�ɺ�����²���ն˽�����С�ؼ��ִ������йؼ���key[i]
    BTree child = p->ptr[i];
    while (child->ptr[0] != NULL) child = child->ptr[0];
    p->key[i] = child->key[1];
    p->recptr[i] = child->recptr[1];
    p = child;
}
void Restore(BTree& p, int i, BTree& T) {//��B�����е���
    int j;
    BTree ap = p->parent;
    if (ap == NULL) //����������ֿյĸ���㣬��ɾ���ø���㣬���߼�1
    {
        T = p; //���������
        p = p->parent;
        return;
    }
    BTree lc, rc, pr;
    int finished = 0, r = 0;
    while (!finished)
    {
        r = 0;
        while (ap->ptr[r] != p) r++; //ȷ��p��ap�����е�λ��
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
        if (r > 0 && lc != NULL && (lc->keynum > (m - 1) / 2))//�����ֵܽ�ؼ���
        {
            p->keynum++;
            for (j = p->keynum;j > 1;j--)//���ؼ�������
            {
                p->key[j] = p->key[j - 1];
                p->recptr[j] = p->recptr[j - 1];
                p->ptr[j] = p->ptr[j - 1];
            }
            p->key[1] = ap->key[r];//���ײ��뵽���
            p->recptr[1] = ap->recptr[r];
            p->ptr[1] = p->ptr[0];
            p->ptr[0] = lc->ptr[lc->keynum];
            if (NULL != p->ptr[0])//�޸�p�е���Ů�ĸ����Ϊp
            {
                p->ptr[0]->parent = p;
            }
            ap->key[r] = lc->key[lc->keynum];//���ֵ����Ƶ�����λ��
            ap->recptr[r] = lc->recptr[lc->keynum];
            lc->keynum--;
            finished = 1;
            break;
        }
        else if (ap->keynum > r&& rc != NULL && (rc->keynum > (m - 1) / 2)) //�����ֵܽ�ؼ���
        {
            p->keynum++;
            p->key[p->keynum] = ap->key[r]; //���ײ��뵽���
            p->recptr[p->keynum] = ap->recptr[r];
            p->ptr[p->keynum] = rc->ptr[0];
            if (NULL != p->ptr[p->keynum]) //�޸�p�е���Ů�ĸ����Ϊp
                p->ptr[p->keynum]->parent = p;
            ap->key[r] = rc->key[1]; //���ֵ����Ƶ�����λ��
            ap->recptr[r] = rc->recptr[1];
            rc->ptr[0] = rc->ptr[1];
            for (j = 1;j < rc->keynum;j++)  //���ֵܽ��ؼ�������
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
        while (ap->ptr[r] != p) //����ȷ��p��ap������λ��
            r++;
        if (r > 0 && (ap->ptr[r - 1]->keynum <= (m - 1) / 2)) //�����ֵܺϲ�      
        {
            lc = ap->ptr[r - 1];
            p->keynum++;
            for (j = p->keynum;j > 1;j--) //��p���ؼ��ֺ�ָ������1λ
            {
                p->key[j] = p->key[j - 1];
                p->recptr[j] = p->recptr[j - 1];
                p->ptr[j] = p->ptr[j - 1];
            }
            p->key[1] = ap->key[r]; //�����Ĺؼ�����p�ϲ�
            p->recptr[1] = ap->recptr[r];
            p->ptr[1] = p->ptr[0]; //��p���ʣ���ָ���������

            p->ptr[0] = lc->ptr[lc->keynum];//�����ֵ�����һ��ָ��,����ʹ��
            ap->ptr[r] = lc;//ָ��ָ��ϲ���Ҫ�����Ľ��
            for (j = 1;j <= lc->keynum + p->keynum;j++) //�����p�йؼ��ֺ�ָ���Ƶ�p���ֵ���
            {
                lc->key[lc->keynum + j] = p->key[j];
                lc->recptr[lc->keynum + j] = p->recptr[j];
                lc->ptr[lc->keynum + j] = p->ptr[j];
            }
            //�޸�p�е���Ů�ĸ����Ϊlc          
            for (j = 1;j <= p->keynum;j++)//p->ptr[0]�� lc->ptr[lc->keynum]��ͬ��������          
                if (lc->ptr[lc->keynum + j])   lc->ptr[lc->keynum + j]->parent = lc;
            //p���ĸ�ָ��ָ�򸸽�㣿       

            lc->keynum = lc->keynum + p->keynum;  //�ϲ���ؼ��ֵĸ���
            for (j = r;j < ap->keynum;j++)//��������йؼ��ֺ�ָ������
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
        else//�����ֵܺϲ�
        {
            rc = ap->ptr[r + 1];
            if (r == 0)
                r++;
            p->keynum++;
            p->key[p->keynum] = ap->key[r]; //�����Ĺؼ�����p�ϲ�
            p->recptr[p->keynum] = ap->recptr[r];
            p->ptr[p->keynum] = rc->ptr[0]; //�����ֵ�����һ��ָ��
            rc->keynum = p->keynum + rc->keynum;//�ϲ���ؼ��ֵĸ���
            ap->ptr[r - 1] = rc;//���ࣿ���ã�ָ���ָ��ϲ���ָ��Ľ��
            for (j = 1;j <= (rc->keynum - p->keynum);j++)//��p���ֵܹؼ��ֺ�ָ������
            {
                rc->key[p->keynum + j] = rc->key[j];
                rc->recptr[p->keynum + j] = rc->recptr[j];
                rc->ptr[p->keynum + j] = rc->ptr[j];
            }
            for (j = 1;j <= p->keynum;j++)//�����p�йؼ��ֺ�ָ���Ƶ�p���ֵ�
            {
                rc->key[j] = p->key[j];
                rc->recptr[j] = p->recptr[j];
                rc->ptr[j] = p->ptr[j];
            }
            rc->ptr[0] = p->ptr[0];
            //�޸�p�е���Ů�ĸ����Ϊrc       
            for (j = 0;j <= p->keynum;j++)
                if (rc->ptr[j])   rc->ptr[j]->parent = rc;

            for (j = r;j < ap->keynum;j++)//��������йؼ��ֺ�ָ������
            {
                ap->key[j] = ap->key[j + 1];
                ap->recptr[j] = ap->recptr[j + 1];
                ap->ptr[j] = ap->ptr[j + 1];
            }
            ap->keynum--;//�����Ĺؼ��ָ�����1
            pr = p;
            free(pr);
            pr = NULL;
            p = rc;
        }
        ap = ap->parent;
        if (p->parent->keynum >= (m - 1) / 2 || (NULL == ap && p->parent->keynum > 0))
            finished = 1;
        else if (ap == NULL) //����������ֿյĸ���㣬��ɾ���ø���㣬���߼�1
        {
            pr = T;
            T = p; //���������
            free(pr);
            pr = NULL;
            finished = 1;
        }
        p = p->parent;
    }
}
void DeleteBTree(BTree& p, int i, BTree& T) {//ɾ��B����p���ĵ�i���ؼ���
    if (p->ptr[i] != NULL) {//�����������²���ն˽��
        Successor(p, i);//��Ai�������ҳ����²���ն˽�����С�ؼ������ki
        DeleteBTree(p, 1, T);//ת��Ϊɾ�����²���ն˽�����С�ؼ���
    }
    else {//�������²���ն˽��
        Remove(p, i);
        if (p->keynum < (m - 1) / 2)//ɾ����ؼ��ָ���С��(m-1)/2
            Restore(p, i, T);//����B��
    }
}

void show_Btree(BTree& p)
{
    if (p == NULL) { cout << "B��������ѽ��" << endl;return; }
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
    cout << "New success��" << endl;
}



void insert_keytype()
{
    cout << "������Ҫ�����Ԫ�أ�" << endl;
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
            cout << "*" << temp << "����ɹ�*" << endl<<"B-Tree��";show_Btree(T);
            cout <<endl;
        }
        else cout << "*Ԫ���Ѵ�����B����*" << endl;
    }
}
void find_keytype()
{
    cout << "������Ҫ���ҵ�Ԫ�أ�" << endl;
    KeyType temp;
    cin >> temp;
    result p;
    SearchBTree(T, temp, p);
    if (p.tag)
    {
        cout << "*���ҳɹ�*" << endl;
        //cout<<p.pt->recptr[p.i]<<endl;
    }
    else cout << "Lookup failure" << endl;
}

void delete_keytype()
{
    cout << "������Ҫɾ����Ԫ�أ�" << endl;
    KeyType temp;
    cin >> temp;
    result p;
    SearchBTree(T, temp, p);
    if (p.tag)
    {
        DeleteBTree(p.pt, p.i, T);
        cout << "*ɾ���ɹ�*" << endl;show_Btree(T);
        cout << "";
    }
    else cout << "*Ԫ�ز�������B����*" << endl;
}



#endif
#pragma once
