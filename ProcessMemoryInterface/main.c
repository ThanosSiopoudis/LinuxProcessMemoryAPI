#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <errno.h>
#include <string.h>

int ReadProcessMemory (pid_t pid, unsigned long address, unsigned long length, unsigned char *buf)
{
    int buffer;
    int endAddress = address + length;
    int loopCount = 0;
    
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL))
    {
        perror("PTRACE_ATTACH");
        return 0;
    }
    wait(NULL);
    for (; address < endAddress; address += sizeof(int))
    {
        errno = 0;
        if (((buffer = ptrace(PTRACE_PEEKDATA, pid, (void *)address, NULL)) == -1) && errno)
        {
            perror("PTRACE_PEEKDATA");
	    printf("%02X", (unsigned int)address);
            if (ptrace(PTRACE_DETACH, pid, NULL, NULL))
                perror("PTRACE_DETACH");
            return 0;
        }
        int pos = loopCount * sizeof(int);
	if (pos > 0) {
	  buf += sizeof(int);
	  memcpy(buf, (unsigned char*)&buffer, sizeof(int));
	}
	else {
	  memcpy(buf, (unsigned char*)&buffer, sizeof(int));
	}
	loopCount++;
    }
    if(ptrace(PTRACE_DETACH, pid, NULL, NULL))
    {
	perror("PTRACE_DETACH");
	return(0);
    }
    
    return 1;
}

int main(int argc, char **argv)
{
    // Main is for testing purposes
    pid_t pid = 14413;
    unsigned long address = 210173952;
    unsigned long length = 0x40;
    unsigned char buf[64];
    
    // Test the readprocmem function
    int result = ReadProcessMemory(pid, address, length, buf);
    for (int i=0; i<length; i++) {
        printf("%02X", buf[i]);
    }
    
    return(result);
}