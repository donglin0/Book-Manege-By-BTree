#include"BTree.h"



void insert() {
    for (;;)
    {
        BTree<int> BT(3);//三阶树
        int i = 0;
        for (;;) {
            cin >> i;
            if (i == 1111) break;
            BT.Insert(i);
        }
        // BT.Insert(53);      //依此在B树中插入关键码
	     BT.Display();      //显示当前B树的内容
    }

}

void menu()
{
	while (1)
	{
		cout << "\t\t\t\t**************多项式计算器***************" << endl
			<< "\t\t\t\t*\t\t1.插入\t\t\t*" << endl
			<< "\t\t\t\t*\t\t2.删除\t\t\t*" << endl
			<< "\t\t\t\t*\t\t3.显示\t\t\t*" << endl
			<< "\t\t\t\t*\t\t4.结束\t\t\t*" << endl
			<< "\t\t\t\t*****************************************" << endl;

		int cho;
		cout << "***请输入选择：***" << endl;
		cin>>cho;
		switch (cho)
		{
		case 1:
			cout << "\t\t\t\t**************插入***************" << endl;
			insert();
				break;
		case 2:
			cout << "\t\t\t\t**************删除***************" << endl;
			break;
		case 3:
			cout << "\t\t\t\t**************显示***************" << endl;
			break;
		case 4:
			cout << "***谢谢使用！***" << endl;
			exit(0);
		default:
			cout << "***输入有误，请重新输入！***" << endl << endl;


		}
	}
}



//main()函数  测试B树的程序
int main()
{  
	menu();
    return 0;
};
///////////////////////////////////main()函数结束