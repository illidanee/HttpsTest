#include <iostream>
#include <string>

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#pragma comment (lib, "libeay32.lib")
#pragma comment (lib, "ssleay32.lib")


extern void NoSafeConnect();
extern void SafeConnect();


int main(int argc, char** argv)
{
	//NoSafeConnect();
	SafeConnect();

	return 0;
}



void NoSafeConnect()
{
	SSL_library_init();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();



	BIO * bio = BIO_new_connect("https://www.taobao.com:80");
	if(bio == NULL)
	{
		/* Handle the failure */
	}
	if(BIO_do_connect(bio) <= 0)
	{
		/* Handle failed connection */
	}



	char* pRequestLine = 
		"GET https://www.taobao.com/ HTTP/1.1\r\n";
	char* pRequestHead = 
		"Host: https://www.taobao.com\r\n";
	char* pRequestBlank =
		"\r\n";
	char* pRequestContext = 
		"";

	std::string info = pRequestLine;
	info += pRequestHead;
	info += pRequestBlank;
	info += pRequestContext;

	int wRes = BIO_write(bio, info.c_str(), info.length());

	char buf[256] = {};
	int rRes = BIO_read(bio, buf, 256);
	printf(buf);

	BIO_free_all(bio);
}

void SafeConnect()
{
	SSL_library_init();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();



	SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
	BIO *bio = BIO_new_ssl_connect(ctx);
	SSL * ssl;
	BIO_get_ssl(bio, & ssl);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

	BIO_set_conn_hostname(bio, "api.weixin.qq.com:443");
	if(BIO_do_connect(bio) <= 0)
	{
		/* Handle failed connection */
	}



	char* pRequestLine = 
		"GET https://api.weixin.qq.com/cgi-bin/token?grant_type=client_credential&appid=APPID&secret=APPSECRET HTTP/1.1\r\n";
	char* pRequestHead = 
		"Host: www.baidu.com\r\n\
Connection: keep-alive\r\n";
	char* pRequestBlank =
		"\r\n";
	char* pRequestContext = 
		"";

	std::string info = pRequestLine;
	info += pRequestHead;
	info += pRequestBlank;
	info += pRequestContext;

	const char* pAppID = "wx12708cc5571f2a9a";
	const char* pAppSecret = "bae9572c4e210e6c485d6dd35dc88e3a";
	const char* pAPPID = "APPID";
	const char* pAPPSECRET = "APPSECRET";
	int pos1 = info.find(pAPPID);
	info.replace(pos1, strlen(pAPPID), pAppID);
	int pos2 = info.find(pAPPSECRET);
	info.replace(pos2, strlen(pAPPSECRET), pAppSecret);


	int wRes = BIO_write(bio, info.c_str(), info.length());

	char buf[1024] = {};
	int rRes = BIO_read(bio, buf, 1024);
	printf(buf);


	BIO_free_all(bio);
	SSL_CTX_free( ctx );
}