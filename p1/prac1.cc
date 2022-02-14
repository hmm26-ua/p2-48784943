// Programación 2 - Práctica 1
// DNI: 48784943B MORAL MORALES, HECTOR

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()

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
     
    int suma_habilidades;
    
    do{
    cout<<"Enter hero name: "<< endl;
    cin.getline(name, KNAME-1);
    }
    
    
    cout<<"Enter attack/defense: "<< endl;
    cin>> hero.features.attack >> hero.features.defense;
        
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
  
    char option;
    cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
       /*cin >> option;
       switch(option){
           case 1:
           case 2:
           case 3:
           case 4:
       }
       */
}

int main(int argc,char *argv[]){
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
  }
}


