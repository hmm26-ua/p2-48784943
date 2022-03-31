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
#include <fstream>

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

struct BookStore{ 
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBook {
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
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

bool isValidName(string nombre){

	bool bien;
	int i;
  int tamanyo_nombre;

	if(nombre.length() == 0){ // cadena.empty() == true // cadena == ""
		 bien = false;
	}else{
		i = 0;
		bien = true;
		tamanyo_nombre = nombre.length();
		while(i < tamanyo_nombre && bien == true){
			if(isalnum(nombre[i]) == 0 && nombre[i] != ',' && nombre[i] != ':' && nombre[i] != ' ' && nombre[i] != '-'){
				bien = false;
			}
			else{
				i++;
			}
		}	
	}
	return bien;
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

bool isValidPrice(float price){

  if(price<=0){
      return false;
    }else{
      return true;
    }

}

void create_slug(Book &book){

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
   
   longitud = book.slug.length();
   if(book.slug[longitud-1]=='-'){
     book.slug.erase(longitud-1, 1);
   }
}

void addBook(BookStore &bookStore){

 Book book;

 book.id = bookStore.nextId;
 bookStore.nextId++;

 bool check_title;

 do{
  cout<<"Enter book title:";
  getline(cin, book.title);

  check_title = isValidName(book.title);

  if(check_title==0){
    error(ERR_BOOK_TITLE);
    check_title =0;
  }
 }while(check_title==0);

 bool check_authors;

 do{
  cout<<"Enter author(s):";
  getline(cin, book.authors);

  check_authors = isValidName(book.authors);

  if(check_authors==0){
    error(ERR_BOOK_AUTHORS);
    check_authors =0;
  }
 }while(check_authors==0);

 string year_text = "";
 book.year = 0;

 while(!isValidYear(book.year)){ 

  cout<<"Enter publication year:";
  getline(cin, year_text);

  if (year_text.length() > 0){
    book.year = stoi(year_text);
  }
  
  if(!isValidYear(book.year)){
    error(ERR_BOOK_DATE);
  }
 }

 string precio_book= "";
 book.price = 0;

 while(!isValidPrice(book.price)){ 
  cout<<"Enter price:";
  getline(cin, precio_book);

  if (precio_book.length() > 0) {
    book.price = stof(precio_book);
  }
  
  if(!isValidPrice(book.price)) {
    error(ERR_BOOK_PRICE);
  }
 } 

 create_slug(book);

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

 cout<<"Enter book id:";
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

 ifstream archivo;
 Book otrobook;
 string precio, anyo, nombre_fichero;

 if(nombre_fichero == ""){

	 cout << "Enter filename: ";
	 getline(cin, nombre_fichero);

 }

 archivo.open(nombre_fichero.c_str());

 if(archivo.is_open()){

	 archivo.get(); 

	while(!archivo.eof()){

		getline(archivo, otrobook.title, '"');
		archivo.get();
		archivo.get();
		getline(archivo, otrobook.authors, '"');
		archivo.get(); 
		getline(archivo, anyo, ','); 			
		archivo.get(); 
		getline(archivo, otrobook.slug, '"');
		archivo.get();
		getline(archivo, precio);			
		archivo.get(); 

		if(!isValidName(otrobook.title)){
			error(ERR_BOOK_TITLE);
		}else{
			if(!isValidName(otrobook.authors)){
				error(ERR_BOOK_AUTHORS);
			}else{
				if(anyo.empty()){
					error(ERR_BOOK_DATE);
				}else{
					otrobook.year = stoi(anyo);					
					if(!isValidYear(otrobook.year)){
						error(ERR_BOOK_DATE);
					}else{
							if(precio.empty()){
								error(ERR_BOOK_PRICE);
							}else{
								otrobook.price = stof(precio);
								if(!isValidPrice(otrobook.price)){
									error(ERR_BOOK_PRICE);
								}else{		
									otrobook.id = bookStore.nextId;
									bookStore.nextId++;
									bookStore.books.push_back(otrobook);
								}
							}
						}
					}
				}
			}
		}

		archivo.close();
	}

	else{
		error(ERR_FILE);
	}

}

void exportToCsv(const BookStore &bookStore){
  
  ofstream archivo;
  string nombre_fichero;
  int tamanyo = bookStore.books.size();
  
  cout<<"Enter filename:";
  getline(cin, nombre_fichero);

  archivo.open(nombre_fichero.c_str(), ios::out);
    
    if(archivo.is_open()) {
      
      for(int i=0; i<tamanyo; i++){
        archivo<<'"'<<bookStore.books[i].title<<'"'<<","<<'"'<<bookStore.books[i].authors<<'"'<<","<<bookStore.books[i].year<<","<<'"'<<bookStore.books[i].slug<<'"'<<","<<bookStore.books[i].price<<endl;
      }
      archivo.close();
      }else{
        error(ERR_FILE);
      }
} 
  
void loadData(BookStore &bookStore){
 
 BinBookStore datos;
 char opcion;

 do{
 
 cout<<"All data will be erased, do you want to continue (Y/N)?: ";
 cin>>opcion;
 cin.get();

 if(opcion == 'Y' || opcion == 'y'){
   
   string nombre_fichero;
   ifstream archivo;

   cout<<"Enter filename:";
   getline(cin, nombre_fichero);

   archivo.open(nombre_fichero, ios::in | ios::binary);

   if(archivo.is_open()){

     bookStore.books.clear();
     bookStore.nextId = 1;

     archivo.read((char *)&datos, sizeof(BinBookStore));

     bookStore.name=datos.name;
     BinBook otros_datos;
     Book b;
     
     for(long unsigned int i=0; i<bookStore.books.size(); i++){
       archivo.read((char *)&otros_datos, sizeof(BinBook));
       b.title = otros_datos.title;
       b.authors = otros_datos.authors;
       b.year = otros_datos.year;
       b.slug = otros_datos.slug;
       b.price = otros_datos.price;

       b.id=bookStore.nextId;
       bookStore.nextId++;
       bookStore.books.push_back(b);
     }
    archivo.close();
   }else{
     error(ERR_FILE);
   }
 }
 }while(opcion != 'Y' && opcion != 'y' && opcion != 'N' && opcion != 'n');
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