#include<iostream>
#include "header.h"

using namespace std;

//���ݵĴ���
	//1. ��ʲô�����������ݡ���������> ����
	//2. ���ݵĽṹ����������> ͼ����Ϣ

Node* head_node = nullptr;	//ȫ�ֱ����������洢ͼ����Ϣ

// ���溯��
void menuFunc() {
	cout << "------------------------------" << endl;
	cout << "\tͼ�����ϵͳ \t" << endl;
	cout << "\t0. �˳�ϵͳ" << endl;
	cout << "\t1. �Ǽ��鼮" << endl;
	cout << "\t2. ����鼮" << endl;
	cout << "\t3. �����鼮" << endl;
	cout << "\t4. �黹�鼮" << endl;
	cout << "\t5. �鼮����" << endl;
	cout << "\t6. ɾ���鼮" << endl;
	cout << "\t7. �����鼮" << endl;
	cout << "------------------------------" << endl;
	cout << "�����루0~7��:\n";
}

// ��������
void keyDown() {
	Book* tempBook = new Book();	// ��ʱ�������洢�û�����
	Node* result = nullptr;
	int user_key = 0;	//�û�����ѡ��
	cin >> user_key;
	switch (user_key) {
	case 0:
		cout << "�˳��ɹ�\n";
		exit(0);
		break;
	case 1:
		cout << " ���Ǽǡ� \n";
		cout << " �������鼮��Ϣ(name, price, num): ";
		cin >> tempBook->name >> tempBook->price >> tempBook->num;
		insertNodeByHead(head_node, tempBook);
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 2:
		cout << " ������� \n";
		printList(head_node);
		break;
	case 3:
		cout << " �����ġ� \n";
		cout << "������Ҫ���ĵ�����: ";
		cin >> tempBook->name;
		result = searchByName(head_node, tempBook->name);
		if (result) {
			//�ҵ���
			if (result->data->num > 0) {
				result->data->num--;
				cout << "���ĳɹ�" << endl;
			}
			else {
				cout << "��ǰ�鼮�޿�棬����ʧ��\n";
			}
		}
		else {
			//û���ҵ�
			cout << "û������鼮�޷����ģ�\n";
		}
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 4:
		cout << " ���黹�� \n";
		cout << "������Ҫ�黹������: ";
		cin >> tempBook->name;
		result = searchByName(head_node, tempBook->name);
		if (result) {
			//�ҵ���
			result->data->num++;
			cout << "�黹�ɹ�" << endl;
		}
		else {
			//û���ҵ�
			cout << "������Դ�Ƿ���\n";
		}
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 5:
		cout << " ������ \n";
		bubbleSort(head_node);
		break;
	case 6:
		cout << " ��ɾ���� \n";
		cout << "������Ҫɾ��������: ";
		cin >> tempBook->name;
		deleteNodeByName(head_node, tempBook->name);
		saveIntoFile("bookinfo.txt", head_node);
		break;
	case 7:
		cout << " �����ҡ� \n";
		cout << " ������Ҫ��ѯ������: ";
		cin >> tempBook->name;
		result = searchByName(head_node, tempBook->name);
		if (result) {
			cout << "����\t�۸�\t����\n";
			cout << result->data->name << "\t" << result->data->price << "\t"
				<< result->data->num << "\t";
		}
		else {
			cout << " �޷��ҵ������Ϣ! " << endl;
		}
		break;
	default:
		cout << "�����������������: ";
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