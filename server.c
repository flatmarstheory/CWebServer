#include <winsock2.h>
#include <stdio.h>
#include <string.h>

int main()
{
    printf("Starting server\n");
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;

    // Initialize Winsock
    printf("Initializing Winsock\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("WSAStartup failed. Error code : %d", WSAGetLastError());
        return 1;
    }

    // Create socket
    printf("Creating socket\n");
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    // Prepare the sockaddr_in structure
    printf("Preparing sockaddr_in structure\n");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind
    printf("Binding socket\n");
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }

    // Listen to incoming connections
    printf("Listening to incoming connections\n");
    listen(s, 3);

    // Accept and incoming connection
    printf("Accepting incoming connections\n");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
    {
        printf("Accept failed with error code : %d", WSAGetLastError());
    }

    // Reply to the client
    printf("Replying to the client\n");
    char *response = "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/html\r\n"
                     "Content-Length: 12\r\n"
                     "\r\n"
                     "Hello Client";
    if (send(new_socket, response, strlen(response), 0) == SOCKET_ERROR)
    {
        printf("Send failed with error code : %d", WSAGetLastError());
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
