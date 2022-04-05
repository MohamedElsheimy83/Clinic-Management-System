#include <iostream>
#include <string>
#include"Patient.h"

using namespace std;

//definition & functions

//setter
void Patient::setId(string p_id) { id = p_id; }
void Patient::setNom(string p_nom) { nom = p_nom; }
void Patient::setPrenom(string p_prenom) { prenom = p_prenom; }
void Patient::setTelephone(string p_Telephone) { telephone = p_Telephone; }

//getter
string Patient::getId() { return id; }
string Patient::getNom() { return nom; }
string Patient::getPrenom() { return prenom; }
string Patient::getTelephone() { return telephone; }

//constructor
Patient::Patient() {};

Patient::Patient(string p_id, string p_nom, string p_prenom, string p_Telephone) {
	id = p_id;
	nom = p_nom;
	prenom = p_prenom;
	telephone = p_Telephone;
}

//methode pour afficher les donnes des patients
void Patient::displayPatient() {
	cout << "Id: " << id<<endl;
	cout << "Nom:" << nom<<endl;
	cout << "Prenom: " << prenom << endl;
	cout << "Telephone: " << telephone << endl;
	cout << "		*********" << endl;
}
