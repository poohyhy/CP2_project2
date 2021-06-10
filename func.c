#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

// search
int tel_search(PHONE *list, int size) 
{
	int yMax, xMax; 
	char *input = (char *)malloc(sizeof(char) * 40);
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *searchwin = newwin(yMax-10, xMax-20, 2, 10);
	box(searchwin, 0, 0);

	refresh();
	wrefresh(searchwin);

	mvwscanw(searchwin, 1, 1, "%s", &input);
	int count = 0;
	// 각 PHONE구조체의 필드에서 입력된 문자열이 있는지 검사하여 있으면 출력하고 count 증가
	for(int i = 0; i < size; i++) {
		if (strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL ) {
			mvwprintw(searchwin, i, 2, "%d %s %s %s", count, 
				list[i].name, list[i].phone, list[i].memo);
		}
	}
	refresh();
	wrefresh(searchwin);
	getch();
	endwin();
	return count;
}

// add
/*
void tel_add(PHONE *list, int size) 
{	
	// 입력된 정보 확인, add 여부 확인
	char *name, *phone, *memo;

	int yMax, xMax; 
	char *input;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *addwin = newwin(yMax-10, xMax-20, 2, 10);
	box(addwin, 0, 0);

	refresh();
	wrefresh(addwin);

	printf("\n%s %s %s\n\nadd? [Y/N]: ", name, phone, memo);
	char ch = getchar();
	if (ch == 'Y') {
		// 배열의 끝 PHONE구조체에 입력된 정보 복사
		strcpy(list[size].name, name);
		strcpy(list[size].phone, phone);
		strcpy(list[size].memo, memo);
		// data.txt파일 쓰기 모드로 열기. 
		FILE *fp = fopen("data.txt", "w");
		// 각 구조체의 필드를 ":"를 구분자로 하여 한 줄로 합치고,
		// 이를 배열의 처음부터 다시 입력하고 파일에 덮어쓰기
		for(int i = 0; i < size+1; i++) {
			char *put = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
			strcpy(put, list[i].name);
			strcat(put, ":");
			strcat(put, list[i].phone);
			strcat(put, ":");
			strcat(put, list[i].memo);
			if(i == size) {
				strcat(put, "\n");
			}
			fputs(put, fp);
		}
		// 파일 닫기
		fclose(fp);
	}
}

// delete
void tel_del(PHONE *list, char *input, int size) 
{
	int arr[size]; // 검색된 구조체의 list내 인덱스를 저장할 배열
	int count = 0;
	// 입력받은 문자열이 있는 PHONE구조체 검색하고 출력
	for(int i = 0; i < size; i++) {
		if(strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL) {
			printf("%d %s %s %s", ++count, list[i].name, list[i].phone, list[i].memo);
			arr[count] = i;
		}
	}
	// 검색된 정보가 없을때
	if (count == 0) {
		printf("no match found\n");
	}
	else {
		// 검색되어 출력된 PHONE구조체 중 삭제할 구조체를 입력받음
		printf("\nwhich one? ");
		int ch;
		scanf("%d", &ch);
		// 선택된 구조체의 다음 인덱스부터 한칸씩 앞으로 복사하여 삭제
		for(int ans = arr[ch]; ans < size; ans++) {
			list[ans] = list[ans+1];
		}
		// data.txt에 변경된 리스트 덮어쓰기
		FILE *fp = fopen("data.txt", "w");
		for(int i = 0; i < size-1; i++) {
			char *put = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
			strcpy(put, list[i].name);
			strcat(put, ":");
			strcat(put, list[i].phone);
			strcat(put, ":");
			strcat(put, list[i].memo);
			fputs(put, fp);
		}
		fclose(fp);
	}
	endwin();
}

//update
void tel_update(PHONE *list, int size)
{

}
*/

// list

int cmpstr(void const *a, void const *b) 
{
    char const *aa = (char const *)a;
    char const *bb = (char const *)b;

    return strcmp(aa, bb);
}

void tel_print(PHONE *list, int size) 
{
	initscr();
	cbreak();
	noecho();
	refresh();

	int yMax, xMax; 
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *listwin = newwin(yMax-10, xMax-20, 2, 10);
	box(listwin, 0, 0);
	refresh();
	wrefresh(listwin);

	if (size == 1) {
		for(int i = 0; i < size; i++) {
			mvwprintw(listwin, i+1, 2, "%d %s %s %s", i+1, list[i].name, list[i].phone, list[i].memo);
		}
	}
	else if (size >= 2) {
		qsort(list, size, sizeof(PHONE), cmpstr);
		for(int i = 0; i < size; i++) {
			mvwprintw(listwin, i+1, 2, "%d %s %s %s", i+1, list[i].name, list[i].phone, list[i].memo);
		}	
	}
	refresh();
	wrefresh(listwin);
	getch();
	menu();
}

