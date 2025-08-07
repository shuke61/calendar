#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iterator>

class Event {
public:
    std::string title;
    std::string description;
    std::string date; // format: YYYY-MM-DD

    Event(std::string t, std::string d, std::string dt)
        : title(t), description(d), date(dt) {
    }

    void print() const {
        std::cout << "  - " << title << " : " << description << "\n";
    }
};

class Calendar {
private:
    std::map<std::string, std::vector<Event>> scheduleMap;

public:
    void addEvent(const Event& e) {
        scheduleMap[e.date].push_back(e);
        std::cout << "予定を追加しました！\n";
    }

    void listEventsByDay(const std::string& date) {
        std::map<std::string, std::vector<Event>>::iterator it = scheduleMap.find(date);
        if (it == scheduleMap.end()) {
            std::cout << "この日に予定はありません。\n";
            return;
        }
        std::cout << date << " の予定：\n";
        int idx = 0;
        std::vector<Event>::iterator evIt;
        for (evIt = it->second.begin(); evIt != it->second.end(); ++evIt) {
            std::cout << "[" << idx++ << "] ";
            evIt->print();
        }
    }

    void deleteEvent(const std::string& date, int index) {
        std::map<std::string, std::vector<Event>>::iterator it = scheduleMap.find(date);
        if (it != scheduleMap.end() && index >= 0 && index < it->second.size()) {
            it->second.erase(it->second.begin() + index);
            std::cout << "予定を削除しました。\n";
            if (it->second.empty()) {
                scheduleMap.erase(date); // 空の日付は削除
            }
        }
        else {
            std::cout << "指定された予定が見つかりません。\n";
        }
    }

    void listEventsByMonth(const std::string& month) {
        std::cout << month << "月の予定一覧：\n";
        std::map<std::string, std::vector<Event>>::iterator it;
        for (it = scheduleMap.begin(); it != scheduleMap.end(); ++it) {
            if (it->first.substr(5, 2) == month) {
                std::cout << "▶ " << it->first << "\n";
                std::vector<Event>::iterator evIt;
                for (evIt = it->second.begin(); evIt != it->second.end(); ++evIt) {
                    evIt->print();         
                }
            }
        }
    }
};

void printMenu() {
    std::cout << "\n==== カレンダー予定管理 ====\n"
        << "1. 予定を追加\n"
        << "2. 予定を削除\n"
        << "3. 指定日の予定を表示\n"
        << "4. 月ごとの予定を表示\n"
        << "5. 終了\n"
        << "選択：";
}

int main() {
    Calendar calendar;
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();  // 入力バッファクリア

        if (choice == 1) {
            std::string date, title, desc;
            std::cout << "日付を入力 (YYYY-MM-DD): ";
            std::getline(std::cin, date);
            std::cout << "タイトル: ";
            std::getline(std::cin, title);
            std::cout << "詳細: ";
            std::getline(std::cin, desc);
            calendar.addEvent(Event(title, desc, date));

        }
        else if (choice == 2) {
            std::string date;
            int idx;
            std::cout << "日付を入力 (YYYY-MM-DD): ";
            std::getline(std::cin, date);
            calendar.listEventsByDay(date);
            std::cout << "削除したい予定の番号を入力: ";
            std::cin >> idx;
            std::cin.ignore();
            calendar.deleteEvent(date, idx);

        }
        else if (choice == 3) {
            std::string date;
            std::cout << "日付を入力 (YYYY-MM-DD): ";
            std::getline(std::cin, date);
            calendar.listEventsByDay(date);

        }
        else if (choice == 4) {
            std::string month;
            std::cout << "月を入力 (例: 08): ";
            std::getline(std::cin, month);
            calendar.listEventsByMonth(month);

        }
        else if (choice == 5) {
            std::cout << "終了します。\n";
            break;
        }
        else {
            std::cout << "無効な選択です。\n";
        }
    }

    return 0;
}
