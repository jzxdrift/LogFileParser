#include <iostream>
#include <string>
#include <cassert>

#include "HTTP_Request.h"
#include "Utility.h"

void testProcessInput()
{
	std::string testInput = "wpbfl2-45.gate.net [29:23:55:46] \"GET /information.html HTTP/1.0\" 200 617";
	HTTP_Request testRequest;

	processInput(testInput, testRequest);

	assert(testRequest.getHostName() == "wpbfl2-45.gate.net");
	assert(testRequest.getTimeStamp() == "[29:23:55:46]");
	assert(testRequest.getRequestName() == "GET /information.html HTTP/1.0");
	assert(testRequest.getReturnCode() == 200);
	assert(testRequest.getReturnSize() == 617);

	assert(testRequest.getRequestType() == "GET");
	assert(testRequest.getRequestURI() == "/information.html");

	std::cout << "processInput test succeeded" << std::endl;
}