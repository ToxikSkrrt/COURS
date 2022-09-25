# MOREAU Thomas-Alexandre TG7

import sqlite3

with sqlite3.connect('dmcovid.db') as connexion:
    cursor = connexion.cursor()

    cursor.execute('''SELECT pays.population,countries.population FROM pays JOIN isocodes ON pays.iso3=isocodes.iso3 JOIN countries ON isocodes.iso2=countries.iso2 WHERE pays.iso3='FRA';''')
    # affiche le résultat
    
    for row in cursor:
        print(row)
        
    cursor.close()
    
# Question 1 : La table covid comprend 500003 lignes.
'''
SELECT COUNT(*) FROM covid;
'''

# Question 2 : Le denier jour des relevés de données dans la table covid est le 16/12/2020.
'''
SELECT MAX(jour) FROM covid;
'''

# Question 3 : Le 01/12/2020, il y a eu 176 relevés.
'''
SELECT COUNT(*) FROM covid WHERE jour='2020-12-01';
'''

# Question 4 : Le 01/12/2020, il y a eu 607002 nouveaux cas.
'''
SELECT SUM(cas_nouveau) FROM covid WHERE jour='2020-12-01';
'''

# Question 5 : Le 01/12/2020, 28 pays n'ont pas eu de cas nouveau recensés.
'''
SELECT COUNT(*) FROM covid WHERE jour='2020-12-01' AND cas_nouveau=0;
'''

# Question 6 : L'ID de l'enregistrement est 46479.
#              Le code iso3 du pays ayant eu le plus de cas nouveaux est TUR.
#              Le jour correspondant est le 10/12/2020 et le nombre de cas nouveaux est de 823225.
'''
SELECT id,iso3,jour,cas_nouveau FROM covid WHERE cas_nouveau=(SELECT MAX(cas_nouveau) FROM covid);
'''

# Question 7 : La requête UPDATE ci-dessous permet de modifier l'anomalie.
'''
UPDATE covid SET cas_nouveau=NULL WHERE id=46479;
'''

# Question 8 : Le 01/12/2020, 8364 nouveaux cas ont été recensés pour la France. Le nombre de nouveaux cas pour un million d'habitants pour la France le 01/12/2020 est de 128 nouveaux cas.
'''
SELECT cas_nouveau FROM covid WHERE iso3='FRA' AND jour='2020-12-01';

SELECT (covid.cas_nouveau*1000000)/pays.population FROM covid JOIN pays ON covid.iso3=pays.iso3 WHERE covid.iso3='FRA' AND covid.jour='2020-12-01';
'''

# Question 9 : Pour la France, la valeur maximale de cas nouveaux par million d'habitants a été de 1625 nouveaux cas.
'''
SELECT MAX((covid.cas_nouveau*1000000)/pays.population) FROM covid JOIN pays ON covid.iso3=pays.iso3 WHERE covid.iso3='FRA';
'''

# Question 10 : La requête ci-dessous permet de montrer la population française des tables pays et countries.
'''
SELECT pays.population,countries.population FROM pays JOIN isocodes ON pays.iso3=isocodes.iso3 JOIN countries ON isocodes.iso2=countries.iso2 WHERE pays.iso3='FRA';
'''