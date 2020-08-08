#pragma once

#include <book/OrderNode.h>
#include <stddef.h>
#include <cassert>
#include <csignal>
#include <cstdio>
#include <vector>

struct PxLvl {
public:
	int px;

	static constexpr size_t INIT_CAPACITY_DEFAULT = 1024;

	PxLvl(int aPx=0, int aOrdCount=0, PxLvl *aPrev = nullptr,
			PxLvl *aNext = nullptr) {
		px = aPx;
		ordCount_ = aOrdCount;
		head_ = tail_ = nullptr;
		cumSz_ = 0;
		isDeleted_ = false;
	}

	~PxLvl(){
		deleteAllOrders();
		px = 0;
		ordCount_ = 0;
		head_ = tail_ = nullptr;
		cumSz_ = 0;
		isDeleted_ = true;
	}

	inline OrderNodePtr getHead(){ return head_;}
	inline OrderNodePtr getTail(){ return tail_;}
	inline bool isDeleted(){ return isDeleted_; }
	inline int getOrderCount(){ return ordCount_; }
	inline bool isEmpty(){
		return (cumSz_<1); }
	inline int getCumSz(){ return cumSz_; }

	// Function to insert into the end of the order queue
	inline void insert(OrderNode *aNode) {
		if (tail_) {
			tail_->next = aNode;
			aNode->prev = tail_;
		} else {
			head_ = aNode;
			aNode->prev = nullptr;
		}
		tail_ = aNode;
		cumSz_ += aNode->sz;
		aNode->next = nullptr;
		ordCount_++;
		aNode->pxLvl = this;
		aNode->px = px;
	}

	//Function for matching orders
	inline OrderNodePtr matchOrders(int &aSz,
			std::vector<OrderNodePtr> &aMatchOrders){
		OrderNodePtr aRes = nullptr;
		OrderNodePtr myOrd = head_;
		OrderNodePtr myNextOrd;
		while((myOrd!=nullptr) & (aSz>0)){
			int myOrdSz = myOrd->sz;
			myNextOrd = myOrd->next;
			if (myOrdSz > aSz){
				myOrd->fill(aSz);
				cumSz_ -=aSz;
				aSz=0;
				aRes = myOrd;
				break;
			}else{
				myOrd->fill(myOrdSz);
				aSz -= myOrdSz;
				cumSz_ -=myOrdSz;
				aMatchOrders.emplace_back(myOrd);
				head_ = myNextOrd;
			}
			myOrd = myNextOrd;
		}

		if (head_ == nullptr){ tail_ = nullptr;}
		else{ head_->prev = nullptr;}
		return aRes;
	}

	//Function for removing the Order node in the queue
	inline void removeOrder(OrderNode *aNode){
		remove(aNode);
		cumSz_ -= aNode->sz;
		ordCount_--;
	}

	inline void deleteAllOrders(){
		if (head_ !=nullptr ){
			std::raise(SIGINT);
		}

		OrderNodePtr myOrd = head_;
		OrderNodePtr myNextOrd;
		while(myOrd){

			myNextOrd = myOrd->next;
			delete myOrd;
			myOrd = myNextOrd;
		}
		head_ = tail_ = nullptr;
		cumSz_ = 0;
		ordCount_ = 0;
	}

	std::vector<OrderNodePtr> getOrderList(){
		std::vector<OrderNodePtr> aRes;
		OrderNodePtr myOrd = head_;
		while (myOrd){
			aRes.push_back(myOrd);
			myOrd = myOrd->next;
		}
		return aRes;
	}

	inline void purge(OrderNodePtr aNode) {
		removeOrder(aNode);
		delete aNode;
	}
	void print(FILE* aStream=stdout){
		OrderNodePtr myOrd = head_;
		while(myOrd != nullptr){
			fprintf(aStream, "[%d,%d,%d]=",myOrd->ordId, myOrd->sz, myOrd->px);
			myOrd = myOrd->next;
		}
		printf("\n");
	}


protected:

	OrderNodePtr head_;
	OrderNodePtr tail_;
	int cumSz_;
	int ordCount_;
	bool isDeleted_;


	inline void remove(const OrderNodePtr aNode) {
		if (aNode == nullptr){
		}
		short myDec = (aNode == tail_) * 2 + (aNode == head_);
		switch (myDec) {
		case 0:
			aNode->prev->next = aNode->next;
			aNode->next->prev = aNode->prev;
			break;
		case 1:
			aNode->next->prev = nullptr;
			head_ = aNode->next;
			break;
		case 2:
			aNode->prev->next = nullptr;
			tail_ = aNode->prev;
			break;
		default:
			head_ = tail_ = nullptr;
			break;
		}
	}
};
