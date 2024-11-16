#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Transaction {
    string type;  
    string description;
    int amount;

    Transaction(const string& t, const string& d, int a) 
        : type(t), description(d), amount(a) {}
};

class BudgetManager {
public:
    void setMonthlyBudget(int budget) {
        monthlyBudget = budget;
        cout << "월간 예산이 " << monthlyBudget << "원으로 설정되었습니다." << endl;
    }

    void addIncome(int amount, const string& description) {
        transactions.push_back(Transaction("수입", description, amount));
        balance += amount;
        cout << "수입 추가: " << description << " + " << amount << "원" << endl;
    }

    void addExpense(int amount, const string& description) {
        transactions.push_back(Transaction("지출", description, amount));
        balance -= amount;
        cout << "지출 추가: " << description << " - " << amount << "원" << endl;
    }

    void showBalance() const {
        cout << "현재 잔액: " << balance << "원 (월간 예산: " << monthlyBudget << "원" << endl;
    }

    void showTransactions() const {
        cout << "거래 내역" << endl;
        for (const auto& transaction : transactions) {
            cout << transaction.type << ": " << transaction.description << " - " << transaction.amount << "원" << endl;
        }
    }

private:
    int monthlyBudget = 0;
    int balance = 0;
    vector<Transaction> transactions;
};

int main() {
    BudgetManager manager;
    int choice;

    while (true) {
        cout << "\n--- 개인 예산 관리 프로그램 ---\n";
        cout << "1. 월간 예산 설정\n";
        cout << "2. 수입 추가\n";
        cout << "3. 지출 추가\n";
        cout << "4. 잔액 확인\n";
        cout << "5. 거래 내역 보기\n";
        cout << "6. 종료\n";
        cout << "선택: ";
        cin >> choice;

        /*if (choice == 1) {
            
        } else if (choice == 2) {
            
        } else if (choice == 3) {
            
        } else if (choice == 4) {
            
        } else if (choice == 5) {
           
        } else if (choice == 6) {
            cout << "프로그램을 종료합니다.\n";
            break;
        } else {
            cout << "잘못된 입력입니다. 다시 선택해 주세요.\n";
        }*/
    }

    return 0;
}
