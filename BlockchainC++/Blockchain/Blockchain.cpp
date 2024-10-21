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

void afficherBlockchain(const std::vector<Bloc>& blockchain)
{
    std::cout << "\n===== Blockchain actuelle =====" << std::endl;
    for (const auto& bloc : blockchain)
    {
        std::cout << "Bloc #" << bloc.numero << std::endl;
        std::cout << "Hachage : " << bloc.hachageActuel << std::endl;
        std::cout << "Hachage precedent : " << bloc.hachagePrecedent << std::endl;
        std::cout << "Donnees : " << bloc.donnees << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}

void supprimerDernierBloc(std::vector<Bloc>& blockchain)
{
    if (blockchain.size() > 1)
    {
        blockchain.pop_back();
        std::cout << "Le dernier bloc a ete supprime." << std::endl;
    }
    else
    {
        std::cout << "non pelo on se supprime pas ca." << std::endl;
    }
}

void ajouterBloc(std::vector<Bloc>& blockchain)
{
    Bloc dernierBloc = blockchain.back();
    std::string contenuBloc;
    std::cout << "Entrez les donnees pour le nouveau bloc : ";
    std::cin.ignore();  
    std::getline(std::cin, contenuBloc);

    Bloc nouveauBloc = creerNouveauBloc(dernierBloc, contenuBloc);
    blockchain.push_back(nouveauBloc);

    std::cout << "Le bloc #" << nouveauBloc.numero << " a ete ajoute a la blockchain." << std::endl;
    std::cout << "Hachage : " << nouveauBloc.hachageActuel << std::endl;
    std::cout << "Hachage precedent : " << nouveauBloc.hachagePrecedent << std::endl;
}

void afficherMenu()
{
    std::cout << "\n===== Menu Blockchain =====" << std::endl;
    std::cout << "1. Ajouter un nouveau bloc" << std::endl;
    std::cout << "2. Supprimer le dernier bloc" << std::endl;
    std::cout << "3. Quitter" << std::endl;
    std::cout << "Fait toi plais pelo : ";
}

int main()
{
    std::vector<Bloc> Blockchain;

    Bloc blocGenesis = creerBlocGenesis();
    Blockchain.push_back(blocGenesis);
    std::string donneesPremierBloc = "Premier Bloc Donnees";
    Bloc premierBloc = creerNouveauBloc(blocGenesis, donneesPremierBloc);
    Blockchain.push_back(premierBloc);
    afficherBlockchain(Blockchain);

    int choix;
    bool continuer = true;
    while (continuer)
    {
        afficherMenu();
        std::cin >> choix;

        switch (choix)
        {
        case 1:
            ajouterBloc(Blockchain);
            afficherBlockchain(Blockchain); 
            break;
        case 2:
            supprimerDernierBloc(Blockchain);
            afficherBlockchain(Blockchain);  
            break;
        case 3:
            continuer = false;
            std::cout << "Au revoir!" << std::endl;
            break;
        default:
            std::cout << "Option invalide. Veuillez reessayer." << std::endl;
        }
    }

    return 0;
}
