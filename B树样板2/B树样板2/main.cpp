#include"BTree.h"


void menu()
{
	while (1)
	{
		cout << "\t\t\t\t**************图书管理系统***************" << endl
			<< "\t\t\t\t*\t\t1.建立新的4阶B树\t*" << endl
			<< "\t\t\t\t*\t\t2.插入\t\t\t*" << endl
			<< "\t\t\t\t*\t\t3.删除\t\t\t*" << endl
			<< "\t\t\t\t*\t\t4.查找\t\t\t*" << endl
			<< "\t\t\t\t*\t\t5.显示（括号）\t\t*" << endl
			<< "\t\t\t\t*\t\t6.显示（凹入）\t\t*" << endl
			<< "\t\t\t\t*\t\t7.结束\t\t\t*" << endl
			<< "\t\t\t\t*****************************************" << endl;
		int cho;
		cout << "***请输入选择：***" << endl;
		cin >> cho;
		switch (cho)
		{
		case 1:
			cout << "*B树创建成功！*" << endl;
			Destory(T);creat_btree();break;
		case 2:
			cout << "\t\t\t\t**************插入***************" << endl;
			insert_keytype();break;
		case 3:
			cout << "\t\t\t\t**************删除***************" << endl;
			delete_keytype();break;
		case 4:
			cout << "\t\t\t\t**************查找***************" << endl;
			find_keytype();break;
		case 5:
			cout << "\t\t\t\t**************显示（括号）***************" << endl;
			show_Btree(T);cout <<endl;break;
		case 6:
			cout << "\t\t\t\t**************显示（凹入）***************" << endl;
			Display(T);cout << endl;break;
		case 7:
			cout << "***谢谢使用！***" << endl;
			exit(0);
		default:
			cout << "***请您看清楚再输入！OK？***" << endl << endl;
		}
	}
}

int main()
{
    //freopen("in.txt","r",stdin);
	
	menu();
    return 0;
}