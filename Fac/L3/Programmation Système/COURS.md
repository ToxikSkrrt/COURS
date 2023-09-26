# COURS

## Requesting privileges

- We need a safe way to do it
  - We already have a mechanism to switch to kernel mode : **interrupts** !  

- Let's use a specific instruction to raise a software interrupt
  - int 80h (Linux x86 32bit kernels)
  - syscall (Linux x86 64bit kernels)

- Idea
  - The kernel has a set of routines which can be useful to processes
  - to invoke one of these routines, a process performs a system call
    - How do we specify the desired routine ?

## System calls

- Exemple :
  - C implementation of the file "getpid" function in libc
  ```c
  pid_t getpid(void) {
    mov __NR_getpid, %eax
    syscall
    ret
  }
  ```

## System Programming : File Management

une fois un fichier ouvert (= processus toujours en cours) -> impossible de changer les droits en direct de la personne ayant ouvert le fichier 

errno : variable d'erreur (pour fprintf)

hexdump : commande terminal pour voir le contenu en hexa d'un fichier (pour voir le nombre précis de caractères par exemple)

## Copying with structured data

Representation ASCII :
```c
int i = ...;
int fd = open();
char buffer[32];
sprintf(buffer, "%d", i);
write(fd, buffer, strlen(buffer));

sprintf(char + buffer, ...);
```

Writing the binary representation of a File :

```c
void ecrire(int fd) {
  int i = 31;
  write(fd, &i, sizeof(int));
}
```

SEEK_SET / SEEK_CUR / SEEK_END

seek.c :

```c
lseek(fd, pos, SEEK_SET);
```

reverse-rel :
```c
off_t pos;

pos = lseek(fd, -1, SEEK_END);

while(pos >= 0) {
  char c;
  int n = read(fd, &c, 1);
  check_syscall(n, "read");
  check(n == 1, "read");

  write(STDOUT_FILENO, &c, 1);

  pos = lseek(fd, -2, SEEK_CUR);
}
```

reverse.c :

```c
off_t taille;

taille = lseek(fd, 0, SEEK_END);

for(off_t pos = taille - 1; pos >= 0; pos--) {
  
}
```

## 

