#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HttpUrl/CHttpUrl.h"
#include <sstream>

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

SCENARIO("Testing Constructors with string")
{
	WHEN("Construct HttpUrl with string of correct url")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://faceit.com"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (with complicated domain)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://faceit.com/kvantero/ratings/solo"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (and with document)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://faceit.com/stats"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (and with MIN available port)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("http://faceit.com:" + std::to_string(MIN_PORT) + "/stats"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (and with MAX available port)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://faceit.com:" + std::to_string(MAX_PORT) + "/kvantero"));
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (no protocol)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("//faceit.com/kvantero"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (no domain)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (wrong protocol)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("abcde://faceit.com/kvantero"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (wrong domain)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://face it.com"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (wrong document)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("https://faceit.com/main / 123"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (port is not a number)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://faceit.com:string"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (port is less than MIN available port)")
	{
		THEN("HttpUrl is not created")
		{
			//REQUIRE_THROWS_AS(CHttpUrl("https://faceit.com:" + (MIN_PORT - 1)), CUrlParsingError);
			REQUIRE_THROWS_AS(CHttpUrl("https://faceit.com:123abc" ), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (port is greater than MAX available port)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://faceit.com:" + (MAX_PORT + 1)), CUrlParsingError);
		}
	}
}

SCENARIO("Testing Constructors with protocol, domain, document")
{
	Protocol protocol;
	std::string domain;
	std::string document;
	WHEN("Construct HttpUrl with correct values and empty document")
	{
		protocol = Protocol::HTTP;
		domain = "faceit.com";
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
		}
	}
	WHEN("Construct HttpUrl with correct values and valued document")
	{
		protocol = Protocol::HTTPS;
		domain = "faceit.com";
		document = "stats/ratings";
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
		}
	}
	WHEN("Construct HttpUrl with incorrect domain")
	{
		protocol = Protocol::HTTP;
		domain = "face i t .com";
		THEN("HttpUrl is created")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with incorrect document")
	{
		protocol = Protocol::HTTPS;
		domain = "faceit.com";
		document = "st ats /kvanter o---";
		THEN("HttpUrl is created")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol), CUrlParsingError);
		}
	}
}

SCENARIO("Testing Constructors with protocol, domain, document and PORT")
{
	Protocol protocol;
	std::string domain;
	std::string document;
	Port port;
	WHEN("Construct HttpUrl with correct values and random port")
	{
		protocol = Protocol::HTTP;
		domain = "faceit.com";
		port = 52532;
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol, MIN_PORT));
		}
	}
}

SCENARIO("Testing get-methods")
{
	Protocol protocol = Protocol::HTTPS;
	std::string domain = "faceit.com";
	Port port = 4554;
	std::string document = "/stats/ratings/form.php?";
	std::string correctStringUrl = CHttpUrl::ConvertProtocolToString(protocol) + "://" + domain + ":" + std::to_string(port) + document;

	CHttpUrl correctUrl(domain, document, protocol, port);
	WHEN("Testing GetProtocol")
	{
		REQUIRE(correctUrl.GetProtocol() == protocol);
	}
	WHEN("Testing GetDomain")
	{
		REQUIRE(correctUrl.GetDomain() == domain);
	}
	WHEN("Testing GetDocument")
	{
		REQUIRE(correctUrl.GetDocument() == document);
	}
	WHEN("Testing GetPort")
	{
		REQUIRE(correctUrl.GetPort() == port);
	}
	WHEN("Testing GetURL")
	{
		REQUIRE(correctUrl.GetURL() == correctStringUrl);
	}
}