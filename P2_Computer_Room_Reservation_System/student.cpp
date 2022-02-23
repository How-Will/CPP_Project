#include"student.h"

//Ĭ�Ϲ��캯��
Student::Student() {
	
}

//�вι��캯��  ������ѧ�ţ�����������
Student::Student(int id, string name, string pwd) {
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;

	// ��ʼ����������
	initVector();
}

//�˵�����
void Student::operMenu() {
	cout << "============  ��ӭѧ������: " << this->m_name << "��¼!  ============\n";
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.����ԤԼ        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.�鿴�ҵ�ԤԼ    | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        3.�鿴����ԤԼ    | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        4.ȡ��ԤԼ        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.ע����¼        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "����������ѡ��: ";
}

//����ԤԼ
void Student::applyOrder() {
	cout << "��������ʱ��Ϊ��һ������! " << endl;
	cout << "����������ԤԼ��ʱ��: " << endl;
	cout << "1. ��һ" << endl;
	cout << "2. �ܶ�" << endl;
	cout << "3. ����" << endl;
	cout << "4. ����" << endl;
	cout << "5. ����" << endl;
	
	//�����û�����
	int date = 0;	
	int interval = 0;
	int room = 0;

	while (1) {
		cin >> date;
		if (date >= 1 && date <= 5)
			break;
		cout << "������������������" << endl;
	}

	cout << "����������ԤԼ��ʱ���: " << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	
	while (1) {
		cin >> interval;
		if (interval >= 1 && interval <= 2)
			break;
		cout << "������������������" << endl;
	}

	cout << "��ѡ�����: " << endl;
	for (int i = 0; i != v_com.size(); i++) {
		cout << v_com[i].m_com_id << "�Ż�������: " << v_com[i].m_max_num << endl;
	}
	
	while (1) {
		cin >> room;
		if (room >= 1 && room <= v_com.size())
			break;
		cout << "������������������" << endl;
	}

	cout << "ԤԼ�ɹ��������......." << endl;

	ofstream ofs(ORDER_FILE, fstream::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;		// 1 ��ʾ�����

	ofs.close();

	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showMyOrder() {
	OrderFile orderf;
}

//�鿴����ԤԼ
void Student::showAllOrder() {

}

//ȡ��ԤԼ
void Student::cancelOrder() {

}

//��ʼ����������
void Student::initVector() {
	this->v_com.clear();	// �������

	ifstream ifs(COMPUTER_FILE, ifstream::in);

	ComputerRoom com;	// �����ļ���Ϣ
	while (ifs >> com.m_com_id >> com.m_max_num) {
		v_com.push_back(com);
	}

	ifs.close();
}