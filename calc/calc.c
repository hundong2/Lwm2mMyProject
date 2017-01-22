#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calcurator()
{
}
int main()
{

	int i;
	char *a[10];
	a[0] = "100";
	a[1] = "+";
	a[2] = "20";
	a[3] = "*";
	a[4] = "100";
	a[10] = "sfdfsfs";
	a[11] = "sdfsdffsf";
	for( i = 0 ; i < 6 ; i++)
		printf("%d %s \n" ,sizeof(a[i]), a[i]);
}
