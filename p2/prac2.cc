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
  
  int cantidad_libros = bookStore.books.size();

  for(int id = 0; id<cantidad_libros; id++){
    cout<<id+1<<". "<<bookStore.books[id].title<<"("<<bookStore.books[id].year<<")"<<","<<bookStore.books[id].price<<endl;
  }
  
}

void showExtendedCatalog(const BookStore &bookStore) {
  
  Book book;
  int i;
  int cantidad_libros = bookStore.books.size();

  for(i=0; i<cantidad_libros; i++){
    cout<<'"'<<bookStore.books[i].title<<'"'<<","<<'"'<<bookStore.books[i].authors<<'"'<<","<<'"'<<bookStore.books[i].year<<'"'<<","<<'"'<<bookStore.books[i].slug<<'"'<<","<<bookStore.books[i].price<<endl;
  }

}

void comprobar_titulo(Book &book){
 
int i; 
int j;

do{

cout<<"Enter book title: ";
  getline(cin, book.title);

  int longitud_titulo;
  longitud_titulo = book.title.size();

  if(longitud_titulo == 0){
    j=1;
  }

  for(i = 0; i<longitud_titulo; i++){
      if(!(isalnum(book.title[i]) || (book.title[i] == ' ') || (book.title[i] == ':') || (book.title[i] == ',') || (book.title[i] == '-'))){
        j = 1;
      }else{
        j=0;
      }
  }

  if(j==1){
        error(ERR_BOOK_TITLE);
  }

}while(j==1);

}

void comprobar_autor(Book &book){
  
int i;
int j;

do{
    
  cout<<"Enter author(s): ";
  getline(cin, book.authors);

  int longitud_autor;
  longitud_autor = book.authors.size();

  if(longitud_autor == 0){
    j=1;
  }

  for(i = 0; i<longitud_autor; i++){
      if(!(isalnum(book.authors[i]) || (book.authors[i] == ' ') || (book.authors[i] == ':') || (book.authors[i] == ',') || (book.authors[i] == '-'))){
        j = 1;
      }else{
        j = 0;
      }
  }

  if(j==1){
    error(ERR_BOOK_AUTHORS);
  }

}while(j==1);

}

void comprobar_anyo(Book &book){

  int j;
  
  do{

    cout<<"Enter publciation year: ";
    cin >> book.year;
  
    if(book.year>2022 || book.year<1440){
      j=1;
    }else{
      j=0;
    }

    if(j==1){
      error(ERR_BOOK_DATE);
    }

  }while(j==1);
  
}

void precio_libro(Book &book){

  int j;

  do{
    cout<<"Enter price: ";
    cin>>book.price;

    if(book.price<0){
      j=1;
    }else{
      j=0;
    }

    if(j==1){
      error(ERR_BOOK_PRICE);
    }
  }while(j==1);
  
}

void addBook(BookStore &bookStore){

Book book;

comprobar_titulo(book);
comprobar_autor(book);
comprobar_anyo(book);
precio_libro(book);

bookStore.books.push_back(book);

}

void deleteBook(BookStore &bookStore){
}

void importExportMenu(BookStore &bookStore){
}

void importFromCsv(BookStore &bookStore){
}

void exportToCsv(const BookStore &bookStore){
}

void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}

int main(int argc, char *argv[]){
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
