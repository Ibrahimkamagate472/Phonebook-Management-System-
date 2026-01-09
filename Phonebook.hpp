#include <iostream>
#include <vector>
#include <iomanip>

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

struct entry{
    std::string first_name_, last_name_, number_;
};


class Phonebook{
    private:
        size_t R, capacity_;
        double size_, load_factor_;
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
        
        /** BASIC OPERATIONS **/

        /**
         * @brief this function adds a contact
         * 
         * @param const reference to a string containing the first name
         * @param const reference to a string containing the last name
         * @param const reference to a string containing the number
         * 
         * @return true or false if we added the contact or not
         */
        bool add(const std::string& first_name_, const std::string& last_name_, const std::string& num_);

        /**
         * @brief this function removes a contact using lazy deletion
         * 
         * @param const reference to a string containing the first name
         * @param const reference to a string containing the last name
         * 
         * @return true or false if we remove the contact or not
         */
        bool remove(const std::string& first_name_, const std::string& last_name_);

        /** 
         * @brief this function finds the loaction for a contact
         * 
         * @param const reference to a string of the first name
         * @param const reference to a string of the last name
         */
        int find(const std::string& first_name_, const std::string& last_name_);

        /** FINDING PRIME NUMBER **/

        /**
         * @brief this function find the next prime number for our hash table.
         * The hash table new capacity has to be at least twice the size of the old.
         * 
         * @param size_t reference to the new capacity
         * 
         * @return a new prime number for the capacity
         */
        int findNextPrime(size_t& new_capacity_, const std::string& indicator_);

        /**
         * @brief this fuction is the helper function for findNextPrime.
         * It insures that the new capacity is prime.
         * 
         * @param size_t reference to the new capacity
         * 
         * @return true or false if the number is prime
         */
        bool isPrime(size_t& new_capacity_);

        /** MUTATER **/
        
        /**
         * @brief this function change the last name for a contact
         * 
         * @param const reference to a string of the old last name we have to update
         * @param const reference to a string of the new last name we want to update
         * 
         * @return true or false if completed  
         */
        bool changeContactLastName(const std::string& first_name_, const std::string& old_last_name_, const std::string& new_last_name_);

        /**
         * @brief this function change the number for a contact
         * 
         * @param const reference to a string of the first name
         * @param const reference to a string of the last name
         * @param const reference to a string of the contact number we want to update
         * 
         * @return true or false if completed  
         */
        bool changeContactNumber(const std::string& first_name_, const std::string& last_name, const std::string& new_number_);

        /** REHASHING AND HASHING **/

        /**
         * @brief this function rehashes when the load factor is too high
         * 
         */
        void rehashUp();

        /**
         * @brief this function rehashes down when the load facotr is too low
         */
        void rehashDown();

        /**
         * @brief this function does double hash until we find an empty spot
         * 
         * @param const reference to a string of the first name
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


        /** GETTERS **/
        
        /**
         * @brief this function is a getter for phonebook
         * 
         * @return return the vector that the phonebook is hashed into
         */
        std::vector<entry> getPhonebook()const;

        /**
         * @brief this function gets the size of the phonebook
         * 
         * @return an int to the size
         */
        int getSize()const;

        /**
         * @brief this fuction gets the capacity of the current phonebook
         * 
         * @return an int to the capacity
         */
        int getCapacity() const;

        /**
         * @brief this function gets the load factor
         * 
         * @return a double for the load factor
         */
        double getLoadFactor() const;

        /**
         * @brief this function gets the number for a contain
         * 
         * @param const reference to a string of the first name
         * @param const reference to a string of the last name
         * @return a string containing the last name 
         */
        std::string getNumber(const std::string& first_name_, const std::string& last_name_);

};
#endif