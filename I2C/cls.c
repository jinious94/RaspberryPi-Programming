#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define DEVICE_ID 0x48

int main(){
	int fd = wiringPiI2CSetup(DEVICE_ID); // Device 초기화
	int v1, v2;
	int x, y;
	
	printf("\033[2J"); // 화면 클리어
	//printf("\033[1;1H"); // [y;xH ->> x: 1, y: 1 
	
	while(1) {	
		wiringPiI2CWrite(fd, 0);// 채널을 변경. ch00 (조도센서)
		wiringPiI2CRead(fd);
		x = (wiringPiI2CRead(fd) * 80) / 255; // 이전 채널의 값을 초기화
		delay(100);
					
		wiringPiI2CWrite(fd, 1);
		wiringPiI2CRead(fd);
		y = (wiringPiI2CRead(fd) * 24) / 255;
		delay(100);
		
		printf("\033[%d;%dH(%d, %d) \n", y, x, x, y);
		delay(100);
	}
	
	return 0;
}
