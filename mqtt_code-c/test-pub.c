#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
/*#define MQTT_HOSTNAME "192.168.0.32" 
#define MQTT_PORT 5555
#define MQTT_TOPIC "/tm/ta-keepalive"
*/
#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"
int publisher (int len, void *buf,char* MQTT_HOSTNAME,char *MQTT_PORT,char *MQTT_TOPIC)
{
	int ret;
	struct mosquitto *mosq = NULL;

	// Initialize the Mosquitto library
	mosquitto_lib_init();

	// Create a new Mosquito runtime instance with a random client ID,
	//  and no application-specific callback data.  
	mosq = mosquitto_new (NULL, 1, NULL);
	if (!mosq)
	{
		fprintf (stderr, "Can't initialize Mosquitto library\n");
		exit (-1);
	}

	mosquitto_username_pw_set (mosq, MQTT_USERNAME, MQTT_PASSWORD);
	// Establish a connection to the MQTT server. Do not use a keep-alive ping
	 ret = mosquitto_connect (mosq, MQTT_HOSTNAME, atoi(MQTT_PORT), 0);
	if (ret)
	{
		fprintf (stderr, "Can't connect to Mosquitto server\n");
		exit (-1);
	}

		// Publish the message to the topic
		ret = mosquitto_publish (mosq, NULL, MQTT_TOPIC, 
				len, buf, 0, 0);
		if (ret)
		{
			fprintf (stderr, "Can't publish to Mosquitto server\n");
			exit (-1);
		}
	// We need a short delay here, to prevent the Mosquito library being
	//  torn down by the operating system before all the network operations
	//  are finished.

	// Tidy up
	mosquitto_disconnect (mosq);
	mosquitto_destroy (mosq);
	mosquitto_lib_cleanup();

	return 0;
}

