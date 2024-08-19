//  This program is used as a binary number calculator. This calculator has three functionalities: converting a binary string into integers, converting integers into binary, as well
//  as add two binary numbers together. T

//  Kylie Heiland
//  8/28/22
//  Note: I understand that I was to not adjust any other functions, but I noticed an issue in Menu 2, regarding when x = 0. As I learned in the textbook, 0 is considered positive,
//  but the if-else statement called it negative. Thus, I removed the = sign from the if statement so that 0 could be converted to binary. This also allowed test_decimal_to_binary
// to test true!

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

using namespace std;

int binary_to_decimal(string s);
// precondition: s is a string that consists of only 0s and 1s
// postcondition: the positive decimal integer that is represented by s

string decimal_to_binary(int n);
// precondition: n is a positive integer
// postcondition: nâ€™s binary representation is returned as a string of 0s and 1s

string add_binaries(string b1, string b2);
// precondition: b1 and b2 are strings that consists of 0s and 1s, i.e.
//               b1 and b2 are binary representations of two positive integers
// postcondition: the sum of b1 and b2 is returned. For instance,
//  if b1 = â€œ11â€, b2 = â€œ01â€, then the return value is â€œ100â€

void menu();
// display the menu. Student shall not modify this function

int grade();
// returns an integer that represents the studentâ€™s grade of this projects.
// Student shall NOT modify

bool is_binary(string b);
// returns true if the given string s consists of only 0s and 1s; false otherwise

bool test_binary_to_decimal();
// returns true if the studentâ€™s implementation of binary_to_decimal function
// is correct; false otherwise. Student shall not modify this function

bool test_decimal_to_binary();
//  returns true if the studentâ€™s implementation of decimal_to_binary function is correct; false otherwise. Student shall not modify this function

bool test_add_binaries();
// which returns true if the studentâ€™s implementation of add_binaries function
// is correct; false otherwise. Student shall not modify this function


int main()
{
    int choice;
    string b1, b2;
    int x, score;
    do{
        // display menu
        menu();
        cout << "Enter you choice: ";
        cin >> choice;
        // based on choice to perform tasks
        switch(choice){
            case 1:
                cout << "Enter a binary string: ";
                cin >> b1;
                if(!is_binary(b1))
                    cout << "It is not a binary number\n";
                else
                    cout << "Its decimal value is: " << binary_to_decimal(b1) << endl;
                break;
                
            case 2:
                cout << "Enter a positive integer: ";
                cin >> x;
                if(x < 0) //This was changed from x <= 0 because 0 is considered to be a positive integer. See note at the top of file for more information.
                    cout << "It is not a positive integer" << endl;
                else
                    cout << "Its binary representation is: " << decimal_to_binary(x) << endl;
                break;
                
            case 3:
                cout << "Enter two binary numbers, separated by white space: ";
                cin >> b1 >> b2;
                if(!is_binary(b1) || !is_binary(b2))
                    cout << "At least one number is not a binary" << endl;
                else
                    cout << "The sum is: " << add_binaries(b1, b2) << endl;
                break;
                
            case 4:
                score = grade();
                cout << "If you turn in your project on blackboard now, you will get " << score << " out of 10" << endl;
                cout << "Your instructor will decide if one-two more points will be added or not based on your program style, such as good commnets (1 points) and good efficiency (1 point)" << endl;
                break;
                
            case 5:
                cout << "Thanks for using binary calculator program. Good-bye" << endl;
                break;
            default:
                cout << "Wrong choice. Please choose 1-5 from menu" << endl;
                break;
        }
        
    }while(choice != 5);
    return 0;
}

//This function converts a binary number to a decimal number.
int binary_to_decimal(string s){
    
    int powerResult = 1; //powerResult starts at 2^7 and will decrease to 2^6, 2^5, ..., 2^0.

    int decimal = 0; //Decimal is intialized to zero and will (hopefully) be adjusted if the binary number contains any 1s.
    
    int size = s.length();

    int a = s.length() - 1;
 
   if(size == 1){ //If there is only 1 bit.
        if(s.at(a) == '1') //If the bit it 0, 
            return 1;
    } 
    else{
        for(int i = s.length() - 1; i >= 0 && powerResult <= 128; i--){ //Loops through each character of the string, starting at the char farthest to the right. 
            if(s.at(i) == '1'){ //If that specific spot on the binary number has a 1, then decimal is updated.
                decimal += powerResult;
            }
            powerResult *= 2; //Power result is doubled for the next 2^n.
        }
    }
    return decimal; //Every time a 1 was found at a specific char location in the string, the power result (which began with 1, but was doubled each loop iteration)
                    //of that specific character location was added to decimal. Once all of the characters were gone through, then the binary number was officially converted into
                    //decimal and that result was outputted. If there was only 1 bit and it did not equal to 1, then decimal (0) was returned. 
}

string decimal_to_binary(int n){
    int power = 0; //2^0

    bool firstLoop = true;

    string s; //Empty string which will eventually have a binary number within it.

    if(n == 0){    
        s = "0";
        return s;
    }
   
    while(n >= pow(2, power)){ //Finds the power that is higher than n
        power++;
    }
    power -= 1; //Lowers power so that it is on the highest power that still remains to be lower than n.
   
   //If the only element is 0, then just return that value as a string!
   
    for(int i = pow(2, power); i >= 1; i = i / 2){ //Begins looping at the highest possible power for the decimal number. 
        if(firstLoop == true){
            if(n >= i){
                n -= i;
                s = "1";
            }
            else
                s = "0";
                firstLoop = false;
        }
        else if(n >= i){
            n -= i;
            s = s + '1';
        }
        else
            s = s + '0';        
    }
    return s; 
}

string add_binaries(string b1, string b2){
    int b1Decimal = binary_to_decimal(b1); //b1's binary digits are converted to decimal.

    int b2Decimal = binary_to_decimal(b2); //b2's binary digits are converted to decimal.

    int sum = b1Decimal + b2Decimal;

    string decToBi = decimal_to_binary(sum);

    return decToBi;
}

void menu()
{
    cout << "******************************\n";
    cout << "*          Menu              *\n";
    cout << "* 1. Binary to Decimal       *\n";
    cout << "* 2. Decinal to Binary       *\n";
    cout << "* 3. Add two Binaries        *\n";
    cout << "* 4. Grade                   *\n";
    cout << "* 5. Quit                    *\n";
    cout << "******************************\n";
}

int grade(){
    int result = 0;
    // binary_to_decimal function worth 3 points
    if(test_binary_to_decimal()){
        cout << "binary_to_decimal function pass the test" << endl;
        result += 3;
    }
    else
        cout << "binary_to_decimal function failed" << endl;
    
    // decinal_to_binary function worth 2 points
    if(test_decimal_to_binary()){
        cout << "decimal_to_binary function pass the test" << endl;
        result += 2;
    }
    else
        cout << "decimal_to_binary function failed" << endl;
    // add_binaries function worth 3 points
    if(test_add_binaries()){
        cout << "add_binaries function pass the test" << endl;
        result += 3;
    }
    else
        cout << "add_binaries function pass failed" << endl;
    return result;
}

bool is_binary(string s){
    for(int i = 0; i < s.length(); i++)
        if(s[i] != '0' && s[i] != '1') // one element in s is not '0' or '1'
            return false;  // then it is not a binary nunber representation
    return true;
}

bool test_binary_to_decimal(){
    if(binary_to_decimal("0") != 0 || binary_to_decimal("1") != 1)
        return false;
    if(binary_to_decimal("010") != 2 || binary_to_decimal("10") != 2)
        return false;
    if(binary_to_decimal("01101") != 13 || binary_to_decimal("1101") != 13)
        return false;
    return true;
}

bool test_decimal_to_binary(){
    if(decimal_to_binary(0) != "0" || decimal_to_binary(1) != "1")
        return false;
    if(decimal_to_binary(2) != "10" || decimal_to_binary(13) != "1101")
        return false;
    return true;
}

bool test_add_binaries(){
    if(add_binaries("0", "0") != "0") return false;
    if(add_binaries("0", "110101") != "110101") return false;
    if(add_binaries("1", "110111") != "111000") return false;
    if(add_binaries("101", "111011") != "1000000") return false;
    return true;
}

/* OUTPUT
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 1
Enter a binary string: 01001011
Its decimal value is: 75
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 1
Enter a binary string: 01111001
Its decimal value is: 121
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 1
Enter a binary string: 00100000
Its decimal value is: 32
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 2
Enter a positive integer: 105
Its binary representation is: 1101001
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 2
Enter a positive integer: 115
Its binary representation is: 1110011
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 2
Enter a positive integer: 32
Its binary representation is: 100000
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 3
Enter two binary numbers, separated by white space: 100000 1001011
The sum is: 1101011
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 3
Enter two binary numbers, separated by white space: 01111001 1101001
The sum is: 11100010
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 3
Enter two binary numbers, separated by white space: 001000000 1101001
The sum is: 10101001
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 4
binary_to_decimal function pass the test
decimal_to_binary function pass the test
add_binaries function pass the test
If you turn in your project on blackboard now, you will get 8 out of 10
Your instructor will decide if one-two more points will be added or not based on your program style, such as good commnets (1 points) and good efficiency (1 point)
******************************
*          Menu              *
* 1. Binary to Decimal       *
* 2. Decinal to Binary       *
* 3. Add two Binaries        *
* 4. Grade                   *
* 5. Quit                    *
******************************
Enter you choice: 5
Thanks for using binary calculator program. Good-bye
*/
