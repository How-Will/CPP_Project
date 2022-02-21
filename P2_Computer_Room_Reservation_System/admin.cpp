#include"admin.h"

//Ĭ�Ϲ���
Admin::Admin() {

}

//�вι��� ������Ա������ ���룩
Admin::Admin(string name, string pwd) {
	this->m_name = name;
	this->m_pwd = pwd;

	// ��ʼ����������ȡ�������ļ���ѧ������ʦ��Ϣ
	initVector();
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
	string error_tip;
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
			error_tip = "ѧ���ظ�������������";
			break;
		}
		else if (user_key == 2) {
			tip = "������ְ�����: ";
			file_name = TEACHER_FILE;
			error_tip = "ְ������ظ�������������";
			break;
		}
		else {
			cout << "���벻�Ϸ�������������" << endl;
			system("pause");
			cout << endl;
		}
	}

	ofs.open(file_name, fstream::out | fstream::app);	// �󶨶�Ӧ���ļ�
	int id;
	string name;
	string pwd;

	cout << tip;
	while (1) {
		cin >> id;
		bool res = checkReapeat(id, user_key);

		if (!res)
			break;
		else 
			cout << error_tip << endl;
	}
	
	cout << "����������: ";
	cin >> name;
	cout << "����������: ";
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;
	

	system("pause");
	system("cls");

	ofs.close();

	// ���ó�ʼ�������ӿڣ����»�ȡ�ļ��е����ݣ��������ʱ���µ�bug
	this->initVector();
}

//��ʼ����������
void Admin::initVector() {
	this->v_stu.clear();
	this->v_tea.clear();	// �Ƚ��������

	ifstream ifs(STUDENT_FILE, fstream::in);
	if (!ifs.is_open()) {
		cout << "student.txt��ȡʧ��" << endl;
		return;
	}

	// ��ȡѧ���ļ��е���Ϣ����v_stu��
	Student stu;
	while (ifs >> stu.m_id >> stu.m_name >> stu.m_pwd) {
		v_stu.push_back(stu);	
	}
	cout << "��ǰѧ������Ϊ: " << v_stu.size() << endl;
	ifs.close();

	// ��ȡ��ʦ�ļ��е���Ϣ����v_tea��
	ifs.open(TEACHER_FILE, fstream::in);
	if (!ifs.is_open()) {
		cout << "teacher.txt��ȡʧ��" << endl;
		return;
	}

	Teacher tea;
	while (ifs >> tea.m_empid >> tea.m_name >> tea.m_pwd) {
		v_tea.push_back(tea);
	}
	cout << "��ǰ��ʦ����Ϊ: " << v_tea.size() << endl;
	ifs.close();

	// ��ȡ�����ļ��е���Ϣ����v_com��
	ifs.open(COMPUTER_FILE, fstream::in);
	if (!ifs.is_open()) {
		cout << "computerRoom.txt��ȡʧ��" << endl;
		return;
	}

	ComputerRoom com;
	while (ifs >> com.m_com_id >> com.m_max_num) {
		v_com.push_back(com);
	}
	cout << "��ǰ�Ļ�������Ϊ: " << v_com.size() << endl;
	ifs.close();
}

// ����ظ�����
bool Admin::checkReapeat(int id, int type) {
	if (type == 1) {	// ���ѧ��id�Ƿ��ظ�
		for (auto e : v_stu) {
			if (id == e.m_id)
				return true;
		}
	}
	else if (type == 2) {	// ����ʦְ������Ƿ��ظ�
		for (auto e : v_tea) {
			if (id == e.m_empid) 
				return true;
		}
	}
	return false;
}

void printStudent(const Student& s) {
	cout << "ѧ��: " << s.m_id << " ����: " << s.m_name << " ����: " << s.m_pwd << endl;
}

void printTeacher(const Teacher& t) {
	cout << "ְ�����: " << t.m_empid << " ����: " << t.m_name << " ����: " << t.m_pwd << endl;
}

//�鿴�˺�
void Admin::showPerson() {
	cout << "��ѡ��Ҫ�鿴������\n";
	cout << "1. �鿴����ѧ��\n";
	cout << "2. �鿴������ʦ\n";
	cout << "���������ѡ��: ";

	int user_key = 0;
	cin >> user_key;

	switch (user_key)
	{
	case 1:	// �鿴ѧ����Ϣ
		cout << "����ѧ����Ϣ����: " << endl;
		for_each(v_stu.cbegin(), v_stu.cend(), printStudent);
		break;
	case 2:	// �鿴��ʦ��Ϣ
		cout << "���н�ʦ��Ϣ����: " << endl;
		for_each(v_tea.cbegin(), v_tea.cend(), printTeacher);
		break;
	default:
		cout << "�Ƿ����룬������һ��Ԫ" << endl;
		break;
	}

	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Admin::showComputer() {
	cout << "������Ϣ����: " << endl;
	for (auto e : v_com) {
		cout << "�������: " << e.m_com_id << " �����������: " << e.m_max_num << endl;
	}

	system("pause");
	system("cls");
}


//���ԤԼ��¼
void Admin::cleanFile() {
	cout << "����ļ��󲻿ɻָ�����ȷ��(y/n): ";
	string user_key;
	cin >> user_key;

	if (user_key == "y") {
		ofstream ofs(ORDER_FILE, fstream::trunc);
		ofs.close();
		cout << "��ճɹ�!" << endl;
	}
	else{
		cout << "������һ��Ԫ" << endl;
	}
	
	system("pause");
	system("cls");
}