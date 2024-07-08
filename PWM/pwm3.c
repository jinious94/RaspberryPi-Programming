#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define wPi_PWM1 23

int PSC = 19; // Prescaler: ~1MHz
int RANGE = 100;
int DUTY = 50 / 2; // 50

enum {DO = 0, Do, RE, Re, MI, FA, Fa, SL, Sl, LA, La, CI};
int pitch[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
int range[12];
int song[] = {
	DO, DO, DO, DO, DO, MI, SL, SL, MI, DO, SL, SL, MI, SL, SL, MI, DO, DO, DO,
	SL, SL, MI, DO, SL, SL, SL, SL, SL, MI, DO, SL, SL, SL,
	SL, SL, MI, DO, SL, SL, SL, LA, SL, DO, SL, DO, SL, MI, RE, DO
	
};
int rythm[] = {
	4, 2, 2, 4, 4, 4, 2, 2, 4, 4, 2, 2, 4, 2, 2, 4, 4, 4, 8,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 8,
	4, 4, 4, 4, 2, 2, 2, 2, 8, 4, 4, 4, 4, 4, 4, 8
};

void calcRange() { // 계이름을 가지고 Range 값을 계산
	for (int i = 0; i < 12; i++) {
		range[i] = 19200000/(PSC * pitch[i]);
	}
}

void playMusic(int um, int rythm) {
	pwmSetClock(PSC);
	pwmSetRange(range[um]);
	pwmWrite(wPi_PWM1, range[um]/2);
	delay(rythm * 125);
}

int main() {
	wiringPiSetup();
	pinMode(wPi_PWM1, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	
	// 설정할게 크게 3가지
	// 19.2M/(19 * x(range)) = 10k(frequency)
	//pwmSetClock(PSC); // 클록을 얼마나 놓을건지 -> 위 식에서는 19
	//pwmSetRange(RANGE); // 위 식에서는 x값인 100
	//pwmWrite(wPi_PWM1, DUTY); // compare를 설정 -> 거의 대부분 RANGE의 50%
	calcRange();
	for (int i = 0; i < 49; i++) {
		playMusic(song[i], rythm[i]);
	}
	pinMode(wPi_PWM1, OUTPUT);
	
	return 0;
}
