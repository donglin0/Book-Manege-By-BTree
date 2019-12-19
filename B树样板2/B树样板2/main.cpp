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
			<< "\t\t\t\t*\t\t7.采编入库\t\t*" << endl
			<< "\t\t\t\t*\t\t8.清除库存\t\t*" << endl
			<< "\t\t\t\t*\t\t9.借阅\t\t\t*" << endl
			<< "\t\t\t\t*\t\t10.归还\t\t\t*" << endl
			<< "\t\t\t\t*\t\t11.查找(书籍)\t\t*" << endl	
			<< "\t\t\t\t*\t\t12.查找(著者)\t\t*" << endl


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
			cout << "\t\t\t\t**************查找（元素）***************" << endl;
			find_keytype();break;
		case 5:
			cout << "\t\t\t\t**************显示（括号）***************" << endl;
			show_Btree(T);cout <<endl;break;
		case 6:
			cout << "\t\t\t\t**************显示（凹入）***************" << endl;
			Display(T);cout << endl;break;
		case 7:
			cout << "\t\t\t\t**************采编入库***************" << endl;
			book_ruku();break;
		case 8:
			cout << "\t\t\t\t**************清除库存***************" << endl;
			book_qingchu();break;
		case 9:
			cout << "\t\t\t\t**************借阅***************" << endl;
			book_broow();break;
		case 10:
			cout << "\t\t\t\t**************归还***************" << endl;
			book_return();break;
		case 11:
			cout << "\t\t\t\t**************查找（书籍）***************" << endl;
			book_chazhao();break;
		case 12:
			cout << "\t\t\t\t**************查找（著者）***************" << endl;
			book_author();break;
		
		
		
		
		
		case 0:
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