#include <iostream>
using namespace std;

class Employee {
    int id;
    string name, department;
    double salary;

public:
    Employee() {
        id = 0;
        name = "None";
        department = "None";
        salary = 0;
    }

    Employee(int i, string n) {
        id = i;
        name = n;
    }

    Employee(int i, string n, string d, double s) {
        id = i;
        name = n;
        department = d;
        salary = s;
    }

    Employee(Employee &e) {
        id = e.id;
        name = e.name;
        department = e.department;
        salary = e.salary;
    }

    double calculatePay() {
        return salary;
    }

    double calculatePay(double bonus) {
        return salary + bonus;
    }

    double calculatePay(double hours, double rate) {
        return salary + hours * rate;
    }

    double calculatePay(double bonus, float tax) {
        double total = salary + bonus;
        return total - total * tax / 100;
    }

    void updateProfile(string d) {
        department = d;
    }

    void updateProfile(double s) {
        salary = s;
    }

    void updateProfile(string d, double s) {
        department = d;
        salary = s;
    }

    void show() {
        cout << id << " " << name << " "
             << department << " " << salary << endl;
    }
};

int main() {
    int id;
    string name, department;
    double salary, bonus, hours, rate;
    float tax;

    cout << "Enter ID, Name, Department, Salary: ";
    cin >> id >> name >> department >> salary;

    Employee e1;
    Employee e2(id, name);
    Employee e3(id, name, department, salary);
    Employee e4(e3);

    e3.show();

    cout << "Base Pay: " << e3.calculatePay() << endl;

    cout << "Enter Bonus: ";
    cin >> bonus;
    cout << "Pay: " << e3.calculatePay(bonus) << endl;

    cout << "Enter Overtime Hours and Rate: ";
    cin >> hours >> rate;
    cout << "Pay: " << e3.calculatePay(hours, rate) << endl;

    cout << "Enter Bonus and Tax: ";
    cin >> bonus >> tax;
    cout << "Pay after Tax: "
         << e3.calculatePay(bonus, tax) << endl;

    cout << "Enter New Department: ";
    cin >> department;
    e3.updateProfile(department);

    cout << "Enter New Salary: ";
    cin >> salary;
    e3.updateProfile(salary);

    e3.updateProfile(department, salary);

    e3.show();

    return 0;
}