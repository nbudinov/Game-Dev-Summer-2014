#include <iostream>

using namespace std;

int searched[4] = {99, 99, 99, 99};

	void generate() {
		int i = 0;
		bool NO = false;
	
		while(i < 4) {
			int randInd = rand() % 10;
			for (int j = 0; j < 4; j++) {
				if(randInd == searched[j]) {
					NO = true;
				}
			}

			if( NO == false) {
				searched[i] = randInd;
				i++;
			}	
		}
	}

int main() {
	int firstInput = 0,
		secInput = 0,
		cows = 0,
		bulls = 0,
		none = 0;
	bool guessed = false;
	int arrInp[128];
	int i = 0;
	bool NO = false;
	
	generate();
	
	for(int i = 0; i < 4; i++){
		cout << searched[i] ;
	}
	
	bool digits = true;
	while(guessed != true) {

		cout << " Tell me a 4 digit number" << endl;
		cin >> secInput ;
		if(secInput > 1000 && secInput < 9998) {
			arrInp[0] = secInput / 1000;
			arrInp[1] = (secInput / 100) % 10;
			arrInp[2] = ((secInput / 10) % 100 ) % 10;
			arrInp[3] = secInput % 10;
		
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					if(arrInp[i] == arrInp[j] && i != j) {
						NO = true;
					}
				}
			}

			if(!NO) {
			for(int i = 0; i < 4; i++) {
				for(int g = 0; g < 4; g++) {
					if(searched[i] == arrInp[g]) {
						if( i == g ) {
							bulls += 1;
						}
						else {
							cows += 1;
						}
					}
					else {
						none += 1;
					}
				}
			}
			cout << cows << " Cows " << endl << bulls << " Bulls " << endl; 
			}
			else{
				cout << "No povtoreniq " << endl;
				NO = false;
			}
		}
		else 
			cout << "Your number should be 4 digits" << endl;
		if(bulls == 4) {
			guessed = true;
			cout << "You got the Number !!!" << endl;
		}
		cows = 0;
		bulls = 0;
	}
	
	system("pause");
	return 0;
}