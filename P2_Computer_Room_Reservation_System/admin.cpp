#include"admin.h"

//Ĭ�Ϲ���
Admin::Admin() {

}

//�вι��� ������Ա������ ���룩
Admin::Admin(string name, string pwd) {
	this->m_name = name;
	this->m_pwd = pwd;
}

//ѡ��˵�
void Admin::operMenu() {
	cout << "============  ��ӭ����Ա: " << this->m_name << "��¼!  ============\n";
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.����˺�        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.�鿴�˺�        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        3.�鿴����        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        4.���ԤԼ        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.ע����¼        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "����������ѡ��: ";
}

//����˺�
void Admin::addPerson() {
	string file_name;
	string tip;
	ofstream ofs;
	int user_key = 0;	// �����û���ѡ��

	while (1) {
		cout << "����˺ŵ�����\n";
		cout << "1. ���ѧ��" << endl;
		cout << "2. �����ʦ" << endl;
		cout << "���������ѡ��: ";

		cin >> user_key;

		if (user_key == 1) {
			tip = "������ѧ��: ";
			file_name = STUDENT_FILE;
			break;
		}
		else if (user_key == 2) {
			tip = "������ְ�����: ";
			file_name = TEACHER_FILE;
			break;
		}
		else {
			cout << "���벻�Ϸ�������������";
			system("pause");
			system("cls");
		}
	}

	ofs.open(file_name, fstream::out | fstream::app);	// �󶨶�Ӧ���ļ�
	int id;
	string name;
	string pwd;

	cout << tip;
	cin >> id;
	cout << "����������: ";
	cin >> name;
	cout << "����������: ";
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");

	ofs.close();
}

//�鿴�˺�
void Admin::showPerson() {

}

//�鿴������Ϣ
void Admin::showComputer() {

}

//���ԤԼ��¼
void Admin::cleanFile() {

}