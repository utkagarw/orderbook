#pragma once

#include <stddef.h>
#include <cstdio>
#include <assert.h>


struct PxLvl;
typedef PxLvl *PxLvlPtr;
struct OrderNode {

	static constexpr int NULL_ORDER_ID = -1;
	static constexpr size_t INIT_CAPACITY_DEFAULT = 1024*8;

	OrderNode *prev;
	OrderNode *next;
	PxLvlPtr pxLvl;
	int sz;
	int ordId;
	int px;
	int filled;


	OrderNode(int aExcOrdId=NULL_ORDER_ID, int aSz=0,
			OrderNode *aPrev = nullptr, OrderNode *aNext = nullptr) {
		sz = aSz;

		px = filled = 0;
		ordId = aExcOrdId;
		prev = aPrev;
		next = aNext;
		pxLvl = nullptr;
	}

	~OrderNode() {
		sz = px = 0;
		filled = 0;
		ordId = NULL_ORDER_ID;
		prev = next = nullptr;
		pxLvl = nullptr;
	}

	inline void fill(int aSz){
		sz -= aSz;
		filled = aSz;
	}

protected:

};
using OrderNodePtr = OrderNode*;

