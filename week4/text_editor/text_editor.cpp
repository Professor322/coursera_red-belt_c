#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() = default;
  void Left() {
  	if (cursor != text.begin()) {
		cursor--;
	}
  }
  void Right() {
  	if (cursor != text.end()) {
		cursor++;
	}
  }
  void Insert(char token) {
  	text.insert(cursor, token);
  }
  void Cut(size_t tokens = 1) {
  	Copy(tokens);

  	while(tokens && cursor != text.end()) {
  		cursor = text.erase(cursor);
  		tokens--;
  	}
  }
  void Copy(size_t tokens = 1) {
  	buff.clear();
  	for (auto it = cursor;
  		it != text.end() && tokens != 0;
  		++it, --tokens)
  		buff.push_back(*it);
  }
  void Paste() {
  	list<char> temp_buff(buff.begin(), buff.end());
  	text.splice(cursor, temp_buff);
  }
  string GetText() const {
	  return  {text.begin(), text.end()};
  }

private:

	list<char> buff;
	list<char> text;
	list<char>::iterator cursor = text.end();
};




void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void CustomTest2() {
Editor editor;
TypeText(editor, "1234567");

editor.Left();

editor.Left();

editor.Cut(1);

editor.Paste();

editor.Paste();

editor.Paste();

ASSERT_EQUAL(editor.GetText(), "123456667");

}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
   	editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void CustomTest() {
	Editor e;
	const string text = "chlen";

	TypeText(e, text);
	for (int i = 0; i < text.size(); ++i) {
		e.Left();
	}
	e.Cut();
	e.Paste();
	e.Cut(1);
	ASSERT_EQUAL(e.GetText(), "clen");
}

void TestCut()
{
	Editor editor;
	//1
	editor.Cut(10);
	editor.Insert('a');
	editor.Left();
	//2
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	//3
	editor.Cut(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	TypeText(editor, "bcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//5
	editor.Cut(5);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	//6
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bcde");
	editor.Right();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bde");
	editor.Cut(1);
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
	Editor editor;
	//1
	editor.Copy(10);
	editor.Insert('a');
	editor.Paste();
	editor.Left();
	ASSERT_EQUAL(editor.GetText(), "a");
	//2
	editor.Copy(1);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");//between a
	//3
	editor.Copy(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");
	TypeText(editor, "bcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcdea");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
	RUN_TEST(tr, CustomTest);
RUN_TEST(tr, TestCut);
	RUN_TEST(tr, CustomTest2);
  return 0;
}