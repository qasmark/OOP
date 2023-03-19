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
	int port;
	std::string document;
};

Protocol ParseProtocol(const std::string& protocolStr);

std::string ParseHost(const std::string hostStr);

int ParsePort(const std::string& portStr, Protocol protocol);

URLForm ParseURL(const std::string& url);

void PrintUnpackedURL(std::ostream& output, const URLForm& urlForm);



void ParseURLFromStreams(std::istream& input, std::ostream& output);