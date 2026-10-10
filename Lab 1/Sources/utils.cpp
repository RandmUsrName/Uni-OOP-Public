#include "utils.hpp"

using namespace std;

namespace utils {

    string CInputManager(string coutText, regex regexToMatchInput, bool instant, bool verbose){
        string output = "";
        char input;

        cout << coutText;

        // Keycodes: 13 - enter; 8 - backspace; 27 - esc
        while (true) {
            input = getch();

            // check if we want to wait for user to press enter
            if (instant) {
                // we don't wait
                if (input == 27) {
                    return "esc";
                }
                else {
                    output += input;
                    if (regex_search(output,regexToMatchInput)) {
                        if (verbose) {cout << output << endl;}
                        break;
                    }
                    else {output = "";}
                }
            }
            else {
                // we wait
                if (input == 27) {
                    return "esc";
                }
                else if (input == 8) {
                    if (verbose && output.length() > 0) {cout << "\b \b";}
                    if (output.length() > 0) {output.erase(output.end()-1);}
                }
                else if (input == 13) {
                    if (regex_search(output, regexToMatchInput)) {
                        cout << endl;
                        break;
                    }    
                    else{
                        output = "";
                        cout << "\n\033[31m>>>>> Bad input <<<<<\033[0m" << endl;
                        cout << coutText;
                    }
                }
                else {
                    if (verbose) {cout << input;}
                    output += input;
                }
            }
        }

        return output;
    }

    int string_find(string input, string what_to) {
        int pos;
        pos = input.find(what_to);
        if (pos != input.npos) {return pos;}
        return -1;
    }

    int string_count(string string_to_search, string to_find) {
        int pos = 0;
        for (int i = 0 ;; i++) {
            pos = string_to_search.find(to_find, pos);
            if (pos != string_to_search.npos) {pos++; continue;}
            return i;
        }
        return -1;
    }

    int lowerThan(string str_number, long double lower_than_this) {
        long double ld_number;

        ld_number = stold(str_number);
        if (ld_number < lower_than_this) {
            return 1;
        }
        return 0;
    }

    int write_string_to_array(long int array[], string string_to_write, string separator, int starting_point) {
        int sep_pos;
        string temp_substr;
        bool doBreak = false;
        int ElementsWritten = 0;

        for (int i = 0 ;; i++) {
            sep_pos = string_to_write.find(separator);
            if (sep_pos != string_to_write.npos) {
                temp_substr = string_to_write.substr(0, sep_pos);
                string_to_write = string_to_write.substr(sep_pos+1);
            }
            else {
                temp_substr = string_to_write;
                doBreak = true;
            }

            if (lowerThan(temp_substr, numeric_limits<long int>::max())) {
                array[starting_point+i] = stol(temp_substr);
            }
            else {array[starting_point+i] = 0;}
            ElementsWritten++;

            if (doBreak) {break;}
        }
        return ElementsWritten;
        
    }

}