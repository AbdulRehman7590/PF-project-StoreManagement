#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <iomanip>
#include <ctime>
using namespace std;

// Prototypes
void printmenu(string menu);
void dateandtime();
void gotoxy(int x, int y);
void signUp();
bool signup(string num, string name, string pass, string contct);
void SignIn();
void Admininterface();
void Employeeinterface();
void Customerinterface();
bool isNum(string NN);
string isAlpha(string input);
bool logout();
void sent();
void received();
void msgsent();
void msgseen();
int whichquantity(int idx);
void halt();

// admin login check
bool checkadmin();
bool enteradmincode();
void pinsetup();

// taking and processing user data
string enterusername();
string enteruserpassword(string name);
string enterusercontact(string name, string pass);
void signupworking(string option, string name, string pass, string phone);

// admin options prototypes
void Addproduct();
void Updateproduct();
void Manage();
void Placesale();
void Customertraffic();

// further admin options prototypes
void plusproduct();
void minusproduct();
void RemoveProductonsale();
void AddProductonsale();
void updateprice();
void updatequantity();
void Employeedetails();
void Removeemployee();
bool isproductexits(string isname);

// (admin & employee) same options prototypes
void Productview();
void Onsaleproducts();
void messenger();
void Announcements();

// employee options prototypes
void lessquantity();
void orders();

// (employee & customer) same options prototypes
void productlist();
void salelist();
void order();

// customer options prototypes
void Search();
void Cart();
void Bill();

// further customer options prototypes
void addcart();
void removecart();
bool cartremoving(string productname);
string productsavailability(int idx);

// data store functions
void storepin();
void storebuystatus();
void storelogindata(string num, string name, string pass, string cntct);
void storeproductdata(string name, int value, int ratio, int salevalue);
void storecartproductsdata(string custname, string name, int value, int ratio, int salevalue);
void storeorderfiledata(string custname, string name, int value, int ratio, int salevalue);
void storeannouncements(string name, string transferdata);

// data load functions
void loadpin();
void loadlogindata();
void loadproductsdata();
void loadcartproductsdata();
void loadbuystatus();
void loadannouncements();
void loadorderfiledata();

// data update storage functions
void updatelogindata();
void updateproductsdata();
void updatecartproductsdata();
void updatepin();
void updatebuystatus();
void updateorderfiledata();

// data parsing function
string parsedata(string line, int field);

// global arrays
string role[100];          // role of user
string username[100];      // name of user
string password[100];      // password of user
string contact[100];       // phone no. of user
string product[100];       // name of product
int price[100];            // price of product
int quantity[100];         // quantity of product
int originalquantity[100]; // to store original quantity of products
int sale[100];             // sale percentage
string chat[100];          // stores Announcements
string chatsender[100];    // to know who is making announcements
string message[100];       // stores messages
string msgsender[100];     // to know whos is texting

// global variables
string pin;               // to store the admin login pin
string Loginname;         // login names
string Loginpass;         // login passwords
string inter;             // header interface message
int count = 0;            // no. of users
int ProductsCount = 0;    // no. of products
int msg = 0;              // no. of Announcements
bool buy = false;         // to send list of order to employee
int cart = 0;             // no. of products in cart
string customername[100]; // name of customer buying products
string cartproduct[100];  // name of products in cart
int cartprice[100];       // price of cart items
int cartquant[100];       // to store quantity of products in cart
int cartsale[100];        // cart sale on products
int orderCount = 0;       // No. of products in order
string orderName[100];    // name of order giver
string orderProduct[100]; // name of products in order
int orderPrice[100];      // price of products in order
int orderQuant[100];      // quantity of products in order
int orderSale[100];       // sale on products in order

// Main
main()
{
    string number;
    bool check = true;
    loadpin();
    loadbuystatus();
    loadlogindata();
    loadproductsdata();
    loadcartproductsdata();
    loadorderfiledata();
    loadannouncements();

    while (check)
    {
        // login page
        inter = "Login screen";
        printmenu(inter);
        cout << "1. Sign up : " << endl;
        cout << "2. Sign in : " << endl;
        cout << "3. Exit " << endl
             << endl;
        cout << "Select option : ";
        cin >> number;

        // signup
        if (number == "1")
        {
            signUp();
        }

        // sign in
        else if (number == "2")
        {
            SignIn();
        }

        // exit program
        else if (number == "3")
        {
            check = false;
        }

        // invalid number
        else
        {
            cout << " " << endl;
            cout << "Enter valid number " << endl;
            halt();
        }
    }
}

// goto function body
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

// header
void printmenu(string menu)
{
    system("cls");

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 12);
    cout << " $$$$$$\\  $$\\   $$\\  $$$$$$\\  $$$$$$$\\        $$\\   $$\\  $$$$$$\\  $$\\      $$\\ $$$$$$$$\\  " << endl;
    cout << "$$  __$$\\ $$ |  $$ |$$  __$$\\ $$  __$$\\       $$$\\  $$ |$$  __$$\\ $$$\\    $$$ |$$  _____| " << endl;
    SetConsoleTextAttribute(h, 11);
    cout << "$$ /  \\__|$$ |  $$ |$$ /  $$ |$$ |  $$ |      $$$$\\ $$ |$$ /  $$ |$$$$\\  $$$$ |$$ |       " << endl;
    cout << "\\$$$$$$\\  $$$$$$$$ |$$ |  $$ |$$$$$$$  |      $$ $$\\$$ |$$$$$$$$ |$$\\$$\\$$ $$ |$$$$$\\     " << endl;
    cout << " \\____$$\\ $$  __$$ |$$ |  $$ |$$  ____/       $$ \\$$$$ |$$  __$$ |$$ \\$$$  $$ |$$  __|    " << endl;
    SetConsoleTextAttribute(h, 9);
    cout << "$$\\   $$ |$$ |  $$ |$$ |  $$ |$$ |            $$ |\\$$$ |$$ |  $$ |$$ |\\$  /$$ |$$ |       " << endl;
    cout << "\\$$$$$$  |$$ |  $$ | $$$$$$  |$$ |            $$ | \\$$ |$$ |  $$ |$$ | \\_/ $$ |$$$$$$$$\\  " << endl;
    cout << " \\______/ \\__|  \\__| \\______/ \\__|            \\__|  \\__|\\__|  \\__|\\__|     \\__|\\________| " << endl;

    SetConsoleTextAttribute(h, 15);
    cout << "*****************************************************************************************" << endl
         << endl;

    gotoxy(30, 10);
    dateandtime();

    SetConsoleTextAttribute(h, 6);
    cout << " \t \t \t \t " << menu << endl;
    SetConsoleTextAttribute(h, 15);
    cout << "*****************************************************************************************" << endl
         << endl;
}

// To show date and time
void dateandtime()
{
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    char *dt = ctime(&now);

    cout << dt << endl;
}

// signup function
void signUp()
{
    // local variales
    string option;
    string name, pass, phone;

    // signup header
    inter = "Role Selection";
    printmenu(inter);

    // taking role
    cout << "1. As Admin " << endl;
    cout << "2. As Employee" << endl;
    cout << "3. As Customer " << endl;
    cout << "4. Move Back " << endl
         << endl;
    cout << "Select Option : ";
    cin >> option;
    if (option == "1")
    {
        if (checkadmin() == false)
        {
            name = enterusername();
            pass = enteruserpassword(name);
            phone = enterusercontact(name, pass);
            signupworking(option, name, pass, phone);
            pinsetup();
        }
        else
        {
            if (enteradmincode() == true)
            {
                name = enterusername();
                pass = enteruserpassword(name);
                phone = enterusercontact(name, pass);
                signupworking(option, name, pass, phone);
            }
            else
            {
                cout << endl;
                cout << "You can't Sign up as Admin without code !" << endl;
            }
        }
    }
    else if (option == "2")
    {
        if (enteradmincode() == true)
        {
            name = enterusername();
            pass = enteruserpassword(name);
            phone = enterusercontact(name, pass);
            signupworking(option, name, pass, phone);
        }
        else
        {
            cout << endl;
            cout << "You can't Sign up as Employee without code !" << endl;
        }
    }
    else if (option == "3")
    {
        name = enterusername();
        pass = enteruserpassword(name);
        phone = enterusercontact(name, pass);
        signupworking(option, name, pass, phone);
    }
    else if (option == "4")
    {
    }
    else
    {
        cout << "Invalid number !" << endl;
    }
    cout << endl;
    halt();
}

// take user name
string enterusername()
{
    string name;
    // signup header
    inter = "Sign up Screen";
    printmenu(inter);

    // taking inputs
    cout << "Enter Username : ";
    cin.clear();
    cin.sync();
    getline(cin >> ws, name);
    name = isAlpha(name);
    return name;
}
// take user password
string enteruserpassword(string name)
{
    string pass;
    int passlength = 0;
    while (passlength != 4)
    {
        inter = "Sign up Screen";
        printmenu(inter);

        cout << "Enter Username : " << name << endl;

        cout << "Set Password(4 digits only) : ";
        cin.clear();
        cin.sync();
        getline(cin, pass);
        passlength = pass.length();
    }
    return pass;
}
// take user contact
string enterusercontact(string name, string pass)
{
    string phone;
    int cntctlength = 0;
    bool status;
    while (cntctlength != 10)
    {
        inter = "Sign up Screen";
        printmenu(inter);

        cout << "Enter Username : " << name << endl;
        cout << "Set Password(4 digits only) : " << pass << endl;

        // taking and checking contact no.
        cout << "Enter your contact number(10 digits) : +92 ";
        cin.clear();
        cin.sync();
        getline(cin, phone);
        cntctlength = phone.length();
        status = isNum(phone);
        if (status == false)
        {
            cout << endl;
            cout << "Enter Correct Number" << endl;
            cntctlength = 5;
        }
    }
    return phone;
}
// signup working
void signupworking(string option, string name, string pass, string phone)
{
    bool check;
    // working
    check = signup(option, name, pass, phone);
    if (check == false)
    {
        cout << " " << endl;
        cout << "User already exist" << endl
             << endl;
    }
    else
    {
        cout << " " << endl;
        cout << "Sign Up Successfully" << endl
             << endl;
    }
}

// signup function
bool signup(string num, string name, string pass, string contct)
{
    bool status = true;

    for (int index = 0; index < count; index++)
    {
        if (username[index] == name && password[index] == pass)
        {
            status = false;
            break;
        }
    }
    if (status == true)
    {
        role[count] = num;
        username[count] = name;
        password[count] = pass;
        contact[count] = contct;
        storelogindata(num, name, pass, contct);
        count++;
    }
    return status;
}

// sign In function
void SignIn()
{
    int counter = 0;
    // sign in header
    inter = "Sign in Screen";
    printmenu(inter);

    // taking inputs
    cout << "Enter the username : ";
    cin.clear();
    cin.sync();
    getline(cin, Loginname);
    cout << "Enter password : ";
    cin.clear();
    cin.sync();
    getline(cin, Loginpass);

    // working
    for (int idx = 0; idx < count; idx++)
    {
        if (username[idx] == Loginname && password[idx] == Loginpass)
        {
            if (role[idx] == "1")
            {
                Admininterface();
            }
            else if (role[idx] == "2")
            {
                Employeeinterface();
            }
            else if (role[idx] == "3")
            {
                Customerinterface();
            }
            break;
        }
        counter++;
    }
    if (counter == count)
    {
        // sign in header
        inter = "Sign in Screen";
        printmenu(inter);
        cout << "No user found !" << endl
             << endl;
        halt();
    }
}

// admin check function
bool checkadmin()
{
    bool flag = false;
    for (int x = 0; x < count; x++)
    {
        if (role[x] == "1")
        {
            flag = true;
        }
    }
    return flag;
}

// admin pin setup
void pinsetup()
{
    int pinlength = 0;
    bool status;
    // signup header
    inter = "Sign up Screen";
    printmenu(inter);

    while (pinlength != 5)
    {
        cout << "Enter (5 number)pin to login as admin : ";
        cin >> pin;
        pinlength = pin.length();
        status = isNum(pin);
        if (status == false)
        {
            pinlength = 2;
        }
    }
    cout << "Pin updated !" << endl
         << endl;
    storepin();
    updatepin();
    halt();
}
// check admin login code
bool enteradmincode()
{
    string code;
    bool flag;
    cout << endl;
    cout << "Enter the (5digit) code to Sign up : ";
    cin >> code;

    if (code == pin)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }
    return flag;
}

// is num function
bool isNum(string NN)
{
    bool check;
    int size = NN.length();
    int isdigit;
    for (int count = 0; count < size; count++)
    {
        isdigit = int(NN[count]);
        if (isdigit >= 48 && isdigit <= 57)
        {
            check = true;
        }
        else
        {
            check = false;
            break;
        }
    }
    return check;
}

// is alphabet function
string isAlpha(string input)
{
    int size;
    int check;
    bool flap;
    while (true)
    {
        size = input.length();
        for (int i = 0; i < size; i++)
        {
            check = int(input[i]);
            if ((check >= 65 && check <= 90) || (check >= 97 && check <= 122) || input[i] == ' ')
            {
                flap = true;
            }
            else
            {
                flap = false;
                break;
            }
        }
        if (flap == true)
        {
            return input;
        }
        else
        {
            cin.clear();
            cin.sync();
            cout << "Wrong Charater..." << endl;
            cout << "Enter Again: ";
            getline(cin >> ws, input);
        }
    }
}

// log out function
bool logout()
{
    bool status = false;
    inter = "Logout message";
    printmenu(inter);

    char num;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 12);
    cout << "|| Are you sure you want to log out ||" << endl
         << endl;
    SetConsoleTextAttribute(h, 15);
    cout << "Press 1 to Log out " << endl;
    cout << "Press any key to cancel" << endl;
    cout << "Enter option : ";
    cin >> num;
    if (num == '1')
    {
        status = true;
    }
    return status;
}

// Which quantity to show
int whichquantity(int idx)
{
    int val = 0;

    if (buy == true)
    {
        val = quantity[idx];
    }
    else
    {
        val = originalquantity[idx];
    }
    return val;
}

// halt function
void halt()
{
    cout << "Press any key to continue...";
    getch();
}

// Admin interface
void Admininterface()
{
    string option;
    bool check;
    while (true)
    {
        inter = "Admin Interface";
        printmenu(inter);

        cout << "1.  View list of products  " << endl;
        cout << "2.  View products on sale  " << endl
             << endl;
        cout << "3.  Add/Remove product  " << endl;
        cout << "4.  Update the product  " << endl;
        cout << "5.  Place products on sale " << endl
             << endl;
        cout << "6.  Manage Employee  " << endl;
        cout << "7.  See customer traffic " << endl
             << endl;
        cout << "8.  Message an Employee " << endl;
        cout << "9.  Check Announcements Section" << endl
             << endl;
        cout << "10. Update Admin Sign up Pin " << endl
             << endl;
        cout << "11. Log out " << endl
             << endl;
        cout << "Enter your option : ";
        cin >> option;
        if (option == "1")
        {
            Productview();
        }
        else if (option == "2")
        {
            Onsaleproducts();
        }
        else if (option == "3")
        {
            Addproduct();
        }
        else if (option == "4")
        {
            Updateproduct();
        }
        else if (option == "5")
        {
            Placesale();
        }
        else if (option == "6")
        {
            Manage();
        }
        else if (option == "7")
        {
            Customertraffic();
        }
        else if (option == "8")
        {
            messenger();
        }
        else if (option == "9")
        {
            Announcements();
        }
        else if (option == "10")
        {
            pinsetup();
        }
        else if (option == "11")
        {
            check = logout();
            if (check == true)
            {
                break;
            }
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// admin option 3
void Addproduct()
{
    string num;
    while (true)
    {
        inter = "Add/Remove products";
        printmenu(inter);

        cout << "1. Add product" << endl;
        cout << "2. Remove product" << endl;
        cout << "3. Back to main menu" << endl
             << endl;
        cout << "Enter your option : ";
        cin >> num;

        if (num == "1")
        {
            plusproduct();
            //  ProductsCount is a global variable declared for loop iterations
            ProductsCount++;
        }
        else if (num == "2")
        {
            minusproduct();
        }
        else if (num == "3")
        {
            break;
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// admin option 4
void Updateproduct()
{
    string name;
    string option;

    while (true)
    {
        inter = "Update the Product";
        printmenu(inter);

        cout << "1. Update the Price" << endl;
        cout << "2. Update the Quantity" << endl;
        cout << "3. Back to main menu" << endl
             << endl;
        cout << "Enter your option : ";
        cin >> option;

        if (option == "1")
        {
            updateprice();
        }
        else if (option == "2")
        {
            updatequantity();
        }
        else if (option == "3")
        {
            break;
        }
        else
        {
            cout << endl;
            cout << "Invalid Option !" << endl
                 << endl;
            halt();
        }
    }
}
// admin option 5
void Manage()
{
    char num = 0;
    while (true)
    {
        inter = "Manage Employee";
        printmenu(inter);

        cout << "1. Watch Employee" << endl;
        cout << "2. Remove Employee" << endl;
        cout << "3. Back to main menu" << endl
             << endl;
        cout << "Enter your option : ";
        cin >> num;

        if (num == '1')
        {
            Employeedetails();
        }
        else if (num == '2')
        {
            Removeemployee();
        }
        else if (num == '3')
        {
            break;
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// admin option 7
void Placesale()
{
    char num = 0;
    while (true)
    {
        inter = "Add/Remove products";
        printmenu(inter);

        cout << "1. Add sale on product" << endl;
        cout << "2. Remove sale from product" << endl;
        cout << "3. Back to main menu" << endl
             << endl;
        cout << "Enter your option : ";
        cin >> num;

        if (num == '1')
        {
            AddProductonsale();
        }
        else if (num == '2')
        {
            RemoveProductonsale();
        }
        else if (num == '3')
        {
            break;
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// admin option 8
void Customertraffic()
{
    inter = "Customer traffic";
    printmenu(inter);
    int index = 0;

    cout << left << setw(20) << "Index" << setw(20) << "Name" << setw(20) << "Contact no." << endl
         << endl;
    for (int y = 0; y < count; y++)
    {
        if (role[y] == "3")
        {
            index++;
            cout << left << setw(20) << index << setw(20) << username[y] << "+92 " << contact[y] << endl;
        }
    }
    cout << endl;
    halt();
}

// admin opt3 (add product)
void plusproduct()
{
    bool check = true;
    string num, val;
    string checknameproduct;
    while (true)
    {
        inter = "Add Product";
        printmenu(inter);

        while (true)
        {
            cout << "Enter the name of product : ";
            cin.clear();
            cin.sync();
            getline(cin >> ws, checknameproduct);

            if (isproductexits(checknameproduct) == true)
            {
                cout << endl;
                cout << "Product already exists. " << endl
                     << endl;
                ProductsCount--;
                break;
            }
            product[ProductsCount] = checknameproduct;
            while (check)
            {
                cout << "Price of product(per piece) : ";
                cin >> price[ProductsCount];
                val = to_string(price[ProductsCount]);
                if (isNum(val) == false)
                {
                    cout << endl;
                    cout << "Enter Correct Amount" << endl;
                    check = true;
                }
                else
                {
                    check = false;
                }
            }

            cout << "Enter quantity of product :";
            cin >> quantity[ProductsCount];
            originalquantity[ProductsCount] = quantity[ProductsCount];
            sale[ProductsCount] = 0;
            storeproductdata(product[ProductsCount], price[ProductsCount], quantity[ProductsCount], sale[ProductsCount]);
            break;
        }

        inter = "Add Product";
        printmenu(inter);

        cout << "1. Add more " << endl;
        cout << "2. Move back " << endl;
        cout << "Select option : ";
        cin >> num;

        if (num == "1")
        {
            ProductsCount++;
        }
        else if (num == "2")
        {
            break;
        }
        else
        {
            cout << endl;
            cout << "Invalid Option !" << endl
                 << endl;
        }
        halt();
    }
}
// admin opt3 (remove product)
void minusproduct()
{
    string productname;
    string option;

    while (true)
    {
        inter = "Remove products";
        printmenu(inter);

        cout << "1. Remove" << endl;
        cout << "2. Move back" << endl;
        cout << "Select option : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Remove products";
            printmenu(inter);

            cout << "Enter the name of product : ";
            cin.clear();
            cin.sync();
            getline(cin >> ws, productname);

            for (int counter = 0; counter < ProductsCount; counter++)
            {
                if (productname == product[counter])
                {
                    // ProductsCount is used for loop iterations declared globally
                    for (int x = counter; x < ProductsCount - 1; x++)
                    {
                        product[x] = product[x + 1];
                        price[x] = price[x + 1];
                        quantity[x] = quantity[x + 1];
                        sale[x] = sale[x + 1];
                    }
                    cartremoving(productname);
                    ProductsCount--;
                    updateproductsdata();

                    inter = "Remove products";
                    printmenu(inter);

                    cout << "Product removed !" << endl
                         << endl;
                    halt();
                    break;
                }
                else
                {
                    inter = "Remove products";
                    printmenu(inter);

                    cout << "No product found !" << endl
                         << endl;
                }
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << " Invalid option" << endl
                 << endl;
        }
        halt();
    }
}
// admin opt6 (watch employee)
void Employeedetails()
{
    inter = "Employee's details";
    printmenu(inter);
    int index = 0;

    cout << left << setw(20) << "Index" << setw(20) << "Name" << setw(20) << "contact no." << endl
         << endl;
    for (int y = 0; y < count; y++)
    {
        if (role[y] == "2")
        {
            index++;
            cout << left << setw(20) << index << setw(20) << username[y] << "+92 " << contact[y] << endl;
        }
    }
    halt();
}
// admin opt6 (remove employee)
void Removeemployee()
{
    int empcounter = 0;
    string empname;
    string option;

    while (true)
    {
        inter = "Remove Employee";
        printmenu(inter);

        cout << "1. Remove" << endl;
        cout << "2. Move back" << endl;
        cout << "Select option : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Remove Employee";
            printmenu(inter);

            cout << "Enter the name of employee : ";
            cin.clear();
            cin.sync();
            getline(cin, empname);

            // count is the no. of users
            for (int counter = 0; counter < count; counter++)
            {
                if (empname == username[counter] && role[counter] == "2")
                {
                    for (int x = counter; x < count; x++)
                    {
                        role[x] = role[x + 1];
                        username[x] = username[x + 1];
                        password[x] = password[x + 1];
                        contact[x] = contact[x + 1];
                    }
                    count--;
                    updatelogindata();

                    inter = "Remove Employee";
                    printmenu(inter);
                    cout << "Employee removed !" << endl
                         << endl;
                    break;
                }
                empcounter++;
            }
            if (empcounter == count)
            {

                inter = "Remove Employee";
                printmenu(inter);
                cout << "No user found !" << endl
                     << endl;
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << " Invalid option" << endl
                 << endl;
        }
        halt();
    }
}
// admin opt5 (add sale)
void AddProductonsale()
{
    int index = 0;
    string name;
    string option;

    while (true)
    {
        inter = "Place product one Sale";
        printmenu(inter);

        cout << "1. Search " << endl;
        cout << "2. Move back " << endl;
        cout << "Select : ";
        cin >> option;

        if (option == "1")
        {

            inter = "Place product one Sale";
            printmenu(inter);

            cout << "Enter name of product : ";
            cin.clear();
            cin.ignore();
            getline(cin, name);

            for (int idx = 0; idx < ProductsCount; idx++)
            {
                if (name == product[idx])
                {
                    inter = "Place product on sale";
                    printmenu(inter);

                    cout << "Place a sale of : ";
                    cin >> sale[idx];
                    updateproductsdata();
                    break;
                }
                index++;
            }
            if (index == ProductsCount)
            {
                inter = "Place product on sale";
                printmenu(inter);
                cout << "Product not found !" << endl
                     << endl;
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
        halt();
    }
}
// admin opt5 (remove sale)
void RemoveProductonsale()
{
    int salecounter = 0;
    string productname;
    char option;

    while (true)
    {
        inter = "Remove products from sale";
        printmenu(inter);

        cout << "1. Remove" << endl;
        cout << "2. Move back" << endl;
        cout << "Select option : ";
        cin >> option;

        if (option == '1')
        {
            inter = "Remove products from sale";
            printmenu(inter);

            cout << "Enter the name of product : ";
            cin.clear();
            cin.sync();
            getline(cin, productname);

            for (int counter = 0; counter < ProductsCount; counter++)
            {
                if (productname == product[counter] && sale[counter] > 0)
                {
                    sale[counter] = 0;

                    inter = "Remove products from sale";
                    printmenu(inter);

                    cout << "Product removed from sale !" << endl
                         << endl;

                    updateproductsdata();
                    break;
                }
                salecounter++;
            }
            if (salecounter == ProductsCount)
            {
                inter = "Remove products from sale";
                printmenu(inter);

                cout << "No product found !" << endl
                     << endl;
            }
        }
        else if (option == '2')
        {
            break;
        }
        else
        {
            cout << " Invalid option" << endl
                 << endl;
        }
        halt();
    }
}
// admin opt4 (price updating)
void updateprice()
{
    string option, name;

    while (true)
    {
        inter = "Update the price of Product";
        printmenu(inter);

        cout << "1. Search " << endl;
        cout << "2. Move back " << endl;
        cout << "Select : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Update the price of product";
            printmenu(inter);

            cout << "Enter name of product : ";
            cin.clear();
            cin.ignore();
            getline(cin, name);

            for (int idx = 0; idx < ProductsCount; idx++)
            {
                if (name == product[idx])
                {

                    inter = "Update the price of product";
                    printmenu(inter);

                    cout << "Old price is : " << price[idx] << endl;
                    cout << "New price is : ";
                    cin >> price[idx];
                    cout << endl;

                    cout << "Price updated !" << endl;
                    updateproductsdata();
                    break;
                }
                else
                {
                    inter = "Update the price of product";
                    printmenu(inter);

                    cout << "Product not found !" << endl
                         << endl;
                }
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
        halt();
    }
}
// admin opt4 (quantity updating)
void updatequantity()
{
    string option, name;

    while (true)
    {
        inter = "Update the quantity of Product";
        printmenu(inter);

        cout << "1. Search " << endl;
        cout << "2. Move back " << endl;
        cout << "Select : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Update the quantity of product";
            printmenu(inter);

            cout << "Enter name of product : ";
            cin.clear();
            cin.ignore();
            getline(cin, name);

            for (int idx = 0; idx < ProductsCount; idx++)
            {
                if (name == product[idx])
                {
                    inter = "Update the quantity of product";
                    printmenu(inter);

                    cout << "Old quantity is : " << quantity[idx] << endl;
                    cout << "New quantity is : ";
                    cin >> quantity[idx];

                    originalquantity[idx] = quantity[idx];

                    cout << endl;
                    cout << "quantity updated !" << endl;
                    updateproductsdata();
                    break;
                }
                else
                {
                    inter = "Update the quantity of product";
                    printmenu(inter);

                    cout << "Product not found !" << endl
                         << endl;
                }
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
        halt();
    }
}
// checking for same product
bool isproductexits(string isname)
{
    bool flag = false;
    for (int x = 0; x < ProductsCount; x++)
    {
        if (product[x] == isname)
        {
            flag = true;
        }
    }
    return flag;
}

// (admin and employee) same functions
// product details
void Productview()
{
    inter = "Product details";
    printmenu(inter);
    int index = 0;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << left << setw(20) << "Index" << setw(20) << "Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl
         << endl;
    for (int idx = 0; idx < ProductsCount; idx++)
    {
        index++;
        SetConsoleTextAttribute(h, 15);
        cout << left << setw(20) << index << setw(20) << product[idx] << setw(20) << price[idx] << setw(20) << whichquantity(idx) << endl;
    }
    cout << endl;
    halt();
}
// on sale product details
void Onsaleproducts()
{
    inter = "Product On sale";
    printmenu(inter);
    int index = 0;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << left << setw(20) << "Index" << setw(20) << "Name" << setw(20) << "Actual Price" << setw(20) << "Quantity" << setw(20) << "Sale" << endl
         << endl;
    for (int idx = 0; idx < ProductsCount; idx++)
    {
        if (sale[idx] > 0)
        {
            index++;
            SetConsoleTextAttribute(h, 15);
            cout << left << setw(20) << index << setw(20) << product[idx] << setw(20) << price[idx] << setw(20) << whichquantity(idx) << sale[idx] << "%" << endl;
        }
    }
    cout << endl;
    halt();
}
// Announcements
void Announcements()
{
    char num = 0;
    while (true)
    {
        inter = "Announcements";
        printmenu(inter);

        cout << "1. Make Announcement " << endl;
        cout << "2. Watch Announcement " << endl;
        cout << "3. Back to main menu" << endl
             << endl;
        cout << "Select option : ";
        cin >> num;

        if (num == '1')
        {
            sent();
        }
        else if (num == '2')
        {
            received();
        }
        else if (num == '3')
        {
            break;
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// Announcements (sent)
void sent()
{
    char option;
    string announced;

    while (true)
    {
        inter = "Announcements Log-in";
        printmenu(inter);

        cout << "1. Log-in to Announcements " << endl;
        cout << "2. Move back" << endl
             << endl;
        cout << "Select option : ";
        cin >> option;

        if (option == '1')
        {
            inter = "Announcements";
            printmenu(inter);

            chatsender[msg] = Loginname;

            cout << "Type Announcement : ";
            cin.clear();
            cin.sync();
            getline(cin, announced);
            if (announced != "")
            {
                chat[msg] = announced;
                storeannouncements(chatsender[msg], chat[msg]);
                msg++;
            }
            cout << endl;
        }
        else if (option == '2')
        {
            break;
        }
        else
        {
            cout << " Invalid option" << endl
                 << endl;
        }
        halt();
    }
}
// Announcements (received)
void received()
{
    if (msg > 0)
    {
        inter = "Announcements";
        printmenu(inter);

        // q is used as a counter
        for (int q = 0; q < msg; q++)
        {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 11);
            cout << "From : " << chatsender[q] << endl
                 << endl;
            SetConsoleTextAttribute(h, 15);
            cout << chat[q] << endl
                 << endl;
        }
    }
    else
    {
        inter = "Announcements";
        printmenu(inter);

        cout << "No announcements !!!" << endl
             << endl;
    }
    halt();
}

// ( Messenger has limitation that it can send 1 personal message per person. If a 2nd message
//  is sent through this, the 2st message will be overwritten. )
// Messenger
void messenger()
{
    char num = 0;
    while (true)
    {
        inter = "Messenger";
        printmenu(inter);

        cout << "1. Message " << endl;
        cout << "2. See messages " << endl;
        cout << "3. Back to main menu" << endl
             << endl;
        cout << "Enter your option : ";
        cin >> num;

        if (num == '1')
        {
            msgsent();
        }
        else if (num == '2')
        {
            msgseen();
        }
        else if (num == '3')
        {
            break;
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// message sent
void msgsent()
{
    int counter = 0;
    string receivername;
    string option;

    while (true)
    {
        inter = "Messenger Log-in";
        printmenu(inter);

        cout << "1. Log-in to messenger " << endl;
        cout << "2. Move back" << endl
             << endl;
        cout << "Select option : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Messenger";
            printmenu(inter);

            cout << "Enter receiver's name : ";
            cin.clear();
            cin.sync();
            getline(cin, receivername);

            for (int idx = 0; idx < count; idx++)
            {
                if (receivername == username[idx])
                {
                    inter = "Messenger";
                    printmenu(inter);

                    msgsender[idx] = Loginname;

                    cout << "Type message : ";
                    cin.clear();
                    cin.sync();
                    getline(cin, message[idx]);

                    cout << endl;
                    halt();
                    break;
                }
                counter++;
            }
            if (counter == count)
            {
                inter = "Messenger";
                printmenu(inter);

                cout << "No user found !!!" << endl
                     << endl;
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << " Invalid option" << endl
                 << endl;
        }
        halt();
    }
}
// message watch
void msgseen()
{
    string option;

    while (true)
    {
        inter = "Messenger Log-in interface";
        printmenu(inter);

        cout << "1. Messenger " << endl;
        cout << "2. Move back" << endl
             << endl;
        cout << "Select option : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Messenger";
            printmenu(inter);

            for (int idx = 0; idx < count; idx++)
            {
                if (username[idx] == Loginname)
                {
                    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(h, 14);
                    cout << "From : " << msgsender[idx] << endl
                         << endl;
                    cout << message[idx] << endl
                         << endl;
                    break;
                }
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << " Invalid option" << endl
                 << endl;
        }
        halt();
    }
}

// Employee interface
void Employeeinterface()
{
    string option;
    bool check;
    while (true)
    {
        inter = "Employee Interface";
        printmenu(inter);

        cout << "1.  View list of products  " << endl;
        cout << "2.  View list of products on sale  " << endl;
        cout << "3.  Checkout Products in less quantity " << endl
             << endl;
        cout << "4.  Pending order " << endl;
        cout << "5.  Update order list " << endl
             << endl;
        cout << "6.  check Announcements " << endl;
        cout << "7.  Messenger " << endl
             << endl;
        cout << "8.  Log out " << endl
             << endl;
        cout << "Enter your option : ";
        cin >> option;
        if (option == "1")
        {
            Productview();
        }
        else if (option == "2")
        {
            Onsaleproducts();
        }
        else if (option == "3")
        {
            if (buy == true)
            {
                lessquantity();
            }
            else
            {
                inter = "Employee Interface";
                printmenu(inter);

                cout << "No products in less quantity !" << endl
                     << endl;
                halt();
            }
        }
        else if (option == "4")
        {
            if (buy == true)
            {
                orders();
            }
            else
            {
                inter = "Employee Interface";
                printmenu(inter);

                cout << "No new order received !" << endl
                     << endl;
                halt();
            }
        }
        else if (option == "5")
        {
            inter = "Order Completed.";
            printmenu(inter);

            cout << "Order list updated !" << endl
                 << endl;
            // for updating prices
            for (int x = 0; x < ProductsCount; x++)
            {
                for (int y = 0; y < orderCount; y++)
                {
                    if (product[x] == orderProduct[y])
                    {
                        originalquantity[x] = quantity[x];
                    }
                }
            }
            updateproductsdata();
            orderCount = 0;
            updateorderfiledata();
            halt();
        }
        else if (option == "6")
        {
            Announcements();
        }
        else if (option == "7")
        {
            messenger();
        }
        else if (option == "8")
        {
            check = logout();
            if (check == true)
            {
                break;
            }
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// employe option 3
void lessquantity()
{
    inter = "Products less than 30 %";
    printmenu(inter);
    int index = 0, data = 0;

    cout << left << setw(20) << "Index" << setw(20) << "Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl
         << endl;
    for (int idx = 0; idx < ProductsCount; idx++)
    {
        data = ((quantity[idx] * 100) / originalquantity[idx]);
        if (data < 30)
        {
            index++;
            cout << left << setw(20) << index << setw(20) << product[idx] << setw(20) << price[idx] << setw(20) << quantity[idx] << endl;
        }
    }
    halt();
}
// order list
void orders()
{
    int total = 0, index = 0, discount = 0;
    inter = "Order details";
    printmenu(inter);

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << left << setw(20) << "Index" << setw(20) << "Product" << setw(20) << "Quantity" << setw(20) << "Price" << setw(20) << "Sale" << endl
         << endl;
    for (int idx = 0; idx < orderCount; idx++)
    {
        if (orderQuant[idx] > 0)
        {
            index++;
            SetConsoleTextAttribute(h, 15);
            cout << left << setw(20) << index << setw(20) << orderProduct[idx] << setw(20) << orderQuant[idx] << setw(20) << orderPrice[idx] << orderSale[idx] << "%" << endl;

            if (orderSale[idx] > 0)
            {
                discount = ((orderPrice[idx] * orderSale[idx]) / 100);
                total = total + (orderQuant[idx] * discount);
            }
            else
            {
                total = total + (orderQuant[idx] * orderPrice[idx]);
            }
        }
    }
    orderCount = 0;
    cout << endl;

    SetConsoleTextAttribute(h, 9);
    cout << "Total bill is : " << total << endl
         << endl;
    halt();
}

// Customer interface
void Customerinterface()
{
    string option;
    bool check;
    while (true)
    {
        inter = "Customer Interface";
        printmenu(inter);

        cout << "1.  View list of products  " << endl;
        cout << "2.  View Products on sale  " << endl
             << endl;
        cout << "3.  Search for products  " << endl;
        cout << "4.  Add to cart  " << endl;
        cout << "5.  Checkout the bill " << endl
             << endl;
        cout << "6.  Announcements " << endl
             << endl;
        cout << "7.  Log out  " << endl
             << endl;
        cout << "Enter your option : ";
        cin >> option;
        if (option == "1")
        {
            productlist();
        }
        else if (option == "2")
        {
            salelist();
        }
        else if (option == "3")
        {
            Search();
        }
        else if (option == "4")
        {
            Cart();
        }
        else if (option == "5")
        {
            Bill();
        }
        else if (option == "6")
        {
            received();
        }
        else if (option == "7")
        {
            check = logout();
            if (check == true)
            {
                break;
            }
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// customer option 1
void productlist()
{
    inter = "Product details";
    printmenu(inter);
    int index = 0;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << left << setw(20) << "Index" << setw(20) << "Name" << setw(20) << "Price" << setw(20) << "Status" << endl
         << endl;
    for (int idx = 0; idx < ProductsCount; idx++)
    {
        index++;
        SetConsoleTextAttribute(h, 15);
        cout << left << setw(20) << index << setw(20) << product[idx] << setw(20) << price[idx] << setw(20) << productsavailability(idx) << endl;
    }
    cout << endl;
    halt();
}
// customer option 2
void salelist()
{
    inter = "Product On sale";
    printmenu(inter);
    int index = 0;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << left << setw(20) << "Index" << setw(20) << "Name" << setw(20) << "Price" << setw(20) << "Sale" << setw(20) << "Status" << endl
         << endl;
    for (int idx = 0; idx < ProductsCount; idx++)
    {
        if (sale[idx] > 0)
        {
            index++;
            SetConsoleTextAttribute(h, 15);
            cout << left << setw(20) << index << setw(20) << product[idx] << setw(20) << price[idx] << sale[idx] << setw(20) << "%" << productsavailability(idx) << endl;
        }
    }
    cout << endl;
    halt();
}
// customer option 3
void Search()
{
    int counter = 0;
    string name;
    string option;

    while (true)
    {
        inter = "Products Search Panel";
        printmenu(inter);

        cout << "1. Search " << endl;
        cout << "2. Move back " << endl;
        cout << "Select : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Product Search Panel";
            printmenu(inter);

            cout << "Enter name of product : ";
            cin.clear();
            cin.ignore();
            getline(cin, name);

            for (int idx = 0; idx < ProductsCount; idx++)
            {
                if (name == product[idx])
                {
                    inter = "Product Search Panel";
                    printmenu(inter);

                    cout << left << setw(20) << "Index" << setw(20) << "Product" << setw(20) << "Price" << setw(20) << "Sale" << endl
                         << endl;
                    cout << left << setw(20) << idx + 1 << setw(20) << product[idx] << setw(20) << price[idx] << setw(20) << sale[idx] << endl;

                    break;
                }
                counter++;
            }
            if (counter == ProductsCount)
            {
                inter = "Product Search Panel";
                printmenu(inter);
                cout << "Product not found !" << endl
                     << endl;
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
        halt();
    }
}
// customer option 4
void Cart()
{
    string name;
    string option;

    while (true)
    {
        inter = "Your Cart";
        printmenu(inter);

        cout << "1. Add to cart " << endl;
        cout << "2. Remove from cart " << endl;
        cout << "3. Move back " << endl;
        cout << "Select : ";
        cin >> option;

        if (option == "1")
        {
            addcart();
        }
        else if (option == "2")
        {
            removecart();
        }
        else if (option == "3")
        {
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
        halt();
    }
}
// customer option 5
void Bill()
{
    string num;
    while (true)
    {
        inter = "Products Bill";
        printmenu(inter);

        cout << "1. Watch Bill" << endl;
        cout << "2. Buy " << endl;
        cout << "3. Back to main menu" << endl
             << endl;
        cout << "Enter your option : ";
        cin >> num;

        if (num == "1")
        {
            order();
        }
        else if (num == "2")
        {
            if (cart > 0)
            {
                inter = "Products Bill";
                printmenu(inter);
                buy = true;
                cout << "Purchase completed !" << endl;
                cout << "You will shortly received the products !" << endl
                     << endl;
                for (int i = 0; i < cart; i++)
                {
                    if (customername[i] == Loginname)
                    {
                        orderName[orderCount] = customername[i];
                        orderProduct[orderCount] = cartproduct[i];
                        orderPrice[orderCount] = cartprice[i];
                        orderQuant[orderCount] = cartquant[i];
                        orderSale[orderCount] = cartsale[i];
                        storeorderfiledata(orderName[orderCount], orderProduct[orderCount], orderPrice[orderCount], orderQuant[orderCount], orderSale[orderCount]);
                        for (int j = i; j < cart - 1; j++)
                        {
                            customername[j] = customername[j + 1];
                            cartproduct[j] = cartproduct[j + 1];
                            cartprice[j] = cartprice[j + 1];
                            cartquant[j] = cartquant[j + 1];
                            cartsale[j] = cartsale[j + 1];
                        }
                        orderCount++;
                        cart--;
                        updatecartproductsdata();
                    }
                }
                halt();
                break;
            }
            else
            {
                cout << endl;
                cout << "No Products in cart" << endl
                     << endl;
                halt();
            }
        }
        else if (num == "3")
        {
            break;
        }
        else
        {
            cout << "Enter valid number " << endl
                 << endl;
            halt();
        }
    }
}
// order details
void order()
{
    int total = 0, index = 0, discount = 0;
    inter = "Order details";
    printmenu(inter);

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    cout << left << setw(20) << "Index" << setw(20) << "Product" << setw(20) << "Quantity" << setw(20) << "Price" << setw(20) << "Sale" << endl
         << endl;
    for (int idx = 0; idx < cart; idx++)
    {
        if (cartquant[idx] > 0 && customername[idx] == Loginname)
        {
            index++;
            SetConsoleTextAttribute(h, 15);
            cout << left << setw(20) << index << setw(20) << cartproduct[idx] << setw(20) << cartquant[idx] << setw(20) << cartprice[idx] << cartsale[idx] << "%" << endl;

            if (cartsale[idx] > 0)
            {
                discount = ((cartprice[idx] * cartsale[idx]) / 100);
                total = total + (cartquant[idx] * discount);
            }
            else
            {
                total = total + (cartquant[idx] * cartprice[idx]);
            }
        }
    }
    cout << endl;

    SetConsoleTextAttribute(h, 9);
    cout << "Total bill is : " << total << endl
         << endl;
    halt();
}

// customer opt4 (add cart)
void addcart()
{
    int counter = 0;
    int cartquanty = 0;
    string name;
    string option;

    while (true)
    {
        inter = "Add to Cart";
        printmenu(inter);

        cout << "1. Search " << endl;
        cout << "2. Move back " << endl;
        cout << "Select : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Add to Cart";
            printmenu(inter);

            cout << "Enter name of product : ";
            cin.clear();
            cin.ignore();
            getline(cin, name);

            for (int idx = 0; idx < ProductsCount; idx++)
            {
                if (name == product[idx])
                {
                    if (quantity[idx] > 0)
                    {
                        customername[cart] = Loginname;
                        cartproduct[cart] = name;
                        cartprice[cart] = price[idx];
                        cartsale[cart] = sale[idx];

                        while (cartquanty == 0)
                        {
                            inter = "Add to Cart";
                            printmenu(inter);

                            cout << "Enter quantity of product : ";
                            cin >> cartquanty;
                            if (isNum(to_string(cartquanty)) == false)
                            {
                                cout << endl;
                                cout << "Enter Correct Amount" << endl;
                                cartquanty = 0;
                            }
                            else
                            {
                                cartquant[cart] = cartquanty;

                                if (quantity[idx] - cartquant[cart] < 0)
                                {
                                    cout << endl;
                                    cout << "Item quantity is out of range" << endl;
                                    cout << quantity[idx] << " quantity left !" << endl;
                                    cartquanty = 0;
                                    halt();
                                }
                                else
                                {
                                    quantity[idx] = quantity[idx] - cartquant[cart];
                                }
                            }
                        }
                        storecartproductsdata(customername[cart], cartproduct[cart], cartprice[cart], cartquant[cart], cartsale[cart]);
                        cart++;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Product is out of stock !" << endl
                             << endl;
                    }
                    break;
                }
                counter++;
            }
            if (counter == ProductsCount)
            {
                inter = "Add to Cart";
                printmenu(inter);
                cout << "Product not found !" << endl
                     << endl;
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
        halt();
    }
}
// customer opt4 (remove cart)
void removecart()
{
    string productname;
    string option;

    while (true)
    {
        inter = "Remove Products from Cart";
        printmenu(inter);

        cout << "1. Remove" << endl;
        cout << "2. Move back" << endl;
        cout << "Select option : ";
        cin >> option;

        if (option == "1")
        {
            inter = "Remove Products from Cart";
            printmenu(inter);

            cout << "Enter the name of product : ";
            cin.clear();
            cin.sync();
            getline(cin, productname);

            if (cartremoving(productname) == true)
            {
                inter = "Remove Products from Cart";
                printmenu(inter);

                cout << "Product removed !" << endl
                     << endl;
            }
            else
            {
                inter = "Remove Products from Cart";
                printmenu(inter);
                cout << "No product found !" << endl
                     << endl;
            }
        }
        else if (option == "2")
        {
            break;
        }
        else
        {
            cout << " Invalid option" << endl
                 << endl;
        }
        halt();
    }
}
bool cartremoving(string productname)
{
    bool check = false;
    for (int counter = 0; counter < cart; counter++)
    {
        if (productname == product[counter])
        {
            customername[counter] = "";
            cartproduct[counter] = "";
            cartprice[counter] = 0;
            quantity[counter] = quantity[counter] + cartquant[counter];
            cartquant[counter] = 0;
            cartsale[counter] = 0;
            cart--;
            updatecartproductsdata();
            check = true;
            break;
        }
    }
    return check;
}
// customer opt 1 & 2
string productsavailability(int idx)
{
    string data;
    if (quantity[idx] == 0)
    {
        data = "Out Of Stock";
    }
    else
    {
        data = "In Stock";
    }
    return data;
}

// data parsing
string parsedata(string line, int field)
{
    string item;
    int commaCount = 1;
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + line[i];
        }
    }
    return item;
}

// storing admin sign up pin
void storepin()
{
    fstream pinfile; // file name
    pinfile.open("adminpin.csv", ios::app);
    pinfile << pin;
    pinfile.close();
}
// loading admin sign up pin
void loadpin()
{
    fstream pinfile; // file name
    string line;
    pinfile.open("adminpin.csv", ios::in);
    getline(pinfile, line);
    if (line != "")
    {
        pin = line;
    }
    pinfile.close();
}
// updating admin sign up pin
void updatepin()
{
    fstream pinfile; // file name
    pinfile.open("adminpin.csv", ios::out);

    pinfile << pin << endl;

    pinfile.close();
}

// storing customer buying status
void storebuystatus()
{
    fstream buyfile; // file name
    buyfile.open("Buystatus.csv", ios::app);
    buyfile << buy;
    buyfile.close();
}
// loading customer buying status
void loadbuystatus()
{
    fstream buyfile; // file name
    string line;
    buyfile.open("Buystatus.csv", ios::in);
    getline(buyfile, line);
    if (line != "")
    {
        buy = stoi(line);
    }
    buyfile.close();
}
// update buying status
void updatebuystatus()
{
    fstream buyfile; // file name
    buyfile.open("Buystatus.csv", ios::out);

    buyfile << buy << endl;

    buyfile.close();
}

// store login data
void storelogindata(string num, string name, string pass, string cntct)
{
    fstream sign; // file name
    sign.open("UserData.csv", ios::app);
    sign << num << ",";
    sign << name << ",";
    sign << pass << ",";
    sign << cntct << endl;
    sign.close();
}
// load login data
void loadlogindata()
{
    fstream sign; // file name
    string line;
    sign.open("UserData.csv", ios::in);
    while (getline(sign, line))
    {
        if (line != "")
        {
            role[count] = parsedata(line, 1);
            username[count] = parsedata(line, 2);
            password[count] = parsedata(line, 3);
            contact[count] = parsedata(line, 4);
            count++;
        }
    }
    sign.close();
}
// update login data
void updatelogindata()
{
    fstream sign; // file name
    sign.open("UserData.csv", ios::out);
    for (int x = 0; x < count; x++)
    {
        sign << role[x] << ",";
        sign << username[x] << ",";
        sign << password[x] << ",";
        sign << contact[x] << endl;
    }
    sign.close();
}

// store products data
void storeproductdata(string name, int value, int ratio, int salevalue)
{
    fstream Prod; // file name
    Prod.open("ProductsData.csv", ios::app);
    Prod << name << ",";
    Prod << value << ",";
    Prod << ratio << ",";
    Prod << salevalue << endl;
    Prod.close();
}
// load products data
void loadproductsdata()
{
    fstream Prod; // file name
    string line;
    Prod.open("ProductsData.csv", ios::in);
    while (getline(Prod, line))
    {
        if (line != "")
        {
            product[ProductsCount] = parsedata(line, 1);
            price[ProductsCount] = stoi(parsedata(line, 2));
            quantity[ProductsCount] = stoi(parsedata(line, 3));
            originalquantity[ProductsCount] = quantity[ProductsCount];
            sale[ProductsCount] = stoi(parsedata(line, 4));
            ProductsCount++;
        }
    }
    Prod.close();
}
// update products store data
void updateproductsdata()
{
    fstream Prod; // file name
    Prod.open("ProductsData.csv", ios::out);
    for (int x = 0; x < ProductsCount; x++)
    {
        Prod << product[x] << ",";
        Prod << price[x] << ",";
        Prod << quantity[x] << ",";
        Prod << sale[x] << endl;
    }
    Prod.close();
}

// store cart dara
void storecartproductsdata(string custname, string name, int value, int ratio, int salevalue)
{
    fstream CartsData; // file name
    CartsData.open("CartsData.csv", ios::app);
    CartsData << custname << ",";
    CartsData << name << ",";
    CartsData << value << ",";
    CartsData << ratio << ",";
    CartsData << salevalue << endl;
    CartsData.close();
}
// load cart products data
void loadcartproductsdata()
{
    fstream CartsData; // file name
    string line;
    CartsData.open("CartsData.csv", ios::in);
    while (getline(CartsData, line))
    {
        if (line != "")
        {
            customername[cart] = parsedata(line, 1);
            cartproduct[cart] = parsedata(line, 2);
            cartprice[cart] = stoi(parsedata(line, 3));
            cartquant[cart] = stoi(parsedata(line, 4));
            originalquantity[cart] = cartquant[cart];
            cartsale[cart] = stoi(parsedata(line, 5));
            cart++;
        }
    }
    CartsData.close();
}
// update cart product data
void updatecartproductsdata()
{
    fstream CartsData; // file name
    CartsData.open("CartsData.csv", ios::out);
    for (int x = 0; x < cart; x++)
    {
        CartsData << customername[x] << ",";
        CartsData << cartproduct[x] << ",";
        CartsData << cartprice[x] << ",";
        CartsData << cartquant[x] << ",";
        CartsData << cartsale[x] << endl;
    }
    CartsData.close();
}

// store order file data
void storeorderfiledata(string custname, string name, int value, int ratio, int salevalue)
{
    fstream OrdersData; // file name
    OrdersData.open("OrdersData.csv", ios::app);
    OrdersData << custname << ",";
    OrdersData << name << ",";
    OrdersData << value << ",";
    OrdersData << ratio << ",";
    OrdersData << salevalue << endl;
    OrdersData.close();
}
// load order file data
void loadorderfiledata()
{
    fstream OrdersData; // file name
    string line;
    OrdersData.open("OrdersData.csv", ios::in);
    while (getline(OrdersData, line))
    {
        if (line != "")
        {
            orderName[orderCount] = parsedata(line, 1);
            orderProduct[orderCount] = parsedata(line, 2);
            orderPrice[orderCount] = stoi(parsedata(line, 3));
            orderQuant[orderCount] = stoi(parsedata(line, 4));
            orderSale[orderCount] = stoi(parsedata(line, 5));
            orderCount++;
        }
    }
    OrdersData.close();
}
// update order file data
void updateorderfiledata()
{
    fstream OrdersData; // file name
    OrdersData.open("OrdersData.csv", ios::out);
    OrdersData.close();
}

// store announcements
void storeannouncements(string name, string transferdata)
{
    fstream announce; // file name
    announce.open("Announcements.csv", ios::app);
    announce << name << ",";
    announce << transferdata << endl;
    announce.close();
}
// load announcements
void loadannouncements()
{
    fstream announce; // file name
    string line;
    announce.open("Announcements.csv", ios::in);
    while (getline(announce, line))
    {
        if (line != "")
        {
            chatsender[msg] = parsedata(line, 1);
            chat[msg] = parsedata(line, 2);
            msg++;
        }
    }
    announce.close();
}
