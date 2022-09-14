#include "book.h"
#include <algorithm>

Book::Book(const std::string category, const std::string name, double price,
           int qty, const std::string author, const std::string isbn)
    : Product(category, name, price, qty), author(author), isbn(isbn) {}

std::set<std::string> Book::keywords() const {
    auto name_set = parseStringToWords(name_);
    auto author_set = parseStringToWords(author);
    auto set = setUnion(name_set, author_set);
    set.insert(convToLower(isbn));
    return set;
}

std::string Book::displayString() const {
    return name_ + "\nAuthor: " + author + " ISBN: " + isbn + '\n' +
           std::to_string(price_) + ' ' + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
    os << category_ << '\n'
       << name_ << '\n'
       << price_ << '\n'
       << qty_ << '\n'
       << author << '\n'
       << isbn << '\n';
}
