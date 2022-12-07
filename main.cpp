#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include "HashMap.h"
#include "Graph.h"
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/GutenbergBook.h"
using namespace std;
using namespace bridges;
using namespace chrono;

/* google doc report https://docs.google.com/document/d/1X7XGDAzmmM6IthXJ2HKMJj6fwKgk9qWj8J482xXRqFk/edit?usp=sharing
*/


int main(int argc, char **argv) {
    Bridges bridges (1, "rjanco", "265942688027");
    int menuOpt;
    string input,textData;
    int randomBook,bookSelect, displayOpt;
    bridges.setTitle("Gutenberg Book Collection Meta Data");
    DataSource ds (&bridges);
    vector<GutenbergBook> bookList;
    Graph graph;
    HashMapTable map;

    vector<string> subjects = {"Animal", "Canada", "Children", "Classics", "Countries", "Crime", "Education", "Fiction", "Fine arts", "General Works", "Geography", "History", "Language and Literature","Law","Music","Psychology and Philosophy", "Religion", "Science", "Social Sciences", "Technology", "Wars"};

    cout << "================================================="<< "\n"
         << "Welcome to our Project Gutenberg matching system!" << "\n" << "=================================================" << endl;
    cout << "Designed by Ethan Fan, Brandon Miguel, and Rama Janco for COP3530" << "\n" << endl;
    // Print intro & select option

    do{
        cout << "Please select an option " << endl;
        cout << "1. Search by Title" << "\n" << "2. Search by Year" << "\n" << "3. Search by Author"<< "\n"
             << "4. Search by Subject" << "\n" << "5. Inspiration!" << "\n" << "-1. Exit" << endl;
        cin >> menuOpt;
        bookList.clear();


        if (menuOpt == 1){
            bookList.clear();
            char exitPol;

            vector<GutenbergBook> titles;
            do{
                cout << "Please enter a title: " << endl;
                cin.ignore();
                getline (cin, input);
                bookList = ds.getGutenbergBookMetaData(input, "title");
                if (bookList.size() == 0) cout << "\n" << "Name not found! Please check for spelling." << endl;
                else {
                    titles.push_back(bookList.at(0));

                }

                cout << "Would you like to enter more titles? Enter y for yes or n for no" << endl;
                cin >> exitPol;
            } while(exitPol != 'n');
            for(int i = 0; i < titles.size(); i++) {
                if (titles.at(i).getLang() == "en") {
                    map.insertDataHM(ds.getGutenbergBookText(titles.at(i).getId()));
                  graph.insertData(ds.getGutenbergBookText(titles.at(i).getId()));
                    cout << i << "." << "\n\tTitle: " << titles.at(i).getTitle();
                    cout << "\n\tAuthors:";
                    for (auto &k: titles.at(i).getAuthors()) {
                        cout << k << ",";
                    }
                    cout << "\n\tDate: " << titles.at(i).getDateAdded() << "\n";
                }
            }
            cout << "\n\t1. Display top 20 words of all five works" <<"\n\t2. Search for occurrences of word" << endl;
            cin >> displayOpt;
            if (displayOpt == 1){
                cout << "Displaying..." << endl;
                auto start = high_resolution_clock::now();
                graph.printMostCommon();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by Graphs: " << duration.count() << " microseconds" << endl;
                start = high_resolution_clock::now();
                map.Get_HM_mostCommonWord();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
              cout << "Time taken by Hash Maps: " << duration.count() << " microseconds" << endl;
                cout << "Would you like to search for words as well? Input 2 for yes or 1 for no: " << endl;
                cin >> displayOpt;
            }
            if (displayOpt == 2){
                char exit;
                do {
                    string wordSearch;
                    cout << "Please input word to be searched" << endl;
                    cin >> wordSearch;
                    graph.findWord(wordSearch);
                   map.searchWord(wordSearch);
                    cout << "Would you like to search another word? Input y or n: ";
                    cin >> exit;
                } while(exit != 'n');
            }
            graph.clearData();
            map.Done();
        }


        else if (menuOpt == 2){ //date issued
            graph.clearData();
          map.Done();
            cout << "Please enter a year: ";
            cin.ignore();
            getline (cin, input);
            input.append("-01-01");
            bookList.clear();
            bookList = ds.getGutenbergBookMetaData(input, "date");
            int i = 1;
            cout << "Displaying 5 books: "<< endl;
            if(bookList.size() != 0){
                int i = 1;
                int j = 0;
                for (auto& b : bookList) {
                    if(b.getLang() == "en"){
 map.insertDataHM(ds.getGutenbergBookText(bookList.at(i-1).getId()));
                      graph.insertData(ds.getGutenbergBookText(bookList.at(i-1).getId()));
                        cout << i << "." << "\n\tTitle: "  << b.getTitle();
                        cout << "\n\tAuthors:";
                        for (auto& k: b.getAuthors()){
                            cout << k << ",";
                        }
                        cout << "\n\tDate: "  << b.getDateAdded() << "\n";

                        if (i == 5){
                            cout << endl;
                            break;
                        }
                        i++;
                    }
                    else j++;
                }
            }

            cout << "\n\t1. Display top 20 words of all five works" <<"\n\t2. Search for occurrences of word" << endl;
            cin >> displayOpt;
            if (displayOpt == 1){
                cout << "Displaying..." << endl;
                auto start = high_resolution_clock::now();
                graph.printMostCommon();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by Graphs: " << duration.count() << " microseconds" << endl;
                start = high_resolution_clock::now();
                map.Get_HM_mostCommonWord();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
              cout << "Time taken by Hash Maps: " << duration.count() << " microseconds" << endl;
                cout << "Would you like to search for words as well? Input 2 for yes or 1 for no: " << endl;
                cin >> displayOpt;
            }
            if (displayOpt == 2){
                char exit;
                do {
                    string wordSearch;
                    cout << "Please input word to be searched" << endl;
                    cin >> wordSearch;
                    graph.findWord(wordSearch);
                     map.searchWord(wordSearch);
                    cout << "Would you like to search another word? Input y or n: ";
                    cin >> exit;
                } while(exit != 'n');
            }
            graph.clearData();
            map.Done();
        }
        else if (menuOpt == 3){
            bookList.clear();
            char exitPol;
            vector<GutenbergBook> authors;
            do{
                cout << "Please enter an author: " << endl;
                cin.ignore();
                getline (cin, input);
                bookList = ds.getGutenbergBookMetaData(input, "author");
                if (bookList.size() == 0) cout << "\n" << "Name not found! Please check for spelling." << endl;
                else{
                    for (int i = 0; i < bookList.size(); i++) {
                        authors.push_back(bookList.at(i));
                    }
                }
                bookList.clear();
                cout << "Would you like to add another author's work? Enter y for yes or n for no" << endl;
                cin >> exitPol;
            } while(exitPol != 'n');
            for(int i = 0; i < authors.size(); i++) {
                if (authors.at(i).getLang() == "en") {
                   map.insertDataHM(ds.getGutenbergBookText(authors.at(i).getId())); graph.insertData(ds.getGutenbergBookText(authors.at(i).getId()));
                    cout << i << "." << "\n\tTitle: " << authors.at(i).getTitle();
                    cout << "\n\tAuthors:";
                    for (auto &k: authors.at(i).getAuthors()) {
                        cout << k << ",";
                    }
                    cout << "\n\tDate: " << authors.at(i).getDateAdded() << "\n";
                }
            }
            cout << "\n\t1. Display top 20 words of all five works" <<"\n\t2. Search for occurrences of word" << endl;
            cin >> displayOpt;
            if (displayOpt == 1){
                cout << "Displaying..." << endl;
                auto start = high_resolution_clock::now();
                graph.printMostCommon();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by Graphs: " << duration.count() << " microseconds" << endl;
                start = high_resolution_clock::now();
                map.Get_HM_mostCommonWord();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                cout << "Would you like to search for words as well? Input 2 for yes or 1 for no: " << endl;
                cin >> displayOpt;
            }
            if (displayOpt == 2){
                char exit;
                do {
                    string wordSearch;
                    cout << "Please input word to be searched" << endl;
                    cin >> wordSearch;
                    graph.findWord(wordSearch);
                    map.searchWord(wordSearch);
                    cout << "Would you like to search another word? Input y or n: ";
                    cin >> exit;
                } while(exit != 'n');
            }
            graph.clearData();
            map.Done();
        }

        else if (menuOpt == 4){
            cout << "Now listing out all available subjects..." << endl;
            for(int i = 0; i < subjects.size(); i++){
                cout << i + 1 << ": " << subjects.at(i) << endl;
            }
            cout << "Please enter a number: " << endl;
            int genre;
            cin >> genre;
            bookList.clear();

            bookList = ds.getGutenbergBookMetaData(subjects.at(genre-1), "genre");
            if(bookList.size() != 0){
                int i = 1;
                int j = 0;
                for (auto& b : bookList) {
                    if(b.getLang() == "en"){
                        map.insertDataHM(ds.getGutenbergBookText(bookList.at(i-1).getId()));
                        graph.insertData(ds.getGutenbergBookText(bookList.at(i-1).getId()));
                        cout << i << "." << "\n\tTitle: "  << b.getTitle();
                        cout << "\n\tAuthors:";
                        for (auto& k: b.getAuthors()){
                            cout << k << ",";
                        }
                        cout << "\n\tDate: "  << b.getDateAdded() << "\n";

                        if (i == 5){
                            cout << endl;
                            break;
                        }
                        i++;
                    }
                    else j++;
                }
            }

            cout << "\n\t1. Display top 20 words of all five works" <<"\n\t2. Search for occurrences of word" << endl;
            cin >> displayOpt;
            if (displayOpt == 1){
                cout << "Displaying..." << endl;
                auto start = high_resolution_clock::now();
                graph.printMostCommon();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by Graphs: " << duration.count() << " microseconds" << endl;
                start = high_resolution_clock::now();
                map.Get_HM_mostCommonWord();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                cout << "Would you like to search for words as well? Input 2 for yes or 1 for no: " << endl;
                cin >> displayOpt;
            }
            if (displayOpt == 2){
                char exit;
                do {
                    string wordSearch;
                    cout << "Please input word to be searched" << endl;
                    cin >> wordSearch;
                    graph.findWord(wordSearch);
                     map.searchWord(wordSearch);
                    cout << "Would you like to search another word? Input y or n: ";
                    cin >> exit;
                } while(exit != 'n');
            }
            graph.clearData();
            map.Done();
        }

        else if (menuOpt == 5){
            cout << "Enter a random number: ";
            cin >> randomBook;
            srand(randomBook); //use srand and user input so never the same sequence
            cout << "Finding your random book!!!" << endl;
            randomBook = rand() % (65970);
            bookList.clear();
            while(bookList.size() != 5){
                if(ds.getGutenbergBookMetaData(randomBook).getLang() == "en"){
                    bookList.push_back(ds.getGutenbergBookMetaData(randomBook));
                }
                randomBook = rand() % (65970);
            }
            int i = 1;
            cout << "Displaying 5 random books: "<< endl;
            for (auto& b : bookList) {
                graph.insertData(ds.getGutenbergBookText(bookList.at(i-1).getId()));
                map.insertDataHM(ds.getGutenbergBookText(bookList.at(i-1).getId()));
                cout << i << "." << "\n\tTitle: "  << b.getTitle();
                cout << "\n\tAuthors:";
                for (auto& k: b.getAuthors()){
                    cout << k << ",";
                }
                cout << "\n\tDate: "  << b.getDateAdded() << "\n";
                if (i == 5){
                    cout << endl;
                    break;
                }
                i++;
            }

            cout << "\n\t1. Display top 20 words of all five works" <<"\n\t2. Search for occurrences of word" << endl;
            cin >> displayOpt;
            if (displayOpt == 1){
                cout << "Displaying..." << endl;
                auto start = high_resolution_clock::now();
                graph.printMostCommon();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken by Graphs: " << duration.count() << " microseconds" << endl;
                start = high_resolution_clock::now();
                map.Get_HM_mostCommonWord();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                cout << "Would you like to search for words as well? Input 2 for yes or 1 for no: " << endl;
                cin >> displayOpt;
            }
            if (displayOpt == 2){
                char exit;
                do {
                    string wordSearch;
                    cout << "Please input word to be searched" << endl;
                    cin >> wordSearch;
                    graph.findWord(wordSearch);
                   map.searchWord(wordSearch);
                    cout << "Would you like to search another word? Input y or n: ";
                    cin >> exit;
                } while(exit != 'n');
            }
          map.Done();  
          graph.clearData();
        }
        else if (menuOpt == -1){
            //exit condition
        }
        else {
            cout << "Invalid Input" << "\n" << "Please re-enter a valid input" << endl;
            //cin.clear();
        }

    }
    while (menuOpt != -1);
    cout <<"Thanks for using our program! Have a great day." << endl;
    return 0;
}

