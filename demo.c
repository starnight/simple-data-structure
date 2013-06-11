#include <stdio.h>
#include "datastructure.h"

#define BUFLEN	8

int demoQueue(void) {
	/* Have a buffer of the queue. */
	int8_t buf[BUFLEN];
	/* Have a queue. */
	DS_QUEUE q;
	uint8_t elem = 0;
	int i = 0;
	uint8_t res;

	/* Initial the queue. */
	DS_InitQueue(&q, BUFLEN, buf);

	printf("Queue 0x%x demo started!\n", (q.type & 0x60) >> 5);
	/*Have the size of the queue. */
	printf("The length of the queue is %d.\n", (int)DS_Size(&q));
	/* Check the queue is empty. */
	printf("The queue is %sempty.\n", (DS_Empty(&q) ? "not ":""));
	
	do {
		printf("inpos=%d outpos=%d  ", q.inpos, q.outpos);
		/* Push an element into the queue. */
		elem = i*2;
		res = DS_Push(&q, &elem, sizeof(elem));
		i++;
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Push an element: %d.  ", elem);
			DS_Front(&q, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&q, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the queue remian? */
	printf("The queue remains %d elements.\n", DS_Empty(&q));

	for(i=0; i<q.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	/* Emulate the queue elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d  ", q.inpos, q.outpos);
		DS_Front(&q, &elem, sizeof(elem));
		res = DS_Pop(&q);
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Pop an element: %d.  ", elem);
			//DS_Front(&q, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&q, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the queue remian? */
	printf("The queue remains %d elements.\n", DS_Empty(&q));

	return 0;
}

int demoStack(void) {
	/* Have a buffer of the stack. */
	int8_t buf[BUFLEN];
	/* Have a stack. */
	DS_STACK s;
	uint8_t elem = 0;
	int i = 0;
	uint8_t res = 0;

	/* Initial the stack. */
	DS_InitStack(&s, BUFLEN, buf);

	printf("Stack 0x%d demo started!\n", (s.type & 0x60) >> 5);
	/*Have the size of the stack. */
	printf("The length of the stack is %d.\n", (int)DS_Size(&s));
	/* Check the stack is empty. */
	printf("The stack is %sempty.\n", (DS_Empty(&s) ? "not ":""));
	
	do {
		printf("inpos=%d outpos=%d  ", s.inpos, s.outpos);
		/* Push an element into the stack. */
		elem = i*2;
		res = DS_Push(&s, &elem, sizeof(elem));
		printf("res=%d  ", res);
		i++;
		if(res == DS_OK) {
			printf("Push an element: %d.  ", elem);
			DS_Front(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&s, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the queue remian? */
	printf("The stack remains %d elements.\n", DS_Empty(&s));

	for(i=0; i<s.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	/* Emulate the stack elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d  ", s.inpos, s.outpos);
		res = DS_Front(&s, &elem, sizeof(elem));
		res = DS_Pop(&s);
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Pop an element: %d.  ", elem);
			//DS_Front(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&s, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the queue remian? */
	printf("The stack remains %d elements.\n", DS_Empty(&s));

	return 0;
}

int demoRing(void) {
	/* Have a buffer of the ring. */
	int8_t buf[BUFLEN];
	/* Have a ring. */
	DS_RING r;
	uint8_t elem = 0;
	int i = 0;
	uint8_t res = 0;

	/* Initial the ring. */
	DS_InitRing(&r, BUFLEN, buf);

	printf("Ring 0x%d demo started!\n", (r.type & 0x60) >> 5);
	/*Have the size of the stack. */
	printf("The length of the ring is %d.\n", (int)DS_Size(&r));
	/* Check the stack is empty. */
	printf("The ring is %sempty.\n", (DS_Empty(&r) ? "not ":""));
	
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x60) >> 5);
		/* Push an element into the ring. */
		elem = i*2;
		res = DS_Push(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		i++;
		if(res == DS_OK) {
			printf("Push an element: %d.  ", elem);
			DS_Front(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", DS_Empty(&r));

	for(i=0; i<r.len; i++)
		printf("%d\t",buf[i]);
	printf("\n");

	/* Emulate the ring elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x60) >> 5);
		res = DS_Front(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		res = DS_Pop(&r);
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Pop an element: %d.  ", elem);
			//DS_Front(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", DS_Empty(&r));
	i = 0;
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x60) >> 5);
		/* Push an element into the ring. */
		elem = i*2;
		res = DS_Push(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		i++;
		if(res == DS_OK) {
			printf("Push an element: %d.  ", elem);
			DS_Front(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", DS_Empty(&r));

	for(i=0; i<(r.len + 1); i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	/* Emulate the ring elements and pop each element. */
	do {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x60) >> 5);
		res = DS_Front(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		res = DS_Pop(&r);
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Pop an element: %d.  ", elem);
			//DS_Front(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}while(res == DS_OK);

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", DS_Empty(&r));
	
	for (i = 0; i < 4; i++) {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x60) >> 5);
		/* Push an element into the ring. */
		elem = i*2;
		res = DS_Push(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Push an element: %d.  ", elem);
			DS_Front(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", DS_Empty(&r));

	for(i=0; i<(r.len + 1); i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	/* Emulate the ring elements and pop each element. */
	for (i = 0; i < 2; i++) {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x60) >> 5);
		res = DS_Front(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		res = DS_Pop(&r);
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Pop an element: %d.  ", elem);
			//DS_Front(&s, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}

	/* How many elements does the queue remian? */
	printf("The ring remains %d elements.\n", DS_Empty(&r));
	
	for(i=0; i<(r.len + 1); i++)
		printf("%d\t",buf[i]);
	printf("\n");
	
	for (i = 0; i < 4; i++) {
		printf("inpos=%d outpos=%d type=%d  ", r.inpos, r.outpos, (r.type & 0x60) >> 5);
		/* Push an element into the ring. */
		elem = i*2;
		res = DS_Push(&r, &elem, sizeof(elem));
		printf("res=%d  ", res);
		if(res == DS_OK) {
			printf("Push an element: %d.  ", elem);
			DS_Front(&r, &elem, sizeof(elem));
			printf("Front element: %d.  ", elem);
			DS_Back(&r, &elem, sizeof(elem));
			printf("Back element: %d.\n", elem);
		}
	}

	/* How many elements does the ring remian? */
	printf("The ring remains %d elements.\n", DS_Empty(&r));

	for(i=0; i<(r.len + 1); i++)
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
