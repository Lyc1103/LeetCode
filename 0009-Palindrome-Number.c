#include<stdio.h>
#include<stdlib.h>

_Bool isPalindrome(int x){
	if(x<0) return 0;
	int tmp = x, reflect = 0;
	while(tmp){
		reflect = reflect * 10 + tmp % 10;
		tmp = tmp / 10;
	}
	if(x == reflect) return 1;
	return 0;
}

int main(){
	int input = 101;
	if(isPalindrome(input)) printf("True\n");
	else printf("False\n");
	return 0;
}