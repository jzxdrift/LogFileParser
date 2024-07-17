#include <string>
#include <cstdint>
#include <sstream>

#include "../Headers/HTTP_Request.h"

HTTP_Request::HTTP_Request()
{

}

const std::string& HTTP_Request::getHostName() const
{
	return m_hostName;
}

const std::string& HTTP_Request::getTimeStamp() const
{
	return m_timeStamp;
}

const std::string& HTTP_Request::getRequestName() const
{
	return m_requestName;
}

uint32_t HTTP_Request::getReturnCode() const
{
	return m_returnCode;
}

uint32_t HTTP_Request::getReturnSize() const
{
	return m_returnSize;
}

std::string HTTP_Request::getRequestType() const
{
	std::string requestType;
	std::istringstream iss(m_requestName);
	//extract first word as request type
	iss >> requestType;

	return requestType;
}

std::string HTTP_Request::getRequestURI() const
{
	std::string requestURI;
	std::istringstream iss(m_requestName);
	//extract second word as request URI
	iss >> requestURI >> requestURI;

	return requestURI;
}

void HTTP_Request::setHostName(const std::string& hostName)
{
	m_hostName = hostName;
}

void HTTP_Request::setTimeStamp(const std::string& timeStamp)
{
	m_timeStamp = timeStamp;
}

void HTTP_Request::setRequestName(const std::string& requestName)
{
	m_requestName = requestName;
}

void HTTP_Request::setReturnCode(uint32_t returnCode)
{
	m_returnCode = returnCode;
}

void HTTP_Request::setReturnSize(uint32_t returnSize)
{
	m_returnSize = returnSize;
}

bool HTTP_Request::operator==(const HTTP_Request& otherRequest) const
{
	return m_hostName == otherRequest.m_hostName;
}
