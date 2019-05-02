# Dynamic library C

Using dynamic library to modularize code base and allow a hot reload of the application by injecting new version of the library.

- msg1.c => Library: 1 function "Message" returning a string
- main.c => HTTP server (port 3000) executing the "Message" function of the library (libmessage.so) foreach request.
- lib.sh => compile msg1.c and create the dynamic library => libmessage.so

Once the server is running, by updating the msg1.c and execute lib.sh, and send an http request to the server, the message content changes dynamically (like hot-reload).