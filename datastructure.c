#include <string.h>
#include "datastructure.h" 

/* Initial the queue. */
void SDSInitQueue(SDS_QUEUE *b, uint8_t len, void *elems) {
	b->type = (b->type & 0xFC) | SDS_QUEUETYPE;
	b->len = len;
	b->inpos = 0;
	b->outpos = 0;
	b->elems = elems;
}

/* Initial the stack. */
void SDSInitStack(SDS_STACK *b, uint8_t len, void *elems) {
	b->type = (b->type & 0xFC) | SDS_STACKTYPE;
	b->len = len;
	b->inpos = 0;
	b->outpos = 0;
	b->elems = elems;
}

/* Initial the ring. */
void SDSInitRing(SDS_RING *b, uint8_t len, void *elems) {
	b->type = (b->type & 0xFC) | SDS_RINGTYPE;
	b->len = len;
	b->inpos = 0;
	b->outpos = 0;
	b->elems = elems;
}

/* Test the data structure is empty or not. */
uint8_t SDSEmpty(struct _SDS_BUFFER *b) {
	uint8_t rem;

	/* It is empty if input position is different from out position. */
	rem = (b->inpos == b->outpos);

	return rem;
}

/* Get the number of elements in the buffer of the data structure. */
uint8_t SDSSize(struct _SDS_BUFFER *b) {
	uint8_t rem;

	/* Check the array type.  Then, have the remain count. */
	if ((b->type & 0x01) == 0)
		/* It is the queue or ring type. */
		rem = b->inpos - b->outpos;
	else if ((b->type & 0x03) == SDS_STACKTYPE)
		/* It is the stack type. */
		rem = b->inpos;
	else
		/* It is the rounded ring type. */
		rem = b->inpos + (b->len - b->outpos);

	return rem;
}

/* Push an element into the queue. */
uint8_t SDSPushQueue(SDS_QUEUE *b, void *elem, size_t size) {
	void *dst;
	uint8_t res = SDS_OK;

	/* Check the queue is not full to prevent buffer over flow. */
	if(b->inpos < b->len) {
		/* The queue is not full. */
		dst = b->elems + size * b->inpos;
		memcpy(dst, elem, size);
		b->inpos += 1;
	}
	else {
		/* The queue is full. */
		res = SDS_BUFFERFULL;
	}

	return res;
}

/* Push an element into the stack. */
uint8_t SDSPushStack(SDS_STACK *b, void *elem, size_t size) {
	void *dst;
	uint8_t res = SDS_OK;

	/* Check the stack is not full to prevent buffer over flow. */
	if(b->inpos < b->len) {
		/* The queue is not full. */
		dst = b->elems + size * b->inpos;
		memcpy(dst, elem, size);
		b->outpos = b->inpos;
		b->inpos += 1;
	}
	else {
		/* The queue is full. */
		res = SDS_BUFFERFULL;
	}

	return res;
}

/* Push an element into the ring. */
uint8_t SDSPushRing(SDS_RING *b, void *elem, size_t size) {
	void *dst;
	uint8_t res = SDS_OK;
	
	/* Check the array type is not rounded ring. */
	if ((b->type & 0x03) == SDS_RINGTYPE) {
		/* Check the input position to prevent buffer over flow. */
		if(b->inpos < b->len) {
			/* The input position is not at the end of the buffer. */
			/* Have the destination pointer for not being rounded. */
			dst = b->elems + size * b->inpos;
			/* Increase the position of the buffer for input. */
			b->inpos += 1;
			/* Copy the element into the buffer with the defined position. */
			memcpy(dst, elem, size);
		}
		else if (b->outpos > 0) {
			/* The input position is at the end of the buffer. */
			/* Have the destination pointer for being rounded. */
			dst = b->elems;
			/* Set the array type being a rounded ring. */
			b->type = b->type | (SDS_ROUNDEDRINGTYPE);
			/* Circular the input position of the buffer for input. */
			b->inpos = 1;
			/* Copy the element into the buffer with the defined position. */
			memcpy(dst, elem, size);
		}
		else {
			/* The input position is beyond output position.. */
			res = SDS_BUFFEROVERFLOW;
		}
	}
	/* The array type is rounded ring. */
	else {
		/* Check the input position to prevent beyond output position. */
		/* The input position is not beyond output position. */
		if(b->inpos < b->outpos) {
			dst = b->elems + size * b->inpos;
			memcpy(dst, elem, size);
			b->inpos += 1;
		}
		/* The input position is beyond output position.. */
		else {
			res = SDS_BUFFEROVERFLOW;
		}
	}

	return res;
}

/* Pop the first ordered element from the queue. */
uint8_t SDSPopQueue(SDS_QUEUE *b) {
	uint8_t res = SDS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->outpos < b->inpos) {
		/* The queue is not empty. */
		b->outpos += 1;
	}
	else {
		/* The queue is empty. */
		res = SDS_BUFFEREMPTY;
	}

	return res;
}

/* Pop the first ordered element from the stack. */
uint8_t SDSPopStack(SDS_STACK *b) {
	uint8_t res = SDS_OK;

	/* Check the stack is not empty to prevent buffer over flow. */
	if(b->inpos > 0) {
		/* The stack is not empty. */
		/* Check the output position to prevent buffer over flow. */
		if(b->outpos > 0) {
			/* The output position is not at begin of the buffer. */
			b->inpos -= 1;
			b->outpos -= 1;
		}
		else {
			/* The output position is at begin of the buffer. */
			b->inpos = 0;
			b->outpos = 0;
		}
	}
	else {
		/* The stack is empty. */
		res = SDS_BUFFEREMPTY;
	}

	return res;
}

/* Pop the first ordered element from the ring. */
uint8_t SDSPopRing(SDS_RING *b) {
	uint8_t res = SDS_OK;

	/* Check the array type is not rounded ring. */
	if ((b->type & 0x03) == SDS_RINGTYPE) {
		/* Check the output position to prevent buffer over flow. */
		if (b->outpos < b->inpos) {
			/* The ring is not empty. */
			/* Increase the position of the buffer for output. */
			b->outpos += 1;
		}
		else {
			/* The ring is empty. */
			res = SDS_BUFFEREMPTY;
		}
	}
	else {
		/* The array type is rounded ring. */
		/* Check the output position to prevent buffer over flow. */
		if(b->outpos < b->len) {
			/* The output position is not at the end of the buffer. */
			/* Increase the position of the buffer for output. */
			b->outpos += 1;
		}
		else {
			/* The output position is at the end of the buffer. */
			/* Set the array type being a rounded ring. */
			b->type = (b->type & 0xFC) | (SDS_RINGTYPE);
			/* Circular the input position of the buffer for input. */
			b->outpos = 1;
		}
	}

	return res;
}

/* Access next element from the queue. */
void * SDSFrontQueue(SDS_QUEUE *b, size_t size, uint8_t *err) {
	void *src = NULL;
	
	*err = SDS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->outpos < b->inpos) {
		/* The queue is not empty. */
		src = b->elems + size * b->outpos;
	}
	else {
		/* The queue is empty. */
		*err = SDS_BUFFEREMPTY;
	}

	return src;
}

/* Access next element from the stack. */
void * SDSTopStack(SDS_STACK *b, size_t size, uint8_t *err) {
	void *src = NULL;
	
	*err = SDS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->inpos > 0) {
		/* The queue is not empty. */
		src = b->elems + size * b->outpos;
	}
	else {
		/* The queue is empty. */
		*err = SDS_BUFFEREMPTY;
	}

	return src;
}

/* Access next element from the ring. */
void * SDSFrontRing(SDS_RING *b, size_t size, uint8_t *err) {
	void *src = NULL;
	
	*err = SDS_OK;

	/* Check the ring is rounded or not. */
	if ((b->type & 0x03) == SDS_RINGTYPE) {
		/* It is not rounded ring. */
		/* Check the ring is not empty to prevent buffer over flow. */
		if(b->outpos < b->inpos) {
			/* The ring is not empty. */
			src = b->elems + size * b->outpos;
		}
		else {
			/* The ring is empty. */
			*err = SDS_BUFFEREMPTY;
		}
	}
	else {
		/* It is rounded ring. */
		/* Check the ring is not empty to prevent buffer over flow. */
		if (b->outpos <= b->len) {
			/* The ring is not empty. */
			src = b->elems + size * (b->outpos % b->len);
		}
		else {
			/* The ring is empty. */
			*err = SDS_BUFFEREMPTY;
		}
	}

	return src;
}

/* Access last element from the queue. */
void * SDSBackQueue(SDS_QUEUE *b, size_t size, uint8_t *err) {
	void *src = NULL;
	
	*err = SDS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->outpos < b->inpos) {
		/* The queue is not empty. */
		src = b->elems + size * (b->inpos - 1);
	}
	else {
		/* The queue is empty. */
		*err = SDS_BUFFEREMPTY;
	}

	return src;
}

/* Access last element from the stack. */
void * SDSBackStack(SDS_STACK *b, size_t size, uint8_t *err) {
	void *src = NULL;
	
	*err = SDS_OK;

	/* Check the stack is not empty to prevent buffer over flow. */
	if(b->inpos > 0) {
		/* The queue is not empty. */
		src = b->elems;
	}
	else {
		/* The queue is empty. */
		*err = SDS_BUFFEREMPTY;
	}

	return src;
}

/* Access last element from the ring. */
void * SDSBackRing(SDS_RING *b, size_t size, uint8_t *err) {
	void *src = NULL;
	
	*err = SDS_OK;

	/* Check the ring is not empty to prevent buffer over flow. */
	if(b->outpos != b->inpos) {
		/* The ring is not empty. */
		src = b->elems + (b->inpos - 1) * size;
	}
	else {
		/* The ring is empty. */
		*err = SDS_BUFFEREMPTY;
	}

	return src;
}

/* Push an element into the buffer of the data structure. */
uint8_t SDSPush(struct _SDS_BUFFER *b, void *elem, size_t size) {
	uint8_t (*func[4])(struct _SDS_BUFFER *, void *, size_t);

	/* Set the function pointers for pushing. */
	func[0] = SDSPushQueue;
	func[1] = SDSPushStack;
	func[2] = SDSPushRing;
	func[3] = SDSPushRing;

	return func[b->type & 0x03](b, elem, size);
}

/* Pop the first ordered element from the buffer of the data structure. */
uint8_t SDSPop(struct _SDS_BUFFER *b) {
	uint8_t (*func[4])(struct _SDS_BUFFER *);

	/* Set the function pointers for poping. */
	func[0] = SDSPopQueue;
	func[1] = SDSPopStack;
	func[2] = SDSPopRing;
	func[3] = SDSPopRing;

	return func[b->type & 0x03](b);
}

/* Access next element from the buffer of the data structure. */
void * SDSFront(struct _SDS_BUFFER *b, size_t size, uint8_t *err) {
	void * (*func[4])(struct _SDS_BUFFER *, size_t, uint8_t *);

	/* Set the function pointers for get next element. */
	func[0] = SDSFrontQueue;
	func[1] = SDSTopStack;
	func[2] = SDSFrontRing;
	func[3] = SDSFrontRing;

	return func[b->type & 0x03](b, size, err);
}

/* Access last element from the buffer of the data structure. */
void * SDSBack(struct _SDS_BUFFER *b, size_t size, uint8_t *err) {
	void * (*func[4])(struct _SDS_BUFFER *, size_t, uint8_t *);

	/* Set the function pointers for get last element. */
	func[0] = SDSBackQueue;
	func[1] = SDSBackStack;
	func[2] = SDSBackRing;
	func[3] = SDSBackRing;

	return func[b->type & 0x03](b, size, err);
}
