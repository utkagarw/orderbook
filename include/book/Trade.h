#pragma once

#include <book/OrderNode.h>
#include <cstdio>
#include <vector>


class Trade {

public:
	// Function for printing trades
	static void print(int aTrdSz, int aTrdPx, int aBoId, int aSoId, FILE *aStream = stdout) {
		fprintf(aStream, "[%d @ %d] oIds[%d, %d]\n",
				aTrdSz, aTrdPx, aBoId, aSoId);
	}

};

