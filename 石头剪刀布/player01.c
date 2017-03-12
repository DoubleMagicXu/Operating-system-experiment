#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include<time.h>
#define FIFO_NAME "/home/sqxu/Desktop/pipe"                    //定义宏，指向管道文件位置
#define TEN_MEG ( 1024*1024*10 )                      //文件缓冲区最大值


int main( int argc, char* argv[  ] )
{
  int res;
  int c;
  int pipe_fd;
  int open_mode = O_WRONLY;                         //设置读写权限
  int bytes_send = 0;


  if( access( FIFO_NAME, F_OK ) == -1 )
  {
      res = mkfifo(FIFO_NAME, 0777);
      if (res != 0) {
      fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
      exit(1);
    }
  }

  pipe_fd = open( FIFO_NAME, open_mode );             //打开管道，并设置打开权限
  if( pipe_fd !=-1 ){
      srand((unsigned)time(NULL));
      c=rand()%3;
      res = write( pipe_fd, &c, 4 );                       //向管道中写数据
      if( res == -1 ){
    perror( "write error" );
    printf("write failed\n");
    close( pipe_fd );
    exit( 1 );
      }
    printf("write success!%d\n",c);
    close( pipe_fd );
  }


  return 0;
}
