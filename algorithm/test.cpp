/*
 *Latest update: 2015.12.1
 *
 * tty_fd : receive data from ADC
 * tty_fd2: receive communicate with master machine
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
	int ppp_cnt = 0;
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
	int filter_name=8;
	double des=0.0;     //selected wavelet filter result
	int peak_flag1=0;    //flag2
	int peak_flag2=0;    //flag2
	int peak_delay= 0;  //peak refresh rate
	double peak = 0.0;  //QRS peak
	double peak_l = 0.0;//QRS peak temp

    /******* configure serial port for receiving******/
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;
    int tty_fd;	
    /* *uart4 for sending**/    
    struct termios tio2;
    struct termios stdio2;
    struct termios old_stdio2;
    int tty_fd2;	


    unsigned char c='D';
	unsigned char c2 = 'D';
    unsigned char char_a = 'a';
    const char* portname = "/dev/ttyS2";
    const char* portname2 = "/dev/ttyS1";
    tcgetattr(STDOUT_FILENO,&old_stdio);
    

  //  printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
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

	
    memset(&tio2,0,sizeof(tio2));
    tio2.c_iflag=0;
    tio2.c_oflag=0;
    tio2.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio2.c_lflag=0;
    tio2.c_cc[VMIN]=1;
    tio2.c_cc[VTIME]=5;

	//for serial port 
	char buf[10];    //store received bytes
	char buf2[10];   //store bytes tobe sent
	int  da = 0;     //direct number received from ADC
	int	buf_cnt=0;

	memset(buf,0,10*sizeof(char));
	memset(buf2,0,10*sizeof(char));
	
	port1:
    tty_fd=open (portname,  O_RDWR | O_NONBLOCK);      
    if(tty_fd == -1)   
	{
		printf("open port error!!!\n");
		goto port1;
	}
    cfsetospeed(&tio,B115200);            // 115200 baud
    cfsetispeed(&tio,B115200);            // 115200 baud
    
	port2:
    tty_fd2=open (portname2,  O_RDWR | O_NONBLOCK);      
    if(tty_fd2 == -1)
	{
		printf("open port error!!!\n");
		goto port2;
	}
    cfsetospeed(&tio2,B115200);            // 115200 baud
    cfsetispeed(&tio2,B115200);            // 115200 baud

	//set terminal parameters
	tcsetattr(tty_fd ,TCSANOW,&tio );
    tcsetattr(tty_fd2,TCSANOW,&tio2);
    while (c2!='q')
    {
		if (read(tty_fd2,&c2,1)>0)
		{
			if( c2 == 'b')  
				filter_name = 1;
			else if( c2 == 'c')
				filter_name = 2;
			else if( c2 == 'd')
				filter_name = 3;
			else if( c2 == 'e')
				filter_name = 4;
			else if( c2 == 'f')
				filter_name = 5;
			else if( c2 == 'g')
				filter_name = 6;
			else if( c2 == 'h')
				filter_name = 7;
			else if( c2 == 'i')
				filter_name = 8;
			else
				filter_name = 8;
		}
		
        if (read(tty_fd,&c,1)>0)        
		{
			//capture spliter 'a'
			if(c == 'a')
			{	
				//convert char buf to numbers and clear flags
				da = atoi(buf);
				buf_cnt = 0;
				memset(buf,0,10*sizeof(char));
				
				//move out components ahead
				for(int i=0;i<signal_len-_step;i++)
					signal_des[i]=signal_des[i+_step];

				//put new data to signal
				for (int i=signal_len-_step; i<signal_len;i++)
				{
					signal_des[i]=da;		
				}
				//begin filter
				switch(filter_name)
				{
				case 0: //db4
					{
						WaveDecompose(signal_des,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				case 1: //db5
					{
						WaveDecompose(signal_des,signal_len,db5_Lo_D,db5_len,db4_Hi_D,db5_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,db5_Lo_R,db5_len,db4_Hi_R,db5_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				case 2: //db6
					{
						WaveDecompose(signal_des,signal_len,db6_Lo_D,db6_len,db6_Hi_D,db6_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,db6_Lo_R,db6_len,db6_Hi_R,db6_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				case 3: //sym4
					{
						WaveDecompose(signal_des,signal_len,sym4_Lo_D,sym4_len,sym4_Hi_D,sym4_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,sym4_Lo_R,sym4_len,sym4_Hi_R,sym4_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				case 4: //sym5
					{
						WaveDecompose(signal_des,signal_len,sym5_Lo_D,sym5_len,sym5_Hi_D,sym5_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,sym5_Lo_R,sym5_len,sym5_Hi_R,sym5_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				case 5: //sym6
					{
						WaveDecompose(signal_des,signal_len,sym6_Lo_D,sym6_len,sym6_Hi_D,sym6_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,sym6_Lo_R,sym6_len,sym6_Hi_R,sym6_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				case 6: //coif4
					{
						WaveDecompose(signal_des,signal_len,coif4_Lo_D,coif4_len,coif4_Hi_D,coif4_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,coif4_Lo_R,coif4_len,coif4_Hi_R,coif4_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				case 7: //coif5
					{
						WaveDecompose(signal_des,signal_len,coif5_Lo_D,coif5_len,coif5_Hi_D,coif5_len,coeff,de_level);
						WaveReconstruct(signal_des,signal_len,coif5_Lo_R,coif5_len,coif5_Hi_R,coif5_len,coeff,recon,'a',de_level);
						des = recon[0].capp[_shift];
						break;
					}
				default:  //disable filter
					{
						des = da;
						break;
					}
				}
				//select data in the middle of the signal
				//for (int i=_shift;i<_shift+_step;i++)
				//des = recon[0].capp[_shift];
				
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
					peak_delay = 100;
				else
					peak_delay++;
				
				if (signal_buf4[0]>=peak*4/5)
					peak_flag1 = 1;
				else
					peak_flag1 = 0;
				if (signal_buf4[1]>=peak*4/5)
					peak_flag2 = 1;
				else
					peak_flag2 = 0;
				//detect a peak here
				if((peak_flag2==1)&(peak_flag1==0))
				{
					//find last peak distance: if the distance larger than 30 point, then output a peak 
					if (peak_delay>30)
					{
						//ppp_cnt++;
						peak_delay = 0;
						
						//ouput a value
						memset(buf2,0,10*sizeof(char));
						//gcvt(1000,10,buf2);
						//write(tty_fd2,buf2,10);
						//write(tty_fd2,&char_a,1); //write a spliter character 'a'
						//printf("0\n");
					}
				}
				
				//ouput processed data
				memset(buf2,0,10*sizeof(char));
				gcvt(des,10,buf2);   //convert float number to char* 
				write(tty_fd2,buf2,10);
				write(tty_fd2,&char_a,1); //write a spliter character 'a'

			}
			//capture char in number range
			else if ( (c<=0x39) & (c>=0x30) )
			{
				buf[buf_cnt] = c;
				
				//add index
				++buf_cnt;
				//if index exceed the size of buf size, clear buf and receive again
				if (buf_cnt>10) //boundary is 10
				{
					memset(buf,0,10*sizeof(char));
					buf_cnt = 0;
				}
			}
			//null char
			else
				;
		}
	}

	//close port
    close(tty_fd);
	close(tty_fd2);
    tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
	
    return 0;
}











