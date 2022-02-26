#include"teacher.h"


// Ĭ�Ϲ���
Teacher::Teacher() {

}

// �вι���	(ְ����ţ� ������ ����)
Teacher::Teacher(int empid, string name, string pwd) {
	this->m_empid = empid;
	this->m_name = name;
	this->m_pwd = pwd;
}

// �˵�����
void Teacher::operMenu() {
	cout << "============  ��ӭ��ʦ: " << this->m_name << "��¼!  ============\n";
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.�鿴����ԤԼ    | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.���ԤԼ        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.ע����¼        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "����������ѡ��: ";
}

// �鿴����ԤԼ
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_order_data.size(); i++) {
		cout << i + 1 << "�� ";

		cout << "ԤԼ����:��" << of.m_order_data[i]["date"] << " ";
		cout << "ʱ��:" << (of.m_order_data[i]["interval"] == "1" ? "����" : "����") << " ";
		cout << "ѧ��:" << of.m_order_data[i]["stuId"] << " ";
		cout << "����:" << of.m_order_data[i]["stuName"] << " ";
		cout << "����:" << of.m_order_data[i]["roomId"] << " ";

		string status = "״̬:";
		// 1. ����� 2. ��ԤԼ -1. ԤԼʧ��  0. ȡ��ԤԼ
		if (of.m_order_data[i]["status"] == "1")
			status += "�����";
		else if (of.m_order_data[i]["status"] == "2")
			status += "ԤԼ�ɹ�";
		else if (of.m_order_data[i]["status"] == "-1")
			status += "ԤԼʧ�ܣ����δͨ��";
		else
			status += "ԤԼ��ȡ��";
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

// ���ԤԼ
void Teacher::validOrder() {
	OrderFile of;	
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}


	vector<int> v;
	int index = 0;
	cout << "����˵�ԤԼ��¼����: " << endl;
	for (int i = 0; i < of.m_order_data.size(); i++) {
		// ���Ҵ�������е�ԤԼ��¼
		if (of.m_order_data[i]["status"] == "1") {
			v.push_back(i);
			cout << ++index << "�� ";
			
			cout << "ԤԼ����:��" << of.m_order_data[i]["date"] << " ";
			cout << "ʱ��:" << (of.m_order_data[i]["interval"] == "1" ? "����" : "����") << " ";
			cout << "ѧ��:" << of.m_order_data[i]["stuId"] << " ";
			cout << "����:" << of.m_order_data[i]["roomId"] << " ";
			cout << "״̬:�����" << endl;
		}
	}

	cout << "��������˵�ԤԼ��¼��0������" << endl;
	int user_key = 0;	//�����û�ѡ���ԤԼ��¼
	int ret = 0;	// ����ԤԼ���

	while (1) {
		cin >> user_key;
		if (user_key >= 0 && user_key <= v.size()) {
			if (user_key == 0)
				break;
			else {
				cout << "��������˵Ľ��" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				cin >> ret;
				if (ret == 1) {
					of.m_order_data[v[user_key - 1]]["status"] = "2";
				}
				else {
					of.m_order_data[v[user_key - 1]]["status"] = "-1";
				}
				of.updateOrder();	//����ԤԼ��¼
				cout << "������" << endl;
				break;
			}
		}
		cout << "������������������!" << endl;
	}

	system("pause");
	system("cls");
}