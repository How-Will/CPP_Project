#include"teacher.h"


// 默认构造
Teacher::Teacher() {

}

// 有参构造	(职工编号， 姓名， 密码)
Teacher::Teacher(int empid, string name, string pwd) {
	this->m_empid = empid;
	this->m_name = name;
	this->m_pwd = pwd;
}

// 菜单界面
void Teacher::operMenu() {
	cout << "============  欢迎教师: " << this->m_name << "登录!  ============\n";
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.查看所有预约    | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.审核预约        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.注销登录        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "请输入您的选择: ";
}

// 查看所有预约
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_order_data.size(); i++) {
		cout << i + 1 << "、 ";

		cout << "预约日期:周" << of.m_order_data[i]["date"] << " ";
		cout << "时段:" << (of.m_order_data[i]["interval"] == "1" ? "上午" : "下午") << " ";
		cout << "学号:" << of.m_order_data[i]["stuId"] << " ";
		cout << "姓名:" << of.m_order_data[i]["stuName"] << " ";
		cout << "机房:" << of.m_order_data[i]["roomId"] << " ";

		string status = "状态:";
		// 1. 审核中 2. 已预约 -1. 预约失败  0. 取消预约
		if (of.m_order_data[i]["status"] == "1")
			status += "审核中";
		else if (of.m_order_data[i]["status"] == "2")
			status += "预约成功";
		else if (of.m_order_data[i]["status"] == "-1")
			status += "预约失败，审核未通过";
		else
			status += "预约已取消";
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

// 审核预约
void Teacher::validOrder() {
	OrderFile of;	
	if (of.m_size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}


	vector<int> v;
	int index = 0;
	cout << "待审核的预约记录如下: " << endl;
	for (int i = 0; i < of.m_order_data.size(); i++) {
		// 查找处于审核中的预约记录
		if (of.m_order_data[i]["status"] == "1") {
			v.push_back(i);
			cout << ++index << "、 ";
			
			cout << "预约日期:周" << of.m_order_data[i]["date"] << " ";
			cout << "时段:" << (of.m_order_data[i]["interval"] == "1" ? "上午" : "下午") << " ";
			cout << "学号:" << of.m_order_data[i]["stuId"] << " ";
			cout << "机房:" << of.m_order_data[i]["roomId"] << " ";
			cout << "状态:审核中" << endl;
		}
	}

	cout << "请输入审核的预约记录，0代表返回" << endl;
	int user_key = 0;	//接收用户选择的预约记录
	int ret = 0;	// 接受预约结果

	while (1) {
		cin >> user_key;
		if (user_key >= 0 && user_key <= v.size()) {
			if (user_key == 0)
				break;
			else {
				cout << "请输入审核的结果" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;
				if (ret == 1) {
					of.m_order_data[v[user_key - 1]]["status"] = "2";
				}
				else {
					of.m_order_data[v[user_key - 1]]["status"] = "-1";
				}
				of.updateOrder();	//更新预约记录
				cout << "审核完毕" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入!" << endl;
	}

	system("pause");
	system("cls");
}