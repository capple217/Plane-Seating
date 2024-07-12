// CIS 142 Airplane Seating Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 1. View Seating; 2. Books Seats: 2.1. Singles: 2.1.1. Choose seat type || 2.2 Multiple Seats: 2.2.1 Choose Quantity: 2.2.2 Choose Type

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#define ROWS 13
#define COLS 6


class AirplaneSeating {
	std::string seatingChart[ROWS][COLS];
	std::string columnIndex[COLS] = { "A", "B", "C", "D", "E", "F" };
	int takenCounter = 0;
	int totalSeats = ROWS * COLS;

public:
	AirplaneSeating() {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				seatingChart[i][j] = "*";
			}
		}
	}

	int enoughSeats() {
		int numOfSeats;
		std::cin >> numOfSeats;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Invalid input. Please enter a number\n";
			return 0;
		}

		if (totalSeats - takenCounter < numOfSeats) {
			std::cerr << "Sorry, there's not enough seats\n";
			return 0;
		}
		return numOfSeats;
	}

	bool seatType(int seatRow) {
		int choice3;
		std::string classType;

		if (1 <= seatRow && seatRow <= 2) {
			classType = "first class";
		}
		else if (3 <= seatRow && seatRow <= 7) {
			classType = "business class";
		}
		else if (8 <= seatRow && seatRow <= 13) {
			classType = "economy class";
		}
		else {
			std::cerr << "Invalid row number\n";
			return false;
		}

		std::cout << "Would you like to book this " << classType <<" seat?\n";
		std::cout << "1: Yes\n";
		std::cout << "2: No\n";
		std::cin >> choice3;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Invalid input. Please enter 1 or 2\n";
			return false;
		}

		switch (choice3) {
		case 1:
			return true;
		case 2:
			return false;
		default:
			std::cerr << "Invalid choice, please try again\n";
			return false;
		}
	}

	void seatBooker(int numOfSeats) {
		for (int i = 0; i < numOfSeats; i++) {
			std::cout << "Seat #" << i + 1 << " (Column Row, e.g., D5): ";
			std::string seatColLetter, seatRowStr;
			std::cin >> seatColLetter >> seatRowStr;

			if (seatColLetter.length() != 1 || !isalpha(seatColLetter[0])) {
				std::cerr << "Please input a valid column letter\n";
				i--;
				continue;
			}

			seatColLetter[0] = toupper(seatColLetter[0]);

			if (seatRowStr.empty() || !std::all_of(seatRowStr.begin(), seatRowStr.end(), ::isdigit)) {
				std::cerr << "Please input a valid row number\n";
				i--;
				continue;
			}

			int seatRow = std::stoi(seatRowStr);

			if (seatRow > ROWS || seatRow <= 0) {
				std::cerr << "Please input a valid row number\n";
				i--;
				continue;
			}

			auto it = std::find(columnIndex, columnIndex + COLS, seatColLetter);
			if (it == columnIndex + COLS) {
				std::cerr << "Please input a valid column letter\n";
				i--;
				continue;
			}

			int seatCol = std::distance(columnIndex, it);

			if (seatingChart[seatRow - 1][seatCol] == "*") {
				if (!seatType(seatRow)) {
					i--;
					continue;
				}

				seatingChart[seatRow - 1][seatCol] = "X";
				takenCounter++;
				std::cout << "Booked " << seatColLetter << seatRow << "!\n";
			}
			else {
				std::cerr << "Sorry, that seat is taken\nPlease choose another seat\n";
				i--;
			}
		}
	}

	void seatView() {

		std::cout << "\t\t" << "A\t" << "B\t" << "C\t" << "D\t" << "E\t" << "F\t\n\n";

		for (int i = 0; i < ROWS; i++) {
			std::cout << "Row " << i + 1 << "\t\t";
			for (int j = 0; j < COLS; j++) {
				std::cout << seatingChart[i][j] << "\t";
			}
			std::cout << "\n\n";
		}
	}
};

int main() {
	AirplaneSeating interface;
	std::cout << "Thank you for choosing CIS 142 Airlines!\n";

	int choice1, choice2;
	do {
		std::cout << "1. View Seating\n";
		std::cout << "2. Leave\n";
		std::cin >> choice1; 

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Invalid input. Please enter 1 or 2\n";
			continue;
		}

		switch (choice1) {
		case 1:
			interface.seatView();
			std::cout << "Would you like to book?\n";
			std::cout << "1. Book Seat\n";
			std::cout << "2. Back\n";
			std::cin >> choice2;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cerr << "Invalid input. Please enter 1 or 2\n";
				continue;
			}

			if (choice2 == 1) {
				std::cout << "How many seats would you like to book?\n";
				int num = interface.enoughSeats();
				if (num > 0) {
					interface.seatBooker(num);
				}
			}
			else if (choice2 == 2) {
				break;
			}
			else {
				std::cerr << "Improper input\n";
			}
			break;
		case 2:
			break;
		default:
			std::cerr << "Invalid choice, please try again";}

	} while (choice1 != 2);

	return 0;
}

