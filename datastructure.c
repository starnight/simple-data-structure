#include "datastructure.h" 

/* Initial the queue. */
void DS_InitQueue(struct _DS_BUFFER *b, uint8_t len, void *elems) {
	b->type = (b->type & 0x9F) | (DS_QUEUETYPE << 5);
	b->len = len;
	b->inpos = 0;
	b->outpos = 0;
	b->elems = elems;
}

/* Initial the stack. */
void DS_InitStack(struct _DS_BUFFER *b, uint8_t len, void *elems) {
	b->type = (b->type & 0x9F) | (DS_STACKTYPE << 5);
	b->len = len;
	b->inpos = 0;
	b->outpos = 0;
	b->elems = elems;
}

/* Initial the ring. */
void DS_InitRing(struct _DS_BUFFER *b, uint8_t len, void *elems) {
	b->type = (b->type & 0x9F) | (DS_RINGTYPE << 5);
	b->len = len;
	b->inpos = 0;
	b->outpos = 0;
	b->elems = elems;
}

/* Check the buffer of the data structure is empty or not. */
uint8_t DS_Empty(struct _DS_BUFFER *b) {
	uint8_t rem;

	/* Check the array type.  Then, have the remain count. */
	if ((b->type & 0x20) == 0)
		/* It is the queue or ring type. */
		rem = b->inpos - b->outpos;
	else if ((b->type & 0x40) == 0)
		/* It is the stack type. */
		rem = b->inpos;
	else
		/* It is the rounded ring type. */
		rem = b->inpos + (b->len - b->outpos);

	return rem;
}

/* Get the buffer size of the data structure. */
uint8_t DS_Size(struct _DS_BUFFER *b) {
	return b->len;
}

/* Push an element into the queue. */
uint8_t DS_PushQueue(DS_QUEUE *b, void *elem, size_t size) {
	void *dst;
	uint8_t res = DS_OK;

	/* Check the queue is not full to prevent buffer over flow. */
	if(b->inpos < b->len) {
		/* The queue is not full. */
		dst = b->elems + size * b->inpos;
		memcpy(dst, elem, size);
		b->inpos += 1;
	}
	else {
		/* The queue is full. */
		res = DS_BUFFERFULL;
	}

	return res;
}

/* Push an element into the stack. */
uint8_t DS_PushStack(DS_STACK *b, void *elem, size_t size) {
	void *dst;
	uint8_t res = DS_OK;

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
		res = DS_BUFFERFULL;
	}

	return res;
}

/* Push an element into the ring. */
uint8_t DS_PushRing(DS_RING *b, void *elem, size_t size) {
	void *dst;
	uint8_t res = DS_OK;
	
	/* Check the array type is not rounded ring. */
	if ((b->type & 0x60) == (DS_RINGTYPE << 5)) {
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
			b->type = b->type | (DS_ROUNDEDRINGTYPE << 5);
			/* Circular the input position of the buffer for input. */
			b->inpos = 1;
			/* Copy the element into the buffer with the defined position. */
			memcpy(dst, elem, size);
		}
		else {
			/* The input position is beyond output position.. */
			res = DS_BUFFEROVERFLOW;
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
			res = DS_BUFFEROVERFLOW;
		}
	}

	return res;
}

/* Pop the indexed element from the queue. */
uint8_t DS_PopQueue(DS_QUEUE *b) {
	uint8_t res = DS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->outpos < b->inpos) {
		/* The queue is not empty. */
		b->outpos += 1;
	}
	else {
		/* The queue is empty. */
		res = DS_BUFFEREMPTY;
	}

	return res;
}

/* Pop the indexed element from the stack. */
uint8_t DS_PopStack(DS_STACK *b) {
	uint8_t res = DS_OK;

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
		res = DS_BUFFEREMPTY;
	}

	return res;
}

/* Pop the indexed element from the ring. */
uint8_t DS_PopRing(DS_RING *b) {
	uint8_t res = DS_OK;

	/* Check the array type is not rounded ring. */
	if ((b->type & 0x60) == (DS_RINGTYPE << 5)) {
		/* Check the output position to prevent buffer over flow. */
		if (b->outpos < b->inpos) {
			/* The ring is not empty. */
			/* Increase the position of the buffer for output. */
			b->outpos += 1;
		}
		else {
			/* The ring is empty. */
			res = DS_BUFFEREMPTY;
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
			b->type = (b->type & 0x9F) | (DS_RINGTYPE << 5);
			/* Circular the input position of the buffer for input. */
			b->outpos = 1;
		}
	}

	return res;
}

/* Get next element from the queue. */
uint8_t DS_FrontQueue(DS_QUEUE *b, void *elem, size_t size) {
	void *src;
	uint8_t res = DS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->outpos < b->inpos) {
		/* The queue is not empty. */
		src = b->elems + size * b->outpos;
		memcpy(elem, src, size);
	}
	else {
		/* The queue is empty. */
		res = DS_BUFFEREMPTY;
	}

	return res;
}

/* Get next element from the stack. */
uint8_t DS_FrontStack(DS_STACK *b, void *elem, size_t size) {
	void *src;
	uint8_t res = DS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->inpos > 0) {
		/* The queue is not empty. */
		src = b->elems + size * b->outpos;
		memcpy(elem, src, size);
	}
	else {
		/* The queue is empty. */
		res = DS_BUFFEREMPTY;
	}

	return res;
}

/* Get next element from the ring. */
uint8_t DS_FrontRing(DS_RING *b, void *elem, size_t size) {
	void *src;
	uint8_t res = DS_OK;

	/* Check the ring is rounded or not. */
	if ((b->type & 0x6F) == (DS_RINGTYPE << 5)) {
		/* It is not rounded ring. */
		/* Check the ring is not empty to prevent buffer over flow. */
		if(b->outpos < b->inpos) {
			/* The ring is not empty. */
			src = b->elems + size * b->outpos;
			memcpy(elem, src, size);
		}
		else {
			/* The ring is empty. */
			res = DS_BUFFEREMPTY;
		}
	}
	else {
		/* It is rounded ring. */
		/* Check the ring is not empty to prevent buffer over flow. */
		if (b->outpos <= b->len) {
			/* The ring is not empty. */
			src = b->elems + size * (b->outpos % b->len);
			memcpy(elem, src, size);
		}
		else {
			/* The ring is empty. */
			res = DS_BUFFEREMPTY;
		}
	}

	return res;
}

/* Get last element from the queue. */
uint8_t DS_BackQueue(DS_QUEUE *b, void *elem, size_t size) {
	void *src;
	uint8_t res = DS_OK;

	/* Check the queue is not empty to prevent buffer over flow. */
	if(b->outpos < b->inpos) {
		/* The queue is not empty. */
		src = b->elems + size * (b->inpos - 1);
		memcpy(elem, src, size);
	}
	else {
		/* The queue is empty. */
		res = DS_BUFFEREMPTY;
	}

	return res;
}

/* Get last element from the stack. */
uint8_t DS_BackStack(DS_STACK *b, void *elem, size_t size) {
	///* It is same for get last element from the stack. */
	//return DS_BackQueue(b, elem, size);
	void *src;
	uint8_t res = DS_OK;

	/* Check the stack is not empty to prevent buffer over flow. */
	if(b->inpos > 0) {
		/* The queue is not empty. */
		src = b->elems;
		memcpy(elem, src, size);
	}
	else {
		/* The queue is empty. */
		res = DS_BUFFEREMPTY;
	}

	return res;
}

/* Get last element from the ring. */
uint8_t DS_BackRing(DS_RING *b, void *elem, size_t size) {
	void *src;
	uint8_t res = DS_OK;

	/* Check the ring is not empty to prevent buffer over flow. */
	if(b->outpos != b->inpos) {
		/* The ring is not empty. */
		src = b->elems + (b->inpos - 1) * size;
		memcpy(elem, src, size);
	}
	else {
		/* The ring is empty. */
		res = DS_BUFFEREMPTY;
	}

	return res;
}

/* Push an element into the buffer of the data structure. */
uint8_t DS_Push(struct _DS_BUFFER *b, void *elem, size_t size) {
	uint8_t (*func[4])(struct _DS_BUFFER *, void *, size_t);

	/* Set the function pointers for pushing. */
	func[0] = DS_PushQueue;
	func[1] = DS_PushStack;
	func[2] = DS_PushRing;
	func[3] = DS_PushRing;

	return func[(b->type & 0x60) >> 5](b, elem, size);
}

/* Pop the indexed element from the buffer of the data structure. */
uint8_t DS_Pop(struct _DS_BUFFER *b) {
	uint8_t (*func[4])(struct _DS_BUFFER *);

	/* Set the function pointers for poping. */
	func[0] = DS_PopQueue;
	func[1] = DS_PopStack;
	func[2] = DS_PopRing;
	func[3] = DS_PopRing;

	return func[(b->type & 0x60) >> 5](b);
}

/* Get the next element from the buffer of the data structure. */
uint8_t DS_Front(struct _DS_BUFFER *b, void *elem, size_t size) {
	uint8_t (*func[4])(struct _DS_BUFFER *, void *, size_t);

	/* Set the function pointers for get next element. */
	func[0] = DS_FrontQueue;
	func[1] = DS_FrontStack;
	func[2] = DS_FrontRing;
	func[3] = DS_FrontRing;

	return func[(b->type & 0x60) >> 5](b, elem, size);
}

/* Get the last element from the buffer of the data structure. */
uint8_t DS_Back(struct _DS_BUFFER *b, void *elem, size_t size) {
	uint8_t (*func[4])(struct _DS_BUFFER *, void *, size_t);

	/* Set the function pointers for get last element. */
	func[0] = DS_BackQueue;
	func[1] = DS_BackStack;
	func[2] = DS_BackRing;
	func[3] = DS_BackRing;

	return func[(b->type & 0x60) >> 5](b, elem, size);
}
