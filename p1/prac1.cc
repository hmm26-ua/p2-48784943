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

Hero createHero(){
    
    Hero hero;
    int j=0;

    do{
      cout<<"Enter hero name: ";
      cin.getline(hero.name, KNAME-1, '\n');
      
      
      if(strlen(hero.name)==0){
        j=1;
      }
       else if(isalpha(hero.name[0])==0){
        j=1;
      }else{
            for(int i = 0; i<strlen(hero.name); i++){
              if(isalpha(hero.name[i])==0 && isspace(hero.name[i])==0 && isalnum(hero.name[i])==0){
                j=1;
              }else{
                j=0;
              }
        }
      }
      if(j==1){
        cout<<"Error: wrong name"<<endl;
      }
        
    }while(j==1);
}

Enemy createEnemy(){
    
//     rollDice();
//     if(rollDice==(1 || 2 || 3 || 4 || 5 || 6))
//         Breed = AXOLOTL;
    
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
      
}

int main(int argc,char *argv[]){
    
    bool nombrevalido;
     char name;
    if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
  }
  char option;
  int suma_habilidades;
  char c;

    Hero hero = createHero();

    do{
      cout<<"Enter attack/defense: ";
      cin>>hero.features.attack>>c>>hero.features.defense;
    
      suma_habilidades = hero.features.attack + hero.features.defense;
      

      if(suma_habilidades > 100){
        cout<<"Error: wrong distribution"<<endl;
      }else if(suma_habilidades < 100){
        cout<<"Error: wrong distribution"<<endl;
      }
    }while(suma_habilidades > 100 && suma_habilidades < 100);
  
    do{
        showMenu();
        cin >> option;
        switch(option){
           case '1':
           case '2':
           case '3':
           case '4':
           case 'q': break;
       }
    }while(option != 'q');
  
  
 
    
    
    
    Enemy enemy = createEnemy();
   
}


