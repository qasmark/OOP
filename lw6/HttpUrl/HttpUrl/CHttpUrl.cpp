#include "CHttpUrl.h"

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

const Port HTTP_PORT = 80;
const Port HTTPS_PORT = 443;

const std::string PROTOCOL_REGEX_STRING = "(https?)://";
const std::string DOMAIN_REGEX_STRING = "([0-9A-Za-z\\-.]+)";
const std::string PORT_REGEX_STRING = "(?:\\:([\\d]{1,5}))?";
const std::string DOCUMENT_REGEX_STRING = "(?:(?:/)([\\S]*))?";

const std::regex URL_REGEX = std::regex(PROTOCOL_REGEX_STRING + DOMAIN_REGEX_STRING + PORT_REGEX_STRING + DOCUMENT_REGEX_STRING);
const std::regex DOMAIN_REGEX = std::regex(DOMAIN_REGEX_STRING);
const std::regex DOCUMENT_REGEX = std::regex("([\\S]*)?");

std::string StringToLowerCase(std::string const& str);
Protocol ParseStringToProtocol(std::string const& stringProtocol);
Port ParsePort(std::string const& stringPort, Protocol protocol);
bool IsValidDomain(std::string const& domain);
bool IsValidDocument(std::string const& document);
Port GetDefaultPort(Protocol protocol);

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string copyUrl = StringToLowerCase(url);

	std::smatch matches;

	if (!std::regex_match(copyUrl, matches, URL_REGEX))
	{
		throw CUrlParsingError::InvalidUrl();
	}

	m_protocol = ParseStringToProtocol(matches[1]);
	m_domain = matches[2];
	m_port = ParsePort(matches[3], m_protocol);
	m_document += "/";
	m_document += matches[4];
}

std::string StringToLowerCase(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](char c) { return std::tolower(c); });

	return result;
}

Protocol ParseStringToProtocol(const std::string& stringProtocol)
{
	if (stringProtocol == "http")
	{
		return Protocol::HTTP;
	}

	if (stringProtocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError::InvalidProtocol();
}

Port ParsePort(std::string const& stringPort, Protocol protocol)
{
	if (stringPort.empty())
	{
		return GetDefaultPort(protocol);
	}

	int portNumber;

	try
	{
		portNumber = std::stoi(stringPort);
	}
	catch (...)
	{
		throw CUrlParsingError::InvalidPort();
	}
	// тест, вблизи границы допустимое и недопустимое 
	if (portNumber < MIN_PORT || portNumber > MAX_PORT)
	{
		throw CUrlParsingError::InvalidPort();
	}

	return static_cast<Port>(portNumber);
}

bool IsValidDomain(std::string const& domain)
{
	std::smatch matches;
	return (std::regex_match(domain, matches, DOMAIN_REGEX));
}

bool IsValidDocument(std::string const& document)
{
	std::smatch matches;
	return (std::regex_match(document, matches, DOCUMENT_REGEX));
}

Port GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return HTTP_PORT;
	case Protocol::HTTPS:
		return HTTPS_PORT;
	default:
		throw CUrlParsingError::InvalidProtocol();
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError::InvalidDomain();
	}
	m_domain = domain;

	if (!IsValidDocument(document))
	{
		throw CUrlParsingError::InvalidDocument();
	}

	if (document[0] != '/')
	{
		m_document += "/";
	}
	m_document += document;

	m_protocol = protocol;
	m_port = GetDefaultPort(protocol);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, Port port)
	: CHttpUrl(domain, document, protocol)
{
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string url;

	url += ParseProtocolToString(m_protocol);
	url += "://";
	url += m_domain;
	url += (m_port != HTTP_PORT && m_port != HTTPS_PORT) ? ":" + std::to_string(m_port) : "";
	url += m_document;

	return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

Port CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ParseProtocolToString(Protocol protocol)
{

	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		throw CUrlParsingError::InvalidProtocol();
	}
}




