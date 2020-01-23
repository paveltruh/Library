#include <iostream>
#include "library.h"
#include "libraryview.h"

enum class Options : unsigned int {
	exit,
	view_all_books,
	view_all_readers,
	find_book,
	find_reader,
	add_book,
	add_reader,
	give_book_to_reader,
	return_book_from_reader,
	upload_changes
};


int main() {
	std::unique_ptr<Library> library;
	try {
		library = std::make_unique<Library>();
		library->load();
	}
	catch (std::exception & ex) {
		std::cout << ex.what();
		return EXIT_FAILURE;
	}
	LibraryView view(std::move(library));
	std::cout << "0 - Exit\n";
	std::cout << "1 - View all books\n";
	std::cout << "2 - View all readers\n";
	std::cout << "3 - Find book\n";
	std::cout << "4 - Find reader\n";
	std::cout << "5 - Add new book\n";
	std::cout << "6 - Add new reader\n";
	std::cout << "7 - Give book to reader\n";
	std::cout << "8 - Return book to reader\n";
	std::cout << "9 - Upload changes\n";
	while (true) {
		int int_option;
		int first_option = static_cast<int>(Options::exit);
		int last_option = static_cast<int>(Options::upload_changes);
		std::cout << "\nSelect the option: ";
		while (!(std::cin >> int_option) ||
			(int_option < first_option || int_option > last_option)){
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cout << "Wrong input \n";
			std::cout << "Select the option: ";
		}
		Options option = static_cast<Options>(int_option);
		if (option == Options::exit)
			break;
		switch (option) {
		case Options::view_all_books: {
			view.view_all_books();
			break;
		}
		case Options::view_all_readers: {
			view.view_all_readers();
			break;
		}
		case Options::find_book: {
			view.find_book();
			break;
		}
		case Options::find_reader: {
			view.find_reader();
			break;
		}
		case Options::add_book: {
			view.add_book();
			break;
		}
		case Options::add_reader: {
			view.add_reader();
			break;
		}
		case Options::give_book_to_reader: {
			view.give_book_to_reader();
			break;
		}
		case Options::return_book_from_reader: {
			view.return_book_from_reader();
			break;
		}
		case Options::upload_changes: {
			if (!view.upload_changes())
				return EXIT_FAILURE;
			else
				std::cout << "Uploading successful\n";
			break;
		}
		}
	} 
}
