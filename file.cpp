#include "file.hpp"


/**
 * @brief this function is the default constructor
 * 
 * set the file name 
 * creates a file if one isn't made or found
 */
File::File(): file_name_{"Phonebook.txt"}{
    std::ifstream file_(file_name_);

    if(!file_.is_open()){
        file_.close();

        std::ofstream new_file_ (file_name_);
        new_file_.close();
    }

    file_.close();
}

/**
 * @brief this function reads in local file that contains the
 * contact information at start up
 * 
 * @param reference to a phonebook
 */
void File::readFromFile(Phonebook& phonebook_){
    //opens in read only mode
    std::ifstream file_(file_name_);

    //double check if we was able to open it
    if(!file_.is_open()){
        return;
    }
    //loop through line by line
    std::string line_;
    while(std::getline(file_, line_)){

        //locates the commas since thats how we store the data
        size_t first_comma = line_.find(',');
        size_t second_comma =  line_.find(',', first_comma + 1);

        //double check that we found the commas
        if(first_comma == std::string::npos || second_comma == std::string::npos){
            continue;
        }

        //extract the first and last name and their number
        std::string name_ = line_.substr(0, first_comma);
        std::string name2_ = line_.substr(first_comma + 1, second_comma - first_comma - 1);
        std::string num_ = line_.substr(second_comma + 1);

        //add it to the phonebook vector 
        phonebook_.add(name_, name2_, num_);
    }
    file_.close();
}

/**
 * @brief this function stores the Phonebook to a local file
 * 
 * @param const reference to a phonebook
 */
void File::readToFile(const Phonebook& phonebook_){
    //chose to override the file each time to store
    std::ofstream file_(file_name_);

    //goes through each item in the phonebook
    for(const auto& i : phonebook_.getPhonebook()){
        
        //skip if there is no entry or we lazy deleted
        if(i.first_name_.empty() || i.first_name_ ==  "x"){
            continue;
        }

        //adds it to the file
        file_ << i.first_name_ << "," << i.last_name_ << "," << i.number_ << "\n";
    }
    file_.close();
}