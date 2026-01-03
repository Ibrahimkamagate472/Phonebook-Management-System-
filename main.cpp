#include "Phonebook.hpp"

int main(){
    Phonebook test;
    std::string input_, val, val_num;

    std::cout << "Hi, welcome to phonebook.\nWhat would you like to do add, remove or contain.\n";
    std::cin >> input_;

    while(input_ != "done"){
        if(input_ == "add"){
            std::cout << "What is the name and number of the contact.\n";
            std::cin >> val >> val_num;
            std::cout << test.add(val, val_num);

        }else if(input_ == "remove"){
            std::cout << "What is the contact that you are looking to remove.\n";
            std::cin >> val;
            std::cout << test.remove(val);

        }else if(input_ == "contain"){
            std::cout << "What is the contact that you are looking for.\n";
            std::cin >> val;
            std::cout << test.contains(val);

        }else if(input_ == "done"){
            break;
        }else{
            std::cout << "That was not a valid input. Please try again.\n";
        }

        std::cout << "\nWhat would you like to do add, remove or contain.\n";
        std::cin >> input_;
    }
    return 1;
}