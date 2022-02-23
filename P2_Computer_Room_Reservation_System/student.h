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


// 学生类
class Student : public Identity {
public:
	//默认构造函数
	Student();

	//有参构造函数  参数：学号，姓名，密码
	Student(int id, string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	//学生学号
	int m_id;	

	// 初始化容器函数
	void initVector();

	// 机房容器
	vector<ComputerRoom> v_com;
};