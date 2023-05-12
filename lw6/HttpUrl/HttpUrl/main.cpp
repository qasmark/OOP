#include "CHttpUrl.h"
#include <iostream>

void PrintUrlInfo(std::ostream& outputStream, CHttpUrl const& httpUrl)
{
	outputStream << "Protocol: " << CHttpUrl::ParseProtocolToString(httpUrl.GetProtocol())
		<< std::endl << "Port: " << httpUrl.GetPort() << std::endl
		<< "Domain: " << httpUrl.GetDomain() << std::endl
		<< "Document: " << httpUrl.GetDocument() << std::endl
		<< std::endl;
}

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			PrintUrlInfo(std::cout, url);
		}
		catch (CUrlParsingError const& e)
		{
			std::cout << e.what() << std::endl
				<< std::endl;
		}
	}

	return 0;
}