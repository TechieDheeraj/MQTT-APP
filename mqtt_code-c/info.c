#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"msg.pb-c.h"

int publisher (int len, void *buf,char* MQTT_HOSTNAME,char *MQTT_PORT,char *MQTT_TOPIC);
int main(int argc,char *argv[])
{
	int i=1;
	char *port=NULL;
	char *host=NULL;
	char *topic=NULL;
	char *msgx=NULL;
        char *msgid=NULL;
        char *msgtype=NULL;
        char *message=NULL;
	char *tmp=NULL;
	char *keep=NULL;
	char *name=NULL;
        while((i<argc))
        {
                if(strcmp(argv[i],"-p")==0)
                {
                        if(argv[i+1]!=0)
			{
                        port=argv[i+1];
			}
                        else
                        printf("pls put some value of port\n");
                        break;
                }
        i++;
        }
	i=1;
	while((i<argc))
        {
       
                if(strcmp(argv[i],"-h")==0)
                {
                        if(argv[i+1]!=0)
			{
                        host=argv[i+1];

			
			}
                        else
                        printf("pls put some value of host\n");
                        break;
                }
        i++;
        }
	i=1;
        while((i<argc))
        {
       
                if(strcmp(argv[i],"-name")==0)
                {
                        if(argv[i+1]!=0)
                        {
                        name=argv[i+1];

                        
                        }
                        else
                        printf("pls put some value of name\n");
                        break;
                }
        i++;
        }
	i=1;
	while((i<argc))
        {
     
                if(strcmp(argv[i],"-t")==0)
                {
                        if(argv[i+1]!=0)
			{
                        topic=argv[i+1];

			
			}
                        else
                        printf("pls put some value of topic\n");
                        break;
                }
        i++;
        }
	i=1;
	while((i<argc))
        {
     
                if(strcmp(argv[i],"-m")==0)
                {
                        if(argv[i+1]!=0)
			{
                        msgx=argv[i+1];
			
			printf("%s\n",msgx);
			}
                        else
                        printf("pls put some message\n");
                        break;
                }

        i++;
        }
	char *token=NULL;
	char *rest=(char *)&msgx;
	unsigned len;
	void *buf;
	Mack msg = MACK__INIT;
        token = strtok(msgx, " ");

 	msg.transactionid=atoi(token);
        token = strtok(NULL, " ");

  	msg.messagetype=atoi(token);
        token = strtok(NULL, " ");

  	msg.result=token;
        token = strtok(NULL, " ");

	if(strcmp(token,"0"))
		msg.payload=token;
	else
		printf("NO PAYLOAD\n");

        printf("Final Message is-> %s\n",token);
	msg.ta_name=name;
	printf(" Port: %s\n",port);
	printf("Broker IP: %s\n",host);
	printf("Topic For MQTT: %s\n",topic);
	printf("TA_NAME: %s\n",name);
	printf("Transaction ID: %d\n",msg.transactionid);
	printf("Message Type: %d\n",msg.messagetype);
	len=mack__get_packed_size(&msg);
	buf=malloc(len);	
	mack__pack(&msg,buf);
	publisher(len,buf,host,port,topic);
	free(buf);
	return 0;
			
}
