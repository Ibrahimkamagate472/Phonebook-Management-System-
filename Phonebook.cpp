#include "Phonebook.hpp"
#include <cctype>

/**
 * @brief this is the default constructor
 * 
 * default R to 3
 * default capacity_ to 5  
 * default size_ to 0
 * default load_factor_ to 0
 * default lazy_deletion_size_ to 0
 * 
 */
Phonebook::Phonebook(): R(3), capacity_(5), size_(0), load_factor_(0), lazy_deletion_size_(0), phonebook_(capacity_){}

/** BASIC OPERATIONS **/

/**
 * @brief this function adds a contact.
* 
* @param const reference to a string containing the first name
* @param const reference to a string containing the last name
* @param const reference to a string containing the number
* 
* @return true or false if we added the contact
*/
bool Phonebook::add(const std::string& first_name_, const std::string& last_name_,const std::string& num_){
    //calls the hash functions and save the insert location
    size_t location_ = hash(first_name_, phonebook_);

    //check if it is a valid location and insert
    if(insert(location_, first_name_,last_name_, num_, phonebook_)){
        size_++;
        load_factor_ = size_ / capacity_;
        //if able to add, double check that the load factor isn't too high
        if(load_factor_ >= .6){
            rehashUp();
        }
        return true;
    }

    //if the contact was unable to be added 
    return false;
}

/**
 * @brief this function just inserts in the given location
 * 
 * @param const reference to an int to the location 
 * @param const reference to a string containing the first name
 * @param const reference to a string containing the last name
 * @param const reference to a string containing the number
 * @param reference to the phonebook that we will be inserting
 * 
 */
bool Phonebook::insert(const int& location_, const std::string& first_name_, const std::string& last_name_, 
const std::string& num_, std::vector<entry>& curr_phonebook){
    if(location_ >= 0){
        curr_phonebook[location_].first_name_ = first_name_;
        curr_phonebook[location_].last_name_ = last_name_;
        curr_phonebook[location_].number_ = num_;
        return true;
    }
    return false;
}

/**
* @brief this function removes a contact using lazy deletion. Keeps track of 
* number of lazy deletions to trigger rehashing if too many.
 * 
 * @param const reference to a string containing the first name
 * @param const reference to a string containing the last name
 * 
 * @return true or false if we remove the contact
 */
bool Phonebook::remove(const std::string& first_name_, const std::string& last_name_){
    //calls find and store location if found 
    size_t location_ = find(first_name_, last_name_);

    //double check location is a valid spot and set name to x as the flag
    if(location_ >= 0 ){
        phonebook_[location_].first_name_ = "x";
        size_--;
        lazy_deletion_size_++;
        load_factor_ = size_ / capacity_;

        //checks if we did to many lazy deletion or if the load factor is too low
        if(lazy_deletion_size_ / capacity_ > .3){
            toManyLazyDeletion();
        }else if(load_factor_ < .25){
            rehashDown();
        }
        return true;
    }
    //if we were unable to remove the contact
    return false;
}

/** 
 * @brief this function finds the loaction for a contact
 * 
 * @param const reference to a string of the first name
 * @param const reference to a string of the last name
 */
int Phonebook::find(const std::string& first_name_, const std::string& last_name_){
    int j = 0;    
    int h = hashHelper(first_name_.substr(0,3));
    size_t hash1 = h % capacity_;
    size_t hash2 = R - (h % R);

    //keep going until we find it
    while(j < capacity_){
        //double hash function
        size_t total_hash_ = (hash1 + j * hash2) % capacity_;

        //checks if there is anything there
        if(phonebook_[total_hash_].first_name_ == first_name_ && 
        phonebook_[total_hash_].last_name_ == last_name_){
            return total_hash_;
        }
        j++;
    }
    return -1;
}

/** FINDING PRIME NUMBERS **/

/**
 * @brief this function find the next prime number for our hash table.
 * The hash table new capacity has to be at least twice the size of the old.
 * 
 * @param size_t reference to the new capacity
 * 
 * @return a new prime number for the capacity
 */
int Phonebook::findNextPrime(size_t& new_capacity_, const std::string& indicator_){ 
    //if the new capacity isn't a prime number then we run a isPrime to look for one
    while(!isPrime(new_capacity_) && indicator_ == "up"){
        new_capacity_ += 2;
    }

    while(!isPrime(new_capacity_) && indicator_ == "down"){
        new_capacity_ -= 2;
    }

    //time to update R for whenever we are adding to the new table
    R = new_capacity_-2;
    while(!isPrime(R)){
        R -= 2;
    }
    return new_capacity_;
}

/**
 * @brief this fuction is the helper function for findNextPrime.
 * It insures that the new capacity is prime.
 * 
 * @param size_t reference to the new capacity
 * 
 * @return true or false if the number is prime
 */
bool Phonebook::isPrime(size_t& new_capacity_){
    for (size_t i = 3; i * i <= new_capacity_; i += 2){
        if (new_capacity_ % i == 0){
            return false;
        }
    }
    return true;
}

/** MUTATER **/

/**
 * @brief this function change the name for a contact
 * 
 * @param const reference to a string of the old last name we have to update
 * @param const reference to a string of the new last name we want to update
 * 
 * @return true or false if completed  
 */
bool Phonebook::changeContactLastName(const std::string& first_name_, const std::string& old_last_name_, const std::string& new_last_name_){
    //locate the contact
    int location_ = find(first_name_, old_last_name_);

    if(location_ > -1){
        phonebook_[location_].last_name_ = new_last_name_;
        return true;
    }
    return false;
}

/**
 * @brief this function change the number for a contact
 * 
 * @param const reference to a string of the first name
 * @param const reference to a string of the last name
 * @param const reference to a string of the contact number we want to update
 * 
 * @return true or false if completed  
 */
bool Phonebook::changeContactNumber(const std::string& first_name_, const std::string& last_name_, const std::string& new_number_){
    //locates the contact
    int location_ = find(first_name_, last_name_);

    if(location_ > -1){
        phonebook_[location_].number_ = new_number_;
        return true;
    }
    return false;
}

/** REHASHING AND HASHING **/

/**
 * @brief this function rehashes when the load factor is too high
 * 
 */
void Phonebook::rehashUp(){
    //makes a temp phonebook with a capacity that is new prime number at least twice the size as the old one
    capacity_ = (capacity_ * 2) + 1;
    capacity_ = findNextPrime(capacity_, "up");
    std::vector<entry> new_phonebook_(capacity_); 

    //loops throguh each item in the old phonebook and runs the hash fuction on it
    for(const auto& i : phonebook_){
        //if there is nothing there or lazy deleted skip
        if(i.first_name_.empty() || i.first_name_ == "x"){
            continue;
        }

        //find the location to insert at
        size_t location_ = hash(i.first_name_, new_phonebook_);

        insert(location_, i.first_name_, i.last_name_, i.number_, new_phonebook_);
    }
    //reasgin the table
    phonebook_ = std::move(new_phonebook_);
    //recalculate the new load factor 
    load_factor_ = size_ / capacity_;
}

/**
 * @brief this function rehashes down when the load facotr is too low
 */
void Phonebook::rehashDown(){
    //makes a temp phonebook with a capacity that is new prime number at least half the size as the old one
    capacity_ = (capacity_ / 2) + 1;
    capacity_ = findNextPrime(capacity_, "down");
    std::vector<entry> new_phonebook_(capacity_);

    //loops through each item in vector
    for(const auto& i : phonebook_){
        //if empty or lazy deleted skip
        if(i.first_name_.empty() || i.first_name_ == "x"){
            continue;
        }
        //finds a location to insert
        size_t location_ = hash(i.first_name_, new_phonebook_);

        insert(location_, i.first_name_, i.last_name_, i.number_, new_phonebook_);

    }
    //reasgin the table
    phonebook_ = std::move(new_phonebook_);
    //recalculate the new load factor 
    load_factor_ = size_ / capacity_;
}

/**
 * @brief this function rehashes when there were too many lazy deletion
 */
void Phonebook::toManyLazyDeletion(){
    for(const auto& i : phonebook_){
        //if deleted or nothing is there skip
        if(i.first_name_ == "x" || i.first_name_.empty()){
            continue;
        }

        size_t location_ = hash(i.first_name_, phonebook_);
        insert(location_, i.first_name_, i.last_name_, i.number_, phonebook_);
    }
}

/**
 * @brief this function does double hash until we find an empty spot
 * 
 * @param const reference to a string of the first name
 * @param const reference to a the hash table we want to insert in
 * 
 * @return an int to where to insert the contact
 */
int Phonebook::hash(const std::string& contact_name_, std::vector<entry>& table_){
    int h = hashHelper(contact_name_.substr(0,3));
    size_t hash1 = h % capacity_;
    size_t hash2 = R - (h % R);
    int j = 0;

    //if hash2 needs to be > 0
    if(hash2 == 0){
        hash2 = 1;
    }

    //keep going until we find a spot then we break
    while(j < capacity_){
        //double hash function
        size_t total_hash_ = (hash1 + j * hash2) % capacity_;

        //checks if there is anything there
        if(table_[total_hash_].first_name_.empty()){
            return total_hash_;
        }
        j++;
    }
    return -1;
}

/**
 * @brief this function hasehes strings using only the first three characters 
 * 
 * @param const reference to string of the item to be hashed
 * 
 * @return an int to the value produced 
 */
int Phonebook::hashHelper(const std::string& contact_name_){
    int hash_val_ = 0;

    //k3 +37(k2 + 37(k1 +37k0))
    for(char ch : contact_name_)
        hash_val_ = 37 * hash_val_ + ch;
    return hash_val_;
}

/** GETTERS **/

/**
 * @brief this function is a getter for phonebook
 * 
 * @return return the vector that the phonebook is hashed into
 */
std::vector<entry> Phonebook::getPhonebook()const{
    return phonebook_;
}

/**
 * @brief this function gets the size of the phonebook
 * 
 * @return an int to the size
 */
int Phonebook::getSize()const{
    return size_;
}

/**
 * @brief this fuction gets the capacity of the current phonebook
 * 
 * @return an int to the capacity
 */
int Phonebook::getCapacity() const{
    return capacity_;
}

/**
 * @brief this function gets the load factor
 * 
 * @return a double for the load factor
 */
double Phonebook::getLoadFactor() const{
    return load_factor_;
}

/**
 * @brief this function gets the number for a contain
 * 
 * @param const reference to a string of the first name
 * @param const reference to a string of the last name
 * 
 * @return a string containing the last name 
 */
std::string Phonebook::getNumber(const std::string& first_name_, const std::string& last_name_){
    //calls find function and save location if found
    int location_ = find(first_name_, last_name_);

    if(location_ > -1){
        return "The person you are looking for number is: " + phonebook_[location_].number_;
    }

    return  "Unable to find the person you are looking for.";
}