#pragma once
#include <iostream>
#include <windows.h>

HANDLE createFile() {
	HANDLE hCreateFile;
	try {
		hCreateFile = CreateFile(
			L"\\\\.\\pipe\\MyNamedPipe",
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}
	catch (std::exception& e) {

	}
	return hCreateFile;
}

BOOL readFromFile(HANDLE& hCreateFile, char szReadFileBuffer[], DWORD dwReadFileBufferSize, DWORD& dwNoBytesReadForReading) {
	BOOL bReadFile;
	try {
		bReadFile = ReadFile(
			hCreateFile,
			szReadFileBuffer,
			dwReadFileBufferSize,
			&dwNoBytesReadForReading,
			NULL
		);
		std::cout << "Read from pipe: " << szReadFileBuffer << std::endl;
	}
	catch (std::exception& e) {
		bReadFile = FALSE;
	}
	return bReadFile;
}

BOOL writeToFile(HANDLE& hCreateFile, char szWriteFileBuffer [], DWORD dwWriteFileBufferSize, DWORD& dwNoBytesReadForWriting) {
	BOOL bWriteFile;
	try {
		bWriteFile = WriteFile(
			hCreateFile,
			szWriteFileBuffer,
			dwWriteFileBufferSize,
			&dwNoBytesReadForWriting,
			NULL
		);
	}
	catch (std::exception& e) {
		bWriteFile = FALSE;
	}
	return bWriteFile;
}
