## Parsing : Une étape clé du projet

Le **parsing** est une des parties les plus cruciales du projet.
Une mauvaise gestion des **redirections**, des **quotes** ou des **pipes** peut entraîner des fuites de mémoire et des erreurs difficiles à corriger.  

> Une simple erreur passée inaperçue peut obliger à **refactoriser entièrement** le parsing.

### Utilisation des TOKENS

Pour éviter ces problèmes, il est essentiel d'utiliser les **TOKENS**, conçus pour simplifier le parsing.  

En gérant les **quotes** dès le départ  
En suivant les **règles de tokenisation documentées**  
On minimise ainsi les risques de bugs et de surprises.
