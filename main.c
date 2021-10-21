#include "tools/player.c"
#include "tools/gallows.c"
#include "tools/interface.c"

typedef int lang;

int main(){
    lang lang=choose_lang();
    printf("%d",lang);
    write(lang,"gecit szoptam");
    return 0;
}