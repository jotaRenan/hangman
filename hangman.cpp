#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <fstream>

using namespace std;

#define MAX 46
#define LIVES 7
#define red "\033[22;31m"
#define green "\033[22;32m"
#define white "\033[22;37m"
#define yellow "\033[01;33m"
#define SIZE 29858 //numero de palavras

void gotoxy(int coluna, int linha) {
        COORD point;
        point.X = coluna; point.Y = linha;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

class Hangman {
  private:
    int lives=LIVES, acertos=0;
    string palavra, palavraHidden, listados;
  public:
    //void initialize();
    void typeWord();          //usuario digita
    void pickWord();          //programa escolhe de um .txt
    void inserir();
    void check(char);         //checa correcao da letra
    void ending(int);         //tela final
    int continua();           //ve se o jogo acabou
    void status();            //mostra vidas e acertos
    void hearts();            //mostra vidinhas
    void listar(char);        //mostra palpites
    void convert(string&);    //vira lowercase
};

void Hangman::typeWord(){
  char ch;
  gotoxy(28, 11);
  cout << "Insira palavra: ";
  cin >> palavra;
  convert(palavra);
  system("cls");
}

void Hangman::pickWord(){
  /*srand(time(0));
  string opcoes[] = { "maracuja", "microfone", "teclado", "periquito", "Jesus", "gIlmAR"};
  int choice = rand()%6;
  palavra=opcoes[choice];
  */
  ifstream file("Lista-De-Palavras.txt");
  string myArray[SIZE];
  if(file.is_open()){
    for (int i=0; i<SIZE; ++i)
      file >> myArray[i];
  }
  srand(time(0));
  int choice = rand()%SIZE;
  palavra=myArray[choice];
  convert(palavra);
  system("cls");
}

void Hangman::inserir() {
  char letra;
  status();
  gotoxy( 8, 17);
  cout << "Arrisque uma letra ou palavra: ";
  cin >> letra;
  check(letra);
  listar(letra);
}

void Hangman::listar(char ch) {
  gotoxy(40, 8);
  listados.resize(listados.size()+1, ch);
  cout << "Palpites: ";
  int i;
  for (i=0; i < listados.size()-1; i++) {
    cout << listados[i] << ", ";
  }
  cout << listados[i] << ".";
}

void Hangman::hearts() {
  cout << red;
  for (int i=0; i<lives; i++)
    cout << '*';
  cout << white;
}

void Hangman::convert(string& s) {
  for (int i=0; i<s.length(); i++) {
    s[i]=tolower(s[i]);
  }
  palavraHidden = palavra;
  for (int i=0; i < palavra.size(); i++)
    palavraHidden[i]='*';
}

void Hangman::check(char letra) {
  bool achou=false;
  for (int j=0; j<listados.size(); j++)
    if(letra==listados[j]) {
      achou=true;
    }
  if (achou==true) {
    Beep(100,400);
    inserir();
  }
  else {
    bool achou=false;
    for (int i=0; i < palavra.size(); ++i ) {
      if (letra == palavra[i]) {
        palavraHidden[i]=letra;
        ++acertos;
        achou = true;
        Beep(2500,250);
      }
    }

    if (achou == false) {
      lives--;
      Beep(250,250);
    }
  }
}

void Hangman::ending(int situ) {
  system("cls");
  string status;
  situ==0 ? status="\033[22;31mperdeu" : status="\033[22;32mganhou";
  gotoxy(17, 12);
  cout << "O jogo acabou. Voce " << status << white <<". A palavra era: " << palavra;
  gotoxy(0,22);
  Beep(2000,750);
}

int Hangman::continua(){
  if (lives == 0 || acertos == palavra.size()) {
    if (lives==0)
      ending(0);
    else
      ending(1);
    return 0;
  }
  else {
    return 1;
  }
}

void Hangman::status() {
  gotoxy(5, 8);
  cout << "PALAVRA ATUAL: " << yellow;
  gotoxy(20, 8);
  cout << palavraHidden;
  gotoxy(15, 13);
  cout << white << "\t\tVidas: "; hearts(); cout << "\t\tAcertos: " << acertos;
}




main () {
  Hangman partida;
  //partida.typeWord();
  partida.pickWord();
  do {
    partida.inserir();
  } while (partida.continua());
}
