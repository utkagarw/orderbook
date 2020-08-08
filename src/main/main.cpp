#include <mktReader/MktReader.h>
#include <book/OrderBook.h>
#include <book/OrderBookMgr.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

int main(int argc, char *argv[]){

	if (argc < 2) {
		printf(" Usage %s <Path To MktDataFile>" , argv[0]);
		return 0;
	}


	MktReader *mktReader = new MktReader(std::string(argv[1]));

	OrderBook *bids = new OrderBook();
	OrderBook *asks = new OrderBook();

	OrderBookMgr *orderBookMgr = new OrderBookMgr(*bids, *asks);

	std::vector<char> &type = mktReader->type;
	std::vector<int> &orderId = mktReader->orderId;
	std::vector<char> &side = mktReader->side;
	std::vector<int> &size = mktReader->size;
	std::vector<int> &px = mktReader->px;

	int iterations = mktReader->type.size();
	printf("Trades =>\n");
	for(int i=0; i<iterations; i++){
		int myDec = (type[i] == 'A')*1 + (side[i] == 'B')*2;
		switch (myDec){
		case 0:
			orderBookMgr->cancelOrderFills(false, orderId[i]);
			break;
		case 1:
			orderBookMgr->newOrderFills(false, orderId[i],
						px[i], size[i]);
			break;
		case 2:
			orderBookMgr->cancelOrderFills(true, orderId[i]);
			break;
		case 3:
			orderBookMgr->newOrderFills(true, orderId[i],
						px[i], size[i]);
			break;
		default:
			break;
		}
	}
	bids->print<true>();
	asks->print<false>();
	return 0;
}
