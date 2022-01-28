#include<iostream>
#include<bits/stdc++.h>

template <typename T>
T myMax(T x, T y) {
  if (x > y) return x;
  else return y;
}

using namespace std;

int main() {
  cout << myMax<int>(3, 7) << endl;
  cout << myMax<double>(3.9, 7.9) << endl;
  cout << myMax<char>('g', 'c') << endl;

  return 0;
}
