#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
struct appointment {
	int hours;
	int minutes;
};
// Creating a class person which is an abstract class since no persons will be created. Either a docto or a patient is created
class Person {

private:
	string name;
	int id;
	int age;
public:
	Person() :name(""), id(0), age(20) {
		//cout << "Base default constructor\n";
	}
	Person(string n, int a, int i) :name(n), age(a), id(i) { //cout << "Base parapertrized constructor\n";
	}
	Person(const Person& obj) //in the copy constructor, const is used because we want to guarantee that nothing will change in the object.
		//TO MAKE SURE: the & is used in this copy constructor for a better usage of memory (no need to make a copy at first)
	{
		name = obj.name;
		id = obj.id;
		age = obj.age;
	}
	void setName(string n) {
		this->name = n; //just using this keyword to practice.
	}

	void setId(int id) {
		this->id = id; // No problem to use the same word "id" twice because the this keyword differntiates. What is with it is the attribute of the obj.
	}

	void setAge(int n) {
		age = n;
	}

	string getName() const {
		return name;
	}
	int getId() const {
		return id;
	}
	int getAge() const {
		return age;
	}
	virtual void print()
	{
		cout << "name: " << name << endl;
		cout << "id: " << id << endl;
		cout << "age: " << age << endl;
	}

};

class Patient : public Person {
private:

	appointment app;
	int doctorID;
	string doctorName; // for simplicity to print the doctor's name without looping with the id to match with the dr.
public:
	//Patient() : Person("", 0, 0) {}
	Patient(string n = "", int age = 0, int id = 0) :Person(n, age, id) {
	}
	void setAppointment(appointment ap) {//Every object in the class will have an appointment app. We differentiate normally by the object that calls the function.
		app.hours = ap.hours;
		app.minutes = ap.minutes;
	}
	void setDoctorID(int id) {
		doctorID = id;
	}
	void setDoctorName(string n) {
		doctorName = n;
	}
	string getDoctorName()
	{
		return doctorName;
	}
	appointment getAppointment() const {
		return app;
	}
	int getDoctorID() const {
		return doctorID;
	}

	bool operator< (const Patient& pat2) {
		if (this->app.hours < pat2.app.hours)
			return true;
		if (this->app.hours == pat2.app.hours)
			if (this->app.minutes < pat2.app.minutes)
				return true;
		return false;
	}
	bool operator> (const Patient& pat2) {
		if (this->app.hours > pat2.app.hours)
			return true;
		if (this->app.hours == pat2.app.hours)
			if (this->app.minutes > pat2.app.minutes)
				return true;
		return false;
	}
	bool operator== (const Patient& pat2) {
		if (this->app.hours == pat2.app.hours && this->app.minutes == pat2.app.minutes)
			return true;
		return false;
	}

	void print() {
		cout << "name: " << this->getName() << endl;
		cout << "id: " << this->getId() << endl;
		cout << "age: " << this->getAge() << endl;
		cout << "Appointment at: " << app.hours << ":" << app.minutes << " with Dr. " << doctorName << endl;
	}
};

class Doctor : public Person {
private:
	int counter;
	appointment appArr[100];
public:
	/*	Doctor() : Person("", 0, 0) {
			cout << "Default constructor of dr\n";
		}*/
	Doctor(string name = "", int age = 0, int id = 0) :Person(name, age, id) {
		//cout << "Doctor parametrized & default constructor\n";
		counter = -1;
	}
	bool available(appointment a) {
		for (int i = 0; i <= counter; i++)
			if (a.hours == this->appArr[i].hours && a.minutes == this->appArr[i].minutes)    //if the doctor is available now but will be busy like in 10 minutes should I consider this?
			{
				//cout << "Counter: " << counter << " here..." << getName() << endl;
				return false;
			}
		return true;
	}

	void setAppointments(appointment ap)
	{
		counter++;
		appArr[counter].hours = ap.hours;
		appArr[counter].minutes = ap.minutes;
	}
	void print() {
		cout << "name: " << this->getName() << endl;
		cout << "id: " << this->getId() << endl;
		cout << "age: " << this->getAge() << endl;
		cout << "number of appointments: " << this->counter + 1 << endl;
		for (int i = 0; i < counter; i++)
			cout << "Appointment " << i + 1 << " at: " << appArr[i].hours << ":" << appArr[i].minutes << endl;

	}
};
template <class T> 
class queue : public Patient {
private:
	int back = -1; //to be anto into a constructor
	T arr[100];
public: // for simplicity, no need to define the functions out the class
	T enqueue(const T pat) {
		back++;
		arr[back] = pat;
		return pat;
	}
	T dequeue(const T pat) {
		T temp = pat;
		back--;
		return temp;
	}
	void print()  //print the the statements in a form of Ahmed has an appointment at: 1:00. with Dr Ayman
	{
		cout << "\nPatients' appointments\n";
		for (int i = 0; i <= back; i++)
		{
			cout << arr[i].T::getName() << " has an appointment at " << arr[i].T::getAppointment().hours << ":";
			if (arr[i].T::getAppointment().minutes < 10)
				cout << 0;
			cout<< arr[i].T::getAppointment().minutes << " with Dr. " << arr[i].T::getDoctorName() << endl;
		}
	}

	void printInfo()  //print the full information of the patients IN ORDER (if needed)
	{
		cout << "\nInfo of patients in order\n";
		for (int i = 0; i <= back; i++)
		{
			cout << "Patient " << i + 1 << " info:\n";
			arr[i].T::print();
			cout << endl;
		}
	}

};

int main() {
	
	int nofDoctors;
	Doctor* arrDoctors;
	//cout << "Initializing the array of doctors\n";
	string name;
	int age, id, appointments;
	appointment ap;
	int nofPatients;
	Patient* arrPatients; 
	

	char c = 'F';
	cout << "Welcome! How do you want the data to be entered (F for a file and U for user input)\n";
	cin >> c;
	

	if (c == 'F' || c == 'f') {
		ifstream myfile;
		myfile.open("Readme.txt");
		if (!myfile.is_open())
		{
			cout << "Error while opening the file\n";
			return 0;
		}

		else
		{
			string n;
			getline(myfile, n);
			stringstream obj(n);
			obj>>nofDoctors;
			arrDoctors = new Doctor[nofDoctors];
			for (int i = 0; i < nofDoctors; i++) {
				getline(myfile, n);
				name=n;
				getline(myfile, n);
				istringstream(n) >> age;
				getline(myfile, n);
				istringstream(n) >> id;
				getline(myfile, n);
				istringstream(n) >> appointments;
				arrDoctors[i] = Doctor(name, age, id);
				for (int j = 0; j < appointments; j++)
				{
					getline(myfile, n);
					istringstream(n) >> ap.hours;
					getline(myfile, n);
					istringstream(n) >> ap.minutes;
					arrDoctors[i].setAppointments(ap);
				}
			}
			getline(myfile, n);
			nofPatients = stoi(n);
			arrPatients = new Patient[nofPatients];
			for (int i = 0; i < nofPatients; i++) {
				getline(myfile, n);
				name=n;
				getline(myfile, n);
				istringstream(n) >> age;
				getline(myfile, n);
				istringstream(n) >> id;
				arrPatients[i] = Patient(name, age, id);
				getline(myfile, n);
				istringstream(n) >> ap.hours;
				getline(myfile, n);
				istringstream(n) >> ap.minutes;
				arrPatients[i].setAppointment(ap);
			}
			getline(myfile, n);
			cout << n;
		}
	}
	else 	if (c == 'U' || c == 'u')
	{
		cout << "Enter the number of Doctors\n";
		cin >> nofDoctors;
		arrDoctors = new Doctor[nofDoctors]; // HERE CALLS THE DEFAULT CONSTRUCTOR nofDoctors times and therefore CALLS THE BASE PARAMETRIZED CONSTRUCTOR
		//cout << "Doctors' array initialized\n";

		for (int i = 0; i < nofDoctors; i++)
		{
			cout << "\nDoctor " << i + 1 << " info:\n";
			cout << "Name: ";
			cin >> name;
			cout << "Age: ";
			cin >> age;
			cout << "ID: ";
			cin >> id;
			cout << "Number of appointments: ";
			cin >> appointments;
			arrDoctors[i] = Doctor(name, age, id);
			if (appointments > 0)
				cout << "Enter the time of the appointment\n";
			for (int j = 0; j < appointments; j++)
			{
				cout << "Appointment " << j + 1 << endl;
				cout << "hour: ";
				cin >> ap.hours;
				cout << "minute: ";
				cin >> ap.minutes;
				arrDoctors[i].setAppointments(ap);
			}
		}


		//for (int i = 0; i < nofDoctors; i++)
		//{
		//	cout << "Dr " << i + 1 << " info:\n";
		//	arrDoctors[i].print();
		//}



		cout << "\nNumber of patients\n";
		cin >> nofPatients;
		arrPatients = new Patient[nofPatients];
		for (int i = 0; i < nofPatients; i++)
		{
			cout << "\nPatient " << i + 1 << " info:\n";
			cout << "Name: ";
			cin >> name;
			cout << "Age: ";
			cin >> age;
			cout << "ID: ";
			cin >> id;
			arrPatients[i] = Patient(name, age, id);
			cout << "Enter the time of the appointment\n";
			cout << "hour: ";
			cin >> ap.hours;
			cout << "minute: ";
			cin >> ap.minutes;
			arrPatients[i].setAppointment(ap);
		}
	}

	else { cout << "invalid input\n"; return 0; }
	//for (int i = 0; i < nofPatients; i++)
	//{
	//	cout << "Patient " << i + 1 << " info:\n";
	//	arrPatients[i].print();
	//}



	for (int i = 0, j = 0; i < nofPatients; i++)
	{
		while (arrDoctors[j].available(arrPatients[i].getAppointment()) == false)
		{
			j++;
			if (j == nofDoctors)
				j = 0;
		}
		//cout << "Setting the dr. id with " << arrDoctors[j].getId() << endl;
		arrPatients[i].setDoctorID(arrDoctors[j].getId());
		arrPatients[i].setDoctorName(arrDoctors[j].getName());
		arrDoctors[j].setAppointments(arrPatients[i].getAppointment());
		j++;
		if (j == nofDoctors)
			j = 0;
	}
	//cout << endl << endl;
	//for (int i = 0; i < nofPatients; i++)
	//{
	//	cout << "Patient " << i + 1 << " info:\n";
	//	arrPatients[i].print();
	//	cout << endl;
	//}

	Patient min;
	for (int i = 0, index; i < nofPatients - 1; i++)
	{
		min = arrPatients[i];
		for (int j = i + 1; j < nofPatients; j++)
		{
			if (arrPatients[j] < min)
			{
				min = arrPatients[j];
				//index = j;
				arrPatients[j] = arrPatients[i];
				arrPatients[i] = min;
			}
		}

	}

	//cout << endl << "In order\n"<<endl;
	//for (int i = 0; i < nofPatients; i++)
	//{
	//	cout << "Patient " << i + 1 << " info:\n";
	//	arrPatients[i].print();
	//	cout << endl;
	//}
	queue<Patient> queueofPatients;
	for (int i = 0; i < nofPatients; i++)
		queueofPatients.enqueue(arrPatients[i]);
	queueofPatients.print();

	return 0;
}