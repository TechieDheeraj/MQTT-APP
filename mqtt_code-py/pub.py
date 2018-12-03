#! /usr/bin/python3

import paho.mqtt.client as mqtt
import time

UPSTREAM_TOPIC="test/upstream"
DOWNSTREAM_TOPIC="test/downstream"
QOS=0
KEEPALIVE=60
BROKER="127.0.0.1"
PORT=8008

def on_connect(client, userdata, flags, rc):
	print("Connected with Result Code: %d" % rc)
	payload="THIS IS UPSTREAM REPLY"
	client.publish(UPSTREAM_TOPIC, payload, qos=QOS, retain=False)

def on_disconnect(client, userdata, rc):
	print("Client Disconnected from Broker with rc: %d" % rc)
	#client.loop_stop()

def on_subscribe(client, userdata, mid, granted_qos): 
	print("Successfully subscribed Userdata: %s : granted_qos: %s" % (str(userdata), str(granted_qos)))

def on_publish(client, userdata, mid):
	print("Successfully published Message %s: mid: %s" % (str(userdata), str(mid)))
	client.subscribe(DOWNSTREAM_TOPIC)

def on_message(client, userdata, msg):
	msg.payload = msg.payload.decode("utf-8")
	print("Got Message: Topic: %s Msg: %s" % (str(msg.topic),str(msg.payload)))
	client.unsubscribe(DOWNSTREAM_TOPIC)
	payload="THIS IS UPSTREAM REPLY"
	time.sleep(1)
	client.publish(UPSTREAM_TOPIC, payload, qos=QOS, retain=False)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_publish = on_publish
client.on_subscribe = on_subscribe
client.connect(BROKER, PORT, KEEPALIVE)
#client.loop_start()
client.loop_forever()

