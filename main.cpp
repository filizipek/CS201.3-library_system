// Filiz İpek Oktay
//main.cpp

#include <iostream>
#include <vector>
#include "strutils.h"
using namespace std;

struct Book {
    string title, author;
    int year;
};

void bookVec(vector<Book> &books){
    books = {
                 {"The Great Gatsby", "F Scott Fitzgerald", 1925},
                 {"Moby Dick", "Herman Melville", 1851},
                 {"To Kill a Mockingbird", "Harper Lee", 1960},
                 {"Pride and Prejudice", "Jane Austen", 1813},
                 {"Burmese Days", "George Orwell", 1934},
                 {"Brave New World", "Aldous Huxley", 1932},
                 {"Animal Farm", "George Orwell", 1945}
    };
}

void prompt(int &choice) {
    cout << "Library System Menu:" << endl;
    cout << "1. Add books" << endl << "2. Search for an author" << endl;
    cout <<  "3. Search for by book title" << endl << "4. Display books";
    cout << endl << "5. Quit" << endl <<"Enter your choice: ";
    
    cin >> choice;
    
    if (choice > 5 || choice < 1) // not in range
        cout << "Invalid choice, please try again." << endl;
    
    if (choice == 5)
        cout << "Goodbye!" << endl;
    
}

void SelectSort(vector<Book> &books, bool &sorted){ //SORTING
// pre: a contains a.size() elements
// post: elements of a are sorted in non-decreasing order
    int j, k, minIndex, numElts = books.size();
    Book temp;
    for(k=0; k < numElts - 1; k++){
        minIndex = k;             // minimal element index
        for(j=k+1; j < numElts; j++){
            string a = LowerString(books.at(j).author.substr(books.at(j).author.rfind(' ') + 1)), b = LowerString(books.at(minIndex).author.substr(books.at(minIndex).author.rfind(' ') + 1));
            if (a < b){
                minIndex = j;
            } else if (a == b && LowerString(books[j].title) < LowerString(books.at(minIndex).title)){
                minIndex = j;
            }
        }
        temp = books[k];// swap min and k-th elements
        books[k] = books[minIndex];
        books[minIndex] = temp;
    }
    sorted = true;
}


int bsearch( vector<Book> &books, string &search_author, vector <int> &ind){
    ind = {};
    int low = 0;                 // leftmost possible entryx
    int high = books.size() - 1; // rightmost possible entry
    int mid = 0;                     // middle of current range
    bool flag = false, flag2 = false;
    
    while (low <= high){
        mid = (low + high) / 2;
        
        if (LowerString(books.at(mid).author.substr(books.at(mid).author.rfind(' ') + 1)) == LowerString(search_author.substr(LowerString(search_author).rfind(' ') + 1))){
            flag = true;
            low = mid + 1;
            for(int i = 0; i < mid + 1; i ++){
                if (LowerString(books.at(i).author.substr(books.at(i).author.rfind(' ') + 1)) == LowerString(search_author.substr(LowerString(search_author).rfind(' ') + 1))){
                    flag2 = true;
                    bool found = false;
                    for (int m = 0; m < ind.size(); m++) {
                        if (ind[m] == i) {
                            found = true;
                            break;
                        }
                    }
                    if(!found)
                        ind.push_back(i);
                    flag2 = false;
                }
            }
        } else if (LowerString(books[mid].author.substr(books[mid].author.rfind(' ') + 1)) < LowerString(search_author.substr(LowerString(search_author).rfind(' ') + 1))){   // key in upper half
            low = mid + 1;
        } else {   // key in lower half
            high = mid - 1;
        }
    }
    if(ind.size() == 0)
        return -1;
    else// not in list,
        return 1;
    
}

bool SearchTitle(vector<Book> &books, string &book_title, vector <int> &ind, int &pos){
    ind = {};
    int k = 0;
    while(k < books.size()){
        if(LowerString(books.at(k).title) == LowerString(book_title)){
            pos = k;
            return true;
        }
        k++;
    }
    return false;
}

int main() {
    vector<Book> books;
    string title, author, add_title, add_author, search_author, book_title;
    vector<int> ind;
    int choice = 0, add_year = 0, pos = 0;
    bool sorted = false;
    bookVec(books);
    
  
    while (choice != 5) {
        prompt(choice);
        if (choice == 4){ // DISPLAY
            if(sorted == false){
                SelectSort(books, sorted);
            }
            cout << "Sorted books by author's last name:" << endl;
            for (int i = 0; i < books.size(); i ++){
                cout << i+1 << ". " << books.at(i).title << ", " << books.at(i).author << ", " << books.at(i).year << endl;
            }
            cout << endl;
        } else if (choice == 1){
            cout << "Enter the new book details: " << endl;
            cout << "Enter book's title: ";
            cin.ignore();
            getline(cin, add_title);
           
            cout << "Enter book's author: ";
            getline(cin, add_author);
            cout << "Enter book's publication year: ";
            cin >> add_year;
            
            books.push_back({add_title, add_author, add_year});
            SelectSort(books, sorted);
            
        } else if (choice == 2) {
            if(sorted == false){
                SelectSort(books, sorted);
            }
            cout << "Enter the author of the book you want to search for: ";
            cin.ignore();
            getline(cin, search_author);
            int index = bsearch(books, search_author, ind);
            if (index == -1) {
                cout << "No books were found." << endl;
            } else {
                cout << "Books by " << search_author.substr(search_author.rfind(' ') + 1) << ":" << endl;
                for(int i = 0; i < ind.size(); i++){
                    cout << "Title: " << books.at(ind.at(i)).title << ", Publication Year: " ;
                    cout << books.at(ind.at(i)).year << ", Position: " << ind.at(i) + 1 << endl;
                }
            }

        } else if (choice == 3) {
            cout << "Enter the title of the book you want to search for: ";
            cin.ignore();
            getline(cin, book_title);
            cin.ignore(0);
            SelectSort(books, sorted);
            if(SearchTitle(books, book_title, ind, pos) == true){
                cout << "Books matching the title \"" << book_title << "\":" << endl;
                cout <<"Title: " << books.at(pos).title << ", Author: " <<books.at(pos).author << ", Publication Year: " << books.at(pos).year;
                cout << ", Position: " << pos + 1 << endl;
            } else {
                cout << "Books matching the title \"" << book_title << "\":" << endl;
                cout << "No books were found." << endl;
            }
        }
    }
}
