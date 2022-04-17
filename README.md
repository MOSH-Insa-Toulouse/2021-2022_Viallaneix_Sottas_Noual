# 2021-2022_Viallaneix_Sottas_Noual MOSH Project 2022
Granulometric sensor

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
> Pour cela, nous allons concevoir un banc de mesures qui nous permettra, dans un premier temps, d'étalonner les capteurs (leurs sensibilités varient en fonction de la dureté) puis, dans un deuxième temps, de les éprouver dans des conditions et durées d'utilisation variées.
> Les jeux de données issues de ces tests vont devenir rapidement conséquents et il sera utile de prévoir les scripts et la visualisation en sortie du banc de test et étalonnage. 
> La composante **étalonnage** du banc permet de calibrer un capteur de sensibilité inconnue. La composante **test** permet de renseigner la datasheet.


# Les étapes
> Dans la suite du projet le capteur désignera le corps d'épreuve et le banc de test permettant l'acquisition des données.
> La première étape consiste à la réalisation du capteur granulométrique. Ce capteur est utilisé pour le développement du banc d'étalonnage

***
## Les axes du projets
* [Présentation du capteur granulométrique](#présentation-du-capteur-granulométrique)
* [Acquisition des données](#acquisition-des-données)
  * [Carte Arduino](#la-carte-arduino)
  * [Étude du circuit électrique](#le-conditionneur)
    * [Partie 1: Mesure d'un très faible courant avec l'aide d'un micro-contrôleur](#partie-1-mesure-dun-très-faible-courant-avec-laide-dun-micro-contrôleur)
       * [Vérification avec la Datasheet de l'AOP](#vérification-avec-la-datasheet-de-laop)
    * [Partie 2: Mise en oeuvre du filtrage du signal](#partie-2-mise-en-oeuvre-du-filtrage-du-signal)
    * [Schéma du circuit électronique final](#schéma-du-circuit-électronique-final)
    * [Partie 3: Simulations sous *LTSpice*](#partie-3-simulations-sous-ltspice)
  * [Code Arduino du système](#code-arduino-du-système)
  * [Application sur Android](#application-sur-android)
* [Réalisation du PCB](#réalisation-du-pcb)
   * [Partie 1: Conception de la schématique et des connexions entre les composants électroniques](#partie-1-conception-de-la-schématique-et-des-connexions-entre-les-composants-électroniques)
   * [Partie 2: Conception du PCB](#partie-2-conception-du-pcb)
   * [Partie 3: Soudure des composants sur le PCB et premiers tests](#partie-3-soudure-des-composants-sur-le-pcb-et-premiers-tests)
* [Banc de tests](#banc-de-tests)
* [Measurement System Analysis](#measurement-system-analysis)

***

### Présentation du capteur granulométrique
> Le capteur sélectionné dans le cadre de ce projet est un dépôt de graphite sur un papier, effectué à l’aide d’un crayon plus ou moins gras. 
Nous utiliserons pour cela la résistivité du graphite, qui est suffisamment faible pour laisser circuler un courant mesurable. Néanmoins, avec cette résistivité de 8 µΩ.m (contre 0,017 µΩ.m pour le cuivre), il faudra utiliser un montage amplificateur dans notre banc de test.

> Le dépôt de graphite effectué sur le papier sera alors représentatif de la flexion que ce dernier subit : les grains de graphite jouent le rôle de conducteur mais leur éloignement variera selon la flexion, et va donc influencer la résistance mesurée.

<div align="center">
<img src="Images/Dessin Capteur graphite.png"/></p>

**Figure 1: Première description schématique d'une mesure sur le capteur de graphite**

<div align="left">
</p>

> Dans l’exemple ci dessus, on mesurera pour une même tension appliquée que:

<div align="center">
<img src="Images/Calculs/Formule 0.png"/></p>

<div align="left">
</p>

> L’intérêt de ce capteur se situe dans son aspect low-tech qui lui permet d’être facilement produit, mais pas uniquement :  la vaste gamme de dureté des mines de crayon (H, F, HB, B) offre un large choix pour la résistivité du dépôt.
En effet, la dureté d’une mine correspond à ses proportions de graphite et d’argile. Le graphite est, par exemple, plus présent dans un crayon dit « gras » de type B que dans un crayon de type H. Ainsi, nous disposons assez simplement d’un large panel de capteurs pour éventuellement les comparer à l’aide du banc de tests.

(#### Propriété d'un système granulaire)
### Acquisition des données
#### La carte Arduino
#### Le conditionneur

#### Partie 1: Mesure d'un très faible courant avec l'aide d'un micro-contrôleur
L’objectif étant d’extraire l’information utile du capteur ayant un très faible courant (environ 100 nA), le montage électrique doit être adapté de manière à mesurer des courants faibles. Selon les caractéristiques techniques du microcontrôleur Arduino (cf Datasheet), on ne peut pas mesurer directement de très faibles courants en raison de l’impédance de source (environ égale à quelques kOhms). Il est donc nécessaire d’utiliser un circuit amplificateur transimpédance composé d’un amplificateur opérationnel AOP pour convertir un courant issu du capteur en une tension mesurable par le CAN (Convertisseur Analogique-Numérique) de l’Arduino UNO.

<p align="center"><img src="Images/solution classique transimpédance.png" align=middle width="456.690135pt" height="300.925785pt"/></p>
<div align="center"></p>
  
**Figure 2: Montage de transimpédance (ou convertisseur courant-tension)**
  
<div align="left"></p>

L’inconvénient d’un montage classique de transimpédance est qu’il nécessite une grande résistance pour amplifier le signal et que la tension d’alimentation du capteur doit être négative. On peut donc ajouter un autre étage inverseur à la suite du premier montage : 


<p align="center"><img src="Images/Circuit%20Transimp%C3%A9dance%202%20%C3%A9tages.jpg" align=middle width="556.690135pt" height="250.925785pt"/></p>
<p align="center"><img src="Images/Calculs/Formule 2.png" align=middle width="194.090135pt" height="48.925785pt"/></p>

<div align="center"></p>
  
**Figures 3 et 4: Ajout d'un étage inverseur sur le montage de transimpédance et Calcul du gain du second montage**

<div align="left"></p>

Dans le montage ci-dessus, le gain du second étage étant négatif compte-tenu de son caractère inverseur (`cf Figure 3`), la résistance R1 du premier étage n’a plus besoin d’avoir une grande valeur. De plus, l’alimentation du capteur est donc positive grâce au second montage inverseur du fait des produits des gains de deux étages. 

Pour plus de simplicité, on a choisi un montage en prenant un seul AOP dans le montage.
<p align="center"><img src="Images/Solution minimale.png" align=middle width="367.690135pt" height="242.925785pt"/></p>

<div align="center"></p> 

**Figure 5: Solution simplifiée pour le montage transimpédance**

<p align="center"><img src="Images/Calculs/Formule 3.png" align=middle width="494.690135pt" height="23.925785pt"/></p>

**Figure 6: Calcul de la tension aux bornes de R1**

<div align="left"></p>
  
En calculant la tension aux bornes de la résistance R1, on obtient une tension environ égale à 10 mV d'après la `Figure 4`.

Il s’agit d’une valeur importante pour le choix de l’AOP notamment pour l'effet de l’offset du signal d’entrée. 
Le Gain de ce montage et la Tension de sortie ADC sont décrits dans les calculs ci-dessous : 

<p align="center"><img src="Images/Calculs/Formule 4.png" align=middle width="361.690135pt" height="52.925785pt"/></p>

<p align="center"><img src="Images/Calculs/Formule 5.png" align=middle width="428.690135pt" height="23.925785pt"/></p>
<div align="center"> </p>
  
**Figure 7: Calculs du gain du montage et de la tension de sortie**

<div align="left"></p>
  
Si on a un courant nul en entrée, on veut alors obtenir une tension ADC nulle en sortie, cela implique qu’il n’y ait pas de dérives en tension de la part de l’AOP.
Les principales contraintes pour le choix de l’amplificateur opérationnel sont le faible courant d’entrée et un très faible offset de tension devant être négligeable devant 10mV (tension aux bornes de R1).

##### Vérification avec la Datasheet de l'AOP

Selon les données de la [Datasheet](LTC1050C.pdf) de l'AOP 1050C, on constate qu'il possède un faible offset de tension d'environ 5μV au maximum et un très faible drift pour l'offset de tension à environ 0.05μV/°C. Cela indique la bonne stabilité de l'amplificateur opérationnel. Par comparaison, les AOP utilisés traditionnellement en salle de TP possèdent un offset autour de 5mV, une valeur 1000 fois plus grande que celle du 1050C.
En comparant la tension d'entrée (autour de 10mV `cf Figure 5`), on constate que l'offset de 5μV est très faible.
De plus, on peut remarquer que cet AOP possède un mode commun incluant la masse ce qui correspond à notre montage électrique.
  
<div align="center"></p>
<p align="center"><img src="Images/Simulation_LTSpice/Electrical characteristics LTC1050C.jpg"/></p>
  
**Figure 8: Extrait de la datasheet dans la partie Electrical Characteristics**

<div align="left"></p>
  
Enfin, on constate que le courant de polarisation en entrée (Input Bias Current) est au maximum égale à 30pA, cela convient car nous effectuons des mesures de courant autour de 100nA. Il faut que le courant Isense `cf Figure 4` soit très faible devant 100nA et le reste du courant passe dans la résistance R1. 
En respectant les différentes conditions énoncées précédemment, l'AOP 1050C est adapté pour notre circuit électronique.


#### Partie 2: Mise en oeuvre du filtrage du signal

Étant donné que ce montage est très sensible aux signaux parasites (50Hz, horloge du microcontrôleur Arduino, Bluetooth entre autres), on doit mettre en œuvre un filtrage passe-bas pour limiter les perturbations du signal.
D’une part, il faut appliquer un filtre passif en entrée pour limiter les perturbations de type radiofréquences pouvant conduire à un excès de bruit dans l’ADC.
Ensuite, on applique un filtre actif au niveau de l’amplificateur opérationnel pour augmenter l’efficacité de l’échantillonnage du signal. 
À la sortie de l’AOP, on utilise un dernier filtre passif pour retirer le bruit sur le traitement du signal et les phénomènes de repliement de spectre (aliasing). 

En intégrant les différents filtres, le montage ressemble à ceci : 

<div align="center"></p>
<p align="center"><img src="Images/Simulation_LTSpice/Schéma électrique 1.png" align=middle width="952.090135pt" height="446.025785pt"/></p>
  
**Figure 9: Schéma du montage électrique avec les différents filtres**

<div align="left"></p>

On distingue 3 différents filtres où nous avons cherché pour chacun la fréquence de coupure et son rôle principal pour le filtrage : 

<div align="center"></p>
<p align="center"><img src="Images/Simulation_LTSpice/Distinction des filtres.png" align=middle width="742.090135pt" height="483.025785pt"/></p>
  
**Figure 10: Identification des différents filtres dans le montage**

<div align="left"></p> 
 
Tout d'abord, le filtre passe-bas passif, placé à l'entrée de l'AOP, est constitué de R1(100kΩ) et C1(100nF). Il possède une fréquence de coupure théorique environ égale à 16Hz `cf Figure 7` . Il permet donc de filtrer les perturbations et les excès de bruit en courant sur la forme du signal d'entrée. 

<p align="center"><img src="Images/Calculs/Formule 6.png" align=middle width="533.090135pt" height="48.025785pt"/></p>
<div align="center"></p> 

**Figure 11: Calcul de la fréquence de coupure du filtre passif (R1 et C1)**

<div align="left"></p>

Ensuite, le filtre passe-bas actif, placé entre l'entrée et la sortie de l'AOP, est constitué de R3(100kΩ) et C4(1μF) en parallèle. Ce dernier possède une fréquence de coupure théorique environ égale à 1.6Hz `cf Figure 8`. Son rôle principal est de supprimer la composante parasite de 50Hz (du fait du couplage capacitif avec la tension 230V) qui perturbe significativement le signal `cf Figure XX`.

<p align="center"><img src="Images/Calculs/Formule 7.png" align=middle width="453.090135pt" height="48.025785pt"/></p>
<div align="center"></p>

**Figure 12: Calcul de la fréquence de coupure du filtre actif (R3 et C4)**

<div align="left"></p>

Enfin, le filtre passe-bas passif, placé à la sortie de l'AOP, est constitué de R6(100kΩ) et C2(100nF). Il possède une fréquence de coupure théorique environ égale à 1.6kHz `cf Figure 9`. En sachant que la fréquence d'échantillonnage du micro-contrôleur est environ égale à 15,4kHz, il faut respecter la condition d'échantillonnage de Shannon à savoir:  

<p align="center"><img src="Images/Calculs/Formule 8.png" align=middle width="524.090135pt" height="48.025785pt"/></p>
<div align="center"></p> 

**Figure 13: Calcul de la fréquence de coupure du filtre passif (R6 et C2) et Vérification de la condition d'échantillonnage de Shannon**

<div align="left"></p>

Selon les calculs, on respecte bien la condition d'échantillonnage de Shannon `cf Figure ci-dessus`, le filtre permet de limiter les effets de repliement de spectre (rôle d'anti-aliasing) et de manière générale, le bruit lors du traitement du signal. 

#### Schéma du circuit électronique final
> Voici un première proposition du schéma électrique
  
<div align="center"></p>
<p align="center"><img src="Images/Simulation_LTSpice/Schéma électrique 1.png" align=middle width="952.090135pt" height="446.025785pt"/></p>

**Figure 14: Premier schéma du montage électronique**

<div align="left"></p>
  
Dans ce schéma, nous simulons le bruit en courant à l'entrée en mettant une capacité à côté du générateur de tension. On a ajouté une capacité C3 pour filtrer le bruit de la source d'alimentation.
  
> On propose une optimisation du montage électronique en simulant le capteur de graphite `cf Figure ci-dessous`
  
<div align="center"></p>
<p align="center"><img src="Images/Simulation_LTSpice/Schéma électrique optimisé.png" align=middle width="930 pt" height="420.025785pt"/></p>

**Figure 15: Schéma électrique optimisé**

<div align="left"></p>
  
Nous avons simulé notre capteur de graphite (cf rectangle en haut à gauche de la `figure précédente`). 
> Commentaires à ajouter


#### Partie 3: Simulations sous *LTSpice*
  
On vérifie les conditions optimales de fonctionnement du montage électronique en effectuant différentes simulations sur le logiciel *LTSPice* `cf figures ci-dessous`.

<div align="center"></p>
<img src="Images/Simulation_LTSpice/Simulation 1 illustration du gain montage.png"/></p>

**Figure 16: Vérification du gain d'amplification du signal environ égal 100**
  
<img src="Images/Simulation_LTSpice/Question 1_bis.jpg"/></p>

**Figure 17: Vérification du la tension de sortie du montage avec un courant d'entrée égal à 100nA**

<div align="left"></p>
  
Pour l'illustration graphique du gain du montage général, on distingue qu'il y a bien 3 filtres dans le circuit électronique grâce aux différentes variations du terme de phase (courbe en traits en pointillés `cf Figure `).
> Mettre photo 

> On vérifie graphiquement la fréquence de coupure de chaque filtre en effectuant une simulation fréquentielle (AC Sweep):

Pour le premier filtre à l'entrée de l'AOP (R1 et C1):
<div align="center">
<img src="Images/Simulation_LTSpice/Simulation 3 filtre gauche.png"/></p>

**Figure 18: Illustration graphique de la fréquence de coupure du filtre (R1 et C1)**

<div align="left"></p>
  
Pour le second filtre entre l'entrée et la sortie de l'AOP (R3 et C4) et le dernier filtre à la sortie (R6 et C2):
  
<div align="center">
<img src="Images/Simulation_LTSpice/Simulation 5 filtres centre et droit.png"/></p>

**Figure 19: Illustration graphique des fréquences de coupure des deux filtres passe-bas**

<div align="left"></p>


> On vérifie l'incidence du courant d'entrée de l'amplificateur sur la tension de sortie par une simulation temporelle:

<div align="center">
<img src="Images/Simulation_LTSpice/Question 3.jpg"/></p>

**Figure 20: Illustration graphique de l'incidence du courant d'entrée sur la tension de sortie**

<div align="left"></p>
  
On peut remarquer dans cette image qu'à partir d'une valeur de 500nA pour le courant d'entrée, on obtient une tension pouvant saturer le convertisseur analogique-numérique de l'Arduino. 

  
> On observe graphiquement l'atténuation globale du signal d'un bruit en courant de 50 Hz ainsi que celle associée à un bruit en courant à la fréquence de repliement de spectre autour de 7 kHz. 

<div align="center">
<img src="Images/Simulation_LTSpice/Question 5_6.jpg"/></p>
<img src="Images/Calculs/Atténuation 50 Hz.png"/> 
<p align="center"><img src="Images/Calculs/Atténuation échantillonnage.png"/></p>

**Figures 21 et 22: Illustration graphique de l'atténuation du signal d'un bruit en courant pour deux fréquences spécifiques et calculs des atténuations**

<div align="left"></p>

Comme on peut le voir avec les calculs précédents, on constate qu'il y a une atténuation en bruit de courant environ égale à 40dB pour une fréquence autour de 50Hz et elle est environ égale à 100 dB pour un bruit en courant au voisinage de la fréquence de repliement de spectre. Cela montre bien que le signal peut être fortement perturbé et atténué si on laisse la composante fréquentielle à 50 Hz et si on ne respecte la condition d'échantillonnage.   


> (Simulation continue paramétrique (DC Sweep))

### Code Arduino du système
<div align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2021-2022_Viallaneix_Sottas_Noual/blob/39fd9ad23a14a9ccfff4c6776e45fc2be55771ee/Images/logigramme.jpg"/></p>

**Figure 23: Logigramme de notre code Arduino**

<div align="left"></p>
  
Voici une présentation graphique de notre code Arduino.
  
### Application sur Android

  
  
<div align="center"></p>


**Figure 24: Aperçu visuel de notre application **

<div align="left"></p>
    

### Réalisation du PCB

Après avoir réalisé les simulations sur *LTSpice*, nous avons conçu un premier modèle de PCB avec l'aide du logiciel *KiCAD*. 

#### Partie 1: Conception de la schématique et des connexions entre les composants électroniques

> Lors de cette étape, nous avons choisi un modèle basé sur l'Arduino UNO pour avoir les bonnes dimensions de la carte et les pins de connexion adéquats. Afin de réaliser précisément le PCB, nous avons dû concevoir certains composants électroniques nous-mêmes dans la partie Schématique (écran OLED, module Bluetooth, l'amplificateur LTC1050C, l'encodeur rotatoire et le potentiomètre digital)  `cf Figures ci-dessous`

<div align="center">
<img src="Images/Schématique Carte Arduino.png"/></p>
 
**Figure 25: Schéma des pins de connexion de la carte Arduino UNO**
 
<img src="Images/Module OLED.png"/><img src=""/></p>
<img src="Images/module Bluetooth.png"/><img src=""/></p>
<img src="Images/Encodeur rotatoire.png"/><img src=""/></p>
<img src="Images/Potentiomètre digital.png"/><img src=""/></p>

**Figures 26: Schémas et empreintes de chacun de nos composants électroniques (Écran OLED, BLuetooth, Encodeur rotatoire, Potentiomètre digital)**

<div align="left"></p>

#### Partie 2: Conception du PCB

> Dans cette partie, nous plaçons virtuellement les différents composants sur le PCB et nous effectuons toutes les connexions entre les pins de composants et ceux de la carte Arduino. Nos différentes professeurs réferents (Mr Jérémie Grisolia et Mme Catherine Crouzet) nous ont indiqués les consignes à respecter pour la réalisation du PCB: 
  
* Largeur des pistes = 0.6 mm
* Largeur d'isolation des pistes = 0.9 mm
* Dimensions du trou pour l'écran OLED, le module Bluetooth et l'encodeur rotatoire = 2 mm * 2.5 mm
* Diamètre du via (trou entre la face avant et arrières du PCB) = 2 mm
* Taille du trou de perçage du via = 0.8 mm
* Taille du trou de perçage pour l'écran OLED, le module Bluetooth et l'encodeur rotatoire, l'AOP et le potentiomètre digital = 1 mm
* Dimensions du trou pour le support de l'AOP (pad n°1 rectangulaire et les autres pins sont ovales) = 2 mm * 2.5 mm
* Taille du trou de perçage pour les résistances et les capacités = 0.8 mm
  
<div align="center">
<img src="Images/PCB KiCAD pistes.png"/><img src=""/></p>

**Figure 27: Schémas des pistes sur le PCB**

<div align="left"></p>

> Mettre une photo 3D
  
Avec l'aide de Mme Catherine Crouzet, nous avons réalisé le PCB selon le protocole suivant:

* Insolation de la plaque de résine positive par photo-lithographie UV par contact avec un masque `cf Figure ci-dessous` imprimé sur un film transparent, provenant du logiciel *KiCAD*. Cette résine est choisie de telle manière à être sensible aux rayons UV.
Une fois l'insolation réalisée, la partie de la résine insolée est dissoute dans une solution de développeur. Le reste de la résine, étant protégé par le masque, reste intact. On observe l'apparition des pistes du circuit sur le PCB.
  
* Passage dans un bain de péroxyde de fer pour enlever les résidus de la piste de cuivre sur le PCB
  
* Nettoyage et Séchage de la plaque à l'eau naturelle

<div align="center">
<img src="Images/Masque PCB.png"/></p>

**Figure 28: Masque imprimé du PCB sur un film transparent**

<div align="left"></p>

#### Partie 3: Soudure des composants sur le PCB et premiers tests
 
Uns fois le PCB réalisé, nous avons percé tous les trous des pins associés à chaque composant électronique puis nous avons soudé les différents composants et les broches latérales entre le PCB et la carte Arduino.


### Banc de tests
> En Cours de réalisation, mettre 1-2 images sur le banc de tests fonctionnels

> Le but de ce banc de test est de déterminer la sensibilité du capteur, de voir l’évolution de cette dernière selon la répétition des flexions et de comparer ces données avec un capteur commercialisé "Flex-Sensor".

> Ce banc de test est composé d’un servomoteur pour une bonne précision sur les angles, ainsi que d’un support où l’on vient encastrer le capteur. Une roue où l’on positionne le bout du capteur est alors entraînée par le servomoteur et génère la flexion. Il est fait de plaques de contreplaqué superposées, qui ont été découpées au FabLab et il permet de garder le capteur le plus intact possible, car celui-ci n’est maintenu qu’aux deux extrêmités et non pas sur le dépôt de graphite lui-même.
L’utilisateur détermine au préalable le nombre de répétitions souhaité à l’aide de l’encodeur rotatoire placé sur le PCB. Il peut ensuite récupérer les données (angle, itération de la mesure, résistance lue) sur le moniteur série et les traiter dans un logiciel comme Rmarkdown, Python via l'interpréteur Spyder IDE ou Qtiplot.
Le capteur qui servira de référence comparative sera le Flex Sensor fourni dans le kit Arduino, qui possède déjà une datasheet.

> Nous avons élaboré un premier modèle en 2D de notre banc de tests: 
<div align="center"></p>

![Dessin 2D du banc de tests](Images/Dessin_bancTest.jpg "Dessin 2D montage banc de test")

**Figure 29: Dessin 2D du banc de test**

<div align="left"></p>

### Measurement System Analysis






