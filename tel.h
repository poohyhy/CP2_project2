#define MAX_PHONE_SIZE 100

// PHONE 구조체
typedef struct PHONE {
	char name[30];
	char phone[20];
	char memo[40];
} PHONE;

void tel_how();
int tel_search(PHONE *list, char *input, int size); 
void tel_add(PHONE *list, char *name, char *phone, char *memo, int size);
void tel_del(PHONE *list, char *input, int size);
void tel_print(PHONE *list, int size);
void tel_update(PHONE *list, char *name, char *phone, char *memo, int size);