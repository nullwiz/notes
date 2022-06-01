- When a socket is created by the socket(2) function, its nameless. **Like a telephone, we must bind a name to a socket, as if it was a phone number**
  It has nothing to do with hostnames, it refers to the **address** of the socket.
- ```bind(2)
  #include <sys/types.h>
  #include <sys/socket.h>
  int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
  ```
  file descriptor -> returned by socket(2) call
  success, returns zero, else -1.
  address must be a pointer to the address structure, this is basically what bind is, points a file descriptor to a structure address socket, which comes from the protocol family internet (and specifies ip + port)