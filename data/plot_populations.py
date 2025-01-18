#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

# Lecture des données
data = np.loadtxt('data/population_stats.txt')
iterations = data[:, 0]
proies = data[:, 1]
predateurs = data[:, 2]

# Création du graphique
plt.figure(figsize=(10, 6))
plt.plot(iterations, proies, 'g-', label='Proies', linewidth=2)
plt.plot(iterations, predateurs, 'r-', label='Prédateurs', linewidth=2)
plt.grid(True)
plt.xlabel('Itérations')
plt.ylabel('Population')
plt.title('Évolution des populations dans l\'écosystème')
plt.legend()

# Sauvegarde du graphique
plt.savefig('data/evolution_populations.png')
