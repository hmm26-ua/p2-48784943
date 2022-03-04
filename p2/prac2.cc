// Programación 2 - Práctica 2
// DNI: 48784943B
// Nombre: HECTOR MORAL MORALES

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <ctype.h>

using namespace std;

const int KMAXSTRING = 50;

enum Error {
  ERR_OPTION,
  ERR_BOOK_TITLE,
  ERR_BOOK_AUTHORS,
  ERR_BOOK_DATE,
  ERR_BOOK_PRICE,
  ERR_ID,
  ERR_FILE,
  ERR_ARGS
};

struct Book {
  unsigned int id;
  string title;
  string authors;
  int year;
  string slug;
  float price;
}book;

struct BinBook {
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
};

struct BookStore {
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBookStore {
  char name[KMAXSTRING];
  unsigned int nextId;
};

void error(Error e) {
  switch (e) {
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_BOOK_TITLE:
      cout << "ERROR: wrong book title" << endl;
      break;
    case ERR_BOOK_AUTHORS:
      cout << "ERROR: wrong author(s)" << endl;
      break;
    case ERR_BOOK_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_BOOK_PRICE:
      cout << "ERROR: wrong price" << endl;
      break;
    case ERR_ID:
      cout << "ERROR: wrong book id" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
      break;
  }
}

void showMainMenu() {
  cout << "[Options]" << endl
       << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl
       << "3- Add book" << endl
       << "4- Delete book" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void showCatalog(const BookStore &bookStore) {
  
  Book book;
  int i;
  int cantidad_libros;

  for(i = 0; i<bookStore.books.size(); i++){
    cout<<i<<". "<<bookStore.books[i].title<<endl;
  }
  
}

void showExtendedCatalog(const BookStore &bookStore) {
  Book book;
  int i;
  int cantidad_libros = bookStore.books.size();

  for(i=0; i<cantidad_libros; i++){
    cout<<'"'<<book.title[i]<<'"'<<","<<'"'<<book.authors[i]<<'"'<<","<<'"'<<book.year<<'"'<<","<<'"'<<book.slug<<'"'<<","<<book.price<<endl;
  }

}

void addBook(BookStore &bookStore) {
  Book book;
  int i;
  int j;
  int longitud_titulo = book.title.size();
  int longitud_autor = book.authors.size();

do{

  cout<<"Enter book title: ";
  getline(cin, book.title);

  for(i = 0; i<longitud_titulo; i++){
      if(!(isalnum(book.title[i]) || (book.title[i] = ' ') || (book.title[i] = ':') || (book.title[i] = ',') || (book.title[i] = '-'))){
        j = 1;
        error(ERR_BOOK_TITLE);
      }else{
        j=0;
      }
  }

}while(j==1);

do{
    
  cout<<"Enter author(s): ";
  getline(cin, book.authors);

  for(i = 0; i<longitud_autor; i++){
      if(!(isalnum(book.authors[i]) || (book.authors[i] = ' ') || (book.authors[i] = ':') || (book.authors[i] = ',') || (book.authors[i] = '-'))){
        j = 1;
        error(ERR_BOOK_AUTHORS);
      }else{
        j = 0;
      }
  }

}while(j==1);

do{

  cout<<"Enter publication year: ";
  getline(cin, book.year);

  if(book.year < 1440 && book.year > 2022 && book.year.size() == 0 ){
    j= 1;
    error(ERR_BOOK_DATE);
  }


}while(j==1);


  bookStore.books.push_back(book);
}

void deleteBook(BookStore &bookStore) {
}

void importExportMenu(BookStore &bookStore) {
}

void importFromCsv(BookStore &bookStore){
}

void exportToCsv(const BookStore &bookStore){
}

void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}

int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;

  char option;
  do {
    showMainMenu();
    cin >> option;
    cin.get();

    switch (option) {
      case '1':
        showCatalog(bookStore);
        break;
      case '2':
        showExtendedCatalog(bookStore);
        break;
      case '3':
        addBook(bookStore);
        break;
      case '4':
        deleteBook(bookStore);
        break;
      case '5':
        importExportMenu(bookStore);
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}