# 2021-2022_Viallaneix_Sottas_Noual
Granulometric sensor - MOSH project 2022.

## Informations générales
> Ce projet s'inscrit dans le cadre de l'UF _"Du capteur au banc de test en open source hardware"_.
> Le coeur du projet bat sur fréquence de la **LOW TECH**. Nous partirons de la fabrication d'un capteur granulométrique élaboré à partir d'une feuille de papier sur laquelle une couche de carbone sera déposée à l'aide d'un crayon à papier (panel de dureté entre HB et 9B) selon un motif prédeterminé. A ce corps d'épreuve, deux électrodes insérées aux extrémités du motif permettrons la circulation d'un courant. Une déformation du capteur entrainera une variation du courant mesurable par un système d'acquisition de données. Les enjeux du projet sont donc multiples!
> **Physique** : sur les propriétés d'un capteur granulométrique
> **Technique** : sur la conception et le développement d'un système d'acquisition
> **Exploratoire** : par l'utilisation des outils et concepts de l'Open Source Hardware.
> **Se construire une composante _low-tech_  de l'ingénieur que nous serons** : en s'intérogeant sur les attente d'une société en mutation, en posant un regard critique sur la notion de progrès technique et sa finalité.
![lowtech](https://fr.wikipedia.org/wiki/Low-tech#/media/Fichier:Infographie_low-tech.jpg)

### Ce que fait ce projet 

> La finalité du projet est de pouvoir estimer les forces et faiblesses de ces capteurs low-tech. Pour cela nous allons devoir les tester, déterminer leurs caractéristiques et leur limites d'utilisations, autrement dit déterminer leurs datasheets.
> Pour cela nous allons concevoir un banc de mesures qui nous permettra dans un premier temps d'étalonner les capteurs (leurs sensibilités varient en fonction de la dureté) puis dans un deuxième temps de les éprouver dans des conditions et durées d'utilisation variées.
> Les jeux de données issues de ces tests vont vite devenir conséquents et il sera utile de prévoir les scripts et la visualisation en sortie du banc de test et étalonnage.
> La composante **étalonnage** du banc permet d'étalonner un capteur de sensibilité inconnue. La composante  **test** permet de renseigner la datasheet.


### Les étapes
> Dans la suite du projet le capteur désignera le corps d'épreuve et le banc le système permetant l'acquisition des 
> La première étape consiste à la réalisation du capteur granulométrique. Ce capteur est utilisé pour le développement du banc d'étalonnage

### Les axes du projets
#### Présentation du capteur granulométrique
##### Le capteur
##### propriété d'un système granulaire
#### Acquisition des données
##### La carte Arduino
##### Le conditionneur
###### Schéma electrique
###### Code du système
###### Tests KiCad & LT-Spice
###### Réalisation du PCB
