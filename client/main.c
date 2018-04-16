#include <sys/socket.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/***
 *  Types of messages:
 *
 *  -Private message: /<user> <msg>
 *  -Issue server command: /<command>
 *  -Broadcast message: .<message>
 *  -...
 */

char *username;

int main()
{
  struct sockaddr_in endpoint;
  memset(&endpoint, 0, sizeof(endpoint));
  endpoint.sin_family = AF_INET;
  endpoint.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  /* localhost, 127.0.0.1 */
  endpoint.sin_port = htons(PORTNUM);

  printf(">> username: ");
  scanf("%s", username);

  int srv_socket = socket(AF_INET, SOCK_STREAM, 0);
  connect(srv_socket, (struct sockaddr *)&endpoint, sizeof(struct sockaddr_in));

  /* verification */

  char *init_msg = malloc((sizeof(char) * strlen(username)) + 1);
  strcpy(init_msg, "I");
  strcat(init_msg, username);

  send(srv_socket, init_msg, strlen(username) + 1, NULL);

  /* -------------- */

  int bytes = recv(srv_socket, )
}