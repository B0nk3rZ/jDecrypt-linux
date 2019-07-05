#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "Types.h"
class CryptAES 
{

private:
	BYTE pKey[16];
	BYTE pIV[16];
	EVP_CIPHER_CTX* ectx;
	EVP_CIPHER_CTX* dctx;
	BYTE* plaintext;
	int plen;
	BYTE* ciphertext;
	int clen;

	void HandleErrors(bool dontabort=false);

public:
	~CryptAES();
	CryptAES(BYTE *pKey, BYTE *pIV);
	
	int Encrypt(BYTE *pData, DWORD *pdwDataSize, DWORD dwBufferSize, BOOL bFinal);
	int Decrypt(BYTE *pData, DWORD *pdwDataSize, BOOL bFinal);
};