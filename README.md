# dut_a1_iap_tables

Le but du projet est de programmer un interpréteur de commandes sur une
table de données. Huit commandes sont à programmer :


    * trois commandes de traitement d’une table :
        - création
        - destruction
        - affichage de son schéma
    * cinq commandes de manipulation des données d’une table déjà créée :
        - insertion
        - suppression
        - sélection monocritère
        - affichage d’un enregistrement donné
        - affichage de tous les enregistrements

**Quatre types de données sont manipulés dans ce projet :** 

    - les entiers (INT)
    - les réels (FLOAT)
    - les chaînes de caractères (TEXT) (Limitées par une taille MAX)
    - les dates (DATE). 

L’application doit interpréter neuf commandes (huit commandes sur la table de donnée et une commande de sortie de l’interpréteur). 
Celles-ci sont représentées sous forme de chaînes de caractères non accentuées de formats spécifiés dans ce document. 
Le caractère séparateur entre la commande et les différents champs d’information est le caractère espace.
Les commandes pourront être soit entrées en utilisant l’entrée standard (le clavier) ou par redirection d’un fichier texte sur l’entrée standard.