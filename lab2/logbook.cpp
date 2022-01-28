#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

class Logbook {
    private:
        int logMonth;
        int logYear;
        int daysInMonth;
        vector<int> entries;

        bool isLeapYear(int year);
    
    public:
        Logbook(int month, int year);

        void putEntry(int day, int value);

        int getEntry(int day);
        int getDaysInMonth();
        int getMonth();
        int getYear();
// *task1
        bool hasTargetBeenReached(int target);
        int longestConsecutiveSubsequence();
// *task2
        void putEntry(int value);
        bool hasTargetBeenReached(int target, int check_day);
// *task3
        int operator [] (int day) {
            return entries[day];
        }
        
        Logbook operator + (const Logbook &rightLogbook) {
            Logbook rightLbk = *&rightLogbook;
            Logbook result(getMonth(), getYear());
            for (int i = 1; i < daysInMonth + 1; i++) {
                result.entries[i] = entries[i] + rightLbk.entries[i];
            }
            return result;
        }

        vector<int> operator % (const Logbook &rightLogbook) {
            Logbook rightLbk = *&rightLogbook;
            map<int, int> mp;
            vector<int> result;
            for (int i = 1; i < daysInMonth + 1; i++) {
                if (mp.find(entries[i]) == mp.end()) {
                    mp[entries[i]] = 1;
                } else {
                    mp[entries[i]]++;
                }

                if (mp.find(rightLbk.entries[i]) == mp.end()) {
                    mp[rightLbk.entries[i]] = 1;
                } else {
                    mp[rightLbk.entries[i]]++;
                }
            }

            for (auto& it: mp) {
                if (it.second == 1) {
                    result.push_back(it.first);
                }
            }

            return result;
        }
};

bool Logbook::isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            } else return false;
        } else return true;
    } else return false;
}

Logbook::Logbook(int month, int year) {
    logMonth = month;
    logYear = year;

    vector<int> daysList;
    
    daysList.push_back(31);
    daysList.push_back(28);
    daysList.push_back(31);
    daysList.push_back(30);
    daysList.push_back(31);
    daysList.push_back(30);
    daysList.push_back(31);
    daysList.push_back(31);
    daysList.push_back(30);
    daysList.push_back(31);
    daysList.push_back(30);
    daysList.push_back(31);
    

    if (month == 2 && isLeapYear(logYear) == true) {
        daysInMonth = 29;
    } else {
        daysInMonth = daysList[logMonth - 1];
    }

    entries.resize(daysInMonth + 1, 0);
}

void Logbook::putEntry(int day, int value) {
    entries[day] = value;
}

int Logbook::getEntry(int day) {
    return entries[day];
}

int Logbook::getMonth() {
    return logMonth;
}

int Logbook::getYear() {
    return logYear;
}

int Logbook::getDaysInMonth() {
    return daysInMonth;
}

bool Logbook::hasTargetBeenReached(int target) {
    int sales = 0;
    for (int i = 0; i < daysInMonth + 1; i++) {
        sales += entries.at(i);
    }
    if (sales >= target) {
        return true;
    } else return false;
}

int Logbook::longestConsecutiveSubsequence() {
    int n = daysInMonth, ans = 0, count = 0;
    int arr[n];
    for (int i = 1; i < n + 1; i++) {
        arr[i - 1] = entries.at(i);
    }
    
    sort(arr, arr + n);

    vector<int> v;
    v.push_back(arr[0]);

    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) {
            v.push_back(arr[i]);
        }
    }

    for (int i = 0; i < v.size(); i++) {
        if (i > 0 && v[i] == v[i - 1] + 1) {
            count++;
        } else {
            count = 1;
        }

        ans = max(ans, count);
    }

    return ans;
}

void Logbook::putEntry(int value) {
    for (int i = 1; i < daysInMonth + 1; i++) {
        entries[i] = value;
    }
}

bool Logbook::hasTargetBeenReached(int target, int check_day) {
    int sales = 0;
    for (int i = 0; i < check_day; i++) {
        sales += entries.at(i);
    }
    if (sales >= target) {
        return true;
    } else return false;
}

int main() {
    // logbook run code for testing
    Logbook testLogbook(2, 2020);
    Logbook testLogbook2(2, 2020);

    for (int i = 1; i <= 29; i++) {
        testLogbook.putEntry(i, i);
        testLogbook2.putEntry(i, i + 1);
    }

    cout << testLogbook[5] << endl;

    Logbook additionLogbook = testLogbook + testLogbook2;

    cout << additionLogbook[29] << endl;

    vector<int> combinedUniqueEntries = testLogbook % testLogbook2;
    sort(combinedUniqueEntries.begin(), combinedUniqueEntries.end());

    cout << combinedUniqueEntries.front() << " " << combinedUniqueEntries.back() << endl;

    return 0;
}
