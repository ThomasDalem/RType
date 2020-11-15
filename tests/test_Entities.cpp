#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Player.hpp"
#include "Entities.hpp"

using namespace std;
using namespace client;
static void redirect_all_std(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//Entitie(s)
Test(Entities, Id, .init = redirect_all_std) {
    Entities _ent(10, 0, "Dani");

    cr_assert(_ent.getId() == 10);
    _ent.setId(20);
    cr_assert(_ent.getId() == 20);
}

Test(Entities, Name, .init = redirect_all_std) {
    Entities _ent(10, 0, "Dani");

    cr_assert(_ent.getName() == "Dani");
    _ent.setName("Didier");
    cr_assert(_ent.getName() == "Didier");
}

Test(Entities, Type, .init = redirect_all_std) {
    Entities _ent1(10, 1, "Dani");
    Entities _ent2(10, 5, "Didier");
    Entities _ent3(10, 9, "Claude");

    cr_assert(_ent1.getEntityType() == 1);
    cr_assert(_ent2.getEntityType() == 5);
    cr_assert(_ent3.getEntityType() == 9);
}

//Player(s)
Test(Player, Id, .init = redirect_all_std) {
    Player player(10);

    cr_assert(player.getId() == 10);
    player.setId(20);
    cr_assert(player.getId() == 20);
}

Test(Player, Room, .init = redirect_all_std) {
    Player player(10);

    player.setRoom(7);
    cr_assert(player.getRoom() == 7);
    player.setRoom(20);
    cr_assert(player.getRoom() == 20);
    cr_assert(player.getRoom() != player.getId());
}

Test(Player, Name, .init = redirect_all_std) {
    Player player(10);

    player.setName("Patrick");
    cr_assert(player.getName() == "Patrick");
}

Test(Player, Admin, .init = redirect_all_std) {
    Player player(10);

    cr_assert(!player.getAdmin());
    player.setAdmin(true);
    cr_assert(player.getAdmin());
    player.setAdmin(false);
    cr_assert(!player.getAdmin());
}
