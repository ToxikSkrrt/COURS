import sqlite3

# keys=['iso', 'country', 'Capital', 'Area', 'Population', 'Continent', 'CurrencyCode', 'CurrencyName']

with sqlite3.connect('MaBase.db') as connexion:
    
    # le résultat d'exécution sera une liste d'instances de sqlite3.Row
    # (sinon liste de tuples)
    # connexion.row_factory = sqlite3.Row
    # utilisation de Row.keys()
    #    row = cursor.fetchone()
    #    print(row.keys())
    cursor=connexion.cursor()
    
    # Nombre d'enregistrements de la table
    print("---------------------------\nNombre d'enregistrements de la table")
    cursor.execute("SELECT COUNT(*) FROM countries")
    for row in cursor:
        print(row)    
    
    # Liste des pays avec monnaie euro
    print("---------------------------\Liste des pays avec monnaie euro")
    cursor.execute("SELECT * FROM countries WHERE CurrencyCode='EUR'")
    for row in cursor:
        print(row)
        
    # Nombre de pays avec monnaie euro
    print("---------------------------\nNombre de pays avec monnaie euro")
    cursor.execute("SELECT COUNT(*) FROM countries WHERE CurrencyCode='EUR'")
    for row in cursor:
        print(row)
        
    # Population totale des pays avec monnaie euro
    print("---------------------------\nPopulation totale des pays avec monnaie euro")
    cursor.execute("SELECT SUM(Population) FROM countries WHERE CurrencyCode='EUR'")
    for row in cursor:
        print(row)
        
    # Les pays de la zone euro trié par population décroissante
    print("---------------------------\nLes pays de la zone euro trié par population décroissante")
    cursor.execute("SELECT country,Population FROM countries WHERE CurrencyCode='EUR' ORDER BY Population DESC")
    for row in cursor:
        print(row)
        
    # Le pays le plus peuplé, en utilisant un SELECT imbriqué
    print("---------------------------\nLe pays le plus peuplé, en utilisant un SELECT imbriqué")
    cursor.execute("SELECT country FROM countries WHERE Population=(SELECT MAX(Population) FROM countries)")
    for row in cursor:
        print(row)
    # Le pays le plus peuplé sans utiliser de SELECT imbriqué    
    print("---------------------------\nLe pays le plus peuplé sans utiliser de SELECT imbriqué")
    cursor.execute("SELECT MAX(Population), country FROM countries")
    for row in cursor:
        print(row)

    # Le pays avec la plus forte densité de population
    print("---------------------------\nLe pays avec la plus forte densité de population")
    cursor.execute("SELECT MAX(Population/Area),country FROM countries")
    for row in cursor:
        print(row)