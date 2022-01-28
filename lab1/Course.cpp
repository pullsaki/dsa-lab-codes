#include<iostream>
#include<vector>
#include<string>

using namespace std;
class Course {
  public:
    string name;
    string ic;
    int numOfStds;
    int totalMarks;

  private:
    vector<int> studentMarks(int numOfStds);

  Course(string nm, string i, int n, int m) {
    name = nm;
    ic = i;
    numOfStds = n;
    totalMarks = m;
  }

  friend class Lab;
};

class Lab : public Course {
  private:
    vector<int> labMarks(int numOfStds);

  public:
    int countNC(int threshold);
};

int Lab::countNC(int threshold) {
  int count = 0;
  for (int i = 0; i < numOfStds; i++) {
    int coursemarks = (int) studentMarks(i);
    int labmarks = labMarks(i);
    int sum = coursemarks + labmarks;
    if (sum < threshold) count++;
  }

  return count;
}

int main() {
//  Lab("dsa", "ic", 50, 100) l;

//  cout << l.name << l.ic << l.numOfStds << l.totalMarks << endl;
  
}
