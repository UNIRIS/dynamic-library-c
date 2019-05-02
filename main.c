#include <dlfcn.h>
#include<netinet/in.h>    
#include<stdio.h>    
#include<stdlib.h>    
#include<sys/socket.h>    
#include<sys/stat.h>    
#include<sys/types.h>    
#include<unistd.h>    
    
int main() {    
   int create_socket, new_socket;    
   socklen_t addrlen;    
   int bufsize = 1024;    
   char *buffer = malloc(bufsize);    
   struct sockaddr_in address;    
 
   if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){    
      printf("The socket was created\n");
   }
    
   address.sin_family = AF_INET;    
   address.sin_addr.s_addr = INADDR_ANY;    
   address.sin_port = htons(3000);    
    
   if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){    
      printf("Binding Socket\n");
   }

    void *handle;
        char* (*message)();
        char* error;

    while (1) {    
        if (listen(create_socket, 10) < 0) {    
            perror("server: listen");    
            exit(1);    
        }    
        
        if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {    
            perror("server: accept");    
            exit(1);    
        }    
        
        recv(new_socket, buffer, bufsize, 0);    
        printf("\n");    

        handle = dlopen("libmessage.so", RTLD_LAZY);
        if (handle == NULL ) {
            fputs(dlerror(), stderr);
            exit(1);
        }

        message = dlsym(handle, "Message");
        if ((error = dlerror()) != NULL ) {
            fputs(error, stderr);
            exit(1);
        }

        printf("%s\n",(*message)() );
        
        dlclose(handle);
        close(new_socket);    
    } 

    close(create_socket);    
    return 0;    
}