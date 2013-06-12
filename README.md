Simple Data Structure
=====================

It is a simple data structure library which provides QUEUE, STACK and RING 
(Circular Buffer) APIs.

Have the code
-------------

You can have it from the Github: [https://github.com/starnight/simple-data-structure](https://github.com/starnight/simple-data-structure, "Simple Date Sturcture")

Or, clone the source code from Github.

```
git clone git://github.com/starnight/simple-data-structure.git
```

Demo usage
----------

Before compile this library, you must have the compiler, for example GCC, of
course.  There is a demo code which is 'demo.c'.  You can just use the 'make'
utility which will compile the codes according to the 'Makefile'.  Then execute
the program 'demo.bin' for demo.  I also use the program to test the APIs I
wrote working right or wrong.

```
$ make
$ ./demo.bin
```

The program will do the demo three rounds.
The first round tests the QUEUE.
Second round tests the STACK.
Third round tests the RING.

Quick Start
-----------

This example is first round of codes in 'demo.c' which tests the QUEUE behavior.
It will push elements into the QUEUE until the QUEUE is full.  Then enumerates
the elements in the QUEUE to show the values.  Finally, pop all the elements in
the QUEUE.

Create a C file where the main function located.

```
#include <stdio.h>
#include "datastructure.h"

#define BUFLEN	8;

int main (void) {
	/* Have a buffer of the queue. */
	int8_t buf[BUFLEN];
	/* Have a queue. */
	SDS_QUEUE q;

	uint8_t elem = 0;
	int i = 0;
	uint8_t res;

	printf("Queue demo started!\n");
	
	/* Initial the queue. */
	SDSInitQueue(&q, BUFLEN, buf);
	/*Have the size of the queue. */
	printf("The length of the queue is %d.\n", (int)SDSSize(&q));
	/* Check the queue is empty. */
	printf("The queue is %sempty.\n", (SDSEmpty(&q) ? "not ":""));

	do {
		printf("inpos=%d outpos=%d ", q.inpos, q.outpos);
		/* Push an element into the queue. */
		elem = i*2;
		res = SDSPush(&q, &elem, sizeof(elem));
		i++;
		printf("res=%d ", res);
		if(res == SDS_OK) {
			printf("Push an element: %d. ", elem);
			SDSFront(&q, &elem, sizeof(elem));
			printf("Front element: %d. ", elem);
			SDSBack(&q, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The queue remains %d elements.\n", SDSEmpty(&q));

	for(i = 0; i < q.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	/* Enumerate the queue elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d ", q.inpos, q.outpos);
		SDSFront(&q, &elem, sizeof(elem));
		res = SDSPop(&q);
		printf("res=%d ", res);
		if(res == SDS_OK) {
			printf("Pop an element: %d. ", elem);
			SDSFront(&q, &elem, sizeof(elem));
			printf("Front element: %d. ", elem);
			SDSBack(&q, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The queue remains %d elements.\n", SDSEmpty(&q));
}
```

License
-------

simple-data-structure's code uses the BSD license, see our ['LICENSE.md'](https://github.com/starnight/simple-data-structure/blob/master/LICENSE.md "LICENSE.md") file.
