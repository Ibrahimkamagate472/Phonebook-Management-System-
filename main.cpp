#include "Phonebook.hpp"
#include "file.hpp"

int main(){
    Phonebook company_phonebook_;
    File company_file_;
    std::string input_, first_name_, last_name_, num_, updated_last_name_, new_num_;

    //load up contacts from file
    company_file_.readFromFile(company_phonebook_);

    std::cout << "Hi, welcome to company phonebook.\n";
    std::cout << "What would you like to do search, add, remove, update last name, and update number.\n";
    std::getline(std::cin, input_);

    while(input_ != "done"){
        //gets persons phone number
        if(input_ == "search"){
            std::cout << "What is the person you are looking for: ";
            std::cin >> first_name_ >> last_name_;
            std::cout << company_phonebook_.getNumber(first_name_, last_name_);
        }
        //adds a new person
        else if(input_ == "add"){
            std::cout << "What is the first and last name, then the number: ";
            std::cin >> first_name_ >> last_name_ >> num_;
            std::cout << company_phonebook_.add(first_name_, last_name_, num_);

            //test
            std::cout << "\nsize: "<< company_phonebook_.getSize()
            << " capacity: " << company_phonebook_.getCapacity()
            << " Load factor: " << company_phonebook_.getLoadFactor();

        }
        //removes a person
        else if(input_ == "remove"){
            std::cout << "What is the first and last name of the person that you want to remove: ";
            std::cin >> first_name_ >> last_name_;
            std::cout << company_phonebook_.remove(first_name_, last_name_);


            //test
            std::cout << "\nsize: "<< company_phonebook_.getSize()
            << " capacity: " << company_phonebook_.getCapacity()
            << " Load factor: " << company_phonebook_.getLoadFactor();

        }
        //updates last name
        else if(input_ == "update last name"){
            std::cout << "What is the name of the person: ";
            std::cin >> first_name_ >> last_name_;
            std::cout << "\nWhat is the updated last name: ";
            std::cin >> updated_last_name_;
            std::cout << company_phonebook_.changeContactLastName(first_name_, last_name_, updated_last_name_);

        }else if(input_ == "update number"){
            std::cout << "What is the name of the person number you want to update: ";
            std::cin >> first_name_ >> last_name_;
            std::cout << company_phonebook_.changeContactNumber(first_name_, last_name_, new_num_);

        }else if(input_ == "done"){
            break;

        }else{
            std::cout << "That was not a valid input. Please try again.";
        }

        std::cout << "\nWhat would you like to do search, add, remove, update last name, and update number.dfg\n";
        std::getline(std::cin, input_);
    }

    company_file_.readToFile(company_phonebook_);
    
    return 1;
}