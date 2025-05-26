# Gestion Projet

## Auteurs

| Nom     | Prénom  | Numéro d'étudiant |
| :-----: | :-----: | :-----: |
| Zobo Nomo| Franc| 71800466 |
| Abdelli| Mohand Said| 22124465 |

## Introduction

Ce projet est le travail demander pour le 1er TP noté du cours de programmation objet avancée. On s’intéresse à la gestion de projets qui se décomposent en tâches dépendantes les unes des autres.

## Architecture

Le code source du travail se trouve dans le répertoire [src/](./src/). On y retrouvera les classes principales, les classes de Test ainsi que les classes annexes.

Les renseignements complémentaire se trouve dans le répertoire [docs/](./docs). On y trouvera notamment des renseignements sur le code dans un [rapport](./docs/report.pdf) et un [diagramme UML](./docs/diagramme-uml.png).

## Compilation

La compilation est relativement simple, il suffit simplement de lancé la commande `make` dans un terminal (situé à la racine du projet). À la suite de cette commande, 2 répertoire vont être créer:

* Le repertoire [log](.log/) contenant les fichiers debuggage.

* Le repertoire [bin](.bin/) contenant les fichiers compilé.

## Les tests

Pour lancer les tests, il y a deux solution:

1. Lancer la commande de test: \$ `make test_all`\
  pour tester toutes les classes décrites dans les [fichiers sources](./src/main/).
2. Lancer une commande de test: \$ `make test_classname` \
  pour teste le fichier source `classname`. \
  Exemple: \$ `make test_task`\
  Testera la class `Task` contenu dans ce le fichier [Task.cpp](./src/main/Task.cpp).