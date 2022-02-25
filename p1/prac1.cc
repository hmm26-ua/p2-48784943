// Programación 2 - Práctica 1
// DNI: 48784943B MORAL MORALES, HECTOR

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <ctype.h>
#include <cstring>
#include <string> // Para string
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
};

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

    
    int suma_habilidades;
    char c;

    do{
      cout<<"Enter hero name: ";
      cin.getline(hero.name, KNAME-1, '\n');
      
      
      if(strlen(hero.name)==0){ // Si la longitud del nombre es 0 el error se muestra en pantalla
        j=1;
      }
       else if(isalpha(hero.name[0])==0){ // Si la primera letra no es una letra se muestra el error en pantalla
        j=1;
      }else{
            for(int i = 0; i<strlen(hero.name); i++){ // bucle for para identificar en el nombre si hay algo diferente a una letra, numero o espacio en blanco
              if(isalpha(hero.name[i])==0 && isspace(hero.name[i])==0 && isalnum(hero.name[i])==0){
                j=1;
              }else{
                j=0;
              }
        }
      }
      if(j==1){ // En cada bucle si no se cumple la condicion j = 0, la j equivale a 1, entonces si la j = 1 se muestra el error
        cout<<"ERROR: wrong name"<<endl;
      }
        
    }while(j==1); // Condicion para que se repita el bucle

    do{
      cout<<"Enter attack/defense: ";
      cin>>hero.features.attack>>c>>hero.features.defense;
    
      suma_habilidades = hero.features.attack + hero.features.defense; 

     

      if(suma_habilidades > 100){
        cout<<"ERROR: wrong distribution"<<endl;
      }else if(suma_habilidades < 100){
        cout<<"ERROR: wrong distribution"<<endl;
      }
    }while(suma_habilidades > 100 || suma_habilidades < 100);


  return hero;
}

Enemy createEnemy(){
    
    Enemy enemy;
    
    string nombre_enemigo;
    int num;
    num = rollDice();
    
    if(num >=1 && num <=6){ // enemigo: AJOLOTE
      enemy.name = AXOLOTL;
      enemy.features.attack = 40;
      enemy.features.defense = 40;
      enemy.features.hp = 2 * enemy.features.defense;
      nombre_enemigo = "Axolotl";
    }else if(num > 6 && num <= 11){ // enemigo: TROLL
      enemy.name = TROLL;
      enemy.features.attack = 60;
      enemy.features.defense = 80;
      enemy.features.hp = 2 * enemy.features.defense;
      nombre_enemigo = "Troll";
    }else if(num > 11 && num <= 15){ // enemigo: ORCO
      enemy.name = ORC;
      enemy.features.attack = 80;
      enemy.features.defense = 120;
      enemy.features.hp = 2 * enemy.features.defense;
      nombre_enemigo = "Orc";
    }else if(num >15 && num <=18){ // enemigo: PERRO DEL INFIERNO
      enemy.name = HELLHOUND;
      enemy.features.attack = 120;
      enemy.features.defense = 100;
      enemy.features.hp = 2 * enemy.features.defense;
      nombre_enemigo = "Hellhound";
    }else if(num >18 && num <=20){ // enemigo: DRAGÓN
      enemy.name = DRAGON;
      enemy.features.attack = 160;
      enemy.features.defense = 140;
      enemy.features.hp = 2 * enemy.features.defense;
      nombre_enemigo = "Dragon";
    }
    
    cout << endl << "[Enemy]" << endl
       << "Breed: " << nombre_enemigo << endl
       << "Attack: " << enemy.features.attack<< endl
       << "Defense: " << enemy.features.defense<< endl 
       << "Health points: " << enemy.features.hp << endl;

    return enemy;
}

void report(Hero &hero){
  
  string special_attack;
  hero.special = true;
  int porcentaje_defensa;
  int vida;
  porcentaje_defensa = 2*hero.features.defense;
  vida = 2*porcentaje_defensa;
  if(hero.special == true){
    special_attack = "yes";
  }
  
  cout << endl<< "[Report]" << endl
       << "Name: " << hero.name << endl
       << "Attack: " << hero.features.attack<< endl
       << "Defense: " << porcentaje_defensa << endl 
       << "Health points: " << vida << endl
       << "Special: " << special_attack << endl
       << "Runaways: " <<endl
       << "Exp: " << endl
       << "Enemies killed: " << endl;

}

void ataque_especial(Hero &hero){
  hero.special = true;

}

void huir(int &runaway){
    
    cout<<"You run away"<<endl;
           runaway--; 
           if(runaway == 0 || runaway < 0){
             cout<<"ERROR: cannot runaway"<<endl;
           }
  
}

void fight(Hero &hero,Enemy &enemy){

    int dado_heroe;
    int dado_enemigo;
    int ataque_heroe;
    int ataque_enemigo;
    int defensa_heroe; 
    int defensa_enemigo;
    int vida_heroe;
    int vida_enemy;
    int hitpoints_hero;
    int hitpoints_enemy;
    int porcentaje_ataque;
    int porcentaje_defensa;
    int exp;

    exp = 0;
    dado_heroe = rollDice() * 5;
    dado_enemigo = rollDice() * 5;
    porcentaje_ataque = (2*hero.features.attack);
    porcentaje_defensa = (2*hero.features.defense);
    ataque_heroe = dado_heroe  + porcentaje_ataque;
    ataque_enemigo = dado_enemigo + enemy.features.attack;
    defensa_heroe = dado_heroe + porcentaje_defensa;
    defensa_enemigo = dado_enemigo + enemy.features.defense;
    hitpoints_hero = ataque_heroe - defensa_enemigo;
    hitpoints_enemy = ataque_enemigo - defensa_heroe;

    hero.features.hp = (2*porcentaje_defensa);
    
    vida_heroe = hero.features.hp - hitpoints_enemy;
    vida_enemy = enemy.features.hp - hitpoints_hero;

    if(hitpoints_hero < 0){
      hitpoints_hero = 0;
      vida_enemy = enemy.features.hp - 0;
    }

    if(hitpoints_enemy < 0){
      hitpoints_enemy = 0;
      vida_heroe = hero.features.hp - 0;
    }

  cout << endl << "[Hero -> Enemy]" << endl
       << "Attack: " << porcentaje_ataque << "+" << dado_heroe << endl
       << "Defense: " << enemy.features.defense << "+" << dado_enemigo << endl
       << "Hit points: " << hitpoints_hero << endl 
       << "Enemy health points: " << vida_enemy << endl;
   
  if((vida_enemy > 0)){
  cout << endl<< "[Enemy -> Hero]" << endl
       << "Attack: " << enemy.features.attack << "+" << dado_enemigo << endl
       << "Defense: " << porcentaje_defensa << "+" << dado_heroe << endl
       << "Hit points: " << hitpoints_enemy << endl 
       << "Hero health points: " << vida_heroe << endl;
  }
  if((vida_enemy == 0) || (vida_enemy < 0)){
      cout<<"Enemy killed"<<endl;
      createEnemy();
      if(enemy.name == 0 && vida_enemy == 0){
          exp = 100;
      }
      if(enemy.name == 1 && vida_enemy == 0){
          exp = 150;
      }
      if(enemy.name == 2 && vida_enemy == 0){
          exp = 200;
      }
      if(enemy.name == 3 && vida_enemy == 0){
          exp = 300;
      }
      if(enemy.name == 4 && vida_enemy == 0){
          exp = 400;
      }
  }
   if((vida_heroe == 0) || (vida_heroe < 0)){
          cout<<"You are dead"<<endl;
          report(hero);
  }
  
}

void showMenu(){
  
    cout << endl<< "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
      
}

int main(int argc,char *argv[]){
    
 if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
  
  int runaway;
  runaway = 3;
  char option;

  Hero hero = createHero();
  Enemy enemy = createEnemy();
  
    do{
        showMenu();
        cin >> option;
       
        switch(option){
           
           case '1': fight(hero, enemy);
           break;
           
           case '2': huir(runaway);
           break;
           
           case '3': ataque_especial(hero);
          
           case '4': report(hero);
           break;
           
           case 'q': break;
           
           default: cout<<"ERROR: wrong option"<<endl;
           break;
       }
    }while(option != 'q');
  }
}
