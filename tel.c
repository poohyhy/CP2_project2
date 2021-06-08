#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tel.h"

int main(int argc, char *argv[])
{
	PHONE *list = (PHONE *)malloc(sizeof(PHONE) * 100); // PHONE 구조체 배열 동적으로 선언
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

	// 기본 작동
	if (argc == 1) {
		tel_how();
		return 0;
	}
	// command line args로 옵션 입력 시
	else if (argc > 1) {
		// "-a" 입력 시
		if (strcmp(argv[1], "-a") == 0) {
			tel_add(list, argv[2], argv[3], argv[4], count);
		}
		// "-d" 입력 시
		else if (strcmp(argv[1], "-d") == 0) {
			tel_del(list, argv[2], count);
		}
		// "-l" 입력 시	
		else if (strcmp(argv[1], "-l") == 0) {
			tel_print(list, count);
		}
		// 검색할 문자열 입력 시
		else if (argc == 2) {
			int c = tel_search(list, argv[1], count);
			if (c == 0) {
				printf("\nno match found.\n");
			}
			else {
				printf("\nmatch found.\n");
			}
		}
	}
	return 0;
}
