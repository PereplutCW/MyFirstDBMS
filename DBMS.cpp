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
  int year;
  int month;
  int day;
public:
  Date() {
    year = 0;
    month = 0;
    day = 0;
  };
  Date(const int new_year, const int new_month, const int new_day) {
    year = new_year;
    if (new_month < 1 || new_month > 12) {
      string error_message;
      error_message = "Month value is invalid: " + to_string(new_month);
      throw runtime_error(error_message);
    } else if (new_day < 1 || new_day > 31) {
      string error_message;
      error_message = "Day value is invalid: " + to_string(new_day);
      throw runtime_error(error_message);
    } else {
      month = new_month;
      day = new_day;
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

void EnsureNextSymbolAndSkip(stringstream& stream, const string& data_string) {
  if (stream.peek() != '-') {
    stringstream error_message;
    error_message << "Wrong date format: " + data_string;
    throw runtime_error(error_message.str());
  }
  stream.ignore(1);
}

// Перегрузка оператора >> для класса Date для возможности ввода объектов этого класса 
// из стандартного ввода

istream& operator>>(istream& stream, Date& date) {
  int year = 0;
  int month = 0;
  int day = 0;
  string data_string;
  string string_end = "";
  if (stream >> data_string) {
    stringstream input(data_string);
    input >> year;
    EnsureNextSymbolAndSkip(input, data_string);
    input >> month;
    EnsureNextSymbolAndSkip(input, data_string);
    input >> day;
    input >> string_end;
    if (year >= 0 && year < 10000 && month < 100 && day < 100 && string_end == "") {
      date = Date(year, month, day);
      return stream;
    } else {
      stringstream error_message;
      error_message << "Wrong date format: " + data_string;
      throw runtime_error(error_message.str());
    }
  } else {
    stringstream error_message;
    error_message << "Wrong date format: " + data_string;
    throw runtime_error(error_message.str());
  }
}

// Определение и реализация класса Databates для хранения и операций с парами Дата - Событие

class Database {
  map<Date, set<string>> dates;
public:
  void AddEvent(const Date& date, const string& event) {
    dates[date].insert(event);
  };
  bool DeleteEvent(const Date& date, const string& event) {
    if (dates.count(date)) {
        if (dates[date].count(event)) {
            dates[date].erase(event);
            return true;
        } else {
            return false;
        }     
    } else {
      return false;
    }
  };
  int DeleteDate(const Date& date) {
    if (dates.count(date)) {
      int events_nums = dates[date].size();
      dates.erase(date);
      return events_nums;
    }
    return 0;
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
};

// Определение и реализация функции ParseCommands для чтения и обработки комманд из потока

void ParseCommands(const string& command, Database& data_base) { 
  stringstream stream(command);
  string com;
  Date date;
  string event;
  if (stream >> com) {
    if (com == "Add") {
        if (stream >> date) {
            if (stream >> event) {
                data_base.AddEvent(date, event);
            } else {
                stringstream error_message;
                error_message << "Wrong date format: " << date;
                throw runtime_error(error_message.str());
            }
        }
    } else if (com == "Del") {
        if (stream >> date) {
            if (stream >> event) {
                if (data_base.DeleteEvent(date, event)) {
                    cout << "Deleted successfully" << endl;
                } else {
                    cout << "Event not found" << endl;
                }
            } else {
                cout << "Deleted " << data_base.DeleteDate(date) << " events" << endl;
            }
        }
    } else if (com == "Find") {
        if (stream >> date) {
            data_base.Find(date);
        }
    } else if (com == "Print") {
        data_base.Print();
    } else {
      stringstream error_message;
      error_message << "Unknown command: " << com;
      throw runtime_error(error_message.str());
    }
  }  
}

int main() {
  try {
    Database data_base;
    string command;

    while (getline(cin, command)) {
      ParseCommands(command, data_base);
    }
  } catch (exception& ex) {
      cout << ex.what() << endl;
  }

  return 0;
}