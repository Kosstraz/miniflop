###### LISTE DES CHOSES A FAIRE : ######

- [HISTORY] Faire un historique fonctionnel, basique.

- [QUOTES] Interpréter les singles quotes et les doubles quotes.

- [$] Gérer les dollars (avec ou sans double quote).

- [<] Redirige l'input.

- [>] Redirige l'output.

- [<<] Redirige l'input avec un délimiteur.

- [>>] Redirige l'output en mode APPEND.

- [PIPES] Implémenter les pipes '|' (output de la commande de gauche --> input de la commande de droite).

- [ENV_VAR] Interpréter les variables d'environnements, initiées avec un dollars avant le nom (ex : $VAR).

- [$?] Retourne la valeur DE RETOUR de la dernière commande (ex : ls renvoie 0 s'il y a eu aucune erreur).

- [ctrl-C] Interpréter ce signal (SIGINT). Affiche un nouveau prompt avec une nouvelle ligne.

- [ctrl-D] Interpréter ce signal (EOF <=> End-Of-File). With a read(). Quitte le Shell actuel.

- [ctrl-\] Interpréter ce signal (SIGQUIT). Ne doit rien faire.

###### BUILTINS : ######

- [echo] Avec l'option -n. Affiche l'argument.

- [cd] Fonctionnant avec un chemin relatif et absolu.

- [pwd] Affiche le répertoire dans lequel se trouve l'utilisateur appelant.

- [export] Ajouter une variable à l'environnement shell actuel. Si 'export' ne reçoit aucune argument, affiche toutes les variables d'environnements exportées.

- [unset] Détruit une variable. Cette commande ne retourne rien --> void unset(...).

- [env] Affiche toutes les variables d'environnements. Si des arguments sont donnés, cela modifie les variables d'environnements indiquées, temporairement (le temps d'exécuter un script, ...). Exemple : "env VAR1=A VAR2=B ... ./program".

- [exit] Quitte le terminal.

###### BONUS : ######

- [||] Exécute seulement seulement la première commande valide trouvée (de gauche à droite).

- [&&] N'exécute aucune commande si l'une d'entre elles n'est pas valide. 

- [*] Doit fonctionner sur le répertoire courant.

###### QUESTIONNEMENTS : ######

