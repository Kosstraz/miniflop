###### A RAJOUTER/REGLER : ######

- [QUOTES_BUG] Régler le bug où les quotes ne sont pas affichées dans un contexte
comme le suivant : """"""''"''" ou encore ''""''""'''""""' . Rien est affiché ce qui
n'est pas normal. Seul bug repéré jusqu'ici.

- [ctrl-C] C'est normalement automatiquement déjà géré, mais pour rappel si jamais : Gérer les commandes bloquantes.

###### QUESTIONNEMENTS : ######

###### TERMCAP : ######
{cachetra}

- [FT_READLINE] Faire ft_readline() ez.

###### PARSING : ######
{ymanchon}

- -~~~ [QUOTES] Interpréter les singles quotes et les doubles quotes.~~~

- -~~~ [COMMANDS] Commands~~~

- -~~~ [ARGUMENTS] Arguments~~~

- -~~~ [|] Pipe~~~

- -~~~[||] Or~~~

- -~~~[&&] And~~~

- [<] Parser et tokeniser dans ce contexte.
- [>] Parser et tokeniser dans ce contexte.

- [*]

- -~~~[ENV_VAR] Parser et remplacer les variables d'environnement trouvées.~~~

- [EXCEPTIONS] Gestion des exceptions faute de quote fermant.

- [PARHENTESES] Parser les parentheses et créer des sous-tokenisation. Aussi découper
la chaîne de token et les déplacer pour gérer les priorités.

###### LISTE DES CHOSES A FAIRE : ######

- [HISTORY] Faire un historique fonctionnel, basique. {ymanchon}

- [$] Gérer les dollars (avec ou sans double quote). {cachetra}

- [<] Redirige l'input. {ymanchon}

- [>] Redirige l'output. {ymanchon}

- [<<] Redirige l'input avec un délimiteur. {cachetra}

- [>>] Redirige l'output en mode APPEND. {cachetra}

- [PIPES] Implémenter les pipes '|' (output de la commande de gauche --> input de la commande de droite). {ymanchon}

- [HERE_DOC] Implémenter un fonctionnement similaire à heredoc. {cachetra}

- [$?] Retourne la valeur DE RETOUR de la dernière commande (ex : ls renvoie 0 s'il y a eu aucune erreur). {cachetra}

- -~~~ [ctrl-C] Interpréter ce signal (SIGINT). Affiche un nouveau prompt avec une nouvelle ligne. {ymanchon}~~~

- -~~~ [ctrl-D] Interpréter ce signal (EOF <=> End-Of-File). With a read(). Quitte le Shell actuel. {ymanchon}~~~

- -~~~ [ctrl-\] Interpréter ce signal (SIGQUIT). Ne doit rien faire. {ymanchon}~~~

###### BUILTINS : ######

- -~~~ [echo] Avec l'option -n. Affiche l'argument. {ymanchon}~~~

- -~~~ [cd] Fonctionnant avec un chemin relatif et absolu. {ymanchon}~~~

- [pwd] Affiche le répertoire dans lequel se trouve l'utilisateur appelant. {cachetra}

- [export] Ajouter une variable à l'environnement shell actuel. Si 'export' ne reçoit aucun argument, affiche toutes les variables d'environnements exportées. {cachetra}

- [unset] Détruit une variable. Cette commande ne retourne rien --> void unset(...). {ymanchon}

- [env] Affiche toutes les variables 'environnements.d {cachetra}

- [exit] Quitte le terminal. {cachetra}

###### BONUS : ######

- [||] Exécute seulement seulement la première commande valide trouvée (de gauche à droite). {cachetra}

- [&&] N'exécute aucune commande si l'une d'entre elles n'est pas valide. {cachetra}

- [*] Doit fonctionner sur le répertoire courant. {ymanchon}
