#include <sys/socket.h>
#include <inttypes.h>
#include <stdlib.h>

/****
	ClientList ((:

	- Access client by index
	- Iterate over clients efficiently
	- Automatic array stacking, size reduction

 ****/

struct clientData 
{
	int32_t socket;			// socket
	sockaddr_in addr_info;	// address
};

typedef struct ClientList 
{
	struct clientData *client_info;	// info: socket and address
	int16_t size;					// clients in list
	int16_t capacity;				// list max size
} client_list_t;


extern client_list_t g_clientList;

/**
 *	[init_ClientList: initialize the client list]
 *	@param:  capacity [max amount of clients in list]
 *	@return: status   [0: success, 1: failure]
 */
int8_t init_ClientList(int16_t capacity);

/**
 *	[add_ClientList: add a client to the client list]
 *	@param:  client_info [client data]
 *	@return: status      [0: success, 1: invalid client info, 2: client list full]
 */
int8_t add_ClientList(struct clientData client_info);

/**
 *	[at_ClientList: access a client by index within the client list]
 *	@param:  id         [client index]
 *	@assert: id         [break: id out of bounds]
 *	@return: clientData [client data]
 */
struct clientData at_ClientList(int16_t id);

/**
 *	[rm_Client: remove a client from the client list]
 *	@param:  id     [client index]
 *	@return: status [0: success, 1: no such client]
 */
int8_t rm_ClientList(int16_t id);

/**
 *	[valid_client: validate client info]
 *	@param:  client_info [client data]
 *	@return: status      [0: valid, 1: failure]
 */
int8_t valid_client(struct clientData client_info);
