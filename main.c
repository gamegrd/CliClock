#include <stdio.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include <mmsystem.h>
DWORD tgt[3];//分别存储3个时间数据 
time_t t,x;
HANDLE std;
COORD xy={0,0};
struct tm *lt;

void delay(int t,int x){//负责更新时间 
	tgt[x]=(tgt[x]?tgt[x]:timeGetTime())+t;
}
void showTime(){//渲染输出 
	SetConsoleCursorPosition(std,xy);
    struct tm *lt;
    lt = localtime(&x);//转为时间结构。
    //2019-11-6 16:07:29 
    printf("%d-%d-%d %02d:%02d:%02d\n",lt->tm_year+1900, lt->tm_mon+1,
			lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//输出结果
	delay(1,0);
}
void getTime(){
	time(&t);//获取Unix时间戳。
    lt = localtime(&t);//转为时间结构。
	x=t-lt->tm_sec;
	delay(1000,1);
}
void change(){//负责累加计数 
	if(x<t){
		x++;
	}
	delay(8,2);
}
void setup(){//一些初始化内容 
	std=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(std, &cci);
    SetConsoleTitleA("CliClock V0.01  -by JuncoJet");
}
void loop(){//负责时间片轮转 
	DWORD m=timeGetTime();
	if(m>=tgt[0]||!tgt[0])showTime();
	if(m>=tgt[1]||!tgt[1])getTime();
	if(m>=tgt[2]||!tgt[2])change();
	Sleep(1);
}
int main(){
	setup();
	for(;;){
		loop();
	}
}
