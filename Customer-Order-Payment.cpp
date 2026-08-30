#include <iostream>

using namespace std;

enum Category { ELECTRONICS = 1, CLOTHING, GROCERY };
enum PaymentMethod { CREDIT_CARD = 1, UPI, CASH };

union PaymentDetails {
    char cardNum[17];
    char upiId[30];
    double cashReceived;
};

// --- Product Class ---
class Product {
public:
    int id, stock;
    string name;
    double price;

    void inputProduct() {
        cout << "=== Enter Product Details ===\n";
        cout << "Enter Product ID: "; cin >> id;
        cout << "Enter Product Name: "; cin >> name;
        cout << "Enter Price: $"; cin >> price;
        cout << "Enter Initial Stock Quantity: "; cin >> stock;
    }

    void displayProduct() {
        cout << "\n[Product] ID: " << id << " | Name: " << name 
             << " | Price: $" << price << " | Stock: " << stock << endl;
    }

    void updateStock(int qty) { stock += qty; }
    int checkAvailability(int qty) { return stock >= qty; }
};

// --- Customer Class ---
class Customer {
public:
    int id;
    string name, email, phone, address;

    void inputCustomer() {
        cout << "\n=== Enter Customer Details ===\n";
        cout << "Enter Customer ID: "; cin >> id;
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Email: "; cin >> email;
        cout << "Enter Phone: "; cin >> phone;
        cout << "Enter Address: "; cin >> address;
    }

    void displayCustomer() {
        cout << "[Customer] ID: " << id << " | Name: " << name 
             << " | Phone: " << phone << " | Address: " << address << endl;
    }
};

// --- Order Struct ---
struct Order {
    int orderId, customerId;
    double totalAmount;
    int oStatus; // 0: CREATED, 1: CONFIRMED, 2: CANCELLED
    int pStatus; // 0: PENDING, 1: PAID, 2: REFUNDED
    PaymentMethod pMethod;
    PaymentDetails pDetails;

    void createOrder(int oId, int cId, double amount, int methodChoice) {
        orderId = oId;
        customerId = cId;
        totalAmount = amount;
        pMethod = (PaymentMethod)methodChoice;
        oStatus = 0; // CREATED
        pStatus = 0; // PENDING
    }

    void confirmOrder() { oStatus = 1; pStatus = 1; }
    void cancelOrder()  { oStatus = 2; pStatus = 2; }

    void displayOrder() {
        cout << "\n=== Order Details ===" << endl;
        cout << "Order ID: " << orderId << " | Customer ID: " << customerId 
             << " | Amount: $" << totalAmount << endl;
        cout << "Order Status: " << (oStatus == 1 ? "CONFIRMED" : oStatus == 2 ? "CANCELLED" : "CREATED") << endl;
        cout << "Payment Status: " << (pStatus == 1 ? "PAID" : pStatus == 2 ? "REFUNDED" : "PENDING") << endl;
    }
};

int main() {
    Product p;
    Customer c;
    Order o;

    // Get input for Product & Customer
    p.inputProduct();
    c.inputCustomer();

    // Display entered info
    p.displayProduct();
    c.displayCustomer();

    // Order Placement
    int qty, payChoice;
    cout << "\n=== Place an Order ===" << endl;
    cout << "Enter quantity of " << p.name << " to buy: ";
    cin >> qty;

    if (p.checkAvailability(qty) == 1) {
        cout << "\nSelect Payment Method (1 for Credit Card, 2 for UPI, 3 for Cash): ";
        cin >> payChoice;

        o.createOrder(5001, c.id, p.price * qty, payChoice);
        cout << "\nOrder created successfully!";
        o.displayOrder();

        // Process confirmation
        char confirm;
        cout << "\nDo you want to confirm and pay for this order? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            o.confirmOrder();
            p.updateStock(-qty); // reduce stock
            cout << "\nPayment successful!";
        } else {
            o.cancelOrder();
            cout << "\nOrder cancelled.";
        }

        // Final Summary
        o.displayOrder();
        p.displayProduct();
    } else {
        cout << "\nSorry, not enough stock available!" << endl;
    }

    return 0;
}