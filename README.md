# Simulation Écosystème

Ce projet simule un écosystème simple avec des interactions entre proies et prédateurs, similaire au modèle de Lotka-Volterra.

## Fonctionnement

La simulation représente un écosystème avec trois composants principaux :
- **Proies** (affichées en bleu `*`) : Se nourrissent d'herbe et peuvent se reproduire
- **Prédateurs** (affichés en rouge `O`) : Chassent les proies et peuvent se reproduire
- **Herbe** (affichée en vert `.`) : Repousse après avoir été mangée

Les interactions sont les suivantes :
- Les proies perdent de l'énergie en se déplaçant et en gagnent en mangeant de l'herbe
- Les prédateurs perdent de l'énergie en se déplaçant et en gagnent en mangeant des proies
- L'herbe repousse progressivement après avoir été mangée
- Les animaux meurent si leur énergie tombe à zéro
- Les animaux peuvent se reproduire avec une certaine probabilité

## Prérequis

### Compilation
- GCC
- Make

### Visualisation
Pour la génération des graphiques, vous aurez besoin de Python 3 avec matplotlib.

Sur macOS :
```bash
brew install python-matplotlib
```

Sur Linux :
```bash
sudo apt-get install python3-matplotlib  # Pour Debian/Ubuntu
sudo dnf install python3-matplotlib      # Pour Fedora
```

Sur Windows :
```bash
pip3 install matplotlib numpy
```

## Structure du Projet

```
SimulationEcosysteme/
├── src/            # Code source
│   ├── ecosys.c
│   └── main_ecosys.c
├── include/        # Fichiers d'en-tête
│   └── ecosys.h
├── tests/          # Tests unitaires
│   └── main_tests.c
├── data/           # Données et visualisations
│   ├── plot_populations.py
│   ├── population_stats.txt    # Généré lors de l'exécution
│   └── evolution_populations.png # Généré lors de l'exécution
├── build/          # Fichiers objets compilés
├── bin/           # Exécutables
└── Makefile       # Script de compilation
```

## Compilation et Exécution

### Compiler le projet
```bash
make all
```

### Exécuter la simulation
Deux options sont disponibles :

- Pour exécuter la simulation avec visualisation graphique :
```bash
make run
```

- Pour exécuter la simulation sans visualisation :
```bash
make run-sim
```

### Tests
Pour exécuter les tests unitaires :
```bash
make test
```

### Nettoyage
Pour nettoyer tous les fichiers générés :
```bash
make clean
```

## Visualisation

### Terminal
La simulation affiche en temps réel dans le terminal :
- Proies (`*`) en bleu
- Prédateurs (`O`) en rouge
- Herbe (`.`) en vert
- Bordures (`+`, `-`, `|`) en blanc
- Compteurs de population en haut de l'écran

### Graphique
Le programme génère deux types de sorties :
1. Une visualisation en temps réel dans le terminal
2. Un graphique d'évolution des populations (`data/evolution_populations.png`) basé sur les données collectées (`data/population_stats.txt`)
