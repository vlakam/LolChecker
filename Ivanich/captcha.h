#pragma once
#include "CList.h"
#include "CHTTP.h"
#include "FileReader.h"
class Captcha
{
public:

	struct LoginResponse
	{
		std::string strError;
		std::string strSuccess;
	};

	struct CaptchaInfo
	{
		std::string strAnswer;
		std::string strChallange;		
	};

	struct AccInfo
	{
		std::string strUsername;
		std::string strPassword;
		std::string strSummonerName;
		int iLvl;
		std::string id;
		std::string strUnverified;
	};

	struct ChangeDataStruct
	{
		std::string newPassword;
		std::string newMail;
		std::string message;
		bool success;
	};

	struct PostData
	{
		std::string postKey;
		std::string postValue;
	};

	Captcha();
	~Captcha();

	ChangeDataStruct ChangeData(std::string newDataPassword, std::string newDataMail);
	ChangeDataStruct SendChangeRequest(std::string uri, std::vector<Captcha::PostData> vec);
	std::string GetCaptcha();
	AccInfo GoodAcc;
	LoginResponse CheckLogin(UserData LoginData);

	void SetCaptcha(std::string strAnswer) { this->captcha.strAnswer = strAnswer; }
	int GetLastErrorCode() { return this->lastErrorCode; }
	void GetData();

private:

	CHTTP *HTTP;
	CaptchaInfo captcha;
	
	int lastErrorCode;	
};