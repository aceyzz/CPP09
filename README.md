<img src="utils/CPP09.png" width= 100%>

<br>


## Sujet : Exercise 00 - Bitcoin Exchange

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

<br>

---

<br>

