#pragma once
#include<fstream>
#include<vector>

class Library {
public:
	class Book {
		std::string _title;
		unsigned int _count;
		std::vector<unsigned int> _reader_ids;
	public:
		Book() {}
		Book(std::string title, unsigned int count);
		const std::string& get_title() const { return _title; }
		unsigned int how_much_is_left () const { return _count - _reader_ids.size(); }
		bool operator==(const std::string& other) const { return _title == other; }

		friend Library;
		friend std::istream& operator>>(std::istream& is, Library::Book& book);
		friend std::ostream& operator<<(std::ostream& os, const Library::Book& book);
	};

	class Reader {
		unsigned int _id;
		std::string _name;
		std::vector<std::string> _book_titles;
	public:
		Reader() {}
		Reader(std::string name, unsigned int id);
		const std::string& get_name() const { return _name; }
		unsigned int get_id() const { return _id; }
		const std::vector<std::string>& get_book_titles() const { return _book_titles; }

		friend Library;
		friend std::istream& operator>>(std::istream& is, Library::Reader& reader);
		friend std::ostream& operator<<(std::ostream& os, const Library::Reader& reader);
	};
private:
	std::vector<Book> _books;
	std::vector<Reader> _readers;
	bool _is_changed = false;

	bool is_file_exists(const std::string& file_name);
	template<typename T>
	void upload_vector_to_file(const std::vector<T>& vec, const std::string& file_name);
	template<typename T>
	void load_vector_from_file(std::vector<T>& vec, const std::string& file_name);
	
public:

	void load();
	void upload();
	virtual ~Library();
	const std::vector<Book>& get_books();
	const std::vector<Reader>& get_readers();
	void add_book(const std::string& title, unsigned int count = 1);
	bool is_book_exist(const std::string& title);
	Book* get_book(const std::string& title);
	void add_reader(const std::string& name);
	bool is_reader_exist(unsigned int id);
	Reader* get_reader(unsigned int id);
	bool give_book_to_reader(const std::string& title, unsigned int id);
	bool return_book_from_reader(const std::string& title, unsigned int id);
};
