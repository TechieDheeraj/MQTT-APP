all: info keepalive test-sub

info: info.c test-pub.c msg.pb-c.c
	gcc -o info info.c test-pub.c msg.pb-c.c -lmosquitto -lprotobuf-c
keepalive: keepalive.c test-pub.c msg.pb-c.c
	gcc -o keepalive keepalive.c test-pub.c msg.pb-c.c -lmosquitto -lprotobuf-c
test-sub: test-sub.c msg.pb-c.c
	gcc -o test-sub test-sub.c msg.pb-c.c -lmosquitto -lprotobuf-c
clean:
	rm info keepalive test-sub
