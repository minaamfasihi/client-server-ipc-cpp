#include <iostream>
#include <Windows.h>
#include "Server.h"
#include "ServerObject.h"
#include <string>
#include <vector>

// Copied the below two methods i.e. endsWith and split from stackoverflow. https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
bool endsWith(const std::string& s, const std::string& suffix)
{
	return s.size() >= suffix.size() &&
		s.substr(s.size() - suffix.size()) == suffix;
}

std::vector<std::string> split(const std::string& s, const std::string& delimiter, const bool& removeEmptyEntries = false)
{
	std::vector<std::string> tokens;

	for (size_t start = 0, end; start < s.length(); start = end + delimiter.length())
	{
		size_t position = s.find(delimiter, start);
		end = position != std::string::npos ? position : s.length();

		std::string token = s.substr(start, end - start);
		if (!removeEmptyEntries || !token.empty())
		{
			tokens.push_back(token);
		}
	}

	if (!removeEmptyEntries &&
		(s.empty() || endsWith(s, delimiter)))
	{
		tokens.push_back("");
	}

	return tokens;
}

std::vector<ServerObject> _servers;

// for commands
enum InputType { CreateInstance = 1, CallMethodOnInstance, ReturnAttributes };

// forward declarations
bool CreateObject(int, bool, std::string);
void ProcessInput(std::string, HANDLE&);

void InitializeServerAndStart() {
	BOOL bConnectNamedPipe;

	BOOL bWriteFile;

	char szWriteFileBuffer[1023] = "Hello From NamedPipe Server";
	DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesWrite;

	BOOL bFlushFileBuffer;

	BOOL bReadFile;
	char szReadFileBuffer[1023];
	DWORD dwReadBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesRead;

	HANDLE hNamedPipe = getNamedPipe();
	if (hNamedPipe == INVALID_HANDLE_VALUE) return;

	bConnectNamedPipe = ConnectNamedPipe(hNamedPipe, NULL);
	if (bConnectNamedPipe == FALSE) {
		std::cout << "Connect Named Pipe failed" << std::endl;
	}
	std::cout << "Connect named pipe successful" << std::endl;

	readFromPipe(hNamedPipe,
		szReadFileBuffer,
		dwReadBufferSize,
		dwNoBytesRead);
	std::cout << "Read this from pipe: " << szReadFileBuffer << std::endl;
	ProcessInput(szReadFileBuffer, hNamedPipe);

	readFromPipe(hNamedPipe,
		szReadFileBuffer,
		dwReadBufferSize,
		dwNoBytesRead);
	std::cout << "Read this from pipe: " << szReadFileBuffer << std::endl;
	ProcessInput(szReadFileBuffer, hNamedPipe);

	readFromPipe(hNamedPipe,
		szReadFileBuffer,
		dwReadBufferSize,
		dwNoBytesRead);
	std::cout << "Read this from pipe: " << szReadFileBuffer << std::endl;
	ProcessInput(szReadFileBuffer, hNamedPipe);

	DisconnectNamedPipe(hNamedPipe);
	CloseHandle(hNamedPipe);
}

bool CreateObject(int n, bool t, std::string str) {
	try {
		ServerObject so(n, t, str);
		_servers.push_back(so);
	}
	catch (std::exception& e) {
		return false;
	}
	return true;
}

void ProcessInput(std::string input, HANDLE& hNamedPipe) {
	try {
		std::vector<std::string> inputArray = split(input, "##");
		
		int i = stoi(inputArray[1]);
		int num = -1; bool t = false; std::string str = "";
		char szWriteFileBuffer[1023];
		DWORD dwWriteBufferSize = 0; 
		DWORD dwNoBytesWrite;
		std::string args;
		
		switch (i) {
			case InputType::CreateInstance:
				num = stoi(split(inputArray[2], "=")[1]);
				t = (split(inputArray[3], "=")[1]) == "true" ? true : false;
				str = split(inputArray[4], "=")[1];
				if (CreateObject(num, t, str)) {
					strcpy_s(szWriteFileBuffer, "Successfully created object");
				}
				else {
					strcpy_s(szWriteFileBuffer, "Failed to create object");
				}
				dwWriteBufferSize = sizeof(szWriteFileBuffer);
				break;

			case InputType::CallMethodOnInstance:
				args = split(inputArray[2], "=")[1];
				if (args == "foo") {
					if (_servers.size() > 0) {
						_servers[0].foo();
						strcpy_s(szWriteFileBuffer, "Called foo method successfully");
					}
					else {
						strcpy_s(szWriteFileBuffer, "Failure. No objects on server");
					}
					dwWriteBufferSize = sizeof(szWriteFileBuffer);
				}
				break;

			case InputType::ReturnAttributes:
				args = split(inputArray[2], "=")[1];
				if (args == "attributes") {
					if (_servers.size() > 0) {
						std::string temp = _servers[0].serialize_attributes();
						strcpy_s(szWriteFileBuffer, temp.c_str());
					}
					else {
						strcpy_s(szWriteFileBuffer, "Failure. No objects on server");
					}
					dwWriteBufferSize = sizeof(szWriteFileBuffer);
				}
				break;
		}
	
		writeToPipe(hNamedPipe,
			szWriteFileBuffer,
			dwWriteBufferSize,
			dwNoBytesWrite);

		flushFileBuffer(hNamedPipe);
	}
	catch (std::exception& e) {
	}
}

int main() {
	InitializeServerAndStart();
	return 0;
}
