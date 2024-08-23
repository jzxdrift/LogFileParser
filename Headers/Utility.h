#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../Headers/HTTP_Request.h"

void openFile(const char []);
void processFile(std::ifstream&);
void processInput(std::string&, HTTP_Request&);
void showAccessPerHost(const std::vector<HTTP_Request>&);
void showAccessSuccess(const std::vector<HTTP_Request>&);
