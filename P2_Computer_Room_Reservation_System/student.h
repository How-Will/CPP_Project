#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"identity.h"
#include"globalFile.h"
#include"orderFile.h"
#include"computerRoom.h"
using namespace std;


// ѧ����
class Student : public Identity {
public:
	//Ĭ�Ϲ��캯��
	Student();

	//�вι��캯��  ������ѧ�ţ�����������
	Student(int id, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//ѧ��ѧ��
	int m_id;	

	// ��ʼ����������
	void initVector();

	// ��������
	vector<ComputerRoom> v_com;
};