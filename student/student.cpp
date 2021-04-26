#include <iostream>
#include <string>

struct Student {
	std::string imie;
	std::string nazwisko;
	std::string indeks;
	std::string aktualny_semestr;
	float srednia_ocen;

	Student(std::string imie, std::string nazwisko, std::string indeks);
	std::string toString();
};

std::string Student::toString(){
	return imie + " " + nazwisko + " " + indeks;
}

Student::Student(std::string im, std::string na, std::string in){
	imie = im;
	nazwisko = na;
	indeks = in;
}

auto main() -> int {
	auto student = Student("Jarek", "Podarek", "s31243");
	std::cout << student.toString() << "\n";
	return 0;
}
