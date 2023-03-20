#include "URLHandler.h"
#include "URLHandlerTests.h"


Protocol ParseProtocol(const std::string& protocolStr)
{
	if (protocolStr == "ftp")
	{
		return Protocol::FTP;
	}
	else if (protocolStr == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolStr == "https")
	{
		return Protocol::HTTPS;
	}

	throw std::invalid_argument("invalid URL-protocol");
}

std::string ParseHost(const std::string hostStr)
{
	if (hostStr.empty())
	{
		throw std::invalid_argument("empty URL-host");
	}
	
	return hostStr;
}

int ParsePort(const std::string& portStr, Protocol protocol)
{
	if (portStr.empty())
	{
		return DEFAULT_PORTS.at(protocol);
	}

	int port;
	try
	{
		port = std::stoi(portStr);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("invalid URL-port");
	}

	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw std::invalid_argument("URL-port out of range");
	}

	return port;
}

URLForm ParseURL(const std::string& url)
{
	std::regex urlRegex(R"((ftp|https?)://([0-9A-Za-z\-.]+)(?::(\d+))?(?:/(.*))?)", std::regex_constants::icase);
	URLForm unpackedURL;
	std::smatch urlMatch;

	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		throw std::invalid_argument("invalid URL");
	}

	unpackedURL.url = url;

	std::string protocol = urlMatch[1].str();
	std::transform(protocol.begin(), protocol.end(), protocol.begin(), [](unsigned char c) { return std::tolower(c); });

	unpackedURL.protocol = ParseProtocol(protocol);
	unpackedURL.host = ParseHost(urlMatch[HOST_REGEX_INDEX].str());
	unpackedURL.port = ParsePort(urlMatch[PORT_REGEX_INDEX].str(), unpackedURL.protocol);
	unpackedURL.document = urlMatch[DOCUMENT_REGEX_INDEX].str();

	return unpackedURL;
}

void PrintUnpackedURL(std::ostream& output, const URLForm& urlForm)
{
	output << urlForm.url << std::endl
		<< "HOST: " << urlForm.host << std::endl
		<< "PORT: " << urlForm.port << std::endl
		<< "DOC: " << urlForm.document << std::endl;
}

void ParseURLFromStreams(std::istream& input, std::ostream& output)
{
	std::string url;
	while (std::getline(input, url))
	{
		try
		{
			PrintUnpackedURL(output, ParseURL(url));
		}
		catch (const std::exception& e)
		{
			output << "URL parsing error: " << e.what() << std::endl;
		}
	}
}