#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<sstream>
#include <fstream>
#include <bitset>

using namespace std;

int existe(string temp, string dicionario[], int j){
  for (int i = 0; i < j; i++) {
    if (dicionario[i] == temp)
      return i;
  }
  return -1;
}//serve para ver se a palavra ja existe no dicionário

string toBinario(int x){
  bitset<8> bits(x);
  return bits.to_string();
}//converete para string

long toDecimal(string x){
  bitset<8> bits(x);
  return bits.to_ulong();
}//converete para numero

void compactar(){
  FILE *entrada;
  string text = "", temp = "";
  string dicionario[1100];
  int c;
  int pos, i = 0, j = 0, x = -1;

  entrada = fopen("teste2.txt", "r+");

  ofstream saida ("teste2Compactado.txt");

  if (ferror(entrada))
    return ;

  while(!feof(entrada)){
    c = getc(entrada);
    if(c != EOF)
      text += c;
  }

  while (i < text.length()) {
    temp += text[i];
    pos = existe(temp, dicionario, j);
    if (pos == -1){
      dicionario[j] = temp;
      if(x != -1){
        c = text[i];
        saida << 1 << toBinario(x) << toBinario(c);
      }
      else{
        c = text[i];
        saida << 0 << toBinario(c);
      }

      temp = "";
      i++;
      j++;
      x = -1;
    }
    else{
      i++;
      x = pos;
    }
  }

  fclose(entrada);
}

void descompactar(){
  FILE *entrada;
  string text = "", temp = "";
  string dicionario[1100];
  char c;
  int i = 0, j = 0;

  entrada = fopen("teste2Compactado.txt", "r+");

  ofstream saida ("teste2Descompactado.txt");

  if (ferror(entrada))
    return ;

  while(!feof(entrada)){
    c = getc(entrada);
    if(c != EOF)
      text += c;
  }

  while (i < text.length()) {
    if (text[i] == '0'){
      c = toDecimal(text.substr(i+1, 8));
      saida << c;
      dicionario[j] = c;

      i += 9;
      j++;
    }
    else{
      temp = dicionario[toDecimal(text.substr(i+1, 8))];
      saida << temp;
      i += 9;

      c = toDecimal(text.substr(i, 8));
      saida << c;
      dicionario[j] = temp + c;

      i += 8;
      j++;
    }
  }

  fclose(entrada);
}

int main(void){
  int opcao;

  cout << "0: Compactar" << endl << "1: Descompactar" << endl;
  cin >> opcao;

  switch (opcao) {
    case 0: compactar();
      break;
    case 1: descompactar();
      break;
    default: cout << "Valor inválido";
  }

  return 0;
}