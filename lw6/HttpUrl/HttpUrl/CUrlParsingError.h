#pragma once

#include <string>
#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
	static CUrlParsingError InvalidUrl();
	static CUrlParsingError InvalidPort();
	static CUrlParsingError InvalidProtocol();
	static CUrlParsingError InvalidDocument();
	static CUrlParsingError InvalidDomain();

private:
	CUrlParsingError(std::string const& message);
};