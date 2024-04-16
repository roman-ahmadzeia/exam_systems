#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include <pthread.h>

struct EmailDetails
{
	char * from;
	char * to;
	char * subject;
	char * body;
};

struct Email
{
	char *userName;
    struct EmailDetails details;
};

void populateData(struct Email *emails)
{
    // Email 1
    emails[0].userName = "JobsS";
    emails[0].details.from = "Bill";
    emails[0].details.to = "Jobs";
    emails[0].details.subject = "Finance Presentation";
    emails[0].details.body = "Looking forward to our meeting on finance";

    // Email 2
    emails[1].userName = "BillG";
    emails[1].details.from = "Warren";
    emails[1].details.to = "Bill";
    emails[1].details.subject = "Dinner";
    emails[1].details.body = "It was lovely meeting you over dinner meeting";

    // Email 3
    emails[2].userName = "WarrenB";
    emails[2].details.from = "Elon";
    emails[2].details.to = "Warren";
    emails[2].details.subject = "SpaceX";
    emails[2].details.body = "How's new SpaceX project going?";

    // Email 4
    emails[3].userName = "JobsS";
    emails[3].details.from = "Elon";
    emails[3].details.to = "Jobs";
    emails[3].details.subject = "Twitter";
    emails[3].details.body = "How is it going at Twitter?";
}

char* searchEmails(struct Email *emails, char *username)
{
	char details[1024];

    // Mandatory Method to fill in
    // searches for emails for a user name and returns in the form a char *
    for (int i = 0; i < sizeof(emails); i++)
    {
    	if (emails[i].userName = username)
    	{
    		snprintf(details, sizeof(details), "To: %s\n From: %s\n Subject: %s\n Body: %s\n ****************\n", emails[i].from, emails[i].to, emails[i].subject, emails[i].body);
    	}
    }

    return details;

}

pthread_mutex_t mutex;
sem_t sem;

void* manage_clients(void* arg) {
    int client_socket = *((int*)arg);

    char username[1024];
    recv(client_socket, username, strlen(username), 0);
    char details[1024] = searchEmails(&emails, username);
    send(client_socket, details, strlen(details), 0);


    sleep(1);
    sem_post(&sem);
    close(client_socket);
    return NULL;
}



int main() {

    int serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == 0)
	{
		printf("Error creating server socket\n");
	}
	else
	{
		printf("Server Socket created\n");
	}

	struct sockaddr_in svrAddress;
	svrAddress.sin_family = AF_INET;
	svrAddress.sin_addr.s_addr = INADDR_ANY; 
	svrAddress.sin_port =  htons(27000); 

	int lenAddress = sizeof(svrAddress);

	int bindResult = bind(serverSocket, (struct sockaddr *)&svrAddress, lenAddress);

	if (bindResult < 0)
	{
		printf("Error binding socket\n");
	}
	else
	{
		printf("Socket bound successfully\n");
	}

	int listenResult = listen(serverSocket, 1);
	if (listenResult < 0)
	{
		printf("Error listening to server socket\n");
	}
	else
	{
		printf("Listening to the socket\n");
	}

	int clientSocket;
	while (1) {
        client_len = sizeof(clientSocket);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientSocket, &client_len);
        if (clientSocket < 0) {
            perror("Error accepting connection");
            exit(1);
        }

        sem_wait(&sem);

        pthread_mutex_lock(&mutex);
        if (pthread_create(&threads[thread_args[0]], NULL, manage_clients, &clientSocket) != 0) {
            perror("Error creating thread");
            exit(1);
        }
        thread_args[0]++;
        pthread_mutex_unlock(&mutex);
    }

    close(serverSocket);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);

    return 0;
}




// Client side

int main() 
{
    int client_socket;
    struct sockaddr_in server_addr;
   
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket Created\n";)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connection Established\n");


    char username[1024];
    printf("Enter Username: ");
    scanf("%s", username);
    if (send(client_socket, username, strlen(name), 0) == -1)
    {
    	return perror("Unable to send username to server");
    }
    printf("Username sent to server\n");
    printf("\n************************\n");

    char emails[1024];
    recv(client_socket, emails, strlen(emails), 0);
    printf("%s", emails);


    close(client_socket);
    return 0;

}

