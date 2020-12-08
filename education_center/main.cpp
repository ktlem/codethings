/* 'Education Center'
 *
 * Description:
 * This is a program that presents the user a selection of courses by location. To initialize the
 * program, the user will need to input course data as a csv-file, from which the program will generate
 * the course selection in a format that can be accessed using various commands.
 *
 * The user can input following commands to the program:
 *
 * locations ------------------- prints a list of all known locations
 * courses <location><theme> --- prints a list of all known courses at the selected location
 * available ------------------- prints a list of all available courses
 * courses_in_theme <theme> ---- prints a list of all courses under the chosen theme
 * favorite_theme -------------- prints the most popular course(s) by enrollments
 *
 *
 * Program author
 * Name: Kristian Lempinen
 * Student number: H296236
 * UserID: sbkrle
 * E-Mail: kristian.lempinen@tuni.fi
 *
 * Notes about the program and it's implementation:
 * - Have fun!
 * */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;


int MAX_ENROLLMENTS = 50;


struct Course {
    string name;
    string theme;
    int enrollments;
};


// Main container representing all available course offerings by location.
map<string, vector<Course>> all_courses;


// Split-function for parsing user input within the main program.
vector<string> split(const string& s, const char& delimiter, bool ignore_empty = false){

    vector<string> result;
    string temp = s;

    while (temp.find(delimiter) != string::npos){

        string part = temp.substr(0, temp.find(delimiter));
        temp = temp.substr(temp.find(delimiter) + 1, temp.size());

        if ( not (ignore_empty and part.empty() )){
            result.push_back(part);
        }
    } if ( not (ignore_empty and temp.empty() )){
        result.push_back(temp);
    } return result;
}



// Complementary function used when checking whether a given course is full when parsing input file.
bool isNumeric(const string enrollments){

    for (unsigned long int i=0; i < enrollments.length(); i++){
        if (isdigit(enrollments[i]) == false)
            return false;}

    return true;
}



// Alphabetical sorting function of Course struct-members.
bool sortComparison(const Course& a, const Course& b){
    if ( a.theme == b.theme )
        return a.name < b.name;
    else
        return a.theme < b.theme;
}



// Implementation of 'locations'-command.
void printLocations(map<string, vector<Course>>){

   for (map<string, vector<Course>>::iterator iter = all_courses.begin();
        iter != all_courses.end(); iter++){

       cout << iter->first << endl;
   }
}



// Implementation of 'courses'-command.
void printCourses(const map<string, vector<Course>>, const vector<string> read_input){

    map<string, vector<Course>>::iterator iter = all_courses.find(read_input.at(1));

    if (iter != all_courses.end()){

        vector<Course> courses = iter->second;

        // Checking whether entered theme is valid.
        const string theme_input = read_input.at(2);
        const auto theme_exists = find_if( courses.begin(), courses.end(),
                                [theme_input] (const Course& a)
                                {return a.theme == theme_input;});

        if ( theme_exists != courses.end()){
            sort(courses.begin(), courses.end(), sortComparison);

            for (unsigned long int i = 0; i < courses.size(); i++){

                if ( courses[i].theme == theme_input){

                    if ( courses[i].enrollments == 50 ){
                        cout << courses[i].name << " --- " << "full" << endl;
                    } else {
                        cout << courses[i].name << " --- " << courses[i].enrollments <<
                                " enrollments" << endl;
                    }
                }
            }
        } else {
            cout << "Error: unknown theme " << endl;
        }
    } else {
        cout << "Error: unknown location name " << endl;
    }

}



// Implementation of the 'available'-command.
void printAvailable(const map<string, vector<Course>>){

    for (map<string, vector<Course>>::iterator iter = all_courses.begin();
         iter != all_courses.end(); iter++){

        string location = iter->first;
        vector<Course> courses = iter->second;
        sort(courses.begin(), courses.end(), sortComparison);

        for (unsigned long int i = 0; i < courses.size(); i++){

            if ( courses[i].enrollments < 50 ){

                cout << location << " : " << courses[i].theme << " : "
                     << courses[i].name << endl;
            }
        }
    }
}



// Implementation of the 'courses_in_theme'-command.
void printTheme(const map<string, vector<Course>>, const vector<string> read_input){


    set<string> courses_by_theme;
    
    for (map<string, vector<Course>>::iterator iter = all_courses.begin();
         iter != all_courses.end(); iter++){
  
        if (iter != all_courses.end()){
            vector<Course> courses = iter->second;

            for (unsigned long int i = 0; i < courses.size(); i++){
               if  ( courses[i].theme == read_input[1]){
                   courses_by_theme.insert(courses[i].name);
               }
            }
        }
    }
    if ( courses_by_theme.size() == 0){
        cout << "Error: unknown theme" << endl;
    } else {
        for (auto it = courses_by_theme.begin(); it != courses_by_theme.end(); ++it){
            cout << *it << endl;
        }
    }
}



// Implementation of the 'favorite_theme'-command.
void printFavorite(const map<string, vector<Course>>){

    set<string> most_popular;
    int current_highest = 0;
    map<string, int> courses_m;

    // Creating a separate map which stores courses by theme and enrollment numbers.
    for (map<string, vector<Course>>::iterator iter = all_courses.begin();
         iter != all_courses.end(); iter++){

        string location = iter->first;
        vector<Course> courses = iter->second;

        for (unsigned long int i = 0; i < courses.size(); i++){

            if ( courses_m.count(courses[i].theme) > 0 ){
                courses_m.at(courses[i].theme) += courses[i].enrollments;
            } else {
                courses_m.insert( pair<string, int>(courses[i].theme, courses[i].enrollments));
            }


        }
    }
    // Finding the most popular theme by comparing enrollments within the map.
    for (map<string, int>::iterator itr = courses_m.begin();
         itr != courses_m.end(); itr++){
        string theme_m = itr->first;
        int enrollments_m = itr->second;

        if ( enrollments_m > current_highest ){
            current_highest = enrollments_m;
            most_popular.clear();
            most_popular.insert(theme_m);

        } else if ( enrollments_m == current_highest ){
            most_popular.insert(theme_m);

        }
    }

    if (most_popular.size() > 0){

        cout << current_highest << " enrollments in themes" << endl;
        for (auto it = most_popular.begin(); it != most_popular.end(); ++it){
                cout << "--- " << *it << endl;
        }
    } else {
        cout << "No enrollments" << endl;
    }

}


// --------------------------------------------------------
// --------------------------------------------------------


int main()
{
    // Program starts by asking the user for a file to read.
    string filename = "";
    cout << "Input file: ";
    getline(cin, filename);

    ifstream input_file(filename);


    // Reading input file and checking for errors.
    if (not input_file){
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;

    } else {

        string line;

        while (getline( input_file, line)) {
            vector<string> read_line;
            stringstream s_stream(line);

            while (s_stream.good()) {
                string substring;
                getline(s_stream, substring, ';');
                read_line.push_back(substring);

            } if (read_line.size() != 4){
                cout << "Error: empty field" << endl;
                return EXIT_FAILURE;

            } else {

                /* Enrollments set to constant (representing 'full' value) by default.
                If equivalent vector object is numeric (= not 'full'), the number of
                enrollments will be replaced from stoi(vector object) to represent
                a value that is still relevant for someone browsing for available courses.*/
                int enrolled = MAX_ENROLLMENTS;
                string location = read_line[0];
                string theme = read_line[1];
                string name = read_line[2];

                if ( isNumeric(read_line[3]) ){
                    enrolled = stoi(read_line[3]);
                }

                Course add_course{name, theme, enrolled};

                if (all_courses.find(location) == all_courses.end()) {
                    vector<Course> courses;
                    courses.push_back(add_course);
                    all_courses.insert({location, courses});

                } else {

                    // Checking if the same course appears twice.
                    bool no_duplicates = true;
                    for (unsigned long int i = 0; i < all_courses[location].size(); i++){

                        // Updating enrollments from the latest instance of a duplicate course.
                        if (name == all_courses[location][i].name){
                            all_courses[location][i].enrollments = enrolled;
                            no_duplicates= false;
                        }

                    } if ( no_duplicates ) {
                        all_courses[location].push_back(add_course);

                    } else {
                        continue;
                    }
                }
            }
        }
    }

    input_file.close();

    string user_input ="";
    cout << "> ";

    vector<string> read_input = {};

    while (getline(cin, user_input)){

        read_input = split(user_input, ' ');

        string command = read_input.at(0);

        if (command == "quit"){
            return EXIT_SUCCESS;
        }

        else if (command == "locations"){
            printLocations(all_courses);
        }

        else if (command == "courses" && read_input.size() <= 4){
                for (string& s : read_input){
                    s.erase(remove(s.begin(), s.end(), '"'), s.end());
                }
                // Making input readable by program if entered within quotation marks.
                if (read_input.size() == 4){
                    read_input[2] = read_input[2] + " " + read_input[3];
                    printCourses(all_courses, read_input);

                // Error-handling for false amount of command parameters.
                } else if (read_input.size() > 4){
                    cout << "Error: error in command courses" << endl;

                } else if (read_input.size() < 3){
                    cout << "Error: error in command courses" << endl;

                } else {
                    printCourses(all_courses, read_input);
                }
        }
        else if (command == "available"){
            printAvailable(all_courses);
        }

        else if (command == "courses_in_theme" && read_input.size() == 2){
            printTheme(all_courses, read_input);
        }

        // Error-handling for false amount of command parameters.
        else if (command == "courses_in_theme" && read_input.size() != 2){
            cout << "Error: error in command courses_in_theme" << endl;
        }

        else if (command == "favorite_theme"){
            printFavorite(all_courses);
        }

        else {
            cout << "Error: Unknown command: " << read_input[0] << endl;
        }
        cout << "> ";
    }

}


// --------------------------------------------------------
// --------------------------------------------------------

