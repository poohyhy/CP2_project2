#include <ncurses.h>
#include <menu.h>
#include "tel.h"

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))
#define MAX_MENU	6

int menu(void)
{
	initscr();
	cbreak();
	noecho();

	int yMax, xMax; 
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *menuwin = newwin(8, xMax-85, 25, 5); 
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	keypad(menuwin, true);

	char *choices[MAX_MENU] = {"search", "add", "delete", "update", "show all", "quit"}; 
	int choice;
	int highlight = 0;

	while (1) {
		for (int i = 0; i < MAX_MENU; i++) {
			if (i == highlight)
				wattron(menuwin, A_REVERSE); 
			mvwprintw(menuwin, i+1, 1, choices[i]);
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch (choice) {
			case KEY_UP:
				if (highlight != 0)
					highlight--;
				break;
			case KEY_DOWN:
				if (highlight != MAX_MENU-1)
					highlight++;
				break;
			default:
				break;
		}
		if (choice == 10)
			break;
	}
	switch (highlight) {
		case 0:
			return 0;
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			endwin();
		default:
			return ERROR;
	}
}
