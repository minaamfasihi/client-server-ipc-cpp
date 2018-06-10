#include <iostream>
#include <Windows.h>
#include "Client.h"

void InitializeClientAndStart() {
	HANDLE hCreateFile;

	BOOL bReadFile;
	DWORD dwNoBytesReadForReading;
	char szReadFileBuffer[1023];
	DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);

	BOOL bWriteFile;
	DWORD dwNoBytesReadForWriting;
	char szWriteFileBuffer[1023] = "##1##num=2##truthy=false##myStr=I am here##";
	DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

	hCreateFile = createFile();
	if (hCreateFile == INVALID_HANDLE_VALUE) {
		std::cerr << "File creation failed" << std::endl;
	}

	std::cout << "File Creation success" << std::endl;

	bWriteFile = writeToFile(hCreateFile, szWriteFileBuffer, dwWriteFileBufferSize, dwNoBytesReadForWriting);
	if (bWriteFile == FALSE) {
		std::cout << "WriteFile failed" << std::endl;
	}
	else {
		std::cout << "WriteFile success" << std::endl;
	}

	bReadFile = readFromFile(
		hCreateFile,
		szReadFileBuffer,
		dwReadFileBufferSize,
		dwNoBytesReadForReading
	);

	if (bReadFile == FALSE) {
		std::cout << "Readfile failed" << std::endl;
	}
	else {
		std::cout << "Readfile success" << std::endl;
	}

	strcpy_s(szWriteFileBuffer, "##2##method=foo");
	bWriteFile = writeToFile(hCreateFile, szWriteFileBuffer, dwWriteFileBufferSize, dwNoBytesReadForWriting);
	dwWriteFileBufferSize = sizeof(szWriteFileBuffer);
	
	if (bWriteFile == FALSE) {
		std::cout << "WriteFile failed" << std::endl;
	}
	else {
		std::cout << "WriteFile success" << std::endl;
	}

	bReadFile = readFromFile(
		hCreateFile,
		szReadFileBuffer,
		dwReadFileBufferSize,
		dwNoBytesReadForReading
	);

	if (bReadFile == FALSE) {
		std::cout << "Readfile failed" << std::endl;
	}
	else {
		std::cout << "Readfile success" << std::endl;
	}

	strcpy_s(szWriteFileBuffer, "##3##get=attributes");
	bWriteFile = writeToFile(hCreateFile, szWriteFileBuffer, dwWriteFileBufferSize, dwNoBytesReadForWriting);
	dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

	if (bWriteFile == FALSE) {
		std::cout << "WriteFile failed" << std::endl;
	}
	else {
		std::cout << "WriteFile success" << std::endl;
	}

	bReadFile = readFromFile(
		hCreateFile,
		szReadFileBuffer,
		dwReadFileBufferSize,
		dwNoBytesReadForReading
	);

	if (bReadFile == FALSE) {
		std::cout << "Readfile failed" << std::endl;
	}
	else {
		std::cout << "Readfile success" << std::endl;
	}


	CloseHandle(hCreateFile);
}

int main() {
	InitializeClientAndStart();
	return 0;
}