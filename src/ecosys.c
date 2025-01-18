#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"


Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(x >= 1 && x < SIZE_X - 1);  // On évite les bordures
  assert(y >= 1 && y < SIZE_Y - 1);  // On évite les bordures
  Animal *na = creer_animal(x, y, energie);
  *liste_animal=ajouter_en_tete_animal(*liste_animal, na);
}

void enlever_animal(Animal **liste, Animal *animal) {
    if(! liste || ! animal) return;
  
  if(*liste == animal){
    *liste = (*liste)->suivant;
    free(animal);
  }

  Animal *curr = *liste;
  while(curr){
    if (curr->suivant == animal){
      curr->suivant = curr->suivant->suivant;
      free(animal);
      break;
    }
    curr = curr->suivant;
  }
}

Animal* liberer_liste_animaux(Animal *liste) {
  while(liste){
    Animal *suivant = liste->suivant;
    free(liste);
    liste = suivant;
  }
  return NULL;
}

unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

unsigned int compte_animal_it(Animal *la) {
  unsigned int cpt = 0;
  while (la != NULL) {
    cpt++;
    la = la->suivant;
  }
  return cpt;
}

void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur, int monde[SIZE_X][SIZE_Y]) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred=0,nbproie=0;

  /* on initialise le tableau */
  for(i=0; i<SIZE_X ;i++){
    for(j=0;j<SIZE_Y;j++){
      if ((i>0||i<SIZE_X-1)&&(j==0||j==SIZE_Y-1)){
        ecosys[i][j]='-';      
      }
      else {
        ecosys[i][j]=' ';
      }
      if (((i==0)||(i==SIZE_X-1))&&((j>0)||(j<SIZE_Y-1))){
        ecosys[i][j]='|';
      }
      if (((i==0)||(i==SIZE_X-1))&&((j==0)||(j==SIZE_Y-1))){
        ecosys[i][j]='+';   
      }
    }
  }
         
  /* on ajoute les proies */
  while(liste_proie){
    ecosys[liste_proie->x][liste_proie->y]='*';
    liste_proie=liste_proie->suivant;
    nbproie++;
  }
 
  /* on ajoute les predateurs */
  while(liste_predateur){
    if(ecosys[liste_predateur->x][liste_predateur->y]=='*'){
      ecosys[liste_predateur->x][liste_predateur->y]='@';
    }
    else{
      ecosys[liste_predateur->x][liste_predateur->y]='O';
    }
    nbpred++;
    liste_predateur=liste_predateur->suivant;
  }

  /* on affiche le tableau */
  printf("Nb proies (" ANSI_COLOR_BLUE "*" ANSI_COLOR_RESET ") : %5d\tNb predateurs (" ANSI_COLOR_RED "O" ANSI_COLOR_RESET ") : %5d\n", nbproie, nbpred);
  for(i=0;i<SIZE_Y;i++){
    for(j=0;j<SIZE_X;j++){
      if(ecosys[j][i] == '*'){
        printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, ecosys[j][i]);
      }
      else if(ecosys[j][i] == 'O' || ecosys[j][i] == '@'){
        printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, ecosys[j][i]);
      }
      else if(ecosys[j][i] == ' ' && monde[j][i] > 0){
        printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
      }
      else{
        printf("%c", ecosys[j][i]);
      }
    }
    printf("\n");
  }
}

void clear_screen(void) {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}


void bouger_animaux(Animal *la) {
  while(la){
    if(rand()/RAND_MAX < p_ch_dir){
        la->dir[0] = rand() % 3 - 1;
    }
    if(rand()/RAND_MAX < p_ch_dir){
        la->dir[1] = rand() % 3 - 1;
    }
    
    // Calculer la nouvelle position
    int new_x = la->x - la->dir[1];
    int new_y = la->y - la->dir[0];
    
    // Vérifier si la nouvelle position est valide (pas sur les bordures)
    if(new_x >= 1 && new_x < SIZE_X - 1 && new_y >= 1 && new_y < SIZE_Y - 1) {
        la->x = new_x;
        la->y = new_y;
    } else {
        // Si on touche une bordure, on inverse la direction
        la->dir[0] = -la->dir[0];
        la->dir[1] = -la->dir[1];
    }
    
    la = la->suivant;
  }
}

void reproduce(Animal **liste_animal, float p_reproduce) {
  assert(liste_animal);
  Animal *ani = *liste_animal;
  while(ani){
    if(rand()/RAND_MAX < p_reproduce){
      ani->energie = (ani->energie)/2;
      ajouter_animal(ani->x, ani->y, ani->energie, liste_animal);
    }
    ani=ani->suivant;
  }

}

void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  assert(liste_proie);
  Animal *sup, *p =*liste_proie;
  bouger_animaux(*liste_proie);
  while (p){
    p->energie--;
    if(monde[p->x][p->y] >= 0) {
      p->energie = p->energie + monde[p->x][p->y];
      monde[p->x][p->y] = temps_repousse_herbe;
    }
    if(p->energie < 0){
      sup = p;
      p = p->suivant;
      enlever_animal(liste_proie, sup);
    }else
      p=p->suivant;

  }
  reproduce(liste_proie, p_reproduce_proie);
}

Animal* animal_en_XY(Animal *l, int x, int y) {
  while(l){
    if (l->x == x && l->y == y){
      return l;
    }
    l = l->suivant;
  }
  return NULL;
}

void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  assert(liste_predateur);
  assert(liste_proie);
  Animal *sup, *p =*liste_predateur;
  bouger_animaux(*liste_predateur);
  while (p) {
    p->energie--;
    sup = animal_en_XY(*liste_proie, p->x, p->y);
    if(sup) {
      p->energie = p->energie + sup->energie;
      enlever_animal(liste_proie, sup);
    }
    if(p->energie < 0){
      sup = p;
      p = p->suivant;
      enlever_animal(liste_predateur, sup);
    }else
      p =p->suivant;

  }
  reproduce(liste_predateur, p_reproduce_predateur);
}

void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  int i,j;
  for(i=0 ; i<SIZE_X ; i++){
    for(j=0 ; j < SIZE_Y ; j++){
      monde[i][j]++;
    }
  }
}
