#include "../../include/entity/list.hpp"
using namespace std;
monsterList cons_empty(){
    return nullptr;
}

monsterList addMonster(Monster *m, monsterList M){
    monsterList monster;

    monster = (monsterList)malloc(sizeof(Monster*));
    monster->m = m;
    monster->suivant = M;

    return monster;
}

bool isEmpty(monsterList M){
    return M == nullptr;
}

Monster* head(monsterList M){
    if(isEmpty(M)){
      cerr << "The list is empty: head" << endl;
      exit (0);
    }
    return M->m;
}

monsterList rest(monsterList M){
    return M->suivant;
}

void free_monsterList (monsterList M){
    if (!isEmpty(M)){
      free_monsterList(rest(M)) ;
      free (M);
    }
}