# run
    compile - 
        gcc -c blink.c -o blink.o

        complile main - 
            gcc -o robotTest main.c blink.o -l bcm2835
    run - 
        ./robotTest

# inits
    PWMInit because in mine at least the first line in it calls i2cinit then initMotors then init

# run
    left -> run(RELEASE, 0)
    right -> run(RELEASE, 1)