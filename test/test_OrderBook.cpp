#include <book/OrderBook.h>
#include <book/OrderNode.h>
#include <gtest/gtest.h>
#include <vector>


namespace test_OrderBook {
// Test Cases
using TestOrderBook = OrderBook;

TEST(test_TestOrderBook, empty_struct) {
	TestOrderBook *myBook = new TestOrderBook();
	std::vector<PxLvlPtr> aExpRes;
	EXPECT_EQ(aExpRes, myBook->getPxLvlList());
}

TEST(test_TestOrderBook, single_order_inserted) {
	TestOrderBook *myBook = new TestOrderBook();

	myBook->newOrder(100, 100, 20);
	PxLvlPtr myPxLvl = myBook->getPxLvl(100);

	std::vector<PxLvlPtr> aExpRes;
	aExpRes.push_back(myPxLvl);

	EXPECT_EQ(aExpRes, myBook->getPxLvlList());
}

TEST(test_TestOrderBook, single_order_inserted_deleted) {
	TestOrderBook *myBook = new TestOrderBook();

	myBook->newOrder(100, 100, 20);

	myBook->cancelOrder(100);

	std::vector<PxLvlPtr> aExpRes;

	EXPECT_EQ(aExpRes, myBook->getPxLvlList());

}

TEST(test_TestOrderBook, mult_order_inserted) {
	TestOrderBook *myBook = new TestOrderBook();

	myBook->newOrder(100, 100, 20);
	myBook->newOrder(101, 90, 120);
	myBook->newOrder(102, 110, 1120);
	PxLvlPtr myPxLvl1 = myBook->getPxLvl(90);
	PxLvlPtr myPxLvl2 = myBook->getPxLvl(100);
	PxLvlPtr myPxLvl3 = myBook->getPxLvl(110);

	std::vector<PxLvlPtr> aExpRes;
	aExpRes.push_back(myPxLvl1);
	aExpRes.push_back(myPxLvl2);
	aExpRes.push_back(myPxLvl3);

	EXPECT_EQ(aExpRes, myBook->getPxLvlList());
	EXPECT_EQ(120, myPxLvl1->getCumSz());
	EXPECT_EQ(20, myPxLvl2->getCumSz());
	EXPECT_EQ(1120, myPxLvl3->getCumSz());
}

TEST(test_TestOrderBook, mult_order_inserted_top_cancelled) {
	TestOrderBook *myBook = new TestOrderBook();

	myBook->newOrder(100, 100, 20);
	myBook->newOrder(101, 90, 120);
	myBook->newOrder(102, 110, 1120);
	PxLvlPtr myPxLvl1 = myBook->getPxLvl(90);
	PxLvlPtr myPxLvl2 = myBook->getPxLvl(100);


	std::vector<PxLvlPtr> aExpRes;
	aExpRes.push_back(myPxLvl1);
	aExpRes.push_back(myPxLvl2);

	myBook->cancelOrder(102);

	EXPECT_EQ(aExpRes, myBook->getPxLvlList());
	EXPECT_EQ(120, myPxLvl1->getCumSz());
	EXPECT_EQ(20, myPxLvl2->getCumSz());

}

TEST(test_TestOrderBook, mult_order_inserted_bottom_cancelled) {
	TestOrderBook *myBook = new TestOrderBook();

	myBook->newOrder(100, 100, 20);
	myBook->newOrder(101, 90, 120);
	myBook->newOrder(102, 110, 1120);

	PxLvlPtr myPxLvl2 = myBook->getPxLvl(100);
	PxLvlPtr myPxLvl3 = myBook->getPxLvl(110);

	std::vector<PxLvlPtr> aExpRes;

	aExpRes.push_back(myPxLvl2);
	aExpRes.push_back(myPxLvl3);
	myBook->cancelOrder(101);

	EXPECT_EQ(aExpRes, myBook->getPxLvlList());

	EXPECT_EQ(20, myPxLvl2->getCumSz());
	EXPECT_EQ(1120, myPxLvl3->getCumSz());
}

TEST(test_TestOrderBook, mult_order_inserted_mid_cancelled) {
	TestOrderBook *myBook = new TestOrderBook();

	myBook->newOrder(100, 100, 20);
	myBook->newOrder(101, 90, 120);
	myBook->newOrder(102, 110, 1120);
	PxLvlPtr myPxLvl1 = myBook->getPxLvl(90);

	PxLvlPtr myPxLvl3 = myBook->getPxLvl(110);

	std::vector<PxLvlPtr> aExpRes;
	aExpRes.push_back(myPxLvl1);

	aExpRes.push_back(myPxLvl3);
	myBook->cancelOrder(100);

	EXPECT_EQ(aExpRes, myBook->getPxLvlList());
	EXPECT_EQ(120, myPxLvl1->getCumSz());

	EXPECT_EQ(1120, myPxLvl3->getCumSz());
}


}


