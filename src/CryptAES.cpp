#include <cstring>

#include "CryptAES.h"

void CryptAES::HandleErrors(bool dontabort)
{
    ERR_print_errors_fp(stderr);
    if(!dontabort) abort();
}

CryptAES::CryptAES(BYTE *pKey, BYTE *pIV)
{
	std::memcpy(this->pKey, pKey, 16);
	std::memcpy(this->pIV, pIV, 16);

	if(!(this->ectx = EVP_CIPHER_CTX_new()))
		this->HandleErrors();

	if(1 != EVP_EncryptInit_ex(this->ectx, EVP_aes_128_cbc(), NULL, this->pKey, this->pIV))
		this->HandleErrors();

	//if(1 != EVP_CIPHER_CTX_set_padding(this->ectx, 0))
	//	this->HandleErrors();

	if(!(this->dctx = EVP_CIPHER_CTX_new()))
		this->HandleErrors();

	if(1 != EVP_DecryptInit_ex(this->dctx, EVP_aes_128_cbc(), NULL, this->pKey, this->pIV))
		this->HandleErrors();

	//if(1 != EVP_CIPHER_CTX_set_padding(this->dctx, 0))
	//	this->HandleErrors();
}

CryptAES::~CryptAES()
{
	if (this->ectx != NULL) 
		EVP_CIPHER_CTX_free(this->ectx);

	if (this->dctx != NULL) 
		EVP_CIPHER_CTX_free(this->dctx);
}

int CryptAES::Encrypt(BYTE *pData, DWORD *pdwDataSize, DWORD dwBufferSize, BOOL bFinal)
{
	int len;
	if(this->ciphertext == NULL)
		this->ciphertext = new BYTE[(*pdwDataSize)+16];

	if (this->pKey == NULL)
		return -1;

	if(1 != EVP_EncryptUpdate(this->ectx, this->ciphertext, &len, pData, *pdwDataSize))
		this->HandleErrors(true);
	this->clen = len;

	if(bFinal && (1 != EVP_EncryptFinal_ex(this->ectx, this->ciphertext + this->clen, &len)))
		this->HandleErrors(true);
	else
		this->clen += len;

	std::memcpy(pData, this->ciphertext, this->clen);
	*pdwDataSize = this->clen;

	return ERR_peek_last_error();
}

int CryptAES::Decrypt(BYTE *pData, DWORD *pdwDataSize, BOOL bFinal)
{
	int len;
	if(this->plaintext == NULL)
		this->plaintext = new BYTE[*pdwDataSize];

	if (this->pKey == NULL)
		return -1;

	if(1 != EVP_DecryptUpdate(this->dctx, this->plaintext, &len, pData, *pdwDataSize))
		this->HandleErrors(true);
	this->plen = len;

	if(bFinal && (1 != EVP_DecryptFinal_ex(this->dctx, this->plaintext + this->plen, &len)))
		this->HandleErrors(true);
	else
		this->plen += len;

	std::memcpy(pData, this->plaintext, this->plen);
	*pdwDataSize = this->plen;

	return ERR_peek_last_error();
}
