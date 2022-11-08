#include <iostream>
#include <fstream>
using namespace std;

//super class
class person{
	protected :
		string name;
		string gender;
		int age;
		int passNo;
	public :
		void setPersonInfo(int, string, string, int);
		int getPassNo();
		int getAge();
		string getName();
		person();
		~person();
};

//function to set personal information values
void person::setPersonInfo(int pn, string n, string g, int a){
	passNo = pn;
	name = n;
	gender = g;
	age = a;
}
//constructor
person::person(){
	name = "";
	gender = "";
	age = 0;
	passNo = 0;
}
//destructor
person::~person(){
	name = "";
	gender = "";
	age = 0;
	passNo = 0;
}
//function to return passport number value
int person::getPassNo(){
	return passNo;
}
//function to return age value
int person::getAge(){
	return age;
}
//function to return name value
string person::getName(){
	return name;
}

//this class inherited from the person class
//sub class
class vaccine:public person{
	//friend funtion
	friend void userInput (vaccine &ob);
	friend void menuOne (int passNo, int totalUser, vaccine ob[]);
	friend void menuTwo (int passNo, int totalUser, vaccine ob[]);
	friend void menuThree (int totalUser, vaccine ob[]);
	friend void menuFour (int totalUser, vaccine ob[]);
	friend void menuFive (int totalUser, vaccine ob[]);
	private :
		int status;
		string type;
		string date;
	public :
		vaccine();
		~vaccine();
		void setVaccineInfo(int, string, string);
		void displayInfo();
		void setStatus(int);
		int getStatus();
		string getType();
};
//funtion to set function information values
void vaccine::setVaccineInfo(int s, string t, string d){
	status = s;
	type = t;
	date = d;
}
//function to display user's current info
void vaccine::displayInfo(){
	cout << "----- This is your Current Info -----" << endl;
	cout << "Passport Number \t : " << passNo << endl;
	cout << "Name \t\t\t : " << name << endl;
	cout << "Gender \t\t\t : " << gender << endl;
	cout << "Age \t\t\t : " << age << endl;
	cout << "Vaccination Status \t : " << status << endl;
	cout << "Vaccine Type \t\t : " << type << endl;
	cout << "Vaccination Date \t : " << date << endl;
}
//funtion to set status value
void vaccine::setStatus(int s){
	status = s;
}
//function to return vaccination status value
int vaccine::getStatus(){
	return status;
}
//function to return vaccine type value 
string vaccine::getType(){
	return type;
}
//constructor
vaccine::vaccine(){
	status = 0;
	type = " ";
	date = " ";
}
//destructor
vaccine::~vaccine(){
	status = 0;
	type = " ";
	date = " ";
}

//this class using composition from vaccine class
class file{
	private :
		vaccine vac;//composition
	public :
		void createUserData(int, string, int, string, int, string, string);
		bool isUserExist(int);
};
//funtion to input user data into text file
void file::createUserData(int pn, string n, int a, string g, int s, string t, string d){
	ofstream outputFile;
	outputFile.open("prototype.txt", ios_base::app);

	//this conditional statement is checking weather the file is open or not
	if(outputFile){
		outputFile << pn << " " << n << " " << a << " " << g << " " << s << " " << t << " " << d << endl; 
		cout << "the user " << pn << " created" << endl;
	}else{
		cout << "cannot open the file" << endl;
	}
	outputFile.close();	
}
//this function is checking is user exist or not in text file
bool file::isUserExist(int pn){
	ifstream inputFile;
	inputFile.open("prototype.txt");
	
	int passNo, age, status;
	string name, gender, type, date;
	bool exist = false;
	//this loop will check  weather the given passport number is exist in the text file or not
	while (!inputFile.eof()){
		inputFile >> passNo >> name >> age >> gender >> status >> type >> date;
		if (passNo == pn){
			exist = true;
			break;
		}	
	}
	inputFile.close();
	
	return exist;
}

//friend function prototype
void userInput (vaccine &);
void menuOne (int, int, vaccine ob[]);
void menuTwo (int, int, vaccine ob[]);
void menuThree (int, vaccine ob[]);
void menuFour (int, vaccine ob[]);
//funtion prototype
float calPercentAge (float, int);

int main (){
	//variable declaration
	int passNumInput, passNumFile, age, status, totalUser, choice;
	char again;
	string name, gender, type, date;
	bool exist = false;
	int size = 100;
	//object declaration
	file userFile;
	vaccine vac;
	//array object declaration
	vaccine user[size];
	
	cout << "Welcome to Electronic COVID-19 Passport Information System (eCPIS)" << endl;
	cout << "Please Enter your Passport Number" << endl;
	cin >> passNumInput;
	cout << "Searching your Passport Number... " << endl;
	//this conditional statement is checking weather the file is open or not  
	if(!userFile.isUserExist(passNumInput)){
		//call friend function
		userInput(vac);
	}
	
	ifstream storeFile;
	storeFile.open("prototype.txt");
	int fileLineCounter = 0;
	//this loop will assign user data from text file into array object
	while(!storeFile.eof()){
		
		// retrieve data from text file
		storeFile >> passNumFile >> name >> age >> gender >> status >> type >> date;
		
		// insert values to array
		user[fileLineCounter].setPersonInfo(passNumFile, name, gender, age);
		user[fileLineCounter].setVaccineInfo(status, type, date);
		fileLineCounter++;
	}

	storeFile.close();
	//this loop will displaying menu continuously
	do {
	cout << "--==|Welcome User [" << passNumInput << "]|==--" << endl;
	cout << "Please Choose the Features by Entering its Number" << endl;
	cout << "1. Display Current Info" << endl;
	cout << "2. Update Vaccination Info" << endl;
	cout << "3. Statistic of Vaccination Info" << endl;
	cout << "4. List of Individuals Received Certain Vaccine" << endl;
	cout << "5. Vaccination Percentage According to Age" << endl;
	cout << "6. Exit" << endl;
	cout << "Enter the Number : ";
	cin >> choice;
	//validation
	while(choice <1 || choice >6){
		cout << "-----INVALID INPUT Only Accept (1-6)-----" << endl;
		cout << "Enter the Number : ";
		cin >> choice;
	}
	//this conditional statement will stop the loop if user enter 6
	if (choice == 6){
		break;
	}
	//this conditional statement will redirect the user to choosen menu 
	switch (choice){
		case 1 :
			menuOne(passNumInput, fileLineCounter, user);
			break;
		case 2 :
			menuTwo(passNumInput, fileLineCounter, user);
			break;
		case 3 :
			menuThree(fileLineCounter, user);
			break;
		case 4:
			menuFour(fileLineCounter, user);
			break;
		case 5 :
			menuFive(fileLineCounter, user);
			break;	
	}

	cout << "do you want to return to main menu? Y/N" << endl;
	cin >> again;
	//this statement will clear the screen
	system("cls");
	//this loop will iterate the menu		
	} while (again == 'Y' || again == 'y');
	
	cout << endl << endl << endl;
	cout << "--==|Thank You & See You Again :D|==--" << endl;
	cin.ignore();
	return 0;
}
//this friend function will recieve user input and manipulate it
void userInput (vaccine &ob){
	file userFile;
	cout << "You Have not Registered in the System" << endl;
	cout << "Please fill in the Information form below" << endl;
	cout << "Passport Number \t\t: ";
	cin >> ob.passNo;
	cout << "First Name \t\t\t: ";
	cin >> ob.name;
	cout << "Gender (Male/Female) \t\t: ";
	cin >> ob.gender;
	cout << "Age \t\t\t\t: ";
	cin >> ob.age;
	cout << "Vaccination Dose Status (0/1/2)\t: ";
	cin >> ob.status;
	cout << "Vaccine Type (Name) \t\t: ";
	cin >> ob.type;
	cout << "Vaccination Date (DD-MM-YY) \t: ";
	cin >> ob.date;
	//set person and vaccine info
	ob.setPersonInfo(ob.passNo, ob.name, ob.gender, ob.age);
	ob.setVaccineInfo(ob.status, ob.type, ob.date);
	//add user data into text file
	userFile.createUserData(ob.passNo, ob.name, ob.age, ob.gender, ob.status, ob.type, ob.date);
}
//this friend function will display first menu
void menuOne (int passNo, int totalUser, vaccine ob[]){
	//this loop will check passport number and display info
	for (int i=0; i<totalUser-1; i++){
		if (ob[i].getPassNo() == passNo){
			ob[i].displayInfo();
		}
	}
}
//this friend function will display second menu
void menuTwo (int passNo, int totalUser, vaccine ob[]){
	int status;
	//this loop will check user's vaccination status 
	for (int i=0; i<totalUser-1; i++){
		if (ob[i].getPassNo() == passNo){
			//validation
			if (ob[i].getStatus() == 2){
				cout << "You have been Vaccinated Twice, You can't Update your Status" << endl;
			} else {
			cout << "----- Enter your New Vaccination Status -----" << endl;
			cout << "Current Status \t\t: " << ob[i].getStatus() << endl;
			cout << "Vaccine Status (1/2) : ";
			cin >> status;
			//validation
			while(status == ob[i].getStatus()){
				cout << "INVALID INPUT" << endl;
				cout << "New Status can't be the same as Current Status" << endl;
				cout << "Vaccine Status (1/2) : ";
				cin >> status;
			}
			ob[i].setStatus(status);	
			}
		}
	}	
}
//this friend function will display third menu
void menuThree (int totalUser, vaccine ob[]){
	int unVac=0, parVac=0, fulVac=0; 
	//this loop will check user'vaccination status and increment it if true
	for (int i=0; i<totalUser-1; i++){
		if (ob[i].getStatus() == 0){
			unVac++;
		}else if(ob[i].getStatus() == 1){
			parVac++;
		}else {
			fulVac++;
			}
		}
	//displaying vaccination status chart
	cout << "----- Vaccination Statistic -----" << endl;
	cout << "Unvaccinated Person (" << unVac << ")\t\t: ";
	for (int i=0; i<unVac; i++){
		cout << "* ";
	}
	cout <<"\n";
	cout << "Partial Vaccinated Person (" << parVac << ")\t: ";
	for (int i=0; i<parVac; i++){
		cout << "* ";
	}
	cout <<"\n";
	cout << "Full Vaccinated Person (" << fulVac << ")\t: ";
	for (int i=0; i<fulVac; i++){
		cout << "* ";
	}
	cout <<"\n";			
}
//this friend function will display fourth menu
void menuFour (int totalUser, vaccine ob[]){
	cout << "----- List of Individuals Received Certain Vaccine -----" << endl;
	cout << "\n";
	cout << "--Sinovac--" << endl;
	//this loop will check user's vaccine type and display individual name if true
	for(int i=0; i<totalUser-1; i++){
		if(ob[i].getType() == "sinovac"){
			cout << "- " << ob[i].getName() << endl;
		}
	}
	cout << "\n";
	cout << "--Pfizer--" << endl;
	for(int i=0; i<totalUser-1; i++){
		if(ob[i].getType() == "pfizer"){
			cout << "- " << ob[i].getName() << endl;
		}
	}
	cout << "\n";
	cout << "--AstraZeneca--" << endl; 
	for(int i=0; i<totalUser-1; i++){
		if(ob[i].getType() == "astrazeneca"){
			cout << "- " << ob[i].getName() << endl;
		}
	}	
}
//this friend function will display fifth menu
void menuFive (int totalUser, vaccine ob[]){
	float total;
	float kid=0.0; //5-10 years old
	float teen=0.0; //11-20 years old
	float adult=0.0; //21-45 years old
	float old=0.0; //above 45 years old (>45)
	//this loop will check and incerement each age range if true
	for(int i=0; i<totalUser-1; i++){
		if (ob[i].getStatus() == 1 || ob[i].getStatus() == 2){
			if (ob[i].getAge() >= 5 && ob[i].getAge() <= 10){
				kid++;
			}else if (ob[i].getAge() >= 11 && ob[i].getAge() <= 20){
				teen++;
			}else if (ob[i].getAge() >= 21 && ob[i].getAge() <= 45){
				adult++;
			} else {
				old++;
			}
		total++;
		}
	}
	//displaying Vaccination Percentage According to Age
	cout << "----- Vaccination Percentage According to Age -----" << endl;
	cout << "Number of Individuals Vaccinated : " << total << endl;
	cout << "Kid \t\t[" << kid << "] : " << calPercentAge(kid, total) << "%" << endl;
	cout << "Teen \t\t[" << teen << "] : " << calPercentAge(teen, total) << "%" << endl;
	cout << "Adult \t\t[" << adult <<  "] : " << calPercentAge(adult, total) << "%" << endl;
	cout << "Aged (old) \t[" << old << "] : " << calPercentAge(old, total) << "%" << endl;
}
//funtion to calculate percentage
float calPercentAge(float category, int total){
	float percent;
	percent = (category/total)*100;
	return percent;
}

