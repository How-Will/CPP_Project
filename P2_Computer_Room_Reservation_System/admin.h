#pragma once

#include<iostream>
#include<fstream>
#include"globalFile.h"
#include"identity.h"
using namespace std;

class Admin : public Identity {
public:
	//Ĭ�Ϲ���
	Admin();

	//�вι��� ������Ա������ ���룩
	Admin(string name, string pwd);

	//ѡ��˵�
	virtual void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();
};
