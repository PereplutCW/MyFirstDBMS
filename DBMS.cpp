#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <exception>

using namespace std;

// Определение и реализация класса Date для хранения и операций с датами

class Date {
public:
  explicit Date() {
    year = 0;
    month = 0;
    day = 0;
  };
  explicit Date(const int newYear, const int newMonth, const int newDay) {
    year = newYear;
    if (newMonth < 1 || newMonth > 12) {
      string errorMessage;
      errorMessage = "Month value is invalid: " + to_string(newMonth);
      throw runtime_error(errorMessage);
    } else if (newDay < 1 || newDay > 31) {
      string errorMessage;
      errorMessage = "Day value is invalid: " + to_string(newDay);
      throw runtime_error(errorMessage);
    } else {
      month = newMonth;
      day = newDay;
    }
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

// Перегрузка оператора < для класса Date для возможности сортировки объектов этого класса 
// в контейнерах map и set

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    }
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetYear() < rhs.GetYear();
}

// Перегрузка оператора << для класса Date для возможности вывода объектов этого класса 
// в стандартный вывод

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() << '-' <<
            setw(2) << setfill('0') << date.GetMonth() << '-' <<
            setw(2) << setfill('0') << date.GetDay();
  return stream;
}

// Определение и реализация функции EnsureNextSymbolAndSkip для проверки разделяющего символа
// в дате формата Год-Месяц-День

void EnsureNextSymbolAndSkip(stringstream& stream, const string& dataString) {
  if (stream.peek() != '-') {
    stringstream errorMessage;
    errorMessage << "Wrong date format: " + dataString;
    throw runtime_error(errorMessage.str());
  }
  stream.ignore(1);
}

// Перегрузка оператора >> для класса Date для возможности ввода объектов этого класса 
// из стандартного ввода

istream& operator>>(istream& stream, Date& date) {
  int year = 10000;
  int month = 10000;
  int day = 10000;

  string dataString;
  string endError = "";
  if (stream >> dataString) {
    stringstream stream(dataString);
    stream >> year;
    EnsureNextSymbolAndSkip(stream, dataString);
    stream >> month;
    EnsureNextSymbolAndSkip(stream, dataString);
    stream >> day;
    stream >> endError;
    if (year >= 0 && year < 10000 && month < 10000 && day < 10000 && endError == "") {
      date = Date(year, month, day);
      return stream;
    } else {
      stringstream errorMessage;
      errorMessage << "Wrong date format: " + dataString;
      throw runtime_error(errorMessage.str());
    }
  } else {
    stringstream errorMessage;
    errorMessage << "Wrong date format: " + dataString;
    throw runtime_error(errorMessage.str());
  }
}

// Определение и реализация класса Databates для хранения и операций с парами Дата - Событие

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
      int eventsNums = dates[date].size();
      dates.erase(date);
      return eventsNums;
    }
  };
  void Find(const Date& date) const {
    if (dates.count(date)) {
      for (const string& event : dates.at(date)) {
        cout << event << endl;
      }
    }
  };  
  void Print() const {
    for (auto& date : dates) {
      for (auto& event : date.second) {
        cout << date.first << ' ' << event << endl;
      }
    } 
  };
private:
  map<Date, set<string>> dates;
};

// Определение и реализация функции ParseCommands для чтения и обработки комманд из потока

void ParseCommands(const string& command, Database& dataBase) { 
  stringstream stream(command);
  string com;
  Date date;
  string event;
  if (stream >> com) {
    if (com == "Add") {
      // dataBase.AddEvent(date, event);
    } else if (com == "Del") {
      // dataBase.DeleteEvent(date, event);
      // dataBase.DeleteDate(date);
    } else if (com == "Find") {
      // dataBase.Find(date);
    } else if (com == "Print") {
      // dataBase.Print();
    } else {
      stringstream errorMessage;
      errorMessage << "Unknown command: " << com;
      throw runtime_error(errorMessage.str());
    }
  }
  
}

int main() {
  try {
    Database dataBase;
    string command;

    while (getline(cin, command)) {
      ParseCommands(command, dataBase);
    }
  } catch (exception& ex) {
      cout << ex.what() << endl;
  }

  return 0;
}