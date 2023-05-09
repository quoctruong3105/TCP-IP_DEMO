#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main() {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        return 1;
    }

    // Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipAddress = "127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(sockaddr_in));
    if(connectRes == -1) {
        return 1;
    }


    char buf[4096];
    string userInput;

    do {
        cout << "> ";
        getline(cin, userInput);
        // Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if(sendRes == -1) {
            cout << "Could not send to server" << endl;
            continue;
        }
        // Wait for response
        memset(buf, 0, 4096);
        int bytesReceive = recv(sock, buf, 4096, 0);
        // Display respond
        cout << "SERVER> " << string(buf, bytesReceive) << endl;
    } while(true);


    // Close the socket
    close(sock);

    return 0;
}
