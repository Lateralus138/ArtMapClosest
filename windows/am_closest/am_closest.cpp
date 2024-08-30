#include "stdafx.h"
std::vector<std::string> HELPOPTS = { "/h", "/help", "/H", "/HELP" };
std::vector<std::string> VALUOPTS = { "/v", "/value", "/V", "/VALUE" };
std::vector<std::string> XOPTS = { "/x", "/0x", "/X", "/0X" };
std::vector<std::string> UNIOPTS = { "/u", "/unicode", "/U", "/UNICODE" };
std::vector<std::string> OCTOPTS = { "/o", "/octothorpe", "/O", "/octothorpe" };
std::vector<std::string> EMPOPTS = { "/e", "/empty", "/E", "/EMPTY" };
void static SwitchOptions(ArgumentParser& args, Options& options)
{
  if (args.optionsExist(VALUOPTS)) options.value = true;
  if (args.optionsExist(XOPTS)) options.prefix = "0x";
  if (args.optionsExist(OCTOPTS)) options.prefix = "#";
  if (args.optionsExist(UNIOPTS)) options.prefix = "\\U";
  if (args.optionsExist(EMPOPTS)) options.prefix = "";
}
int static ParseArguments(ArgumentParser& args, Options& options)
{
  int parsed = 0;
  if (args.optionsExist(HELPOPTS))
  {
    std::string message =
      "\n  ArtMap Closest Color - Find the closest ArtMap item or associated"
      "\n  color value from any hexadecimal color."
      "\n\n  am_closest [SWITCHES] <COLOR VALUES>"
      "\n\n  @SWITCHES"
      "\n    /h, /help         This help message."
      "\n    /v, /value        Return the item's hexadcimal value instead of"
      "\n                      the item's name string."
      "\n    /x, /0x           The item's Hexadcimal is prefixed with '0x'"
      "\n                      if the /value switch is provided. This is the"
      "\n                      default value, but can be used to override any"
      "\n                      other switch."
      "\n    /u, /unicode      The item's Hexadcimal is prefixed with '\\U'"
      "\n                      if the /value switch is provided."
      "\n    /o, /octothorpe   The item's Hexadcimal is prefixed with '#'"
      "\n                      if the /value switch is provided."
      "\n    /e, /empty        The item's Hexadcimal is prefixed with ''"
      "\n                      if the /value switch is provided."
      "\n\n  @COLOR VALUES"
      "\n    Hexadecimal       Any number of color values provided in"
      "\n                      hexadecimal format."
      "\n\n";
    std::cout << message;
    return -1;
  }
  SwitchOptions(args, options);
  const std::vector<std::string> arg_list = args.getArgs();
  std::regex trans("^transparent$", std::regex_constants::icase);
  for (std::vector<std::string>::const_iterator iter = arg_list.begin(); iter < arg_list.end(); iter++)
  {
    if ((*iter == "-1") || std::regex_match(*iter, trans))
    {
      options.hexadecimals.push_back(0x01dcdcdc);
      continue;
    }
    if (Globals::IsStringInt(*iter))
    {
      const int integer = std::stoi(std::string(*iter), nullptr, 10);
      if (!Globals::ValueInRange(integer, 0x000000, 0xffffff)) return 3;
      options.hexadecimals.push_back(integer);
      continue;
    }
    if (Globals::IsHexadecimalString(*iter))
    {
      std::string worker = *iter;
      if (worker.substr(0, 2) != "0x") worker.insert(0, "0x");
      const int hex = std::stoi(worker, nullptr, 16);
      if (!Globals::ValueInRange(hex, 0x000000, 0xffffff)) return 3;
      options.hexadecimals.push_back(hex);
      continue;
    }
  }
  if (options.hexadecimals.size() == 0) parsed = 2;
  return parsed;
}

int main(int argc, const char* argv[])
{
  Options options = { false, "0x" };
  Errors errors =
  { {
    {1, "Not enough arguments passed to the program."},
    {2, "No values passed to the program."},
    {3, "Value is not a valid 24 bit color."}
  } };
  if (argc < 2)
  {
    std::cerr << errors.messages[1] << '\n';
    return 1;
  }
  ArgumentParser args(argc, argv, 1);
  const int PARSED = ParseArguments(args, options);
  if (PARSED == -1) return EXIT_SUCCESS;
  if (PARSED > 0)
  {
    std::cerr << errors.messages[PARSED] << '\n';
    return PARSED;
  }
  std::map<std::string, int> colorMap =
  {
    {"Ink Sack", 0x151515}, {"Red Dye", 0xDC0000}, {"Green Dye", 0x586D2C}, {"Cocoa Beans", 0x58412C},
    {"Lapis Lazuli", 0x2C4199}, {"Purple Dye", 0x6D3699}, {"Cyan Dye", 0x416D84}, {"Light Grey Dye", 0x909090},
    {"Gray Dye", 0x8D909E}, {"Pink Dye", 0xD06D8E}, {"Lime Dye", 0x6DB015}, {"Yellow Dye", 0xC5C52C},
    {"Light Blue Dye", 0x5884BA}, {"Magenta Dye", 0x9941BA}, {"Orange Dye", 0xBA6D2C}, {"Bone Meal", 0xDCD9D3},
    {"Pumpkin Seeds", 0xD5C98C}, {"Melon Seeds", 0x825E42}, {"Flint", 0x414141}, {"GunPowder", 0x848484},
    {"Nether Wart", 0x600100}, {"Prismarine Crystals", 0x4FBCB7}, {"Short Grass", 0x6D9930}, {"Gold Nugget", 0xD7CD42},
    {"Ender Eye", 0x01dcdcdc}, {"CobWeb", 0xABABAB}, {"Ice", 0x8A8ADC}, {"Oak Leaves", 0x006A00},
    {"Snow", 0xDCDCDC}, {"Ghast Tear", 0x606060}, {"Lapis Block", 0x3737DC}, {"Dark Oak Log", 0x7B663E},
    {"Brick", 0x842C2C}, {"Lapis Ore", 0x3F6EDC}, {"Emerald", 0x00BB32}, {"Birch Wood", 0x6F4A2A},
    {"Egg", 0xB4988A}, {"Magma Cream", 0x89461F}, {"BeetRoot", 0x804B5D}, {"Mycelium", 0x605D77},
    {"Glowstone Dust", 0xA0721F}, {"Slime Ball", 0x58642D}, {"Spider Eye", 0x8A4243}, {"Soul Sand", 0x31231E},
    {"Brown Mushroom", 0x745C54}, {"Iron Nugget", 0x4B4F4F}, {"Chorus Fruit", 0x693E4B}, {"Purpur Block", 0x41354F},
    {"Podzol", 0x412B1E}, {"Poisonous Potato", 0x414624}, {"Apple", 0x7A3327}, {"Charcoal", 0x1F120D},
    {"Crimson Nylium", 0xA3292A}, {"Crimson Stem", 0x7F3653}, {"Crimson Hyphae", 0x4F1519}, {"Warped Nylium", 0x126C73},
    {"Warped Stem", 0x327A78}, {"Warped Hyphae", 0x4A2535}, {"Warped Wart Block", 0x119B72}, {"Cobbled Deepslate", 0x565656},
    {"Raw Iron", 0xBA967E}, {"Glow Lichen", 0x6D9081}
  };
  for (std::vector<int>::const_iterator iter = options.hexadecimals.begin(); iter < options.hexadecimals.end(); iter++)
  {
    const int test_color = *iter;
    std::map<double, std::string> diffs;
    std::vector<double> diffs_num;
    for (auto const & [key, value] : colorMap)
    {
      const double diff = Globals::ColorDiff(value, test_color);
      diffs_num.push_back(diff);
      diffs[diff] = ((!options.value) ? key : Globals::IntToHexString(value, 6, options.prefix));
    }
    std::vector<double>::iterator result = std::min_element(diffs_num.begin(), diffs_num.end());
    std::cout << diffs[*result] << std::endl;
  }
}
