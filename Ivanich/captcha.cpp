#include <iostream>
#include <regex>
#include "captcha.h"
#include "CHTTP.h"
#include "windows.h"
#include "CLIst.h"
#include "FileIO.h"
#include "FileReader.h"

std::wstring StringToWString(std::string str)
{
	size_t ret;
	wchar_t *pwszWideChar = new wchar_t[(str.length() + 1) * 2]();

	mbstowcs_s(&ret, pwszWideChar, str.length() + 1, str.c_str(), str.length());

	return std::wstring(pwszWideChar);
}

Captcha::~Captcha()
{
	delete this->HTTP;
}

Captcha::Captcha()
{
	this->HTTP = new CHTTP();

	if (!this->HTTP->Open())
		this->lastErrorCode = this->HTTP->GetLastErrorCode();

	this->HTTP->SetFlags(WINHTTP_FLAG_SECURE, true);
}

std::string Captcha::GetCaptcha()
{		
	std::string strPicPath;

	if (this->HTTP->IsOpen() && 
		this->HTTP->Connect(L"www.google.com", 443))
	{
		if (this->HTTP->SendRequest(L"GET", L"/recaptcha/api/reload?c=03AHJ_VuurlCeu8nEIwl-k3nT9fX0IVYaxEic7cN-keN3loPs9NpCNO0W2B6bAvghY4ryJz9gJn_ovYsUIygOnourSkyFuCDOWY5T44uS5gw6PDyJmCGDN7fD6M_vno0uUfXbDNBVWtUpFPMaXVUHaTY412EAzR_n5s_f-HeLJF-nwIFpOea4jvNs3ss2tgTFgm_4U-b1h09FjXzDogkMLQWBOarYjEeUN1w&k=6LcwdeESAAAAAJg_ltVGdjrqlf7Bmbg449SyUcSW&reason=i&type=image", L"", ""))
		{
			std::string strResponse = reinterpret_cast<const char*>(this->HTTP->GetResponse().c_str());

			DWORD dwChallangeStart = strResponse.find("('") + 2,
				 dwChallangeEnd = strResponse.find("',", dwChallangeStart);

			this->captcha.strChallange = strResponse.substr(dwChallangeStart, dwChallangeEnd - dwChallangeStart);

			if (this->captcha.strChallange.size() > 0)
			{
				if (this->HTTP->Connect(L"www.google.com", 443))
				{
					std::wstring strObj = std::wstring(L"/recaptcha/api/image?c=").append(StringToWString(this->captcha.strChallange));

					if (this->HTTP->SendRequest(L"GET", strObj, L"", ""))
					{
						std::basic_string<byte> strResponse = this->HTTP->GetResponse();

						char pwszTempPath[MAX_PATH];

						if (GetTempPathA(MAX_PATH, pwszTempPath))
						{
							char pwszTempFile[MAX_PATH];

							if (GetTempFileNameA(pwszTempPath, "s3c", 0, pwszTempFile))
								DeleteFileA(pwszTempFile);

							strPicPath = pwszTempFile;
							strPicPath.replace(strPicPath.find(".tmp"), 4, ".jpg");

							DWORD dwPos = 0;
							FileIO output(strPicPath.c_str(), GENERIC_WRITE, CREATE_ALWAYS);

							if (output.open())
								output.write(strResponse.c_str(), strResponse.size(), dwPos);
						}
					}
				}
			}
		}
	}

	return strPicPath;
}
void Captcha::GetData()
{
	std::string request = "/api/lol/euw/v1.4/summoner/by-name/" + this->GoodAcc.strSummonerName + "?api_key=870b5b86-95ec-48be-bfab-0e9852323ab3";
	if(this->HTTP->IsOpen() && this->HTTP->Connect(L"euw.api.pvp.net",443))
	{
		if (this->HTTP->SendRequest(L"GET", StringToWString(request),L"",""))
		{
			std::string strResponse = reinterpret_cast<const char*>(this->HTTP->GetResponse().c_str());
			std::string summonerLevel = strResponse.substr(strResponse.find("\"summonerLevel\":") + 16, strResponse.size());
			summonerLevel = summonerLevel.substr(0, summonerLevel.find(","));

			std::string summonerId = strResponse.substr(strResponse.find("\"id\":") + 5, strResponse.size());
			summonerId = summonerId.substr(0, summonerId.find(","));
			
			std::cout << strResponse << std::endl;
			
			int res;
			
			try
			{
				this->GoodAcc.iLvl = std::stoi(summonerLevel);
				this->GoodAcc.id = summonerId;
			}
			catch(std::exception e)
			{
				std::cout << e.what() << std::endl;
				this->GoodAcc.iLvl = -1;
			}
		}
	}
}
Captcha::ChangeDataStruct Captcha::ChangeData(std::string newDataPassword, std::string newDataMail)
{
	ChangeDataStruct CData;
	if(this->HTTP->IsOpen() && this->HTTP->Connect(L"account.leagueoflegends.com", 443))
	{
		if(newDataPassword.size())
		{
			Captcha::PostData* tempData = new Captcha::PostData();
			std::vector<Captcha::PostData> vec;

			(*tempData).postKey = "password-confirm";
			(*tempData).postValue = (std::string) newDataPassword;

			vec.push_back(*tempData);

			(*tempData).postKey = "password-new";
			(*tempData).postValue = (std::string) newDataPassword;

			vec.push_back(*tempData);

			(*tempData).postKey = "password-old";
			(*tempData).postValue = (std::string) this->GoodAcc.strPassword;

			vec.push_back(*tempData);

			CData = this->SendChangeRequest("/update/password", vec);
			if(CData.success)
			{
				CData.newPassword = newDataPassword;
			}

			delete tempData;
		}

		if(newDataMail.size())
		{
			Captcha::PostData* tempData = new Captcha::PostData();
			std::vector<Captcha::PostData> vec;

			(*tempData).postKey = "email";
			(*tempData).postValue = (std::string) newDataMail;

			vec.push_back(*tempData);

			(*tempData).postKey = "email-confirm";
			(*tempData).postValue = (std::string) newDataMail;

			vec.push_back(*tempData);

			(*tempData).postKey = "email-password";
			(*tempData).postValue = (std::string) CData.newPassword;

			vec.push_back(*tempData);

			CData = this->SendChangeRequest("/update/email", vec);
			if(CData.success)
			{
				CData.newMail = newDataMail;
			}

			delete tempData;
		}
	}
	return CData;
}
Captcha::ChangeDataStruct Captcha::SendChangeRequest(std::string uri, std::vector<Captcha::PostData> vec)
{
	ChangeDataStruct CData;
	if(this->HTTP->IsOpen() && this->HTTP->Connect(L"account.leagueoflegends.com", 443))
	{
		std::string strHeader =
			std::string("X-Requested-With: XMLHttpRequest\r\n")
				.append("Referer: https://account.leagueoflegends.com/pm.html\r\n")
				.append("Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n")
				.append("Cookie: PVPNET_REGION=").append("euw");

		std::string strRequest;

		for(int i = 0; i < vec.size(); i++)
		{
			if(!i)
			{
				strRequest = std::string(vec[i].postKey + "=").append(vec[i].postValue);
				continue;
			}
			strRequest.append("&" + vec[i].postKey + "=").append(vec[i].postValue);
		}

		if(this->HTTP->SendRequest(L"POST", StringToWString(uri), StringToWString(strHeader), strRequest))
		{
			std::string strResponseValidation = reinterpret_cast<const char*>(this->HTTP->GetResponse().c_str());
			std::string newStr = strResponseValidation.substr(strResponseValidation.find("\"success\":") + 10, strResponseValidation.size());
			newStr = newStr.substr(0, newStr.find(","));
			if(newStr == "false")
			{
				newStr = strResponseValidation.substr(strResponseValidation.find("\"error\":") + 8, strResponseValidation.size());
				newStr = newStr.substr(0, newStr.find(","));
				CData.message = newStr;
			}
			CData.success = (newStr == "true") ? true : false;
		}
	}
	return CData;
}
Captcha::LoginResponse Captcha::CheckLogin(UserData LoginData)
{
	LoginResponse Response;

	if (this->captcha.strChallange.size() > 0)
	{
		if (this->HTTP->IsOpen() &&
			this->HTTP->Connect(L"account.leagueoflegends.com", 443))
		{
			for (size_t i = 0; i < this->captcha.strChallange.size(); i++)
				if (this->captcha.strChallange.at(i) == 0x20) 
					this->captcha.strChallange.at(i) = '+';

			std::string strRequest = 
				std::string("username=").append(LoginData.username)
					.append("&password=").append(LoginData.password)
					.append("&recaptcha_challenge_field=").append(this->captcha.strChallange)
					.append("&recaptcha_response_field=").append(this->captcha.strAnswer);

			std::string strHeader =
				std::string("X-Requested-With: XMLHttpRequest\r\n")
					.append("Referer: https://account.leagueoflegends.com/pm.html\r\n")
					.append("Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n")
					.append("Cookie: PVPNET_REGION=").append(LoginData.region);

			if (this->HTTP->SendRequest(L"POST", L"/auth", StringToWString(strHeader), strRequest))
			{
				std::string strResponse = reinterpret_cast<const char*>(this->HTTP->GetResponse().c_str());
				std::cout<<strResponse<<std::endl;
				std::string strCookies = this->HTTP->GetResponseHeader();
				DWORD dwSuccessStart = strResponse.find("\"success\":") + 10,
					dwSuccessEnd = strResponse.find(",", dwSuccessStart);
				
				Response.strSuccess = strResponse.substr(dwSuccessStart, dwSuccessEnd - dwSuccessStart);

				if(Response.strSuccess == "true")
				{
					if(this->HTTP->SendRequest(L"GET", L"/account/email-validate-state", StringToWString(strHeader), ""))
					{
						std::string strResponseValidation = reinterpret_cast<const char*>(this->HTTP->GetResponse().c_str());
						std::string newStr = strResponseValidation.substr(strResponseValidation.find("\"eligible_for_award\":") + 21, strResponseValidation.size());
						newStr = newStr.substr(0, newStr.find(","));

						this->GoodAcc.strUnverified = newStr;
					}

					std::smatch match;
					std::regex e("PVPNET_ACCT_" + LoginData.region + "=([^;]+)", std::regex_constants::icase);
					std::regex_search(strCookies,match,e);
					this->GoodAcc.strSummonerName=match[1];
					this->GoodAcc.strUsername=LoginData.username;
					this->GoodAcc.strPassword=LoginData.password;
				}

				DWORD dwErrorStart = strResponse.find(",\"error\":\"") + 10,
					dwErrorEnd = strResponse.find("\"", dwErrorStart);

				Response.strError = strResponse.substr(dwErrorStart, dwErrorEnd - dwErrorStart);		
			}
		}
	}

	return Response;
}