#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace uri
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring encode(const std::wstring& decodedString, bool retainLineFeed);
std::wstring decode(const std::wstring& encodedString);

//===========================================================================
std::wstring                         erase_query_string(const std::wstring& s);
std::wstring                         parse_query_string(const std::wstring& s);
std::map<std::wstring, std::wstring> parse_query_string_parameters(const std::wstring& s);
std::wstring                         build_query_string_parameters(const std::map<std::wstring, std::wstring>& parameter_map, bool retainLineFeed);
std::wstring                         parse_base_directory(const std::wstring& s);
std::wstring                         parse_file(const std::wstring& s);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




