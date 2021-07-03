#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
using namespace std;

int menuFlag = 0;

template <typename T>
void printElement(T t, const int &width)
{
    const char separator = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

class customer
{
    string name, area, address;
    string tempItem[10], item[10];
    int A[10], B[10], cost1[10], cal1[10], cost2[10], cal2[10];
    int numItems = 0, areaFlag = 0, choice = 0;
    int total = 0, price = 0, totalCal = 0, totalQuant = 0, cal = 0;

public:
    void bill()
    {
        cout << "ORDER DETAILS:\n\n";
        const int width = 20;
        printElement("ITEM", width);
        printElement("QUANTITY", width);
        printElement("PRICE", width);
        printElement("CALORIES", width);
        cout << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < numItems; i++)
        {
            price = cost2[i] * B[i];
            total += price;
            cal = cal2[i] * B[i];
            totalCal += cal;
            totalQuant += B[i];
            printElement(item[i], width);
            printElement(B[i], width);
            printElement(price, width);
            printElement(cal, width);
            cout << endl;
        }
        cout << "---------------------------------------------------------------------------------------------" << endl;
        printElement("TOTAL", width);
        printElement(totalQuant, width);
        printElement(total, width);
        printElement(totalCal, width);
        cout << endl
             << "---------------------------------------------------------------------------------------------" << endl;
    }
    void payment()
    {
        int payChoice = 0, amt = 0, attempts = 3;
        bill();
        if (choice == 2 || areaFlag == 0)
            cout << "\nPay Rs." << total << " at the counter.\n";
        else
        {
            cout << "Choose you payment method:\n\n";
            cout << "1. Online\n2. Pay on Delivery\n";
            cout << "Enter your choice: ";
            cin >> payChoice;
            switch (payChoice)
            {
            case 1:
                do
                {
                    cout << "\nAmount to be paid = Rs." << total;
                    cout << "\nEnter the amount: ";
                    cin >> amt;
                    if (amt == total)
                    {
                        cout << "\nPayment successful!!";
                        cout << "\nThe order will be delivered at "<<address;
                        cout << " within 45 minutes.";
                        exit(0);
                    }
                    else
                    {
                        --attempts;
                        cout << "\nIncorrect amount!! " << attempts;
                        cout << " attempts remaining.";
                    }
                } while (attempts != 0);
                if (attempts == 0)
                {
                    cout << "\nPayment Unsuccessful after 3 attempts!!";
                    cout << "\nOrder not placed!!";
                    exit(1);
                }
            case 2:
                    cout << "\nRs. "<<total<<" to be paid at delivery.";
                    cout << "\nThe order will be delivered at "<<address;
                    cout << " within 45 minutes."; 
                    exit(0);
            default:
                    cout << "\nInvalid option!!";
                    exit(1);
            }
        }
    }
    void takeout()
    {
        cout << "\n\nThank You " << name << "!\n";
        cout << "You can pick up your order in 30 minutes.\n";
        payment();
    }
    void checkArea(string area)
    {
        string str;
        int ch = 0;
        ifstream fin("deliveryAreas.txt");
        if (fin.is_open())
        {
            while (getline(fin, str))
            {
                transform(area.begin(), area.end(), area.begin(), ::toupper);
                if (str == area)
                {
                    cout << "\nArea eligible for delivery\n";
                    areaFlag++;
                    return;
                }
            }
            if (areaFlag == 0)
            {
                cout << "\nArea not eligible for delivery. Do you want to order a takeout?\n";
                cout << "Enter 1 to proceed with takeout order or Enter 0 to exit: ";
                cin >> ch;
                if (ch == 1)
                    return;
                else
                    exit(0);
            }
        }
        fin.close();
    }
    void delivery()
    {
        cout << "Enter your address: ";
        cin.ignore();
        getline(cin, address);
        cout << "\n\nThank You " << name << "!\n";
        cout << "Your order has been placed.\n";
        payment();
    }
    void order()
    {
        string bfast[10] = {"Idli", "Dosa", "Upma", "Coffee", "Pasta",
                            "Sandwich", "Omelette", "Aloo Puri", "Bread Pakoda", "Tea"};
        string lunch[10] = {"South Indian Thali", "North Indian Thali", "Rice", "Chole Bhature",
                            "Aloo Paratha", "Paneer Paratha", "Roti with Curry", "Pulao", "Chicken Biriyani", "Egg Biriyani"};
        string dinner[10] = {"Naan", "Fried Rice", "Kadhai Paneer", "Butter Chicken", "Roti",
                             "Veg Biriyani", "Chicken Biriyani", "Egg Biriyani", "Mushroom Masala", "Dal Makhani"};

        int bfastPrice[10] = {30, 40, 25, 15, 70, 25, 30, 50, 35, 10};
        int lunchPrice[10] = {150, 160, 115, 130, 120, 150, 100, 110, 180, 150};
        int dinnerPrice[10] = {45, 100, 160, 250, 25, 150, 300, 230, 170, 150};

        int bfastCal[10] = {176, 265, 217, 249, 323, 316, 154, 324, 412, 75};
        int lunchCal[10] = {157, 212, 170, 128, 323, 346, 154, 324, 372, 289};
        int dinnerCal[10] = {317, 163, 248, 500, 100, 257, 290, 250, 78, 278};
        switch (menuFlag)
        {
        case 1:
            copy(bfast, bfast + 10, tempItem); //copies bfast into tempItem
            memcpy(cost1, bfastPrice, sizeof(bfastPrice));
            memcpy(cal1, bfastCal, sizeof(bfastCal));
            break;
        case 2:
            copy(lunch, lunch + 10, tempItem);
            memcpy(cost1, lunchPrice, sizeof(lunchPrice)); //copies lunchPrice into cost
            memcpy(cal1, lunchCal, sizeof(lunchCal));
            break;
        case 3:
            copy(dinner, dinner + 10, tempItem);
            memcpy(cost1, dinnerPrice, sizeof(dinnerPrice));
            memcpy(cal1, dinnerCal, sizeof(dinnerCal));
            break;
        default:
            exit(0);
        }
        cout << "\nEnter the number of items: ";
        cin >> numItems;
        cout << "\nEnter the serial number of the items you have chosen and their quantity\n";
        for (int i = 0; i < numItems; i++)
        {
            int j = i + 1;
            cout << "Enter serial number of item " << j << ": ";
            cin >> A[i];
            cout << "Enter the quantity: ";
            cin >> B[i];
            item[i] = tempItem[A[i] - 1];
            cost2[i] = cost1[A[i] - 1];
            cal2[i] = cal1[A[i] - 1];
            cout << endl;
        }
    }
    void getDetails()
    {
        cout << "\nPlease enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your area: ";
        getline(cin, area);
        checkArea(area);
        order();
        if (areaFlag == 0)
        {
            takeout();
        }
        else
        {
            cout << "Enter '1' for Home Delivery, Enter '2' for takeout: ";
            cin >> choice;
            if (choice == 1)
                delivery();
            else if (choice == 2)
                takeout();
            else
            {
                cout << "Not a valid option!";
                exit(0);
            }
        }
    }
};

class menu
{
public:
    void bfast()
    {
        menuFlag = 1;
        ifstream fin("bfast.txt");
        cout << "Here is the menu for breakfast:\n";
        if (fin.is_open())
        {
            cout << fin.rdbuf();
        }
        fin.close();
    }
    void lunch()
    {
        menuFlag = 2;
        ifstream fin("lunch.txt");
        cout << "Here is the menu for lunch:\n";
        if (fin.is_open())
        {
            cout << fin.rdbuf();
        }
        fin.close();
    }
    void dinner()
    {
        menuFlag = 3;
        ifstream fin("dinner.txt");
        cout << "Here is the menu for dinner:\n";
        if (fin.is_open())
        {
            cout << fin.rdbuf();
        }
        fin.close();
    }
};

void timeCheck(int hour, int min)
{
    if (hour >= 0 && hour < 8)
    {
        cout << "Sorry we are closed!!!";
        cout << "\nWe are open from 8am till midnight";
        exit(0);
    }
    else
        return;
}

void timeMenu(int hour, int min)
{
    menu m;
    //opening: 08:00 hrs, closing: 00:00 hrs
    //bf: 8:00-11:59am, lunch: 12:00-16:59, dinner: 17:00-23:59.
    if (hour >= 8 && hour < 12)
        m.bfast();
    else if (hour >= 12 && hour < 17)
        m.lunch();
    else if (hour >= 17 && hour <= 23)
        m.dinner();
}

int main()
{
    //reading system time
    time_t currTime = time(0);
    tm *timePtr = localtime(&currTime);
    int hour = timePtr->tm_hour;
    int min = timePtr->tm_min;
    //checking if service is open or closed
    timeCheck(hour, min);
    customer c;
    int ch = 0;
    cout << "\n\n\t\t\t     Welcome!!\n";
    timeMenu(hour, min);
    cout << "\n\nDo you want to place your order?\n";
    cout << "Enter '1' to place order, Enter '0' to exit: ";
    cin >> ch;
    if (ch == 1)
        c.getDetails();
    else
    {
        cout << "Thank You!";
        sleep(2); // pause before exiting
        exit(0);
    }

    return 0;
}