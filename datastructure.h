#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include <string.h>
#include <stdint.h>

/* Define the data structure type. */
#define DS_QUEUETYPE		0
#define DS_STACKTYPE		1
#define DS_RINGTYPE			2
#define DS_ROUNDEDRINGTYPE	3

/* Define the error numbers. */
#define	DS_OK				0
#define	DS_BUFFERFULL		1
#define	DS_BUFFEREMPTY		2
#define	DS_BUFFEROVERFLOW	3

/* Define the base data structure for array type. */
struct _DS_BUFFER {
	uint8_t type;
	uint8_t len;
	uint8_t inpos;
	uint8_t outpos;
	void *elems;
};

/* Define the queue variable type. */
typedef struct _DS_BUFFER DS_QUEUE;
/* Define the stack variable type. */
typedef struct _DS_BUFFER DS_STACK;
/* Define the ring variable type. */
typedef struct _DS_BUFFER DS_RING;

/* Initial the queue. */
inline void DS_InitQueue(struct _DS_BUFFER *, uint8_t, void *);
/* Initial the stack. */
inline void DS_InitStack(struct _DS_BUFFER *, uint8_t, void *);
/* Initial the ring. */
inline void DS_InitRing(struct _DS_BUFFER *, uint8_t, void *);

/* Check the buffer of the data structure is empty or not. */
inline uint8_t DS_Empty(struct _DS_BUFFER *);
/* Get the buffer size of the data structure. */
inline uint8_t DS_Size(struct _DS_BUFFER *);
/* Push an element into the buffer of the data structure. */
inline uint8_t DS_Push(struct _DS_BUFFER *, void *, size_t);
/* Pop the indexed element from the buffer of the data structure. */
inline uint8_t DS_Pop(struct _DS_BUFFER *);
/* Get the next element from the buffer of the data structure. */
inline uint8_t DS_Front(struct _DS_BUFFER *, void *, size_t);
/* Get the last element from the buffer of the data structure. */
inline uint8_t DS_Back(struct _DS_BUFFER *, void *, size_t);

/* Push an element into the buffer of the queue. */
inline uint8_t DS_PushQueue(DS_QUEUE *, void *, size_t);
/* Pop the indexed element from the buffer of the queue. */
inline uint8_t DS_PopQueue(DS_QUEUE *);
/* Get the next element from the buffer of the queue. */
inline uint8_t DS_FrontQueue(DS_QUEUE *, void *, size_t);
/* Get the last element from the buffer of the queue. */
inline uint8_t DS_BackQueue(DS_QUEUE *, void *, size_t);

/* Push an element into the buffer of the stack. */
inline uint8_t DS_PushStack(DS_STACK *, void *, size_t);
/* Pop the indexed element from the buffer of the stack. */
inline uint8_t DS_PopStack(DS_STACK *);
/* Get the next element from the buffer of the stack. */
inline uint8_t DS_FrontStack(DS_STACK *, void *, size_t);
/* Get the last element from the buffer of the stack. */
inline uint8_t BackStack(DS_STACK *, void *, size_t);

/* Push an element into the buffer of the ring. */
inline uint8_t DS_PushRing(DS_RING *, void *, size_t);
/* Pop the indexed element from the buffer of the ring. */
inline uint8_t DS_PopRing(DS_RING *);
/* Get the next element from the buffer of the ring. */
inline uint8_t DS_FrontRing(DS_RING *, void *, size_t);
/* Get the last element from the buffer of the ring. */
inline uint8_t DS_BackRing(DS_RING *, void *, size_t);

#endif
