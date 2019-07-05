#include <iostream>
#include <fstream>

#include "Types.h"
class FileIO
{

private:

	std::fstream sFile;
	const char *pName;
	std::ios_base::openmode mode;

	DWORD dwError;

public:

	~FileIO();
	FileIO(const char *pName, std::ios_base::openmode mode);

	bool open();
	bool read(BYTE *pData, DWORD dwBufSize, DWORD &dwPos);
	bool write(const BYTE *pData, DWORD dwBufSize, DWORD &dwPos);

	size_t getSize();
	DWORD getError();
};
