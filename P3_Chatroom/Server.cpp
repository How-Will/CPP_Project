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

#define SERVER_IP "0.0.0.0"		// 监听IP
#define SERVER_PORT 54000		// 监听端口

using namespace std;

int init(sockaddr_in& hint) {
    // 1. 创建网络套接字
    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == -1) {
        return -1;
    }

    // 2. 创建一个结构体，保存监听IP和端口信息
    hint.sin_family = AF_INET;  // ipv4
    hint.sin_port = htons(SERVER_PORT);   // 由于地址和端口安装网络字节次序存储，需要调用htons转换
    inet_pton(AF_INET, SERVER_IP, &hint.sin_addr);  // 将IP地址转换为2进制形式,存入hint.sin_addr

    // 3. 将 socket 和 IP / port 进行绑定
    int bindRes = bind(listenSock, (sockaddr*)&hint, sizeof(hint));
    if (bindRes == -1) {
        return -2;
    }

    // 4. 将该socket设为监听状态
    if (listen(listenSock, SOMAXCONN) == -1) {
        return -3;
    }

    return listenSock;
}


int main() {
    sockaddr_in hint;   // 保存IP/port信息

    int listenSock = init(hint);
    if (listenSock < 0) {
        cerr << "Init failed, code: " << listenSock << endl;
        return -1;  // 初始化失败
    }

    // 5. 进行套接字管理

    // 建立一个文件描述符集合，存放所有的socket，并初始化
    fd_set master;
    FD_ZERO(&master);

    FD_SET(listenSock, &master);    // 将监听sock放入集合，监听是否有新的连接加入

    int maxFd = listenSock; // 将当前的listenSock的FD设为最大的FD

    // 文件描述符——0,用于判断该连接是否第一次发送消息
    map<int, int> newFdMap;

    map<int, string> newFdName; //每个客户的昵称

    char host[NI_MAXHOST];  // 保存客户端的名称
    char serv[NI_MAXSERV];  // 保存客户端连接的端口号


    char buf[4096]; // 已经接入的连接有消息传到，存储消息

    bool running = true;

    string neckName;    // 客户昵称

    while (running) {
        // 拷贝fd_set，因为select会对源fd_set直接进行修改，导致无法重用
        fd_set masterCopy = master;

        // 检查是否有socket处于待读状态
        int socketCount = select(maxFd + 1, &masterCopy, nullptr, nullptr, nullptr);

        // 有新连接到来,处理新连接
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

            // 将新连接加入fd_set中
            FD_SET(clientSock, &master);

            // 将新连接的fd加入map中，用于判断该连接是否第一次发消息
            newFdMap.insert(pair<int, int>(clientSock, 0));

            // 更新maxFd
            maxFd = clientSock > maxFd ? clientSock : maxFd;
        }



        for (int sock = 0; sock < maxFd + 1; ++sock) {
            if (sock != listenSock && FD_ISSET(sock, &masterCopy)) {
                memset(buf, 0, 4096);

                // 接收消息
                int byteIn = recv(sock, buf, 4096, 0);
                if (byteIn <= 0) {
                    // 表示该连接退出
                    close(sock);
                    FD_CLR(sock, &master);
                    // 将该连接的fd从map中去除
                    newFdMap.erase(sock);
                    newFdName.erase(sock);

                    // 向其他连接传达该连接退出的消息
                    for (int outSock = 0; outSock < maxFd + 1; outSock++) {
                        if (outSock != listenSock && outSock != sock) {
                            ostringstream ss;
                            ss << "【" << host << "@" << neckName << "】" << " exit!";
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
                            running = false;    // 表示中断服务器
                            break;
                        }

                        // 未知的指令
                        continue;
                    }
                    if (newFdMap[sock] == 0) {  // 表示这是该连接发送的第一条消息，即昵称
                        newFdName.insert(pair<int, string>(sock, buf));

                        for (int outSock = 0; outSock < maxFd + 1; outSock++) {
                            if (outSock != listenSock) {
                                ostringstream ss;
                                ss << "【" << host << "@" << newFdName[sock] << "】" << " enter the chat room!";
                                string strOut = ss.str();

                                send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                            }
                        }
                        newFdMap[sock] ++;  // 增加

                        continue;
                    }

                    // Send message to other clients, and definiately NOT the listening socket
                    for (int outSock = 0; outSock < maxFd + 1; outSock++) {
                        if (outSock != listenSock && outSock != sock) {
                            ostringstream ss;
                            ss << "【" << host << "@" << newFdName[sock] << "】" << " " << buf;
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