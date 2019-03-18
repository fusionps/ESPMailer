// #include <ESP8266WiFi.h>
#include <WiFi.h>
// #include <Time.h>
#include <NTPClient.h>
#include <ETH.h>
// #include <NTP.h>
// #ifndef NTP_H
// #error "You haven't installed the ESP-NTP Library. It can be downloaded from http://github.com/ArduinoHannover/NTP"
// #endif

#ifndef MAIL_H
#define MAIL_H

#ifndef null
#define null NULL
#endif

typedef enum SMTP_CONNECTION_ERROR {
    SMTP_ERROR_OK,
    SMTP_ERROR_TCP_FAIL,
    SMTP_ERROR_STARTTLS_FAIL,
    SMTP_ERROR_SSL_FAIL,
    SMTP_ERROR_AUTHENTICATION_FAIL,
    SMTP_ERROR_SENDING_FAIL
} SMTP_ERROR;

		
enum AUTH {
	PLAIN,
	LOGIN,
	XOAUTH2,	// Not supported
	NTLM,		// Not supported
	CRAM_MD5	// Not supported
};

class ESPMailer {
	private:
		const char* _b64_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		const char* _delim = "\n";
		
		WiFiClient _smtp;
		
		char* _from = NULL;
		char* _fromName = NULL;
		char* _to = NULL;
		char* _toNames = NULL;
		char* _cc = NULL;
		char* _ccNames = NULL;
		char* _bcc = NULL;
		char* _bccNames = NULL;
		
		boolean html = false;
		float _timezone = 0;
		int8_t do_debug = 0;
		
		boolean sendCMD(const char*, uint16_t);
		void a3_to_a4(unsigned char*, unsigned char*);
		int base64_encode(char*, const char*, int);
		char* append(char*&, const char*);
		boolean SMTPTo(char*);
		boolean HeaderTo(const char*, char*, char*);
		String last_reply;
	public:
		ESPMailer();
		~ESPMailer();
		
		void setFrom(const char*);
		void setFrom(const char*, const char*);
		void addAddress(const char*);
		void addAddress(const char*, const char*);
		void addCC(const char*);
		void addCC(const char*, const char*);
		void addBCC(const char*);
		void addBCC(const char*, const char*);
		void setTimezone(float);
		void setDebugLevel(uint8_t);
		boolean isHTML();
		boolean isHTML(boolean);
		SMTP_ERROR send();
		
		String Host;
		uint16_t Port = 25;
		boolean SMTPAuth = false;
		String Username;
		String Password;
		String Subject;
		String Body;
		uint16_t Timeout = 300;
		String AltBody;
		AUTH AuthType = PLAIN;
		
		boolean TLS = false;

		NTPClient *ntp;
};
#endif
