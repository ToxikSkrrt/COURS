def creer_graphe(sommets):
    # à partir de la liste des sommets S, produit le graphe (S, ∆)
    dimension = len(sommets)
    adjacence = [[0 for i in range(dimension)] for j in range(dimension)]
    return (sommets, adjacence)


def ajouter_arete(graphe, s1, s2):
    # à partir d'un graphe (S, A) et des sommets s1 et s2 appartenant à S,
    # produit le graphe (S, A ∪ {(s1,s2)})
    i = graphe[0].index(s1)
    j = graphe[0].index(s2)
    graphe[1][i][j] = 1
    graphe[1][j][i] = 1  # non-orienté
    return graphe


def sommets(graphe):
    # à partir d'un graphe (S, A), produit la liste de sommets S
    return graphe[0]


def voisins(graphe, sommet):
    # à partir du graphe (S, A) et du sommet s,
    # produit la liste des voisins de s
    i = sommets(graphe).index(sommet)
    return [sommets(graphe)[j]
            for j in range(len(sommets(graphe))) if graphe[1][i][j] == 1]

# FONCTIONS SUPPLÉMENTAIRES

def degre(G, s):
    v = voisins(G, s)
    acc = 0
    for i in v:
        acc += 1
    return acc

def est_isole(G, s):
    return degre(G, s) == []

def degre_moyen(G):
    d = 0
    acc = 0
    for i in G[0]:
        d += degre(G, i)
        acc += 1
    return d / acc
         
def sont_voisins(G, s1, s2):
    v = voisins(G, s2)
    for i in v:
        if s1 == i:
            return True
    return False


if __name__ == '__main__':
    a = creer_graphe(['A', 'B', 'C', 'D'])
    ajouter_arete(a, 'A', 'B')
    ajouter_arete(a, 'A', 'C')
    ajouter_arete(a, 'B', 'A')
    ajouter_arete(a, 'B', 'C')
    ajouter_arete(a, 'B', 'D')
    ajouter_arete(a, 'C', 'A')
    ajouter_arete(a, 'C', 'B')
    ajouter_arete(a, 'D', 'B')
    print(f'Graphe (a) : {a}')
    
    f = creer_graphe(['A', 'B', 'C', 'D'])
    ajouter_arete(f, 'A', 'B')
    ajouter_arete(f, 'A', 'C')
    ajouter_arete(f, 'A', 'D')
    ajouter_arete(f, 'B', 'A')
    ajouter_arete(f, 'B', 'C')
    ajouter_arete(f, 'C', 'A')
    ajouter_arete(f, 'C', 'B')
    ajouter_arete(f, 'C', 'D')
    ajouter_arete(f, 'D', 'A')
    ajouter_arete(f, 'D', 'C')
    print(f'\nGraphe (f) : {f}')
    
    g = creer_graphe(['A', 'B', 'C'])
    ajouter_arete(g, 'A', 'B')
    ajouter_arete(g, 'A', 'C')
    ajouter_arete(g, 'B', 'A')
    ajouter_arete(g, 'C', 'A')
    print(f'\nGraphe (g) : {g}')