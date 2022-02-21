#include<iostream>
#include<fstream>
#include<string>
#include"student.h"
#include"teacher.h"
#include"admin.h"
#include"globalFile.h"
#include"identity.h"

using namespace std;


// 进入管理员子菜单界面
void adminMenu(Identity* &ident) {
	while (1) {
		// 管理员菜单显示
		ident->operMenu();	// 多态的体现

		// 将父类指针强转为子类指针，以使用子类的功能
		Admin* admin = (Admin*)ident;

		int admin_key = 0;	// 接受用户的选择
		cin >> admin_key;

		switch (admin_key)
		{
		case 1:
			//cout << "添加账号" << endl;
			admin->addPerson();
			break;
		case 2:
			//cout << "查看账号" << endl;
			admin->showPerson();
			break;
		case 3:
			//cout << "查看机房" << endl;
			admin->showComputer();
			break;
		case 4:
			//cout << "清空预约" << endl;
			admin->cleanFile();
			break;
		case 0:
			delete ident;	// 销毁掉堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;	// return 会退出整个函数
		default:
			cout << "输入不合法，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// 登录函数 （操作文件名， 操作身份类型）
void loginIn(string filename, int type) {
	// 父类指针，用于指向子类对象
	Identity* person = nullptr;

	// 读文件
	ifstream ifs(filename, ifstream::in);

	// 判断文件是否存在
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	// 准备接受用户信息
	int id = 0;
	string name;
	string pwd;

	// 判断身份
	if (type == 1) {
		cout << "请输入你的学号: ";
		cin >> id;
	}
	else if (type == 2) {
		cout << "请输入你的职工号: ";
		cin >> id;
	}

	cout << "请输入用户名：";
	cin >> name;
	cout << "请输入密码： ";
	cin >> pwd;


	int f_id;	// 从文件中获取的id
	string f_name;	// 从文件中获取的姓名
	string f_pwd;	// 从文件中获取密码

	if (type == 1) {	// 学生身份验证
		while (ifs >> f_id >> f_name >> f_pwd) {
			// 和用户输入信息做对比
			if (f_id == id && f_name == name && f_pwd == pwd) {
				cout << "学生验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);
				// 进入学生身份的主菜单

				return;
			}
		}
	}
	else if (type == 2) {
		while (ifs >> f_id >> f_name >> f_pwd) {
			if (f_id == id && f_name == name && f_pwd == pwd) {
				cout << "教师验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				// 进入教师身份的主菜单
				 
				return;
			}
		}
	}
	else if (type == 3) {
		while (ifs >> f_name >> f_pwd) {
			if (f_name == name && f_pwd == pwd) {
				cout << "管理员验证登录成功" << endl;
				system("cls");

				person = new Admin(name, pwd);
				// 进入管理员菜单界面
				adminMenu(person);

				return;
			}
		}
	}

	cout << "验证登录失败!" << endl;
	system("pause");
	system("cls");
}

// 搭建界面
void menuFunc() {
	cout << "============  欢迎使用机房预约系统  ============\n";
	cout << endl << "请输入您的身份" << endl;
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.学生代表        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.老    师        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        3.管 理 员        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.退    出        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "请输入您的选择: ";
}

// 交互函数
void keyDown() {

	int user_key = 0;	//用户的选择
	cin >> user_key;

	switch (user_key)
	{
	case 1:		// 学生身份
		loginIn(STUDENT_FILE, 1);
		break;
	case 2:		// 老师身份
		loginIn(TEACHER_FILE, 2);
		break;
	case 3:		// 管理员身份
		loginIn(ADMIN_FILE, 3);
		break;
	case 0:		// 退出系统
		cout << "欢迎下一次使用...." << endl;
		exit(0);
		break;
	default:
		cout << "输入不合法，请重新选择! " << endl;
		system("pause");
		system("cls");
		break;
	}
}


int main() {
	
	while (1) {
		menuFunc();	//显示界面
		keyDown();
	}

	return 0;
}