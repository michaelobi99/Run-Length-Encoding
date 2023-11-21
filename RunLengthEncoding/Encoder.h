#pragma once
#include <iostream>
#include <fstream>


void compressFile(std::fstream& infile, std::fstream& outfile) {
	int ch;
	int ch1;
	ch = infile.get();
	ch1 = ch;
	unsigned short count = 1;
	while ((ch = infile.get()) != EOF) {
		if (ch == ch1) {
			++count;
			if (count == 258) {
				outfile.put(ch1);
				outfile.put(ch1);
				outfile.put(ch1);
				outfile.put(255);
				ch = infile.get();
				ch1 = ch;
				count = 1;
			}
		}
		else {
			if (count == 1) outfile.put(ch1);
			else if (count == 2) { outfile.put(ch1);  outfile.put(ch1); }
			else {
				outfile.put(ch1);
				outfile.put(ch1);
				outfile.put(ch1);
				char remaining = (char)(count)-3;
				outfile.put(remaining);
			}
			ch1 = ch;
			count = 1;
		}
	}
	for (unsigned i = 0; i < count; ++i)
		outfile.put(ch1);
}



	//std::fstream file{ R"(C:\Users\HP\source\repos\Burrows-Wheeler-Transfrom\Burrows-Wheeler-Transfrom\testFile2.txt)", std::ios_base::in | std::ios_base::binary };
	//std::fstream file2{ R"(C:\Users\HP\source\repos\Burrows-Wheeler-Transfrom\Burrows-Wheeler-Transfrom\testFile23.txt)", std::ios_base::in | std::ios_base::binary };
	//char c1, c2;
	//file.get(c1);
	//file2.get(c2);
	//if (c1 != c2) { std::cout << "failed"; exit(1); }
	//while (file.get(c1) && file2.get(c2)) {
	//	//std::cout << c1 << "=>" << c2 << "\n";
	//	if (c1 != c2) { std::cout << "failed"; exit(1); }
	//}