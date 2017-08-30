#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace boost::archive;

class animal
{
public:
  animal() = default;
  animal(int legs, std::string name) :
    legs_{legs}, name_{std::move(name)} {}
  int legs() const { return legs_; }
  const std::string &name() const { return name_; }

private:
  friend class boost::serialization::access;

  template <typename Archive>
  friend void serialize(Archive &ar, animal &a, const unsigned int version);

  int legs_;
  std::string name_;
};

template <typename Archive>
void serialize(Archive &ar, animal &a, const unsigned int version)
{
  ar & a.legs_;
  ar & a.name_;
}

void save(std::ofstream &ofs)
{
  text_oarchive oa{ofs};
  animal a{4, "cat"};
  oa << a;
}

void load(std::ifstream &ifs)
{
  text_iarchive ia{ifs};
  animal a;
  ia >> a;
  std::cout << a.legs() << '\n';
  std::cout << a.name() << '\n';
}

int main()
{
  std::ofstream ofs("file_test");
  save(ofs);
  std::ifstream ifs("file_test");
  load(ifs);
}

