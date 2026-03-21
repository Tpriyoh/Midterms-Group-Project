/*
Name: Tun Tun (Jonathan) Aung
Course: CSCI 272(1)
Midterms Group Project
03/19/26
*/

#include <limits> // required for cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include "BankAccount.h"
using namespace std;

int main() {
    cout << " === Banking System ===" << endl;

    //Declare necessary variables
    string name;
    cout << "Enter owner name: ";
    getline(cin, name); //For teammembers, should we consider checking this input, like numbers or symbols

    //get account number with validation mechanism
    int accountNumber;
    cout << "Enter accout number: ";
    while (true) { //Will keep in loop until correct or breaks.
        cin >> accountNumber; //have to put in the cin first before doing cin.fail(), otherwise we don't know what we are checking
        if (cin.fail() || accountNumber <= 0) { //either not a number at all, or negative accuont number
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore all space and ready to take more cin
            cout << "Invalid input, Enter account number: ";
        } else {
            //cin.clear(); //so don't clear it, it worked. we clear only if we don't want the input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    double initialDeposit = 0; //initalize first deposit and assumed 0;
    cout << "Enter initial deposit (>0): ";
    while (true) { //doing similar check as accountNumber;
        cin >> initialDeposit;
        if (cin.fail() || initialDeposit <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, Enter initial deposit (>0): ";
        }else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    BankAccount account(name, accountNumber, initialDeposit);
    int choice = 0; //name an int variable to allow menu selection
                    //had to initlize with 0 for our loop logic to work

    while (choice != 6) {
        cout << "Menu: " << endl;
        cout << "1) Deposit" <<endl;
        cout << "2) Withdraw" <<endl;
        cout << "3) Show Balance" << endl;
        cout << "4) Show Account Info" << endl;
        cout << "5) Show Transaction History" << endl;
        cout << "6) Exit" << endl;

        cout << " " << endl;
        cout << "Choose Option: ";
        // } okay so endless loop happened here

        //checking for input for choice
        while (true) {
            cin >> choice;
            if (cin.fail() || choice >6 || choice <= 0) { //if choice is within 1-6 range
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                //break;
                cout << "Invalid input, Choose option (1-6): ";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        double amt; //
        if (choice == 1) { //If user input 1, amount deposit
            cout << "Amount to deposit: ";
            while (true) {
                cin >> amt;
                if (cin.fail()) { //checks for non numbers
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    //break;
                    cout << "Deposit cannot be non-numbers, Enter amount to deposit: ";
                } else if (amt <= 0) { //checks if amount is 0 or less
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    //break;
                    cout << "You entered negative numbers or 0, Enter amount to deposit: ";
                } else { //succeed
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
            account.deposit(amt);
            cout << fixed << setprecision(2) << "Deposited $" << amt << endl;

        } else if (choice == 2) {
            cout << "Amout to withdraw: ";
            while (true) {
                //first attempted to make the deduction, logic was wrong
                cin >> amt;
                if (cin.fail()) { // didn't need to check if withdraw is greater than amt, since BankAccount.h already checks it
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    //break;
                    cout << "Not a number, Enter withdraw amount: ";
                } else if (amt <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    //break;
                    cout << "You entered less than 0, try again: ";
                } else if (bool success = account.withdraw(amt)) { //check if bool success == true;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << fixed << setprecision(2) << "Withdrawed $" << amt << endl;
                    break;
                    } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    //break;
                    cout << "Insufficient balance, Enter amount to withdraw: ";
                }
            }

        } else if (choice == 3){
            cout <<endl;
            cout << fixed << setprecision(2);
            cout << "Your balance is: $" << account.getBalance() << endl;
            
        }    
            else if (choice == 4){
                account.display();

        } 
            else if (choice == 5){
                account.showHistory(); //shows history for the bank account

        }
            else if (choice == 6){
            cout << "Goodbye." << endl; //exits the program, when choosing choice 6
        
        }
    }

}
/*
 *Tun Tun (Jonathan) Aung
 *Challanges:
 *1. Had to figure out how to constantly keep the menu up and going. Stackoverflow, reddit show "switch" or "do"
 *but since it was not covered in class, i had to work with other alternatives. turns out while
 *they have different names, switch, do, while are essentailly the same thing but named abit different
 *perhaps for contextual purpose, very similar to .size() and .length()
 *source: https://stackoverflow.com/questions/64036374/getting-loop-to-redisplay-message-c#:~:text=2%20Answers&text=Your%20code%20is%20displaying%20the,better%20a%20single%20switch%20block.
 *2. Error bound checks are interesting to find from security aspect. Fool proofing is fun.
 *3. Drawing from reflection 2. at line 30, i was initially clearing the input using cin.clear()
 *which turned out to be a problem.
 *4. For choice 1 and 2, instead of making comparison with the balance after user input, I have decided to work with
 *a double instead. The pro of this is that i don't risk repeated error message since our BankAccount.h is checking
 *for balance on its own too. Additionally, it helps with our validation checks as well since I am able to put it in the amt variable as a place holder and do cin.fail() checks
 *instead of a long winded one.
 *5. Because there is a large usage of while loop, there's alot of risk with infinite loop, tracking {} is somewhat challenging
 *6. Logic again, bit of a challenge to track how the program is flowing, i encountered abit of an issue with tracking how pushback is suppose to work
 *in the loops.
 *
 *Miguel Llapa:
 *One of the tricky part for me in the project is how it is different than the one from StackOverFlow without
 *the switch and do statement for the choice menu to keep going constantly in a loop, and also a bit iffy for me
 *until Bilal, who did choice 3 and 4, did the work and understood how its done, and learned that it didn't need to be 
 *complicated and did 5 and 6 with no problem.
 *source: https://stackoverflow.com/questions/64036374/getting-loop-to-redisplay-message-c#:~:text=2%20Answers&text=Your%20code%20is%20displaying%20the,better%20a%20single%20switch%20block.
 *And one of the things I learned from the error note (03/21/26) is in choice 6
 *in the code, there should be a else if statement to run the code instead of else statement. I learned that the while and else if
 *statements can also work in a loop in the menu without the use of "switch" and "do" statements so the menu can keep going
 *to work.
 */
