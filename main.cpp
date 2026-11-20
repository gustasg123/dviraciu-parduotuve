#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

string kategorijos[100];
string prekiuPavadinimai[100];
double vienetoKainos[100];
int uzsakytiKiekiai[100];
int prekiuSkaicius;

bool nuskaitytiDuomenis(string kategorijos[], string prekiuPavadinimai[], double vienetoKainos[], int uzsakytiKiekiai[], int &prekiuSkaicius) 
{

    ifstream failas("uzsakymas.txt");

    if (!failas.is_open())
    {
        cout << "Klaida: Nepavyko atidaryti failo!" << endl;
        return false;
    }

    failas >> prekiuSkaicius;

    if (!failas) {
        cout << "Klaida: Nepavyko nustatyti prekiu skaiciaus!" << endl;
        return false;
    }

    if (prekiuSkaicius < 1 || prekiuSkaicius > 100) 
    {
        cout << "Klaida: Netinkamas prekiu skaicius!" << endl;
        return false;
    }

    failas.ignore();

    for (int i = 0; i < prekiuSkaicius; i++)
    {
        getline(failas, kategorijos[i], ';');

        if (!failas)
        {
            cout << "Klaida: Nepavyko kategorijos nuskaitymas!" << endl;
            return false;
        }

        if (kategorijos[i] != "Dviraciai" &&
            kategorijos[i] != "Dalys" &&
            kategorijos[i] != "Aksesuarai")
        {
            cout << "Klaida: Netinkama prekes kategorija!" << endl;
            return false;
        }
        getline(failas, prekiuPavadinimai[i], ';');

        if (!failas)
        {
            cout << "Klaida: Nepavyko pavadinimo nuskaitymas!" << endl;
            return false;
        }

        failas >> vienetoKainos[i];

        if (!failas) {
            cout << "Klaida: Nepavyko nustatyti prekes vieneto kainos!" << endl;
            return false;
        }

        if (vienetoKainos[i] <= 0)
        {
            cout << "Klaida: Prekes vieneto kaina netinkama!" << endl;
            return false;
        }
        failas.ignore();
        
        failas >> uzsakytiKiekiai[i];

        if (!failas) {
            cout << "Klaida: Nepavyko nustatyti uzsakyto kiekio!" << endl;
            return false;
        }

        if (uzsakytiKiekiai[i] <= 0)
        {
            cout << "Klaida: Prekes uzsakytas kiekis netinkamas!" << endl;
            return false;
        }
        failas.ignore();
    }
    failas.close();
    return true;
}

void perziuretiPrekes(string kategorijos[], string prekiuPavadinimai[], double vienetoKainos[], int uzsakytiKiekiai[], int prekiuSkaicius) 
{
    for (int i = 0; i < prekiuSkaicius; i++)
    {
        cout << "Kategorija: " << kategorijos[i] << endl;
        cout << "Pavadinimas: " << prekiuPavadinimai[i] << endl;
        cout << "Vieneto kaina: " << vienetoKainos[i] << " Eur." << endl;
        cout << "Uzsakytas kiekis: " << uzsakytiKiekiai[i] << endl;
        cout << "------------------------" << endl;
    }
}

string pasirinktiKategorija()
{
    string pasirinktaKategorija;

        do 
        {
            cout << "Pasirinkite kategorija: Dviraciai, Dalys, Aksesuarai\n";
            cout << "Irasykite savo pasirinkima: ";
            cin >> pasirinktaKategorija;
            cout << endl;

            if (pasirinktaKategorija != "Dviraciai" &&
                pasirinktaKategorija != "Dalys" && 
                pasirinktaKategorija != "Aksesuarai") 
            {
                cout << "Pasirinkote neteisinga kategorija!" << endl;
            }

            } while (pasirinktaKategorija != "Dviraciai" &&
                     pasirinktaKategorija != "Dalys" && 
                     pasirinktaKategorija != "Aksesuarai");

        return pasirinktaKategorija;
}

void perziuretiKategorijosPrekes (string kategorijos[], string prekiuPavadinimai[], double vienetoKainos[], int uzsakytiKiekiai[], int prekiuSkaicius, string pasirinktaKategorija)
{
    for (int i = 0; i < prekiuSkaicius; i++) {
        
        if (kategorijos[i] == pasirinktaKategorija)
        {
            cout << "Kategorija: " << kategorijos[i] << endl;
            cout << "Pavadinimas: " << prekiuPavadinimai[i] << endl;
            cout << "Vieneto kaina: " << vienetoKainos[i] << " Eur." << endl;
            cout << "Uzsakytas kiekis: " << uzsakytiKiekiai[i] << endl;
            cout << "------------------------" << endl;
        }
    }
}

double eilutesSuma(double vienetoKainos, int uzsakytiKiekiai)
{
    return vienetoKainos * uzsakytiKiekiai;
}

double apskaiciuotiNuolaida(double eilutesSuma, int uzsakytiKiekiai)
{
    if (uzsakytiKiekiai >= 10) 
    {
        return eilutesSuma * 0.10;
    }

    return 0;
}

void perziuretiUzsakymoSumas (ostream& isvestis, double vienetoKainos[], int uzsakytiKiekiai[], int prekiuSkaicius)
{
    double bendraSuma = 0;
    double bendraNuolaida = 0;

    for (int i = 0; i < prekiuSkaicius; i++) 
    {
        double suma = eilutesSuma(vienetoKainos[i], uzsakytiKiekiai[i]);

        double nuolaida = apskaiciuotiNuolaida(suma, uzsakytiKiekiai[i]);

        bendraSuma += suma;
        bendraNuolaida += nuolaida;
    }

    double galutineSuma = bendraSuma - bendraNuolaida;

    isvestis << fixed << setprecision(2);
    isvestis << "Bendra uzsakymo suma: " << bendraSuma << " Eur." << endl;
    isvestis << "Bendra nuolaida: " << bendraNuolaida << " Eur." << endl;
    isvestis << "Galutine uzsakymo suma po nuolaidos: " << galutineSuma << " Eur." << endl;
}

double kategorijosSuma (string kategorijos[], double vienetoKainos[], int uzsakytiKiekiai[], int prekiuSkaicius, string pasirinktaKategorija)
{
    double suma = 0;

    for (int i = 0; i < prekiuSkaicius; i++)
    {
        if (kategorijos[i] == pasirinktaKategorija)
        {
            double eilute = eilutesSuma(vienetoKainos[i], uzsakytiKiekiai[i]);
            double nuolaida = apskaiciuotiNuolaida(eilute, uzsakytiKiekiai[i]);

            suma += eilute - nuolaida;
        }
    } 
    
    return suma;

}

void perziuretiKategorijosSumas (ostream& isvestis, string kategorijos[], double vienetoKainos[], int uzsakytiKiekiai[], int prekiuSkaicius)
{
    double dviraciai = kategorijosSuma(kategorijos, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius, "Dviraciai");
    double dalys = kategorijosSuma(kategorijos, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius, "Dalys");
    double aksesuarai = kategorijosSuma(kategorijos, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius, "Aksesuarai");

    isvestis << fixed << setprecision(2);
    isvestis << "Dviraciu galutine suma: " << dviraciai << " Eur." << endl;
    isvestis << "Daliu galutine suma: " << dalys << " Eur." << endl;
    isvestis << "Aksesuaru galutine suma: " << aksesuarai << " Eur." << endl;
}

void parodytiUzsakymoAtaskaita (ostream& isvestis, string kategorijos[], string prekiuPavadinimai[], double vienetoKainos[], int uzsakytiKiekiai[], int prekiuSkaicius)
{
    isvestis << fixed << setprecision(2);

    for (int i = 0; i < prekiuSkaicius; i++)
    {
        isvestis << "PREKES NR. " << i + 1 << endl;
        isvestis << "Kategorija: " << kategorijos[i] << endl;
        isvestis << "Pavadinimas: " << prekiuPavadinimai[i] << endl;
        isvestis << "Vieneto kaina: " << vienetoKainos[i] << " Eur." << endl;
        isvestis << "Uzsakytas kiekis: " << uzsakytiKiekiai[i] << endl;
        double suma = eilutesSuma(vienetoKainos[i],uzsakytiKiekiai[i]);
        isvestis << "Eilutes suma: " << suma << " Eur." << endl;
        double nuolaida = apskaiciuotiNuolaida(suma,uzsakytiKiekiai[i]);
        isvestis << "Pritaikyta nuolaida: " << nuolaida << " Eur." << endl;
        isvestis << "Galutine suma: " << suma - nuolaida << " Eur." << endl;
        isvestis << "------------------------" << endl;
    }

        isvestis << "Bendra uzsakymo suvestine:" << endl;
        perziuretiUzsakymoSumas(isvestis, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius);
        isvestis << "------------------------" << endl;
        isvestis << "Sumos pagal kategorijas:" << endl;
        perziuretiKategorijosSumas(isvestis, kategorijos, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius);
}

void IssaugotiFaila ()
{
    ofstream ataskaita("ataskaita.txt");

    if (!ataskaita.is_open())
    {
        cout << "Klaida: Nepavyko sukurti ataskaitos failo!" << endl;
        return;
    }

    parodytiUzsakymoAtaskaita(ataskaita, kategorijos, prekiuPavadinimai, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius);

    ataskaita.close();

    if (!ataskaita)
    {
        cout << "Klaida: Nepavyko išsaugoti ataskaitos failo!" << endl;
        return;
    }

    cout << "Ataskaita issaugota faile ataskaita.txt!" << endl;
}

void rodytiMeniu()
{
    cout << "\n========== DVIRACIU PARDUOTUVE ==========\n"
         << "1. Visos uzsakymo prekes\n"
         << "2. Prekes pagal kategorija\n"
         << "3. Viso uzsakymo sumos\n"
         << "4. Sumos pagal kategorijas\n"
         << "5. Visa uzsakymo ataskaita\n"
         << "6. Issaugoti ataskaita i faila\n"
         << "7. Iseiti\n"
         << "=========================================\n";
}

int main () 
{   
    int pasirinkimas;

    if (!nuskaitytiDuomenis(kategorijos,prekiuPavadinimai,vienetoKainos,uzsakytiKiekiai,prekiuSkaicius))
    {
        cout << "Klaida: Nepavyko nuskaityti duomenu!" << endl;
        return 1;
    }

    do {
        rodytiMeniu();

        cout << "Pasirinkite veiksma (1-7): ";
        cin >> pasirinkimas;
        cout << endl;

        switch (pasirinkimas) {
            case 1:
            perziuretiPrekes(kategorijos, prekiuPavadinimai, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius);
            break;

            case 2:
            { 
            string pasirinktaKategorija = pasirinktiKategorija();
            perziuretiKategorijosPrekes(kategorijos, prekiuPavadinimai, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius, pasirinktaKategorija);
            break;
            }

            case 3:
            perziuretiUzsakymoSumas(cout, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius);
            break;

            case 4:
            perziuretiKategorijosSumas(cout, kategorijos,vienetoKainos,uzsakytiKiekiai,prekiuSkaicius);
            break;

            case 5:
            parodytiUzsakymoAtaskaita(cout, kategorijos, prekiuPavadinimai, vienetoKainos, uzsakytiKiekiai, prekiuSkaicius);
            break;

            case 6:
            IssaugotiFaila();
            break;

            case 7:
            cout << "Iseinate is programos. Viso gero.\n";
            cout << endl;
            break;

            default:
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.";
            cout << endl;
            break;
        }

    } while (pasirinkimas != 7);

    return 0;
}