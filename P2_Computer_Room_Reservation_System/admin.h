#pragma once

#include<iostream>
#include<fstream>
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
};
