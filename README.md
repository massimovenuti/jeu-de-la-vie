# Jeu de la Vie

## Techniques de développement : projet S3

### Lancement du jeu

#### Avant d'executer le programme

##### Obligatoire

* Générer l'executable : `make`

##### Facultatif

* Générer la documentation : `make doc`
* Générer l'archive avec le code source, le Doxyfile et le Readme : `make dist`

#### Execution du programme

Le jeu se lance dans un terminal en entrant la commande : `main <nom_grille>` (windows) | `./main <nom_grille>` (linux).
L'extension et le chemin d'accès de la grille ne doivent pas être saisis.

*Exemple (sous linux):*

    ./main grille1

### Informations importantes

Le terminal devra être mis en plein écran pour éviter tout problème d'affichage.
La saisie d'une nouvelle grille se fait de la même manière qu'au lancement du programme ; sans chemin d'accès ni extension de fichier.
Les grilles se trouvent dans le dossier `/grilles`.

### Versions

Version **X**.**Y**.**Z** :

* **X** : niveau du Jeu de la Vie.
* **Y** : ajouts de fonctionnalités.
* **Z** : corrections de bugs, modifications mineures.

La dernière version disponible pour un niveau du Jeu de la Vie correspond à sa version la plus stable.
**La dernière version disponible du projet correspond à sa forme la plus aboutie.**
