#ifndef TEXT_HPP
#define TEXT_HPP

#include "dominios.hpp"
#include <stdexcept>
#include <string>

class Text : public Dominio {
private:
  void validate(std::string) override;
};

#endif
