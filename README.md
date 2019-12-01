# Jeu de la Vie - projet S3

## Lancement du jeu

### Générer l'executable

* Mode Graphique : `make`
* Mode Texte : `make MODE=TEXTE`

La commande `make clean` doit être exécutée avant de recompiler dans un autre mode (Texte - Graphique).

### Facultatif

* Générer la documentation : `make doxygen`
* Générer l'archive avec le code source, le Doxyfile et le makefile : `make dist`

### Execution du programme

Le jeu se lance dans un terminal en entrant la commande : `./main <chemin_grille>`.

*Exemple :*

    ./main grilles/grille1.txt

### Comment jouer ?

#### Mode Texte

* Evoluer : `\n`
* Activer/désactiver le vieillissement : `v`
* Activer/désactiver le voisinage cyclique : `c`
* Calculer la période d'oscillation : `o`
* Charger une nouvelle grille : `n`
* Quitter : `q`

La période d'oscillation est initialisée à 0 et reste affichée ainsi si elle n'existe pas.

#### Mode Graphique

Les commandes sont les mêmes excepté pour :

* Evoluer : `clic-gauche`
* Quitter : `clic-droit`

La période d'oscillation n'est pas affichée de base et ne s'affichera uniquement si elle existe.

Il est possible de saisir le chemin vers une nouvelle grille directement dans la fenêtre graphique.

## Informations importantes

En mode Texte, le terminal devra être mis en plein écran pour éviter tout problème d'affichage.

La saisie d'une nouvelle grille se fait de la même manière qu'au lancement du programme : il faut renseigner le chemin vers une nouvelle grille.

Les grilles de base se trouvent dans le dossier *grilles/*.

## Versions

Version **X**.**Y**.**Z** :

* **X** : niveau du Jeu de la Vie.
* **Y** : ajouts de fonctionnalités.
* **Z** : corrections de bugs, modifications mineures.

La dernière version disponible pour un niveau du Jeu de la Vie correspond à sa version la plus stable.
**La dernière version disponible du projet correspond à sa forme la plus aboutie**.
