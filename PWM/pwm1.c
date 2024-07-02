#include <stdio.h>
#include <wiringPi.h>

#define wPi_22 22

int main(int n, char* s[]) {
	wiringPiSetup(); // wPi pin number
	pinMode(wPi_22, OUTPUT);
	int dutyRate, dutyRateHigh, dutyRateLow, period = 10;

	
	if (n < 2) {
		printf("usage : pwm1 [duty_rate(%%)] [[period]] \n\n");
		return 1;
	} 
	
	// s[1]을 %d의 포멧으로 읽어서 dutyRate 변수에 저장하라
	sscanf(s[1], "%d", &dutyRate); // 70	
	if (n > 2) sscanf(s[2], "%d", &period);
	

	dutyRateHigh = (dutyRate * period) / 100; // 7
	dutyRateLow = period - dutyRateHigh; // 3    

	for (int i = 0; i < 500; i++){
		digitalWrite(wPi_22, 1);
		delay(dutyRateHigh);
		digitalWrite(wPi_22, 0);;
		delay(dutyRateLow);	
	}

	return 0;
}
