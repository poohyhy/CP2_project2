#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

// search
int tel_search(PHONE *list, int size) 
{
	int yMax, xMax; 
	char input[80]; //= (char *)malloc(sizeof(char) * 40);
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *searchwin = newwin(yMax-10, xMax-20, 2, 10);
	box(searchwin, 0, 0);

	refresh();
	wrefresh(searchwin);
	mvwprintw(searchwin, 1, 2, "Enter string to search\n");
	echo();
	mvwscanw(searchwin, 2, 2, "%s", &input);
	int count = 0;
	// 각 PHONE구조체의 필드에서 입력된 문자열이 있는지 검사하여 있으면 출력하고 count 증가
	for(int i = 0; i < size; i++) {
		if (strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL ) {
			mvwprintw(searchwin, ++count+3, 3, "%d %s %s %s", count, 
				list[i].name, list[i].phone, list[i].memo);
		}
	}
	if (count == 0) {
		mvwprintw(searchwin, 3, 3,"no match");
	}
	mvwprintw(searchwin, 20, 3,"press any key to quit");
	refresh();
	wrefresh(searchwin);
	
	getch();
	endwin();
	return count;
}

// add

void tel_add(PHONE *list, int size) 
{	
	// 입력된 정보 확인, add 여부 확인
	char name[30], phone[20], memo[40];
	char Bool;

	int yMax, xMax; 
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *addwin = newwin(yMax-10, xMax-20, 2, 10);
	box(addwin, 0, 0);

	refresh();
	wrefresh(addwin);

	mvwprintw(addwin, 1, 2, "Enter name");
	echo();
	mvwscanw(addwin, 2, 2, "%s", &name);
	mvwprintw(addwin, 3, 2, "Enter phone");
	mvwscanw(addwin, 4, 2, "%s", &phone);
	mvwprintw(addwin, 5, 2, "Enter memo");
	mvwscanw(addwin, 6, 2, "%s", &memo);
	mvwprintw(addwin, 7, 2, "%s %s %s add? [Y/N]: ", name, phone, memo);
	mvwscanw(addwin, 8, 2, "%c", &Bool);
	if (Bool == 'Y') {
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
		mvwprintw(addwin, 10, 2, "Successfully added");
	}
	else {
		mvwprintw(addwin, 10, 2, "add canceled");
	}
	mvwprintw(addwin, 20, 3,"press any key to quit");
	refresh();
	wrefresh(addwin);
	noecho();
	
	getch();
	endwin();
}

//delete
void tel_del(PHONE *list, int size) 
{
	int arr[size]; // 검색된 구조체의 list내 인덱스를 저장할 배열
	int count = 0;
	char input[80];
	// 입력받은 문자열이 있는 PHONE구조체 검색하고 출력

	int yMax, xMax; 
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *delwin = newwin(yMax-10, xMax-20, 2, 10);
	box(delwin, 0, 0);

	refresh();
	wrefresh(delwin);

	mvwprintw(delwin, 1, 2, "Enter string to search");
	echo();
	mvwscanw(delwin, 2, 2, "%s", &input);

	for(int i = 0; i < size; i++) {
		if(strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL) {
			mvwprintw(delwin, ++count+3, 2, "%d %s %s %s", count, list[i].name, list[i].phone, list[i].memo);
			arr[count] = i;
		}
	}
	// 검색된 정보가 없을때
	if (count == 0) {
		mvwprintw(delwin, count+5, 2, "no match found");
	}
	else {
		// 검색되어 출력된 PHONE구조체 중 삭제할 구조체를 입력받음
		mvwprintw(delwin, count+5, 2, "which one?");
		int ch;
		echo();
		mvwscanw(delwin, count+6, 2, "%d", &ch);
		mvwprintw(delwin, count+7, 2, "delete? [Y/N]:");
		char Bool;
		mvwscanw(delwin, count+8, 2, "%c", &Bool);
		if (Bool == 'Y') {
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
			mvwprintw(delwin, count+10, 2, "Successfully deleted.");
		}
		else {
			mvwprintw(delwin, count+10, 2, "delete canceled.");
		}
	}
	mvwprintw(delwin, 20, 3,"press any key to quit");
	refresh();
	wrefresh(delwin);
	noecho();
	
	getch();
	endwin();
}

//update

void tel_up(PHONE *list, int size)
{
	char name[30], phone[20], memo[40];
	char Bool;
	char input[80];
	int arr[size];
	int count = 0;
	int yMax, xMax; 
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *upwin = newwin(yMax-10, xMax-20, 2, 10);
	box(upwin, 0, 0);

	refresh();
	wrefresh(upwin);

	mvwprintw(upwin, 1, 2, "Enter string to search");
	echo();
	mvwscanw(upwin, 2, 2, "%s", &input);
	for(int i = 0; i < size; i++) {
		if(strstr(list[i].name, input) != NULL||
			strstr(list[i].phone, input) != NULL ||
			strstr(list[i].memo, input) != NULL) {
			mvwprintw(upwin, ++count+3, 2, "%d %s %s %s", count, list[i].name, list[i].phone, list[i].memo);
			arr[count] = i;
		}
	}
	// 검색된 정보가 없을때
	
	if (count == 0) {
		mvwprintw(upwin, count+4, 2, "no match found");
	}

	else {
		// 검색되어 출력된 PHONE구조체 중 수정할 구조체를 입력받음
		mvwprintw(upwin, count+5, 2, "which one?");
		int ch;
		echo();
		mvwscanw(upwin, count+6, 2, "%d", &ch);
		int ans = arr[ch];

		mvwprintw(upwin, count+7, 2, "updating %s %s %s", list[ans].name, list[ans].phone, list[ans].memo);
		mvwprintw(upwin, count+9, 2, "Enter name");
		mvwscanw(upwin, count+10, 2, "%s", &name);
		mvwprintw(upwin, count+11, 2, "Enter phone");
		mvwscanw(upwin, count+12, 2, "%s", &phone);
		mvwprintw(upwin, count+13, 2, "Enter memo");
		mvwscanw(upwin, count+14, 2, "%s", &memo);
		for(int j = 0; j < 30; j++) {
			list[ans].name[j] = name[j];
		}
		for(int j = 0; j < 20; j++) {
			list[ans].phone[j] = phone[j];
		}
		for(int j = 0; j < 40; j++) {
			list[ans].memo[j] = memo[j];
		}
		mvwprintw(upwin, count+15, 2, "update? [Y/N]:");
		char Bool;
		mvwscanw(upwin, count+16, 2, "%c", &Bool);
		if(Bool == 'Y') {
			// data.txt에 변경된 리스트 덮어쓰기
			FILE *fp = fopen("data.txt", "w");
			for(int i = 0; i < size; i++) {
				char *put = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
				strcpy(put, list[i].name);
				strcat(put, ":");
				strcat(put, list[i].phone);
				strcat(put, ":");
				strcat(put, list[i].memo);
				if(i == ans) {
					strcat(put, "\n");
				}
				fputs(put, fp);
			}
			fclose(fp);
			mvwprintw(upwin, count+17, 2, "Successfully updated.");
		}
		else
			mvwprintw(upwin, count+17, 2, "update canceled.");
	}
	mvwprintw(upwin, 23, 3,"press any key to quit");
	refresh();
	wrefresh(upwin);
	noecho();
	
	getch();
	endwin();
}


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
	mvwprintw(listwin, 20, 3,"press any key to quit");
	refresh();
	wrefresh(listwin);
	
	getch();
	endwin();
}

int tel_read(PHONE *list) {
	int count = 0; // 저장된 요소의 개수
		// data.txt 파일 줄단위로 끝까지 읽어 ":"를 구분자로 하여 각 구조체의 필드 입력
	FILE *fp = fopen("data.txt", "r");
	while(!feof(fp)) {
		char *line = (char *)malloc(sizeof(char) * MAX_PHONE_SIZE);
		fgets(line, MAX_PHONE_SIZE, fp);
		// 빈 줄이 있으면 건너뛰기
		if (strcmp(line, "\0") == 0) {
			continue;
		}
		strcpy(list[count].name, strtok(line, ":"));
		strcpy(list[count].phone, strtok(NULL, ":"));
		strcpy(list[count].memo, strtok(NULL, ":"));
		count++;
	}
	fclose(fp);
	return count;
}
