#include <iostream>
#include <vector>

#ifndef PHONEBOOK_H
#define PHONEBOOK_H


struct entry{
    std::string name_;
    std::string number;
};

class Phonebook{
    private:
        int capacity_;
        int size_;
        int load_factor_;
        std::vector<entry> table;



    public:
        /**
         * @brief This is the default constructor
         * Sets the size of the hash table
         * 
         * Default capacity_ to 11  
         */
        Phonebook();

        /**
         * @brief This function rehashes when the load factor is too high
         * 
         */
        void rehash();

        /**
         * @brief This function hasehes the item by their name
         * 
         * @param const reference to string of the item to be hashed
         * 
         * @return an int to where to palace the item in the new hash table
         */
        int rehashHelper(const std::string& name_);

        /**
         * @brief This function checks to see if a contain is saved 
         * 
         * @param const reference of a string to the name of the contact that we have to look for
         * 
         * @return Ture or false if we found the contact or not
         */
        bool contains(const std::string& name_);

        /**
         * @brief This function adds a contact
         * 
         * @param const reference of the string to the name of the contact that we have to add
         * @param const reference to an int for the number of the contact that we have to add
         * 
         * @return Ture or false if we added the contact or not
         */
        bool add(const std::string name_, const int& number_);

        /**
         * @brief This function removes a contact
         * 
         * @param const reference to the name of the contact that we have to remove
         * 
         * @return Ture or false if we remove the contact or not
         */
        bool remove();




};
#endif