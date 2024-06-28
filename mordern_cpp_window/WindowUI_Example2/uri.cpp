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

uri > url 큰 개념

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
void toupper(std::wstring& s)
{
	std::transform(
		s.begin(), 
		s.end(), 
		s.begin(),
		[](wchar_t c) 
		{
			return static_cast<wchar_t>(std::toupper(c)); 
		}
	);
}

std::vector<std::wstring> split(const std::wstring& str, const wchar_t delim)
{
	if (str.empty())
	{
		return {};
	}


	std::vector<std::wstring> tokens;
	std::wistringstream iss(str);
	std::wstring token;


	while (std::getline(iss, token, delim))
	{
		tokens.push_back(token);
	}

	return tokens;
}

//===========================================================================
std::wstring encode(const std::wstring& decodedString, bool retainLineFeed)
{
	std::wstring encodedString;

	wchar_t allowedChars[] = { '-', '_', '.','~','&', '=', '+', };


	for (wchar_t aChar : decodedString)
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
			(!(std::any_of(std::begin(allowedChars), std::end(allowedChars), [aChar](const wchar_t c) {return aChar == c; })))
			)
		{
			std::wstringstream ss;


			ss << '%';
			ss << std::uppercase << std::setfill(L'0') << std::setw(2) << std::hex << static_cast<int>(aChar);

			encodedString += ss.str();
		}
		else
		{
			encodedString += aChar;
		}
	}

	return encodedString;
}

std::wstring decode(const std::wstring& encodedString)
{
	std::wstring decodedString;

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


			std::wistringstream iss(encodedString.substr(pos + 1, 2));
			int charValue;


			iss >> std::hex >> charValue;


			decodedString += static_cast<wchar_t> (charValue);
			

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
std::wstring erase_query_string(const std::wstring& s)
{
	auto pos = s.find_first_of('?');


	if (pos != std::wstring::npos)
	{
		return s.substr(0, pos);
	}

	return s;
}

std::wstring parse_query_string(const std::wstring& s)
{
	auto pos = s.find_first_of('?');


	if (pos != std::wstring::npos)
	{
		return s.substr(pos + 1);
	}

	return {};
}

std::map<std::wstring, std::wstring> parse_query_string_parameters(const std::wstring& s)
{
	std::map<std::wstring, std::wstring> parameter_map;


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

std::wstring build_query_string_parameters(const std::map<std::wstring, std::wstring>& parameter_map, bool retainLineFeed)
{
	std::wstringstream ss;


	for (const auto& keyValToken : parameter_map)
	{
		ss << encode(keyValToken.first, retainLineFeed);
		ss << '&';
		ss << encode(keyValToken.second, retainLineFeed);
	}


	return ss.str();
}

std::wstring parse_base_directory(const std::wstring& s)
{
	std::string::size_type pos;


	pos = s.find_last_of('/');
	if (std::wstring::npos == pos)
	{
		return {};
	}


	return s.substr(0, pos + 1);
}

std::wstring parse_file(const std::wstring& s)
{
	std::string::size_type pos;


	pos = s.find_last_of('/');
	if (std::wstring::npos == pos)
	{
		return {};
	}


	return s.substr(pos + 1);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




