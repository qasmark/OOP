#pragma once

Protocol ParseProtocol(const std::string& protocolStr);

std::string ParseHost(const std::string hostStr);

int ParsePort(const std::string& portStr, Protocol protocol);

URLForm ParseURL(const std::string& url);

void PrintUnpackedURL(std::ostream& output, const URLForm& urlForm);