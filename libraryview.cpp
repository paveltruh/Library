#include "libraryview.h"
#include <iostream>
#include <string>

LibraryView::LibraryView(std::unique_ptr<Library> library) {
	_library = std::move(library);
}

void LibraryView::view_all_readers()
{
	auto& readers = _library->get_readers();
	std::cout << "\tId \tName\n";
	for (const auto& reader : readers)
		std::cout << '\t' << reader.get_id() << '\t' << reader.get_name() << std::endl;

}

void LibraryView::view_all_books()
{
	std::cout << "\tShow not available books\n";
	std::cout << "\t1 - Yes\n";
	std::cout << "\t2 - No\n\t";
	int answer;
	const int yes = 1, no = 2;
	while (!(std::cin >> answer) || (answer != yes && answer != no)) {
		std::cout << "\tWrong input\n";
		std::cout << "\t1 - Yes\n";
		std::cout << "\t2 - No\n\t";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	auto& books = _library->get_books();
	if (books.empty()) {
		std::cout << "\tLibrary doesn't have books";
		return;
	}
	if (answer == yes) {
		for (auto book : books)
			std::cout << '\t' << book.get_title() << std::endl;
	}
	else {
		bool are_books_available = false;
		for (auto book : books) {
			if (book.how_much_is_left() != 0) {
				are_books_available = true;
				std::cout << '\t' << book.get_title() << std::endl;
			}
		}
		if (!are_books_available)
			std::cout << "\tLibrary doesn't have available books";
	}
}

void LibraryView::return_book_from_reader() {
	std::string title;
	std::cout << "\tEnter book title: ";
	std::cin.ignore(255, '\n');
	std::getline(std::cin, title);
	if (!_library->is_book_exist(title)) {
		std::cout << "\tNo such book\n";
		return;
	}
	int id;
	std::cout << "\tEnter reader id: ";
	while (!(std::cin >> id)) {
		std::cout << "\tWrong input\n";
		std::cout << "\tEnter reader id: ";
		std::cin.clear();
		std::cin.ignore(255, '\n');
	}
	if (!_library->is_reader_exist(id)) {
		std::cout << "\tNo such reader\n";
		return;
	}
	if (!_library->return_book_from_reader(title, id))
		std::cout << "\tError\n";
	else
		std::cout << "\tSuccess\n";
}

bool LibraryView::upload_changes()
{
	try {
		_library->upload();
	}
	catch (std::exception & ex) {
		std::cout << ex.what();
		return false;
	}
	return true;
}

void LibraryView::give_book_to_reader() {
	std::string title;
	std::cout << "\tEnter book title: ";
	std::cin.ignore(255, '\n');
	std::getline(std::cin, title);
	if (!_library->is_book_exist(title)) {
		std::cout << "\tNo such book\n";
		return;
	}
	if (_library->get_book(title)->how_much_is_left() == 0) {
		std::cout << "\tAll such books were taken\n";
		return;
	}
	int id;
	std::cout << "\tEnter reader id: ";
	while (!(std::cin >> id)) {
		std::cout << "\tWrong input\n";
		std::cout << "\tEnter reader id: ";
		std::cin.clear();
		std::cin.ignore(255, '\n');
	}
	if (!_library->is_reader_exist(id)) {
		std::cout << "\tNo such reader\n";
		return;
	}
	if (!_library->give_book_to_reader(title, id))
		std::cout << "\tError\n";
	else
		std::cout << "\tSuccess\n";

}

void LibraryView::add_reader() {
	std::string name;
	std::cout << "\tEnter reader name: ";
	std::cin.ignore(255, '\n');
	std::getline(std::cin, name);
	_library->add_reader(name);
	std::cout << "\tAdded\n";
}

void LibraryView::add_book() {
	std::string title;
	std::cout << "\tEnter book title: ";
	std::cin.ignore(255, '\n');
	std::getline(std::cin, title);
	int count;
	std::cout << "\tEnter book count: ";
	std::cin >> count;
	_library->add_book(title, count);
	std::cout << "\tAdded\n";
}

void LibraryView::find_reader() {
	int id;
	std::cout << "\tEnter reader id: ";
	while (!(std::cin >> id)) {
		std::cout << "\tWrong input\n";
		std::cout << "\tEnter reader id: ";
	}
	auto reader = _library->get_reader(id);
	if (!reader) {
		std::cout << "\tNo such reader\n";
		return;
	}
	std::cout << "\tReader exist. Show his books?\n";
	int yes = 1, no = 2, answer;
	std::cout << "\t\t1 - Yes\n";
	std::cout << "\t\t2 - No\n\t\t";
	while (!(std::cin >> answer))
		std::cout << "\t\tWrong input:\n";
	if (answer == yes) {
		if (reader->get_book_titles().size() == 0)
			std::cout << "\t\tUser has no books\n";
		else
			std::cout << "\t\t" << reader->get_name() << " books:\n";
		for (auto book : reader->get_book_titles())
			std::cout << "\t\t" << book << std::endl;
	}
}

void LibraryView::find_book() {
	std::string title;
	std::cout << "\tEnter book title: ";
	std::cin.ignore(255, '\n');
	std::getline(std::cin, title);
	auto book = _library->get_book(title);
	if (!book) {
		std::cout << "\tNo such book\n";
		return;
	}
	if (book->how_much_is_left() == 0)
		std::cout << "\tAll the books went up\n";
	if (book->how_much_is_left() == 1)
		std::cout << "\tThere is only one such book\n";
	else
		std::cout << '\t' << book->how_much_is_left() << " such books left\n";
}
