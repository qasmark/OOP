#pragma once

#include <iostream>
#include <map>
#include <regex>
#include <algorithm>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

constexpr int MIN_PORT = 1;
constexpr int MAX_PORT = 65535;

constexpr int HOST_REGEX_INDEX = 2;
constexpr int PORT_REGEX_INDEX = 3;
constexpr int DOCUMENT_REGEX_INDEX = 4;


const std::map<Protocol, int> DEFAULT_PORTS = {
	{Protocol::FTP, 21},
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443}
};

struct URLForm
{
	std::string url;
	std::string host;
	Protocol protocol;
	int port = 1;
	std::string document;
};

void ParseURLFromStreams(std::istream& input, std::ostream& output);