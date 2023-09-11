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