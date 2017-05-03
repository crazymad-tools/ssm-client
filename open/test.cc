/*********************************************************
 * Author           : none
 * Last modified    : 2017-05-03 19:02
 * Filename         : test.cc
 * Description      : 
 *********************************************************/

#include <stdio.h>
#include <unistd.h>

int main() {
	char a[3][10];
	sprintf(a[0], "1");
	sprintf(a[1], "11");
	sprintf(a[2], "Motor");
	printf("%s\t%s\t%s\n", a[0], a[1], a[2]);
	execl("open", "open", a[0], a[1], a[2], (char*)NULL);

	return 0;
}
