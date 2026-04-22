#include "text.hpp"
#include <cctype>
#include <stdexcept>
#include <string>

void Text::validate(std::string txt) {
  if (txt.empty() || txt.length() > 40)
    throw std::invalid_argument("Invalid size");

  char prim = txt.front(), ult = txt.back();
  if (prim == ',' || prim == '.' || prim == ' ' || ult == ',' || ult == '.' ||
      ult == ' ')
    throw std::invalid_argument("Invalid format at the boundaries");

  for (size_t i = 0; i < txt.length(); i++) {
    char c = txt[i];

    if (!isalnum(c) && c != ',' && c != '.' && c != ' ')
      throw std::invalid_argument("Invalid character");

    if (i + 1 < txt.length()) {
      char prox = txt[i + 1];

      if ((c == ',' || c == '.') && (prox == ',' || prox == '.'))
        throw std::invalid_argument("Punctuation followed by punctuation");

      if (c == ' ' && !isalnum(prox))
        throw std::invalid_argument("Space not followed by letter or digit");
    }
  }
}
