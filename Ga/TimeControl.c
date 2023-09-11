#include "TimeControl.h"
#include <time.h>

//timeControl_startTime == 처음 동작 할 때의, 바로 그 시간
//timeControl_currentTime == timeControl_startTime이 측정된 이후에,  프로그램이 한 바퀴 동작 후 측정된 시간. 
clock_t timeControl_startTime;
clock_t timeControl_currentTime;

int firstUpdate = 1;  // 맨 첫번째만 1로서, 트루값을 반환하고, 그 이후부터는 타임컨트롤업데이트 함수에 따라 0의 값을 받고 false를 반환한다.
float deltaTime = 0.0f;

// 1000 / 60 (ms)  약 166 밀리세컨드. 
const int FRAME_PER_SECOND = 60;


// 첫번째 실행에는 무조건 트루를 반환해서 한번 실행되도록 만든다. (winmain의 while문 참고)
// 첫번째 실행의 마지막 부분에서, firstUpdate가 false를 반환하도록 만든다.
// 첫번째 실행부터는 lasttime이 첫 그 시간이 기록되도록 한다.
int TimeControl_UpdateTime()
{
	float FRAME_PERIOD = 1000.0f / (float)FRAME_PER_SECOND;


	if (firstUpdate == 1)
	{
		timeControl_startTime = clock();

		firstUpdate = 0;

		return 1;  // 트루값을 반환
	}

	else
	{
		timeControl_currentTime = clock();
		if ((timeControl_currentTime - timeControl_startTime) >= FRAME_PERIOD)
		{
			deltaTime = (timeControl_currentTime - timeControl_startTime) / 1000.0f;
			timeControl_startTime = timeControl_currentTime;
			return 1;
		}
	
		else
		{
			return 0;
		}
	
	}

}


//처음에 함수가 불렸을 때 시간과, 그 다음에 불렸을 때의 시간 차이
float TimeControl_DeltaTime()
{
	return deltaTime;
}


	//clock_t start, finish;
	//double duration;

	//start = clock(); // 시작지점 시간
	////Algorithm...
	////...
	////...
	//finish = clock(); // 종료지점 시간
	//duration = (double)(finish - start) / CLOCKS_PER_SEC; // (종료지점 시간 - 시작지점 시간)/1000
	//printf("%f초 입니다.", duration);