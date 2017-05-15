#include<string>
#include<vector>
#include<fstream>

using namespace std;

class student;

class mediator
{
public: 
	void Send_info(string information, student *adr);
};

class student 
{
protected:
	mediator *mediator_;
	string name;
public:
	student(mediator *med, string n) 
	{
		this->mediator_ = med;
		this->name = n;
	}
	string get_name() { return name; }
};

void mediator::Send_info(string information, student *adr)
{
	string to_print = adr->get_name() + ": " + information + "\n\n";
	fstream f;
	f.open("info_for_students.txt", ios_base::app);
	f << to_print;
	f.close();
}

class concrete_student :public student
{
public:
	concrete_student(mediator *m, string n) :student(m,n){};
	void send_info(string information) { mediator_->Send_info(information, this); }
};

class concrete_mediator:public mediator
{
	vector<concrete_student*> students;
public:
	void add_new_student(string name) 
	{
		concrete_student* nst = new concrete_student(this, name);
		students.push_back(nst);
	}
	bool send(string who_from, string info)
	{
		int pos = 0;
		while (pos < students.size() && students[pos]->get_name()!=who_from)
		{
			pos++;
		}
		if (pos < students.size())
		{
			students[pos]->send_info(info); return true;
		}
		else return false;
	}
};