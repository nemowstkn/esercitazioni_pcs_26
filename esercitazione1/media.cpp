#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char *argv[]) 
{
	 if (argc < 2) {
		cerr << "Errore: Mancata definizione del file \n";
		return 1;
	}
	
	ifstream file(argv[1]);
	
	if (file.is_open()) {
		
		for (int i = 1; i <= 3; i++) {
			
			string location;
			double temp1;
			double temp2;
			double temp3;
			double temp4;
			
			file >> location >> temp1 >> temp2 >> temp3 >> temp4;
			
			double media;
			
			media = (temp1 + temp2 + temp3 + temp4)/4;
			
			cout << location << ": " << media << "\n";
			
		}
	}
	else {
		
		cerr << "Errore: impossibile aprire: " << argv[1] << "\n";
		return 1;
	}
}


						
		