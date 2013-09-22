/*------------------------------------------------------------------------------
  Copyright (c) 2013 The Simple Data Structure Project. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be found
  in the LICENSE file.
------------------------------------------------------------------------------*/

#include <stdio.h>
#include "datastructure/datastructure.h"

#define BUFLEN	8

inline void showStatus(struct _SDS_BUFFER *b) {
	uint8_t *get = NULL;
	uint8_t res = SDS_OK;
	
	printf("inpos=%d outpos=%d  ", b->inpos, b->outpos);
	get = SDSFront(b, sizeof(uint8_t), &res);
	if (res == SDS_OK) printf("Front element: %d.  ", *get);
	get = SDSBack(b, sizeof(uint8_t), &res);
	if (res == SDS_OK) printf("Back element: %d.  ", *get);
}

int demoQueue(void) {
	/* Have a buffer of the queue. */
	int8_t buf[BUFLEN];
	/* Have a queue. */
	SDS_QUEUE q;
	uint8_t elem = 0;
	uint8_t *get = NULL;
	int i = 0;
	uint8_t res;

	/* Initial the queue. */
	SDSInitQueue(&q, BUFLEN, buf);

	printf("Queue 0x%x demo started!\n", (q.type & 0x03));
	/*Have the size of the queue. */
	printf("The length of the queue is %d.\n", q.len);
	/* Check the queue is empty. */
	printf("The queue is %sempty.\n", (SDSEmpty(&q) ? "":"not "));
	
	do {
		showStatus(&q);
		/* Push an element into the queue. */
		elem = i*2;
		res = SDSPush(&q, &elem, sizeof(uint8_t));
		i++;
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Push an element: %d.  ", elem);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The queue remains %d elements.\n", SDSSize(&q));

	for(i = 0; i < q.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	do {
		showStatus(&q);
		/* Pop an element into the queue. */
		get = SDSFront(&q, sizeof(uint8_t), &res);
		res = SDSPop(&q);
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Pop an element: %d.  ", *get);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The queue remains %d elements.\n", SDSSize(&q));

	return 0;
}

int demoStack(void) {
	/* Have a buffer of the stack. */
	int8_t buf[BUFLEN];
	/* Have a stack. */
	SDS_STACK s;
	uint8_t elem = 0;
	uint8_t *get = NULL;
	int i = 0;
	uint8_t res = 0;

	/* Initial the stack. */
	SDSInitStack(&s, BUFLEN, buf);

	printf("Stack 0x%d demo started!\n", (s.type & 0x03));
	/*Have the size of the stack. */
	printf("The length of the stack is %d.\n", s.len);
	/* Check the stack is empty. */
	printf("The stack is %sempty.\n", (SDSEmpty(&s) ? "":"not "));
	
	do {
		showStatus(&s);
		/* Push an element into the stack. */
		elem = i*2;
		res = SDSPush(&s, &elem, sizeof(uint8_t));
		printf("res=%d  ", res);
		i++;
		if(res == SDS_OK) printf("Push an element: %d.  ", elem);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The stack remains %d elements.\n", SDSSize(&s));

	for(i = 0; i < s.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	do {
		showStatus(&s);
		/* Pop an element into the stack. */
		get = SDSFront(&s, sizeof(uint8_t), &res);
		res = SDSPop(&s);
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Pop an element: %d.  ", *get);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The stack remains %d elements.\n", SDSSize(&s));

	return 0;
}

int demoRing(void) {
	/* Have a buffer of the ring. */
	int8_t buf[BUFLEN];
	/* Have a ring. */
	SDS_RING r;
	uint8_t elem = 0;
	uint8_t *get = NULL;
	int i = 0;
	uint8_t res = 0;

	/* Initial the ring. */
	SDSInitRing(&r, BUFLEN, buf);

	printf("Ring 0x%d demo started!\n", (r.type & 0x03));
	/*Have the size of the stack. */
	printf("The length of the ring is %d.\n", r.len);
	/* Check the stack is empty. */
	printf("The ring is %sempty.\n", (SDSEmpty(&r) ? "":"not "));
	
	do {
		showStatus(&r);
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(uint8_t));
		printf("res=%d  ", res);
		i++;
		if(res == SDS_OK) printf("Push an element: %d.  ", elem);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSSize(&r));

	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	do {
		showStatus(&r);
		/* Pop an element into the ring. */
		get = SDSFront(&r, sizeof(uint8_t), &res);
		res = SDSPop(&r);
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Pop an element: %d.  ", *get);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", SDSSize(&r));
	i = 0;
	do {
		showStatus(&r);
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(uint8_t));
		printf("res=%d  ", res);
		i++;
		if(res == SDS_OK) printf("Push an element: %d.  ", elem);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSSize(&r));

	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	do {
		showStatus(&r);
		/* Pop an element into the ring. */
		get = SDSFront(&r, sizeof(uint8_t), &res);
		res = SDSPop(&r);
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Pop an element: %d.  ", *get);
		printf("\n");
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", SDSSize(&r));
	
	for (i = 0; i < 4; i++) {
		showStatus(&r);
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(uint8_t));
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Push an element: %d.  ", elem);
		printf("\n");
	}

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSSize(&r));

	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	for (i = 0; i < 2; i++) {
		showStatus(&r);
		/* Pop an element into the ring. */
		get = SDSFront(&r, sizeof(uint8_t), &res);
		res = SDSPop(&r);
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Pop an element: %d.  ", *get);
		printf("\n");
	}

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", SDSSize(&r));
	
	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	for (i = 0; i < 4; i++) {
		showStatus(&r);
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(uint8_t));
		printf("res=%d  ", res);
		if(res == SDS_OK) printf("Push an element: %d.  ", elem);
		printf("\n");
	}

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSSize(&r));

	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	return 0;
}

int main(void) {
	demoQueue();
	printf("\n\n");
	demoStack();
	printf("\n\n");
	demoRing();

	return 0;
}
