#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

_Bool isIsomorphic(char *s, char *t)
{
	int len = strlen(s);
	// if (len != strlen(t))
	// 	return 0;

	int8_t *sbuffer = (int8_t *)calloc(98, sizeof(int8_t)); // 128
	int8_t *tbuffer = (int8_t *)calloc(98, sizeof(int8_t)); // 128
	for (int i = 0; i < len; i++)
	{
		int8_t stmp = s[i] - ' '; // + 32;
		int8_t ttmp = t[i] - ' '; // + 32;
		// printf("s[%d] = \'%c\' = %d, sbuffer[\'%c\'] = %d\n", i, s[i], stmp, s[i], sbuffer[stmp]);
		// printf("t[%d] = \'%c\' = %d, tbuffer[\'%c\'] = %d\n", i, t[i], ttmp, t[i], tbuffer[ttmp]);
		if (sbuffer[stmp] == 0 && tbuffer[ttmp] == 0)
		{
			sbuffer[stmp] = ttmp;
			tbuffer[ttmp] = stmp;
			// printf("---------------> sbuffer[\'%c\'] = %d, tbuffer[\'%c\'] = %d\n", stmp + ' ' - 32, ttmp, ttmp + ' ' - 32, stmp);
		}
		else if (sbuffer[stmp] != ttmp || tbuffer[ttmp] != stmp)
			return 0;
	}

	free(sbuffer);
	free(tbuffer);
	return 1;
}

int main()
{
	char s[100] = "p";
	char t[100] = "t";
	s[strlen(s)] = '\0';
	t[strlen(t)] = '\0';
	if (isIsomorphic(s, t))
		puts("ture");
	else
		puts("false");
	return 0;
}