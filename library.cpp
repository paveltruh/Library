#include "library.h"
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>


Library::~Library() {
	if (_is_changed) {
		try {
			upload();
		}
		catch (...) {}
	}
}

const std::vector<Library::Book>& Library::get_books(){
	return _books;
}

Library::Reader::Reader(std::string name, unsigned int id) {
	_name = name;
	_id = id;
}

bool Library::is_file_exists(const std::string& file_name){
	return  std::ifstream(file_name).is_open();
}

void Library::load() {
	load_vector_from_file(_books, "books.txt");
	load_vector_from_file(_readers, "readers.txt");
}

void Library::upload() {
	upload_vector_to_file( _readers, "readers.txt");
	upload_vector_to_file( _books, "books.txt");
}

const std::vector<Library::Reader>& Library::get_readers()
{
	return _readers;
}

void Library::add_book(const std::string& title, unsigned int count) {
	_is_changed = true;
	auto book = std::find(_books.begin(), _books.end(), title);
	if (book != _books.end()) {
		book->_count += count;
		return;
	}
	_books.push_back(Book(title, count));
}

void Library::add_reader(const std::string& name) {
	_is_changed = true;
	_readers.push_back(Reader(name, _readers.size()));
}

typename Library::Book* Library::get_book(const std::string& title) {
	auto book = std::find(_books.begin(), _books.end(), title);
	if (book == _books.end())
		return nullptr;
	return &(*book);
}

bool Library::is_book_exist(const std::string& title) {
	return get_book(title) != nullptr;
}

typename Library::Reader* Library::get_reader(unsigned int id) {
	auto reader = std::find_if(_readers.begin(), _readers.end(),
		[id](const Library::Reader& r) {	return r.get_id() == id;	});
	if (reader == _readers.end())
		return nullptr;
	return &(*reader);
}

bool Library::is_reader_exist(unsigned int id) {
	return get_reader(id) != nullptr;
}

bool Library::give_book_to_reader(const std::string& title, unsigned int id) {
	auto book = get_book(title);
	if (!is_book_exist(title) || book->_count == book->_reader_ids.size())
		return false;
	if (!is_reader_exist(id))
		return false;
	auto reader = get_reader(id);
	book->_reader_ids.push_back(reader->_id);
	reader->_book_titles.push_back(book->_title);
	_is_changed = true;
	return true;
}

bool Library::return_book_from_reader(const std::string& title, unsigned int id) {
	auto book = get_book(title);
	if (!is_book_exist(title) || book->_count == 0)
		return false;
	if (!is_reader_exist(id))
		return false;
	auto reader = get_reader(id);

	auto reader_id_in_book = std::find(book->_reader_ids.begin(),
		book->_reader_ids.end(), reader->_id);

	auto book_title_in_reader = std::find(reader->_book_titles.begin(),
		reader->_book_titles.end(), title);

	if (reader_id_in_book == book->_reader_ids.end() ||
		book_title_in_reader == reader->_book_titles.end())
		return false;
	book->_reader_ids.erase(reader_id_in_book);
	reader->_book_titles.erase(book_title_in_reader);
	_is_changed = true;
	return true;
}

template<typename T>
void Library::load_vector_from_file(std::vector<T>& vec, const std::string& file_name) {
	if (!is_file_exists(file_name)) {
		return;
	}
	std::ifstream file(file_name);
	if (!file)
		throw std::logic_error("Unable to read the file");
	T tmp;
	while (file >> tmp) {
		vec.push_back(tmp);
	}
}

template<typename T>
void Library::upload_vector_to_file(const std::vector<T>& vec, const std::string& file_name) {
	std::ofstream file(file_name, std::ios_base::trunc);
	if (!file)
		throw std::logic_error("Unable to write in file");
	for (const auto& i : vec)
		file << i;
}


std::istream& operator>>(std::istream& is, Library::Book& book) {
	std::string input;
	int readers_count = 0;
	std::getline(is, book._title);
	if (!is)
		return is;
	std::getline(is, input);
	std::stringstream sstream(input);
	sstream >> book._count >> readers_count;
	book._reader_ids.resize(readers_count);
	if (readers_count != 0) {
		for (auto& id : book._reader_ids) {
			sstream >> id;
		}
	}
	if (!is)
		throw std::logic_error("books load error");
	return is;
}
std::ostream& operator<<(std::ostream& os, const Library::Book& book) {
	os << book._title << std::endl;
	os << book._count << " ";
	os << book._reader_ids.size();
	if (!book._reader_ids.empty())
		os << "\t";
	for (auto& id : book._reader_ids)
		os << " " << id;
	os << std::endl;
	return os;
}
std::istream& operator>>(std::istream& is, Library::Reader& reader) {
	int books_count = 0;
	std::string input;
	std::getline(is, input);
	if (!is)
		return is;
	std::stringstream sstream(input);
	sstream >> reader._id >> books_count;
	getline(is, reader._name);
	reader._book_titles.resize(books_count);
	for (auto& book_title : reader._book_titles) {
		getline(is, book_title);
	}
	if (!is)
		throw std::logic_error("readers load error");
	return is;
}
std::ostream& operator<<(std::ostream& os, const Library::Reader& reader) {
	os << reader._id << " ";
	os << reader._book_titles.size() << std::endl;
	os << reader._name << std::endl;
	for (const auto& book_title : reader._book_titles)
		os << book_title << std::endl;
	return os;
}

Library::Book::Book(std::string title, unsigned int count) { 
	_title = title;
	_count = count; 
}
