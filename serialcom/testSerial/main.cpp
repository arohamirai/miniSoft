
/*串口通信相关头文件*/
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include "math.h"
#include <stdlib.h>  //strtod()

#define max_buffer_size 100 //定义缓冲区最大宽度

using namespace std;

int fd; //定义设备文件描述符

/******************************函数原型声明*****************************/
int open_serial(int k); //打开串口

//串口通信配置函数（后续可将参数改为可扩展形式）
bool serial_setup(int k);

bool send_order_v(float speed);

int main(int argc, char **argv) {
    serial_setup(0);
    open_serial(0);
    
    while(1)
    {
      send_order_v(-2.897);
    }

    return 0;
}

/***************************打开串口函数定义*****************************/
int open_serial(int k)
{
    if(k==0) //串口选择
    {
        fd = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY); //读写方式打开串口
        perror("Open /dev/ttyUSB0");
    }
    else if(k==1)
    {
        fd = open("/dev/ttyUSB1",O_RDWR|O_NOCTTY); //读写方式打开串口
        perror("Open /dev/ttyUSB1");
    }
    else
    {
        printf("Please choice the number of serials");
    }

    if(fd == -1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/******************************发送V指令********************************/
bool send_order_v(float speed)
{
    char sbuf[9];
    
    // 将3个float类型的数据转为12个char类型的数据
    union floatdata
    {
        float f_data;
        unsigned char c_data[4];
    }temp;
   
    temp.f_data = speed;

    sbuf[0] = '\r';
    sbuf[1] = '\n';
    for(int i=0;i<4;i++)
    {
        sbuf[i+2] = temp.c_data[i];
    }
    sbuf[6] = '\n';
    sbuf[7] = '\r';
    sbuf[8] = '\0';

    int retv;

    //int length = sizeof(sbuf); //发送缓冲区数据宽度,这个函数返回的是整个数组的长度

    retv = write(fd,sbuf,8); //发送数据
    
    if(retv == -1)
    {
        printf("ttyUSB0 write failed!\n");
        perror("write failed!");
    }
    else
    {
       printf("%d\n" , retv);
    }

    return true;
}

/******************************串口通信配置函数*******************************/
bool serial_setup(int k)
{
    struct termios option;

    open_serial(k); //打开串口0

    printf("Ready for sending data...\n"); //开始准备发送数据
    tcgetattr(fd,&option);
    cfmakeraw(&option);

    cfsetispeed(&option,B115200); //设置波特率为115200bps
    cfsetospeed(&option,B115200);

    tcsetattr(fd, TCSANOW, &option);

    return true;
}

