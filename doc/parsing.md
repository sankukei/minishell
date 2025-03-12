# Parsing : Une étape clé du projet

Le **parsing** est une des parties les plus cruciales du projet.
Une mauvaise gestion des **redirections**, des **quotes** ou des **pipes** peut entraîner des fuites de mémoire et des erreurs difficiles à corriger.  

> Une simple erreur passée inaperçue peut obliger à **refactoriser entièrement** le parsing.

## Utilisation des TOKENS

Pour éviter ces problèmes, il est essentiel d'utiliser les **TOKENS**, conçus pour simplifier le parsing.  

En gérant les **quotes** dès le départ  
En suivant les **règles de tokenisation documentées**  
On minimise ainsi les risques de bugs et de surprises.

## Structure des commandes : Liste chaînée et TOKENS

Nous allons créer une **liste chaînée**, où chaque maillon représente une **partie de la commande** avec son **type**.  

Chaque nœud contiendra :  
- Une **chaîne de caractères** représentant une partie de la commande  
- Un **entier associé** indiquant le type du token  

### Exemple  

Pour la commande Bash suivante :  
```bash
ls
```
Nous aurons un nœud contenant :
- String : `"ls"`
- Token : `6` (CMD)

### Un autre un peu plus complexe maintenant

Pour la commande Bash suivante :
```bash
cat | rev
```
Nous aurons plusieurs nœuds contenant :
- String : `"cat"`
- Token : `6` (CMD)


Puis
- String : `"|"`
- Token : `5` (PIPE)


Et enfin
- String : `"rev"`
- Token : `6` (CMD)

## Règles de Tokenisation  

La tokenisation suit des **règles simples** pour identifier chaque élément d'une commande.

(merci a l'Homme qui a mis ca sur github c'est trop une legende)

### Attribution des TOKENS  

**Redirections** (`<`, `>`, `<<`, `>>`)  
- `<` → **INPUT** `(1)`  
- `<<` → **HEREDOC** `(2)`  
- `>` → **TRUNC** `(3)`  
- `>>` → **APPEND** `(4)`  

**Commandes et Arguments**  
- Le **premier token** sera **CMD** `(6)`, sauf en cas de redirection au début.  
- Tout token après un **CMD** ou une **redirection** sera un **ARG** `(7)`.  

**Pipes** (`|`)  
- Un pipe (`|`) sera identifié comme **PIPE** `(5)`.  
- Après un **PIPE**, le prochain token sera soit une **redirection**, soit une **CMD**.  

Ces règles assurent une tokenisation claire et cohérente pour un parsing efficace.




