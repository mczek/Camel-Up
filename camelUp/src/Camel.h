#include <Rcpp.h>
#include <string>

// define camel class
class Camel {
private:
  std::string color;
  int space;
  int height;
public:
  Camel(std::string c);
  std::string getColor();

  int getSpace();

  int getHeight();

  void setSpace(int n);
  void setHeight(int n);

  Camel duplicate();

};
