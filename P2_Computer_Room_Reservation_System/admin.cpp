#include"admin.h"

//默认构造
Admin::Admin() {

}

//有参构造 （管理员姓名， 密码）
Admin::Admin(string name, string pwd) {
	this->m_name = name;
	this->m_pwd = pwd;
}

//选择菜单
void Admin::operMenu() {
	cout << "============  欢迎管理员: " << this->m_name << "登录!  ============\n";
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.添加账号        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.查看账号        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        3.查看机房        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        4.清空预约        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.注销登录        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "请输入您的选择: ";
}

//添加账号
void Admin::addPerson() {
	string file_name;
	string tip;
	ofstream ofs;
	int user_key = 0;	// 接收用户的选择

	while (1) {
		cout << "添加账号的类型\n";
		cout << "1. 添加学生" << endl;
		cout << "2. 添加老师" << endl;
		cout << "请输入你的选择: ";

		cin >> user_key;

		if (user_key == 1) {
			tip = "请输入学号: ";
			file_name = STUDENT_FILE;
			break;
		}
		else if (user_key == 2) {
			tip = "请输入职工编号: ";
			file_name = TEACHER_FILE;
			break;
		}
		else {
			cout << "输入不合法，请重新输入";
			system("pause");
			system("cls");
		}
	}

	ofs.open(file_name, fstream::out | fstream::app);	// 绑定对应的文件
	int id;
	string name;
	string pwd;

	cout << tip;
	cin >> id;
	cout << "请输入姓名: ";
	cin >> name;
	cout << "请输入密码: ";
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close();
}

//查看账号
void Admin::showPerson() {

}

//查看机房信息
void Admin::showComputer() {

}

//清空预约记录
void Admin::cleanFile() {

}