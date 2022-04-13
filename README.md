# 2021-2022_Viallaneix_Sottas_Noual
Granulometric sensor - MOSH project 2022.

# Informations générales
> Ce projet s'inscrit dans le cadre de l'UF _"Du capteur au banc de test en open source hardware"_.
> Le cœur du projet bat sur fréquence de la **LOW TECH**. Nous partirons de la fabrication d'un capteur granulométrique élaboré à partir d'une feuille de papier sur laquelle une couche de carbone sera déposée à l'aide d'un crayon à papier (panel de dureté entre HB et 9B) selon un motif prédeterminé. À ce corps d'épreuve, deux électrodes insérées aux extrémités du motif permettront la circulation d'un courant. Une déformation du capteur entraînera une variation du courant mesurable par un système d'acquisition de données. Les enjeux du projet sont donc multiples!
* **Physique** : sur les propriétés d'un capteur granulométrique
* **Technique** : sur la conception et le développement d'un système d'acquisition
* **Exploratoire** : par l'utilisation des outils et concepts de l'Open Source Hardware.
* **Se construire une composante _low-tech_  de l'ingénieur que nous serons** : en s'interrogeant sur les attentes d'une société en mutation, en posant un regard critique sur la notion de progrès technique et sa finalité.

![low-tech](https://upload.wikimedia.org/wikipedia/commons/e/eb/Infographie_low-tech.jpg)

# Ce que fait ce projet 

> La finalité du projet est de pouvoir estimer les forces et faiblesses de ces capteurs low-tech. Pour cela nous allons devoir les tester, déterminer leurs caractéristiques et leur limites d'utilisations, autrement dit déterminer leurs datasheets.
> Pour cela nous allons concevoir un banc de mesures qui nous permettra dans un premier temps d'étalonner les capteurs (leurs sensibilités varient en fonction de la dureté) puis dans un deuxième temps de les éprouver dans des conditions et durées d'utilisation variées.
> Les jeux de données issues de ces tests vont vite devenir conséquents et il sera utile de prévoir les scripts et la visualisation en sortie du banc de test et étalonnage.
> La composante **étalonnage** du banc permet d'étalonner un capteur de sensibilité inconnue. La composante  **test** permet de renseigner la datasheet.


# Les étapes
> Dans la suite du projet le capteur désignera le corps d'épreuve et le banc le système permettant l'acquisition des 
> La première étape consiste à la réalisation du capteur granulométrique. Ce capteur est utilisé pour le développement du banc d'étalonnage

## Les axes du projets
### Présentation du capteur granulométrique
### Le capteur
> Hello voici la description du capteur. 
#### Propriété d'un système granulaire
### Acquisition des données
#### La carte Arduino
#### Le conditionneur
##### Partie 1: Mesure d'un très faible courant avec l'aide d'un micro-contrôleur
L’objectif étant d’extraire l’information utile du capteur ayant un très faible courant (environ 100 nA), le montage électrique doit être adapté de manière à mesurer des courants faibles. Selon les caractéristiques techniques du microcontrôleur Arduino (cf Datasheet), on ne peut pas mesurer directement de très faibles courants en raison de l’impédance de source (environ égale à quelques kOhms). Il est donc nécessaire d’utiliser un circuit amplificateur transimpédance composé d’un amplificateur opérationnel AOP pour convertir un courant issu du capteur en une tension mesurable par le CAN (Convertisseur Analogique-Numérique) de l’Arduino UNO.

<p align="center"><img src="Images/solution classique transimpédance.png" align=middle width="456.690135pt" height="300.925785pt"/></p>

**Figure 1: Montage de transimpédance (ou convertisseur courant-tension)**

L’inconvénient d’un montage classique de transimpédance est qu’il nécessite une grande résistance pour amplifier le signal et que la tension d’alimentation du capteur doit être négative. On peut donc ajouter un autre étage inverseur à la suite du premier montage : 

<p align="center"><img src="Images/Circuit%20Transimp%C3%A9dance%202%20%C3%A9tages.jpg" align=middle width="556.690135pt" height="250.925785pt"/></p>
<p align="center"><img src="Images/Formule 2.png" align=middle width="556.690135pt" height="250.925785pt"/></p>

**Figures 2 et 3: Ajout d'un étage inverseur sur le montage de transimpédance et Calcul du gain du second montage**

Dans le montage ci-dessus, le gain du second étage étant négatif compte-tenu de son caractère inverseur `(cf Figure 3)`, la résistance R1 du premier étage n’a plus besoin d’avoir une grande valeur. De plus, l’alimentation du capteur est donc positive grâce au second montage inverseur du fait des produits des gains de deux étages. 

Pour plus de simplicité, on a choisi un montage en prenant un seul AOP dans le montage. 

En calculant la tension aux bornes de la résistance R1, on obtient une tension environ égale à 10 mV.


Il s’agit d’une valeur importante pour le choix de l’AOP notamment pour l'effet de l’offset du signal d’entrée. 
Le Gain de ce montage et la Tension de sortie ADC sont décrits dans les calculs ci-dessous : 


Si on a un courant nul en entrée, on veut alors obtenir une tension ADC nulle en sortie, cela implique qu’il n’y ait pas de dérives en tension de la part de l’AOP.
Les principales contraintes pour le choix de l’amplificateur opérationnel sont le faible courant d’entrée et un très faible offset de tension devant être négligeable devant 10mV (tension aux bornes de R1).


##### Schéma électrique
> Voici un premier exemple de schéma électrique
<p align="center"><img src="Images/Circuit%20Transimp%C3%A9dance%202%20%C3%A9tages.jpg" align=middle width="552.690135pt" height="250.925785pt"/></p>

![Schéma électrique 1](Images/Circuit%20Transimp%C3%A9dance%202%20%C3%A9tages.jpg)

**Figure 1: Circuit amplificateur transimpédance**

##### Simulation sous LT-Spice
> Simulation continue paramétrique (DC Sweep).
> Simulation temporelle (Transient).
> Simulation fréquentielle (AC Sweep).

### Code du système
###### Tests KiCad & LT-Spice
### Réalisation du PCB
### Banc de tests
![Dessin 2D du banc de tests](Images/Dessin_bancTest.jpg "Dessin 2D montage banc de test")
**Figure 10: Dessin 2D du banc de test**

