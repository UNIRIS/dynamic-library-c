#!bin/sh

cc -fPIC -c msg1.c
cc -shared -o libmessage.so msg1.o