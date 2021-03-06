#include <iostream>
#include <string>
#include "Noeud.h"
#include "Terme.h"
#include <fstream>

#include<bits/stdc++.h>
using namespace std;


Terme *ParcoursInfixe(Noeud* Courant)
{
    Terme *T;
   Terme* gauche;
    Terme* droit;
    if (Courant->getType() == 0) {
        T = new Terme();
        T->setValue(Courant->getValue());
        T->setType(0);   // Nombre
     return T;
    }
    else if (Courant->getType() == 1) {
        gauche = ParcoursInfixe(Courant->getFilsGauche());
        droit = ParcoursInfixe(Courant->getFilsDroit());
        if (((gauche->getType()==2)||(droit->getType()==2))&&(Courant->getValue().compare("+") == 0)) {
            T = new Terme();
            T->setValue(gauche->getValue()+"+"+droit->getValue());
            T->setType(2);
            return T;
        } else if (((gauche->getType()==2)||(droit->getType()==2))&&(Courant->getValue().compare("-") == 0)) {
            T = new Terme();
            T->setValue(gauche->getValue()+"-"+droit->getValue());
            T->setType(2);
            return T;
        } else if (((gauche->getType()==2)||(droit->getType()==2))&&(Courant->getValue().compare("*") == 0)) {
            T = new Terme();
            T->setValue(gauche->getValue()+"*"+droit->getValue());
            T->setType(2);
            return T;

        } else if (((gauche->getType()==2)||(droit->getType()==2))&&(Courant->getValue().compare("/") == 0)) {

            T = new Terme();
            T->setValue(gauche->getValue()+"/"+droit->getValue());
            T->setType(1);
            return T;
        }
        else if (((gauche->getType()!=2)&&(droit->getType()!=2))&&(Courant->getValue().compare("/") == 0)) {

            T = new Terme();
            T->setValue(to_string(stof(gauche->getValue())/stof(droit->getValue())));
            T->setType(1);
            return T;
        }
        else if (((gauche->getType()!=2)&&(droit->getType()!=2))&&(Courant->getValue().compare("+") == 0)) {

            T = new Terme();
            T->setValue(to_string(stof(gauche->getValue())+stof(droit->getValue())));
            T->setType(1);
            return T;
        }
        else if (((gauche->getType()!=2)&&(droit->getType()!=2))&&(Courant->getValue().compare("-") == 0)) {

            T = new Terme();
            T->setValue(to_string(stof(gauche->getValue())-stof(droit->getValue())));
            T->setType(1);
            return T;
        }
        else if (((gauche->getType()!=2)&&(droit->getType()!=2))&&(Courant->getValue().compare("*") == 0)) {

            T = new Terme();
            T->setValue(to_string(stof(gauche->getValue())*stof(droit->getValue())));
            T->setType(1);
            return T;
        }
    }else if (Courant->getType() == 2) {
        T = new Terme();
        T->setValue(Courant->getValue());
        T->setType(2);
        return (T);
    }
}




Noeud * createTree () {
    int i;
    stack<Noeud *> st,dump;
    Noeud *Pere, *FilsGauche, *FilsDroit;
    float result;
    string Gauche;
    string Droite;
    float opGauche;
    float opDroite;
    string expression;
    ofstream myfile ("../logArbre.txt");
    int previous = -88;

    while(expression.compare("=")!=0){

        cin >> expression;
        if (myfile.is_open())
        {
            if (expression!="=") {
                myfile << expression << "\n";
            }



        }
        else cout << "Unable to open file";
        if (((expression[0] == '*') || (expression[0] == '+') || (expression[0] == '-') || (expression[0] == '/')) && (expression[1]=='\0')) {
            cout << "c'est un operateur : " << expression[0];
            cout << endl;



            if(previous == 0){

                Pere = new Noeud();
                Pere->setValue(expression);
                Pere->setType(1);


                if(!st.empty()){

                    FilsDroit = st.top(); // Store top
                    st.pop();


                    FilsGauche = st.top();
                    st.pop();

                }
                Pere->setFilsDroit(FilsDroit);
                Pere->setFilsGauche(FilsGauche);



                // Add this subexpression to stack
                st.push(Pere);
                previous = 0;
            }
            else{
                Pere = new Noeud();
                Pere->setValue(expression);
                Pere->setType(1);


                // Pop two top nodes
                if(!st.empty()){

                    FilsDroit = st.top(); // Store top
                    st.pop();


                    FilsGauche = st.top();
                    st.pop();

                }
                else{
                    FilsDroit = NULL;
                    FilsGauche = NULL;
                }
                if ((FilsDroit!=NULL) && (FilsGauche!=NULL)){
                    cout << "Pere: " << Pere->getValue() << endl;
                    Droite=FilsDroit->getValue();
                    Gauche=FilsGauche->getValue();
                    cout << "Gauche: " << Gauche << " Droite: " << Droite << endl;


                }
                //  make them children
                Pere->setFilsDroit(FilsDroit);
                Pere->setFilsGauche(FilsGauche);


                // Add this subexpression to stack
                st.push(Pere);
                previous = 0;
            }



        } else if (isalpha(expression[0]) && (expression[1]=='\0')) {
            cout << "c'est une lettre : " << expression[0];
            cout << endl;

            // Ajout dans l'arbre
            Pere = new Noeud();
            Pere->setValue(expression);
            Pere->setType(2);
            st.push(Pere);

        }


        else if ((isdigit(expression[0])) && (isalpha(expression[1])== 0)) {

            i = 0;
            previous = 1;
            while (expression[i] != '\0') {
                if (isdigit(expression[i])) {
                    cout << "c'est un chiffre : " << expression;
                    cout << endl;
                }


                i++;

            }
            // Ajout dans l'arbre
            Pere = new Noeud();
            Pere->setValue(expression);
            Pere->setType(0);
            st.push(Pere);

        }

        else if (expression[0]=='-' && isdigit(expression[1])) {
            i = 0;
            previous = 1;
            while (expression[i] != '\0') {
                if (expression[0] == '-' && isdigit(expression[i])) {
                    cout << "c'est un chiffre : " << expression;
                    cout << endl;
                }

                i++;

            }

            // Ajout dans l'arbre
            Pere = new Noeud();
            Pere->setValue(expression);
            Pere->setType(0);
            st.push(Pere);




        } else{
            // Ajout dans l'arbre
            Pere = new Noeud();
            Pere->setValue(expression);
            Pere->setType(2);
            st.push(Pere);
            while (expression[i] != '\0') {
                if(isalpha(expression[i])){

                    char var = expression[i];
                    float nb = stof(expression.erase(i,1));

                    cout << "Le multiplicateur est " << nb << " pour la variable " << var << endl;
                    i++;


                }

            }
        }






    }
    myfile.close();
    // boucle for pour afficcher ce que contient le stack
    for(dump = st;!dump.empty(); dump.pop()){

        if(dump.top()->getType() == 0){
            cout << "ce stack est un nombre : ";
            cout << dump.top()->getValue();
            cout << endl;
        }
        else{
            cout << "ce stack est un opérateur : ";
            cout << dump.top()->getValue();
            cout << endl;
        }
    }
    Pere=st.top();
    st.pop();
    return Pere;
}


void readFile (string file) {
    string expressionLU;
    string STRING;
    ifstream infile;
    infile.open (file);
    while(!infile.eof())
    {
        getline(infile,STRING);

        expressionLU.append(STRING+" ");
    }
    infile.close();
    cout << "L'expression lu depuis le fichier est: " << expressionLU << endl;
}


int main() {
    float result;
    Terme *T;
    cout << "Entrez votre expression en écriture polonaise inversé" << endl;

    string expression;
    expression = "5+4*2*-";
    Noeud* n = createTree();
    T = ParcoursInfixe(n);
    cout << T->getValue();
    cout << endl;
    readFile("../logArbre.txt");

    return 0;
}