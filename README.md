###### A RAJOUTER/REGLER : ######

###### QUESTIONNEMENTS : ######

###### TERMCAP : ######
{cachetra}

- -~~~ [FT_READLINE] Faire ft_readline() ez. LE BOSS FINAL MOUAHAHH!!! ~~~

- -~~~ (*) Remplacer toutes les occurences de free_shell dans /term avec shell_exit ~~~

###### PARSING : ######
{ymanchon}

- -~~~ [QUOTES] Interpréter les singles quotes et les doubles quotes.~~~

- -~~~ [COMMANDS] Commands~~~

- -~~~ [ARGUMENTS] Arguments~~~

- -~~~ [|] Pipe, notamment quand ils sont collés aux arguments/commandes.~~~

- -~~~[||] Or, notamment quand ils sont collés aux arguments/commandes.~~~

- -~~~[&&] And, notamment quand ils sont collés aux arguments/commandes.~~~

- -~~~[<] Parser et tokeniser dans ce contexte. Notamment quand ils sont collés aux arguments/commandes.~~~
- -~~~[>] Parser et tokeniser dans ce contexte. Notamment quand ils sont collés aux arguments/commandes.~~~

- [*] Avec gestion des fichiers cachés et exclusions (avec lettres pré/post wildcard)

- -~~~[ENV_VAR] Parser et remplacer les variables d'environnement trouvées.~~~

- -~~~[PARHENTESES] Parser les parentheses et créer des sous-tokenisation. Aussi découper la chaîne de token et les déplacer pour gérer les priorités. {cachetra}~~~

###### LISTE DES CHOSES A FAIRE : ######

- [HISTORY] Faire un historique fonctionnel, basique. {ymanchon}

- -~~~[EXEC_GENERIC] Execution générique des commandes trouvées. {ymanchon}~~~

- -~~~[<] Redirige l'input. {ymanchon}~~~

- -~~~[>] Redirige l'output. {ymanchon}~~~

- -~~~[2>] Redirige l'output de la sortie d'erreur. {ymanchon}~~~

- [<<] Redirige l'input avec un délimiteur. {cachetra}

- -~~~[2>>] Redirige l'output de la sortie d'erreur en mode APPEND. {ymanchon}~~~

- -~~~[>>] Redirige l'output en mode APPEND. {ymanchon}~~~

- -~~~[PIPES] Implémenter les pipes '|' (output de la commande de gauche --> input de la commande de droite). {ymanchon}~~~

- -~~~[$?] Retourne la valeur DE RETOUR de la dernière commande (ex : ls renvoie 0 s'il y a eu aucune erreur). {cachetra}~~~

- -~~~[ctrl-C] Interpréter ce signal (SIGINT). Affiche un nouveau prompt avec une nouvelle ligne. {ymanchon}~~~

- -~~~[ctrl-D] Interpréter ce signal (EOF <=> End-Of-File). With a read(). Quitte le Shell actuel. {ymanchon}~~~

- -~~~[ctrl-\] Interpréter ce signal (SIGQUIT). Ne doit rien faire. {ymanchon}~~~

###### BUILTINS : ######

- -~~~[echo] Avec l'option -n. Affiche l'argument. {ymanchon}~~~

- -~~~[cd] Fonctionnant avec un chemin relatif et absolu. {ymanchon}~~~

- -~~~[pwd] Affiche le répertoire dans lequel se trouve l'utilisateur appelant. {cachetra}~~~

- [export] Ajouter une variable à l'environnement shell actuel. Si 'export' ne reçoit aucun argument, affiche toutes les variables d'environnements exportées. {cachetra}

- -~~~[unset] Détruit une variable. Cette commande ne retourne rien --> void unset(...). {ymanchon}~~~

- -~~~[env] Affiche toutes les variables 'environnements.d {cachetra}~~~

- -~~~[exit] Quitte le terminal. {ymanchon}~~~

###### BONUS : ######

- -~~~[||] Exécute seulement seulement la première commande valide trouvée (de gauche à droite). {cachetra}~~~

- -~~~[&&] N'exécute aucune commande si l'une d'entre elles n'est pas valide. {cachetra}~~~

- [*] Doit fonctionner sur le répertoire courant. {ymanchon}