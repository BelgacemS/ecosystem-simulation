#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

/* Paramètres globaux de l'ecosysteme */
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 1;
int temps_repousse_herbe = -15;

#define NB_PROIES 20
#define NB_PREDATEURS 20

/* Prototypes des fonctions de test */
void test_creation_animal(void);
void test_ajout_animal(void);
void test_suppression_animal(void);
void test_comptage(void);
void test_affichage(void);

/* Fonctions de test */
void test_creation_animal(void) {
    printf("\n=== Test création animal ===\n");
    Animal *animal = creer_animal(10, 20, 5.0);
    assert(animal != NULL);
    assert(animal->x == 10);
    assert(animal->y == 20);
    assert(animal->energie == 5.0);
    assert(animal->suivant == NULL);
    printf("✓ Test création animal réussi\n");
    liberer_liste_animaux(animal);
}

void test_ajout_animal(void) {
    printf("\n=== Test ajout animal ===\n");
    Animal *liste = NULL;
    ajouter_animal(5, 5, 3.0, &liste);
    assert(liste != NULL);
    assert(compte_animal_it(liste) == 1);
    
    ajouter_animal(6, 6, 4.0, &liste);
    assert(compte_animal_it(liste) == 2);
    printf("✓ Test ajout animal réussi\n");
    liberer_liste_animaux(liste);
}

void test_suppression_animal(void) {
    printf("\n=== Test suppression animal ===\n");
    Animal *animal1 = creer_animal(1, 1, 1.0);
    Animal *animal2 = creer_animal(2, 2, 2.0);
    Animal *liste = animal1;
    liste = ajouter_en_tete_animal(liste, animal2);
    
    assert(compte_animal_it(liste) == 2);
    enlever_animal(&liste, animal1);
    assert(compte_animal_it(liste) == 1);
    assert(liste->x == 2); // Vérifie que c'est bien animal2 qui reste
    printf("✓ Test suppression animal réussi\n");
    liberer_liste_animaux(liste);
}

void test_comptage(void) {
    printf("\n=== Test comptage ===\n");
    Animal *liste = NULL;
    assert(compte_animal_it(liste) == 0);
    assert(compte_animal_rec(liste) == 0);
    
    ajouter_animal(1, 1, 1.0, &liste);
    ajouter_animal(2, 2, 2.0, &liste);
    ajouter_animal(3, 3, 3.0, &liste);
    
    assert(compte_animal_it(liste) == 3);
    assert(compte_animal_rec(liste) == 3);
    printf("✓ Test comptage réussi\n");
    liberer_liste_animaux(liste);
}

void test_affichage(void) {
    printf("\n=== Test affichage ===\n");
    int monde[SIZE_X][SIZE_Y] = {0};
    Animal *proies = NULL;
    Animal *predateurs = NULL;
    
    // Ajout de quelques animaux
    ajouter_animal(5, 5, 5.0, &proies);
    ajouter_animal(10, 10, 5.0, &predateurs);
    
    // Ajout d'herbe
    monde[7][7] = 1;
    monde[8][8] = 1;
    
    printf("Test d'affichage avec couleurs :\n");
    afficher_ecosys(proies, predateurs, monde);
    
    liberer_liste_animaux(proies);
    liberer_liste_animaux(predateurs);
    printf("✓ Test affichage réussi\n");
}

int main(void) {
    printf("Démarrage des tests...\n");
    
    test_creation_animal();
    test_ajout_animal();
    test_suppression_animal();
    test_comptage();
    test_affichage();
    
    printf("\nTous les tests ont réussi !\n");
    return 0;
}
