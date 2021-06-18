#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

int main(void)
{
	int count = 0;
	//실행되면 menu.c에서 선택을 입력받아 선택에 맞는 기능 실행
	while(1) {
		int input = menu();

		if (input == 0) {
			#include "read.h"
			tel_search(list, count);
		}
		if (input == 1) {
			#include "read.h"
			tel_add(list, count);
		}
		if (input == 2) {
			#include "read.h"
			tel_del(list, count);
		}
		if (input == 3) {
			#include "read.h"
			tel_up(list, count);
		}
		if (input == 4) {
			#include "read.h"
			tel_print(list, count);
		}
		if (input ==  5) {
			break;
		}
	}
	endwin();
	return 0;
}
