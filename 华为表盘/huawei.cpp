#include<stdio.h>
#include<graphics.h>   //easyx 图形库头文件
#include<string.h>
#include<time.h>
#include <conio.h>

#pragma comment(lib, "Winmm.lib")


/*
   1.调好文本的样式
   2.动画效果
   3.显示动态时间 
   4.组装整个表盘
*/

#define WIN_SIZE 500//窗口大小
#define WIN_HALF (WIN_SIZE/2)//窗口的一半

IMAGE spaceMan[59];//太空人图片数组
IMAGE Other[6];
void loadImg()
{
	//加载图片  [2~60]
	char fileName[50] = { 0 };
	for (int i = 0; i < 59; i++)
	{
		sprintf_s(fileName, "./images/human (%d).jpg", i + 2);
		loadimage(spaceMan + i, fileName, 140, 130);
	}
}
void setTextStyle(int h,int w,const char *faceName)
{
	LOGFONT f = { 0 };
	f.lfHeight = h;
	f.lfWidth = w;
	strcpy(f.lfFaceName, faceName);
	settextstyle(&f);
}

void watchpicture()
{
	loadimage(Other, "./images/other6.png", 50, 50);
	putimage(165, 50, Other);
	loadimage(Other, "./images/other2.png", 50, 50);
	putimage(WIN_HALF + 100, 66, Other);
	loadimage(Other, "./images/other1.png", 40, 40);
	putimage(75, WIN_HALF + 80, Other);
	loadimage(Other, "./images/other3.png", 45, 45);
	putimage(WIN_HALF + 80, WIN_HALF + 80, Other);
}

void animation()
{
	static DWORD t1 = clock();//只初始化一次
	DWORD t2 = clock();//获取程序运行到调用该函数所经过的毫秒数
	//把图片输出到窗口上
	static int i = 0;
    //Sleep(20);//让程序休眠，它会让整个程序都延迟
	if (t2 - t1 > 20)
	{
		i = (i + 1) % 59;
		t1 = t2;
	}
	/*i++;
	if (i > 59)
	{
		i = 0;
	}*/
	putimage(WIN_HALF - 60, WIN_HALF - 50, spaceMan + i);
	watchpicture();
} 
void hour()
{
	settextcolor(BLACK);//设置文字样式
	setTextStyle(70, 28, "Arial");
	//显示动态时间 
	//获取当前系统时间  time.h
	time_t curTime = time(NULL);
	//printf("%11d\n", curTime);
	struct tm* humanTime = localtime(&curTime);
	//printf("周%d %d-%d\n", humanTime->tm_wday,humanTime->tm_mon+1, humanTime->tm_mday);
	char buf[40] = { 0 };
	sprintf_s(buf, "%d:%d", humanTime->tm_hour, humanTime->tm_min);
	outtextxy(WIN_HALF - 80, WIN_HALF - 115, buf);
}
void second()
{
	settextcolor(BLACK);//设置文字样式
	setTextStyle(20, 12, "Arial");
	time_t curTime = time(NULL);
	struct tm* humanTime = localtime(&curTime);
	char buf[40] = { 0 };
	sprintf_s(buf, "%d", humanTime->tm_sec);
	outtextxy(335, 175, buf);
}
//其他界面绘制
void gameDraw()
{
	settextcolor(BLACK);//设置文字样式
	setTextStyle(55, 23, "Arial");

	setbkcolor(RGB(223, 230, 240));//设置背景颜色
	cleardevice();//清空绘图设备
	setbkmode(TRANSPARENT);//设置背景为透明
    //绘制表盘
	setlinecolor(RGB(68, 68, 68));//线条颜色
	setlinestyle(PS_SOLID, 40);//线条的宽度
	setfillcolor(RGB(223, 230, 240));
	fillellipse(0, 0, WIN_SIZE, WIN_SIZE);
	//绘制线条
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 4);
	//竖线
	line(WIN_HALF - 30, 20, WIN_HALF - 30, 130);
	line(WIN_HALF + 80, WIN_HALF + 120, WIN_HALF + 80, WIN_HALF + 170);
	line(WIN_HALF - 50, WIN_HALF + 170, WIN_HALF - 50, WIN_HALF + 225);
	//横线
	line(WIN_HALF - 195, WIN_HALF - 120, WIN_HALF + 195, WIN_HALF - 120);
	line(WIN_HALF - 195, WIN_HALF + 120, WIN_HALF + 195, WIN_HALF + 120);
	line(WIN_HALF - 50, WIN_HALF + 170, WIN_HALF + 80, WIN_HALF + 170);

	hour();
	second();
}

void big()
{
	settextcolor(BLACK);//设置文字样式
	setTextStyle(35, 13, "Arial");

	outtextxy(100, 90, "90%");
	outtextxy(110, WIN_HALF + 130, "睡眠");
	outtextxy(WIN_HALF - 50, WIN_HALF + 130, "6h30min");
	outtextxy(WIN_HALF + 100, WIN_HALF + 130, "距离");
	outtextxy(WIN_HALF - 30, WIN_HALF + 180, "3.23km");

}

void smell()
{
	settextcolor(BLACK);
	setTextStyle(23, 9, "Arial");
	outtextxy(75, WIN_HALF + 58, "66-120");
}

void watchnumber()
{
	big();
	smell();
	settextcolor(BLACK);
	setTextStyle(25, 10, "Arial");
	outtextxy(WIN_HALF - 15, 40, "空气优质");
	outtextxy(WIN_HALF - 15, 67, "晴天   26°C");
	outtextxy(WIN_HALF - 15, 94, "22°C  16°C");
	outtextxy(123, WIN_HALF + 90, "67");
	outtextxy(WIN_HALF + 140, WIN_HALF + 55, "星期五");
	outtextxy(WIN_HALF + 140, WIN_HALF + 75, "04-15");
	outtextxy(WIN_HALF + 140, WIN_HALF + 95, "8848");
}
void openmusic()
{
	mciSendString(_T("open ./images/music.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
}
int main()
{
	//创建图形窗口
	initgraph(500, 500/*, EW_SHOWCONSOLE*/);

	printf("hello world");//输出到控制台

	loadImg();

	BeginBatchDraw();//双缓冲绘图
	while (true)
	{
		gameDraw();
        animation();
		watchnumber();
		openmusic();

		FlushBatchDraw();
	}
	
	getchar();
	return 0;
}