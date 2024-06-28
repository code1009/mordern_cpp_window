/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <locale>

#include <map>
#include <vector>

#include <algorithm>

#include <iostream>
#include <sstream>
#include <iomanip>

//===========================================================================
#include <windows.h>

//===========================================================================
#include "uri.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace uri
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*
uri: Uniform Resource Identifier
url: Uniform Resource Locator
urn: Uniform Resource Name

url < uri 큰 개념

https://www.example.co.kr/dir/file?id=1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ uri/url
                         ~~~~~~~~~~~~~~ urn

https://www.example.co.kr:443/dirA/dirB/file?id=1&name=code1009#cx:                        
https://                                                          :  protocol or scheme    
                                                                  :  host
        www                                                       :      sub domain        
            example                                               :      domain            
                    co.kr                                         :      top level domain  
                          443                                     :      port number           
                             /dirA/dirB/file                      :  path                  
                                            ?                     :  query string separator
                                             id=1&name=code1009   :  query string parameter
                                                               #cx:  fragment              
*/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring mbcs_to_wcs(std::string input, UINT codepage)
{
	int len = MultiByteToWideChar(codepage, 0, input.c_str(), -1, NULL, 0);


	if (len > 0)
	{
		std::vector<wchar_t> buf(len);


		MultiByteToWideChar(codepage, 0, input.c_str(), -1, &buf[0], len);

		return std::wstring(&buf[0]);
	}

	return std::wstring();
}

std::string wcs_to_mbcs(std::wstring input, UINT codepage)
{
	int len = WideCharToMultiByte(codepage, 0, input.c_str(), -1, NULL, 0, NULL, NULL);


	if (len > 0)
	{
		std::vector<char> buf(len);


		WideCharToMultiByte(codepage, 0, input.c_str(), -1, &buf[0], len, NULL, NULL);

		return std::string(&buf[0]);
	}

	return std::string();
}

std::string utf8_to_mbcs(std::string /*input*/utf8, UINT codepage)
{
	//	std::string  utf8 ;
	std::wstring utf16;
	std::string  mbcs;


	//	utf8  = input;
	utf16 = mbcs_to_wcs(utf8, CP_UTF8);
	mbcs = wcs_to_mbcs(utf16, codepage);

	return mbcs;
}

std::string mbcs_to_utf8(std::string /*input*/mbcs, UINT codepage)
{
	std::string  utf8;
	std::wstring utf16;
	//	std::string  mbcs ;


	//	mbcs  = input;
	utf16 = mbcs_to_wcs(mbcs, codepage);
	utf8 = wcs_to_mbcs(utf16, CP_UTF8);

	return utf8;
}

//===========================================================================
void toupper(std::string& s)
{
	std::transform(
		s.begin(), 
		s.end(), 
		s.begin(),
		[](char c) 
		{
			return static_cast<char>(std::toupper(c)); 
		}
	);
}

std::vector<std::string> split(const std::string& str, const char delim)
{
	if (str.empty())
	{
		return {};
	}


	std::vector<std::string> tokens;
	std::istringstream iss(str);
	std::string token;


	while (std::getline(iss, token, delim))
	{
		tokens.push_back(token);
	}

	return tokens;
}

//===========================================================================
std::string encode(const std::string& decodedString, bool retainLineFeed)
{
	std::string encodedString;

	char allowedChars[] = { '-', '_', '.','~','&', '=', '+', };


	for (char aChar : decodedString)
	{
		/*
			'\n' : newline,
			'\t' : horizontal tab,
			'\v' : vertical tab
			'\r' : Carraige return
			'\f' : form feed
		*/
		if (
			(std::isspace(aChar)) && 
			(aChar != ' ') &&
			(retainLineFeed == false)
			)
		{
			continue;
		}


		if (
			(!std::isalnum(aChar)) &&
			(!(std::any_of(std::begin(allowedChars), std::end(allowedChars), [aChar](const char c) {return aChar == c; })))
			)
		{
			std::stringstream ss;


			ss << '%';
			ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(aChar);

			encodedString += ss.str();
		}
		else
		{
			encodedString += aChar;
		}
	}

	return encodedString;
}

std::string decode(const std::string& encodedString)
{
	std::string decodedString;

	std::size_t size;
	std::size_t pos;


	size = encodedString.size();
	for (pos = 0; pos < size; ++pos)
	{
		if ('%' == encodedString[pos])
		{
			if (pos + 2 >= size)
			{
				break;
			}


			std::istringstream iss(encodedString.substr(pos + 1, 2));
			int charValue;


			iss >> std::hex >> charValue;


			decodedString += static_cast<char> (charValue);
			

			pos += 2;
		}
		else
		{
			decodedString += encodedString[pos];
		}
	}


	return decodedString;
}

//===========================================================================
std::string erase_query_string(const std::string& s)
{
	auto pos = s.find_first_of('?');


	if (pos != std::string::npos)
	{
		return s.substr(0, pos);
	}

	return s;
}

std::string parse_query_string(const std::string& s)
{
	auto pos = s.find_first_of('?');


	if (pos != std::string::npos)
	{
		return s.substr(pos + 1);
	}

	return {};
}

std::map<std::string, std::string> parse_query_string_parameters(const std::string& s)
{
	std::map<std::string, std::string> parameter_map;


	auto keyValTokens = split(s, '&');


	for (const auto& keyValToken : keyValTokens)
	{
		if (keyValToken.size() < 1)
		{
			continue;
		}

		auto keyValVector = split(keyValToken, '=');
		if (keyValVector.size() != 2)
		{
			continue;
		}

		parameter_map[decode(keyValVector[0])] = decode(keyValVector[1]);
	}


	return parameter_map;
}

std::string build_query_string_parameters(const std::map<std::string, std::string>& parameter_map, bool retainLineFeed)
{
	std::stringstream ss;


	for (const auto& keyValToken : parameter_map)
	{
		ss << encode(keyValToken.first, retainLineFeed);
		ss << '&';
		ss << encode(keyValToken.second, retainLineFeed);
	}


	return ss.str();
}

std::map<std::string, std::string> utf8_to_mbcs(const std::map<std::string, std::string>& parameter_map)
{
	std::map<std::string, std::string> mbcs;


	for (const auto& keyValToken : parameter_map)
	{
		mbcs[utf8_to_mbcs(keyValToken.first)] = utf8_to_mbcs(keyValToken.second);
	}

	return mbcs;
}

std::map<std::wstring, std::wstring> utf8_to_wcs(const std::map<std::string, std::string>& parameter_map)
{
	std::map<std::wstring, std::wstring> wcs;


	for (const auto& keyValToken : parameter_map)
	{
		wcs[mbcs_to_wcs(keyValToken.first, CP_UTF8)] = mbcs_to_wcs(keyValToken.second, CP_UTF8);
	}

	return wcs;
}

std::string parse_base_directory(const std::string& s)
{
	std::string::size_type pos;


	pos = s.find_last_of('/');
	if (std::string::npos == pos)
	{
		return {};
	}


	return s.substr(0, pos + 1);
}

std::string parse_file(const std::string& s)
{
	std::string::size_type pos;


	pos = s.find_last_of('/');
	if (std::string::npos == pos)
	{
		return {};
	}


	return s.substr(pos + 1);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




