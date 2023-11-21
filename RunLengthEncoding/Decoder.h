#pragma once
#include <iostream>
#include <fstream>


void expandFile(std::fstream& infile, std::fstream& outfile) {
	int ch1 = infile.get();
	outfile.put(ch1);
	int ch = ch1;
	unsigned short count = 1;
	while ((ch1 = infile.get()) != EOF) {
		outfile.put(ch1);
		if (ch1 == ch) {
			++count;
			if (count == 3) {
				count = 0;
				ch1 = infile.get();
				for (unsigned i{ 0 }; i < (unsigned)ch1; ++i) {
					outfile.put(ch);
				}
				ch1 = infile.get();
				outfile.put(ch1);
				ch = ch1;
				count = 1;
			}
		}
		else {
			ch = ch1;
			count = 1;
		}
	}
}