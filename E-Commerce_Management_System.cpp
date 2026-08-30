#include <iostream>

using namespace std;

// --- Enums & Union ---
enum Category { ELECTRONICS = 1, CLOTHING, GROCERY };
enum OrderStatus { CREATED, CONFIRMED, CANCELLED };
enum PaymentStatus { PENDING, PAID, REFUNDED };
enum PaymentMethod { CREDIT_CARD = 1, UPI, CASH };

union PaymentDetails {
    int last4Digits;
    char upiId[30];
};

// --- Product Class ---
class Product {
public:
    int id, stock;
    string name;
    double price;

    void inputProduct(int num) {
        cout << "\nProduct " << num << " ID, Name, Price, Stock: ";
        cin >> id >> name >> price >> stock;
    }

    void displayProduct() {
        cout << "ID: " << id << " | Name: " << name << " | Price: $" << price << " | Stock: " << stock << endl;
    }

    void updateStock(int qty) { stock += qty; }
    int checkAvailability(int qty) { return stock >= qty; }
};

// --- Customer Class ---
class Customer {
public:
    int id;
    string name, phone;

    void inputCustomer(int num) {
        cout << "Customer " << num << " ID, Name, Phone: ";
        cin >> id >> name >> phone;
    }

    void displayCustomer() {
        cout << "ID: " << id << " | Name: " << name << " | Phone: " << phone << endl;
    }
};

// --- Order Struct ---
struct Order {
    int orderId, customerId;
    double totalAmount;
    OrderStatus oStatus;
    PaymentStatus pStatus;
    PaymentDetails pDetails;

    void createOrder(int oId, int cId, double amount) {
        orderId = oId; customerId = cId; totalAmount = amount;
        oStatus = CREATED; pStatus = PENDING;
    }

    void confirmOrder() { oStatus = CONFIRMED; pStatus = PAID; }
    void cancelOrder()  { oStatus = CANCELLED; pStatus = REFUNDED; }

    void displayOrder() {
        cout << "\n--- Order #" << orderId << " ---\nTotal: $" << totalAmount 
             << " | Status: " << (oStatus == 1 ? "CONFIRMED" : oStatus == 2 ? "CANCELLED" : "CREATED")
             << " | Payment: " << (pStatus == 1 ? "PAID" : pStatus == 2 ? "REFUNDED" : "PENDING") << endl;
    }
};

int main() {
    // 1. Seller Login
    int sellerId;
    cout << "Enter Seller ID: ";
    cin >> sellerId;

    if (sellerId != 9293) {
        cout << "Sorry, unauthorized access!" << endl;
        return 0;
    }
    cout << "Access Granted!\n";

    // 2. Add Products
    int pCount, cCount;
    cout << "\nHow many products to add? "; cin >> pCount;
    Product products[50];
    for (int i = 0; i < pCount; i++) products[i].inputProduct(i + 1);

    // 3. Add Customers
    cout << "\nHow many customers to add? "; cin >> cCount;
    Customer customers[50];
    for (int i = 0; i < cCount; i++) customers[i].inputCustomer(i + 1);

    // 4. Order Processing & Validations
    int cId, pId, qty, payChoice;
    cout << "\n--- Place Order ---\nEnter Customer ID: "; cin >> cId;

    // Check Customer ID (Validation 1)
    int cFound = -1;
    for (int i = 0; i < cCount; i++) if (customers[i].id == cId) cFound = i;
    if (cFound == -1) { cout << "[ERROR] Invalid Customer ID!\n"; return 0; }

    cout << "Enter Product ID: "; cin >> pId;
    // Check Product ID (Validation 1)
    int pFound = -1;
    for (int i = 0; i < pCount; i++) if (products[i].id == pId) pFound = i;
    if (pFound == -1) { cout << "[ERROR] Invalid Product ID!\n"; return 0; }

    cout << "Enter Quantity: "; cin >> qty;
    // Check Stock (Validation 2)
    if (products[pFound].checkAvailability(qty) == 0) {
        cout << "[ERROR] Product Out of Stock!\n";
        return 0;
    }

    // Payment Selection & Union Usage
    cout << "Payment Method (1: Card, 2: UPI, 3: Cash): "; cin >> payChoice;
    Order ord;
    ord.createOrder(1001, cId, products[pFound].price * qty);

    if (payChoice == 1) {
        cout << "Enter Last 4 Digits of Card: "; cin >> ord.pDetails.last4Digits;
    } else if (payChoice == 2) {
        cout << "Enter UPI ID: "; cin >> ord.pDetails.upiId;
    }

    // Confirm or Cancel
    char choice;
    cout << "Confirm and Pay? (y/n): "; cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        ord.confirmOrder();
        products[pFound].updateStock(-qty);
        cout << "[SUCCESS] Payment & Order Confirmed!\n";
    } else {
        ord.cancelOrder();
        cout << "[INFO] Order Cancelled.\n";
    }

    // Summary
    ord.displayOrder();
    products[pFound].displayProduct();

    return 0;
}