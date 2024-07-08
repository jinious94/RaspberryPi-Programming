#include <wiringPi.h>
#include <stdio.h>

#define RED 8
#define GREEN 9
#define YELLOW 7
#define SWITCH 2
#define STOP_SWITCH 5

// 라즈베리파이에 있는 총 핀의 개수: 40
// 40개의 핀의 상태를 관리하기 위한 배열 선언
// 처음엔 모두 0으로 설정
int status[40];

int mode = 0;
int tm;
int interval = 0;

int flag = 1;

void toggle(int pin) {
	status[pin] = !status[pin];
	digitalWrite(pin, status[pin]);
}

void gpioisr() {
	if (++interval > 8) interval = 0;
	printf("GPIO interrupt occured...\n");
}

void gpiostop() {
	flag = 0;
	digitalWrite(RED, 0);
	digitalWrite(GREEN, 0);
	digitalWrite(YELLOW, 0);
	printf("GPIO stopped \n");
}

int main() {
	// wPi 체계의 핀넘버를 사용하겠다.
	wiringPiSetup();
	
	// 8, 9, 7 -> OUT, 2 -> IN
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(SWITCH, INPUT);
	pinMode(STOP_SWITCH, INPUT);
	
	wiringPiISR(SWITCH, INT_EDGE_FALLING, gpioisr);
	wiringPiISR(STOP_SWITCH, INT_EDGE_FALLING, gpiostop);
	

	while (flag) {
		tm = (9 - interval) * 100;
		if(mode) {
			toggle(RED); 
			delay(tm);
					
			toggle(GREEN); 
			delay(tm);
					
			toggle(YELLOW); 
			delay(tm);
		} else {
			toggle(YELLOW); 
			delay(tm);
					
			toggle(GREEN); 
			delay(tm);
					
			toggle(RED); 
			delay(tm);
		}

	}
	
	return 0;
}
