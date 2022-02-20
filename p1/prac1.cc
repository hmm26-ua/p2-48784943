// Programación 2 - Práctica 1
// DNI: 48784943B MORAL MORALES, HECTOR

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <ctype.h>
#include <cstring>
using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado

struct Core{
  int attack;
  int defense;
  int hp;
}features;

enum Breed{
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
}monstruos;

struct Enemy{
  Breed name;
  Core features;
}enemy;

struct Hero{
  char name[KNAME];
  Core features;
  bool special;
  int runaways;
  int exp;
  int kills[KENEMIES];
}hero;

int rollDice(){
  return rand()%KDICE+1;
}



Hero createHero(char name[]){
    
    Hero hero;
    bool resultado;
    int i;
    
    
    cout<<"Introduce el nombre de tu heroe: ";
    cin.getline(hero.name, KNAME-1, '\n');
    
    int longitud;
    longitud=strlen(hero.name);
    
    if(longitud > KNAME){
        resultado = false;
    }
    
    if(isalpha(name[0])==0)
        resultado = false;
     for(i=0;i<32;i++){
         if(!isalpha(name[i]) && !isdigit(name[i]) && !isblank(name[i]))
         resultado = false;
}
    if(resultado == false){
    cout<<"Error: wrong name"<<endl;
    }
    
    
    int suma_habilidades;
    char c;
    cout<<"Enter attack/defense: "<< endl;
    cin>> hero.features.attack >> c >> hero.features.defense;
        
    suma_habilidades = hero.features.attack + hero.features.defense;
        
    if(suma_habilidades > 100){
    cout<<"ERROR: wrong distribution"<< endl;
    }
    
    
    return hero;
}

Enemy createEnemy(){
}

void fight(Hero &hero,Enemy &enemy){
}

void report(const Hero &hero){
}

 
void showMenu(){
  
    cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
      // cin >> option;
}

int main(int argc,char *argv[]){
    
    if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
  }
  
  
  /*do{
        showMenu();
        switch(option){
           case '1':
           case '2':
           case '3':
           case '4':
           case 'q': break;
       }
    }while(option != 'q');*/
  
  char option;
   char name[KNAME];
    Hero hero = createHero(name);
    Enemy enemy = createEnemy();
   
}


