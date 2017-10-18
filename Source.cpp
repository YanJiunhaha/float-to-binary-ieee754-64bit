#include<iostream>
#include<fstream>
#include<string>
using namespace std;
typedef unsigned uint32;

#define MANTISSA 64
void main() {
	ifstream f_in;
	f_in.open("input.txt");
	ofstream f_out;
	f_out.open("output.txt");
	double in;
	int exponent = 1023;
	int mantissa = 0;
	int mantissa_exponent = 0;
	bool counter = false;
	string dec_str;
	string frc_str;
	string out="";
	int counter_success = 1;
	while (!f_in.eof())
	{
		f_in >> in;
		int dec=(int)in; 
		double frc=(in>1)?in-(int)in:in;
		while (dec > 0) {
			dec_str = ((dec & 1) ? '1' : '0') + dec_str;
			dec /= 2;
		}
		mantissa += dec_str.length();
		
		while (mantissa <= 52) {
			frc *= 2;
			if (frc > 1) {
				frc_str = frc_str + '1';
				frc = frc - (int)frc;
				counter = true;
			}
			else if(counter||in>1)frc_str = frc_str + '0';
			if (counter)mantissa++;
			else { 
				if (frc == 0)mantissa++;
				else if (in > 1) {
					mantissa++;
					mantissa_exponent++;
				}
				else(mantissa_exponent++);
			}
		}
		
		if (dec_str.length() != 0)exponent += dec_str.length()-1;
		else exponent -= (mantissa_exponent + 1);
		out =out+dec_str + frc_str;
		out.erase(out.begin());
		for (int i = 0; i < 11; i++) {
			out = ((exponent & 1) ? '1' : '0') + out; exponent /= 2;
		}
		out = '0' + out;
		
		f_out <<out<<endl;
		std::cout << "successful:" << counter_success++ << endl;
		dec_str = ""; frc_str = ""; out = ""; counter = false; mantissa = 0; mantissa_exponent = 0; exponent = 1023;
	}
	f_in.close();
	f_out.close();
	std::cout << "finish.";
	std::system("pause");
}
