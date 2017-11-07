#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>


std::string trouverCle(std::string texte, int longueurCle)
{
  std::string fragmentTexte = "";
  std::string cleTrouvee = "";
  int tabOccurrence[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int position = 0;
  int plusFrequent =0;
  int rangLettre = 0;

  for(rangLettre =0; rangLettre < longueurCle; rangLettre++)
    {
      for(int i = rangLettre; i < texte.length(); i+= longueurCle) // FRAGMENTATION DU TEXTE TOUS LES NEUFS CARACTERES
	{
	  fragmentTexte += texte[i];
	}
      std::cout << "Debut fragment texte:" << fragmentTexte[0] << fragmentTexte[1] << std::endl;

      for (int j =0; j<fragmentTexte.length();j++) // TABLEAU DE REPARTITION DES CARACTERES
	{
	  if((int)fragmentTexte[j] >= 65 && (int)fragmentTexte[j] <= 90 || (int)fragmentTexte[j] >= 97 && (int)fragmentTexte[j] <= 122)
	    {
	      position = ((int)fragmentTexte[j]-97);
	      tabOccurrence[position]++;
	    }
	}

      for(int k=0; k<26; k++) // RECUPERATION DE LA LETTRE LA PLUS PRESENTE
	{
	  if(tabOccurrence[k] < plusFrequent)
	    plusFrequent = tabOccurrence[k];
	}

      cleTrouvee += plusFrequent+97-4+26;

      fragmentTexte = "";
     for(int k=0; k<26; k++) // RECUPERATION DE LA LETTRE LA PLUS PRESENTE
	{
	  tabOccurrence[k] = 0;
	}
	
      
    }
  
  std::cout << "Cle:" << cleTrouvee << std::endl;

  return cleTrouvee;
   
    
    
}


std::string fragmenterTexte(std::string texteComplet, int longueurCle)
{
  std::string texteResultat = "";
  int i =0;
  std::string texteSansEspace = "";
  
  while(i<texteComplet.length())
    {
     if((int)texteComplet[i] >= 65 && (int)texteComplet[i] <= 90 || texteComplet[i] >= 97 && texteComplet[i] <= 122)
       texteSansEspace += texteComplet[i];
     i++;
    }
  
  for(int i = 0; i<texteSansEspace.length(); i+=longueurCle)
    { 
      texteResultat += texteSansEspace[i];  
    }
   

  return texteResultat;
}

double calculIndice(std::string texte)
{
  
  double indice = 0 ; 
   std::cout << "Longueur du texte: " << texte.length() << std::endl;
  int tabOccurrence[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int position = 0;
  for (int i =0; i<texte.length();i++)
    {
      if((int)texte[i] >= 65 && (int)texte[i] <= 90 || (int)texte[i] >= 97 && (int)texte[i] <= 122)
	{
	  position = ((int)texte[i]-97);
	  tabOccurrence[position]++;
	}
    }
  for(int j = 0 ; j < 26; j++)
    std::cout << tabOccurrence[j] << " ";
  
  for(int j = 0 ; j < 26; j++)
    indice = indice + ((double(tabOccurrence[j])*(double(tabOccurrence[j]-1)))/(double(texte.length())*(double(texte.length()-1))));

  std::cout << "Indice:" << indice << std::endl;
  // std::cout << "Longueur texte:" << texte.length();
  return indice;
}

int trouverLongueurCle(std::string texte)
{
  int longueurCle = 2;
  int i = 0;
  double indiceCoincidence = 0;
  double indiceCoincidenceMax =0; // Plus grand indice de coincidence
  int longueurCleResultat = 0; // Longueur de la clé dont l'indice est le plus gros
  std::string fragmentTexte = "";
  std::string texteComplet = "";
  std::string texteDecoupe = "";
  std::ifstream fichier(texte.c_str(), std::ios::in);
  std::string texteSansEspace = "";
  if(fichier) 
    {       
      while(getline(fichier, fragmentTexte))  
	{
	  texteComplet+=fragmentTexte;
	  texteComplet+= '\n';

	  
	}
      // std::cout << "Texte complet:" << texteComplet << std::endl;
      
       do
       	{
	  std::cout << "----------------------------------------" << std::endl;
	  std::cout << "Longueur cle testee:" << longueurCle << std::endl;
	  texteDecoupe = fragmenterTexte(texteComplet, longueurCle);
	  // std::cout << "Texte fragmenté:" << texteDecoupe << std::endl;
	  indiceCoincidence = calculIndice(texteDecoupe);
	  if(indiceCoincidence > indiceCoincidenceMax)
	    {
	      indiceCoincidenceMax = indiceCoincidence;
	      longueurCleResultat = longueurCle;
	    }
	  longueurCle++;   
       	}
       while( longueurCle<11);

       std::cout << "Le plus gros indice de coincidence est : " << indiceCoincidenceMax << std::endl;
       std::cout << "La taille de clé associée est : " << longueurCleResultat << std::endl;
       
       while(i<texteComplet.length())
	 {
	   if((int)texteComplet[i] >= 65 && (int)texteComplet[i] <= 90 || texteComplet[i] >= 97 && texteComplet[i] <= 122)
	     texteSansEspace += texteComplet[i];
	   i++;
	 }
       trouverCle(texteSansEspace, longueurCleResultat);
       
      fichier.close(); 
    }


  
 
   
  return longueurCle;
}
void chiffrement(std::string texte, std::string cle)
{

  int indiceCle = 0;
  int charCode;
  std::string maNewString;
  
  std::ofstream fichier("test.txt", std::ios::app); // Lecture du fichier en écriture



  for(int i = 0 ; i < texte.length() ; i++)
    {
      if((int)texte[i] >= 97 && (int)texte[i] <= 122) // Lettre minuscule
	{
	 
	  charCode = ((int(texte[i]) + int(cle[indiceCle])-'a'-'a')%26)+97;
	  maNewString += (char)charCode;

	  if(indiceCle == cle.length()-1)
	    indiceCle = 0;
	  else indiceCle++;
	}
      else if((int)texte[i] >= 65 && (int)texte[i] <= 90) // Lettre majuscule
	{ 
	  texte[i] = texte[i] + 32;

	   charCode = ((int(texte[i]) + int(cle[indiceCle])-'a'-'a')%26)+97;
	  maNewString += (char)charCode;

	  if(indiceCle == cle.length()-1) // Répétition de la cléà
	    indiceCle = 0;
	  else indiceCle++;

	}
      else  maNewString += texte[i]; // Si c'est un caractère spécial on l'ignore

    }

  
  if(fichier)
    {
      fichier << maNewString << std::endl; // Entrée dans le fichier
    
    }
  
  else
    std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
}  


void dechiffrement(std::string texte, std::string cle) // Dechiffrement sur un principe similaire au chiffrement
{

  int indiceCle = 0;
  int charCode;
  std::string maNewString;
  std::ofstream fichier("test2.txt", std::ios::app);
  
  for(int i = 0 ; i < texte.length() ; i++)
    {
      if((int)texte[i] >= 65 && (int)texte[i] <= 90 || (int)texte[i] >= 97 && (int)texte[i] <= 122)
	{
	  charCode = (((int(texte[i])-'a') - (int(cle[indiceCle])-'a')+26)%26)+'a';

	  maNewString += (char)charCode;
	  
	  if(indiceCle == cle.length()-1)
	    indiceCle = 0;
	  else indiceCle++;
	}
      else maNewString +=  texte[i]; 

    }

  if(fichier)           
      fichier << maNewString << std::endl;
  else
    std::cout << "Impossible d'ouvrir le fichier !" << std::endl;  
}


int main(int argc, char ** argv)
{
  
  std::string maString; 
      
  if (argc < 4)
    {
      if(strcmp(argv[1], "-x") ==0)
	{
	  trouverLongueurCle(argv[2]);
	}
      else
	{
	  std::cout << "Pas assez d'arguments, utilisez le format ./TP1.out <operation> <texte> <cle>" << std::endl;
	  std::cout << "Ou bien ./TP1.out -x <texte> pour le decryptage" << std::endl;
	}
    }
  else
    {     
      if(strcmp(argv[1], "-c") == 0)
	{
	  std::cout << " Chiffrement" << std::endl;
	  std::ifstream fichier(argv[2], std::ios::in); 
	  if(fichier)  
	    {       
	      while(getline(fichier, maString))  // Chiffrement du texte ligne par ligne. 
		{
		  chiffrement(maString, argv[3]);
		}
	      fichier.close(); 
	    }
	  else 
	    std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
	}

	  
      else if (strcmp(argv[1], "-d") == 0)
	{
	  std::cout << " Déchiffrement" << std::endl;
	  std::ifstream fichier(argv[2], std::ios::in); 
	      
	  if(fichier) 
	    {       
	      while(getline(fichier, maString))  
		{
		  dechiffrement(maString, argv[3]); 
		}
	      fichier.close(); 
	    }
	  
	  else  
	    std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
	}

  
      else std::cout << "Argument d'opération invalide" <<  std::endl;
    }

}
