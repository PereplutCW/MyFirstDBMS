#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <exception>

using namespace std;

class Date {
public:
  Date() {};
  Date(int newYear, int newMonth, int newDay) {
    year = newYear;
    month = newMonth;
    day = newDay;
  }
  int GetYear() const {
    return year;
  };
  int GetMonth() const {
    return month;
  };
  int GetDay() const {
    return day;
  };
private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    }
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetYear() < rhs.GetYear();
};

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    dates[date].insert(event);
  };
  bool DeleteEvent(const Date& date, const string& event) {
    if (dates.count(date) && dates[date].count(event)) {
      set<string> events;
      events = dates.at(date);
      events.erase(event);
      return true;
    } else {
      return false;
    }
  };
  int DeleteDate(const Date& date) {
    if (dates.count(date)) {
      int count = 0;
      for (auto& event : dates[date]) {
        dates[date].erase(event);
        count++;
      }
      return count;
    }
  };
  string Find(const Date& date) const {
    if (dates.count(date)) {
      set<string> events;
      events = dates.at(date);
      for (const string& event : events) {
        return event;
      }
    }
  };  
  void Print() const {
    for (const auto& date : dates) {
      setfill('0');
      cout << setw(4) << date.first.GetYear() << '-' <<
             setw(2) << date.first.GetMonth() << '-' <<
             setw(2) << date.first.GetDay() << " ";
      set<string> events;
      events = date.second;
      for (const string& event : events) {
        cout << event << " ";
      }
      cout << endl;
    } 
  };
private:
  map<Date, set<string>> dates;
};

int main() {
  try {
    Database dataBase;
    
    string command;
    while (getline(cin, command)) {
      if (command == "Add") {
        // dataBase.AddEvent(date, event);
      } else if (command == "Del") {
        // dataBase.DeleteEvent(date, event);
        // dataBase.DeleteDate(date);
      } else if (command == "Find") {
        // dataBase.Find(date);
      } else if (command == "Print") {
        // dataBase.Print();
      } else {
        //
      }
    }
  } catch (exception& ex) {
      cout << ex.what() << endl;
  }

  return 0;
}