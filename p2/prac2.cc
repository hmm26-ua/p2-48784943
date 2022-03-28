// Programación 2 - Práctica 2
// DNI: 48784943B
// Nombre: HECTOR MORAL MORALES

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <ctype.h>
#include <cctype>

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

struct BookStore{ 
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
  int i;

  for(i = 0; i<cantidad_libros; i++){
    cout<<bookStore.books[i].id<<". "<<bookStore.books[i].title<<" ("<<bookStore.books[i].year<<")"<<", "<<bookStore.books[i].price<<endl;
  }
  
}

void showExtendedCatalog(const BookStore &bookStore) {
  
  Book book;
  int i;
  int cantidad_libros = bookStore.books.size();

  for(i=0; i<cantidad_libros; i++){
    cout<<'"'<<bookStore.books[i].title<<'"'<<","<<'"'<<bookStore.books[i].authors<<'"'<<","<<bookStore.books[i].year<<","<<'"'<<bookStore.books[i].slug<<'"'<<","<<bookStore.books[i].price<<endl;
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

bool isValidYear(int year) {
  if (year > 2022 || year < 1440){
    return false;
  }
  else
  {
    return true;
  }
}

void comprobar_anyo(Book &book){
  
  string year_text = "";
  book.year = 0;

  while(!isValidYear(book.year)){ 

    cout<<"Enter publciation year: ";
    getline(cin, year_text);

    if (year_text.length() > 0){
      book.year = stoi(year_text);
    }
  
    if(!isValidYear(book.year)){
      error(ERR_BOOK_DATE);
    }
  }
}

bool isValidPrice(float price){

  if(price<=0){
      return false;
    }else{
      return true;
    }

}

void precio_libro(Book &book){
  
  string precio_book= "";
  book.price = 0;

  while(!isValidPrice(book.price)){ 
    cout<<"Enter price: ";
    getline(cin, precio_book);

    if (precio_book.length() > 0) {
      book.price = stof(precio_book);
    }
  
    if(!isValidPrice(book.price)) {
      error(ERR_BOOK_PRICE);
    }
  } 
}

void slug_minusculas(Book &book){

  book.slug = book.title;

  int longitud = book.slug.length();
  int i;

  for(i=0; i<longitud; i++){
    book.slug[i] = tolower(book.slug [i]);

    if(!isalnum(book.slug [i]) && !isalpha(book.slug [i])){
      book.slug [i]= '-';
    }
  }
  
  for(i=0; i<longitud; i++){
    if(book.slug[i]=='-' && book.slug[i+1]=='-'){
      book.slug.erase(book.slug.begin()+(i));
      i--;
      longitud = book.slug.length();
    } 
  }

   if(book.slug[0] == '-'){
      book.slug.erase(book.slug.begin());
   }

   

}


void addBook(BookStore &bookStore){

Book book;
book.id = bookStore.nextId;
bookStore.nextId++;
comprobar_titulo(book);
comprobar_autor(book);
comprobar_anyo(book);
precio_libro(book);
slug_minusculas(book);

bookStore.books.push_back(book);

}

int longitud_delete(const vector<Book> &books, unsigned int id){

  int pos_libro;
  int tamanyo_libros = books.size();
  pos_libro = -1;

  for(int i=0; i<tamanyo_libros && pos_libro == -1; i++){
    if(books[i].id == id){
      pos_libro = i;
    }
  }
  return pos_libro;
}

void deleteBook(BookStore &bookStore){
  
  Book book;
  
  int pos_libro, id;
  string book_id;

  cout<<"Enter book id: ";
  getline(cin, book_id);

  if(book_id.length() == 0){
    error(ERR_ID);
  }else{
    id = stoi(book_id);
    pos_libro = longitud_delete(bookStore.books, id);
    if(pos_libro == -1){
      error(ERR_ID);
    }else{
      bookStore.books.erase(bookStore.books.begin() + pos_libro);
    }
  }
}

void importFromCsv(BookStore &bookStore){
}

void exportToCsv(const BookStore &bookStore){
}

void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}

void menu_import_export(){

  cout << "[Import/export options]" << endl
       << "1- Import from CSV" << endl
       << "2- Export to CSV" << endl
       << "3- Load data" << endl
       << "4- Save data" << endl
       << "b- Back to main menu" << endl
       << "Option: ";

}

void importExportMenu(BookStore &bookStore){
  
  char option;
  
  do {
    menu_import_export();
    cin >> option;
    cin.get();

    switch (option) {
      case '1':
        importFromCsv(bookStore);
        break;
      case '2':
        exportToCsv(bookStore);
        break;
      case '3':
        loadData(bookStore);
        break;
      case '4':
        saveData(bookStore);
        break;
      case 'b':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'b');
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
