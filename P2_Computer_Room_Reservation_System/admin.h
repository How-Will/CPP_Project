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
	//默认构造
	Admin();

	//有参构造 （管理员姓名， 密码）
	Admin(string name, string pwd);

	//选择菜单
	virtual void operMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//初始化容器函数
	void initVector();

	// 检测重复 参数：（传入id, 传入类型）
	bool checkReapeat(int id, int type);

	// 添加两个容器，用于读取文件中信息，进行去重操作
	vector<Student> v_stu;
	vector<Teacher> v_tea;

	// 机房容器
	vector<ComputerRoom> v_com;
};
