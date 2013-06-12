#include <stdio.h>
#include "datastructure.h"

#define BUFLEN	8

int demoQueue(void) {
	/* Have a buffer of the queue. */
	int8_t buf[BUFLEN];
	/* Have a queue. */
	SDS_QUEUE q;
	uint8_t elem = 0;
	int i = 0;
	uint8_t res;

	/* Initial the queue. */
	SDSInitQueue(&q, BUFLEN, buf);

	printf("Queue 0x%x demo started!\n", (q.type & 0x03));
	/*Have the size of the queue. */
	printf("The length of the queue is %d.\n", (int)SDSSize(&q));
	/* Check the queue is empty. */
	printf("The queue is %sempty.\n", (SDSEmpty(&q) ? "not ":""));
	
	do {
		printf("inpos=%d outpos=%d  ", q.inpos, q.outpos);
		/* Push an element into the queue. */
		elem = i*2;
		res = SDSPush(&q, &elem, sizeof(elem));
		i++;
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Push an element: %d.  ", elem);
			SDSFront(&q, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
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
		printf("inpos=%d outpos=%d  ", q.inpos, q.outpos);
		SDSFront(&q, &elem, sizeof(elem));
		res = SDSPop(&q);
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Pop an element: %d.  ", elem);
			//SDSFront(&q, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&q, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The queue remains %d elements.\n", SDSEmpty(&q));

	return 0;
}

int demoStack(void) {
	/* Have a buffer of the stack. */
	int8_t buf[BUFLEN];
	/* Have a stack. */
	SDS_STACK s;
	uint8_t elem = 0;
	int i = 0;
	uint8_t res = 0;

	/* Initial the stack. */
	SDSInitStack(&s, BUFLEN, buf);

	printf("Stack 0x%d demo started!\n", (s.type & 0x03));
	/*Have the size of the stack. */
	printf("The length of the stack is %d.\n", (int)SDSSize(&s));
	/* Check the stack is empty. */
	printf("The stack is %sempty.\n", (SDSEmpty(&s) ? "not ":""));
	
	do {
		printf("inpos=%d outpos=%d  ", s.inpos, s.outpos);
		/* Push an element into the stack. */
		elem = i*2;
		res = SDSPush(&s, &elem, sizeof(elem));
		printf("res=%d  ", res);
		i++;
		if(res == SDS_OK) {
			printf("Push an element: %d.  ", elem);
			SDSFront(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&s, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The stack remains %d elements.\n", SDSEmpty(&s));

	for(i = 0; i < s.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	/* Enumerate the stack elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d  ", s.inpos, s.outpos);
		res = SDSFront(&s, &elem, sizeof(elem));
		res = SDSPop(&s);
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Pop an element: %d.  ", elem);
			//SDSFront(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&s, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The stack remains %d elements.\n", SDSEmpty(&s));

	return 0;
}

int demoRing(void) {
	/* Have a buffer of the ring. */
	int8_t buf[BUFLEN];
	/* Have a ring. */
	SDS_RING r;
	uint8_t elem = 0;
	int i = 0;
	uint8_t res = 0;

	/* Initial the ring. */
	SDSInitRing(&r, BUFLEN, buf);

	printf("Ring 0x%d demo started!\n", (r.type & 0x03));
	/*Have the size of the stack. */
	printf("The length of the ring is %d.\n", (int)SDSSize(&r));
	/* Check the stack is empty. */
	printf("The ring is %sempty.\n", (SDSEmpty(&r) ? "not ":""));
	
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x03));
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		i++;
		if(res == SDS_OK) {
			printf("Push an element: %d.  ", elem);
			SDSFront(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSEmpty(&r));

	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	/* Enumerate the ring elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x03));
		res = SDSFront(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		res = SDSPop(&r);
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Pop an element: %d.  ", elem);
			//SDSFront(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", SDSEmpty(&r));
	i = 0;
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x03));
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		i++;
		if(res == SDS_OK) {
			printf("Push an element: %d.  ", elem);
			SDSFront(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSEmpty(&r));

	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	/* Enumerate the ring elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x03));
		res = SDSFront(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		res = SDSPop(&r);
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Pop an element: %d.  ", elem);
			//SDSFront(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == SDS_OK);

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", SDSEmpty(&r));
	
	for (i = 0; i < 4; i++) {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x03));
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Push an element: %d.  ", elem);
			SDSFront(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSEmpty(&r));

	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	/* Enumerate the ring elements and pop each element. */
	for (i = 0; i < 2; i++) {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x03));
		res = SDSFront(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		res = SDSPop(&r);
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Pop an element: %d.  ", elem);
			//SDSFront(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", SDSEmpty(&r));
	
	for(i = 0; i < r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	for (i = 0; i < 4; i++) {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x03));
		/* Push an element into the ring. */
		elem = i*2;
		res = SDSPush(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		if(res == SDS_OK) {
			printf("Push an element: %d.  ", elem);
			SDSFront(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			SDSBack(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", SDSEmpty(&r));

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
