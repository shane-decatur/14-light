#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static void sighandler(int sig){
  if (sig == SIGINT){
    int fd = open("exit.log",O_WRONLY | O_TRUNC | O_CREAT, 0777);
    char * msg = "program exited due to SIGINT";
    write(fd,msg,strlen(msg));
    close(fd);
    exit(0);
  }
  if (sig == SIGUSR1){
    printf("ppid: %d\n",getppid());
  }
}

int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while (1200){
    printf("pid: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
