#pragma once
#include <string>

namespace Util
{
  std::wstring Utf8ToWString(const std::string &utf8);
  std::string WStringToUtf8(const std::wstring &wide);
  std::string StringToLower(const std::string &str);
}