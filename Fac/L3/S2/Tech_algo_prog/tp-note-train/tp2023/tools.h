#ifndef TOOLS_H_
#define TOOLS_H_

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

// Échange x et y en utilisant la variable z (qui doit être de même type)
#define SWAP(x, y, z) (z) = (x), (x) = (y), (y) = (z)

// Retourne le maximum de deux entiers.
int max(int x, int y);

// Retourne le minimum de deux entiers.
int min(int x, int y);

#endif // TOOLS_H_
