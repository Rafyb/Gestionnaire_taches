# Gestionnaire de taches

Url du projet : https://github.com/Rafyb/Gestionnaire_taches

## Equipe

- Johann De Almeida
- Raphaël Bauvin

## Notice d'utilisation

Compiler à l'aide de la commande `make`

Exectuer à l'aide de la commande `./progCommande` suivi de vos arguments

## Cas d'utilisation

Le programme s'éxécute en tapant dans un terminal la commande suivante :
$ `progCommande {options} [nombre repetition] [delai] [ligne de commande a executer]`

Exemple d'utilisation simple : `./progCommande 2 10 emacs` 
-> Le programme éxécutera 2 fois emacs avec 10 secondes d'écart

Cela fonctionne même avec des arguments passés à la commande
Exemple d'utilisation poussée : `./progCommande 2 10 emacs -T toto`
-> Le programme éxécutera 2 fois emacs avec l'option -T avec 10 secondes d'écart

Le programme comporte les options suivantes qui peuvent être cumulées :

 * -l ( ou -L ) qui permet d'activer les logs. Ainsi toute l'éxécution pourra se suivre dans le fichier test.log
 Exemple d'utilisation : `./progCommande -l 2 10 emacs`
 -> Le programme éxécutera 2 fois emacs avec 10 secondes d'écart et écrira une trace d'éxécution dans le fichier test.log
 
  * -p ( ou -P ) qui permet de spécifier le chemin complet du programme à utiliser
 Exemple d'utilisation : `./progCommande -p "/snap/bin/emacs" 2 10 emacs`
 -> Le programme éxécutera 2 fois emacs qui se situe dans /snap/bin/ avec 10 secondes d'écart
 
  * -h ( ou -H ) qui permet de spécifier que le temps donner est en heure
 Exemple d'utilisation : `./progCommande -h 2 1 emacs`
 -> Le programme éxécutera 2 fois emacs avec 1 heure d'écart
 
   * -m ( ou -M ) qui permet de spécifier que le temps donner est en minute
 Exemple d'utilisation : `./progCommande -m 2 20 emacs`
  -> Le programme éxécutera 2 fois emacs avec 20 minutes d'écart
 
   * -d ( ou -D ) qui permet de spécifier un temps d'attentes avant la première éxécution
 Exemple d'utilisation : `./progCommande -d 10 2 20 emacs`
  -> Le programme éxécutera 2 fois emacs, la premières fois après 10 secondes et la seconde fois avec 20 secondes d'écart
 
 
 Exemple d'utilisations cumulées : `./progCommande -l -m -d 1 -p "/snap/bin/emacs" 3 2 emacs -T toto`
  -> Le programme éxécutera 3 fois emacs qui se situe dans /snap/bin/ avec 15 minutes d'écart et écrira une trace d'éxécution dans le fichier test.log. La première éxécution se fera 1 minute après le lancement de la commande
 
