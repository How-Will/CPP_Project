#pragma once
#include "identity.h"	
#include <iostream>
using namespace std;

class Teacher : public Identity {
public:
	// Ĭ�Ϲ���
	Teacher();

	// �вι���	(ְ����ţ� ������ ����)
	Teacher(int empid, string name, string pwd);

	// �˵�����
	virtual void operMenu();

	// �鿴����ԤԼ
	void showAllOrder();

	// ���ԤԼ
	void validOrder();

	int m_empid;	//��ʦ���
};