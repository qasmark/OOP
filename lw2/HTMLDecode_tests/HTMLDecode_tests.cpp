#define CATCH_CONFING_MAIN
#include "..\catch2\catch.hpp"
#include "..\HTMLDecode\HTMLManager.h"
#include <sstream>

TEST_CASE("encoded string is processed correctly")
{
	SECTION("empty string results in an empty result")
	{
		std::stringstream in(""), out;
		std::string input;
		HtmlDecodeInStreams(in, out);
		out >> input;
		REQUIRE(input.empty());
	}

	SECTION("string with no escape sequences is unchanged")
	{
		std::stringstream in("so let it be written, so let it be done"), out;
		HtmlDecodeInStreams(in, out);

		REQUIRE(in.str() == out.str());
	}

	SECTION("string with only pattern start is unchanged")
	{
		std::stringstream in("so let it be written & so let it be &; done"), out;
		HtmlDecodeInStreams(in, out);

		REQUIRE(in.str() == out.str());
	}

	SECTION("valid replace sequences are replaced correctly")
	{
		std::stringstream in("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"), out;
		const std::string result = "Cat <says> \"Meow\". M&M's";
		HtmlDecodeInStreams(in, out);

		REQUIRE(result == out.str());
	}

	SECTION("invalid replace sequences are not replaced")
	{
		std::stringstream in("Cat &lt;says&gt; &quotted;Meow&quot;. M&ampersand;M&apos;s"), out;
		const std::string result = "Cat <says> &quotted;Meow\". M&ampersand;M's";
		HtmlDecodeInStreams(in, out);

		REQUIRE(out.str() == result);
	}

	SECTION("doubling ampersand sequence is replaced correctly")
	{
		std::stringstream in("&amp&lt;"), out;
		const std::string result = "&amp<";
		HtmlDecodeInStreams(in, out);

		REQUIRE(out.str() == result);
	}

	SECTION("stacked sequences are replaced correctly")
	{
		std::stringstream in("&amp;&lt;"), out;
		const std::string result = "&<";
		HtmlDecodeInStreams(in, out);

		REQUIRE(out.str() == result);
	}


}

TEST_CASE("encoded stream with several lines is processed correctly")
{
	std::istringstream in("Cat &lt;says&gt;\n&quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream out;
	const std::string result = "Cat <says>\n\"Meow\". M&M's\n";
	HtmlDecodeInStreams(in, out);

	REQUIRE(out.str() == result);
}
