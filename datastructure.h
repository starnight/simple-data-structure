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
inline void SDSInitQueue(struct _SDS_BUFFER *, uint8_t, void *);
/* Initial the stack. */
inline void SDSInitStack(struct _SDS_BUFFER *, uint8_t, void *);
/* Initial the ring. */
inline void SDSInitRing(struct _SDS_BUFFER *, uint8_t, void *);

/* Check the buffer of the data structure is empty or not. */
inline uint8_t SDSEmpty(struct _SDS_BUFFER *);
/* Get the buffer size of the data structure. */
inline uint8_t SDSSize(struct _SDS_BUFFER *);
/* Push an element into the buffer of the data structure. */
inline uint8_t SDSPush(struct _SDS_BUFFER *, void *, size_t);
/* Pop the first ordered element from the buffer of the data structure. */
inline uint8_t SDSPop(struct _SDS_BUFFER *);
/* Get the next element from the buffer of the data structure. */
inline uint8_t SDSFront(struct _SDS_BUFFER *, void *, size_t);
/* Get the last element from the buffer of the data structure. */
inline uint8_t SDSBack(struct _SDS_BUFFER *, void *, size_t);

/* Push an element into the buffer of the queue. */
inline uint8_t SDSPushQueue(SDS_QUEUE *, void *, size_t);
/* Pop the first ordered element from the buffer of the queue. */
inline uint8_t SDSPopQueue(SDS_QUEUE *);
/* Get the next element from the buffer of the queue. */
inline uint8_t SDSFrontQueue(SDS_QUEUE *, void *, size_t);
/* Get the last element from the buffer of the queue. */
inline uint8_t SDSBackQueue(SDS_QUEUE *, void *, size_t);

/* Push an element into the buffer of the stack. */
inline uint8_t SDSPushStack(SDS_STACK *, void *, size_t);
/* Pop the first ordered element from the buffer of the stack. */
inline uint8_t SDSPopStack(SDS_STACK *);
/* Get the next element from the buffer of the stack. */
inline uint8_t SDSFrontStack(SDS_STACK *, void *, size_t);
/* Get the last element from the buffer of the stack. */
inline uint8_t SDSBackStack(SDS_STACK *, void *, size_t);

/* Push an element into the buffer of the ring. */
inline uint8_t SDSPushRing(SDS_RING *, void *, size_t);
/* Pop the first ordered element from the buffer of the ring. */
inline uint8_t SDSPopRing(SDS_RING *);
/* Get the next element from the buffer of the ring. */
inline uint8_t SDSFrontRing(SDS_RING *, void *, size_t);
/* Get the last element from the buffer of the ring. */
inline uint8_t SDSBackRing(SDS_RING *, void *, size_t);

#endif
