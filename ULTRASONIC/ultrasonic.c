#include <stdio.h>
#include <wiringPi.h>

#define TRIGGER 8 // 라즈베리파이 물리적 번호는 3, wPi 번호는 8
#define ECHO 9 // 라즈베리파이 물리적 번호는 5, wPi 번호는 9

extern double calculateDist();

// argv는 포인터 배열로
// 배열의 각 요소는 문자열의 주소를 가리키는 포인터
int main(int argc, char* argv[]) {
	wiringPiSetup(); // wPi 체계를 사용하겠다는 선언
	
	pinMode(TRIGGER, OUTPUT); // TRIGGER(8번 핀)는 OUTPUT
	pinMode(ECHO, INPUT); // ECHO(9번 핀)는 INPUT
	
	double dist;
	
	for(;;) {
		dist = calculateDist();
		printf("Distance : %f(cm) \n", dist); // cm 단위의 거리
		delay(500);
	}
	
	
	
	return 0;
}
