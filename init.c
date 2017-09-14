/**
 * @vaidehip_assignment3
 * @author  Vaidehi Santu Patil <vaidehip@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */

/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */

#include <string.h>

#include "../include/global.h"
#include "../include/control_header_lib.h"
#include "../include/network_util.h"


struct neighbour
{
	uint16_t router_id;
	uint16_t router_port;
	uint16_t data_port;
	uint16_t cost;
	int ip_address;

};


//#define AUTHOR_STATEMENT "I, vaidehip, have read and understood the course academic integrity policy."

#define TWO_BYTE_LENGTH 0x02
#define FOUR_BYTE_LENGTH 0x04

//#define AUTHOR_STATEMENT "I, vaidehip, have read and understood the course academic integrity policy."
struct neighbour neighbour_array;
short int router_count;

void init_response(int sock_index,uint16_t payload_len,char* cntrl_payload)
{


	char *payload;

	recvALL(sock_index, payload, payload_len);


	short int update_interval;

	int total_offset=0;
	memcpy(&router_count, payload+total_offset, sizeof(router_count));
	total_offset+=2;
	memcpy(&update_interval, payload+total_offset, sizeof(update_interval));


	struct neighbour neighbour_array[router_count];

	int i=0;
	total_offset+=2;
	while(router_count>0)
	{

		short int router_id;
		short int router_port;
		short int data_port;
		short int cost;
		int ip_address;


		memcpy(&router_id,payload+total_offset,sizeof(router_id));
		total_offset+=2;
		memcpy(&router_port,payload+total_offset,sizeof(router_port));
		total_offset+=2;
		memcpy(&data_port,payload+total_offset,sizeof(data_port));
		total_offset+=2;
		memcpy(&cost,payload+total_offset,sizeof(cost));
		total_offset+=2;
		memcpy(&ip_address,payload+total_offset,sizeof(ip_address));
		total_offset+=4;

		neighbour_array[i].router_id=router_id;
		neighbour_array[i].router_port=router_port;
		neighbour_array[i].data_port=data_port;
		neighbour_array[i].cost=cost;
		neighbour_array[i].ip_address=ip_address;
		i++;
		router_count--;

	}

	free(payload);

//	//send response
//	uint16_t response_len;
//	char *cntrl_response_header, *cntrl_response_payload, *cntrl_response;
//
//	payload_len = 0;
//	//cntrl_response_payload = (char *) malloc(payload_len);
//	//memcpy(cntrl_response_payload, AUTHOR_STATEMENT, payload_len);
//
//	cntrl_response_header = create_response_header(sock_index, 1, 0, payload_len);
//
//	response_len = CNTRL_RESP_HEADER_SIZE+payload_len;
//	cntrl_response = (char *) malloc(response_len);
//	/* Copy Header */
//	memcpy(cntrl_response, cntrl_response_header, CNTRL_RESP_HEADER_SIZE);
//	free(cntrl_response_header);
//	/* Copy Payload */
//	//memcpy(cntrl_response+CNTRL_RESP_HEADER_SIZE, cntrl_response_payload, payload_len);
//	free(cntrl_response_payload);
//	//printf(" cntrl_response   =  %s", cntrl_response);
//
//	sendALL(sock_index, cntrl_response, response_len);
//
//	free(cntrl_response);
	uint16_t response_len;
		char *cntrl_response_header, *cntrl_response_payload, *cntrl_response;

		//payload_len = sizeof(AUTHOR_STATEMENT)-1; // Discount the NULL chararcter
		//cntrl_response_payload = (char *) malloc(payload_len);
		//memcpy(cntrl_response_payload, AUTHOR_STATEMENT, payload_len);
		payload_len = 0;

		cntrl_response_header = create_response_header(sock_index, 0, 0, payload_len);

		response_len = CNTRL_RESP_HEADER_SIZE+payload_len;
		cntrl_response = (char *) malloc(response_len);
		/* Copy Header */
		memcpy(cntrl_response, cntrl_response_header, CNTRL_RESP_HEADER_SIZE);
		free(cntrl_response_header);
		/* Copy Payload */
		//memcpy(cntrl_response+CNTRL_RESP_HEADER_SIZE, cntrl_response_payload, payload_len);
		//free(cntrl_response_payload);

		sendALL(sock_index, cntrl_response, response_len);

		free(cntrl_response);
}


