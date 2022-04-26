title:: the /etc/services file
This file maps the user friendly names of certain Internet services to a port number and protocol.
The precise pathname for this file is given by the C language macro _PATH_SERVICES. 

The following is a pair of well-known service entries:
```
ftp 21/tcp
telnet 23/tcp
```




[[getservent()]] function is used to return a pointer to a struct that represents one entry from the /etc/services file

-
- We can use the getservent() as this example to see these services:
	- ```c
	  /* servent.c:
	   * 
	   * Example getservent(3) program :
	   */
	  #include <stdio.h>
	  #include <unistd.h>
	  #include <stdlib.h>
	  #include <errno.h>
	  #include <string.h>
	  #include <netdb.h>
	  #include <netinet/in.h>
	  
	  int
	  main(int argc,char **argv) {
	      int x;
	      struct servent *sp;
	  
	      for (;;) {
	          errno = 0;
	          if ( !(sp = getservent()) )
	              break;
	  
	          printf("%s:\n"
	              "\tPort:     %d\n"
	              "\tProtocol: %s\n"
	              "\tAliases:  ",
	              sp->s_name,
	              ntohs(sp->s_port),
	              sp->s_proto);
	          for ( x=0; sp->s_aliases[x] != NULL; ++x )
	              printf("%s ",sp->s_aliases[x]);
	          putchar('\n');
	      }
	  
	      if ( errno != 0
	      &&   errno != ENOENT ) /* For RH-6.0 */
	          fprintf(stderr,
	              "%s: getservent(3) %d\n",
	              strerror(errno),errno);
	  
	      return 0;
	  }
	  ```
	  
	  Similarly, there are some companions to this function -- [[setservent(3)]] and [[endservent(3)]] which allows you to rewind the file that is opened behind the scenes (if not, you will continue to receive EOF), and closing the file, respectively.
	  
	  If you want to lookup a service by name and protocol, you would use the [[getservbyname(3)]] function, like so:
	  ```c
	  struct servent *sp;
	  
	  sp = getservbyname("telnet", "tcp");
	  if (!sp){
	     abort(); /* No such service!*/
	  }
	  ```
	  
	  There is also one to get it by port, [[getservbyport(3)]]