/* 
Name: Tanzin Priyoh
Course: CSCI 272(1)
Midterms Group Project
03/17/26
*/


#include <iostream> 
#include <vector>
#include <iomanip>
#include <string>
#include <sstream> //need this for stringstream after learning about it here. 
//https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
using namespace std;

class BankAccount {
private:
    string ownerName; //account holders name 
    int accountNumber; // account number
    double balance; // active balance
    vector<string> history; // all users transaction history will appear here.
    
    
    
public:
    //paramaterized constructor
    BankAccount(const string& n, int an, double b ){ 
     ownerName = n;
     accountNumber = an;
     balance = b;
     
     
     //source for stringstream number rounding
     //https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
     //used this to round up all string numbers to the second decimal place. will note the site only for the following refrences.
     //rnd short for round.
     stringstream rnd;
     rnd << fixed << setprecision(2) << b;
     
     //using + to_string() multiple times throughout the code to convert numbers into string to use for history X.
    // 3/20/26 replaced all to_string() with rnd.str()); because this actually rounds up string numbers to the second decimal place.
     //since the vector is a string type.
    //stringstream rnd makes a temp format box to hold numbers as text.
    // rnd.str() pulls the formatted text out to save it to the history list.
     history.push_back("Account created with an initial deposit of: $" + rnd.str());
    
    }
    
    
    
    void deposit(double amt) {
        // if amt is greater then 0 for the deposit this will trigger.
        if(amt > 0) {
            balance += amt;
          
          //source //https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified *see note above  
            stringstream rnd;
            rnd << fixed << setprecision(2) << amt;
            history.push_back("Deposited: $" + rnd.str());
        }
        //otherwise this will post saying your amount is invalid. wont show in history
        else {
            cout << "Invalid Deposit Amount." << endl;
        }
    }
    
    
    
    bool withdraw(double amt) {
        //if we're using bool here I made a chain of if, else if and else statements to ensure theres no odd cases of user entry creating issues.
        //if amount is less then or = 0 this will trigger and wont show up in transaction history. 
        if(amt <= 0) {
            cout << "Invalid amount entered." << endl;
            return false;
        }
        
        //if the amt is higher then current bal this will trigger. wont show up in history.
        else if (amt > balance) {
            cout << "insufficient funds." << endl;
            return false;
        }
        
        //if the first 2 fail this will trigger taking your requested amt out of bal and adding that to the history. 
        else {
            balance -= amt;
            
            
            //source //https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified *see note above  
            stringstream rnd;
            rnd << fixed << setprecision(2) << amt;
            history.push_back("Withdrawn: $" + rnd.str());
            
            //and if balance is 0 this message will alert the user of that.
            if(balance == 0) {
                cout << "Balance is now zero" << endl;
            }
            return true;
        }
    }
    
    
    // a simple way to show balance.
    double getBalance() const {
        return balance;
    }
    
    
    
    void display() const {
        //setting up setprecision 2 to make number output look nice, along with displaying info like the name,acct num, bal.
        cout << fixed << setprecision(2) << 
        "Account Owner: " << ownerName << endl <<
        "Account Number: " << accountNumber << endl 
        << "Balance: " << balance << endl;
    }
    
    
    
    void showHistory() const {
        //if 0 entries this will trigger
        if(history.size() == 0) {
            cout << "No Transactions Avaliable." << endl;
        }
        
        //if above fails this will trigger looping transaction history using history.size as a stopgap.
        else {
            cout << "Transaction History" << endl;
            
            //used auto i(0) at first but that caused an unexpected behavior due to auto i(0) being treated as an int 
            // while history.size() is looked at as size_t that conflicting data type may have made other bugs. switched it to size_t i(0)
            //unsolved issue- when converting double to string fixed << setprecision(2) no longer works so the output will look like 100.000000000 in Transaction History.
            //fixed issue above using stackoverflow guide
            for(size_t i(0); i < history.size(); ++i) {
                cout << history[i] << endl;
            }
        }
    }
};

/*
Tanzin Priyoh:

One of the difficult parts of making this .h file was figuring out how to add a transaction history through a vector. 
at first I only used push_back() as a placeholder forgetting to add the users entered amount. 
This gave me another problem seeing how im using a string type vector with an int or double number. I then looked online 
at https://www.geeksforgeeks.org/cpp/stdto_string-in-cpp/
to find the to_string function which made it easier to convert numbers to strings allowing it to be stored in that vector<string> type.
//note: 3/20/26 using to_string will remove setprecision and make the output look like 100.00000000 in the history section.
//I ended up using stackoverflow to find a solution that would let me round up string numbers which lead me to use stringstream.
Another issue I made for myself is for void deposit, and withdrawl I had different paramaterized parameter 
names like wthdraw or depo which confused me when i tried to make the if else statements because I kept 
mixing up what var names belonged to which functions. as a result i just changed all of them to amt which not only 
gave me consistancy but implementing the logic became easier.
Through this project I've learned that naming types really matter and that understanding how data type conversion works 
will save you from a big error handling issue later.

*/
