//
//  main.c
//  makeSearchKeys
//
//  Created by Jonathan Gilmour on 3/09/13.
//  Copyright (c) 2013 Jonathan Gilmour. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char * argv[])
{
	int number = atoi(argv[1]);
	int max = atoi(argv[2]);
	int x;
	int y;
	
	for(x = 0; x < number; x++) {
		srand((unsigned int)clock());
		for(y = 0; y < 1000; y++);
		printf("%d\n", rand()%max);
	}
	
	return 0;
}

