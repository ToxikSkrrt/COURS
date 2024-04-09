#include "main.h"

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

int num_tests = 10, min_nb_digits = 3, max_nb_digits = 10, nb_errors_max = 1,
    errors = 0, seed = -1;

short BASE = 10;

// clang-format off
static struct option long_options[] = {
    {"help"    , no_argument,       NULL, 'h'},
    {"comp"    , no_argument,       NULL, 'c'},
    {"add"     , no_argument,       NULL, 'a'},
    {"sub"     , no_argument,       NULL, 's'},
    {"rec"     , no_argument,       NULL, 'r'},
    {"kar"     , no_argument,       NULL, 'k'},
    {"num"     , required_argument, NULL, 'n'},
    {"min"     , required_argument, NULL, 'm'},
    {"max"     , required_argument, NULL, 'M'},
    {"nberr"   , required_argument, NULL, 'e'},
    {"base"    , required_argument, NULL, 'b'},
    {"seed"    , required_argument, NULL, 'S'},
    //
    {NULL, 0, NULL, 0}};
// clang-format on

void usage(char *argv[]) {
  printf("\nUsage: %s [options]\n\n", argv[0]);
  printf("Sans option, le programme lance le mode calculatrice.\n\n"
         "Options disponibles :\n"
         "\t--help ou -h :"
         "\n\t    Affiche cette aide.\n"
         "\n"
         "\t--comp ou -c :"
         "\n\t    Passe en mode tests aléatoires pour la comparaison.\n"
         "\n"
         "\t--add ou -a :"
         "\n\t    Passe en mode tests aléatoires pour l'addition.\n"
         "\n"
         "\t--sub ou -s :"
         "\n\t    Passe en mode tests aléatoires pour la soustraction.\n"
         "\n"
         "\t--kar ou -k :"
         "\n\t    Passe en mode tests aléatoires pour la multiplication "
         "\"Karatsuba\".\n"
         "\n"
         "\t--rec ou -r :"
         "\n\t    Passe en mode tests aléatoires pour la multiplication "
         "récursive \"naïve\".\n"
         "\n"
         "\t--num=<entier> :"
         "\n\t    Définit le nombre de tests aléatoires (%d par défaut).\n"
         "\n"
         "\t--min=<entier> :"
         "\n\t    Définit la taille minimale des entiers pour les tests "
         "aléatoires (%d par défaut).\n"
         "\n"
         "\t--max=<entier> :"
         "\n\t    Définit la taille maximale des entiers pour les tests "
         "aléatoires (%d par défaut).\n"
         "\n"
         "\t--nberr=<entier> :"
         "\n\t    Définit le nombre d'erreurs reportées (%d par défaut).\n"
         "\n"
         "\t--base=<entier> :"
         "\n\t    Définit la base entre 2 et 10 (%d par défaut).\n"
         "\n"
         "\t--seed=<entier> :"
         "\n\t    Définit la graine du générateur aléatoire pour les tests.\n"
         "\n"
         "\n",
         num_tests, min_nb_digits, max_nb_digits, nb_errors_max, BASE);
}

bool comp_mode, add_mode, sub_mode, mrec_mode, mkar_mode;

void parse_argv(int argc, char *argv[]) {
  for (;;) {
    // Lecture des options dans long_options: remplit les flags ou
    // renvoie dans c le code de l'option et dans optarg son paramètre
    char c = getopt_long(argc, argv, "hcasrknmMebS", long_options, NULL);
    if (c == -1)
      break; // fin de lecture des options

    int value = 1;

    if (optarg) {
      value = atoi(optarg);
    }

    switch (c) {
    case 'h':
      usage(argv);
      exit(EXIT_SUCCESS);

    case 'c':
      comp_mode = true;
      break;

    case 'a':
      add_mode = true;
      break;

    case 's':
      sub_mode = true;
      break;

    case 'r':
      mrec_mode = true;
      break;

    case 'k':
      mkar_mode = true;
      break;

    case 'n':
      num_tests = value;
      break;

    case 'm':
      min_nb_digits = value;
      break;

    case 'M':
      max_nb_digits = value;
      break;

    case 'e':
      nb_errors_max = value;
      break;

    case 'b':
      BASE = value;
      if (BASE < 2 || BASE > 10) {
        fprintf(stderr, "%s La base doit être entre 2 et 10\n\n", KO);
        usage(argv);
        exit(EXIT_FAILURE);
      }
      break;

    case 'S':
      seed = value;
      if (seed <= -1) {
        fprintf(stderr, "%s La graine doit être positive\n\n", KO);
        usage(argv);
        exit(EXIT_FAILURE);
      }
      break;

    default:
      usage(argv);
      exit(EXIT_FAILURE);
      break;
    }
  }
}

int vsum(int n, ...) {
  va_list ap;
  va_start(ap, n);
  int s = 0;
  for (int i = 0; i < n; i++) {
    s += va_arg(ap, int);
  }
  va_end(ap);
  return s;
}

int main(int argc, char *argv[]) {
  parse_argv(argc, argv);

  int sum = vsum(5, comp_mode, add_mode, sub_mode, mrec_mode, mkar_mode);

  if (sum > 1) {
    fprintf(stderr,
            "%s Au plus une des options -c, -a, -s, -r ou -k doit être "
            "donnée\n\n",
            KO);
    usage(argv);
    exit(EXIT_FAILURE);
  }

  if (min_nb_digits > max_nb_digits || min_nb_digits < 1) {
    fprintf(
        stderr,
        "%s La taille minimale des entiers doit être positive et inférieure ou "
        "égale à la taille maximale.\n\n",
        KO);
    usage(argv);
    exit(EXIT_FAILURE);
  }

  if (sum == 0) { // Pas d'option, on lance le mode calculatrice
    printf("\tMode calculatrice. Calculs en base %d.\n\n", BASE);
    if (seed != -1)
      printf("\tGraine du générateur aléatoire ignorée.\n\n");

    printf("%s", PROMPT);
    fflush(stdout);

    yyparse();

    exit(EXIT_SUCCESS);
  }

  if (seed == -1)
    seed = time(NULL) % 1000;
  srandom((unsigned int)seed);
  printf("\tGraine du générateur aléatoire : %d\n\n", seed);

  number *(*test_function)(number *, number *);
  void (*gmp_function)(mpz_t, const mpz_t, const mpz_t);

  if (comp_mode) {
    printf("\tComparaison : %d test(s) de nombres ayant entre %d et %d "
           "chiffres\n",
           num_tests, min_nb_digits, max_nb_digits);
    for (int i = 0; i < num_tests; i++) {
      int nb_digits_X =
          (rand() % (max_nb_digits - min_nb_digits + 1)) + min_nb_digits;
      int nb_digits_Y =
          (rand() % (max_nb_digits - min_nb_digits + 1)) + min_nb_digits;

      number *X    = number_random(nb_digits_X);
      number *Y    = number_random(nb_digits_Y);

      int computed = 0, expected = 0;
      char *sX;
      char *sY;

      if (!check_comparison(X, Y, &sX, &sY, &computed, &expected)) {
        errors++;
        if (nb_errors_max--) {
          fprintf(stderr,
                  "\n%s Erreur de comparaison - X = %s,\tY = %s,\n"
                  "   Calculé = %d,\tAttendu = %d\n",
                  KO, sX, sY, computed, expected);
        } else
          exit(EXIT_FAILURE);
      }

      number_multiple_free(X, Y, NULL);
      multiple_free(sX, sY, NULL);
    }
  }

  if (add_mode) {
    printf("\tAddition : %d test(s) de nombres ayant entre %d et %d chiffres\n",
           num_tests, min_nb_digits, max_nb_digits);
    test_function = number_addition;
    gmp_function  = mpz_add;
  }

  if (sub_mode) {
    printf("\tSoustraction : %d test(s) de nombres ayant entre %d et %d "
           "chiffres\n",
           num_tests, min_nb_digits, max_nb_digits);
    test_function = number_substraction;
    gmp_function  = mpz_sub;
  }

  if (mkar_mode) {
    printf("\tMultiplication Karatsuba : %d test(s) de nombres ayant entre %d "
           "et %d chiffres\n",
           num_tests, min_nb_digits, max_nb_digits);
    test_function = number_multiplication_karatsuba;
    gmp_function  = mpz_mul;
  }

  if (mrec_mode) {
    printf("\tMultiplication récursive naïve : %d test(s) de nombres ayant "
           "entre %d et %d chiffres\n",
           num_tests, min_nb_digits, max_nb_digits);
    test_function = number_multiplication_recursive;
    gmp_function  = mpz_mul;
  }

  if (add_mode || sub_mode || mrec_mode || mkar_mode) {
    for (int i = 0; i < num_tests; i++) {
      int nb_digits_X =
          (random() % (max_nb_digits - min_nb_digits + 1)) + min_nb_digits;
      int nb_digits_Y =
          (random() % (max_nb_digits - min_nb_digits + 1)) + min_nb_digits;

      number *X = number_random(nb_digits_X);
      number *Y = number_random(nb_digits_Y);

      number *R = test_function(X, Y);

      char *sX  = number_to_string(X);
      char *sY  = number_to_string(Y);
      char *sR  = number_to_string(R);

      char *mpz_result;

      if (!check_result(X, Y, R, gmp_function, &mpz_result)) {
        errors++;
        if (nb_errors_max--) {
          fprintf(stderr,
                  "\n%s Erreur - X = %s,\tY = %s,\n"
                  "   Calculé = %s,\tAttendu = %s.\n",
                  KO, sX, sY, sR, mpz_result);
        } else
          exit(EXIT_FAILURE);
      }

      multiple_free(sX, sY, sR, mpz_result, NULL);
      number_multiple_free(X, Y, R, NULL);
    }
  }
  if (errors == 0)
    printf("\n\t%s Tests OK !\n", OK);

  return EXIT_SUCCESS;
}
