#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <cstdint>

class HTTP_Request
{
	public:
		HTTP_Request();

		const std::string& getHostName() const;
		const std::string& getTimeStamp() const;
		const std::string& getRequestName() const;
		std::uint32_t getReturnCode() const;
		std::uint32_t getReturnSize() const;

		std::string getRequestType() const;
		std::string getRequestURI() const;
	
		void setHostName(const std::string&);
		void setTimeStamp(const std::string&);
		void setRequestName(const std::string&);
		void setReturnCode(std::uint32_t);
		void setReturnSize(std::uint32_t);

		bool operator==(const HTTP_Request&) const;

	private:
		std::string m_hostName;
		std::string m_timeStamp;
		std::string m_requestName;
		std::uint32_t m_returnCode;
		std::uint32_t m_returnSize;
};

#endif
