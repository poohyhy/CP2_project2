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