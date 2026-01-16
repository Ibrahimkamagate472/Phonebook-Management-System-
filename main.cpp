#include "Phonebook.hpp"
#include "file.hpp"


std::string normalizeName(std::string& name_){
    if (name_.empty()){ 
        return "";
    }

    // lowercase the whole name
    for (char& c : name_) {
        c = std::tolower(static_cast<unsigned char>(c));
    }

    // uppercase first char
    name_[0] = std::toupper(static_cast<unsigned char>(name_[0]));

    return name_;
}

int main(){
    Phonebook company_phonebook_;
    File company_file_;
    std::string input_, first_name_, last_name_, num_, updated_last_name_, updated_num_;

    //load up contacts from file
    company_file_.readFromFile(company_phonebook_);

    std::cout << "Hi, welcome to Phonebook Mangement System.\n";
    std::cout << "What would you like to do search, add, remove, update last name, update number, or done to do noting.\n";
    std::getline(std::cin, input_);

    input_ = normalizeName(input_);

    while(input_ != "Done"){
        //gets persons phone number
        if(input_ == "Search"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);

            //lower case everything beside the first char
            first_name_= normalizeName(first_name_);
            last_name_ = normalizeName(last_name_);
            
            std::cout << company_phonebook_.getNumber(first_name_, last_name_);
        }
        //adds a new person
        else if(input_ == "Add"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);
            std::cout << "Phone number: ";
            std::getline(std::cin, num_);

            //lower case everything beside the first char
            first_name_= normalizeName(first_name_);
            last_name_ = normalizeName(last_name_);

            if(company_phonebook_.add(first_name_, last_name_, num_)){
                std::cout << "You have successfully added: " << first_name_ << " " << last_name_;
            }else{
                std::cout << "Was unsuccessful to add: " << first_name_ << " " << last_name_<< ".";
            }

        }
        //removes a person
        else if(input_ == "Remove"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);

            //lower case everything beside the first char
            first_name_= normalizeName(first_name_);
            last_name_ = normalizeName(last_name_);

            if(company_phonebook_.remove(first_name_, last_name_)){
                std::cout << "You have successfully removed: " << first_name_ << " " << last_name_;
            }else{
                std::cout << "Was unsuccessful to remove: " << first_name_ << " " << last_name_<< ".";
            }

        }
        //updates last name
        else if(input_ == "Update last name"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Old last name: ";
            std::getline(std::cin, last_name_);
            std::cout << "New last name: ";
            std::getline(std::cin, updated_last_name_);

            //lower case everything beside the first char
            first_name_= normalizeName(first_name_);
            last_name_ = normalizeName(last_name_);
            updated_last_name_ = normalizeName(updated_last_name_);

            if(company_phonebook_.changeContactLastName(first_name_, last_name_, updated_last_name_)){
                std::cout << "You have successfully updated: " << first_name_ << " " << last_name_;
            }else{
                std::cout << "Was unsuccessful to update: " << first_name_ << " " << last_name_<< ".";
            }

        }else if(input_ == "Update number"){
            std::cout << "First name: ";
            std::getline(std::cin, first_name_);
            std::cout << "Last name: ";
            std::getline(std::cin, last_name_);
            std::cout << "New Phone number: ";
            std::getline(std::cin, updated_num_);

            first_name_= normalizeName(first_name_);
            last_name_ = normalizeName(last_name_);

            if(company_phonebook_.changeContactNumber(first_name_, last_name_, updated_num_)){
                std::cout << "You have successfully updated the number of: " << first_name_ << " " << last_name_;
            }else{
                std::cout << "Was unsuccessful to update the number of: " << first_name_ << " " << last_name_<< ".";
            }

        }else if(input_ == "done"){
            break;

        }else{
            std::cout << "That was not a valid input. Please try again.";
        }

        std::cout << "\nWould you like to do anything else? Please enter in a option search, add, remove, update last name, update number, or done to do noting.\n";
        std::getline(std::cin, input_);
        input_ = normalizeName(input_);
    }
    std::cout << "Have a good day!";

    company_file_.readToFile(company_phonebook_);
    
    return 1;
}
