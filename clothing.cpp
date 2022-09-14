#include "clothing.h"

Clothing::Clothing(const std::string category, const std::string name,
                   double price, int qty, const std::string size,
                   const std::string brand)
    : Product(category, name, price, qty), size(size), brand(brand) {}

std::set<std::string> Clothing::keywords() const {
    auto name_set = parseStringToWords(name_);
    auto brand_set = parseStringToWords(brand);
    return setUnion(name_set, brand_set);
}

std::string Clothing::displayString() const {
    return name_ + "\nSize: " + size + " Brand: " + brand + '\n' +
           std::to_string(price_) + ' ' + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << '\n'
       << name_ << '\n'
       << price_ << '\n'
       << qty_ << '\n'
       << size << '\n'
       << brand << '\n';
}
