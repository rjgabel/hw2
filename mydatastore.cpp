#include "mydatastore.h"
#include "util.h"
#include <list>

void MyDataStore::addProduct(Product* p) {
    products.insert(p);
    std::set<std::string> map = p->keywords();
    for (std::set<std::string>::iterator it = map.begin(); it != map.end();
         it++) {
        keyword_map[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u) { users[u->getName()] = u; }

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms,
                                          int type) {
    if (terms.size() < 1) {
        return std::vector<Product*>();
    }
    // We need to special case the first term because otherwise AND searches
    // wouldn't work (the intersection of an empty set and another set is always
    // an empty set)
    std::set<Product*> result_set = keyword_map[*terms.begin()];
    for (std::vector<std::string>::iterator it = terms.begin() + 1;
         it != terms.end(); it++) {
        std::set<Product*> matches = keyword_map[*it];
        if (type == 0) { // AND search
            result_set = setIntersection(result_set, matches);
        } else { // OR search
            result_set = setUnion(result_set, matches);
        }
    }

    // Because displayProducts sorts the results before it displays them, we
    // need to sort them as well, so the indices match up for addToCart. But
    // since we can't use the <algorithm> header, we can't use std::sort, so we
    // have to make a temporary std::list and use its built-in sort operator
    // instead.
    std::list<Product*> result_list;
    for (std::set<Product*>::iterator it = result_set.begin();
         it != result_set.end(); it++) {
        result_list.push_back(*it);
    }
    result_list.sort();
    results.clear();
    for (std::list<Product*>::iterator it = result_list.begin();
         it != result_list.end(); it++) {
        results.push_back(*it);
    }
    return results;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (Product* item : products) {
        item->dump(ofile);
    }
    ofile << "</products>\n<users>\n";
    for (std::pair<const std::string, User*> user : users) {
        user.second->dump(ofile);
    }
    ofile << "</users>\n";
}

bool MyDataStore::addToCart(std::string username, int index) {
    if (users.count(username) && 0 <= index &&
        (unsigned)index < results.size()) {
        carts[username].push(results[index]);
        return true;
    } else {
        return false;
    }
}

bool MyDataStore::viewCart(std::string username) {
    if (users.count(username)) {
        std::queue<Product*> cart = carts[username];
        for (size_t i = 0; i < cart.size(); i++) {
            Product* item = cart.front();
            cart.pop();
            std::cout << "Item " << i + 1 << '\n'
                      << item->displayString() << "\n\n";
            // Move the first item in the queue to the back so we can look at
            // the next one
            cart.push(item);
        }
        return true;
    } else {
        return false;
    }
}

bool MyDataStore::buyCart(std::string username) {
    if (users.count(username)) {
        std::queue<Product*>& cart = carts[username];
        // Put size in its own variable since the size of the cart is going to
        // change as items are removed
        size_t size = cart.size();
        for (size_t i = 0; i < size; i++) {
            Product* item = cart.front();
            cart.pop();
            User* user = users[username];
            double price = item->getPrice();
            if (item->getQty() > 0 && user->getBalance() >= price) {
                item->subtractQty(1);
                user->deductAmount(price);
            } else {
                cart.push(item);
            }
        }
        return true;
    } else {
        return false;
    }
}
