///
/// objtest.cpp

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

/******************
  Generated using ObjDump utility
  
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	89 7d fc             	mov    %edi,-0x4(%rbp)
   7:	89 75 f8             	mov    %esi,-0x8(%rbp)
   a:	8b 55 fc             	mov    -0x4(%rbp),%edx
   d:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10:	01 d0                	add    %edx,%eax
  12:	5d                   	pop    %rbp
  13:	c3                   	retq   

********************************************************/


// --- The Above code snippet was converted to a string ....

char addfunc[] = 
"\x48\x89\xe5\x89\x7d\xfc\x89\x75\xf8\x8b\x55\xfc\x8b\x45\xf8\x01\xd0\x5d\xc3";



int main( int argc , char **argv )
{

  // Allocate memory from Heap

  char *Code = (char *)malloc(100);

  // Compute the Page #   
  unsigned page = (unsigned)&Code & ~( getpagesize() - 1 );


  //-------------- Set the Executable Bit

  if( mprotect( (char*)page, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC ) )
    {
      perror( "mprotect failed" );
      exit( errno );
    }

  //--------------- Copy the Code from addfunc to Code
  memcpy(Code,addfunc,sizeof(addfunc));

  // Cast the Code into a Function Pointer
  int (*AddFunc)(int , int ) = (int (*)(int,int))((void *)Code);

  // invoke the method
  int retval = AddFunc(4,5);

  printf("%d\n",retval);

  // ------------ Remove the executable bit

  if( mprotect( (char*)page, getpagesize(), PROT_READ | PROT_WRITE ) )
    {
      perror( "mprotect failed" );
      exit( errno );
    }

    //----------Free the heap allocated memory
 
    free(Code);


}

/// EOF objtest.cpp