#include "TimeControl.h"
#include <time.h>

//timeControl_startTime == ó�� ���� �� ����, �ٷ� �� �ð�
//timeControl_currentTime == timeControl_startTime�� ������ ���Ŀ�,  ���α׷��� �� ���� ���� �� ������ �ð�. 
clock_t timeControl_startTime;
clock_t timeControl_currentTime;

int firstUpdate = 1;  // �� ù��°�� 1�μ�, Ʈ�簪�� ��ȯ�ϰ�, �� ���ĺ��ʹ� Ÿ����Ʈ�Ѿ�����Ʈ �Լ��� ���� 0�� ���� �ް� false�� ��ȯ�Ѵ�.
float deltaTime = 0.0f;

// 1000 / 60 (ms)  �� 166 �и�������. 
const int FRAME_PER_SECOND = 60;


// ù��° ���࿡�� ������ Ʈ�縦 ��ȯ�ؼ� �ѹ� ����ǵ��� �����. (winmain�� while�� ����)
// ù��° ������ ������ �κп���, firstUpdate�� false�� ��ȯ�ϵ��� �����.
// ù��° ������ʹ� lasttime�� ù �� �ð��� ��ϵǵ��� �Ѵ�.
int TimeControl_UpdateTime()
{
	float FRAME_PERIOD = 1000.0f / (float)FRAME_PER_SECOND;


	if (firstUpdate == 1)
	{
		timeControl_startTime = clock();

		firstUpdate = 0;

		return 1;  // Ʈ�簪�� ��ȯ
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


//ó���� �Լ��� �ҷ��� �� �ð���, �� ������ �ҷ��� ���� �ð� ����
float TimeControl_DeltaTime()
{
	return deltaTime;
}


	//clock_t start, finish;
	//double duration;

	//start = clock(); // �������� �ð�
	////Algorithm...
	////...
	////...
	//finish = clock(); // �������� �ð�
	//duration = (double)(finish - start) / CLOCKS_PER_SEC; // (�������� �ð� - �������� �ð�)/1000
	//printf("%f�� �Դϴ�.", duration);