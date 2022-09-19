#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
  public:
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    // Returns true if the item was successfully added, false otherwise
    bool addToCart(std::string username, int index);

    // Returns true if the username is valid, false otherwise
    bool viewCart(std::string username);

    bool buyCart(std::string username);

  private:
    std::set<Product*> products;
    std::map<std::string, std::set<Product*>> keyword_map;
    std::map<std::string, User*> users;
    std::map<std::string, std::queue<Product*>> carts;
    std::vector<Product*> results;
};
