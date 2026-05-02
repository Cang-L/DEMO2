#include<graphics.h>
#include<string>
#include<dwmapi.h>
#include "player.h"
#include "animation.h"
#include "playeranime.h"
#include "handleinput.h"
#include "slime.h"

#pragma comment(lib, "dwmapi.lib")

const double TARGET_FPS = 60.0;
const double TIME_STEP = 1.0 / TARGET_FPS;

int main()
{
	LARGE_INTEGER freq, last, now;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&last);
	initgraph(800, 600);
	BeginBatchDraw();

	bool running = true;

	ExMessage msg;

	IMAGE img_background;

	double accumulator = 0.0;//加载动画

	loadimage(&img_background, _T("img/background.png"));

	Player* pPlayer = new Player(330, GROUND_Y);
	while (running)
	{
		QueryPerformanceCounter(&now);
		double frame_time = (double)(now.QuadPart - last.QuadPart) / freq.QuadPart;
		last = now;
		if (frame_time > 0.033)
		{
			frame_time = 0.033;
		}
		accumulator += frame_time;
		while (accumulator >= TIME_STEP)
		{
			handleInput(pPlayer);
			pPlayer->PhyUpdate((float)TIME_STEP);
			updateSlime((float)TIME_STEP);
			for (std::unique_ptr<Slime>& s : slime)
			{
				s->Move(*pPlayer, (float)TIME_STEP);
			}
			accumulator -= TIME_STEP;
		}

		while (peekmessage(&msg))
		{
			break;
		}

		cleardevice();

        putimage(0, 0, &img_background);

		int delta_ms = (int)(frame_time * 1000);
        delta_ms_copy = delta_ms;

		AnimeUpdate(pPlayer);
		for (std::unique_ptr<Slime>& s : slime)
		{
			s->showSlime();
		}
		FlushBatchDraw();

		DwmFlush();//垂直同步
	}

	delete pPlayer;
	pPlayer = nullptr;

	EndBatchDraw();

	return 0;
}
