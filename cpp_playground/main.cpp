#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

class Job {
public:
	~Job() {
		cout << "[Deconstructor] Job " << endl;
	}
};

class Person {
public:
	string name;
	shared_ptr<Job> job_ref;
	Person(string p_name, shared_ptr<Job> p_job_ref) : name(p_name), job_ref(p_job_ref) {
		cout << "[Constructor] Person" << endl;
	}

	~Person() {
		cout << "[Deconstructor] Person name " << name << endl;
	}
};

void get_instance(Person p) {
	cout << "[Function] Person's name i got is " << p.name << " job_ref.use_count is " << p.job_ref.use_count() << endl;
}

void get_instance_as_ref(Person& p) {
	cout << "[Function] Person's name i got is " << p.name << " job_ref.use_count is " << p.job_ref.use_count() << endl;
}

void get_instance_as_ptr(Person* p) {
	cout << "[Function] Person's name i got is " << p->name << endl;
}

void main() {
	{
		auto job_ref = make_shared<Job>();

		//std::vector<Person> personVector = new std::vector<Person>({ Person("test1", job_ref) });
		std::vector<Person> personVector{ Person("test1", job_ref), Person("test2", job_ref) , Person("test3", job_ref) };

		cout << "----------------get_instance--------------------" << endl;
		Person p("Sam lee", job_ref);
		job_ref = nullptr;
		cout << "p use_count before get_instance() is " << job_ref.use_count() << endl;

		get_instance(p);
		cout << "p use_count before get_instance_as_ref() is " << job_ref.use_count() << endl;
		get_instance_as_ref(p);
		cout << "p use_count after get_instance_as_ref() is " << job_ref.use_count() << endl;
		p.job_ref = nullptr;
		cout << "p use_count after assigning nullptr is " << job_ref.use_count() << endl;

		cout << "------------end of scope-----------------" << endl;
	}

	while (true) {

	}
}