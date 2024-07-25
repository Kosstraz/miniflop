###### A RAJOUTER/REGLER : ######

- [QUOTES_BUG] Régler le bug où les quotes ne sont pas affichées dans un contexte
comme le suivant : """"""''"''" ou encore ''""''""'''""""' . Rien est affiché ce qui
n'est pas normal. Seul bug repéré jusqu'ici.

- [ENV_VAR] Afficher littéralement le texte commençant par un '$' s'il est entouré de single quotes

- [$] Doit s'afficher s'il est seul (ou avec espaces) dans des guillemets doubles

- [*] Gérer plusieurs '*' sur un même mot

- [ctrl-C] C'est normalement automatiquement déjà géré, mais pour rappel si jamais : Gérer les commandes bloquantes.

###### QUESTIONNEMENTS : ######

###### TERMCAP : ######
{cachetra}

- [BIND_KEY] Faire une fonction qui permet de bind à un keycode donné une fonction. Exemple de prototype d'une fonction de ce style.

- [UNBIND_KEY] L'inverse de BIND_KEY, si c'est possibe seulement, peut potentiellement être utile (cosmétiquement). Ne pas perdre trop de temps sur ça ...

- [UTILS] N'importe quelle fonction permettant de modifier des flags termcap rapidement, ou d'utilités pour la modularité. A ton choix de faire ou non, si tu trouves ça utile.

- [FT_READLINE] Faire ft_readline() ez. LE BOSS FINAL MOUAHAHH!!!

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

- -~~~[*] Avec gestion des fichiers cachés et exclusions (avec lettres pré/post wildcard)~~~

- -~~~[ENV_VAR] Parser et remplacer les variables d'environnement trouvées.~~~

- [EXCEPTIONS] Gestion des exceptions faute de quote fermant.

- [PARHENTESES] Parser les parentheses et créer des sous-tokenisation. Aussi découper
la chaîne de token et les déplacer pour gérer les priorités. {cachetra}

###### LISTE DES CHOSES A FAIRE : ######

- [HISTORY] Faire un historique fonctionnel, basique. {ymanchon}

- [<] Redirige l'input. {ymanchon}

- [>] Redirige l'output. {ymanchon}

- [<<] Redirige l'input avec un délimiteur. {cachetra}

- [>>] Redirige l'output en mode APPEND. {cachetra}

- [PIPES] Implémenter les pipes '|' (output de la commande de gauche --> input de la commande de droite). {ymanchon}

- [HERE_DOC] Implémenter un fonctionnement similaire à heredoc. {cachetra}

- [$?] Retourne la valeur DE RETOUR de la dernière commande (ex : ls renvoie 0 s'il y a eu aucune erreur). {cachetra}

- -~~~[ctrl-C] Interpréter ce signal (SIGINT). Affiche un nouveau prompt avec une nouvelle ligne. {ymanchon}~~~

- -~~~[ctrl-D] Interpréter ce signal (EOF <=> End-Of-File). With a read(). Quitte le Shell actuel. {ymanchon}~~~

- -~~~[ctrl-\] Interpréter ce signal (SIGQUIT). Ne doit rien faire. {ymanchon}~~~

###### BUILTINS : ######

- -~~~[echo] Avec l'option -n. Affiche l'argument. {ymanchon}~~~

- -~~~[cd] Fonctionnant avec un chemin relatif et absolu. {ymanchon}~~~

- [pwd] Affiche le répertoire dans lequel se trouve l'utilisateur appelant. {cachetra}

- [export] Ajouter une variable à l'environnement shell actuel. Si 'export' ne reçoit aucun argument, affiche toutes les variables d'environnements exportées. {cachetra}

- -~~~[unset] Détruit une variable. Cette commande ne retourne rien --> void unset(...). {ymanchon}~~~

- [env] Affiche toutes les variables 'environnements.d {cachetra}

- -~~~[exit] Quitte le terminal. {ymanchon}~~~

###### BONUS : ######

- [||] Exécute seulement seulement la première commande valide trouvée (de gauche à droite). {cachetra}

- [&&] N'exécute aucune commande si l'une d'entre elles n'est pas valide. {cachetra}

- -~~~[*] Doit fonctionner sur le répertoire courant. {ymanchon}~~~
