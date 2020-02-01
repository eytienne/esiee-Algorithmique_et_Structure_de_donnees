#ifndef SDA_H
#define SDA_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

typedef void *SDA;

typedef struct __SDA__ {
	void (*new)(SDA *sda);
	int (*isEmpty)(const SDA *sda);
	/*
     * in : k, v
     * in/out : sda
	 * preconditions : k not used
	 * postconditions : k used
	 */
	void (*put)(SDA *sda, Key k, Value v);
    /*
     * in : sda, k
	 */
    int (*containsKey)(const SDA* sda, Key k);
    /*
     * in : sda, k
	 * preconditions : sda contains k
	 */
    Value (*get)(const SDA* sda, Key k);
    /*
     * in/out : sda
	 * postconditions : sda is empty
	 */
    void (*clear)(SDA *sda);
} __SDA__;
extern const __SDA__ SDAFunc;

#endif