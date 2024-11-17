#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 거래 내역 구조체: 수입 또는 지출 정보를 저장
struct Transaction {
    string type;        // "수입" 또는 "지출"
    string description; // 항목 설명
    int amount;         // 금액
    string date;        // 날짜 (예: "2024-11-16")
};

// 특정 월의 거래를 관리하는 클래스
class BudgetManager {
public:
    // 수입을 추가하는 함수
    void addIncome(const string& date, int amount, const string& description) {
        transactions.push_back({"수입", description, amount, date}); // 벡터에 수입 기록 추가
        cout << "수입 기록: " << date << " - " << description << " + " << amount << "원" << endl;
    }

    // 지출을 추가하는 함수
    void addExpense(const string& date, int amount, const string& description) {
        transactions.push_back({"지출", description, amount, date}); // 벡터에 지출 기록 추가
        cout << "지출 기록: " << date << " - " << description << " - " << amount << "원" << endl;
    }

    // 저장된 거래 내역을 출력하는 함수
    void showTransactions() const {
        if (transactions.empty()) { // 거래 내역이 없으면 알림
            cout << "거래 내역이 없습니다." << endl;
            return;
        }

        // 거래 내역 출력
        cout << "\n[거래 내역]" << endl;
        for (const auto& transaction : transactions) {
            cout << transaction.date << " - " << transaction.type << ": " 
                 << transaction.description << " - " << transaction.amount << "원" << endl;
        }
    }

private:
    vector<Transaction> transactions; // 해당 월의 거래 내역을 저장하는 벡터
};

// 연간 거래를 관리하는 클래스
class YearBudgetManager {
public:
    // 월별 거래 관리를 시작하는 함수
    void manageMonthlyBudget() {
        int month;
        while (true) {
            cout << "--- 월간 기록 프로그램 ---" << endl;
            cout << "1~12월 중 기록할 달을 선택하세요 (0 입력 시 종료): ";
            cin >> month;

            if (month == 0) { // 0 입력 시 종료
                cout << "프로그램을 종료합니다." << endl;
                break;
            } else if (month < 1 || month > 12) { // 유효하지 않은 달 입력
                cout << "잘못된 입력입니다. 1부터 12까지의 숫자를 입력하세요." << endl;
                continue;
            }

            // 선택한 월의 거래 관리 시작
            manageBudgetForMonth(month);
        }
    }

private:
    BudgetManager budgetmanagers[12]; // 12개월 데이터를 관리하는 배열

    // 특정 월의 거래를 관리하는 함수
    void manageBudgetForMonth(int month) {
        int choice;
        while (true) {
            cout << "--- " << month << "월 기록 관리 ---" << endl;
            cout << "1. 수입 추가" << endl;
            cout << "2. 지출 추가" << endl;
            cout << "3. 거래 내역 보기" << endl;
            cout << "4. 돌아가기" << endl;
            cout << "선택: ";
            cin >> choice;

            if (choice == 1) { // 수입 추가
                int amount;
                string description, date;
                cout << "수입 금액을 입력하세요: ";
                cin >> amount;
                cin.ignore(); // 개행 문자 제거
                cout << "수입 항목을 입력하세요: ";
                getline(cin, description);
                cout << "수입 날짜를 입력하세요 (예: 2024-11-16): ";
                getline(cin, date);
                budgetmanagers[month - 1].addIncome(date, amount, description); // 선택한 월의 수입 추가

            } else if (choice == 2) { // 지출 추가
                int amount;
                string description, date;
                cout << "지출 금액을 입력하세요: ";
                cin >> amount;
                cin.ignore(); // 개행 문자 제거
                cout << "지출 항목을 입력하세요: ";
                getline(cin, description);
                cout << "지출 날짜를 입력하세요 (예: 2024-11-16): ";
                getline(cin, date);
                budgetmanagers[month - 1].addExpense(date, amount, description); // 선택한 월의 지출 추가

            } else if (choice == 3) { // 거래 내역 보기
                budgetmanagers[month - 1].showTransactions(); // 선택한 월의 거래 내역 출력

            } else if (choice == 4) { // 이전 메뉴로 돌아가기
                cout << "이전 메뉴로 돌아갑니다." << endl;
                break;

            } else { // 잘못된 입력
                cout << "잘못된 입력입니다. 다시 선택해 주세요." << endl;
            }
        }
    }
};

int main() {
    YearBudgetManager yearlymanager; // 연간 거래 관리 객체 생성
    yearlymanager.manageMonthlyBudget(); // 월별 거래 관리 시작
    return 0;
}
