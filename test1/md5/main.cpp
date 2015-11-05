#include "MD5.h"
#include <iostream>  

using namespace std;

void PrintMD5(const string &str, MD5 &md5) {
	cout << "MD5(\"" << str << "\") = " << md5.toString() << endl;
}

string FileDigest(const string &file) {

	ifstream in(file.c_str(), ios::binary);
	if (!in)
		return "";

	MD5 md5;
	std::streamsize length;
	char buffer[1024];
	while (!in.eof()) {
		in.read(buffer, 1024);
		length = in.gcount();
		if (length > 0)
			md5.update(buffer, length);
	}
	in.close();
	return md5.toString();
}

int main() {

	cout << MD5("abc").toString() << endl;
	cout << MD5(ifstream("D:\\test.txt")).toString() << endl;
	cout << MD5(ifstream("D:\\test.exe", ios::binary)).toString() << endl;
	cout << FileDigest("D:\\test.exe") << endl;

//	MD5 md5("e10adc3949ba59abbe56e057f20f883e00000001");
	MD5 md5("111111");	//96e79218965eb72c92a549dd5a330112
	string code = md5.toString();
	md5.reset();
	md5.update("00000001");
	PrintMD5("00000001", md5);

	md5.update("a");
	PrintMD5("a", md5);

	md5.update("bc");
	PrintMD5("abc", md5);

	md5.update("defghijklmnopqrstuvwxyz");
	PrintMD5("abcdefghijklmnopqrstuvwxyz", md5);

	md5.reset();
	md5.update("message digest");
	PrintMD5("message digest", md5);

	md5.reset();
	md5.update(ifstream("D:\\test.txt"));
	PrintMD5("D:\\test.txt", md5);
	return 0;
}