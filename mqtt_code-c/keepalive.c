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
        while((i<argc))
        {
                if(strcmp(argv[i],"-p")==0)
                {
                        if(argv[i+1]!=0)
			{
                        port=argv[i+1];
			}
                        else
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
			}
                        else
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
  	msg.ta_name=token;
	printf("Port:%s,",port);
        printf("Host:%s,",host);
        printf("Topic:%s,",topic);
        printf("Transaction Id:%d,",msg.transactionid);
        printf("Message Type:%d,",msg.messagetype);
        printf("Ta Name%s,",msg.ta_name);
	len=mack__get_packed_size(&msg);
	buf=malloc(len);	
	mack__pack(&msg,buf);
	publisher(len,buf,host,port,topic);
	free(buf);
	return 0;
			
}
