       #include <stdlib.h>
       #include <stdio.h>
       #include <mcheck.h>

       int
       main(int argc, char *argv[])
       {
           char *p;

           if (mcheck(NULL) != 0) {
               fprintf(stderr, "mcheck() failed\n");

               exit(EXIT_FAILURE);
           }

           p = malloc(1000);

           fprintf(stderr, "About to free\n");
           free(p);
           fprintf(stderr, "\nAbout to free a second time\n");
           free(p);

           exit(EXIT_SUCCESS);
       }
