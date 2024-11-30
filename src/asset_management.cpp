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
        expenses += amount; // 지출 금액 추가
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

    // 예산 설정 함수
    void setBudget(int amount) {
        budget = amount; // 예산 설정
        cout << "예산이 " << budget << "원으로 설정되었습니다." << endl;
    }

    // 남은 잔액을 계산하는 함수
    int getRemainingBalance() const {
        return budget - expenses; // 남은 잔액 계산
    }

    // 고정 지출을 설정하는 함수
    void setFixedExpense(int amount, const string& description) {
        // 고정 지출을 Transaction으로 추가
        fixedExpenses.push_back({"고정지출", description, amount, "고정지출"}); // 고정 지출 추가
        cout << "고정 지출이 추가되었습니다: " << description << " - " << amount << "원" << endl;
    }

    // 매월 고정 지출을 적용하는 함수
    void applyFixedExpenses() {
        for (const auto& expense : fixedExpenses) {
            addExpense("고정지출", expense.amount, expense.description); // 고정 지출 추가
        }
    }

    // 고정 지출 목록을 출력하는 함수
    void showFixedExpenses() const {
        if (fixedExpenses.empty()) {
            cout << "고정 지출이 없습니다." << endl;
            return;
        }
        cout << "\n[고정 지출 목록]" << endl;
        for (size_t i = 0; i < fixedExpenses.size(); ++i) {
            cout << i << ": " << fixedExpenses[i].description << " - " << fixedExpenses[i].amount << "원" << endl;
        }
    }

private:
    vector<Transaction> transactions; // 해당 월의 거래 내역을 저장하는 벡터
    vector<Transaction> fixedExpenses; // 고정 지출 목록
    int budget = 0; // 예산 초기화
    int expenses = 0; // 지출 초기화
};

// 연간 거래를 관리하는 클래스
class YearBudgetManager {
public:
    // 월별 거래 관리를 시작하는 함수
    void manageMonthlyBudget() {
        while (true) {
            cout << "--- 고정 지출 관리 ---" << endl;
            cout << "1. 고정 지출 추가" << endl;
            cout << "2. 관리할 달 선택하기" << endl;
            cout << "0. 종료" << endl;
            cout << "선택: ";
            int choice;
            cin >> choice;

            if (choice == 0) {
                cout << "프로그램을 종료합니다." << endl;
                break;
            } else if (choice == 1) {
                addFixedExpense();
            } else if (choice == 2) {
                selectMonth();
            } else {
                cout << "잘못된 입력입니다. 다시 선택해 주세요." << endl;
            }
        }
    }

private:
    BudgetManager budgetmanagers[12]; // 12개월 데이터를 관리하는 배열

    // 고정 지출 추가하는 함수
    void addFixedExpense() {
        int amount;
        string description;
        cout << "고정 지출 금액을 입력하세요: ";
        cin >> amount;
        cin.ignore(); // 개행 문자 제거
        cout << "고정 지출 항목을 입력하세요: ";
        getline(cin, description);
        for (int month = 0; month < 12; ++month) {
            budgetmanagers[month].setFixedExpense(amount, description); // 모든 월에 고정 지출 추가
        }
    }

    // 관리할 달 선택하는 함수
    void selectMonth() {
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
            break; // 월 선택 후 루프 종료
        }
    }

    // 특정 월의 거래를 관리하는 함수
    void manageBudgetForMonth(int month) {
        // 고정 지출 적용
        budgetmanagers[month - 1].applyFixedExpenses(); // 선택한 월의 고정 지출 적용

        int choice;
        while (true) {
            cout << "--- " << month << "월 기록 관리 ---" << endl;
            cout << "남은 예산: " << budgetmanagers[month - 1].getRemainingBalance() << "원" << endl; // 남은 예산 출력
            cout << "1. 예산 설정" << endl; // 예산 설정 옵션 추가
            cout << "2. 수입 추가" << endl;
            cout << "3. 지출 추가" << endl;
            cout << "4. 거래 내역 보기" << endl;
            cout << "5. 돌아가기" << endl;
            cout << "선택: ";
            cin >> choice;

            if (choice == 1) { // 예산 설정
                int amount;
                cout << "예산 금액을 입력하세요: ";
                cin >> amount;
                budgetmanagers[month - 1].setBudget(amount); // 선택한 월의 예산 설정

            } else if (choice == 2) { // 수입 추가
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

            } else if (choice == 3) { // 지출 추가
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

            } else if (choice == 4) { // 거래 내역 보기
                budgetmanagers[month - 1].showTransactions(); // 선택한 월의 거래 내역 출력

            } else if (choice == 5) { // 이전 메뉴로 돌아가기
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
