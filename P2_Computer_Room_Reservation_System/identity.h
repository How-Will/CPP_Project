#pragma once

#include <iostream>

using namespace std;

// ��ݵĳ������
class Identity {
public:
	// ÿ�����඼�и��Ӳ˵����ܣ���������Ϊ���麯��
	virtual void operMenu() = 0;

	string m_name;	//�û���
	string m_pwd;	// ����
};