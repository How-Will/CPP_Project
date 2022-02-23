#include "orderFile.h"	

pair<string, string> splitFunc(string& str, const string& token) {
	int pos = str.find(token);

	string key, value;
	if (pos != -1) {
		key = str.substr(0, pos);
		value = str.substr(pos + 1, str.size() - pos - 1);
	}

	return make_pair(key, value);
}

// 构造函数
OrderFile::OrderFile() {
	// 日期，时间段，学生编号，学生姓名，机房编号，预约状态
	string date, interval, stu_id, stu_name, room_id, status;

	this->m_size = 0;	// 预约记录条数

	ifstream ifs(ORDER_FILE, fstream::in);
	while (ifs >> date >> interval >> stu_id >> stu_name >> room_id >> status) {

		string key, value;	// 键值对
		map<string, string> m;

		m.insert(splitFunc(date, ":"));		// 截取日期
		m.insert(splitFunc(interval, ":"));	// 截取时间段
		m.insert(splitFunc(stu_id, ":"));	// 截取学生编号
		m.insert(splitFunc(stu_name, ":"));	// 截取学生姓名
		m.insert(splitFunc(room_id, ":"));	// 截取机房编号
		m.insert(splitFunc(status, ":"));	// 截取预约状态

		// 将小map容器放入到大的map容器中
		this->m_order_data.insert(make_pair(this->m_size, m));
		this->m_size++;
	}

	ifs.close();

	// 测试最大map容器
	//for (auto it = m_order_data.cbegin(); it != m_order_data.cend(); it++) {
	//	cout << " key = " << it->first << " value = " << endl;
	//	for (auto mit = it->second.begin(); mit != it->second.end(); mit++) {
	//		cout << " key = " << mit->first << " value = " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

// 更新预约记录
void OrderFile::updateOrder() {
	if (this->m_size == 0) {
		return;	//预约记录为0条，直接return
	}

	ofstream ofs(ORDER_FILE, fstream::out | fstream::trunc);
	for (int i = 0; i < this->m_size; i++) {
		ofs << "date:" << this->m_order_data[i]["date"] << " ";
		ofs << "interval:" << this->m_order_data[i]["interval"] << " ";
		ofs << "stuId:" << this->m_order_data[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_order_data[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_order_data[i]["roomId"] << " ";
		ofs << "status:" << this->m_order_data[i]["status"] << endl;
	}

	ofs.close();
}