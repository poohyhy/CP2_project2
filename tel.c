#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

int main(void)
{
	PHONE *list = (PHONE *)malloc(sizeof(PHONE) * 100);
	int count = 0;
	//실행되면 menu.c에서 선택을 입력받아 선택에 맞는 기능 실행
	while(1) {
		int input = menu();

		if (input == 0) {
			count = tel_read(list);
			tel_search(list, count);
		}
		if (input == 1) {
			count = tel_read(list);
			tel_add(list, count);
		}
		if (input == 2) {
			count = tel_read(list);
			tel_del(list, count);
		}
		if (input == 3) {
			count = tel_read(list);
			tel_up(list, count);
		}
		if (input == 4) {
			count = tel_read(list);
			tel_print(list, count);
		}
		if (input ==  5) {
			break;
		}
	}
	endwin();
	return 0;
}
