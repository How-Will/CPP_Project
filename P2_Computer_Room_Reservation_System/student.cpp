#include"student.h"

//默认构造函数
Student::Student() {
	
}

//有参构造函数  参数：学号，姓名，密码
Student::Student(int id, string name, string pwd) {
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;

	// 初始化容器函数
	initVector();
}

//菜单界面
void Student::operMenu() {
	cout << "============  欢迎学生代表: " << this->m_name << "登录!  ============\n";
	cout << "\t\t ---------------------------- \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        1.申请预约        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        2.查看我的预约    | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        3.查看所有预约    | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        4.取消预约        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t |        0.注销登录        | \n";
	cout << "\t\t |                          | \n";
	cout << "\t\t ---------------------------- \n";
	cout << "请输入您的选择: ";
}

//申请预约
void Student::applyOrder() {
	cout << "机房开放时间为周一至周五! " << endl;
	cout << "请输入申请预约的时间: " << endl;
	cout << "1. 周一" << endl;
	cout << "2. 周二" << endl;
	cout << "3. 周三" << endl;
	cout << "4. 周四" << endl;
	cout << "5. 周五" << endl;
	
	//接受用户输入
	int date = 0;	
	int interval = 0;
	int room = 0;

	while (1) {
		cin >> date;
		if (date >= 1 && date <= 5)
			break;
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的时间段: " << endl;
	cout << "1. 上午" << endl;
	cout << "2. 下午" << endl;
	
	while (1) {
		cin >> interval;
		if (interval >= 1 && interval <= 2)
			break;
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请选择机房: " << endl;
	for (int i = 0; i != v_com.size(); i++) {
		cout << v_com[i].m_com_id << "号机房容量: " << v_com[i].m_max_num << endl;
	}
	
	while (1) {
		cin >> room;
		if (room >= 1 && room <= v_com.size())
			break;
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "预约成功！审核中......." << endl;

	ofstream ofs(ORDER_FILE, fstream::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;		// 1 表示审核中

	ofs.close();

	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder() {
	OrderFile orderf;
}

//查看所有预约
void Student::showAllOrder() {

}

//取消预约
void Student::cancelOrder() {

}

//初始化容器函数
void Student::initVector() {
	this->v_com.clear();	// 清空容器

	ifstream ifs(COMPUTER_FILE, ifstream::in);

	ComputerRoom com;	// 接受文件信息
	while (ifs >> com.m_com_id >> com.m_max_num) {
		v_com.push_back(com);
	}

	ifs.close();
}