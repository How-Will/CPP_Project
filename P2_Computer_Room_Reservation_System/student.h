#pragma once

#include<iostream>
#include<string>
#include"identity.h"
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
};