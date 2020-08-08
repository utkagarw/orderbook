#include <gtest/gtest.h>
#include <book/PxLvl.h>

namespace test_PxLvl {
// Test Cases

TEST(test_PxLvl, empty_struct) {
	PxLvl *myPxLvl = new PxLvl();
	std::vector<OrderNodePtr> aExpRes;
	EXPECT_EQ(aExpRes, myPxLvl->getOrderList());
}

TEST(test_PxLvl, single_order_inserted) {
	PxLvl *myPxLvl = new PxLvl();

	OrderNodePtr myOrd = new OrderNode(100,20);
	myPxLvl->insert(myOrd);

	std::vector<OrderNodePtr> aExpRes;
	aExpRes.push_back(myOrd);

	EXPECT_EQ(aExpRes, myPxLvl->getOrderList());
}

TEST(test_PxLvl, single_order_inserted_deleted) {
	PxLvl *myPxLvl = new PxLvl();

	OrderNodePtr myOrd = new OrderNode(100,20);
	myPxLvl->insert(myOrd);
	myPxLvl->removeOrder(myOrd);

	std::vector<OrderNodePtr> aExpRes;

	EXPECT_EQ(aExpRes, myPxLvl->getOrderList());
}

TEST(test_PxLvl, mult_order_inserted) {
	PxLvl *myPxLvl = new PxLvl();

	OrderNodePtr myOrd1 = new OrderNode(100,20);
	OrderNodePtr myOrd2 = new OrderNode(101,120);
	OrderNodePtr myOrd3 = new OrderNode(102,50);
	myPxLvl->insert(myOrd1);
	myPxLvl->insert(myOrd2);
	myPxLvl->insert(myOrd3);

	std::vector<OrderNodePtr> aExpRes;
	aExpRes.push_back(myOrd1);
	aExpRes.push_back(myOrd2);
	aExpRes.push_back(myOrd3);

	EXPECT_EQ(aExpRes, myPxLvl->getOrderList());
}



TEST(test_PxLvl, mult_order_inserted_head_remove) {
	PxLvl *myPxLvl = new PxLvl();

	OrderNodePtr myOrd1 = new OrderNode(100,20);
	OrderNodePtr myOrd2 = new OrderNode(101,120);
	OrderNodePtr myOrd3 = new OrderNode(102,50);
	myPxLvl->insert(myOrd1);
	myPxLvl->insert(myOrd2);
	myPxLvl->insert(myOrd3);
	myPxLvl->removeOrder(myOrd1);

	std::vector<OrderNodePtr> aExpRes;
	aExpRes.push_back(myOrd2);
	aExpRes.push_back(myOrd3);

	EXPECT_EQ(aExpRes, myPxLvl->getOrderList());
}

TEST(test_PxLvl, mult_order_inserted_tail_remove) {
	PxLvl *myPxLvl = new PxLvl();

	OrderNodePtr myOrd1 = new OrderNode(100,20);
	OrderNodePtr myOrd2 = new OrderNode(101,120);
	OrderNodePtr myOrd3 = new OrderNode(102,50);
	myPxLvl->insert(myOrd1);
	myPxLvl->insert(myOrd2);
	myPxLvl->insert(myOrd3);
	myPxLvl->removeOrder(myOrd3);

	std::vector<OrderNodePtr> aExpRes;
	aExpRes.push_back(myOrd1);
	aExpRes.push_back(myOrd2);

}

TEST(test_PxLvl, mult_order_inserted_mid_remove) {
	PxLvl *myPxLvl = new PxLvl();

	OrderNodePtr myOrd1 = new OrderNode(100,20);
	OrderNodePtr myOrd2 = new OrderNode(101,120);
	OrderNodePtr myOrd3 = new OrderNode(102,50);
	myPxLvl->insert(myOrd1);
	myPxLvl->insert(myOrd2);
	myPxLvl->insert(myOrd3);
	myPxLvl->removeOrder(myOrd2);

	std::vector<OrderNodePtr> aExpRes;
	aExpRes.push_back(myOrd1);
	aExpRes.push_back(myOrd3);

	EXPECT_EQ(aExpRes, myPxLvl->getOrderList());
}

TEST(test_PxLvl, mult_order_inserted_multiple_remove) {
	PxLvl *myPxLvl = new PxLvl();

	OrderNodePtr myOrd1 = new OrderNode(100,20);
	OrderNodePtr myOrd2 = new OrderNode(101,120);
	OrderNodePtr myOrd3 = new OrderNode(102,50);
	myPxLvl->insert(myOrd1);
	myPxLvl->insert(myOrd2);
	myPxLvl->insert(myOrd3);
	myPxLvl->removeOrder(myOrd2);
	myPxLvl->removeOrder(myOrd1);

	std::vector<OrderNodePtr> aExpRes;
	aExpRes.push_back(myOrd3);

	EXPECT_EQ(aExpRes, myPxLvl->getOrderList());
}
}



