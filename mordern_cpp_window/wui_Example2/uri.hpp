#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace uri
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring mbcs_to_wcs(std::string  input, UINT codepage = CP_ACP);
std::string  wcs_to_mbcs(std::wstring input, UINT codepage = CP_ACP);
std::string  utf8_to_mbcs(std::string  input, UINT codepage = CP_ACP);
std::string  mbcs_to_utf8(std::string  input, UINT codepage = CP_ACP);

//===========================================================================
std::string encode(const std::string& decodedString, bool retainLineFeed);
std::string decode(const std::string& encodedString);

//===========================================================================
std::string                          erase_query_string(const std::string& s);
std::string                          parse_query_string(const std::string& s);
std::map<std::string, std::string>   parse_query_string_parameters(const std::string& s);
std::string                          build_query_string_parameters(const std::map<std::string, std::string>& parameter_map, bool retainLineFeed);
std::map<std::string, std::string>   utf8_to_mbcs(const std::map<std::string, std::string>& parameter_map);
std::map<std::wstring, std::wstring> utf8_to_wcs(const std::map<std::string, std::string>& parameter_map);
std::string                          parse_base_directory(const std::string& s);
std::string                          parse_file(const std::string& s);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




