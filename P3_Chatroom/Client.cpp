#include <stdio.h> 
#include <string>
#include <conio.h>

#include <winsock2.h> 
#pragma comment (lib, "WS2_32.lib") 


#define SERVER_IP "192.168.1.140" 
#define SERVER_PORT 54000 

using namespace std;

SOCKET serverSocket;	// 网络套接字
sockaddr_in addr;		// 服务器地址

char line1[111]; // 一行分割线
char line2[111];	// 一行空白字符串

HANDLE hMutex;	// 互斥锁

void GBKToUTF8(string& strGBK) {
	int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	wchar_t* wszUtf8 = new wchar_t[len];
	memset(wszUtf8, 0, len);
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wszUtf8, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char* szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);
	strGBK = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
}

string UTF8ToGBK(const char* strUTF8) {
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK)
		delete[] wszGBK;
	if (szGBK)
		delete[] szGBK;
	return strTemp;
}

// 登录函数
void login(char* neckName, int len) {
	system("mode con lines=36 cols=110");
	printf("Welcome to ChatRoom \n\n");
	printf("Input your neckname: ");
	scanf_s("%s", neckName, len);

	while (getchar() != '\n');	// 清除最后一个的换行符

	// Win GBK ——> Linux UTF8，防止乱码
	string name = neckName;
	GBKToUTF8(name);
	send(serverSocket, name.c_str(), strlen(name.c_str()) + 1, 0);
}

int init() {
	// 1. windows 网络服务的初始化 
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (ret != 0) {
		printf("Init environment failed!\r\n");
		return -1;
	}


	// 2. 创建网络套接字 
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == -1) {
		printf("Can't create a socket!\r\n");
		return -2;
	}

	// 3. 创建一个结构体，保存服务器IP/port
	addr.sin_family = AF_INET;	// ipv4
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);


	// 初始化互斥锁
	hMutex = CreateMutex(0, 0, L"console");	// 对窗口光标上锁，防止输入，输出抢夺光标


	return 1;
}

void gotoxy(int x, int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	// 当前输出的句柄
	COORD pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}

void uiInit() {
	system("mode con lines=36, cols=110");
	system("cls");
	gotoxy(0, 33);

	for (int i = 0; i < 110; i++) {
		line1[i] = '-';
		line2[i] = ' ';
	}
	line1[110] = 0;
	line2[110] = 0;

	printf("%s\n", line1);		// 打印输入输出区域分割线
}


void printMsg(const char* msg) {
	// 上锁
	WaitForSingleObject(hMutex, INFINITE);	// 持续等待

	static POINT pos = { 0, 0 };	// 移动输出光标位置
	gotoxy(pos.x, pos.y);
	//printf("%s\n", msg);

	// 彩色字体显示
	static int color = 31;
	printf("\033[0;%d;40m%s\033[0m\n", color++, msg);
	if (color > 36) {
		color = 31;
	}

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hOut, &info);
	pos.x = info.dwCursorPosition.X;	// 保存光标位置，用于下次输出
	pos.y = info.dwCursorPosition.Y;

	// 实现滚动效果
	if (pos.y >= 33) {
		printf("%s\n", line2);
		printf("\n\n");
		gotoxy(0, 33);
		printf("%s\n", line1);

		pos.y -= 1;
	}

	// 将光标返回底部
	gotoxy(1, 34);

	// 释放锁
	ReleaseMutex(hMutex);
}

DWORD WINAPI threadRecv(LPVOID pram) {
	// 接收信息
	char buff[4096];
	while (1) {
		int recRet = recv(serverSocket, buff, sizeof(buff), 0);
		if (recRet <= 0) {
			printf("Oops! something wrong in server!");
			break;
		}

		// 打印信息
		printMsg(UTF8ToGBK(buff).c_str());	// Linux UTF8——> Win GBK
	}

	return 0;
}

// 字符打印
void editPrint(int col, char ch) {
	// 上锁
	WaitForSingleObject(hMutex, INFINITE);

	gotoxy(col, 34);
	printf("%c", ch);

	// 解锁
	ReleaseMutex(hMutex);
}

void editPrint(int col, const char* str) {
	// 上锁
	WaitForSingleObject(hMutex, INFINITE);

	gotoxy(col, 34);
	printf("%s", str);

	// 解锁
	ReleaseMutex(hMutex);
}

// 判断字符是中文还是英文
bool isChinese(char str[], int index) {
	// 一个汉字 两个字节，第一个字节 < 0, 第二个字节 不确定
	// 一个英文 一个字节，都是>0
	int i = 0;
	while (i < index) {
		if (str[i] > 0) {
			i++;
		}
		else {
			i += 2;
		}

		return i > index;
	}
}

int main() {


	if (init() != 1) {
		printf("Init failed!\r\n");
		return -4;
	}



	// 4. 向服务器发起连接
	int conRes = connect(serverSocket, (sockaddr*)&addr, sizeof(addr));
	if (conRes == -1) {
		printf("Can't connect to server!\r\n");
		return -3;
	}

	// 5. 登录到聊天室
	char neckName[256];
	memset(neckName, 0, 256);

	login(neckName, 256);

	// 6. 界面初始化
	uiInit();

	// 7. 信息接收
	// 多线程：一个线程用于输入信息，一个线程用于接收显示信息
	HANDLE hThread = CreateThread(0, 0, threadRecv, 0, 0, 0);
	CloseHandle(hThread);	// 关闭无用的句柄

	// 8. 信息输入
	while (1) {
		editPrint(0, '>');

		int len = 0;
		char buff[1024];	// 存储用户输入字符串
		memset(buff, 0, sizeof(buff));
		while (1) {
			if (_kbhit()) {	// 有按键的时候，才输入，防止阻塞
				char c = getch();	// getch() 相比与 getchar() 不用按回车，即可读取
				if (c == '\r') {	// 按下回车键，跳出循环
					break;
				}
				else if (c == 8) {	// 按下退格键，ASCII是8
					if (len == 0) {	// 字符串长度为0，不能再退
						continue;
					}
					if (isChinese(buff, len - 1)) {
						editPrint(len + 1, "\b\b  \b\b");	// 删除汉字
						buff[len - 1] = 0;
						buff[len - 2] = 0;
						len -= 2;
					}
					else {
						editPrint(len + 1, "\b \b");	// 删除英文
						buff[len - 1] = 0;
						len -= 1;
					}

					continue;
				}

				// 中文，按多次按键，但是打印出来的东西不一样
				// 连续直接读，直到没有输入位置。解决中文输入，显示乱码问题
				WaitForSingleObject(hMutex, INFINITE);

				do {
					printf("%c", c);
					buff[len++] = c;
				} while (_kbhit() && (c = getch()));

				ReleaseMutex(hMutex);

				//editPrint(len + 1, c);
				//buff[len++] = c;
			}
		}

		if (len == 0) {
			continue;
		}

		// 清空编辑区的信息
		char buff2[1024];
		sprintf_s(buff2, sizeof(buff2), "%s\n", line2);
		editPrint(0, buff2);

		// 在聊天窗口输出自己的话
		sprintf_s(buff2, sizeof(buff2), "【Localhost@%s】 %s", neckName, buff);
		printMsg(buff2);

		// 向服务器发送输入的信息
		send(serverSocket, buff, strlen(buff) + 1, 0);
	}

	getchar();
	return 0;
}