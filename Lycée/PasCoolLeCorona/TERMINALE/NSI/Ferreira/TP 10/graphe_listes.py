def creer_graphe(sommets):
    # à partir de la liste des sommets S, produit le graphe (S, ∆)
    return {key: [] for key in sommets}


def ajouter_arete(graphe, x, y):
    # à partir d'un graphe (S, A) et des sommets s1 et s2 appartenant à S,
    # produit le graphe (S, A ∪ {(s1,s2)})
    if x in graphe and y in graphe:
        if y not in graphe[x]:
            graphe[x].append(y)
        if x not in graphe[y]:
            graphe[y].append(x)  # non-orienté


def sommets(graphe):
    # à partir d'un graphe (S, A), produit la liste de sommets S
    return list(graphe.keys())


def voisins(graphe, sommet):
    # à partir du graphe (S, A) et du sommet s,
    # produit la liste des voisins de s
    return list(graphe[sommet])

# FONCTIONS SUPPLÉMENTAIRE

def degre(G, s):
    v = voisins(G, s)
    acc = 0
    for i in v:
        acc += 1
    return acc

def est_isole(G, s):
    return degre(G, s) == []

def degre_moyen(G):
    val = list(G.values())
    count = 0
    for i in val:
        count += 1
    if count == 0:
        return 0
    else:
        j = 0
        acc = 0
        while j < count:
            for k in val[j]:
                acc += 1
            j += 1
        return acc
         
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
    ajouter_arete(f, 'C', 'B')
    ajouter_arete(f, 'C', 'A')
    ajouter_arete(f, 'C', 'D')
    ajouter_arete(f, 'D', 'A')
    ajouter_arete(f, 'D', 'C')
    print(f'\nGraphe (f) : {f}')
    
    g = creer_graphe(['A', 'B', 'C'])
    ajouter_arete(g, 'A', 'B')
    ajouter_arete(g, 'B', 'A')
    ajouter_arete(g, 'C', 'A')
    print(f'\nGraphe (g) : {g}')