#include <errno.h>
#include "FileIO.h"

FileIO::FileIO(const char *pName, std::ios_base::openmode mode)
	: pName(pName), mode(mode) { }

FileIO::~FileIO()
{
	if (this->pName)
		this->pName = 0;

	if (this->sFile.is_open()){
		this->sFile.clear();
		this->sFile.close();
	}
}

bool FileIO::open()
{
	this->sFile.open(this->pName, this->mode);

	if(!this->sFile.is_open()){
		this->dwError = errno;
		return false;
	}

	return true;
}

bool FileIO::read(BYTE *pData, DWORD dwBufSize, DWORD &dwPos)
{
	if (pData == NULL){
		this->dwError = EINVAL;
		return false;
	}

	this->sFile.seekg(dwPos);

	this->sFile.read((char*)pData, dwBufSize);

	dwPos = this->sFile.tellg();

	if(this->sFile.eof()){
		return true;
	}

	if(this->sFile.bad()){
		this->dwError = errno;
		return false;
	}

	return true;
}

bool FileIO::write(const BYTE *pData, DWORD dwBufSize, DWORD &dwPos)
{
	if (pData == NULL)
		return false;

	this->sFile.seekp(dwPos);

	this->sFile.write((char*)pData, dwBufSize);

	if(this->sFile.bad()){
		this->dwError = errno;
		return false;
	}

	dwPos = this->sFile.tellp();

	return true;
}

size_t FileIO::getSize()
{
	if(!this->sFile.is_open())
		return INVALID_FILE_SIZE;
	std::streampos sp = this->sFile.tellg();
	this->sFile.seekg(0, std::ios::end);
	size_t size = this->sFile.tellg();
	this->sFile.seekg(sp);
	return size;
}

DWORD FileIO::getError()
{
	return this->dwError;
}