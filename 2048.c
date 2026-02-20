#include<stdio.h>

#include<curses.h>  // biblioteca ncurses

#include<string.h>

#include<stdlib.h>

#include<time.h>

#define KEYBOARD 0

//ascunde meniul
void hide_menu(WINDOW * wnd_p) {
  wclear(wnd_p);
  wrefresh(wnd_p);
}

//genereaza un 2 sau un 4 pe o pozitie aleatorie din matrice
void generare(int a[4][4]) {
  int p, copie_p;
  int linie, coloana;
  p = rand();
  copie_p = p % 2;
  if (copie_p == 1)
    copie_p = copie_p + 1;
  else if (copie_p == 0)
    copie_p = copie_p + 4;
  //verifica pozitia sa fie nula pentru a genera alt numar
  do {
    linie = rand() % 4;
    coloana = rand() % 4;
  } while (a[linie][coloana] != 0);
  //matricea va fi ulterior furnizata interfetei grafice
  a[linie][coloana] = copie_p;
}

//realizeaza miscarea in sus pentru joc, echivalenta apasarii tastei 'w'
int miscare_in_sus(int a[4][4]) {
  int i, j;
  //S retine si adauga la scorul matricei
  int S = 0;
  for (j = 0; j < 4; j++) {
    i = 0;
    //se incearca orice combinatie pentru eventualele mutari
    while (i < 3) {
      if (a[i][j] == a[i + 1][j] && a[i][j] != 0) {
        if (i == 0) {
          a[0][j] = a[i][j] + a[i + 1][j];
          if (a[2][j] != 0) {
            a[1][j] = a[2][j];
            a[2][j] = a[3][j];
            a[3][j] = 0;
          } else if (a[2][j] == 0 && a[3][j] != 0) {
            a[1][j] = a[3][j];
            a[3][j] = 0;
          } else if (a[2][j] == 0 && a[3][j] == 0) {
            a[1][j] = 0;
          }
          S = S + a[0][j];
        } else if (i == 1) {
          a[1][j] = a[i][j] + a[i + 1][j];
          if (a[3][j] != 0)
            a[2][j] = a[3][j];
          else a[2][j] = 0;
          a[3][j] = 0;
          if (a[0][j] == 0) {
            a[0][j] = a[1][j];
            a[1][j] = a[2][j];
            a[2][j] = a[3][j];
            a[3][j] = 0;
          }
          S = S + a[1][j];
        } else if (i == 2) {
          a[2][j] = a[i][j] + a[i + 1][j];
          a[3][j] = 0;
          if (a[0][j] == 0 && a[1][j] == 0) {
            a[0][j] = a[2][j];
            a[2][j] = 0;
          }
          if (a[0][j] != 0 && a[1][j] == 0) {
            a[1][j] = a[2][j];
            a[2][j] = 0;
          }
          S = S + a[2][j];
        }
      } else if (a[i][j] == a[i + 2][j] && a[i][j] != 0 && a[i + 1][j] == 0) {
        if (i == 0) {
          a[0][j] = a[i][j] + a[i + 2][j];
          if (a[3][j] != 0)
            a[1][j] = a[3][j];
          else a[1][j] = 0;
          a[2][j] = 0;
          a[3][j] = 0;
          S = S + a[0][j];
        } else if (i == 1) {
          a[1][j] = a[i][j] + a[i + 2][j];
          a[2][j] = 0;
          a[3][j] = 0;
          if (a[0][j] == 0) {
            a[0][j] = a[1][j];
            a[1][j] = 0;
          }
          S = S + a[1][j];
        }
      } else if (a[i][j] == a[i + 3][j] && a[i][j] != 0 && a[i + 3][j] != 0 
      && a[i + 1][j] == 0 && a[i + 2][j] == 0) {
        if (i == 0) {
          a[0][j] = a[i][j] + a[i + 3][j];
          a[3][j] = 0;
          S = S + a[0][j];
        }
    } else if (a[i][j] != a[i + 2][j] && a[i][j] != 0 && a[i + 2][j] != 0 
    && a[i + 1][j] == 0) {
        if (i == 0) {
          a[1][j] = a[2][j];
          a[2][j] = 0;
          if (a[3][j] != 0) {
            a[2][j] = a[3][j];
            a[3][j] = 0;
          }
        } else if (i == 1) {
          a[2][j] = a[3][j];
          a[3][j] = 0;
          if (a[0][j] == 0) {
            a[0][j] = a[1][j];
            a[1][j] = a[2][j];
            a[2][j] = 0;
          }
        }
      } else if (a[i][j] != a[i + 3][j] && a[i][j] != 0 && a[i + 3][j] != 0
       && a[i + 1][j] == 0 && a[i + 2][j] == 0) {
        if (i == 0) {
          a[1][j] = a[i + 3][j];
          a[i + 3][j] = 0;
        }
      } else if (a[0][j] == 0) {
        if (a[1][j] != 0 && a[2][j] == 0 && a[3][j] == 0) {
          a[0][j] = a[1][j];
          a[1][j] = 0;
        } else if (a[1][j] == 0 && a[2][j] != 0 && a[3][j] == 0) {
          a[0][j] = a[2][j];
          a[2][j] = 0;
        } else if (a[1][j] == 0 && a[2][j] == 0 && a[3][j] != 0) {
          a[0][j] = a[3][j];
          a[3][j] = 0;
        } else if (a[1][j] != 0 && a[2][j] != 0 && a[3][j] != 0 && 
        a[1][j] != a[2][j] && a[1][j] != a[3][j] && a[2][j] != a[3][j]) {
          a[0][j] = a[1][j];
          a[1][j] = a[2][j];
          a[2][j] = a[3][j];
          a[3][j] = 0;
        } else if (a[1][j] != 0 && a[2][j] != 0 && a[3][j] != 0 
        && a[1][j] == a[2][j] && a[1][j] != a[3][j]) {
          a[0][j] = a[1][j] + a[2][j];
          a[1][j] = a[3][j];
          a[2][j] = 0;
          a[3][j] = 0;
          S = S + a[0][j];
        } else if (a[1][j] != 0 && a[2][j] != 0 && a[3][j] != 0
         && a[1][j] != a[2][j] && a[1][j] == a[3][j]) {
          a[0][j] = a[1][j];
          a[1][j] = a[2][j];
          a[2][j] = a[3][j];
          a[3][j] = 0;
        } else if (a[1][j] != 0 && a[2][j] != 0 && a[3][j] != 0 
        && a[3][j] == a[2][j] && a[1][j] != a[3][j]) {
          a[0][j] = a[1][j];
          a[1][j] = a[2][j] + a[3][j];
          a[2][j] = 0;
          a[3][j] = 0;
          S = S + a[1][j];
        } else if (a[1][j] != 0 && a[2][j] == 0 && a[3][j] != 0 
        && a[1][j] == a[3][j]) {
          a[0][j] = a[1][j] + a[3][j];
          a[1][j] = 0;
          a[3][j] = 0;
        } else if (a[1][j] == 0 && a[2][j] != 0 && a[3][j] != 0 
        && a[2][j] == a[3][j]) {
          a[0][j] = a[2][j] + a[3][j];
          a[1][j] = 0;
          a[2][j] = 0;
          a[3][j] = 0;
        } else if (a[1][j] == 0 && a[2][j] != 0 && a[3][j] != 0 
        && a[2][j] != a[3][j]) {
          a[0][j] = a[2][j];
          a[1][j] = a[3][j];
          a[2][j] = 0;
          a[3][j] = 0;
        } else if (a[1][j] != 0 && a[2][j] != 0 && a[3][j] == 0 
        && a[1][j] != a[2][j]) {
          a[0][j] = a[1][j];
          a[1][j] = a[2][j];
          a[2][j] = 0;
        }
      }
      i++;
    }
  }
  return S;
}

//functia este echivalenta cu cea de mai sus, dar testeaza si realizeaza
//mutarile in jos (tasta 's')
int miscare_in_jos(int a[4][4]) {
  int i, j;
  int S = 0;
  for (j = 0; j < 4; j++) {
    i = 3;
    while (i > 0) {
      if (a[i][j] == a[i - 1][j] && a[i][j] != 0) {
        if (i == 3) {
          a[3][j] = a[i][j] + a[i - 1][j];
          if (a[1][j] != 0) {
            a[2][j] = a[1][j];
            a[1][j] = a[0][j];
            a[0][j] = 0;
          } else if (a[1][j] == 0 && a[0][j] != 0) {
            a[2][j] = a[0][j];
            a[0][j] = 0;
          } else if (a[1][j] == 0 && a[0][j] == 0) {
            a[2][j] = 0;
            a[0][j] = 0;
          }
          S = S + a[3][j];
        } else if (i == 2) {
          a[2][j] = a[i][j] + a[i - 1][j];
          if (a[0][j] != 0)
            a[1][j] = a[0][j];
          else a[1][j] = 0;
          a[0][j] = 0;
          if (a[3][j] == 0) {
            a[3][j] = a[2][j];
            a[2][j] = a[1][j];
            a[1][j] = a[0][j];
            a[0][j] = 0;
          }
          S = S + a[2][j];
        } else if (i == 1) {
          a[1][j] = a[i][j] + a[i - 1][j];
          a[0][j] = 0;
          if (a[0][j] == 0 && a[1][j] == 0) {
            a[3][j] = a[1][j];
            a[1][j] = 0;
          }
          if (a[0][j] != 0 && a[1][j] == 0) {
            a[2][j] = a[1][j];
            a[1][j] = 0;
          }
          S = S + a[1][j];
        }
      } else if (a[i][j] == a[i - 2][j] && a[i][j] != 0 && a[i - 1][j] == 0) {
        if (i == 3) {
          a[3][j] = a[i][j] + a[i - 2][j];
          if (a[0][j] != 0)
            a[2][j] = a[0][j];
          else a[2][j] = 0;
          a[1][j] = 0;
          a[0][j] = 0;
          S = S + a[3][j];
        } else if (i == 2) {
          a[2][j] = a[i][j] + a[i - 2][j];
          a[1][j] = 0;
          a[0][j] = 0;
          if (a[3][j] == 0) {
            a[3][j] = a[2][j];
            a[2][j] = 0;
          }
          S = S + a[2][j];
        }
      } else if (a[i][j] == a[i - 3][j] && a[i][j] != 0 && a[i - 3][j] != 0
       && a[i - 1][j] == 0 && a[i - 2][j] == 0) {
        if (i == 3) {
          a[3][j] = a[i][j] + a[i - 3][j];
          a[0][j] = 0;
          S = S + a[3][j];
        }
      } else if (a[i][j] != a[i - 2][j] && a[i][j] != 0 && a[i - 2][j] != 0 
      && a[i - 1][j] == 0) {
        if (i == 3) {
          a[2][j] = a[1][j];
          a[1][j] = 0;
          if (a[0][j] != 0) {
            a[1][j] = a[0][j];
            a[0][j] = 0;
          }
        } else if (i == 2) {
          a[1][j] = a[0][j];
          a[0][j] = 0;
          if (a[3][j] == 0) {
            a[3][j] = a[2][j];
            a[2][j] = a[1][j];
            a[1][j] = 0;
          }
        }
      } else if (a[i][j] != a[i - 3][j] && a[i][j] != 0 && a[i - 3][j] != 0 
      && a[i - 1][j] == 0 && a[i - 2][j] == 0) {
        if (i == 3) {
          a[2][j] = a[i - 3][j];
          a[i - 3][j] = 0;
        }
      } else if (a[3][j] == 0) //0020  
      {
        if (a[2][j] != 0 && a[1][j] == 0 && a[0][j] == 0) {
          a[3][j] = a[2][j];
          a[2][j] = 0;
        } else if (a[2][j] == 0 && a[1][j] != 0 && a[0][j] == 0) {
          a[3][j] = a[1][j];
          a[1][j] = 0;
        } else if (a[2][j] == 0 && a[1][j] == 0 && a[0][j] != 0) {
          a[3][j] = a[0][j];
          a[0][j] = 0;
        } else if (a[2][j] != 0 && a[1][j] != 0 && a[0][j] != 0 && 
        a[2][j] != a[1][j] && a[2][j] != a[0][j] && a[1][j] != a[0][j]) {
          a[3][j] = a[2][j];
          a[2][j] = a[1][j];
          a[1][j] = a[0][j];
          a[0][j] = 0;
        } else if (a[2][j] != 0 && a[1][j] != 0 && a[0][j] != 0 
        && a[2][j] == a[1][j] && a[2][j] != a[0][j]) {
          a[3][j] = a[2][j] + a[1][j];
          a[2][j] = a[0][j];
          a[1][j] = 0;
          a[0][j] = 0;
          S = S + a[3][j];
        } else if (a[2][j] != 0 && a[1][j] != 0 && a[0][j] != 0 
        && a[2][j] != a[1][j] && a[2][j] == a[0][j]) {
          a[3][j] = a[2][j];
          a[2][j] = a[1][j];
          a[1][j] = a[0][j];
          a[0][j] = 0;
        } else if (a[2][j] != 0 && a[1][j] != 0 && a[0][j] != 0 
        && a[0][j] == a[1][j] && a[2][j] != a[0][j]) {
          a[3][j] = a[2][j];
          a[2][j] = a[1][j] + a[0][j];
          a[1][j] = 0;
          a[0][j] = 0;
          S = S + a[2][j];
        } else if (a[2][j] != 0 && a[1][j] == 0 && a[0][j] != 0 
        && a[2][j] == a[0][j]) {
          a[3][j] = a[2][j] + a[0][j];
          a[2][j] = 0;
          a[0][j] = 0;
          S = S + a[3][j];
        } else if (a[2][j] == 0 && a[1][j] != 0 && a[0][j] != 0 
        && a[1][j] == a[0][j]) {
          a[3][j] = a[1][j] + a[0][j];
          a[2][j] = 0;
          a[1][j] = 0;
          a[0][j] = 0;
          S = S + a[3][j];
        } else if (a[2][j] == 0 && a[1][j] != 0 && a[0][j] != 0 
        && a[1][j] != a[0][j]) {
          a[3][j] = a[1][j];
          a[2][j] = a[0][j];
          a[1][j] = 0;
          a[0][j] = 0;
        } else if (a[2][j] != 0 && a[1][j] != 0 && a[0][j] == 0 
        && a[2][j] != a[1][j]) {
          a[3][j] = a[2][j];
          a[2][j] = a[1][j];
          a[1][j] = 0;
        }
      }
      i--;
    }
  }
  return S;
}

//functia este echivalenta cu cea de mai sus, dar testeaza si realizeaza
//mutarile in stanga (tasta 'a')
int miscare_in_stanga(int a[4][4]) {
  int i, j;
  int S = 0;
  for (i = 0; i < 4; i++) {
    j = 0;
    while (j < 3) {
      if (a[i][j] == a[i][j + 1] && a[i][j] != 0) {
        if (j == 0) {
          a[i][0] = a[i][j] + a[i][j + 1];
          if (a[i][2] != 0) {
            a[i][1] = a[i][2];
            a[i][2] = a[i][3];
            a[i][3] = 0;
          } else if (a[i][2] == 0 && a[i][3] != 0) {
            a[i][1] = a[i][3];
            a[i][3] = 0;
          } else if (a[i][2] == 0 && a[i][3] == 0) {
            a[i][1] = 0;
          }
          S = S + a[i][0];
        } else if (j == 1) {
          a[i][1] = a[i][j] + a[i][j + 1];
          if (a[i][3] != 0)
            a[i][2] = a[i][3];
          else a[i][2] = 0;
          a[i][3] = 0;
          if (a[i][0] == 0) {
            a[i][0] = a[i][1];
            a[i][1] = a[i][2];
            a[i][2] = a[i][3];
            a[i][3] = 0;
          }
          S = S + a[i][1];
        } else if (j == 2) {
          a[i][2] = a[i][j] + a[i][j + 1];
          a[i][3] = 0;
          if (a[i][0] == 0 && a[i][1] == 0) {
            a[i][0] = a[i][2];
            a[i][2] = 0;
          }
          if (a[i][0] != 0 && a[i][1] == 0) {
            a[i][1] = a[i][2];
            a[i][2] = 0;
          }
          S = S + a[i][2];
        }
      } else if (a[i][j] == a[i][j + 2] && a[i][j] != 0 && a[i][j + 1] == 0) {
        if (j == 0) {
          a[i][0] = a[i][j] + a[i][j + 2];
          if (a[i][3] != 0)
            a[i][1] = a[i][3];
          else a[i][1] = 0;
          a[i][2] = 0;
          a[i][3] = 0;
          S = S + a[i][0];
        } else if (j == 1) {
          a[i][1] = a[i][j] + a[i][j + 2];
          a[i][2] = 0;
          a[i][3] = 0;
          if (a[i][0] == 0) {
            a[i][0] = a[i][1];
            a[i][1] = 0;
          }
          S = S + a[i][1];
        }
      } else if (a[i][j] == a[i][j + 3] && a[i][j] != 0 && a[i][j + 3] != 0 
     && a[i][j + 1] == 0 && a[i][j + 2] == 0) {
        if (j == 0) {
          a[i][0] = a[i][j] + a[i][j + 3];
          a[i][3] = 0;
          S = S + a[i][0];
        }
      } else if (a[i][j] != a[i][j + 2] && a[i][j] != 0 && a[i][j + 2] != 0
       && a[i][j + 1] == 0) {
        if (j == 0) {
          a[i][1] = a[i][2];
          a[i][2] = 0;
          if (a[i][3] != 0) {
            a[i][2] = a[i][3];
            a[i][3] = 0;
          }
        } else if (j == 1) {
          a[i][2] = a[i][3];
          a[i][3] = 0;
          if (a[i][0] == 0) {
            a[i][0] = a[i][1];
            a[i][1] = a[i][2];
            a[i][2] = 0;
          }
        }
      } else if (a[i][j] != a[i][j + 3] && a[i][j] != 0 && a[i][j + 3] != 0 
      && a[i][j + 1] == 0 && a[i][j + 2] == 0) {
        if (j == 0) {
          a[i][1] = a[i][j + 3];
          a[i][j + 3] = 0;
        }
      } else if (a[i][0] == 0) {
        if (a[i][1] != 0 && a[i][2] == 0 && a[i][3] == 0) {
          a[i][0] = a[i][1];
          a[i][1] = 0;
        } else if (a[i][1] == 0 && a[i][2] != 0 && a[i][3] == 0) {
          a[i][0] = a[i][2];
          a[i][2] = 0;
        } else if (a[i][1] == 0 && a[i][2] == 0 && a[i][3] != 0) {
          a[i][0] = a[i][3];
          a[i][3] = 0;
        } else if (a[i][1] != 0 && a[i][2] != 0 && a[i][3] != 0 
        && a[i][1] != a[i][2] && a[i][1] != a[i][3] && a[i][2] != a[i][3]) {
          a[i][0] = a[i][1];
          a[i][1] = a[i][2];
          a[i][2] = a[i][3];
          a[i][3] = 0;
        } else if (a[i][1] != 0 && a[i][2] != 0 && a[i][3] != 0 
        && a[i][1] == a[i][2] && a[i][1] != a[i][3]) {
          a[i][0] = a[i][1] + a[i][2];
          a[i][1] = a[i][3];
          a[i][2] = 0;
          a[i][3] = 0;
          S = S + a[i][0];
        } else if (a[i][1] != 0 && a[i][2] != 0 && a[i][3] != 0
         && a[i][1] != a[i][2] && a[i][1] == a[i][3]) {
          a[i][0] = a[i][1];
          a[i][1] = a[i][2];
          a[i][2] = a[i][3];
          a[i][3] = 0;
        } else if (a[i][1] != 0 && a[i][2] != 0 && a[i][3] != 0 
        && a[i][3] == a[i][2] && a[i][1] != a[i][3]) {
          a[i][0] = a[i][1];
          a[i][1] = a[i][2] + a[i][3];
          a[i][2] = 0;
          a[i][3] = 0;
          S = S + a[i][1];
        } else if (a[i][1] != 0 && a[i][2] == 0 && a[i][3] != 0 
        && a[i][1] == a[i][3]) {
          a[i][0] = a[i][1] + a[i][3];
          a[i][1] = 0;
          a[i][3] = 0;
          S = S + a[i][0];
        } else if (a[i][1] == 0 && a[i][2] != 0 && a[i][3] != 0 
        && a[i][2] == a[i][3]) {
          a[i][0] = a[i][2] + a[i][3];
          a[i][1] = 0;
          a[i][2] = 0;
          a[i][3] = 0;
          S = S + a[i][0];
        } else if (a[i][1] == 0 && a[i][2] != 0 && a[i][3] != 0 
        && a[i][2] != a[i][3]) {
          a[i][0] = a[i][2];
          a[i][1] = a[i][3];
          a[i][2] = 0;
          a[i][3] = 0;
        } else if (a[i][1] != 0 && a[i][2] != 0 && a[i][3] == 0 
        && a[i][1] != a[i][2]) {
          a[i][0] = a[i][1];
          a[i][1] = a[i][2];
          a[i][2] = 0;
        }
      }
      j++;
    }
  }
  return S;
}

//functia este echivalenta cu cea de mai sus, dar testeaza si realizeaza
//mutarile in dreapta (tasta 'd')
int miscare_in_dreapta(int a[4][4]) {
  int i, j;
  int S = 0;
  for (i = 0; i < 4; i++) {
    j = 3;
    while (j > 0) {
      if (a[i][j] == a[i][j - 1] && a[i][j] != 0) {
        if (j == 3) {
          a[i][3] = a[i][j] + a[i][j - 1];
          if (a[i][1] != 0) {
            a[i][2] = a[i][1];
            a[i][1] = a[i][0];
            a[i][0] = 0;
          } else if (a[i][1] == 0 && a[i][0] != 0) {
            a[i][2] = a[i][0];
            a[i][0] = 0;
          } else if (a[i][1] == 0 && a[i][0] == 0) {
            a[i][2] = 0;
          }
          S = S + a[i][3];
        } else if (j == 2) {
          a[i][2] = a[i][j] + a[i][j - 1];
          if (a[i][2] != 0)
            a[i][1] = a[i][0];
          else a[i][1] = 0;
          a[i][0] = 0;
          if (a[i][3] == 0) {
            a[i][3] = a[i][2];
            a[i][2] = a[i][1];
            a[i][1] = a[i][0];
            a[i][0] = 0;
          }
          S = S + a[i][2];
        } else if (j == 1) {
          a[i][1] = a[i][j] + a[i][j - 1];
          a[i][0] = 0;
          if (a[i][3] == 0 && a[i][2] == 0) {
            a[i][3] = a[i][1];
            a[i][1] = 0;
          }
          if (a[i][3] != 0 && a[i][2] == 0) {
            a[i][2] = a[i][1];
            a[i][1] = 0;
          }
          S = S + a[i][1];
        }
      } else if (a[i][j] == a[i][j - 2] && a[i][j] != 0 && a[i][j - 1] == 0) {
        if (j == 3) {
          a[i][3] = a[i][j] + a[i][j - 2];
          if (a[i][0] != 0)
            a[i][2] = a[i][0];
          else a[i][2] = 0;
          a[i][1] = 0;
          a[i][0] = 0;
          S = S + a[i][3];
        } else if (j == 2) {
          a[i][2] = a[i][j] + a[i][j - 2];
          a[i][1] = 0;
          a[i][0] = 0;
          if (a[i][3] == 0) {
            a[i][3] = a[i][2];
            a[i][2] = 0;
          }
          S = S + a[i][2];
        }
      } else if (a[i][j] == a[i][j - 3] && a[i][j] != 0 && a[i][j - 3] != 0 
      && a[i][j - 1] == 0 && a[i][j - 2] == 0) {
        if (j == 3) {
          a[i][3] = a[i][j] + a[i][j - 3];
          a[i][0] = 0;
          S = S + a[i][3];
        }
      } else if (a[i][j] != a[i][j - 2] && a[i][j] != 0 && a[i][j - 2] != 0
       && a[i][j - 1] == 0) {
        if (j == 3) {
          a[i][2] = a[i][1];
          a[i][1] = 0;
          if (a[i][0] != 0) {
            a[i][1] = a[i][0];
            a[i][0] = 0;
          }
        } else if (j == 2) {
          a[i][1] = a[i][0];
          a[i][0] = 0;
          if (a[i][3] == 0) {
            a[i][3] = a[i][2];
            a[i][2] = a[i][1];
            a[i][1] = 0;
          }
        }
      } else if (a[i][j] != a[i][j - 3] && a[i][j] != 0 && a[i][j - 3] != 0 
      && a[i][j - 1] == 0 && a[i][j - 2] == 0) {
        if (j == 3) {
          a[i][2] = a[i][j - 3];
          a[i][j - 3] = 0;
        }
      } else if (a[i][3] == 0) {
        if (a[i][2] != 0 && a[i][1] == 0 && a[i][0] == 0) {
          a[i][3] = a[i][2];
          a[i][2] = 0;
        } else if (a[i][2] == 0 && a[i][1] != 0 && a[i][0] == 0) {
          a[i][3] = a[i][1];
          a[i][1] = 0;
        } else if (a[i][2] == 0 && a[i][1] == 0 && a[i][0] != 0) {
          a[i][3] = a[i][0];
          a[i][0] = 0;
        } else if (a[i][2] != 0 && a[i][1] != 0 && a[i][0] != 0 && 
        a[i][2] != a[i][1] && a[i][2] != a[i][0] && a[i][1] != a[i][0]) {
          a[i][3] = a[i][2];
          a[i][2] = a[i][1];
          a[i][1] = a[i][0];
          a[i][0] = 0;
        } else if (a[i][2] != 0 && a[i][1] != 0 && a[i][0] != 0 &&
         a[i][2] == a[i][1] && a[i][2] != a[i][0]) {
          a[i][3] = a[i][2] + a[i][1];
          a[i][2] = a[i][0];
          a[i][1] = 0;
          a[i][0] = 0;
          S = S + a[i][3];
        } else if (a[i][2] != 0 && a[i][1] != 0 && a[i][0] != 0 && 
        a[i][2] != a[i][1] && a[i][2] == a[i][0]) {
          a[i][3] = a[i][2];
          a[i][2] = a[i][1];
          a[i][1] = a[i][0];
          a[i][0] = 0;
        } else if (a[i][2] != 0 && a[i][1] != 0 && a[i][0] != 0 && 
        a[i][0] == a[i][1] && a[i][2] != a[i][0]) {
          a[i][3] = a[i][2];
          a[i][2] = a[i][1] + a[i][0];
          a[i][1] = 0;
          a[i][0] = 0;
          S = S + a[i][2];
        } else if (a[i][2] != 0 && a[i][1] == 0 && a[i][0] != 0 && 
        a[i][2] == a[i][0]) {
          a[i][3] = a[i][2] + a[i][0];
          a[i][2] = 0;
          a[i][0] = 0;
          S = S + a[i][3];
        } else if (a[i][2] == 0 && a[i][1] != 0 && a[i][0] != 0 &&
         a[i][1] == a[i][0]) {
          a[i][3] = a[i][1] + a[i][0];
          a[i][2] = 0;
          a[i][1] = 0;
          a[i][0] = 0;
          S = S + a[i][3];
        } else if (a[i][2] == 0 && a[i][1] != 0 && a[i][0] != 0 && 
        a[i][1] != a[i][0]) {
          a[i][3] = a[i][1];
          a[i][2] = a[i][0];
          a[i][1] = 0;
          a[i][0] = 0;
        } else if (a[i][2] != 0 && a[i][1] != 0 && a[i][0] == 0 && 
        a[i][2] != a[i][1]) {
          a[i][3] = a[i][2];
          a[i][2] = a[i][1];
          a[i][1] = 0;
        }
      }
      j--;
    }
  }
  return S;
}

//functia numara cate numere egale cu zero sunt in matrice
//functia va fi utilizata pentru a determina cea mai buna mutare
int numara_casutele_goale(int a[4][4]) {
  int i, j;
  int c = 0;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (a[i][j] == 0)
        c++;
  return c;
}

//decide singura unde sa miste jocul in functie de casutele libere
int cea_mai_buna_mutare(int a[4][4]) {
  int copie[4][4];
  int b, c, d, e;
  int i, j, k;
  int max;
  //se copiaza matricea intr-o copie
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      copie[i][j] = a[i][j];
  for (k = 97; k <= 119; k++) {
    //b,c,d,e retin numarul de casute goale ce vor aparea in urma 
    //fiecarei mutari
    if (k == 97) {
      miscare_in_stanga(copie);
      e = numara_casutele_goale(copie);
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          copie[i][j] = a[i][j];
    } else if (k == 100) {
      miscare_in_dreapta(copie);
      b = numara_casutele_goale(copie);
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          copie[i][j] = a[i][j];
    } else if (k == 115) {
      miscare_in_jos(copie);
      c = numara_casutele_goale(copie);
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          copie[i][j] = a[i][j];
    } else if (k == 119) {
      miscare_in_sus(copie);
      d = numara_casutele_goale(copie);
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          copie[i][j] = a[i][j];
    }
  }
  if (e >= b && e >= c && e >= d)
    max = 97;
  else if (b >= e && b >= c && b >= d)
    max = 100;
  else if (c >= e && c >= b && c >= d)
    max = 115;
  else if (d >= e && d >= b && d >= c)
    max = 119;

  return max; //codul ascii pentru cea mai buna mutare
}

void afisare_matrice(int a[4][4]) {
  int i, j;
  attron(A_BOLD); // ingroasa numerele 
  //culorile din stanga reprezinta cum vor fi colorate numerele din 
  //matricea din interfata grafica
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
  init_pair(6, 8, COLOR_BLACK);
  init_pair(7, 11, COLOR_BLACK);
  init_pair(8, 13, COLOR_BLACK);
  init_pair(9, 9, COLOR_BLACK);
  init_pair(10, 14, COLOR_BLACK);
  init_pair(11, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(12, COLOR_BLUE, COLOR_BLACK);
  init_pair(13, 6, COLOR_BLACK);
  init_pair(14, COLOR_BLACK, COLOR_BLACK);

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      switch (a[i][j]) {
        //daca in matrice exista o valorea nula, ea nu va fi 
        //colorata, ci o sa apara un gol, de culoarea fundalului
      case 0:
        attron(COLOR_PAIR(14));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%s", "   ");
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%s", "   ");
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%s", "   ");
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%s", "   ");
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%s", "   ");
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%s", "   ");
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%s", "   ");
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%s", "   ");
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%s", "   ");
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%s", "   ");
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%s", "   ");
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%s", "   ");
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%s", "   ");
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%s", "   ");
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%s", "   ");
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%s", "   ");
        attroff(COLOR_PAIR(14));
        break;

        //numerele cu 2 vor avea toate aceeasi culoare (magenta in
        //acest caz) cu scopul unei vizibilitati mai bune 
        //mvprintw are ca argumente coordonatele unde vor fi
        //afisate numerele din matrice
      case 2:
        attron(COLOR_PAIR(4)); //porneste culoarea magenta
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(4)); //inchide culoarea magenta
        break;

        //de aici incolo se foloseste aceeasi logica, numerele 
        //egale vor aparea cu aceeasi culoare 
      case 4:
        attron(COLOR_PAIR(5));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(5));
        break;

      case 8:
        attron(COLOR_PAIR(6));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(6));
        break;

      case 16:
        attron(COLOR_PAIR(7));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(7));
        break;

      case 32:
        attron(COLOR_PAIR(8));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(8));
        break;

      case 64:
        attron(COLOR_PAIR(3));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(3));
        break;

      case 128:
        attron(COLOR_PAIR(9));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(9));
        break;

      case 256:
        attron(COLOR_PAIR(10));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(10));
        break;

      case 512:
        attron(COLOR_PAIR(11));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(11));
        break;

      case 1024:
        attron(COLOR_PAIR(12));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(12));
        break;

      case 2048:
        attron(COLOR_PAIR(13));
        if (i == 0 && j == 0)
          mvprintw(13, 35, "%d", a[0][0]);
        if (i == 0 && j == 1)
          mvprintw(13, 45, "%d", a[0][1]);
        if (i == 0 && j == 2)
          mvprintw(13, 55, "%d", a[0][2]);
        if (i == 0 && j == 3)
          mvprintw(13, 65, "%d", a[0][3]);
        if (i == 1 && j == 0)
          mvprintw(18, 35, "%d", a[1][0]);
        if (i == 1 && j == 1)
          mvprintw(18, 45, "%d", a[1][1]);
        if (i == 1 && j == 2)
          mvprintw(18, 55, "%d", a[1][2]);
        if (i == 1 && j == 3)
          mvprintw(18, 65, "%d", a[1][3]);
        if (i == 2 && j == 0)
          mvprintw(23, 35, "%d", a[2][0]);
        if (i == 2 && j == 1)
          mvprintw(23, 45, "%d", a[2][1]);
        if (i == 2 && j == 2)
          mvprintw(23, 55, "%d", a[2][2]);
        if (i == 2 && j == 3)
          mvprintw(23, 65, "%d", a[2][3]);
        if (i == 3 && j == 0)
          mvprintw(28, 35, "%d", a[3][0]);
        if (i == 3 && j == 1)
          mvprintw(28, 45, "%d", a[3][1]);
        if (i == 3 && j == 2)
          mvprintw(28, 55, "%d", a[3][2]);
        if (i == 3 && j == 3)
          mvprintw(28, 65, "%d", a[3][3]);
        attroff(COLOR_PAIR(13));
        break;
      }
    }
  }
  attroff(A_BOLD); //se incheie boldul folosit pentru numere
}

void matricea_mea(int mat[4][4]) {
  int i, j, p;
  int best;
  int choice;
  while (1) {
    timeout(15000); //timp de 15 secunde
    choice = getch(); //choice primeste input de la tastatura
    switch (choice) {
    case 'w':
      miscare_in_sus(mat);
      generare(mat);
      afisare_matrice(mat);
      break;
    case 'a':
      miscare_in_stanga(mat);
      generare(mat);
      break;
    case 'd':
      miscare_in_dreapta(mat);
      generare(mat);
      break;
    case 's':
      miscare_in_jos(mat);
      generare(mat);
      break;
      //in cazul in care nu primeste nimic de la tastatura             
    case ERR:
      //best este codul ascii al literei ce va reprezenta cea mai
      //buna mutare
      best = cea_mai_buna_mutare(mat);
      switch (best) {
      case 119:
        miscare_in_sus(mat);
        generare(mat);
        break;
      case 97:
        miscare_in_stanga(mat);
        generare(mat);
        break;
      case 100:
        miscare_in_dreapta(mat);
        generare(mat);
        break;
      case 115:
        miscare_in_jos(mat);
        generare(mat);
        break;
      }
      break;
    }
    //se iese din while (adica se termina jocul)
    //atunci cand ecranul este umplut de numere
    p = numara_casutele_goale(mat);
    if (p == 0)
      break;
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++)
        if (mat[i][j] == 2048)
          break;
    }
    if (mat[i][j] == 2048)
      break;
  }
}

void show_menu(WINDOW * wnd_parametru) {
  int nrows, ncols, y, x;
  // dimensiunile maxime ale ecranului
  getmaxyx(wnd_parametru, ncols, nrows);
  //meniul si un desen 
  const char * text1 = "New game";
  const char * text2 = "Resume";
  const char * text3 = "Quit";
  const char * text =
    "\n    *************************************************\n\
    *                                               *\n\
    *                                               *\n\
    *                                               *\n\
    *     #######    #####   ##         #######     *\n\
    *    ##     ##  ##   ##  ##    ##  ##     ##    *\n\
    *           ## ##     ## ##    ##  ##     ##    *\n\
    *     #######  ##     ## ##    ##   #######     *\n\
    *    ##        ##     ## ######### ##     ##    *\n\
    *    ##         ##   ##        ##  ##     ##    *\n\
    *    #########   #####         ##   #######     *\n\
    *                                               *\n\
    *                                               *\n\
    *                                               *\n\
    *************************************************";
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  wbkgd(wnd_parametru, COLOR_PAIR(1));
  x = (nrows - 8) / 2;
  y = (ncols - 8) / 2;
  mvwprintw(wnd_parametru, y + 6, x - 5, "%s", text1);
  mvwprintw(wnd_parametru, y + 7, x - 5, "%s", text2);
  mvwprintw(wnd_parametru, y + 8, x - 5, "%s", text3);
  mvwprintw(wnd_parametru, y - 14, x - 5, "%s", text);
  wrefresh(wnd_parametru);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  wattron(wnd_parametru, COLOR_PAIR(2));
  mvwprintw(wnd_parametru, y + 6, x - 5, "%s", text1);
  wattroff(wnd_parametru, COLOR_PAIR(2));

}

void patrat() {
  int heigth, length, start_x, start_y;
  int i;
  heigth = 21;
  length = 40;
  start_x = 30;
  start_y = 10;
  int x = 95, y = 10;
  initscr();
  WINDOW * patrat = newwin(heigth, length, start_y, start_x);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  wrefresh(patrat);
  //ACS_HLINE si ACS_VLINE sunt linii desenate care impreuna alcatuiesc
  //un patrat de tip 4x4, respectiv tabla de joc in care 
  //se desfasoara aplicatia
  for (i = 2; i < 41; i++) {
    wattron(patrat, COLOR_PAIR(3));
    mvaddch(10, 29 + i, ACS_HLINE);
    mvaddch(30, 29 + i, ACS_HLINE);
    wattroff(patrat, COLOR_PAIR(3));
  }
  for (i = 1; i <= 19; i++) {
    wattron(patrat, COLOR_PAIR(3));
    mvaddch(10 + i, 30, ACS_VLINE);
    mvaddch(10 + i, 70, ACS_VLINE);
    wattroff(patrat, COLOR_PAIR(3));
  }
  for (i = 2; i < 41; i++) {
    wattron(patrat, COLOR_PAIR(1));
    mvaddch(15, 29 + i, ACS_HLINE);
    mvaddch(20, 29 + i, ACS_HLINE);
    mvaddch(25, 29 + i, ACS_HLINE);
    wattroff(patrat, COLOR_PAIR(1));
  }
  for (i = 1; i <= 19; i++) {
    wattron(patrat, COLOR_PAIR(1));
    mvaddch(10 + i, 40, ACS_VLINE);
    mvaddch(10 + i, 50, ACS_VLINE);
    mvaddch(10 + i, 60, ACS_VLINE);
    wattroff(patrat, COLOR_PAIR(1));
  }
  refresh();
  //ajutor pentru a se afisa data si timpul curente
  time_t now;
  time( & now);
  char * timp = ctime( & now);
  //se afiseaza comenzila, regulamentul si scorul(care va fi
  //actualizat dupa fiecare n)
  const char * leg1 = "W : Move Up";
  const char * leg2 = "A : Move Left";
  const char * leg3 = "D : Move Right";
  const char * leg4 = "S : Move Down";
  const char * leg5 = "Score : ";
  const char * leg6 = "Date and Time : ";
  const char * leg7 = "How to play?";
  const char * leg8 = "Q : Quit";
  mvprintw(y, x, "%s", leg1);
  mvprintw(y + 1, x, "%s", leg2);
  mvprintw(y + 2, x, "%s", leg3);
  mvprintw(y + 3, x, "%s", leg4);
  mvprintw(y + 8, x, "%s", leg5);
  mvprintw(y + 20, x, "%s", leg6);
  mvprintw(y + 20, x + 16, "%s", timp);
  mvprintw(y - 2, x, "%s", leg7);
  mvprintw(y + 4, x, "%s", leg8);
}

void meniu() {
  int t, a = 0;
  int c = 0;
  int i, j;
  int casute, end = 0;
  int scor, scor_total = 0;
  int joc_nou[4][4];
  int k = 1, control;
  int nrows, ncols, y, x;
  WINDOW * wnd = initscr();
  getmaxyx(wnd, ncols, nrows);
  const char * text1 = "New game";
  const char * text2 = "Resume";
  const char * text3 = "Quit";
  //singura modalitate ca desenul sa fie formatat corect
  const char * text =
    "\n    *************************************************\n\
    *                                               *\n\
    *                                               *\n\
    *                                               *\n\
    *     #######    #####   ##         #######     *\n\
    *    ##     ##  ##   ##  ##    ##  ##     ##    *\n\
    *           ## ##     ## ##    ##  ##     ##    *\n\
    *     #######  ##     ## ##    ##   #######     *\n\
    *    ##        ##     ## ######### ##     ##    *\n\
    *    ##         ##   ##        ##  ##     ##    *\n\
    *    #########   #####         ##   #######     *\n\
    *                                               *\n\
    *                                               *\n\
    *                                               *\n\
    *************************************************";

  x = (nrows - 8) / 2;
  y = (ncols - 8) / 2;
  keypad(stdscr, TRUE); // imi da voie sa folosesc sagetile
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  wattron(wnd, COLOR_PAIR(1));
  mvwprintw(wnd, y - 14, x - 5, "%s", text);
  wattroff(wnd, COLOR_PAIR(1));
  wattron(wnd, COLOR_PAIR(2));
  mvwprintw(wnd, y + 6, x - 5, "%s", text1);
  wattroff(wnd, COLOR_PAIR(2));
  //cand se umbla prin meniu, locul care este pregatit pentru a se apasa
  //ENTER (tasta de decizie) va fi colorata cu rosu pentru o mai buna
  //vizibilitate de pozitia unde ma aflu
  while (1) {
    control = getch();
    switch (control) {
    case KEY_UP:
      if (k > 1) {
        k--;
      } else if (k == 1) {
        k = 3;
      }
      break;
    case KEY_DOWN:
      if (k < 3) {
        k++;
      } else if (k == 3) {
        k = 1;
      }
      break;
    }
    switch (k) {
    case 1:
      wattron(wnd, COLOR_PAIR(2));
      mvwprintw(wnd, y + 6, x - 5, "%s", text1);
      wattroff(wnd, COLOR_PAIR(2));
      wattron(wnd, COLOR_PAIR(1));
      mvwprintw(wnd, y + 7, x - 5, "%s", text2);
      mvwprintw(wnd, y + 8, x - 5, "%s", text3);
      wattroff(wnd, COLOR_PAIR(1));
      break;

    case 2:
      wattron(wnd, COLOR_PAIR(2));
      mvwprintw(wnd, y + 7, x - 5, "%s", text2);
      wattroff(wnd, COLOR_PAIR(2));
      wattron(wnd, COLOR_PAIR(1));
      mvwprintw(wnd, y + 6, x - 5, "%s", text1);
      mvwprintw(wnd, y + 8, x - 5, "%s", text3);
      wattroff(wnd, COLOR_PAIR(1));
      break;

    case 3:
      wattron(wnd, COLOR_PAIR(2));
      mvwprintw(wnd, y + 8, x - 5, "%s", text3);
      wattroff(wnd, COLOR_PAIR(2));
      wattron(wnd, COLOR_PAIR(1));
      mvwprintw(wnd, y + 6, x - 5, "%s", text1);
      mvwprintw(wnd, y + 7, x - 5, "%s", text2);
      wattroff(wnd, COLOR_PAIR(1));
      break;
    }
    //daca se apasa "New game"
    //10 este codul ASCII pentru enter, de aici verificarea
    //control == 10
    if (control == 10 && k == 1) {
      scor = 0;
      scor_total = 0;
      //se ascunde meniul
      hide_menu(wnd);
      //se initializeaza un nou ecran
      initscr();
      int i, j;
      int joc[4][4];
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          joc[i][j] = 0;
      //inceputul jocului. tabela goala cu 2 numere (2 sau 4) generate
      srand(time(NULL));
      generare(joc);
      generare(joc);
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          joc_nou[i][j] = joc[i][j];
      afisare_matrice(joc_nou);
      patrat();
      while (1) {
        casute = 0;
        end = 0;
        a = 0;
        c = 0;
        scor = 0;
        t = getch();
        switch (t) {
        case 113:
          //daca se apasa quit se afiseaza din nou meniul,
          // se iese din tabla de joc
          endwin();
          hide_menu(wnd);
          show_menu(wnd);
          a++;
          break;
          //la apasarea tastelor de mutare, se afiseaza jocul
          //dupa ce a efectuat miscarea si scorul rezultat 
        case 119:
          scor = miscare_in_sus(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          casute = numara_casutele_goale(joc_nou);
          //intotdeauna se numara casutele libere.
          //daca toate casutele contin numere, jocul se termina
          //si se afiseaza un nou ecran cu mesajul "game over"
          mvprintw(18, 105, "%d", scor_total);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          //daca jucatorul ajunge la 2048 jocul se incheie,
          //acesta fiind declarat castigator, se afiseaza 
          //mesajul "you won"
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        case 97:
          //acelasi lucru se intampla pentru fiecare tasta
          scor = miscare_in_stanga(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          casute = numara_casutele_goale(joc_nou);
          mvprintw(18, 105, "%d", scor_total);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        case 100:
          scor = miscare_in_dreapta(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          casute = numara_casutele_goale(joc_nou);
          mvprintw(18, 105, "%d", scor_total);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        case 115:
          scor = miscare_in_jos(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          casute = numara_casutele_goale(joc_nou);
          mvprintw(18, 105, "%d", scor_total);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        }

        if (a != 0 || end != 0)
          break;
      }
    }
    //daca se apasa resume, iar jucatorul tocmai ce a iesit din
    //"new game", tasta se deblocheaza si daca este apasata se
    //ajunge la ultima matrice calculata
    if (control == 10 && k == 2 && a != 0) {
      hide_menu(wnd);
      patrat();
      refresh();
      afisare_matrice(joc_nou);
      while (1) {
        //odata ce este apasat resume, rationamentul ramane acelasi
        //si jocul se continua din punctul ramas
        a = 0;
        t = getch();
        switch (t) {
        case 113:
          endwin();
          hide_menu(wnd);
          show_menu(wnd);
          a++;
          break;
        case 119:
          scor = miscare_in_sus(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          mvprintw(18, 105, "%d", scor_total);
          casute = numara_casutele_goale(joc_nou);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        case 97:
          scor = miscare_in_stanga(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          mvprintw(18, 105, "%d", scor_total);
          casute = numara_casutele_goale(joc_nou);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        case 100:
          scor = miscare_in_dreapta(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          mvprintw(18, 105, "%d", scor_total);
          casute = numara_casutele_goale(joc_nou);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        case 115:
          scor = miscare_in_jos(joc_nou);
          scor_total = scor_total + scor;
          generare(joc_nou);
          clear();
          patrat();
          refresh();
          afisare_matrice(joc_nou);
          mvprintw(18, 105, "%d", scor_total);
          casute = numara_casutele_goale(joc_nou);
          if (casute == 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "Game over :(");
            end++;
          }
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
              if (joc_nou[i][j] == 2048)
                c++;
          if (c != 0) {
            clear();
            initscr();
            mvprintw(y - 2, x - 5, "%s", "You won!!!  :)");
            end++;
          }
          refresh();
          break;
        }
        if (a != 0 || end != 0)
          break;
      }
    }
    //daca se apasa quit jocul se termina si se iese din ecran
    if (control == 10 && k == 3)
      break;
  }
}
int main() {
  //in main doar se intitializeaza un ecran si se apeleaza functiile de 
  //mai sus. functiile fac toata treaba
  WINDOW * wnd = initscr();
  show_menu(wnd);
  meniu();
  endwin(); // inchide ecranul
  return 0;
}