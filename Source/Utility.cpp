#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <utility>
#include <algorithm>

#include "Utility.h"
#include "HTTP_Request.h"

void openFile(const char argv[])
{
	std::ifstream ifs;
	ifs.open(argv, std::ios::in);

	if(ifs.is_open())
	{
		processFile(ifs);
		ifs.close();
	}
	else
		std::cerr << "Error opening file" << std::endl;

	//pause before terminating
	std::cin.get();
}

void processFile(std::ifstream& ifs)
{
	HTTP_Request request;
	std::vector<HTTP_Request> requests;

	std::string input;
	while(!ifs.eof())
	{
		//read 1 line from file
		std::getline(ifs, input);
		//assign values to HTTP_Request object members accordingly
		processInput(input, request);
		requests.push_back(request);
	}

	std::cout << "----------------------------------------------" << std::endl;
	showAccessPerHost(requests);

	std::cout << std::endl;
	showAccessSuccess(requests);
	std::cout << "----------------------------------------------" << std::endl;
}

void processInput(std::string& input, HTTP_Request& request)
{
	//extract request name from original input string and omit quotation marks
	size_t startDelim = input.find('\"');
	size_t endDelim = input.find_last_of('\"');
	std::string tempString = input.substr(startDelim + 1, endDelim - startDelim - 1);
	
	//set m_requestName member in HTTP_Request
	request.setRequestName(tempString);

	//remove request name and additional whitespace from original input string
	input.erase(startDelim, endDelim - startDelim + 2);

	//set m_hostName member in HTTP_Request
	std::istringstream iss(input);
	iss >> tempString;
	request.setHostName(tempString);

	//set m_timeStamp member in HTTP_Request
	iss >> tempString;
	request.setTimeStamp(tempString);

	//set m_returnCode member in HTTP_Request
	uint32_t val = 0;
	iss >> val;
	request.setReturnCode(val);

	//set m_returnSize member in HTTP_Request
	iss >> val;
	//check for hyphen sign conversion failure
	if(iss.fail())
		val = 0;
	request.setReturnSize(val);
}

void showAccessPerHost(const std::vector<HTTP_Request>& requests)
{
	//collection of pairs of HTTP_Request and number of accesses to server per host
	std::vector<std::pair<HTTP_Request, uint32_t>> requestsPerHost;

	//running total of accesses to server per host
	uint32_t requestAccessTotal = 0;
	for(size_t i = 0; i < requests.size(); ++i)
	{
		HTTP_Request curRequest = requests[i];

		for(const auto& req : requests)
		{
			//compare current request with all other requests in collection by host name
			if(curRequest == req)
				++requestAccessTotal;
		}

		requestsPerHost.push_back(std::make_pair(curRequest, requestAccessTotal));
		requestAccessTotal = 0;
	}

	//sort ascending by host name
	std::sort(requestsPerHost.begin(), requestsPerHost.end(), [](const auto& left, const auto& right) -> bool
	{
		return left.first.getHostName() < right.first.getHostName();
	});

	//remove duplicate host names
	requestsPerHost.erase(std::unique(requestsPerHost.begin(), requestsPerHost.end()), requestsPerHost.end());

	//sort descending by number of accesses to server per host
	std::sort(requestsPerHost.begin(), requestsPerHost.end(), [](const auto& left, const auto& right) -> bool
	{
		return left.second > right.second;
	});

	std::cout << "Number of accesses to web server per host:" << std::endl;
	for(const auto& req : requestsPerHost)
		std::cout << req.first.getHostName() << " " << req.second << std::endl;
}

void showAccessSuccess(const std::vector<HTTP_Request>& requests)
{
	const std::string ACCESS_TYPE = "GET";
	const uint32_t HTTP_OK = 200;

	//collection of pairs of HTTP_Request and number of successful resource accesses by URI
	std::vector<std::pair<HTTP_Request, uint32_t>> requestsPerURI;

	//running total of successful resource accesses by URI
	uint32_t successRequestAccessTotal = 0;
	for(size_t i = 0; i < requests.size(); ++i)
	{
		if(requests[i].getRequestType() == ACCESS_TYPE && requests[i].getReturnCode() == HTTP_OK)
		{
			++successRequestAccessTotal;
			for(size_t j = i + 1; j < requests.size(); ++j)
			{
				//compare current request with next requests in collection by request URI
				if(requests[i].getRequestURI() == requests[j].getRequestURI()
					&& requests[j].getRequestType() == ACCESS_TYPE
					&& requests[j].getReturnCode() == HTTP_OK)
				{
					++successRequestAccessTotal;
				}
			}

			requestsPerURI.push_back(std::make_pair(requests[i], successRequestAccessTotal));
			successRequestAccessTotal = 0;
		}
	}

	//sort ascending by request URI
	std::sort(requestsPerURI.begin(), requestsPerURI.end(), [](const auto& left, const auto& right) -> bool
	{
		return left.first.getRequestURI() < right.first.getRequestURI();
	});

	//remove duplicate URIs
	auto it = std::unique(requestsPerURI.begin(), requestsPerURI.end(), [](const auto& left, const auto& right) -> bool
	{
		return left.first.getRequestURI() == right.first.getRequestURI();
	});
	requestsPerURI.erase(it, requestsPerURI.end());

	//sort descending by number of successful resource accesses by URI
	std::sort(requestsPerURI.begin(), requestsPerURI.end(), [](const auto& left, const auto& right) -> bool
	{
		return left.second > right.second;
	});

	std::cout << "Number of successful resource accesses by URI:" << std::endl;
	for(const auto& req : requestsPerURI)
		std::cout << req.first.getRequestURI() << " " << req.second << std::endl;
}
