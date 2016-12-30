#include "../include/websocket.hpp"
#include "../../xtest/include/xtest.hpp"
xtest_run;

XTEST_SUITE(xbase64)
{
	XUNIT_TEST(decode)
	{
		std::string data = "1029wjsjshdhancjaksdamjdadjoaidjao";
		auto encode_data =  xbase64::encode(data);

		std::string decode_result;
		auto res = xbase64::decode(encode_data, decode_result);

		xassert(res);
		xassert(data == decode_result);

	}
}