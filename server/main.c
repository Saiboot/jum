#include <sys/socket.h>
#include <inttypes.h>
#include <stdlib.h>

/***
 *  Types of messages:
 *  
 *  - A: Normal
 *  - B: Broadcast
 *  - 
 *  - S: Server interaction
 *  - P: Private message
 *  
 *  - I: init
 */


typedef struct {
  int32_t socket;
  struct sockaddr_in client_info;
  char *username;
} clientData_t;

typedef struct {
  char type;
  char *msg;
} msgf_t;

#define MAX_CLIENT_CONNECTIONS 64
#define MAX_NAME_LENGTH 18

int32_t srv_socket;   // server: socket endpoint for clients to connect to
int8_t srv_online;    // server: status
int16_t srv_cons;     // server: connections

client_list_t g_clientList;

/**
 *  [srv_pull_coque: accept incoming connections from the socket queue]
 *  @x
 */
void srv_pull_coque(void)
{
    if(srv_cons >= MAX_CLIENT_CONNECTIONS)   // TODO: message connecting client!

    struct clientData client;
    client.socket = accept(srv_socket, (struct sockaddr *)&client.addr_info, sizeof(struct sockaddr_in));
    
    if(client.socket) {
      add_ClientList(client);
      srv_cons++;
    }
}

msgf_t msg_format_st(char *in_msg)
{
  msgf_t t_msg = malloc(sizeof(msgf_t));
  t_msg.type = in_msg[0];
  t_msg.msg = malloc(sizeof(char) * (strlen(in_msg) - 1));
  strcpy(t_msg.msg, in_msg + 1);
}

void srv_broadcast_msg(char *msg)
{
  for (int i = 0; i < srv_cons; i++)
    send(at_ClientList(i).client_info.socket, msg, strlen(msg), NULL);
}

void srv_private_msg(char *msg, char *from, char *to)
{

}

void srv_msg(char *msg, char *from)
{

}

void srv_update(void)
{
      //char *client_name = calloc(sizeof(char) * MAX_NAME_LENGTH + 1);
      
      for (int i = 0; i < srv_cons; i++) {

        struct clientData client = at_ClientList(i).client_info;

        char *t_msgBuf = malloc(sizeof(char) * 512);
        recv(client.socket, t_msgBuf, (sizeof(char) * 512), NULL);
      
        msgf_t msg_data = msg_format_st(t_msgBuf);

        // set client username in: authorize_client(char *name);

        if (!strcmp(msg_data.type, "I") && authorize_client(msg_data.msg))  // init msg
        {
          char *aBuf;
          sprintf(aBuf, "%s has joined!", msg_data.msg);
          srv_broadcast_msg(aBuf);
        }

        if (!strcmp(msg_data.type, "A"))                                // normal msg
        {
          char *aBuf;
          sprintf(aBuf, "%s :: %s", client., msg_data.msg);
          srv_msg(aBuf, );
        }

      }
}

int main()
{
  g_clientList = init_ClientList(MAX_CLIENT_CONNECTIONS);

  struct sockaddr_in srv_endpoint;
  memset(&srv_endpoint, 0, sizeof(srv_endpoint));
  srv_endpoint.sin_family      = AF_INET;                
  srv_endpoint.sin_addr.s_addr = htonl(INADDR_ANY);
  srv_endpoint.sin_port        = htons(PORTNUM);           

  srv_socket = socket(AF_INET, SOCK_STREAM, 0);

  bind(srv_socket, (struct sockaddr *)&srv_endpoint, sizeof(struct sockaddr));

  listen(srv_socket, 1);  // mark socket for listening

  srv_online = 1;
  srv_cons = 0;

  while(srv_online)
  {
    srv_pull_coque();
    srv_update();
  }  

  close(srv_socket);
  return 0;
}