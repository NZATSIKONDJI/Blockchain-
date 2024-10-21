#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>

class Bloc
{
public:
    int numero;
    std::string hachagePrecedent;
    long horodatage;
    std::string donnees;
    std::string hachageActuel;

    Bloc(int numeroBloc, std::string hachPrecedent, long temps, std::string data, std::string hachage)
        : numero(numeroBloc), hachagePrecedent(hachPrecedent), horodatage(temps), donnees(data), hachageActuel(hachage) {}
};

std::string genererHachage(int numero, std::string hachagePrecedent, long horodatage, std::string donnees)
{
    std::ostringstream flux;
    flux << numero << hachagePrecedent << horodatage << donnees;
    return std::to_string(std::hash<std::string>{}(flux.str()));
}

Bloc creerBlocGenesis()
{
    long horodatageInitial = std::time(nullptr);
    std::string hachageGenesis = genererHachage(0, "0", horodatageInitial, "BlocGenesis");
    return Bloc(0, "0", horodatageInitial, "BlocGenesis", hachageGenesis);
}

Bloc creerNouveauBloc(const Bloc& blocPrecedent, const std::string& donnees)
{
    int nouveauNumero = blocPrecedent.numero + 1;
    long nouveauHorodatage = std::time(nullptr);
    std::string hachagePrecedent = blocPrecedent.hachageActuel;
    std::string hachageNouveau = genererHachage(nouveauNumero, hachagePrecedent, nouveauHorodatage, donnees);
    return Bloc(nouveauNumero, hachagePrecedent, nouveauHorodatage, donnees, hachageNouveau);
}

int main()
{
    std::vector<Bloc> Blockchain;

    Bloc blocGenesis = creerBlocGenesis();
    Blockchain.push_back(blocGenesis);

    std::cout << "Le bloc #" << blocGenesis.numero << " (Genesis) est la base de la blockchain" << std::endl;
    std::cout << "Hachage : " << blocGenesis.hachageActuel << std::endl;
    std::cout << "Hachage precedent : " << blocGenesis.hachagePrecedent << std::endl << std::endl;

    Bloc dernierBloc = Blockchain.back();
    const int totalBlocs = 5;

    for (int i = 0; i < totalBlocs; ++i)
    {
        std::string contenuBloc = "Bloc " + std::to_string(i + 1) + " Donnees";
        Bloc nouveauBloc = creerNouveauBloc(dernierBloc, contenuBloc);
        Blockchain.push_back(nouveauBloc);

        std::cout << "Le bloc #" << nouveauBloc.numero << " a ete ajoute a la blockchain" << std::endl;
        std::cout << "Hachage : " << nouveauBloc.hachageActuel << std::endl;
        std::cout << "Hachage precedent : " << dernierBloc.hachageActuel << std::endl << std::endl;

        dernierBloc = nouveauBloc;
    }

    return 0;
}
