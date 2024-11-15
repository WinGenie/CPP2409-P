#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Transaction{
    string type;
    string description;
    int amount;
};

class BudgetManager{
    public:
        void setMontlyBudget(int budget){
            montlyBudget = budget;
            cout << "월간 예산이 " << montlyBudget << "원으로 설정되었습니다." << endl;
        }
        void adddIncome(int amount, const string& description){
            transactions.push_back({"수입", description, amount});
            balance += amount;
            cout << "수입 추가: " << description << " + " << amount << "원" << endl;
        }
        void addExpense(int amount, const string& description){
            transactions.push_back({"지출", description, amount});
            balance -= amount;
            cout << "지출 추가: " << description << " - " << amount << "원" << endl;
        }
        void showBalance() {
            cout << "현재 잔액: " << balance << "원 (월간 예산 : " << montlyBudget << endl;
        }
    private:
        int montlyBudget = 0;
        int balance = 0;
        vector<Transaction> transactions;
};