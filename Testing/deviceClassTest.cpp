
/**
 * Unit Tests for Device class
**/

#include <gtest/gtest.h>
#include "../device/device.h"
#include "../src/IRrecv.h"
 
class deviceClassTest : public ::testing::Test
{
	protected:
		deviceClassTest(){} //constructor runs before each test
		virtual ~deviceClassTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

/* EXAMPLE TEST FORMAT
TEST(deviceClassTest, unitTestName)
{
	ASSERT_TRUE(true);
}
*/
TEST(deviceClassTest, addDevice_pass)
{
	Dlist temp;
	decode_results* res;
	bool found;
	found = temp.addDevice("Power", res);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, add_two_Devices_pass)
{
	Dlist temp;
	decode_results* res;
	bool found;
	temp.addDevice("TV", res);
	found = temp.addDevice("Power", res);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, addDevice_fail)
{
	Dlist temp;
	decode_results* res;
	bool found;
	temp.addDevice("P",res);
	found = temp.addDevice("P",res);
	ASSERT_FALSE(found);
}

TEST(deviceClassTest, searchDevice_pass)
{
	Dlist temp;
	decode_results* res;
	temp.addDevice("Power", res);
	bool found;
	found = temp.searchDevice("Power");
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, searchDevice_fail)
{
	Dlist temp;
	bool found;
	found = temp.searchDevice("P");
	ASSERT_FALSE(found);
}
TEST(deviceClassTest, findDevice_fail)
{
	Dlist temp;
	Device* found;
	found = temp.findDevice("P");
	ASSERT_EQ(found,nullptr);
}
TEST(deviceClassTest, findDevice_pass)
{
	Dlist temp;
	Device* found;
	decode_results *res;
	temp.addDevice("P",res);
	found = temp.findDevice("P");
	ASSERT_NE(found,nullptr);
}
TEST(deviceClassTest, findDevice_two_devices_pass)
{
	Dlist temp;
	Device* found;
	decode_results *res;
	temp.addDevice("P",res);
	temp.addDevice("R",res);
	found = temp.findDevice("P");
	ASSERT_NE(found,nullptr);
}
TEST(deviceClassTest, addRoom_pass)
{
	Dlist temp;
	bool found;
	found = temp.addRoom("Living Room");
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, add_two_Rooms_pass)
{
	Dlist temp;
	bool found;
	temp.addRoom("Living Room");
	found = temp.addRoom("Family Room");
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, add_Room_fail)
{
	Dlist temp;
	bool found;
	temp.addRoom("Family Room");
	found = temp.addRoom("Family Room");
	ASSERT_FALSE(found);
}
TEST(deviceClassTest, search_Room_fail)
{
	Dlist temp;
	bool found;
	found = temp.searchRoom("Family Room");
	ASSERT_FALSE(found);
}
TEST(deviceClassTest, search_Room_pass)
{
	Dlist temp;
	bool found;
	temp.addRoom("Family Room");
	found = temp.searchRoom("Family Room");
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, search_for_2nd_Room_fail)
{
	Dlist temp;
	bool found;
	temp.addRoom("Family Room");
	temp.addRoom("Living");
	found = temp.addRoom("Family Room");
	ASSERT_FALSE(found);
}

TEST(deviceClassTest, add_QA_fail)
{
	Dlist temp;
	bool found;
	found = temp.addQA("TV",-1);
	ASSERT_FALSE(found);
}
TEST(deviceClassTest, add_QA_spot0_pass)
{
	Dlist temp;
	bool found;
	found = temp.addQA("TV",0);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, add_QA_spot1_pass)
{
	Dlist temp;
	bool found;
	found = temp.addQA("TV",1);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, add_QA_spot2_pass)
{
	Dlist temp;
	bool found;
	found = temp.addQA("TV",2);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, add_QA_multiple_pass)
{
	Dlist temp;
	bool found;
	temp.addQA("Fan",1);
	temp.addQA("Lamp",2);
	found = temp.addQA("TV",0);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, devce_get_name)
{
	Dlist temp;
	char* found;
	char* ans = "TV";
	decode_results *res;
	temp.addDevice("TV",res);
	found = temp.findDevice("TV")->get_name();
	ASSERT_EQ(found,ans);
}

TEST(deviceClassTest, searchButton_fail)
{
	Dlist temp;
	bool found;
	decode_results* res;
	temp.addDevice("TV",res);
	found = temp.findDevice("TV")->searchButton("r");
	ASSERT_FALSE(found);
}
TEST(deviceClassTest, searchButton_pass)
{
	Dlist temp;
	bool found;
	decode_results* res;
	temp.addDevice("TV",res);
	temp.findDevice("TV")->add_button("vol",*res);
	found = temp.findDevice("TV")->searchButton("vol");
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, searchButton_multi_pass)
{
	Dlist temp;
	bool found;
	decode_results* res;
	temp.addDevice("TV",res);
	temp.findDevice("TV")->add_button("vol",*res);
	temp.findDevice("TV")->add_button("r",*res);
	found = temp.findDevice("TV")->searchButton("vol");
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, addButton_pass)
{
	Dlist temp;
	bool found;
	decode_results* res;
	temp.addDevice("TV",res);
	found = temp.findDevice("TV")->add_button("r",*res);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, addButton_multi_pass)
{
	Dlist temp;
	bool found;
	decode_results* res;
	temp.addDevice("TV",res);
	temp.findDevice("TV")->add_button("r",*res);
	found = temp.findDevice("TV")->add_button("Pr",*res);
	ASSERT_TRUE(found);
}
TEST(deviceClassTest, addButton_fail)
{
	Dlist temp;
	bool found;
	decode_results* res;
	temp.addDevice("TV",res);
	temp.findDevice("TV")->add_button("vol",*res);
	found = temp.findDevice("TV")->add_button("vol",*res);
	ASSERT_FALSE(found);
}












