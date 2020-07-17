# SpaceShooters-GasynaGawron



Projekt dwuosobowy (Paweł Gawron A5/L9, Bartłomiej Gasyna A5/L9)z obsługą sieci 

W tej grze sterujemy statkiem kosmicznym który posiada 3 życia. Plansza gry jest złożona z kilku okręgów po którym poruszają się statki, z których środka wylatują złe asteroidy oraz dobre bonusy. Naszym zadaniem jest uniknięcie zderzenia poprzez zejście z toru asteroidy lub zniszczenie jej za pomocą lasera.

 
![](https://github.com/BartlomiejGasyna/EventHorizon/blob/master/makieta.jpeg)

Runda kończy się w momencie utracenia ostatniego życia uderzenia w asteroidę , przyznając punkty:

* w trybie singleplayer:

punkty oparte są na czasie (im dłużej uda nam się pozostać przy życiu, tym więcej punktów otrzymujemy) oraz na niszczeniu asteroid - dodatkowe punkty

 

* w trybie multiplayer:

Rywalizacja polega na zdobyciu większej ilości punktów w wyznaczonym czasie lub zestrzelenie statku przeciwnika (więcej o trybie multiplayer na samym dole)

 

## Asteroidy: 

Pojawiają się w środku planszy i w sposób losowy zmierzają we wszystkich możliwych kierunkach w strony krawędzi - zaznaczonych na rysunku liniami.

niszczenie - asteroidy dzielimy na 3 rodzaje względem niszczenia przez laser:

 

* małe ->po 1 uderzeniu

* średnie -> po 2 uderzeniach

* duże -> po 3 uderzeniach

 

W miarę upływu czasu zwiększa się ilość asteroid, ich prędkość oraz częstość wystąpienia większych asteroid

 

ich rozmiar w miarę przebytej drogi zwiększa się, przy końcowym momencie lotu zaś zmniejsza się, dając uczucie omijania danego elementu, tak jakby oddalał się.

 

## Bonus:

złapanie “bonusu” graficznie reprezentowanego jako prezent skutkuje dodaniem lepszej broni (laser który może strzelać szybciej lub kilkoma strumieniami jednocześnie) lub dodatkowego życia

## Statek:

* model graficzny - nie będzie zwykłym prostokątem

>Spaceship 1

![](https://github.com/BartlomiejGasyna/EventHorizon/blob/master/Event%20Horizon/Resources/Spaceship1.png)

>Spaceship 2

![](https://github.com/BartlomiejGasyna/EventHorizon/blob/master/Event%20Horizon/Resources/Spaceship2.png)
* poruszanie się po rzędach okręgów strzałki góra/dół

* ruchy prawo/lewo na każdym z okręgów ( pełne 360 stopni, całkowita swoboda)





## Multiplayer:

W trybie rzeczywistym gracze widzą wzajemnie swoje statki oraz ich położenie na planszy, na obu ekranach wyświetla się jednocześnie to samo. każdy gracz ma 3 życia, odejmowanie przy zderzeniu z asteroidą. Każdy bonus może być zebrany tylko przez jednego gracza - kto pierwszy ten lepszy.



>Podczas gry widoczne statki obydwu graczy między którymi istnieje możliwość kolizji jak i zestrzelenie siebie nawzajem w przypadku gdy jeden z graczy znajduje się na okręgu bliższym centrum. 

# Instrukcja obsługi:
## Odpalenie gry w trybie dwuosobowym:
1. Wszystkie programy znajdują się w folderze Event Horizon,
2. Uruchomienie programów EventHorizon_Client1 oraz EventHorizon_Client2 w dowolnej kolejności,
3. Uruchomienie programu EventHorizon_Serwer.

## Klawiszologia:
1. Statkiem poruszamy lewą oraz prawą strzałką odpowiednio zgodnie z ruchem wskazówek zegara oraz przeciwnie,
2. Aby zniszczyś asteroidy strzelamy lewym przyciskiem myszy.

## Mechanika:
- gracz ma trzy życia,
- za każdorazowe wlecenie statkiem na asteroide gracz traci jedno życie,
- gdy gracz straci trzy życia przegrywa,
- gracz dostaje jeden punkt za każde trafienie asteroidy,
- zebranie bonusu w postaci gwiazdki to dodatkowe dziesięć punktów.

## Wideo prezentujące działanie projektu: 
https://www.youtube.com/watch?v=5oRpJkVI2Qs&feature=youtu.be&fbclid=IwAR3WHzFLmJMRYo2swAmkN7rsKRBhnwa11QAQpJF0Oo27iuv7Jfs7AoG-GMo

# Podział odpowiedzialności:
## Bartłomiej Gasyna:
- tworzenie i handling statków
- tryb sieciowy,
- ruch obiektów,
- grafiki, animacje,
- refaktoryzacja

## Paweł Gawron:
- tworzenie i handling asteroid, laserów oraz bonusów
- interakcje między obiektami,
- dokumentacja doxygen,
- kontroler
- refaktoryzacja

# Źródła tekstur:
- backgroundbase.png - https://pl.pinterest.com/pin/400750066824198708/
- backgroundbase2.png - https://pl.pinterest.com/pin/400750066824198708/
- bonus.png - https://pl.pinterest.com/pin/692921092646381596/
- large_asteroid.png - http://pixelartmaker.com/art/6dab6ecf5720fdf
- medium_asteroid.png - http://pixelartmaker.com/art/b02b88d8461a4fb
- small_asteroid.png - https://opengameart.org/content/a-layered-asteroid-rock
- laser.png - http://pixelartmaker.com/art/c15aa99396c3429
- Spaceship1.png - Bartłomiej Gasyna
- Spaceship2.png - Bartłomiej Gasyna
