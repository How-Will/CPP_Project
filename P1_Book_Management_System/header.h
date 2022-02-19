#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Book {
	string name;	// ����
	unsigned num;	// ����
	double price;	//�۸�
};

struct Node {
	Book* data;
	struct Node* next;
};


// ������ͷ����ͷ����һ���ṹ�������ʵ��һ���б�ͷ������
Node* createHead() {
	Node* head_node = new Node();
	// �����Ļ�������ʹ��ǰ�����ʼ��
	head_node->next = nullptr;
	return head_node;
}

// �����ڵ�,Ϊ������׼�������û����ݱ�Ϊ�ṹ�����
Node* createNode(Book* data) {
	Node* new_node = new Node();
	new_node->data = data;
	new_node->next = nullptr;
	return new_node;
}

// ͷ�巨
void insertNodeByHead(Node* head_node, Book* data) {
	Node* new_node = createNode(data);

	new_node->next = head_node->next;
	head_node->next = new_node;
}

// β�巨
void insertNodeByTail(Node* head_node, Book* data) {
	Node* new_node = createNode(data);

	Node* p_move = head_node;
	while (p_move->next) {	// ����β���
		p_move = p_move->next;
	}

	p_move->next = new_node;
}

// ��������ɾ��Ԫ��
void deleteNodeByName(Node* head_node, const string book_name) {
	Node* pos_pre_node = head_node;
	Node* pos_node = head_node->next;

	while (pos_node != nullptr && pos_node->data->name != book_name) {	// ����Ŀ����
		pos_pre_node = pos_node;
		pos_node = pos_pre_node->next;
	}
	// ���۽��
	if (pos_node == nullptr)	// û�ҵ�
		return;
	else {		// �ҵ���
		cout << "ɾ���ɹ�\n";
		pos_pre_node->next = pos_node->next;
		delete pos_node;
		pos_node = nullptr;
	}
}


// ����Ŀ����
Node* searchByName(Node* head_node, const string book_name) {
	Node* pos_node = head_node->next;

	while (pos_node != nullptr && pos_node->data->name != book_name)//����Ŀ��ڵ�
		pos_node = pos_node->next;

	return pos_node;	//����nullptr����ʾû�ҵ�
}

// ��ӡ����
void printList(Node* head_node) {
	Node* p_move = head_node->next;
	cout << "����\t����\t�۸�\n";
	while (p_move) {
		cout << p_move->data->name << "\t" << p_move->data->num << "\t" <<
			p_move->data->price << endl;
		p_move = p_move->next;
	}
}

// ������ļ۸�ð������
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

// �ļ���д
// ������
void readFromFile(const string filename, Node* head_node) {
	ifstream ifs(filename, fstream::in);
	Book* tempBook = new Book();

	if (ifs) {	// �ж��ļ��Ƿ�ɹ��򿪣�Ϊ���ʾ�ɹ���
		while (ifs >> tempBook->name >> tempBook->price >> tempBook->num) {
			insertNodeByHead(head_node, tempBook);	// ��������
		}
	}
	else {
		// �����ھʹ����ļ�
		ifs.open(filename, fstream::out | fstream::app);
	}
	ifs.close();	//�ر��ļ���
}

// д���������б�����д���ļ�
void saveIntoFile(const string filename, Node* head_node) {
	ofstream ofs(filename, fstream::app);	//Ĭ��Ϊ�����׷��

	Node* p_move = head_node->next;

	if (ofs) {	// �ж��ļ��Ƿ�ɹ���
		while (p_move) {
			ofs << p_move->data->name << "\t" << p_move->data->price << "\t" << p_move->data->num;
			p_move = p_move->next;
		}
	}
	else {
		cout << "�ļ���ʧ��" << endl;
	}

	ofs.close();	// �ر��ļ���
}