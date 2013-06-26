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
course.  There is a demo code which is '[demo.c](demo.c)'.  You can just use the
'make' utility which will compile the codes according to the 'Makefile'.  Then
execute the program 'demo.bin' for demo.  I also use the program to test the
APIs I wrote working right or wrong.

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

This example demos the QUEUE behavior.
It will push elements into the QUEUE until the QUEUE is full.  Then pop an
elements from the QUEUE.  Meanwhile, it will print the status of the QUEUE for
each action.

Create a C file where the main function located.

```C
#include <stdio.h>
#include "datastructure.h"

#define BUFLEN 8

int main(void) {
    /* Have a queue of SDS structure. */
    SDS_QUEUE q;
    /* Define the length of the buffer going to be bound. */
    uint8_t len = BUFLEN;
    /* Have an integer buffer array going to be bound. */
    int elems[BUFLEN];
    int elem, *get = NULL;
	uint8_t err = 0;

    /* Initial the queue with assigned length and the buffer array. */
    SDSInitQueue(&q, len, elems);
    printf("The queue can have %d elements.\n", q.len);

    /* Push BUFLEN elements into the queue. */
    for (elem = 100; elem < (100 + BUFLEN); elem++) {
        /* Push an element into the queue. */
        SDSPush(&q, &elem, sizeof(int)); printf("Pushed an element.  ");
        /* Get next element from the queue. */
        get = SDSFront(&q, sizeof(int), &err); printf("Front queue:%d  ", *get);
        /* Get last element from the queue. */
        get = SDSBack(&q, sizeof(int), &err); printf("Back queue:%d\n", *get);
    }

    /* Pop an element from the queue. */
    SDSPop(&q); printf("Popped an element.  ");
    /* Get next element from the queue. */
    get = SDSFront(&q, sizeof(int), &err); printf("Front queue:%d  ", *get);
    /* Get last element from the queue. */
    get = SDSBack(&q, sizeof(int), &err); printf("Back queue:%d\n", *get);

    /* Test the queue is empty or not. */
    if(!SDSEmpty(&q))
		printf("The queue remians with %d elements.\n", SDSSize(&q));
	else
		printf("The queue is empty.\n");

    return 0;
}

```

License
-------

simple-data-structure's code uses the BSD license, see our ['LICENSE.md'](https://github.com/starnight/simple-data-structure/blob/master/LICENSE.md "LICENSE.md") file.
