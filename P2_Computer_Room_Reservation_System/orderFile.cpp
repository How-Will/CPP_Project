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

// ���캯��
OrderFile::OrderFile() {
	// ���ڣ�ʱ��Σ�ѧ����ţ�ѧ��������������ţ�ԤԼ״̬
	string date, interval, stu_id, stu_name, room_id, status;

	this->m_size = 0;	// ԤԼ��¼����

	ifstream ifs(ORDER_FILE, fstream::in);
	while (ifs >> date >> interval >> stu_id >> stu_name >> room_id >> status) {

		string key, value;	// ��ֵ��
		map<string, string> m;

		m.insert(splitFunc(date, ":"));		// ��ȡ����
		m.insert(splitFunc(interval, ":"));	// ��ȡʱ���
		m.insert(splitFunc(stu_id, ":"));	// ��ȡѧ�����
		m.insert(splitFunc(stu_name, ":"));	// ��ȡѧ������
		m.insert(splitFunc(room_id, ":"));	// ��ȡ�������
		m.insert(splitFunc(status, ":"));	// ��ȡԤԼ״̬

		// ��Сmap�������뵽���map������
		this->m_order_data.insert(make_pair(this->m_size, m));
		this->m_size++;
	}

	ifs.close();

	// �������map����
	//for (auto it = m_order_data.cbegin(); it != m_order_data.cend(); it++) {
	//	cout << " key = " << it->first << " value = " << endl;
	//	for (auto mit = it->second.begin(); mit != it->second.end(); mit++) {
	//		cout << " key = " << mit->first << " value = " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

// ����ԤԼ��¼
void OrderFile::updateOrder() {
	if (this->m_size == 0) {
		return;	//ԤԼ��¼Ϊ0����ֱ��return
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