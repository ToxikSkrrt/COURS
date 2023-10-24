# Correction DS entrainement (2020)

## Exo 1

### Q1

SIG_PIPE.  
s'il reste des éléments dans le tube, il les lit sinon renvoie 0

### Q2

stdout -> permet de manipuler des fichiers avec la lib C (type : FILE *)  
STDOUT_FILENO -> descripteur de fichier (type = int (= 1))

## Exo 2

### Q1

```c
int read_next(int fd, struct article *ptr) {
    while (true) {
        int n = read(fd, ptr, sizeof(struct article));
        if (n == 0) {
            return -1;
        }
        if (ptr->ref > 0) {
            return 0;
        }
    }

    return 0;
}
```

### Q2

```c
int read_next_skip(int fd, struct article *ptr) {
    lseek(fd, ptr->skip, SEEK_CUR);
    int n = read(fd, ptr, sizeof(struct article));
    if (n == 0) {
        return -1;
    }
    assert(ptr->ref > 0)

    return 0;
}
```

### Q3

```c
void add_new_ref(char *filename, int ref, char *name);
```

**CORRECTION SUR MOODLE AAAAAH**