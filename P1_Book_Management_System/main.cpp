#include<iostream>
#include "header.h"

using namespace std;

//数据的处理
	//1. 用什么东西处理数据。————> 链表
	//2. 数据的结构。————> 图书信息

Node* head_node = nullptr;	//全局变量，链表，存储图书信息

// 界面函数
void menuFunc() {
	cout << "------------------------------" << endl;
	cout << "\t图书管理系统 \t" << endl;
	cout << "\t0. 退出系统" << endl;
	cout << "\t1. 登记书籍" << endl;
	cout << "\t2. 浏览书籍" << endl;
	cout << "\t3. 借阅书籍" << endl;
	cout << "\t4. 归还书籍" << endl;
	cout << "\t5. 书籍排序" << endl;
	cout << "\t6. 删除书籍" << endl;
	cout << "\t7. 查找书籍" << endl;
	cout << "------------------------------" << endl;
	cout << "请输入（0~7）:\n";
}

// 交互函数
void keyDown() {
	Book* tempBook = new Book();	// 临时变量，存储用户输入
	Node* result = nullptr;
	int user_key = 0;	//用户按键选择
	cin >> user_key;
	switch (user_key) {
	case 0:
		cout << "退出成功\n";
		exit(0);
		break;
	case 1:
		cout << " 【登记】 \n";
		cout << " 请输入书籍信息(name, price, num): ";
		cin >> tempBook->name >> tempBook->price >> tempBook->num;
		insertNodeByHead(head_node, tempBook);
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 2:
		cout << " 【浏览】 \n";
		printList(head_node);
		break;
	case 3:
		cout << " 【借阅】 \n";
		cout << "请输入要借阅的书名: ";
		cin >> tempBook->name;
		result = searchByName(head_node, tempBook->name);
		if (result) {
			//找到了
			if (result->data->num > 0) {
				result->data->num--;
				cout << "借阅成功" << endl;
			}
			else {
				cout << "当前书籍无库存，借阅失败\n";
			}
		}
		else {
			//没有找到
			cout << "没有相关书籍无法借阅！\n";
		}
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 4:
		cout << " 【归还】 \n";
		cout << "请输入要归还的书名: ";
		cin >> tempBook->name;
		result = searchByName(head_node, tempBook->name);
		if (result) {
			//找到了
			result->data->num++;
			cout << "归还成功" << endl;
		}
		else {
			//没有找到
			cout << "该书来源非法！\n";
		}
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 5:
		cout << " 【排序】 \n";
		bubbleSort(head_node);
		break;
	case 6:
		cout << " 【删除】 \n";
		cout << "请输入要删除的书名: ";
		cin >> tempBook->name;
		deleteNodeByName(head_node, tempBook->name);
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 7:
		cout << " 【查找】 \n";
		cout << " 请输入要查询的书名: ";
		cin >> tempBook->name;
		result = searchByName(head_node, tempBook->name);
		if (result) {
			cout << "书名\t价格\t数量\n";
			cout << result->data->name << "\t" << result->data->price << "\t"
				<< result->data->num << "\t";
		}
		else {
			cout << " 无法找到相关信息! " << endl;
		}
		break;
	default:
		cout << "输入错误，请重新输入: ";
	}
}


int main() {

	head_node = createHead();
	readFromFile("bookinfo.txt", head_node);


	while (1) {
		menuFunc();
		keyDown();
		system("pause");
		system("cls");
	}


	return 0;
}