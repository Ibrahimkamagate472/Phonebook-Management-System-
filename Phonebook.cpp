#include "Phonebook.hpp"


/**
 * @brief This is the default constructor
 * Sets the size of the hash table
 * 
 * Default capacity_ to 5  
 * Default R to 3
 */
Phonebook::Phonebook(): capacity_(5), R(3), phonebook_(capacity_), size_(0), load_factor_(0){}


/**
 * @brief 
 * 
 * @return an int to where to insert the contact
 */
int Phonebook::hash(const std::string& contact_name_, std::vector<entry>& table_){
    int h = hashHelper(contact_name_.substr(0,3));
    size_t hash1 = h % capacity_;
    size_t hash2 = R - (h % R);
    int j = 0;

    //keep going until we find a spot then we break
    while(j < capacity_){
        //double hash function
        size_t total_hash_ = (hash1 + j * hash2) % capacity_;

        //checks if there is anything there
        if(table_[total_hash_].name_ == "" && table_[total_hash_].number_ == ""){
            size_++;
            load_factor_ = size_ / capacity_;
            return total_hash_;
        }
        j++;
    }    
    return -1;
}

/**
 * @brief This function is the helper function for rehash
 * retruns the hash value so we can double hash
 * 
 * @param const reference to string of the item to be hashed
 * 
 * @return an int to the hash value of the string
 */
int Phonebook::hashHelper(const std::string& contact_name_){
    int hash_val_ = 0;

    for(char ch : contact_name_)
        hash_val_ = 37 * hash_val_ + ch;
    return hash_val_;
}

/**
 * @brief This function rehashes when the load factor is too high
 * 
 */
void Phonebook::rehash(){
    //makes the new hash table that is at least double the previous size
    std::vector<entry> new_table_(findNextPrime(capacity_)); 

    //loops throguh each item in the old phonebook and runs the hash fuction on it
    for(const auto& i : phonebook_){
        size_t location_ = hash(i.name_, new_table_);

        //check to see if location is valid
        if(location_ >= 0){
            new_table_[location_].name_ = i.name_;
            new_table_[location_].number_ = i.number_;
        }
    }
    //reasgin the table
    phonebook_ = std::move(new_table_);
}

int Phonebook::findNextPrime(size_t& new_capacity_){
    //double the size of the old capacity and try to find the new prime
    new_capacity_ = (new_capacity_ * 2) + 1; 

    //if the new capacity isn't a prime number then we run a isPrime to look for one
    while(!isPrime(new_capacity_)){
        new_capacity_ += 2;
    }

    //time to update R for whenever we are adding to the new table
    R = new_capacity_;
    while(!isPrime(R)){
        R -= 2;
    }
    return new_capacity_;
}

bool Phonebook::isPrime(size_t& new_capacity_){
    for (size_t i = 3; i * i <= new_capacity_; i += 2){
        if (new_capacity_ % i == 0){
            return false;
        }
    }
    return true;
}

/**
 * @brief This function adds a contact
 * 
 * @param const reference of the string to the name of the contact that we have to add
 * @param const reference to an int for the number of the contact that we have to add
 * 
 * @return true or false if we added the contact or not
 */
bool Phonebook::add(const std::string& contact_name_, const std::string& num_){
    //triggers rehashing
    if(load_factor_ > .6){
        rehash();
    }
    size_t location_ = hash(contact_name_, phonebook_);

    //check if it is a valid location
    if(location_ >= 0){
        phonebook_[location_].name_ = contact_name_;
        phonebook_[location_].number_ = num_;
        return true;
    }
    return false;
}

/**
 * @brief This function removes a contact using lazy deletion
 * 
 * @param const reference to a string of the name of the contact that we have to remove
 * 
 * @return true or false if we remove the contact or not
 */
bool Phonebook::remove(const std::string& contact_name_){
    int j = 0;

    int h = hashHelper(contact_name_.substr(0,3));
    size_t hash1 = h % capacity_;
    size_t hash2 = R - (h % R);

    //keep going until we find the contact to remove 
    while(j < capacity_){
        //double hash function
        size_t total_hash_ = (hash1 + j * hash2) % capacity_;

        //checks if there is anything there
        if(phonebook_[total_hash_].name_ == ""){
            phonebook_[total_hash_].name_ = "x";
            size_--;
            load_factor_ = size_ / capacity_;
            return true;
        }
        j++;
    }
    return false;
}

/**
 * @brief This function checks to see if a contain is saved 
 * 
 * @param const reference of a string to the name of the contact that we have to look for
 * 
 * @return true or false if we found the contact or not
 */
bool Phonebook::contains(const std::string& contact_name_){
    int j = 0;    
    int h = hashHelper(contact_name_.substr(0,3));
    size_t hash1 = h % capacity_;
    size_t hash2 = R - (h % R);

    //keep going until we find it
    while(j < capacity_){
        //double hash function
        size_t total_hash_ = (hash1 + j * hash2) % capacity_;

        //checks if there is anything there
        if(phonebook_[total_hash_].name_ == contact_name_){
            return true;
        }
        j++;
    }
    return false;
}