#include <stdio.h> 
#include <string>
#include <conio.h>

#include <winsock2.h> 
#pragma comment (lib, "WS2_32.lib") 


#define SERVER_IP "192.168.1.140" 
#define SERVER_PORT 54000 

using namespace std;

SOCKET serverSocket;	// �����׽���
sockaddr_in addr;		// ��������ַ

char line1[111]; // һ�зָ���
char line2[111];	// һ�пհ��ַ���

HANDLE hMutex;	// ������

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

// ��¼����
void login(char* neckName, int len) {
	system("mode con lines=36 cols=110");
	printf("Welcome to ChatRoom \n\n");
	printf("Input your neckname: ");
	scanf_s("%s", neckName, len);

	while (getchar() != '\n');	// ������һ���Ļ��з�

	// Win GBK ����> Linux UTF8����ֹ����
	string name = neckName;
	GBKToUTF8(name);
	send(serverSocket, name.c_str(), strlen(name.c_str()) + 1, 0);
}

int init() {
	// 1. windows �������ĳ�ʼ�� 
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (ret != 0) {
		printf("Init environment failed!\r\n");
		return -1;
	}


	// 2. ���������׽��� 
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == -1) {
		printf("Can't create a socket!\r\n");
		return -2;
	}

	// 3. ����һ���ṹ�壬���������IP/port
	addr.sin_family = AF_INET;	// ipv4
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);


	// ��ʼ��������
	hMutex = CreateMutex(0, 0, L"console");	// �Դ��ڹ����������ֹ���룬���������


	return 1;
}

void gotoxy(int x, int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	// ��ǰ����ľ��
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

	printf("%s\n", line1);		// ��ӡ�����������ָ���
}


void printMsg(const char* msg) {
	// ����
	WaitForSingleObject(hMutex, INFINITE);	// �����ȴ�

	static POINT pos = { 0, 0 };	// �ƶ�������λ��
	gotoxy(pos.x, pos.y);
	//printf("%s\n", msg);

	// ��ɫ������ʾ
	static int color = 31;
	printf("\033[0;%d;40m%s\033[0m\n", color++, msg);
	if (color > 36) {
		color = 31;
	}

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hOut, &info);
	pos.x = info.dwCursorPosition.X;	// ������λ�ã������´����
	pos.y = info.dwCursorPosition.Y;

	// ʵ�ֹ���Ч��
	if (pos.y >= 33) {
		printf("%s\n", line2);
		printf("\n\n");
		gotoxy(0, 33);
		printf("%s\n", line1);

		pos.y -= 1;
	}

	// ����귵�صײ�
	gotoxy(1, 34);

	// �ͷ���
	ReleaseMutex(hMutex);
}

DWORD WINAPI threadRecv(LPVOID pram) {
	// ������Ϣ
	char buff[4096];
	while (1) {
		int recRet = recv(serverSocket, buff, sizeof(buff), 0);
		if (recRet <= 0) {
			printf("Oops! something wrong in server!");
			break;
		}

		// ��ӡ��Ϣ
		printMsg(UTF8ToGBK(buff).c_str());	// Linux UTF8����> Win GBK
	}

	return 0;
}

// �ַ���ӡ
void editPrint(int col, char ch) {
	// ����
	WaitForSingleObject(hMutex, INFINITE);

	gotoxy(col, 34);
	printf("%c", ch);

	// ����
	ReleaseMutex(hMutex);
}

void editPrint(int col, const char* str) {
	// ����
	WaitForSingleObject(hMutex, INFINITE);

	gotoxy(col, 34);
	printf("%s", str);

	// ����
	ReleaseMutex(hMutex);
}

// �ж��ַ������Ļ���Ӣ��
bool isChinese(char str[], int index) {
	// һ������ �����ֽڣ���һ���ֽ� < 0, �ڶ����ֽ� ��ȷ��
	// һ��Ӣ�� һ���ֽڣ�����>0
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



	// 4. ���������������
	int conRes = connect(serverSocket, (sockaddr*)&addr, sizeof(addr));
	if (conRes == -1) {
		printf("Can't connect to server!\r\n");
		return -3;
	}

	// 5. ��¼��������
	char neckName[256];
	memset(neckName, 0, 256);

	login(neckName, 256);

	// 6. �����ʼ��
	uiInit();

	// 7. ��Ϣ����
	// ���̣߳�һ���߳�����������Ϣ��һ���߳����ڽ�����ʾ��Ϣ
	HANDLE hThread = CreateThread(0, 0, threadRecv, 0, 0, 0);
	CloseHandle(hThread);	// �ر����õľ��

	// 8. ��Ϣ����
	while (1) {
		editPrint(0, '>');

		int len = 0;
		char buff[1024];	// �洢�û������ַ���
		memset(buff, 0, sizeof(buff));
		while (1) {
			if (_kbhit()) {	// �а�����ʱ�򣬲����룬��ֹ����
				char c = getch();	// getch() ����� getchar() ���ð��س������ɶ�ȡ
				if (c == '\r') {	// ���»س���������ѭ��
					break;
				}
				else if (c == 8) {	// �����˸����ASCII��8
					if (len == 0) {	// �ַ�������Ϊ0����������
						continue;
					}
					if (isChinese(buff, len - 1)) {
						editPrint(len + 1, "\b\b  \b\b");	// ɾ������
						buff[len - 1] = 0;
						buff[len - 2] = 0;
						len -= 2;
					}
					else {
						editPrint(len + 1, "\b \b");	// ɾ��Ӣ��
						buff[len - 1] = 0;
						len -= 1;
					}

					continue;
				}

				// ���ģ�����ΰ��������Ǵ�ӡ�����Ķ�����һ��
				// ����ֱ�Ӷ���ֱ��û������λ�á�����������룬��ʾ��������
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

		// ��ձ༭������Ϣ
		char buff2[1024];
		sprintf_s(buff2, sizeof(buff2), "%s\n", line2);
		editPrint(0, buff2);

		// �����촰������Լ��Ļ�
		sprintf_s(buff2, sizeof(buff2), "��Localhost@%s�� %s", neckName, buff);
		printMsg(buff2);

		// ������������������Ϣ
		send(serverSocket, buff, strlen(buff) + 1, 0);
	}

	getchar();
	return 0;
}