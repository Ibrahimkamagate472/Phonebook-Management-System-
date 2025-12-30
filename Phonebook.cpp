#include "Phonebook.hpp"


/**
 * @brief This is the default constructor
 * Sets the size of the hash table
 * 
 * Default capacity_ to 11  
 */
Phonebook::Phonebook(): capacity_(5), table(capacity_), size_(0), load_factor_(0){}


/**
 * @brief This function adds a contact
 * 
 * @param const reference of the string to the name of the contact that we have to add
 * @param const reference to an int for the number of the contact that we have to add
 * 
 * @return Ture or false if we added the contact or not
 */
bool Phonebook::add(const std::string name_, const int& number_){
    //triggers rehashing
    if(load_factor_ > .6){
        rehash();
    }
    
}


/**
 * @brief This function rehashes when the load factor is too high
 * 
 */
void Phonebook::rehash(){
    size_t hash1, hash2;
    //make the new capacity a prime number 
    capacity_  = (capacity_ * 2) + 1;
    size_t R = capacity_ - 2 ;

    //makes the new hash table
    std::vector<entry> new_table_(capacity_);

    //goes through everything in the table
    for(const auto& i : table){
        //if there is no entry skip or lazy deletion
        if(i.name_ == "" || i.name_ == "x"){
            continue; 
        }

        size_t h = rehashHelper(i.name_.substr(0,3));
        hash1 = h % capacity_;
        hash2 = R - (h % R);

        int j = 0;

        //keep going until we find a spot then we break
        while(j < capacity_){
            //double hash function
            size_t total_hash_ = (hash1 + j * hash2) % capacity_;

            //checks if there is anything there
            if(new_table_[total_hash_].name_ == ""){
                new_table_[total_hash_] = i;
                break;
            }
            j++;
        }
    }
    //reasgin the table
    table = std::move(new_table_);
}


/**
 * @brief This function is the helper function for rehash
 * retruns the hash value so we can double hash
 * 
 * @param const reference to string of the item to be hashed
 * 
 * @return an int to the hash value of the string
 */
int Phonebook::rehashHelper(const std::string& name_){
    size_t hash_val_ = 0;

    for(char ch : name_)
        hash_val_ = 37 * hash_val_ + ch;
    return hash_val_;
}