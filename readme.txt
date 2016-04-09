Compilando a biblioteca
$ gcc -c deadlock.c -o deadlock.o

Gerando a biblioteca
$ ar rcs libdeadlock.a deadlock.o
$ ar tv libdeadlock.a //visualizar info
$ nm -s --defined-only libdeadlock.a

Compilando código MAIN() utilizando a biblioteca
$ gcc <código.c> -L. libdeadlock.a -o <nome de bin> -pthread


OBS: ESSES PASSOS FUNCIONAM SE TODOS OS ARQUIVOS ESTIVEREM NO MESMO DIRETÓRIO