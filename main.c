#include "jatekos.c"
#include "akaszto.c"
#include "felulet.c"

typedef int lang;

int main(){
    lang lang=choose_lang();
    printf("%d",lang);
    write(lang,"gecit szoptam");
    return 0;
}