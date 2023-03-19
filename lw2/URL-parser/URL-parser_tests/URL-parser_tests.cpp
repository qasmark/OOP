#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../URL-parser/URLHandler.h"

SCENARIO("TESTS")
{
	WHEN("invalid URL")
	{
		std::stringstream in("HELP ME WITH STUDY");
		std::stringstream out;

		ParseURLFromStreams(in, out);

		REQUIRE(out.str() == "URL parsing error: invalid URL\n");
	}
	WHEN("Protocols is working correctly")
	{
		REQUIRE(ParseProtocol("ftp") == Protocol::FTP);
		REQUIRE(ParseProtocol("http") == Protocol::HTTP);
		REQUIRE(ParseProtocol("https") == Protocol::HTTPS);

		REQUIRE_THROWS_AS(ParseProtocol("HELP ME"), std::invalid_argument);
	}
	WHEN("Hosts is working correctly")
	{
		REQUIRE(ParseHost("www.ispringsolutions.com") == "www.ispringsolutions.com");
		REQUIRE(ParseHost("1") == "1");

		REQUIRE_THROWS_AS(ParseHost(""), std::invalid_argument);
		
	}
	WHEN("Ports is working correctly")
	{
		REQUIRE(ParsePort("99", Protocol::HTTP) == 99);
		REQUIRE(ParsePort("3000", Protocol::HTTPS) == 3000);
		REQUIRE(ParsePort("23", Protocol::FTP) == 23);
		REQUIRE(ParsePort("", Protocol::HTTP) == 80);
		REQUIRE(ParsePort("", Protocol::HTTPS) == 443);
		REQUIRE(ParsePort("", Protocol::FTP) == 21);

		REQUIRE_THROWS_AS(ParsePort("abcd", Protocol::HTTP), std::invalid_argument);
		REQUIRE_THROWS_AS(ParsePort("???", Protocol::HTTP), std::invalid_argument);

		REQUIRE_THROWS_AS(ParsePort(std::to_string(MIN_PORT - 1), Protocol::HTTP), std::invalid_argument);
		REQUIRE_THROWS_AS(ParsePort(std::to_string(MAX_PORT + 1), Protocol::HTTP), std::invalid_argument);

	}
	WHEN("All parts is working correctly")
	{
		URLForm site;
		site.host = "vk.com";
		site.url = "https://vk.com:3000/id1";
		site.document = "id1";
		site.port = 3000;
		site.protocol = Protocol::HTTPS;

		std::stringstream out;

		PrintUnpackedURL(out, site);

		REQUIRE(out.str() == "https://vk.com:3000/id1\nHOST: vk.com\nPORT: 3000\nDOC: id1\n");
	}
}
