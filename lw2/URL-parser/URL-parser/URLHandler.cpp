#include "URLHandler.h"

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
		throw std::invalid_argument("invalid URL-port value");
	}

	return port;
}

URLForm ParseURL(const std::string& url)
{
	std::regex urlRegex(R"(^(\w+):\/\/([^:\/\s]+)(?::(\d+))?\/(.*)$)");
	URLForm unpackedURL;
	std::smatch urlMatch;

	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		throw std::invalid_argument("invalid URL");
	}
	unpackedURL.url = url;
	unpackedURL.protocol = ParseProtocol(urlMatch[1].str());
	unpackedURL.host = ParseHost(urlMatch[2].str());
	unpackedURL.port = ParsePort(urlMatch[3].str(), unpackedURL.protocol);
	unpackedURL.document = urlMatch[4].str();

	return unpackedURL;
}

void PrintUnpackedURL(std::ostream& output, const URLForm& urlForm)
{
	output << urlForm.url << '\n' << "HOST: " << urlForm.host << "\n" << "PORT: " << urlForm.port << "\n" << "DOC: " << urlForm.document << '\n';
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
			output << "URL parsing error: " << e.what() << '\n';
		}
	}
}