#include "headers.h"

int main()
{
	bg_arr = (char **)malloc(123456 * sizeof(char *));
	c_dir = (char *)malloc(1024);
	current = (char *)malloc(1024);
	current[0] = '~';
	current[1] = '\0';
	track = 0;
	strcpy(c_dir, current);
	//work=0;
	while(1){
		prompt();
	}
}
