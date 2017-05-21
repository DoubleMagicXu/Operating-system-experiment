#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define FIFO_NAME_1 "/home/sqxu/Desktop/pipe"                    //定义宏，指向管道文件的位置
#define FIFO_NAME_2 "/home/sqxu/Desktop/guandao"                    //定义宏，指向管道文件的位置

int main( int argc, char *argv[  ] )
{
  int open_mode = O_RDONLY;
  int res;
  int pipe_fd;
  int c;
  int d;
  if( access( FIFO_NAME_1, F_OK ) == -1 )
  {
      res = mkfifo(FIFO_NAME_1, 0777);
      if (res != 0) {
      fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME_1);
      exit(1);
    }
  }

  pipe_fd = open( FIFO_NAME_1, open_mode );
    if( pipe_fd !=-1 )
    {
      res = read( pipe_fd, &c, 4 );
      if(res<=0)
      {
        printf("error\n");
        exit(1);
        close( pipe_fd );
      }
      if(c==0)
      printf("选手一为：石头\t");
      if(c==1)
      printf("选手一为：剪刀\t");
      if(c==2)
      printf("选手一为：布\t");
      close( pipe_fd );
    }



    if( access( FIFO_NAME_2, F_OK ) == -1 )
    {
        res = mkfifo(FIFO_NAME_2, 0777);
        if (res != 0) {
        fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME_2);
        exit(1);
      }
    }

    pipe_fd = open( FIFO_NAME_2, open_mode );
      if( pipe_fd !=-1 )
      {
        res = read( pipe_fd, &d, 4 );
        if(res<=0)
        {
          printf("error\n");
          exit(1);
          close( pipe_fd );
        }
        if(d==0)
        printf("选手二为：石头\t");
        if(d==1)
        printf("选手二为：剪刀\t");
        if(d==2)
        printf("选手二为：布\t");
        close( pipe_fd );
      }

      if(c==d)
      {
        printf("平局\n");
      }
      else if((c==0&&d==1)||(c==1&&d==2))
      {
        printf("选手一赢\n");

      }
      else
      {
        printf("选手二赢\n");
      }




  return 0;
}
