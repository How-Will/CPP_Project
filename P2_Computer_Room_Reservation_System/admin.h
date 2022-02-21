#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<numeric>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"
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

	//��ʼ����������
	void initVector();

	// ����ظ� ������������id, �������ͣ�
	bool checkReapeat(int id, int type);

	// ����������������ڶ�ȡ�ļ�����Ϣ������ȥ�ز���
	vector<Student> v_stu;
	vector<Teacher> v_tea;

	// ��������
	vector<ComputerRoom> v_com;
};
