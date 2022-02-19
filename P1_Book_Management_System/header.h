#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Book {
	string name;	// 书名
	unsigned num;	// 数量
	double price;	//价格
};

struct Node {
	Book* data;
	struct Node* next;
};


// 创建表头，表头就是一个结构体变量。实现一个有表头的链表
Node* createHead() {
	Node* head_node = new Node();
	// 变量的基本规则，使用前必须初始化
	head_node->next = nullptr;
	return head_node;
}

// 创建节点,为插入做准备。把用户数据变为结构体变量
Node* createNode(Book* data) {
	Node* new_node = new Node();
	new_node->data = data;
	new_node->next = nullptr;
	return new_node;
}

// 头插法
void insertNodeByHead(Node* head_node, Book* data) {
	Node* new_node = createNode(data);

	new_node->next = head_node->next;
	head_node->next = new_node;
}

// 尾插法
void insertNodeByTail(Node* head_node, Book* data) {
	Node* new_node = createNode(data);

	Node* p_move = head_node;
	while (p_move->next) {	// 查找尾结点
		p_move = p_move->next;
	}

	p_move->next = new_node;
}

// 根据书名删除元素
void deleteNodeByName(Node* head_node, const string book_name) {
	Node* pos_pre_node = head_node;
	Node* pos_node = head_node->next;

	while (pos_node != nullptr && pos_node->data->name != book_name) {	// 查找目标结点
		pos_pre_node = pos_node;
		pos_node = pos_pre_node->next;
	}
	// 讨论结果
	if (pos_node == nullptr)	// 没找到
		return;
	else {		// 找到了
		cout << "删除成功\n";
		pos_pre_node->next = pos_node->next;
		delete pos_node;
		pos_node = nullptr;
	}
}


// 查找目标结点
Node* searchByName(Node* head_node, const string book_name) {
	Node* pos_node = head_node->next;

	while (pos_node != nullptr && pos_node->data->name != book_name)//查找目标节点
		pos_node = pos_node->next;

	return pos_node;	//返回nullptr，表示没找到
}

// 打印链表
void printList(Node* head_node) {
	Node* p_move = head_node->next;
	cout << "书名\t数量\t价格\n";
	while (p_move) {
		cout << p_move->data->name << "\t" << p_move->data->num << "\t" <<
			p_move->data->price << endl;
		p_move = p_move->next;
	}
}

// 根据书的价格冒泡排序
void bubbleSort(Node* head_node) {
	for (Node* p = head_node->next; p != nullptr; p = p->next) {
		for (Node* q = p->next; q != nullptr; q = q->next) {
			if (q->data->price > p->data->price) {
				Book* tempBook = q->data;
				q->data = p->data;
				p->data = tempBook;
			}
		}
	}
}

// 文件读写
// 读操作
void readFromFile(const string filename, Node* head_node) {
	ifstream ifs(filename, fstream::in);
	Book* tempBook = new Book();

	if (ifs) {	// 判断文件是否成功打开，为真表示成功打开
		while (ifs >> tempBook->name >> tempBook->price >> tempBook->num) {
			insertNodeByHead(head_node, tempBook);	// 插入链表
		}
	}
	else {
		// 不存在就创建文件
		ifs.open(filename, fstream::out | fstream::app);
	}
	ifs.close();	//关闭文件流
}

// 写操作，将列表内容写入文件
void saveIntoFile(const string filename, Node* head_node) {
	ofstream ofs(filename, fstream::app);	//默认为输出和追加

	Node* p_move = head_node->next;

	if (ofs) {	// 判断文件是否成功打开
		while (p_move) {
			ofs << p_move->data->name << "\t" << p_move->data->price << "\t" << p_move->data->num;
			p_move = p_move->next;
		}
	}
	else {
		cout << "文件打开失败" << endl;
	}

	ofs.close();	// 关闭文件流
}