/*
 *  How to store data in .txt file from map container in ios::binary mode? ...
 *  Can anyone tell me ...
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std::literals::string_literals;

/*
 *  iterate with a STL iterator
 */
void fnuc_iterator(void) {
  std::map<std::string, int> mymap {
    { "A - \u00a3 1,101.00"s, 1, },
    { "A - \u20ac 222.00"s, 2, },
    { "B - \u00a5 33,345,00"s, 3, },
    { "C - \u20a9 34,567,00"s, 4, },
    { "D - \u20a8 136,789,00"s, 5, },
  };

  std::fstream wri("aiter.dat", std::ios::out | std::ios::binary);

  for (std::map<std::string, int> ::const_iterator it = mymap.begin(); it != mymap.end(); it++) {
    // wri.write((char *) it->first, sizeof(mymap));
    // wri.write((char *) it->second, sizeof(mymap));
    std::cout << std::setw(5) << it->second
              << ", "s
              << std::quoted(it->first)
              << '\n';
    wri.write(it->first.c_str(), it->first.size());
    wri.write(reinterpret_cast<char const *>(&it->second), sizeof(int));
  }

  std::cout << std::endl;
}

/*
 *  iterate with range based loop
 */
void fnuc_rbloop(void) {
  std::map<std::string, int> mymap {
    { "a - \u00a3 1,101.00"s, 11, },
    { "a - \u20ac 222.00"s, 12, },
    { "b - \u00a5 33,345,00"s, 13, },
    { "c - \u20a9 34,567,00"s, 14, },
    { "d - \u20a8 136,789,00"s, 15, },
  };

  std::fstream wri("bloop.dat", std::ios::out | std::ios::binary);

  //  kv is a std::pair
  for (auto const & kv : mymap) {
    std::cout << std::setw(5) << kv.second
              << ", "s
              << std::quoted(kv.first)
              << '\n';
    wri.write(kv.first.c_str(), kv.first.size());
    wri.write(reinterpret_cast<char const *>(&kv.second), sizeof(int));
  }

  std::cout << std::endl;
}

/*
 *  iterate with STL for_each() algorithm
 */
void fnuc_freach(void) {
  std::map<std::string, int> mymap {
    { "\u03b1 - \u00a3 1,101.00"s, 21, },
    { "\u03b1 - \u20ac 222.00"s, 22, },
    { "\u03b2 - \u00a5 33,345,00"s, 23, },
    { "\u03b3 - \u20a9 34,567,00"s, 24, },
    { "\u03b4 - \u20a8 136,789,00"s, 25, },
  };

  std::fstream wri("freach.dat", std::ios::out | std::ios::binary);

  std::for_each(mymap.cbegin(), mymap.cend(), [&wri](auto const & kv) {
    std::cout << std::setw(5) << kv.second
              << ", "s
              << std::quoted(kv.first)
              << '\n';
    wri.write(kv.first.c_str(), kv.first.size());
    wri.write(reinterpret_cast<char const *>(&kv.second), sizeof(int));
  });

  std::cout << std::endl;
}

// ???
int main(int argc, char const * argv[]) {

  fnuc_iterator();
  fnuc_rbloop();
  fnuc_freach();

  return 0;
}
