#include <stdio.h>
#include <stdlib.h>

int main() {
	char s[101];

	printf("%s\n", "���ڸ� �Է��ϼ���(100�� �̳�).");
	scanf("%s", s);
	printf("�Էµ� ���ڴ� %s�Դϴ�.\n", s);

	system("pause"); // keep terminal open
	return 0;
}
