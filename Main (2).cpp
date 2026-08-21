#include <iostream>
using namespace std;

class GPayUser {
    string name;
    int balance;

public:
    // Constructor & Destructor
    GPayUser(string n, int b) { name = n; balance = b; }
    ~GPayUser() {}

    string getName() { return name; }
    int getBalance() { return balance; }

    void setName(string n) { name = n; }
    void setBalance(int b) { balance = b; }

    void sendMoney(GPayUser &receiver, int amount) {
        balance -= amount;
        receiver.balance += amount;
        cout << name << " paid Amount of " << amount << " to " << receiver.name << "\n";
    }
};

int main() {

    GPayUser u1("A", 1000);
    GPayUser u2("B", 500);
    GPayUser u3("C", 300);
    GPayUser u4("D", 200);
    GPayUser u5("E", 100);

    
    u1.sendMoney(u2, 200);

    // Balance check
    cout<<"Updated Balance of both users are: \n";
    cout <<"Balance of "<<u1.getName()<<" is "<<u1.getBalance() << "\n";
    cout <<"Balance of "<<u2.getName()<<" is "<<u2.getBalance() << "\n";

    return 0;
}