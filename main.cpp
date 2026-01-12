#include "Phonebook.hpp"
#include "file.hpp"

int main(){
    Phonebook company_phonebook_;
    File company_file_;
    std::string input_, first_name_, last_name_, num_, updated_last_name_, updated_num_;

    //load up contacts from file
    company_file_.readFromFile(company_phonebook_);

    std::cout << "Hi, welcome to company phonebook.\n";
    std::cout << "What would you like to do search, add, remove, update last name, update number, or done to do noting.\n";
    std::getline(std::cin, input_);

    while(input_ != "done"){
        //gets persons phone number
        if(input_ == "search"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);

            std::cout << company_phonebook_.getNumber(first_name_, last_name_);
        }
        //adds a new person
        else if(input_ == "add"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);
            std::cout << "Phone number: ";
            std::getline(std::cin, num_);
            std::cout << company_phonebook_.add(first_name_, last_name_, num_);

            //test
            std::cout << "\nsize: "<< company_phonebook_.getSize()
            << " capacity: " << company_phonebook_.getCapacity()
            << " Load factor: " << company_phonebook_.getLoadFactor();

        }
        //removes a person
        else if(input_ == "remove"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);

            std::cout << company_phonebook_.remove(first_name_, last_name_);


            //test
            std::cout << "\nsize: "<< company_phonebook_.getSize()
            << " capacity: " << company_phonebook_.getCapacity()
            << " Load factor: " << company_phonebook_.getLoadFactor();

        }
        //updates last name
        else if(input_ == "update last name"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);
            std::cout << "New last name: ";
            std::getline(std::cin, updated_last_name_);

            std::cout << company_phonebook_.changeContactLastName(first_name_, last_name_, updated_last_name_);

        }else if(input_ == "update number"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);
            std::cout << "New Phone number: ";
            std::getline(std::cin, updated_num_);

            std::cout << company_phonebook_.changeContactNumber(first_name_, last_name_, updated_num_);

        }else if(input_ == "done"){
            break;

        }else{
            std::cout << "That was not a valid input. Please try again.";
        }

        std::cout << "\nWhat would you like to do search, add, remove, update last name, update number, or done to do noting.\n";
        std::getline(std::cin, input_);
    }

    company_file_.readToFile(company_phonebook_);
    
    return 1;
}