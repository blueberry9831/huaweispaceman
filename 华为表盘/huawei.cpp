#include<stdio.h>
#include<graphics.h>   //easyx ͼ�ο�ͷ�ļ�
#include<string.h>
#include<time.h>
#include <conio.h>

#pragma comment(lib, "Winmm.lib")


/*
   1.�����ı�����ʽ
   2.����Ч��
   3.��ʾ��̬ʱ�� 
   4.��װ��������
*/

#define WIN_SIZE 500//���ڴ�С
#define WIN_HALF (WIN_SIZE/2)//���ڵ�һ��

IMAGE spaceMan[59];//̫����ͼƬ����
IMAGE Other[6];
void loadImg()
{
	//����ͼƬ  [2~60]
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
	static DWORD t1 = clock();//ֻ��ʼ��һ��
	DWORD t2 = clock();//��ȡ�������е����øú����������ĺ�����
	//��ͼƬ�����������
	static int i = 0;
    //Sleep(20);//�ó������ߣ����������������ӳ�
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
	settextcolor(BLACK);//����������ʽ
	setTextStyle(70, 28, "Arial");
	//��ʾ��̬ʱ�� 
	//��ȡ��ǰϵͳʱ��  time.h
	time_t curTime = time(NULL);
	//printf("%11d\n", curTime);
	struct tm* humanTime = localtime(&curTime);
	//printf("��%d %d-%d\n", humanTime->tm_wday,humanTime->tm_mon+1, humanTime->tm_mday);
	char buf[40] = { 0 };
	sprintf_s(buf, "%d:%d", humanTime->tm_hour, humanTime->tm_min);
	outtextxy(WIN_HALF - 80, WIN_HALF - 115, buf);
}
void second()
{
	settextcolor(BLACK);//����������ʽ
	setTextStyle(20, 12, "Arial");
	time_t curTime = time(NULL);
	struct tm* humanTime = localtime(&curTime);
	char buf[40] = { 0 };
	sprintf_s(buf, "%d", humanTime->tm_sec);
	outtextxy(335, 175, buf);
}
//�����������
void gameDraw()
{
	settextcolor(BLACK);//����������ʽ
	setTextStyle(55, 23, "Arial");

	setbkcolor(RGB(223, 230, 240));//���ñ�����ɫ
	cleardevice();//��ջ�ͼ�豸
	setbkmode(TRANSPARENT);//���ñ���Ϊ͸��
    //���Ʊ���
	setlinecolor(RGB(68, 68, 68));//������ɫ
	setlinestyle(PS_SOLID, 40);//�����Ŀ��
	setfillcolor(RGB(223, 230, 240));
	fillellipse(0, 0, WIN_SIZE, WIN_SIZE);
	//��������
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 4);
	//����
	line(WIN_HALF - 30, 20, WIN_HALF - 30, 130);
	line(WIN_HALF + 80, WIN_HALF + 120, WIN_HALF + 80, WIN_HALF + 170);
	line(WIN_HALF - 50, WIN_HALF + 170, WIN_HALF - 50, WIN_HALF + 225);
	//����
	line(WIN_HALF - 195, WIN_HALF - 120, WIN_HALF + 195, WIN_HALF - 120);
	line(WIN_HALF - 195, WIN_HALF + 120, WIN_HALF + 195, WIN_HALF + 120);
	line(WIN_HALF - 50, WIN_HALF + 170, WIN_HALF + 80, WIN_HALF + 170);

	hour();
	second();
}

void big()
{
	settextcolor(BLACK);//����������ʽ
	setTextStyle(35, 13, "Arial");

	outtextxy(100, 90, "90%");
	outtextxy(110, WIN_HALF + 130, "˯��");
	outtextxy(WIN_HALF - 50, WIN_HALF + 130, "6h30min");
	outtextxy(WIN_HALF + 100, WIN_HALF + 130, "����");
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
	outtextxy(WIN_HALF - 15, 40, "��������");
	outtextxy(WIN_HALF - 15, 67, "����   26��C");
	outtextxy(WIN_HALF - 15, 94, "22��C  16��C");
	outtextxy(123, WIN_HALF + 90, "67");
	outtextxy(WIN_HALF + 140, WIN_HALF + 55, "������");
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
	//����ͼ�δ���
	initgraph(500, 500/*, EW_SHOWCONSOLE*/);

	printf("hello world");//���������̨

	loadImg();

	BeginBatchDraw();//˫�����ͼ
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