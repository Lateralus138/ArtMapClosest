#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
struct Options
{
  bool value;
  std::string prefix;
  std::vector<int> hexadecimals;
};
struct Errors
{
  std::map<int, std::string> messages;
};
namespace Globals
{
  extern unsigned int UINT_MAX_ENSURE;
  bool IsHexadecimalString(const std::string& string);
  std::map<std::string, int> HexToRGB(int hex);
  void StripHexadecimalPrefix(std::string& string);
  void StringReplace(std::string& haystack, const std::string& needle, const std::string& replace);
  bool ValueInRange(const long long int& value_, const long long int& min_, const long long int& max_);
  double ColorDiff(int colorA, int colorB);
  std::string IntToHexString(const int& number, const int& width, const std::string& prefix);
  bool IsStringInt(const std::string& string);
}
#endif // ! GLOBALS_H