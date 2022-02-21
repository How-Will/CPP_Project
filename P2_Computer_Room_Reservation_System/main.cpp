#include<iostream>
#include<fstream>
#include<string>
#include"student.h"
#include"teacher.h"
#include"admin.h"
#include"globalFile.h"
#include"identity.h"

using namespace std;


// �������Ա�Ӳ˵�����
void adminMenu(Identity* &ident) {
	while (1) {
		// ����Ա�˵���ʾ
		ident->operMenu();	// ��̬������

		// ������ָ��ǿתΪ����ָ�룬��ʹ������Ĺ���
		Admin* admin = (Admin*)ident;

		int admin_key = 0;	// �����û���ѡ��
		cin >> admin_key;

		switch (admin_key)
		{
		case 1:
			//cout << "����˺�" << endl;
			admin->addPerson();
			break;
		case 2:
			//cout << "�鿴�˺�" << endl;
			admin->showPerson();
			break;
		case 3:
			//cout << "�鿴����" << endl;
			admin->showComputer();
			break;
		case 4:
			//cout << "���ԤԼ" << endl;
			admin->cleanFile();
			break;
		case 0:
			delete ident;	// ���ٵ���������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;	// return ���˳���������
		default:
			cout << "���벻�Ϸ�������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// ��¼���� �������ļ����� ����������ͣ�
void loginIn(string filename, int type) {
	// ����ָ�룬����ָ���������
	Identity* person = nullptr;

	// ���ļ�
	ifstream ifs(filename, ifstream::in);

	// �ж��ļ��Ƿ����
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	// ׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;

	// �ж����
	if (type == 1) {
		cout << "���������ѧ��: ";
		cin >> id;
	}
	else if (type == 2) {
		cout << "���������ְ����: ";
		cin >> id;
	}

	cout << "�������û�����";
	cin >> name;
	cout << "���������룺 ";
	cin >> pwd;


	int f_id;	// ���ļ��л�ȡ��id
	string f_name;	// ���ļ��л�ȡ������
	string f_pwd;	// ���ļ��л�ȡ����

	if (type == 1) {	// ѧ�������֤
		while (ifs >> f_id >> f_name >> f_pwd) {
			// ���û�������Ϣ���Ա�
			if (f_id == id && f_name == name && f_pwd == pwd) {
				cout << "ѧ����֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);
				// ����ѧ����ݵ����˵�

				return;
			}
		}
	}
	else if (type == 2) {
		while (ifs >> f_id >> f_name >> f_pwd) {
			if (f_id == id && f_name == name && f_pwd == pwd) {
				cout << "��ʦ��֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				// �����ʦ��ݵ����˵�
				 
				return;
			}
		}
	}
	else if (type == 3) {
		while (ifs >> f_name >> f_pwd) {
			if (f_name == name && f_pwd == pwd) {
				cout << "����Ա��֤��¼�ɹ�" << endl;
				system("cls");

				person = new Admin(name, pwd);
				// �������Ա�˵�����
				adminMenu(person);

				return;
			}
		}
	}

	cout << "��֤��¼ʧ��!" << endl;
	system("pause");
	system("cls");
}

// �����
void menuFunc() {
	cout << "============  ��ӭʹ�û���ԤԼϵͳ  ============\n";
	cout << endl << "�������������" << endl;
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.ѧ������        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.��    ʦ        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        3.�� �� Ա        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.��    ��        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "����������ѡ��: ";
}

// ��������
void keyDown() {

	int user_key = 0;	//�û���ѡ��
	cin >> user_key;

	switch (user_key)
	{
	case 1:		// ѧ�����
		loginIn(STUDENT_FILE, 1);
		break;
	case 2:		// ��ʦ���
		loginIn(TEACHER_FILE, 2);
		break;
	case 3:		// ����Ա���
		loginIn(ADMIN_FILE, 3);
		break;
	case 0:		// �˳�ϵͳ
		cout << "��ӭ��һ��ʹ��...." << endl;
		exit(0);
		break;
	default:
		cout << "���벻�Ϸ���������ѡ��! " << endl;
		system("pause");
		system("cls");
		break;
	}
}


int main() {
	
	while (1) {
		menuFunc();	//��ʾ����
		keyDown();
	}

	return 0;
}