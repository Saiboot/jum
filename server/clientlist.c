#include "clientlist.h"

#include <assert.h>

int8_t valid_client(struct clientData client_info);

int8_t init_ClientList(int16_t capacity)
{
	if (g_clientList.size <= 0)
		return 1;

	g_clientList.size = 0;
	g_clientList.client_info = (struct clientData *)malloc(sizeof(struct clientData) * capacity);
	
	return 0;
}

int8_t add_ClientList(struct clientData client_info)
{
	if (!valid_client(client_info))
		return 1;

	g_clientList.client_info[g_clientList.size] = client_info;
	return 0;
}

struct clientData at_ClientList(int16_t id)
{
	assert(!(id >= g_clientList.size));	// Array index within bounds ?
	return g_clientList.client_info[id];
}

int8_t rm_ClientList(int16_t id)
{
	if (id >= g_clientList.size)
		return 1;

	if (id != (g_clientList.size - 1))
		for (size_t i = 0; i < (g_clientList.size - 1) - id; i++)
			g_clientList.client_info[i + id] = g_clientList.client_info[i + id + 1];
	g_clientList.size--;
	return 0;
}

//	TODO: valid_client function

int8_t valid_client(struct clientData client_info)
{
	return 1;
}
