#include <iostream>
#include <string>
#include <vector>
#include<list>
#include<map>
#include <chrono>
#include <thread>
#include <climits>
#include <fstream>
#include <queue>
#include <algorithm>
#include<sstream>
#include"Patient.h"
using namespace std;

//variables global
int nbr_patients = 0;
string fullName;

// linked list des patients
struct node
{
	Patient listPatients;
	node* next;
};
//pointure head initialize a null (la linked liste est vide)
node* head = NULL;

// prototype de les fonctions
void afficherMenu();
void insererPatient(Patient patient);
void supprimerPatient(int position);
void afficherPatients();
void afficherBackup();
string recherchNom(string id);
int verifierEntier();
int verifierIdExiste(string id);

int main()
{
	//declarer les variables
	string username, passwrod;
	bool loginCheck = false;
	bool finProgram = false;
	int patientIndex;
	int menuChoix = -1;
	string id, nom, prenom, telephone;
	queue<string> waitingList;
	bool fullNameExiste = false;
	string fullName;
	string temp;

	//creer un map pour stocker les informations de connexion 
	map<string, string> userRecord;
	//Ajouter 2 utilsateurs
	userRecord["mohamed"] = "1234";
	userRecord["x"] = "x";

	//verification de username et password
	do
	{
		cout << "Entrez nom d'utilisateur: " << flush;
		getline(cin, username);
		cout << "Entrez le mot de passe: " << flush;
		getline(cin, passwrod);

		//si la connextion a reussi
		if (userRecord[username] == passwrod)
		{
			//clear screen
			system("CLS");
			cout << "************************************************ " << endl;
			cout << "		  Bienvenu " << username << endl;
			cout << "************************************************ " << endl;
			std::chrono::seconds dura(1); // pause 1 seconds
			std::this_thread::sleep_for(dura);
			system("CLS");
			loginCheck = true;
		}//

		//si la connextion a echouee
		if (!loginCheck)
			cout << "Nom d'utilisateur/ mot de passe incorrect" << endl;
	} while (!loginCheck);

	do
	{
		//affichage de menu principal
		afficherMenu();
		//verifier que le choix de menu est (entier)
		menuChoix = verifierEntier();
		switch (menuChoix)
		{
				
		case 1: //Inserer un patient
			do
			{
				cout << "Le id du patient: " << flush;
				cin >> id;
				//on appelle la fonction(verifierIdExiste) qui return l'index de ID dans la liste
				//return -1 si l'id n'existe pas
				patientIndex = verifierIdExiste(id);

				if (patientIndex == -1) {
					cout << "Le nom du patient: " << flush;
					cin >> nom;
					cout << "Le prenom du patient: " << flush;
					cin >> prenom;
					cout << "Le telephone du patient: " << flush;
					cin >> telephone;

					//initailization de nouveau patient
					Patient newPatients(id, nom, prenom, telephone);

					//on appelle la fonction (insererPatient) pour ajouter le patient dans la liste
					insererPatient(newPatients);

					//aujmenter le nombre de patients
					nbr_patients++;

					cout << "\n\tL'insertion du patient a ete effectuee avec succes\n" << endl;

					// mise a jour de fichier patient
					//on essaye de lire les donnees dans le fichier si il existe
					ifstream backupfile("patient.txt");

					//si le fichier est deja ouvert
					if (backupfile.is_open())
					{
						ofstream backupfile("patient.txt", ios::out | ios::app);
					//ios::out >> pour utiliser le mode ecriture 
					//ios::app >> pour ajouter les donnees a la fin du fichier

						backupfile << id << "\t\t" << nom << "\t\t" << prenom << "\t\t" << telephone << "\t\t" << endl;
					}//
					else {
						//si le fichier n'existe pas on ouvre un nouveau fichier
						ofstream backupfile("patient.txt", ios::out);
						backupfile << "###############################################################" << endl;
						backupfile << "			BACKUP" << endl;
						backupfile << "###############################################################" << endl;
						backupfile << "Id\t\t" << "Nom\t\t" << "Prenom\t\t" << "telephone\t\t" << endl;
						backupfile << "---\t\t" << "----\t\t" << "------\t\t" << "---------\t\t" << endl;
						backupfile << id << "\t\t" << nom << "\t\t" << prenom << "\t\t" << telephone << "\t\t" << endl;
					}//
					//fermer le fichier
					backupfile.close();
				}//

				 // si le ID existe deja
				else if (patientIndex != -1)
				{
					//CLEAR BUFFER
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Id du patient existe deja! " << endl;
				}//
			} while (patientIndex != -1);

			break;

		case 2: //  Supprimer un patient
		{
			if (nbr_patients != 0) {
				do
				{
					cout << "Le id du patient a supprimer: " << flush;
					cin >> id;
					//on appelle la fonction(verifierIdExiste) qui return l'index de ID dans la liste
				//return -1 si l'id n'existe pas
					patientIndex = verifierIdExiste(id);

					//on appelle la fonction qui return fullName pour le supprimer de la liste d'attente
					fullName = recherchNom(id);

					//si le patient existe dans la liste des patients
					if (patientIndex != -1) {

						//on appelle la fonction(supprimerPatient) pour supprimer le patient
						supprimerPatient(patientIndex);
						nbr_patients--;
						system("CLS");
						cout << "\n\tLa suppression du patient a ete effectuee avec succes\n" << endl;

						//verifier si le patient existe dans la liste d'attente
						for (int i = 0; i < waitingList.size(); i++)
						{
							//on utilse un queue temporaire pour chercher fullName et 
							//conserver la queue originle telle quelle
							temp.clear();
							temp = waitingList.front();
							if (temp == fullName) {
								waitingList.pop();
								cout << "\n\tLe patient a ete supprime de la liste d'attente!\n " << endl;
								break;
							}//
							waitingList.pop();
							waitingList.push(temp);
						}//
					}//
					// si le patient n'existe pas dans la liste des patients
					else if (patientIndex == -1)
					{
						//CLEAR BUFFER
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "Id du patient n'existe pas! " << endl;
					}//
				} while (patientIndex == -1);
			}//

			//si le nombre de patients est 0, donc la liste des patients est vide
			else {
				system("cls");
				cout << "\n\tLa liste des patients est vide!\n" << endl;
			}//
			break;
		}//
		case 3: //Afficher la liste des patients
			//on appelle la fonction qui affiche les donnees des patients
			afficherPatients();
			break;

		case 4://Afficher le contenu du fichier 'Backup' pour les donnees des patients
			//on appelle la fonction qui affiche les contenu du fichier Backup-patients
			afficherBackup();
			break;

		case 5://Inscription d'un patient sur la liste d'attente
			cout << "Le id du patient: " << flush;
			cin >> id;

			//on appelle la fonction(verifierIdExiste) qui return l'index de ID dans la liste
			//return -1 si l'id n'existe pas
			patientIndex = verifierIdExiste(id);

			//on appelle la fonction qui return fullName pour l'ajouter dans la liste d'attente
			fullName = recherchNom(id);

			// si le patient d'existe pas dans la liste de patients
			if (patientIndex == -1) {
				system("CLS");
				cout << "\n\tLe patient n'existe pas dans nos dossiers, veuillez l'inserer svp\n" << endl;
			}//

			// si le patient existe dans la liste de patients
			else {
				//reinitializer le boleen fullNameExiste
				fullNameExiste = false;

				//on cherhce le fullName dans la liste d'attente
				for (int i = 0; i < waitingList.size(); i++)
				{
					//on utilse un queue temporaire pour chercher fullName et 
					//conserver la queue originle telle quelle
					temp = waitingList.front();
					if (temp == fullName) {
						//si le fullName existe dans la liste d'attente
						fullNameExiste = true;
						system("CLS");
						cout << "\n\tId du patient existe deja sur la liste d'attente!\n " << endl;
						break;
					}//
					waitingList.pop();
					waitingList.push(temp);
				}//

				 //si le fullName n'existe pas dans la liste d'attente
				if (!fullNameExiste) {
					system("CLS");
					waitingList.push(fullName);
					cout << "\n\t" << fullName << " a ete inscrit avec succes sur la liste d'attente\n" << endl;
				}//
			}//

			break;
		case 6: //Afficher la liste d'attente
			//verifier si la queue est vide
			if (waitingList.empty()) {
				system("CLS");
				cout << "\n\tLa liste d'attente est vide\n" << endl;
			}//
			// si la queue n'est pas vide
			else
			{
				system("CLS");
				string temp;
				cout << "\n\tLa liste d'attente: \n" << endl;
				for (int i = 0; i < waitingList.size(); i++)
				{
					//on utilse un queue temporaire pour sauvegarder 
					//les donnees existant dans le que temporaire et
					//conserver la queue originle telle quelle

					temp = waitingList.front();
					cout << i + 1 << "- " << temp << endl;
					waitingList.pop();
					waitingList.push(temp);
				}
			}//
			break;

		case 7: //Quitter
			finProgram = true;
			system("CLS");
			cout << "*********************************************** " << endl;
			cout << "		Au revoir " << username << endl;
			cout << "*********************************************** " << endl;
			std::chrono::seconds dura(1); // pause 1 seconds
			std::this_thread::sleep_for(dura);
			break;
		
		default:
			system("cls");
			cout << "\n\tVotre choix n'est pas valide\n" << endl;
			break;
		}

	} while (!finProgram);

}//main

//////////////////////////////////////////////////////////////////////////////

// definition des fonctions

void afficherMenu() {
	system("color 02");
	cout << "*********************** GESTION DU CLINIQUE DE ROSEMONT ***********************" << endl;
	cout << "1- Inserer un patient" << endl;
	cout << "2- Supprimer un patient" << endl;
	cout << "3- Afficher la liste des patients" << endl;
	cout << "4- Afficher le contenu du fichier 'Backup' pour les donnees des patients" << endl;
	cout << "5- Inscription d'un patient sur la liste d'attente" << endl;
	cout << "6- Afficher la liste d'attente" << endl;
	cout << "7- Quitter\n" << endl;
	cout << "Votre choix: " << flush;
};

//////////////////////////////////////////////////////////////////////////////

int verifierEntier() {
	int valeur = 0;
	bool valid = false;
	while (!valid) {
		//verifier si la valeur est un entier
		if (!(cin >> valeur))
		{
			//CLEAR BUFFER
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Erreur! Ce n'est pas un nombre \n" << "Entrer un nombre valide svp: ";
		}
		else
			valid = true;
	}
	return valeur;
};//

//////////////////////////////////////////////////////////////////////////////

void insererPatient(Patient patient)
{
	system("CLS");
	//creer 2 nodes (nouveau node et dernier node)
	node* new_node, *last;
	new_node = new node;

	// le nouveau node (donnee) va recevoir le nouveau patient
	new_node->listPatients = patient;

	// si le head pointe au NULL (la liste est vide)
	if (head == NULL) {
		head = new_node;
		new_node->next = NULL;
	}//

	// si le head pointe au autre node (la liste n'est pas vide vide)
	//on cherche le dernier node
	else {
		last = head; // dernier node point au premier node
		//run list
		while (last->next != NULL) {
			// deplacer last jusqu a dernier node
			last = last->next;
		}//

		// le nouveau node va etre la dernier node dans la liste
		last->next = new_node;
		new_node->next = NULL;
	}//

};//

//////////////////////////////////////////////////////////////////////////////

int verifierIdExiste(string id) {
	int index = 0;

	//creer un nouveau node temporaire qui point au head
	node *temp = head;
	
	// run liste
	while (temp != NULL) {
		// si le ID dans la partie(data) de le node=id, on return l'index de node dans la liste
		if (temp->listPatients.getId() == id) { return index; }
		temp = temp->next; // deplacer au next node
		index++;
	}//
	//si l'element n'est pas trouve
	return -1;
};//

//////////////////////////////////////////////////////////////////////////////

void afficherPatients() {
	system("CLS");
	// declarer un nouveau node temporaire
	node* temp;

	// si le head pointe au NULL (la liste est vide)
	if (head == NULL) {
		system("cls");
		cout << "\n\tLa liste est vide!\n" << endl;
	}//

	// si le head pointe a autre node (la liste n'est pas vide vide)
	else {
		system("CLS");
		cout << "************************************************ " << endl;
		cout << "		La liste des patients " << endl;
		cout << "************************************************ " << endl;

		temp = head;
		while (temp != NULL) {
			//Afficher les donnees de chaque node
			temp->listPatients.displayPatient();
			temp = temp->next; // deplacer au next node
		}//
	}//
};//

//////////////////////////////////////////////////////////////////////////////

void supprimerPatient(int position) {
	//creer un nouveau node temporaire point au head
	node *temp = head;
	int count = 0;

	//si le head est l'element a supprimer
	if (position == 0)
	{
		head = temp->next; //pointer le head a l'element suivant
		free(temp);      //free old head
		return;
	}//

	//si le head n'est pas l'element a supprimer
	// chercher le node precedent du node a supprimer
	for (int i = 0; temp != NULL && i < position - 1; i++)
		temp = temp->next;

	/* If position is more than number of ndoes
	if (temp == NULL || temp->next == NULL)
		return;*/

	// Node temp->next is the node to be deleted
	// Store pointer to the next of node to be deleted 
	//creer un nouveau node pointe a la node qu'on veut supprimer
	//on deplace 2 fois apres la node a la position avant la node qu'on veut supprimer
	node *next = temp->next->next;

	// supprimer le node de la linked list 
	free(temp->next);  // Free memory 
	// Unlink the deleted node from list
	temp->next = next; //previous point to new

};//

//////////////////////////////////////////////////////////////////////////////

void afficherBackup() {
	system("CLS");
	ifstream backupfile("patient.txt");

	if (backupfile.is_open())
	{
		string line;
		while (backupfile.good()) {
			getline(backupfile, line);
			cout << line << endl;
		}//
		backupfile.close();
	}//
	else {
		cout << "Le fichier n'existe pas" << endl;
	}//

}//;

//////////////////////////////////////////////////////////////////////////////

string recherchNom(string id) {
	//creer un node temporaire pointe a head
	node *temp = head;
	//run list
	while (temp != NULL) {
	// si le ID dans la partie(data) de le node=id, on get le nom et prenom du patient
		if (temp->listPatients.getId() == id) {
			fullName = (temp->listPatients.getNom()) + ", " + (temp->listPatients.getPrenom());
		}
		temp = temp->next; // deplacer au next node
	}//
	return fullName;
}//;
