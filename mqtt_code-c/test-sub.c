#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mosquitto.h>
#include <signal.h>

#define MAX_MSG_SIZE 1024

#include"msg.pb-c.h"



// Server connection parameters
#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"

/*
* my_message_callback. 
 * Called whenever a new message arrives
 */
struct mosquitto *mosq = NULL;
void my_message_callback(struct mosquitto *mosq, void *obj, 
		const struct mosquitto_message *message)
{
	// Note: nothing in the Mosquitto docs or examples suggests that we
	//  must free this message structure after processing it.
	while((message->payload)==NULL);
	// ---------------------------------protobuf start ---------------------	
	Mack *tmmsg;
        uint8_t msg[MAX_MSG_SIZE];
        memcpy(msg,message->payload,message->payloadlen);
	size_t msg_len = (size_t)message->payloadlen;
        tmmsg = mack__unpack(NULL,msg_len,msg);
        if (tmmsg == NULL)
        {
                fprintf(stderr, "error unpacking incoming message\n");
                exit(1);
        }
	printf("%d\n",tmmsg->transactionid);
	printf("%s\n",tmmsg->ta_name);
	printf("%d\n",tmmsg->messagetype);
	printf("%d\n",tmmsg->test_duration);
	printf("%d\n",tmmsg->result_duration);
	printf("%s\n",tmmsg->binary_name);
	printf("%s\n",tmmsg->binary_argument_list);
	// ---------------------------------protobuf end ---------------------	
	mosquitto_disconnect(mosq);
}
int main (int argc, char **argv)
{
	//host =argv[1] port =argv[2] topic =argv[3]
	// Initialize the Mosquitto library
	mosquitto_lib_init();

	// Create a new Mosquito runtime instance with a random client ID,
	//  and no application-specific callback data.  
	mosq = mosquitto_new (NULL, true, NULL);
	if (!mosq)
	{
		printf ("Can't init Mosquitto library\n");
		exit (-1);
	}
	// Set up username and password
	mosquitto_username_pw_set (mosq, MQTT_USERNAME, MQTT_PASSWORD);
	// Establish a connection to the MQTT server. Do not use a keep-alive ping
	//int ret = mosquitto_connect (mosq, MQTT_HOSTNAME, MQTT_PORT, 0);
	int ret = mosquitto_connect (mosq, argv[1], atoi(argv[2]), 0);
	if (ret)
	{
		printf ("Can't connect to Mosquitto server\n");
		exit (-1);
	}
	// Subscribe to the specified topic. Multiple topics can be
	//  subscribed, but only one is used in this simple example.
	//  Note that we don't specify what to do with the received
	//  messages at this point
	//ret = mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0);
	ret = mosquitto_subscribe(mosq, NULL, argv[3], 0);
	if (ret)
	{
		printf ("Can't publish to Mosquitto server\n");
		exit (-1);
	}
	// Specify the function to call when a new message is received
	mosquitto_message_callback_set (mosq, my_message_callback);

	// Wait for new messages
	
	mosquitto_loop_forever(mosq,-1,1);
	//  force the mosquitto_loop_forever call to exit by disconnecting
	//  the session in the message-handling callback if required.
	mosquitto_destroy (mosq);
	mosquitto_lib_cleanup();
	return 0;
}

