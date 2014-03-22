#include "util.hpp"
#include <utf8.h>
#include <cstdlib>

std::wstring Util::Utf8ToWString(const std::string &str)
{
  std::wstring ret;
  
  if(sizeof(wchar_t) == 4)
    utf8::utf8to32(str.begin(), str.end(), std::back_inserter(ret));
  else if(sizeof(wchar_t) == 2)
    utf8::utf8to16(str.begin(), str.end(), std::back_inserter(ret));
  else ret = L"__UNICODE NOT SUPPORTED__";
  
  return ret;
}

std::string Util::WStringToUtf8(const std::wstring &wide)
{
  std::string ret;
  
  if(sizeof(wchar_t) == 4)
    utf8::utf32to8(wide.begin(), wide.end(), std::back_inserter(ret));
  else if(sizeof(wchar_t) == 2)
    utf8::utf16to8(wide.begin(), wide.end(), std::back_inserter(ret));
  else
    ret = "__UNICODE NOT SUPPORTED__";
  
  return ret;
}

/* This function fucks UTF8 strings in the ass. Watch out. */
std::string Util::StringToLower(const std::string &str)
{
  std::string lower(str);
  
  for(auto it = lower.begin(); it != lower.end(); ++it)
  {
    char &ch = *it;
    
    if(ch >= 'A' && ch <= 'Z')
      ch -= 'Z';
  }
  
  return lower;
}