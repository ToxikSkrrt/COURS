# NOTES

## Jump

```c
jmp_buf env;    // init buffer pour jump
volatile int i = 0;
setjmp(env);    // set jump à env

if (i < 10) {
    i++;
    printf("%d\n", i);
    longjmp(env, 1);
}
```

=> fonctionne pas car tout est dans la meme fonction

```c
void handler(int sig) {
    ...
    siglongjmp(env, sig);   // same que longjmp mais gère le masque en meme temps 
}

sigsetjmp(env);     // idem
```

