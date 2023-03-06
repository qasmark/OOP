#include "HTMLManager.h"

constexpr char UNIVERSAL_LETTER = '&';

using Dict = std::vector<std::pair<std::string, std::string>>;

const Dict RULES_OF_REPLACE =
{
	{ "\"", "&qout;" },
	{ "'", "&apos;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "&", "&amp;" }
};

std::string FindAndReplaceEntity(std::string html, size_t& replacePos) 
{
	for (size_t rule = 0; rule < RULES_OF_REPLACE.size(); ++rule)
	{
		if (html.compare(replacePos, RULES_OF_REPLACE[rule].second.length(), RULES_OF_REPLACE[rule].second) == 0)
		{
			replacePos += RULES_OF_REPLACE[rule].second.length();
			return RULES_OF_REPLACE[rule].first;
		}
	}
	++replacePos;
	return  { UNIVERSAL_LETTER };
};

std::string HTMLDecode(std::string const& html)
{
	size_t searchPos = 0;
	std::string result;

	while (searchPos < html.length())
	{
		size_t replacePosition = html.find(UNIVERSAL_LETTER, searchPos);
		result.append(html, searchPos, replacePosition - searchPos);

		if (replacePosition == std::string::npos)
		{
			break;
		}
		auto const pattern = FindAndReplaceEntity(html, replacePosition);
		result.append(pattern);
		searchPos = replacePosition;
	}
	return result;
}

void HtmlDecodeInStreams(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (line == "EXIT")
		{
			break;
		}
		output << HTMLDecode(line) << std::endl;
	}
}