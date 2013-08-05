#ifndef _SIMPLEDATASTRUCTURE_H_
#define _SIMPLEDATASTRUCTURE_H_

#include <stdint.h>

/* Define the data structure type. */
#define SDS_QUEUETYPE		0
#define SDS_STACKTYPE		1
#define SDS_RINGTYPE		2
#define SDS_ROUNDEDRINGTYPE	3

/* Define the error numbers. */
#define	SDS_OK				0
#define	SDS_BUFFERFULL		1
#define	SDS_BUFFEREMPTY		2
#define	SDS_BUFFEROVERFLOW	3

/* Define the base data structure for array type. */
struct _SDS_BUFFER {
	uint8_t type;
	uint8_t len;
	uint8_t inpos;
	uint8_t outpos;
	void *elems;
};

/* Define the queue variable type. */
typedef struct _SDS_BUFFER SDS_QUEUE;
/* Define the stack variable type. */
typedef struct _SDS_BUFFER SDS_STACK;
/* Define the ring variable type. */
typedef struct _SDS_BUFFER SDS_RING;

/* Initial the queue. */
void SDSInitQueue(SDS_QUEUE *, uint8_t, void *);
/* Initial the stack. */
void SDSInitStack(SDS_STACK *, uint8_t, void *);
/* Initial the ring. */
void SDSInitRing(SDS_RING *, uint8_t, void *);

/* Test the data structure is empty or not. */
uint8_t SDSEmpty(struct _SDS_BUFFER *);
/* Get the number of elements in the buffer of the data structure. */
uint8_t SDSSize(struct _SDS_BUFFER *);
/* Push an element into the buffer of the data structure. */
uint8_t SDSPush(struct _SDS_BUFFER *, void *, size_t);
/* Pop the first ordered element from the buffer of the data structure. */
uint8_t SDSPop(struct _SDS_BUFFER *);
/* Access next element from the buffer of the data structure. */
void * SDSFront(struct _SDS_BUFFER *, size_t, uint8_t *);
/* Access last element from the buffer of the data structure. */
void * SDSBack(struct _SDS_BUFFER *, size_t, uint8_t *);

/* Push an element into the buffer of the queue. */
uint8_t SDSPushQueue(SDS_QUEUE *, void *, size_t);
/* Pop the first ordered element from the buffer of the queue. */
uint8_t SDSPopQueue(SDS_QUEUE *);
/* Access next element from the buffer of the queue. */
void * SDSFrontQueue(SDS_QUEUE *, size_t, uint8_t *);
/* Access last element from the buffer of the queue. */
void * SDSBackQueue(SDS_QUEUE *, size_t, uint8_t *);

/* Push an element into the buffer of the stack. */
uint8_t SDSPushStack(SDS_STACK *, void *, size_t);
/* Pop the first ordered element from the buffer of the stack. */
uint8_t SDSPopStack(SDS_STACK *);
/* Access next element from the buffer of the stack. */
void * SDSTopStack(SDS_STACK *, size_t, uint8_t *);
/* Access last element from the buffer of the stack. */
void * SDSBackStack(SDS_STACK *, size_t, uint8_t *);

/* Push an element into the buffer of the ring. */
uint8_t SDSPushRing(SDS_RING *, void *, size_t);
/* Pop the first ordered element from the buffer of the ring. */
uint8_t SDSPopRing(SDS_RING *);
/* Access next element from the buffer of the ring. */
void * SDSFrontRing(SDS_RING *, size_t, uint8_t *);
/* Access last element from the buffer of the ring. */
void * SDSBackRing(SDS_RING *, size_t, uint8_t *);

#endif
