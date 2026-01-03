#include "Phonebook.hpp"

int main(){
    Phonebook test;
    std::string input_, val, val_num;

    std::cout << "Hi, welcome to phonebook.\n What would you like to do add, remove or contain.";
    std::cin >> input_;

    while(input_ != "done"){
        if(input_ == "add"){
            std::cout << "What is the contact that you are looking for.\n";
            std::cin >> val;
            test.add(val, val_num);

        }else if(input_ == "remove"){
            std::cout << "What is the contact that you are looking to remove.\n";
            std::cin >> val;
            test.remove(val);

        }else if(input_ == "contain"){
            std::cout << "What is the contact that you are looking for.\n";
            std::cin >> val;
            test.contains(val);

        }else if(input_ == "done"){
            break;
        }else{
            std::cout << "That was not a valid input. Please try again.\n";
        }
    }
    return 1;
}