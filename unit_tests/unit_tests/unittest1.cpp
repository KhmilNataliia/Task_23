#include "stdafx.h"
#include "CppUnitTest.h"

#include "catch.hpp"
#include "mediator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{		
	TEST_CASE("info_send")
	{
		concrete_mediator *m = new concrete_mediator();
		m->add_new_student("John");
		fstream pre; pre.open("info_for_students.txt", ios_base::out); pre.clear(); pre.close();
		m->send("John", "Hello!!!");
		fstream f; f.open("info_for_students.txt");
		string s1, s2;
		f >> s1; f >> s2; s1 += " " + s2;
		f.close();
		REQUIRE(s1 == "John: Hello!!!");
	};
	TEST_CASE("wrong_name")
	{
		concrete_mediator *m = new concrete_mediator();
		m->add_new_student("John");
		bool res=m->send("Johnny", "Hello!!!");
		
		REQUIRE(res==false);
	};
	TEST_CASE("few_students")
	{
		concrete_mediator *m = new concrete_mediator();
		m->add_new_student("John");
		m->add_new_student("Den");
		fstream pre; pre.open("info_for_students.txt", ios_base::out); pre.clear(); pre.close();
		m->send("John", "Hello!!!");
		m->send("Den", "Hi,have we a test tomorrow?");
		fstream f; f.open("info_for_students.txt");
		string s1, s2,s3;
		f >> s1; f >> s2; s1 += " " + s2;
		f >> s3; f >> s2; s3 += " " + s2;
		f >> s2; s3 += " " + s2;
		f >> s2; s3 += " " + s2;
		f >> s2; s3 += " " + s2;
		f >> s2; s3 += " " + s2;
		f.close();
		bool res = true;
		if (s1 != "John: Hello!!!" || s3 != "Den: Hi,have we a test tomorrow?") res = false;
		REQUIRE(res==true);
	};
}