#include <iostream>
#include <vector>

#ifndef PHONEBOOK_H
#define PHONEBOOK_H


struct entry{
    std::string name_;
    std::string number_;
};

class Phonebook{
    private:
        size_t R;
        size_t capacity_;
        int size_;
        size_t load_factor_;
        std::vector<entry> phonebook_;

    public:
        /**
         * @brief this is the default constructor
         * 
         * default R to 3
         * default capacity_ to 5  
         * default size to 0
         * default load factor to 0
         * 
         */
        Phonebook();

        /**
         * @brief This function rehashes when the load factor is too high
         * 
         */
        void rehash();

        /**
         * @brief this function does double hash until we find an empty spot
         * 
         * @param const reference to a string of the contact name
         * @param const reference to a the hash table we want to insert in
         * 
         * @return an int to where to insert the contact
         */
        int hash(const std::string& contact_name_, std::vector<entry>& table_);

        /**
         * @brief this function hasehes strings using only the first three characters 
         * 
         * @param const reference to string of the item to be hashed
         * 
         * @return an int to the value preduced 
         */
        int hashHelper(const std::string& contact_name_);

        /**
         * @brief this function checks to see if a contain is saved 
         * 
         * @param const reference to a string containing the name
         * 
         * @return true or false if we found the contact or not
         */
        bool contains(const std::string& contact_name_);

        /**
         * @brief this function adds a contact
         * 
         * @param const reference to a string to the name of the contact that we have to add
         * @param const reference to an int for the number of the contact that we have to add
         * 
         * @return true or false if we added the contact or not
         */
        bool add(const std::string& contact_name_, const std::string& num_);

        /**
         * @brief this function removes a contact using lazy deletion
         * 
         * @param const reference to a string of the name of the contact that we have to remove
         * 
         * @return true or false if we remove the contact or not
         */
        bool remove(const std::string& contact_name_);

        /**
         * @brief this function find the next prime number for our hash table.
         * The hash table new capacity has to be at least twice the size of the old.
         * 
         * @param size_t reference to the new capacity
         * 
         * @return a new prime number for the capacity
         */
        int findNextPrime(size_t& new_capacity_);

        /**
         * @brief this fuction is the helper function for findNextPrime.
         * It insures that the new capacity is prime.
         * 
         * @param size_t reference to the new capacity
         * 
         * @return true or false if the number is prime
         */
        bool isPrime(size_t& new_capacity_);

};
#endif