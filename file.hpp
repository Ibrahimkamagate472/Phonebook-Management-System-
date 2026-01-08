#include <fstream>
#include <iostream>
#include "Phonebook.hpp"


#ifndef FILE_H
#define FILE_H

class Phonebook;

class File{
    private:
        std::string file_name_;


    public:
        /**
         * @brief this function is the default constructor
         * 
         * set the file name 
         * creates a file if one isn't made or found
         */
        File();

        /**
         * @brief this function reads in local file that contains the
         * contact information at start up
         * 
         * @param reference to a phonebook
         */
        void readFromFile(Phonebook& phonebook_);

        /**
         * @brief this function stores the Phonebook to a local file
         * 
         * @param const reference to a phonebook
         */
        void readToFile(const Phonebook& phonebook_);
};
#endif