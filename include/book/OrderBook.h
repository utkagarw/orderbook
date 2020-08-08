#pragma once

#include <book/OrderNode.h>
#include <book/PxLvl.h>
#include <book/Trade.h>
#include <cstdio>
#include <limits>
#include <map>
#include <vector>

struct PxLvl;

class OrderBook {
public:
	typedef PxLvl *PxLvlPtr;
	typedef std::map<int, PxLvlPtr> Px2PxLvlMap;
	typedef std::map<int, OrderNodePtr> OrdId2OrderNodeMap;

	OrderBook(){
	}

	virtual ~OrderBook() {	deleteAllPxLvls();	}

	inline void newOrder(int aOrdId, int aPx, int aSz) {
		if (aSz > 0){
			OrderNodePtr myOrd = new OrderNode(aOrdId, aSz);
			PxLvlPtr myPxLvl = getPxLvl(aPx);
			myPxLvl->insert(myOrd);
			orderMap_[aOrdId] = myOrd;
		}
	}

	inline PxLvlPtr getPxLvl(int aPx) {
		PxLvlPtr myPxLvl = pxMap_[aPx];
		if (myPxLvl){return myPxLvl; }
		else{ myPxLvl =  insertPxLvl(aPx); return myPxLvl;}
	}
	inline virtual bool cancelOrder(int aOrdId) { return cancelOrder(orderMap_[aOrdId]);}
	inline virtual bool cancelOrder(OrderNodePtr aOrd) {
		if (aOrd) {
			cleanOrder(aOrd);
			return true;
		}
		else { return false;}
	}

	inline OrderNodePtr getOrder(int aOrdId){
		return orderMap_[aOrdId];
	}

	//Function for checking if there is a crossing happening in the order book

	//This function is called on the ask order book side to check if there is a crossing happening at the ask side
	inline bool chkBottomCrossing(int aPx) {
		auto myPxIter = pxMap_.begin();
		auto myPxIterEnd = pxMap_.end();
		if (myPxIter == myPxIterEnd) return false;
		return ((myPxIter->second)->px <= aPx);
	}

	//This function is called on the bid order book side to check if there is a crossing happening at the bid side
	inline bool chkTopCrossing(int aPx) {
		auto myPxIter = pxMap_.rbegin();
		auto myPxIterEnd = pxMap_.rend();
		if (myPxIter == myPxIterEnd) return false;
		return ((myPxIter->second)->px >= aPx);
	}

	//This function is called on bid side and give relevant orders on the bid side against an aggressive ask order
	OrderNodePtr matchFromTop(int aPx, int &aSz, std::vector<OrderNodePtr> &aResMatchedOrds) {
		aResMatchedOrds.clear();
		OrderNodePtr aPartialFill=nullptr;
		auto myPxIter = pxMap_.rbegin();
		while ((myPxIter != pxMap_.rend())) {
			PxLvlPtr myPxLvl = myPxIter->second;
			if (myPxLvl->px < aPx) break;
			aPartialFill = myPxLvl->matchOrders(aSz, aResMatchedOrds);
			if (myPxLvl->isEmpty()) {
				pxMap_.erase(std::next(myPxIter).base());
				delete myPxLvl;}
			else {
				assert(aSz < 1);
				break;
			}
		}
		return aPartialFill;
	}

	//This function is called on ask side and give relevant orders on the ask side against an aggressive bid order
	OrderNodePtr matchFromBottom(int aPx, int &aSz, std::vector<OrderNodePtr> &aResMatchedOrds) {
		aResMatchedOrds.clear();
		OrderNodePtr aPartialFill=nullptr;
		auto myPxIter = pxMap_.begin();
		while ((myPxIter != pxMap_.end())) {
			PxLvlPtr myPxLvl = myPxIter->second;
			if (myPxLvl->px > aPx) break;
			aPartialFill = myPxLvl->matchOrders(aSz, aResMatchedOrds);
			if (myPxLvl->isEmpty()) {
				myPxIter = pxMap_.erase(myPxIter); delete myPxLvl;}
			else {
				break;
			}
		}

		return aPartialFill;
	}

	//This function is called to erase completely matched orders from the order book
	inline virtual void handleFullyMatchedOrder(OrderNodePtr aOrd){
		orderMap_.erase(aOrd->ordId);
		delete aOrd;
	}

	template<bool BID>
	void print() {
		if(BID)printf("[BID SIDE]=>\n");
		else printf("[ASK SIDE]=>\n");
		auto myPxIter = pxMap_.rbegin();
		auto myPxIterEnd = pxMap_.rend();
		while(myPxIter != myPxIterEnd){(myPxIter->second)->print(); myPxIter++; }
	}

	//This is a helper function called only in the googetest for unit testing
	std::vector<PxLvlPtr> getPxLvlList() {
		std::vector<PxLvlPtr> aRes;

		auto myPxIter = pxMap_.begin();
		auto myPxIterEnd = pxMap_.end();

		while(myPxIter != myPxIterEnd){aRes.push_back(myPxIter->second); myPxIter++; }
		return aRes;
	}

protected:
	Px2PxLvlMap pxMap_;
	OrdId2OrderNodeMap orderMap_;

	inline PxLvlPtr insertPxLvl(int aPx) {
		PxLvlPtr myPxLvl = new PxLvl(aPx);
		pxMap_[aPx] = myPxLvl;
		return myPxLvl;
	}

	inline void pxLvlChk(PxLvlPtr aPxLvl) { if (aPxLvl->isEmpty()) { purge(aPxLvl);} }

	inline void deleteAllPxLvls() {

		auto myPxIter = pxMap_.begin();
		auto myPxIterEnd = pxMap_.end();

		while(myPxIter != myPxIterEnd){pxMap_.erase(myPxIter->first); delete myPxIter->second; ++myPxIter;}
		pxMap_.clear();
	}

	inline void cleanOrder(OrderNodePtr aOrd) {
		PxLvlPtr myPxLvl = aOrd->pxLvl;
		int myOrdId = aOrd->ordId;
		orderMap_.erase(myOrdId);
		myPxLvl->purge(aOrd);
		pxLvlChk(myPxLvl);
	}

	inline void purge(PxLvlPtr aPxLvl) {
		pxMap_.erase(aPxLvl->px);
		delete aPxLvl;}
}
;

