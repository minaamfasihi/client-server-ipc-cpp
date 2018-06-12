#pragma once
#include <iostream>
#include <ctime>
#include <string>

HANDLE getNamedPipe() {
	HANDLE hCreateNamedPipe;
	char inputBuffer[1023];
	char outputBuffer[1023];
	DWORD dwszInputBuffer = sizeof(inputBuffer);
	DWORD dwszOutputBuffer = sizeof(outputBuffer);

	try {
		hCreateNamedPipe = CreateNamedPipe(
			L"\\\\.\\pipe\\MyNamedPipe",
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			dwszOutputBuffer,
			dwszInputBuffer,
			0,
			NULL
		);
	}
	catch (std::exception& e) {
		hCreateNamedPipe = INVALID_HANDLE_VALUE;
	}
	return hCreateNamedPipe;
}

BOOL writeToPipe(HANDLE& hNamedPipe, char szWriteFileBuffer[], DWORD dwWriteBufferSize, DWORD& dwNoBytesWrite) {
	BOOL bWriteFile = FALSE;

	try {
		bWriteFile = WriteFile(
			hNamedPipe,
			szWriteFileBuffer,
			dwWriteBufferSize,
			&dwNoBytesWrite,
			NULL
		);
		if (bWriteFile == FALSE) std::cout << "Write File Failed" << GetLastError() << std::endl;
		else std::cout << "Write File Success" << std::endl;
	}
	catch (std::exception& e) {
		bWriteFile = FALSE;
	}
	return bWriteFile;
}

BOOL readFromPipe(HANDLE& hNamedPipe, char szReadFileBuffer[], DWORD dwReadBufferSize, DWORD& dwNoOfBytesRead) {
	BOOL bReadFile = FALSE;
	try {
		bReadFile = ReadFile(
				hNamedPipe,
				szReadFileBuffer,
				dwReadBufferSize,
				&dwNoOfBytesRead,
				NULL
		);
		if (bReadFile == FALSE) std::cout << "ReadFile failed" << std::endl;
		else std::cout << "ReadFile success" << std::endl;
	}
	catch (std::exception& e) {
		bReadFile = FALSE;
	}
	return bReadFile;
}

BOOL flushFileBuffer(HANDLE& hNamedPipe) {
	BOOL bFlushFileBuffer = FALSE;
	try {
		bFlushFileBuffer = FlushFileBuffers(hNamedPipe);
		if (bFlushFileBuffer == FALSE) std::cout << "Flush file buffer failed" << std::endl;
		else std::cout << "Flush file buffer success" << std::endl;
	}
	catch (std::exception& e) {
		bFlushFileBuffer = FALSE;
	}
	return bFlushFileBuffer;
}
