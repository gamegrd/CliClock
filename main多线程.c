#include <stdio.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include <mmsystem.h>
DWORD tgt;
time_t t,x;
HANDLE std;
COORD xy={0,0};

void showTime(){
	SetConsoleCursorPosition(std,xy);
    struct tm *lt;
    lt = localtime(&x);//转为时间结构。
    //2019-11-6 16:07:29 
    printf("%d-%d-%d %02d:%02d:%02d\n",lt->tm_year+1900, lt->tm_mon+1,
			lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//输出结果
	Sleep(1);
}
void render(LPVOID param){
	for(;;){
		//这里是渲染算法
		showTime(); 
	}
}
void init(){
	std=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(std, &cci);
    SetConsoleTitleA("CliClock V0.01  -by JuncoJet");
	_beginthread(render,0,NULL);
}
void change(){
	tgt=timeGetTime();
	time(&t);//获取Unix时间戳。
    struct tm *lt;
    lt = localtime(&t);//转为时间结构。
	x=t-lt->tm_sec;
	for(int i=0;i<lt->tm_sec;i++){
		x++;
		Sleep(8);
	}
	for(;;)
		if(timeGetTime()<tgt+1000){
			Sleep(20);
		}else{
			break;
		}
}
int main(){
	init();
	for(;;){
		change();
	}
}
