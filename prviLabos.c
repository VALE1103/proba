#include <stdio.h>

//funkcija za izračun binomnog koeficijenta (PROBAAAAAAAAAA :):):):):))
unsigned long long binomniKoeficijent(unsigned long long n, unsigned long long k) {

    //osnovna provjera kod binomnog koeficijenta, rezultat je automatski 0
    if (k > n) {
        return 0;
    }

    unsigned long long rezultat = 1;

    //koristimo simetriju binomnog koeficijenta za lakši i brži račun
    if (k > n - k) {
        k = n - k;
    }

    for (unsigned long long i = 0; i < k; ++i) { //npr. za 6c4 imamo: (6 * 5 * 4 * 3) / (1 * 2 * 3 * 4)
        rezultat *= (n - i); //ovo je upravo izračun brojnika, ovo radi 6 * 5 * 4 * 3 za naš primjer
        rezultat /= (i + 1); //ovo je upravo izračun nazivnika, ovo radi upravo k!, 1 * 2 * 3 * 4 za naš primjer
    }

    return rezultat;
}

unsigned long long generirajRjesenja(unsigned long long m_, unsigned long long a_1, unsigned long long a_2, unsigned long long a_3, unsigned long long a_4) {

    unsigned long long m = m_;
    unsigned long long a1 = a_1 + 1; //odmah si uvećamo eksponente za koje znamo da su veći za 1
    unsigned long long a2 = a_2 + 1;
    unsigned long long a3 = a_3 + 1;
    unsigned long long a4 = a_4 + 1;

    unsigned long long polje[8] = {0, a1, 0, a2, 0, a3, 0, a4}; //množenje polinoma preko polja

    int cardA = 0; //izračun kardinaliteta skupa ai
    for (int i = 0; i < 8; i++) {
        if (polje[i] != 0) {
            ++cardA;
        }
    }

    unsigned long long potPolje1[4]; //umnozak prve 2 zagrade
    unsigned long long potPolje2[4]; //umnozak druge 2 zagrade
    unsigned long long mnoziPol[16]; //umnozak svih zagrada

    int d = 0;
    for (int i = 0; i < 2; i++) { //množenje prve 2 zagrade
        for (int j = 2; j < 4; j++) {
            potPolje1[d++] = polje[i] + polje[j];
        }
    }   
    potPolje1[d] = '\0';

    int t = 0;
    for (int i = 4; i < 6; i++) { //množenje druge 2 zagrade
        for (int j = 6; j < 8; j++) {
            potPolje2[t++] = polje[i] + polje[j];
        }
    }
     potPolje2[t] = '\0';

    int l = 0;
    for (int i = 0; i < 4; i++) { //množenje 2 novonastale zagrade u konačan rezultat množenja svih ovih zagrada
        for (int j = 0; j < 4; j++) {
            mnoziPol[l++] = potPolje1[i] + potPolje2[j];
        }
    }
    mnoziPol[l] = '\0'; //sada u polju čuvam eksponente svih članova nastalih tim množenjem

    int brojacKaova = 0;  
    for (int i = 0; i < 16; i++) {
        if (mnoziPol[i]  <= m) {
            ++brojacKaova; //samo bilježimo koliko ima eksponenata manjih od mog "m"
        }
    }

    if (brojacKaova == 0) {
        return 0;
    }

    unsigned long long poljeKaova[brojacKaova];
    int predznakKaova[brojacKaova]; //ovdje ću bilježit s kojim predznakom ću računat binomni koeficijent

    int poljeMinusPlus[16] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};

    for (int i = 0, j = 0, k = 0; i < 16; i++) {
        if (mnoziPol[i] <= m) { //u slučaju da naletimo na eksponent koji treba nadopuniti do "m"...
            poljeKaova[j++] = m - mnoziPol[i]; //stavi ga u ovo polje i provjeri s kojim predznakom ćemo za njega zvati bin.koef!
            if (i == 0 || i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 12 || i == 15) {
            predznakKaova[k++] = 1; //predznak "+" za binomni koeficijent
            } else {
            predznakKaova[k++] = 0; //predznak "-" za binomni koeficijent
            }
        }
    }

    unsigned long long medjuRezultat = 0ull;

    for (int i = 0; i < brojacKaova; i++) {
        unsigned long long binKoef = binomniKoeficijent(poljeKaova[i] + (cardA - 1), (cardA - 1));
        if (predznakKaova[i] == 0) {
            binKoef *= (-1); //tj. računamo bin. koef. s predznakom "-"!!!
        }
        medjuRezultat += binKoef;
    }

    return medjuRezultat;
}

int main() {

    unsigned long long m, a1, a2, a3, a4; //priprema parametara za ovaj labos

    //unos podataka od korisnika
    printf("Unesite nenegativan cijeli broj m: ");
    scanf("%llu", &m);
    printf("Unesite nenegativan cijeli broj a_1: ");
    scanf("%llu", &a1);
    printf("Unesite nenegativan cijeli broj a_2: ");
    scanf("%llu", &a2);
    printf("Unesite nenegativan cijeli broj a_3: ");
    scanf("%llu", &a3);
    printf("Unesite nenegativan cijeli broj a_4: ");
    scanf("%llu", &a4);

    //poziv funkcije za izračun broja rješenja
    unsigned long long rez = generirajRjesenja(m, a1, a2, a3, a4);

    //ispis rezultata cijelog labosa
    printf("Broj rjesenja trazene jednadzbe je %llu\n", rez);

    return 0;
}
