#pragma once
#include "product.h"
#include "util.h"

class Movie : public Product {
  public:
    Movie(const std::string category, const std::string name, double price,
          int qty, const std::string genre, const std::string rating);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

  private:
    std::string genre;
    std::string rating;
};
