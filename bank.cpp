#include <iostream>
#include <fstream>
#include <vector>

/*
This program is a simulated bank account system with all the necessary functions such as display balance, deposit, withdraw, and exit. Prior to these functions showing, the 
user must create an account with their username and 4-digit pin code. For this example, each created user will have a balance of $1,000.00 in their account. A file will be created
with the owner's information and will be updated/edited with every method chosen by the user.
*/
std::vector<std::pair <std::string, int>> verification;

class User{
    private:
        double wallet = 1000; // Let's give our users some money incase they would like to deposit
        double balance = 0;
        std::string username;
        std::string firstName;
        std::string lastName;
        int pinCode;
        
    public:
        User(std::string _username, int _pinCode, std::string _firstName, std::string _lastName){

            username = _username;
            pinCode = _pinCode;
            firstName = _firstName;
            lastName = _lastName;

            verification.push_back(make_pair(_username, _pinCode));
            std::ofstream myFile;
            myFile.open(_username+".txt");
            
            if(!myFile){
                std::cout << "File not created." << std::endl;
            }
            else{
                myFile << "First name: " << _firstName << std::endl << "Last name: " << _lastName << std::endl << "Username: " << _username << std::endl << "Pin: " << pinCode;
                myFile.close();
            }
            return;
        }

        void withdraw(double withdrawAmt){
            if (withdrawAmt > balance){
                std::cout << "Your balance is too low. Please enter selected amount to withdraw: ";
                std::cin >> withdrawAmt;
                return withdraw(withdrawAmt);
            }
            else{
                balance -= withdrawAmt;
                wallet += withdrawAmt;
                std::cout << "---------------------------------------------------------------------------\n";
                std::cout << "\t\t\t\tRECEIPT\n---------------------------------------------------------------------------\n\t\t\t\tBalance: " << balance << "\n\t\t\t\tWithdraw amount: " <<  withdrawAmt << std::endl;
                std::cout << "---------------------------------------------------------------------------\n";
            }
            return;
        }

        void deposit(double depositAmt){
            if (depositAmt > wallet){
                std::cout << "You do not have that much money to deposit. Please enter the selected amount to deposit: ";
                std::cin >> depositAmt;
                return deposit(depositAmt);
            }
            else{
                balance += depositAmt;
                wallet -= depositAmt;
                std::cout << "---------------------------------------------------------------------------\n";
                std::cout << "\t\t\t\tRECEIPT\n---------------------------------------------------------------------------\n\t\t\t\tBalance: " << balance << "\n\t\t\t\tDeposit amount: " <<  depositAmt << std::endl;
                std::cout << "---------------------------------------------------------------------------\n";
            }
            return;
        }

        void showBalance(){
            std::cout << "User balance: " << balance << std::endl;
            return;
        }
};

std::vector<User> database;

void interface(int id){
    
    int choice;
    double depositAmt, withdrawalAmt;
    int flag = 0;

    std::cout << "\n1. Deposit\n2. Withdraw\n3. Show Balance\n4. Logout\n";
    std::cin >> choice;

    while (choice < 1 || choice > 4){
        std::cout << "Invalid entry. Please select your choice: " << std::endl;
        std::cout << "1. Deposit\n2. Withdraw\n3. Show Balance\n4. Logout\n";
        std::cin >> choice;
    }
    
while(flag == 0){
    switch(choice){ 
        case 1: // Deposit
            std::cout << "How much would you like to deposit?\n";
            std::cin >> depositAmt;
            database[id].deposit(depositAmt);
            std::cout << "\n1. Deposit\n2. Withdraw\n3. Show Balance\n4. Logout\n";
            std::cin >> choice;                     
            break;
        case 2: // Withdraw
            std::cout << "How much would you like to withdraw?\n";
            std::cin >> withdrawalAmt;
            database[id].withdraw(withdrawalAmt);
            std::cout << "\n1. Deposit\n2. Withdraw\n3. Show Balance\n4. Logout\n";
            std::cin >> choice;         
            break;
        case 3: // Show Balance
            database[id].showBalance();
            std::cout << "\n1. Deposit\n2. Withdraw\n3. Show Balance\n4. Logout\n";
            std::cin >> choice;            
            break;
        case 4: // Exit and go to prompt
            flag = 1;
            break;
    }
}
    return;
}

std::pair<bool, int> login(){
    std::string user;
    int pin;

    std::pair<bool,int> my_pair;

        std::cout << "Please enter your crendentials: \n";
        std::cout << "User: ";
        std::cin >> user;
        std::cout << "Pin: ";
        std::cin >> pin;
    
    for(int i = 0; i < verification.size(); i++){
        if(user == verification[i].first && pin == verification[i].second){
            std::cout << "Login successful\n";
            my_pair.first = true;
            my_pair.second = i;
            return my_pair;
        }
    }
        std::cout << "Login unsuccessful\n";
            my_pair.first = false;
            return my_pair;
}

void createUser(){
        
        std::string firstName, lastName, username;
        int pinCode;

        std::cout << "\nEnter your first name: \n";
        std::cin >> firstName;
        
        std::cout << "\nEnter your last name: \n";
        std::cin >> lastName;
            
        std::cout << "\nEnter a username: \n";
        std::cin >> username;

        std::cout << "\nEnter a pincode: \n";
        std::cin >> pinCode;

        User person(username, pinCode, firstName, lastName); // Pass by address so we don't have to make a copy
        database.push_back(person);
        std::cout << "\nRegistration Complete!\n";    

        return;
}

int prompt(){
    int ch, flag = 0;
    std::pair<bool,int> validate;

    std::cout << "Welcome to the Bank of Lawnie. Please select your choice: " << std::endl;
    std::cout << "1. Register\n2. Login\n3. Exit\n";
    std::cin >> ch;

    while (ch < 1 || ch > 3){
        std::cout << "Invalid entry. Please select your choice: " << std::endl;
        std::cout << "1. Register\n2. Login\n3. Exit\n";
        std::cin >> ch;
    }

    switch(ch){
        case 1: // Register
            createUser();
            break;
        case 2: // Login
            validate = login();
            if(validate.first == true){
                interface(validate.second);
            }
            else{
                std::cout << "Incorrect username or password.\n";
                break;
            }
        case 3: // Exit
            std::cout << "Goodbye!";
            flag = 1;
            break;
    }
    return flag;
}

int main(){

    int flag = 0;

    while (flag == 0){
        flag = prompt();
    }

    return 0;
}
