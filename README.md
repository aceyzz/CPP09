<img src="utils/CPP09.png" width= 100%>

<br>


## Exercise 00 - Bitcoin Exchange

<details>
  <summary>Afficher/Masquer</summary>

### Objectif :

Le but de cet exercice est de créer un programme qui affiche la valeur d'une certaine quantité de bitcoins à une date donnée. Le programme utilise une base de données au format csv représentant le prix du bitcoin au fil du temps. Il prend en entrée une deuxième base de données stockant les différents prix/dates à évaluer.

#### Contraintes :

- Le programme doit prendre un fichier comme argument.
- Chaque ligne de ce fichier doit utiliser le format : "date | valeur".
- Une date valide est toujours au format `Année-Mois-Jour`.
- Une valeur valide doit être un flottant ou un entier positif, entre `0` et `1000`.
- Au moins un conteneur doit être utilisé dans le code.
- Le programme doit gérer les erreurs potentielles avec un message d'erreur approprié.


#### Exemple d'utilisation du programme :

Si la date dans l'entrée n'existe pas dans la DB, la date la plus proche contenue dans la DB est utilisée.

Exemple d'exécution et de sortie du programme :

```zsh
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
...
Error: too large a number.
```

### Mon Implémentation :

[Lien ici](https://github.com/aceyzz/CPP09/tree/main/ex00)

#### Fonctionnalités principales :

- Validation de la date : Assure que la date est dans un format valide et se trouve dans une plage acceptable.
- Extraction du taux de change : Récupère le taux de change pour une date donnée à partir de la base de données csv.
- Gestion des erreurs : Plusieurs exceptions sont définies pour gérer les erreurs telles que les fichiers non ouvrables, les formats invalides, et les valeurs hors de portée.

#### Exceptions personnalisées :

- `FileOpenException` : Gérée si le fichier ne peut pas être ouvert.
- `InvalidFormatException` : Gérée si le format du fichier est invalide.
- `OutOfRangeException` : Gérée si une valeur est en dehors de la plage autorisée.
- `DateNotFoundException` : Gérée si la date spécifiée n'est pas trouvée dans la base de données.
- `InvalidDateFormatException` : Gérée si le format de la date est invalide.
- `LargeNumberException` : Gérée si le nombre spécifié est trop grand.
- `EmptyFileException` : Gérée si le fichier est vide.
- `ParsingErrorException` : Gérée si une erreur de parsing survient.

#### Exemple de flux de travail :

- `ParseData` : Lit et analyse la base de données csv pour extraire les taux de change.
- `isValidDate` : Vérifie si une date est valide.
- `getExchangeRateForDate` : Trouve le taux de change pour une date donnée ou la date la plus proche.

<br>

> Cet exercice illustre l'utilisation des conteneurs, la gestion des exceptions, et le traitement des données issues de fichiers.

</details>

<br>

---

<br>

## Exercise 01 - RPN

<details>
  <summary>Afficher/Masquer</summary>

#### Objectif :

L'objectif de cet exercice est de créer un programme capable de traiter une expression mathématique en [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) (RPN) et d'afficher le résultat correct. Les nombres utilisés dans l'expression et passés en arguments seront toujours inférieurs à 10, bien que le calcul lui-même et le résultat ne soient pas limités par cette règle. Le programme doit gérer les opérations avec les opérateurs `+` `-` `/` `*`.

#### Contraintes :

- Le programme s'appelle `RPN`.
- Le programme prend une expression RPN en argument.
- Le programme doit afficher le résultat sur la sortie standard.
- En cas d'erreur, un message d'erreur doit être affiché.
- Utilisation d'au moins un conteneur.

#### Gestion des erreurs :

Des exceptions personnalisées sont définies pour gérer diverses erreurs telles que "Trop d'opérandes", "Pas assez d'opérandes", "Division par zéro", et "Valeur invalide".

Exemple d'utilisation du programme :
```zsh
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
```

### Mon Implémentation :

[Lien ici](https://github.com/aceyzz/CPP09/tree/main/ex01)

#### Fonctionnalités principales :

- Analyse et traitement de l'expression RPN : Utilise un conteneur std::stack<int> pour stocker et manipuler les opérandes.
- Opérations mathématiques : Implémente les opérations de base `+`, `-`, `*`, `/` en prenant en compte les règles de la notation RPN.
- Exceptions personnalisées :
	- `TooManyOperandsException` : Générée s'il y a trop d'opérandes.
	- `NotEnoughOperandsException` : Générée s'il n'y a pas assez d'opérandes pour une opération.
	- `DivisionByZeroException` : Générée en cas de tentative de division par zéro.
	- `InvalidValueException` : Générée lorsqu'une valeur invalide est détectée dans l'expression.

<br>

> Cet exercice illustre la manipulation d'expressions mathématiques en notation polonaise inversée (RPN), l'utilisation de conteneurs pour stocker des données, et la gestion des erreurs à travers des exceptions personnalisées.

</details>

<br>

---

<br>

## Exercise : 02 - PmergeMe

<details>
  <summary>Afficher/Masquer</summary>

#### Objectif :
Créer un programme capable de trier une séquence d'entiers positifs en utilisant l'algorithme de tri par fusion-insertion (Ford-Johnson). Le programme doit être capable de gérer au moins 3000 entiers différents.

#### Contraintes :
- Nom du programme : `PmergeMe`.
- Utilisation de deux conteneurs différents pour valider l'exercice.
- Gestion des erreurs avec affichage de messages appropriés.

#### Fonctionnalités principales :
- **`pmerge(int argc, char **argv)`** : Analyse les arguments passés au programme, effectue le tri et affiche les résultats.

#### Gestion des erreurs :
Des exceptions personnalisées sont utilisées pour traiter divers cas d'erreurs :
- **`EmptyListException`** : Lancée si la liste est vide.
- **`EmptyVectorException`** : Lancée si le vecteur est vide.
- **`DuplicateException`** : Lancée en cas de détection de doublons.
- **`InvalidValueException`** : Lancée pour une valeur invalide.

### Mon implémentation :

[Lien ici](https://github.com/aceyzz/CPP09/tree/main/ex02)

*J'ai choisi de faire les `mergeSort()` pour chacun des containers, plutot que de passer par une alternative avec les `template` et des itérateurs communs, pour une meilleure lisibilité. J'ai aussi fait le choix de pouvoir gérer des nombres négatifs. Pour ce qui est des doublons, ceux-ci sont ignorés (en lancant une exception tout de même) et le programme continue avec les autres nombres.*

- Utilisation de `std::vector<int>` et `std::list<int>` comme conteneurs principaux.
- Les nombres sont initialement stockés dans un `std::set<int>` pour éliminer les doublons.
- **`myMergeSortVector(std::vector<int> &vec)`** et **`myMergeSortList(std::list<int> &list)`** : Fonctions de tri personnalisées pour chaque conteneur.
- **`mergeVector(std::vector<int> &left, std::vector<int> &right)`** et **`mergeList(std::list<int> &left, std::list<int> &right)`** : Fonctions de fusion pour le tri.
- Mesure du temps d'exécution du tri pour chaque conteneur à l'aide de `gettimeofday()`.

#### Exemple d'utilisation :

```zsh
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::list : 0.00014 us
```

<br>

*Cet exercice illustre l'utilisation de plusieurs conteneurs STL pour trier une grande quantité de données, tout en gérant les erreurs de manière appropriée.*

</details>

<br>

---
