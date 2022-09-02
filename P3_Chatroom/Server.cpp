#include <iostream>
#include <sstream>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <map>

#define SERVER_IP "0.0.0.0"		// ����IP
#define SERVER_PORT 54000		// �����˿�

using namespace std;

int init(sockaddr_in& hint) {
    // 1. ���������׽���
    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == -1) {
        return -1;
    }

    // 2. ����һ���ṹ�壬�������IP�Ͷ˿���Ϣ
    hint.sin_family = AF_INET;  // ipv4
    hint.sin_port = htons(SERVER_PORT);   // ���ڵ�ַ�Ͷ˿ڰ�װ�����ֽڴ���洢����Ҫ����htonsת��
    inet_pton(AF_INET, SERVER_IP, &hint.sin_addr);  // ��IP��ַת��Ϊ2������ʽ,����hint.sin_addr

    // 3. �� socket �� IP / port ���а�
    int bindRes = bind(listenSock, (sockaddr*)&hint, sizeof(hint));
    if (bindRes == -1) {
        return -2;
    }

    // 4. ����socket��Ϊ����״̬
    if (listen(listenSock, SOMAXCONN) == -1) {
        return -3;
    }

    return listenSock;
}


int main() {
    sockaddr_in hint;   // ����IP/port��Ϣ

    int listenSock = init(hint);
    if (listenSock < 0) {
        cerr << "Init failed, code: " << listenSock << endl;
        return -1;  // ��ʼ��ʧ��
    }

    // 5. �����׽��ֹ���

    // ����һ���ļ����������ϣ�������е�socket������ʼ��
    fd_set master;
    FD_ZERO(&master);

    FD_SET(listenSock, &master);    // ������sock���뼯�ϣ������Ƿ����µ����Ӽ���

    int maxFd = listenSock; // ����ǰ��listenSock��FD��Ϊ����FD

    // �ļ�����������0,�����жϸ������Ƿ��һ�η�����Ϣ
    map<int, int> newFdMap;

    map<int, string> newFdName; //ÿ���ͻ����ǳ�

    char host[NI_MAXHOST];  // ����ͻ��˵�����
    char serv[NI_MAXSERV];  // ����ͻ������ӵĶ˿ں�


    char buf[4096]; // �Ѿ��������������Ϣ�������洢��Ϣ

    bool running = true;

    string neckName;    // �ͻ��ǳ�

    while (running) {
        // ����fd_set����Ϊselect���Դfd_setֱ�ӽ����޸ģ������޷�����
        fd_set masterCopy = master;

        // ����Ƿ���socket���ڴ���״̬
        int socketCount = select(maxFd + 1, &masterCopy, nullptr, nullptr, nullptr);

        // �������ӵ���,����������
        if (FD_ISSET(listenSock, &masterCopy)) {
            sockaddr_in client;
            socklen_t clientSize = sizeof(client);

            int clientSock = accept(listenSock, (sockaddr*)&client, &clientSize);

            if (clientSock == -1) {
                cerr << "Problem with client connecting!";
                return -4;
            }

            memset(host, 0, NI_MAXHOST);
            memset(serv, 0, NI_MAXHOST);

            int res_2 = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, serv, NI_MAXSERV, 0);
            if (res_2 == 0)
            {
                inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
                cout << host << " connected on port " << ntohs(client.sin_port) << endl;
            }
            else {
                cout << host << " connected on port " << serv << endl;
            }

            // �������Ӽ���fd_set��
            FD_SET(clientSock, &master);

            // �������ӵ�fd����map�У������жϸ������Ƿ��һ�η���Ϣ
            newFdMap.insert(pair<int, int>(clientSock, 0));

            // ����maxFd
            maxFd = clientSock > maxFd ? clientSock : maxFd;
        }



        for (int sock = 0; sock < maxFd + 1; ++sock) {
            if (sock != listenSock && FD_ISSET(sock, &masterCopy)) {
                memset(buf, 0, 4096);

                // ������Ϣ
                int byteIn = recv(sock, buf, 4096, 0);
                if (byteIn <= 0) {
                    // ��ʾ�������˳�
                    close(sock);
                    FD_CLR(sock, &master);
                    // �������ӵ�fd��map��ȥ��
                    newFdMap.erase(sock);
                    newFdName.erase(sock);

                    // ���������Ӵ���������˳�����Ϣ
                    for (int outSock = 0; outSock < maxFd + 1; outSock++) {
                        if (outSock != listenSock && outSock != sock) {
                            ostringstream ss;
                            ss << "��" << host << "@" << neckName << "��" << " exit!";
                            string strOut = ss.str();

                            send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                        }
                    }
                }
                else {
                    if (buf[0] == '\\') {
                        string cmd = string(buf, byteIn);
                        cmd.erase(cmd.find_last_not_of(" ") + 1);
                        if (cmd == "\\quit") {
                            running = false;    // ��ʾ�жϷ�����
                            break;
                        }

                        // δ֪��ָ��
                        continue;
                    }
                    if (newFdMap[sock] == 0) {  // ��ʾ���Ǹ����ӷ��͵ĵ�һ����Ϣ�����ǳ�
                        newFdName.insert(pair<int, string>(sock, buf));

                        for (int outSock = 0; outSock < maxFd + 1; outSock++) {
                            if (outSock != listenSock) {
                                ostringstream ss;
                                ss << "��" << host << "@" << newFdName[sock] << "��" << " enter the chat room!";
                                string strOut = ss.str();

                                send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                            }
                        }
                        newFdMap[sock] ++;  // ����

                        continue;
                    }

                    // Send message to other clients, and definiately NOT the listening socket
                    for (int outSock = 0; outSock < maxFd + 1; outSock++) {
                        if (outSock != listenSock && outSock != sock) {
                            ostringstream ss;
                            ss << "��" << host << "@" << newFdName[sock] << "��" << " " << buf;
                            string strOut = ss.str();

                            send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                        }
                    }

                }
            }
        }
    }

    // Remove the listening socket from the master file descriptor set and close it
    // to prevent anyone else trying to connect.
    FD_CLR(listenSock, &master);
    close(listenSock);

    // Message to let users know what's happening.
    string msg = "Server is shutting down. Goodbye\r\n";

    // Get the socket number
    for (int sock = 0; sock < maxFd + 1; sock++) {
        if (FD_ISSET(sock, &master) && sock != listenSock) {
            send(sock, msg.c_str(), msg.size() + 1, 0);

            // Remove it from the master file list and close the socket
            FD_CLR(sock, &master);
            close(sock);
        }
    }

    return 0;
}