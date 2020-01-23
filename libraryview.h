#pragma once
#include "library.h"
#include <memory>

class LibraryView {
	std::unique_ptr<Library> _library;
public:
	LibraryView(std::unique_ptr<Library> library);
	void find_book();
	void find_reader();
	void add_book();
	void add_reader();
	void give_book_to_reader();
	void return_book_from_reader();
	void view_all_books();
	void view_all_readers();
	bool upload_changes();
};

