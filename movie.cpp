#include "movie.h"

Movie::Movie(const std::string category, const std::string name, double price,
             int qty, const std::string genre, const std::string rating)
    : Product(category, name, price, qty), genre(genre), rating(rating) {}

std::set<std::string> Movie::keywords() const {
    auto set = parseStringToWords(name_);
    set.insert(genre);
    return set;
}

std::string Movie::displayString() const {
    return name_ + "\nGenre: " + genre + " Rating: " + rating + '\n' +
           std::to_string(price_) + ' ' + std::to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const {
    os << category_ << '\n'
       << name_ << '\n'
       << price_ << '\n'
       << qty_ << '\n'
       << genre << '\n'
       << rating << '\n';
}
