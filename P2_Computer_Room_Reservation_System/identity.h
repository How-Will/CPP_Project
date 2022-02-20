#pragma once

#include <iostream>

using namespace std;

// 身份的抽象基类
class Identity {
public:
	// 每个子类都有个子菜单功能，将其设置为纯虚函数
	virtual void operMenu() = 0;

	string m_name;	//用户名
	string m_pwd;	// 密码
};