/*
 *Last update: 2015.10.19
 *
 * */


//#include <firwin.h>
#include "wavelet.h"
//#include <Wavelet.hpp>
#include <string.h>
#include <math.h>
//time counter
#include <sys/time.h>


//serial port header
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>



int main(int argc,char** argv)
{
	int signal_len=40;
	int _step  = 1;// (int) signal_len/10;  //read length
	int _shift = (int) signal_len/2;  //select points from reconstructed data

	double* signal_des  = (double*) malloc(signal_len*sizeof(double));
	double* signal_buf1 = (double*) malloc(signal_len*sizeof(double));   //signal buff, hold wavelet filtered signal
	double* signal_buf2 = (double*) malloc(signal_len*sizeof(double));   //signal buff, hold differentiated result
	double* signal_buf3 = (double*) malloc(signal_len*sizeof(double));   //signal buff, hold squaring result
	double* signal_buf4 = (double*) malloc(signal_len*10*sizeof(double));   //signal buff, hold integrated function result
	
	memset(signal_des ,0,signal_len*sizeof(double));
	memset(signal_buf1,0,signal_len*sizeof(double));
	memset(signal_buf2,0,signal_len*sizeof(double));
	memset(signal_buf3,0,signal_len*sizeof(double));
	memset(signal_buf4,0,signal_len*10*sizeof(double));
	
	
	WaveCoeff coeff[10];
	WaveRecon recon[10];
	int de_level=5;
	int filter_name=0;
	double des=0.0;     //selected wavelet filter result
	int peak_flag1=0;    //flag2
	int peak_flag2=0;    //flag2
	int peak_delay= 0;  //peak refresh rate
	double peak = 0.0;  //QRS peak

	/******* configure serial port ******/
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;
    int tty_fd;	
	
    unsigned char c='D';
	const char* portname = "ttyS1";
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
	
	//for serial port 
	unsigned char buf[10];
	int     da = 0;
	int	buf_cnt=0;
  	struct timeval start;
	unsigned long timer;
    unsigned char c='D';
    
    tty_fd=open(portname, O_RDWR | O_NONBLOCK);      
    cfsetospeed(&tio,B115200);            // 115200 baud
    cfsetispeed(&tio,B115200);            // 115200 baud
    
    tcsetattr(tty_fd,TCSANOW,&tio);	
	while (c!='q')
    {
        //if (read(tty_fd,&c,1)>0)        write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
        if (read(tty_fd,&c,1)>0)        
		{
			//write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
			//printf("\n");
			if (c == 'a')
			{	gettimeofday(&start,NULL);
				timer = start.tv_usec;
				//printf("t:%d\n",timer);
				da = atof(buf);
				//printf("%d",da);
				buf_cnt = 0;
				memset(buf,10,sizeof(unsigned char));
	/*   }
	

				//enable test (read file)
				FILE *fp_r;
				FILE *fp_w;
				char* filename=argv[1];
				const char filename2[]="test2.txt";

				printf("opening file %s",filename);

				FILE *fp_r=fopen(filename,"r");     //read data
				FILE *fp_w=fopen(filename2,"w");    //write result

				struct timeval start;
				unsigned long timer;	

				//begin loop
				if (fp_r==NULL)
				{
					printf("NULL file pionter");
					return 0;
				}
				char buf[15]={0};

				while (fgets(buf,15,fp_r)!=NULL)
				{	
					//time counter
					gettimeofday(&start,NULL);
					timer=start.tv_usec;
				//	printf("%d\n",timer);	
				
					//move out components ahead
					for(int i=0;i<signal_len-_step;i++)
						signal_des[i]=signal_des[i+_step];

					//put new data to signal
					for (int i=signal_len-_step; i<signal_len;i++)
					{
						signal_des[i]=atof(buf);
						if (fgets(buf,15,fp_r)==NULL)
							continue;			
					}
				*/
					//move out components ahead
					for(int i=0;i<signal_len-_step;i++)
						signal_des[i]=signal_des[i+_step];

					//put new data to signal
					for (int i=signal_len-_step; i<signal_len;i++)
					{
						signal_des[i]=da;
						//signal_des[i]=atof(buf);
						//if (fgets(buf,15,fp_r)==NULL)
						//	continue;			
					}
					//begin filter
					switch(filter_name)
					{
					case 0: //db4
						{
							WaveDecompose(signal_des,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
							break;
						}
					case 1: //db5
						{
							WaveDecompose(signal_des,signal_len,db5_Lo_D,db5_len,db4_Hi_D,db5_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,db5_Lo_R,db5_len,db4_Hi_R,db5_len,coeff,recon,'a',de_level);
							break;
						}
					case 2: //db6
						{
							WaveDecompose(signal_des,signal_len,db6_Lo_D,db6_len,db6_Hi_D,db6_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,db6_Lo_R,db6_len,db6_Hi_R,db6_len,coeff,recon,'a',de_level);
							break;
						}
					case 3: //sym4
						{
							WaveDecompose(signal_des,signal_len,sym4_Lo_D,sym4_len,sym4_Hi_D,sym4_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,sym4_Lo_R,sym4_len,sym4_Hi_R,sym4_len,coeff,recon,'a',de_level);
							break;
						}
					case 4: //sym5
						{
							WaveDecompose(signal_des,signal_len,sym5_Lo_D,sym5_len,sym5_Hi_D,sym5_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,sym5_Lo_R,sym5_len,sym5_Hi_R,sym5_len,coeff,recon,'a',de_level);
							break;
						}
					case 5: //sym6
						{
							WaveDecompose(signal_des,signal_len,sym6_Lo_D,sym6_len,sym6_Hi_D,sym6_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,sym6_Lo_R,sym6_len,sym6_Hi_R,sym6_len,coeff,recon,'a',de_level);
							break;
						}
					case 6: //coif4
						{
							WaveDecompose(signal_des,signal_len,coif4_Lo_D,coif4_len,coif4_Hi_D,coif4_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,coif4_Lo_R,coif4_len,coif4_Hi_R,coif4_len,coeff,recon,'a',de_level);
							break;
						}
					case 7: //coif5
						{
							WaveDecompose(signal_des,signal_len,coif5_Lo_D,coif5_len,coif5_Hi_D,coif5_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,coif5_Lo_R,coif5_len,coif5_Hi_R,coif5_len,coeff,recon,'a',de_level);
							break;
						}
					default: //db4
						{
							WaveDecompose(signal_des,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
							WaveReconstruct(signal_des,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
							break;
						}
					}
					
					des = recon[0].capp[_shift];
					
					for(int i=signal_len-1;i>0;i--)
						signal_buf1[i] = signal_buf1[i-1];
					signal_buf1[0] = des;
					
					//1.  differentiate function -- derivative
					for(int i=signal_len-1;i>0;i--)
						signal_buf2[i] = signal_buf2[i-1];
					signal_buf2[0] = signal_buf1[0]-signal_buf1[3];
					
					//2.  Squaring funciton 
					for(int i=signal_len-1;i>0;i--)
						signal_buf3[i] = signal_buf3[i-1];
					//signal_buf3[0] = signal_buf2[0]*signal_buf2[0];
					signal_buf3[0] = abs(signal_buf2[0]);
					
					//3.  Integrate function
					peak = 0.0;
					for (int i=signal_len*10-1;i>0;i--)	
					{
						if(peak<signal_buf4[i])
							peak = signal_buf4[i];
						signal_buf4[i] = signal_buf4[i-1];
					}
					signal_buf4[0] = 0.0;
					for (int i=0;i<signal_len;i++)
						signal_buf4[0] = signal_buf4[0]+signal_buf3[i];
					
					//search peak
					if(peak_delay>100)
						peak_delay = 0;
					else
						peak_delay++;
					
					if (signal_buf4[0]>=peak*4/5)
						peak_flag1 = 1;
					else
						peak_flag1 = 0;
					if (signal_buf4[3]>=peak*4/5)
						peak_flag2 = 1;
					else
						peak_flag2 = 0;
					//detect a peak here
					if((peak_flag2==0)&(peak_flag1==1))
					{
						//find last peak distance: if the distance larger than 10 point, then output a peak 
						if (peak_delay>10)
						{
							peak_delay = 0;
							printf("ok\n");
							//printf("%f\n",);		
						}
					}
					//select data in the middle of the signal
					for (int i=_shift;i<_shift+_step;i++)
						printf("%f\n",des);// recon[0].capp[i]);
					
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

/*	//close file
	fclose(fp_r);
	fclose(fp_w);
*/
	//close port
	close(tty_fd);
    tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
	
	return 0;
}











