#include "Phonebook.hpp"

int main(){
    Phonebook test;
    std::string input_, name, num, new_name, new_number;

    std::cout << "Hi, welcome to phonebook.\nWhat would you like to do add, remove, update name, update number or contain.\n";
    std::getline(std::cin, input_);

    while(input_ != "done"){
        if(input_ == "add"){
            std::cout << "What is the name and number of the contact.\n";
            std::cin >> name >> num;
            std::cout << test.add(name, num);

        }else if(input_ == "remove"){
            std::cout << "What is the contact that you are looking to remove.\n";
            std::cin >> name;
            std::cout << test.remove(name);

        }else if(input_ == "contain"){
            std::cout << "What is the contact that you are looking for.\n";
            std::cin >> name;
            std::cout << test.contains(name);

        }else if(input_ == "update name"){
            std::cout << "What is the contact that you are looking for.\n";
            std::cin >> name;
            std::cout << test.changeContactName(name, new_name);

        }else if(input_ == "update number"){
            std::cout << "What is the contact that you are looking for.\n";
            std::cin >> name;
            std::cout << test.changeContactNumber(name, new_number);

        }else if(input_ == "done"){
            break;

        }else{
            std::cout << "That was not a valid input. Please try again.\n";
        }

        std::cout << "What would you like to do add, remove, update name, update number or contain.\n";
        std::getline(std::cin, input_);
    }
    return 1;
}