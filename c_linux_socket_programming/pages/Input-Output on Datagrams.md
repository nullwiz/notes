title:: Input-Output on Datagrams

Before we saw the socketpair(2) function created a pair of sockets using a connection-oriented protocol [[SOCK_STREAM]] .
When sending and receiving datagrams, a different pair of functions is required.

	- # The sendto(2) function
	  
	  ``` sendto(2)
	  int sendto(int s, const void *msg,
	                    int len,
	                    unsigned flags,
	                    const struct sockaddr *to,
	                    int tolen);
	  ```
	  
	  When successful, returns number of bytes sent. If not, returns -1.
	  The flags are usually zero, but those are option bits.
-
	- # The recvfrom(2) function
	  Companion to the upper function. Differs from read(2) in that it allows you to receive the sender's address at the same time as you receive the datagram.
	  
	  ``` recvfrom(2)
	  int recvfrom(        int s,
	                       void *buf,
	                       int len,
	                       unsigned flags,
	                       struct sockaddr *from,
	                       int *fromlen);
	  
	  ```
	- socket to receive the datagram from, buffer pointer to receive into, maxlen, option bit flag, pointer to the receiving socket address buffer, which will receive the sender's address, and the pointer to the max len in bytes of the receiving socket address buffer _from_ . The integer that this pointer points to must be initialized before calling the function. 
	  Same error handling as above.