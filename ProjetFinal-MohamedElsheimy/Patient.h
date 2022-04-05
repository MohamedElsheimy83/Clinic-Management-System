#include<iostream>
#include <string>

using namespace std;

class Patient {
	//declaration
private:
	//attributes
	string id;
	string nom;
	string prenom;
	string telephone;;

public:
	//setter
	void setId(string p_id);
	void setNom(string p_nom);
	void setPrenom(string p_prenom);
	void setTelephone(string p_Telephone);

	//getter
	string getId();
	string getNom();
	string getPrenom();
	string getTelephone();

	//constructor

	//default constructor
	Patient();
	Patient(string p_id, string p_nom, string p_prenom, string p_Telephone);

	// fonctions
	void displayPatient();
};//

