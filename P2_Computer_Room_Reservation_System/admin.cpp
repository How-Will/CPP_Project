#include"admin.h"

//默认构造
Admin::Admin() {

}

//有参构造 （管理员姓名， 密码）
Admin::Admin(string name, string pwd) {
	this->m_name = name;
	this->m_pwd = pwd;

	// 初始化容器，获取到所有文件中学生，老师信息
	initVector();
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
	string error_tip;
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
			error_tip = "学号重复，请重新输入";
			break;
		}
		else if (user_key == 2) {
			tip = "请输入职工编号: ";
			file_name = TEACHER_FILE;
			error_tip = "职工编号重复，请重新输入";
			break;
		}
		else {
			cout << "输入不合法，请重新输入" << endl;
			system("pause");
			cout << endl;
		}
	}

	ofs.open(file_name, fstream::out | fstream::app);	// 绑定对应的文件
	int id;
	string name;
	string pwd;

	cout << tip;
	while (1) {
		cin >> id;
		bool res = checkReapeat(id, user_key);

		if (!res)
			break;
		else 
			cout << error_tip << endl;
	}
	
	cout << "请输入姓名: ";
	cin >> name;
	cout << "请输入密码: ";
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;
	

	system("pause");
	system("cls");

	ofs.close();

	// 调用初始化容器接口，重新获取文件中的数据，解决不及时更新的bug
	this->initVector();
}

//初始化容器函数
void Admin::initVector() {
	this->v_stu.clear();
	this->v_tea.clear();	// 先将容器清空

	ifstream ifs(STUDENT_FILE, fstream::in);
	if (!ifs.is_open()) {
		cout << "student.txt读取失败" << endl;
		return;
	}

	// 读取学生文件中的信息存入v_stu中
	Student stu;
	while (ifs >> stu.m_id >> stu.m_name >> stu.m_pwd) {
		v_stu.push_back(stu);	
	}
	cout << "当前学生数量为: " << v_stu.size() << endl;
	ifs.close();

	// 读取教师文件中的信息存入v_tea中
	ifs.open(TEACHER_FILE, fstream::in);
	if (!ifs.is_open()) {
		cout << "teacher.txt读取失败" << endl;
		return;
	}

	Teacher tea;
	while (ifs >> tea.m_empid >> tea.m_name >> tea.m_pwd) {
		v_tea.push_back(tea);
	}
	cout << "当前教师数量为: " << v_tea.size() << endl;
	ifs.close();

	// 读取机房文件中的信息存入v_com中
	ifs.open(COMPUTER_FILE, fstream::in);
	if (!ifs.is_open()) {
		cout << "computerRoom.txt读取失败" << endl;
		return;
	}

	ComputerRoom com;
	while (ifs >> com.m_com_id >> com.m_max_num) {
		v_com.push_back(com);
	}
	cout << "当前的机房数量为: " << v_com.size() << endl;
	ifs.close();
}

// 检查重复函数
bool Admin::checkReapeat(int id, int type) {
	if (type == 1) {	// 检查学生id是否重复
		for (auto e : v_stu) {
			if (id == e.m_id)
				return true;
		}
	}
	else if (type == 2) {	// 检查教师职工编号是否重复
		for (auto e : v_tea) {
			if (id == e.m_empid) 
				return true;
		}
	}
	return false;
}

void printStudent(const Student& s) {
	cout << "学号: " << s.m_id << " 姓名: " << s.m_name << " 密码: " << s.m_pwd << endl;
}

void printTeacher(const Teacher& t) {
	cout << "职工编号: " << t.m_empid << " 姓名: " << t.m_name << " 密码: " << t.m_pwd << endl;
}

//查看账号
void Admin::showPerson() {
	cout << "请选择要查看的内容\n";
	cout << "1. 查看所有学生\n";
	cout << "2. 查看所有老师\n";
	cout << "请输入你的选择: ";

	int user_key = 0;
	cin >> user_key;

	switch (user_key)
	{
	case 1:	// 查看学生信息
		cout << "所有学生信息如下: " << endl;
		for_each(v_stu.cbegin(), v_stu.cend(), printStudent);
		break;
	case 2:	// 查看老师信息
		cout << "所有教师信息如下: " << endl;
		for_each(v_tea.cbegin(), v_tea.cend(), printTeacher);
		break;
	default:
		cout << "非法输入，返回上一单元" << endl;
		break;
	}

	system("pause");
	system("cls");
}

//查看机房信息
void Admin::showComputer() {
	cout << "机房信息如下: " << endl;
	for (auto e : v_com) {
		cout << "机房编号: " << e.m_com_id << " 机房最大容量: " << e.m_max_num << endl;
	}

	system("pause");
	system("cls");
}


//清空预约记录
void Admin::cleanFile() {
	cout << "清空文件后不可恢复，请确认(y/n): ";
	string user_key;
	cin >> user_key;

	if (user_key == "y") {
		ofstream ofs(ORDER_FILE, fstream::trunc);
		ofs.close();
		cout << "清空成功!" << endl;
	}
	else{
		cout << "返回上一单元" << endl;
	}
	
	system("pause");
	system("cls");
}