#include<iostream>
#include<bits/stdc++.h>

class ClassName {
  private:
    int value;
  public:
    void increment_value();
};

void ClassName::increment_value() {
  value++;
}

class construct {
  public:
    int a, b;

    construct() {
      a = 10;
      b = 25;
    }
};

using namespace std;
int main() {
  construct c;
  cout << "a: " << c.a << endl << "b: " << c.b << endl;
}
