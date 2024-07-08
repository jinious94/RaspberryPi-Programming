#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define wPi_Pin 23

int main(int n, char* s[]){
	wiringPiSetup(); // wPi pin number
	pinMode(wPi_Pin, OUTPUT);
	
	int dutyRate = 50, dutyRateHigh, period = 10;
	
	if (n < 2) {
		printf("usage : pwm1 [duty_rate(%%)] [[period]] \n\n");
		printf("		period = 10ms if empty \n\n");
		printf("default value : period = 10ms, duty rate = 50%%\n\n");
		return 1;
	}
	
	// s[1]을 %d의 포멧으로 읽어서 dutyRate 변수에 저장하라
	sscanf(s[1], "%d", &dutyRate); // 70	
	if (n > 2) sscanf(s[2], "%d", &period);

	dutyRateHigh = (dutyRate * period) / 100; // 7
	
	pwmSetMode(PWM_MODE_MS);
	softPwmCreate(wPi_Pin, dutyRateHigh, period);
	
	delay(5000);
	softPwmStop(wPi_Pin);
	
	return 0;
}
