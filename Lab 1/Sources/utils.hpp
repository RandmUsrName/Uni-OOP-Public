#pragma once

#include <iostream>
#include <cmath>
#include <windows.h>
#include <regex>
#include <conio.h>
#include <format>

using namespace std;

namespace utils {

    /// @brief 
    /// @param coutText what to output when function gets called
    /// @param regexToMatchInput regex to match input against
    /// @param instant don't wait for enter
    /// @param verbose print out input as user types
    /// @return "esc" if esc key gets pressed else user input
    string CInputManager(string coutText, regex regexToMatchInput = regex("\\S+"), bool instant = false, bool verbose = true);

    int string_find(string input, string what_to);

    int string_count(string string_to_search, string to_find);

    int lowerThan(string str_number, long double lower_than_this);
 
    /// @brief 
    /// @param array array to modify
    /// @param string_to_write string to write to array
    /// @param separator separator between values in a string
    /// @param starting_point point to start inputing at
    /// @return ammout of element written
    int write_string_to_array(long int array[], string string_to_write, string separator, int starting_point = 0);


    // ----------------------------------- templates ----------------------------------- 

    template <typename type> void array_print(type array[], int size_of_array, int start_pos = 0){
        cout << "{";
        for (int i = 0; i < size_of_array; i++) {
            cout << array[start_pos+i] << ((i < size_of_array-1) ? ", ":"");
        }
        cout << "}";
    }

    template <typename type> int array_find(type array[], int size_of_array, type element_to_find) {
    for (int i = 0; i < size_of_array; i++) {
        if (array[i] == element_to_find) {return i;}
    }
    return -1;
    }

    // moves element at | pos | to last pos in | array | and returns it
    template <typename type> type array_tolast(type array[], int array_size, int pos) {
        type saved_element = array[pos];
        for (int i = pos; i < (array_size-1); i++) {
            swap(array[i],array[i+1]);
        }
        return saved_element;
    }

    // creates an emtpy spot at | pos | and inserts | val | there
    template <typename type> void array_insert(type array[], int array_size, int pos, type val) {
        for (int i = array_size; i > (pos-1); i--) {
            swap(array[i+1],array[i]);
        }
        array[pos] = val;
    }

    template <typename type> void array_sort(type array[], int size_of_array, bool reverse = false) {
        if (reverse) {
            for (int i = 0; i < size_of_array-1;i++) {
                for (int j = 0; j < size_of_array-1-i;j++) {
                    if (array[j] < array[j+1]) {swap(array[j],array[j+1]);}
                }
            }
        }
        else {
            for (int i = 0; i < size_of_array-1;i++) {
                for (int j = 0; j < size_of_array-1-i;j++) {
                    if (array[j] > array[j+1]) {swap(array[j],array[j+1]);}
                }
            }
        }
    }

}