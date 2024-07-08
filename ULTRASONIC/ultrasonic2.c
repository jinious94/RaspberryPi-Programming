#include <stdio.h>
#include <wiringPi.h>

#define TRIGGER 8 // 라즈베리파이 물리적 번호는 3, wPi 번호는 8
#define ECHO 9 // 라즈베리파이 물리적 번호는 5, wPi 번호는 9


double calculateDist() {
	digitalWrite(TRIGGER, 1); // TRIGGER에서 1을 출력
	delayMicroseconds(10); // 10 마이크로초 지연 
	digitalWrite(TRIGGER, 0);
	delayMicroseconds(200);
	
	while(digitalRead(ECHO) != 1); // ECHO가 0일 때 -> ECHO가 1이 되는 순간 끝
	int t1 = micros(); // 현재의 시간을 마이크로초로 받아오기
	while(digitalRead(ECHO) != 0); // ECHO가 0이 되는 순간 끝
	int t2 = micros();
		
	return (t2 - t1) * 0.017; // (t2 - t1) * (340 / 1000000 / 2 * 100)
}

