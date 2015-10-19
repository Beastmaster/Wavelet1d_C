#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>
int main(int argc,char** argv)
{
        struct termios tio;
        struct termios stdio;
        struct termios old_stdio;
        int tty_fd;
	unsigned char buf[10];
	int     da = 0;
	int	buf_cnt=0;
  	struct timeval start;
	unsigned long timer;
        unsigned char c='D';
        
	memset(buf,0,10*sizeof(unsigned char));

	tcgetattr(STDOUT_FILENO,&old_stdio);
	
        printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;
        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;

        tty_fd=open(argv[1], O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B115200);            // 115200 baud
        cfsetispeed(&tio,B115200);            // 115200 baud

        tcsetattr(tty_fd,TCSANOW,&tio);
        while (c!='q')
        {
                if (read(tty_fd,&c,1)>0)        
		{
			//write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
			//printf("\n");
			if (c == 'a')
			{	gettimeofday(&start,NULL);
				timer = start.tv_usec;
				printf("t:%d\n",timer);
				da = atof(buf);
				printf("%d",da);
				buf_cnt = 0;
				memset(buf,10,sizeof(unsigned char));
			}		
			else
			{	if(buf_cnt>=10)
					buf_cnt = 0;
				buf[buf_cnt] = c;
				buf_cnt++;	
			}

                }
		if (read(STDIN_FILENO,&c,1)>0)  write(tty_fd,&c,1);                     // if new data is available on the console, send it to the serial port
        }

        close(tty_fd);
        tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);

        return EXIT_SUCCESS;
}
