#include <stdio.h>
#include <string.h>

_Bool isPalindrome(char *s)
{
	int len = strlen(s);
	int front = 0, rear = len - 1, fchar, rchar;
	while (front < rear)
	{
		// printf("front = %d, rear = %d, s[%d] = %c, s[%d] = %c, ", front, rear, front, s[front], rear, s[rear]);
		fchar = (s[front] - ' ') + 32;
		rchar = (s[rear] - ' ') + 32;
		// printf("fchar = %d, rchar = %d\n", fchar, rchar);

		while (front < rear && !((fchar < 91 && fchar > 64) || (fchar < 123 && fchar > 96) || (fchar < 58 && fchar > 47)))
		{
			// printf("front: \'%c\'is passed, check \'%c\'\n", s[front], s[front + 1]);
			fchar = (s[++front] - ' ') + 32;
		}
		while (front < rear && !((rchar < 91 && rchar > 64) || (rchar < 123 && rchar > 96) || (rchar < 58 && rchar > 47)))
		{
			// printf("rear: \'%c\'is passed, check \'%c\'\n", s[rear], s[rear - 1]);
			rchar = (s[--rear] - ' ') + 32;
		}

		if (fchar < 91 && fchar > 64)
		{
			fchar += 32;
		}
		if (rchar < 91 && rchar > 64)
		{
			rchar += 32;
		}

		if ((front <= rear) && (fchar != rchar))
			return 0;
		front++;
		rear--;
	}
	// printf("last state: front %d, rear = %d, fchar = %d, rchar = %d\n", front, rear, fchar, rchar);
	return 1;
}

int main()
{
	char s[100] = "ab2a";
	if (isPalindrome(s))
		puts("true");
	else
		puts("false");

	return 0;
}