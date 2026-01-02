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
         * @brief This is the default constructor
         * Sets the size of the hash table
         * 
         * Default capacity_ to 5  
         * Default R to 3
         */
        Phonebook();

        /**
         * @brief This function rehashes when the load factor is too high
         * 
         */
        void rehash();

        /**
         * @brief 
         * 
         * @return an int to where to insert the contact
         */
        int hash(const std::string& contact_name_, std::vector<entry>& table_);

        /**
         * @brief This function hasehes the item by their name
         * 
         * @param const reference to string of the item to be hashed
         * 
         * @return an int to where to palace the item in the new hash table
         */
        int hashHelper(const std::string& contact_name_);

        /**
         * @brief This function checks to see if a contain is saved 
         * 
         * @param const reference of a string to the name of the contact that we have to look for
         * 
         * @return true or false if we found the contact or not
         */
        bool contains(const std::string& contact_name_);

        /**
         * @brief This function adds a contact
         * 
         * @param const reference of the string to the name of the contact that we have to add
         * @param const reference to an int for the number of the contact that we have to add
         * 
         * @return true or false if we added the contact or not
         */
        bool add(const std::string& contact_name_, const std::string& num_);

        /**
         * @brief This function removes a contact using lazy deletion
         * 
         * @param const reference to a string of the name of the contact that we have to remove
         * 
         * @return true or false if we remove the contact or not
         */
        bool remove(const std::string& contact_name_);

        int findNextPrime(size_t& new_capacity_);

        bool isPrime(size_t& new_capacity_);

};
#endif