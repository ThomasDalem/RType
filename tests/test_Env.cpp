#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Exception.hpp"
#include "ErrorHandler.hpp"

using namespace std;
using namespace client;
static void redirect_all_std(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//Exceptions
Test(Exception, catch, .init = redirect_all_std) {
    try {
        throw Exception("Test Successfull");
    } catch (Exception &e) {
        cr_assert(strcmp(e.what(), "Test Successfull") == 0);
    }
}

//ErrorHandler
Test(ErrorHandler, EnvDisplayer, .init = redirect_all_std) {
    char *env[3];
    ErrorHandler errhdl;

    env[0] = strdup("Hello");
    env[1] = strdup("World");
    env[2] = strdup("!");
    cr_assert(!errhdl.isDisplayEnv(env));
}

Test(ErrorHandler, Arguments, .init = redirect_all_std) {
    char *tab[3];
    ErrorHandler errhdl;
    vector<string> vect;

    tab[0] = strdup("Hello");
    tab[1] = strdup("World");
    tab[2] = strdup("!");
    vect = errhdl.getArgs(tab);
    for (size_t i = 0; i < vect.size(); i ++)
        cr_assert(vect[i] == string(tab[i]));
}
