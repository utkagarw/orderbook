#pragma once

#include <book/OrderNode.h>
#include <book/OrderBook.h>
#include <book/Trade.h>
#include <algorithm>
#include <vector>

class OrderBookMgr {
public:
	typedef std::vector<OrderNodePtr> OrderNodePtrList;
	OrderBookMgr(OrderBook &aBids, OrderBook &aOffers) : bids(aBids), offers(aOffers) {

	}
	~OrderBookMgr(){}

	//Function for adding a new order in the order book
    inline void newOrderFills(bool aIsBuy, int aOrdId, int aPx, int aSz) {
      if (aIsBuy){ newOrd<true>(aOrdId, aPx, aSz);}
      else{ newOrd<false>(aOrdId, aPx,aSz); }
      return;
    }

    //Function for cancelling a prevailing order in the order book
	inline void  cancelOrderFills(bool aIsBuy, int aOrdId) {
		if (aIsBuy) { bids.cancelOrder(aOrdId);	}
		else {  offers.cancelOrder(aOrdId);	}
		return;
	}

protected:
	OrderBook &bids;
	OrderBook &offers;

	template<bool BID>
	inline void newOrd(int aOrdId, int aPx, int aSz) {
		static OrderNodePtrList matchOrds_;
		static OrderNodePtr partialMatch_;
		int myRemSz = aSz;
		if(BID){
			if(offers.chkBottomCrossing(aPx)){
				partialMatch_ = offers.matchFromBottom(aPx, myRemSz, matchOrds_);
				generateTrades<BID>(aOrdId, matchOrds_, partialMatch_);
				bids.newOrder(aOrdId, aPx, myRemSz);
				return;
			}
			bids.newOrder(aOrdId, aPx, myRemSz);
		}
		else{
			if(bids.chkTopCrossing(aPx)){
				partialMatch_ = bids.matchFromTop(aPx, myRemSz, matchOrds_);
				generateTrades<BID>(aOrdId, matchOrds_, partialMatch_);
				offers.newOrder(aOrdId, aPx, myRemSz);
				return;
			}
			offers.newOrder(aOrdId, aPx, myRemSz);
		}
	}

	template<bool BID>
	void generateTrades(int aOrdId, OrderNodePtrList &aMatchOrders, OrderNodePtr aPartialMatch){
		for (OrderNodePtr myOrd : aMatchOrders) {
			if(BID){
				Trade::print(myOrd->filled, myOrd->px, aOrdId, myOrd->ordId);
				offers.handleFullyMatchedOrder(myOrd);
			}
			else{
				Trade::print(myOrd->filled, myOrd->px, myOrd->ordId, aOrdId);
				bids.handleFullyMatchedOrder(myOrd);
			}
		}

		if (aPartialMatch) {
			if(BID){
				Trade::print(aPartialMatch->filled, aPartialMatch->px, aOrdId, aPartialMatch->ordId);
			}
			else{
				Trade::print(aPartialMatch->filled, aPartialMatch->px, aPartialMatch->ordId, aOrdId);
			}
		}
		aMatchOrders.clear();
	}
};

