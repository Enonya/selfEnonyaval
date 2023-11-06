// author : black_trees

#include <bits/stdc++.h>

#ifdef __linux__
	#include <cstdlib>
#elif _WIN32
	#include <windows.h>
#endif

using namespace std;
using u64 = unsigned long long;

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

	string sep = "#====================================#\n";

	if(argc < 2) {
		cout << "Usage: senyv <FILE> <EXT_IN> <EXT_OUT> <EXT_USR> <CHECKER>" << endl;
		cout << "\t FILE: cpp source file, without extension name" << endl;
		cout << "\t EXT_IN: extension of input file, default: in" << endl;
		cout << "\t EXT_OUT: extension of output file (jury's out), default: out" << endl;
		cout << "\t EXT_USR: extension of user's output file, default: usr" << endl;
		cout << "\t CHECKER: file name of checker(cpp), without extension name, not inneed" << endl;
		cout << "  Possible formats:" << endl;
		cout << "\t >$ senyv <FILE>" << endl;
		cout << "\t >$ senyv <FILE> <CHECKER>" << endl;
		cout << "\t >$ senyv <FILE> <EXT_IN> <EXT_OUT> <EXT_USR>" << endl;
		cout << "\t >$ senyv <FILE> <EXT_IN> <EXT_OUT> <EXT_USR> <CHECKER>" << endl;
		return 0;
	}

	string fileName = string(argv[1]), chkName = "$$$";
	string extIn = "in", extOut = "out", extUsr = "usr";

	if(argc == 3) chkName = string(argv[2]);
	if(argc == 5) 
		extIn = string(argv[2]), extOut = string(argv[3]), extUsr = string(argv[4]); 
	if(argc == 6) 
		extIn = string(argv[2]), extOut = string(argv[3]), extUsr = string(argv[4]), chkName = string(argv[5]); 

	extIn = "." + extIn, extOut = "." + extOut, extUsr = "." + extUsr;

	// compile source file.
	cout << endl << "Compiling file: " << fileName << ".cpp" << endl;
	if(system(("g++ " + fileName + ".cpp -o" + fileName + " -std=c++14 -Wall -Wextra -Wshadow -O2").c_str())) {
		cout << "[Error] source file: " << fileName << ".cpp does not pass the compilation." << endl;
		return 0;
	}
	cout << "Compile success." << endl << endl;
	
	// compile checker file.
	if(chkName != "$$$") {
		cout << "Compiling file: " << chkName << ".cpp" << endl;
		if(system(("g++ " + chkName + ".cpp -o" + chkName + " -std=c++17 -Wall -Wextra -Wshadow -O2").c_str())) {
			cout << "[Error] source file: " << chkName << ".cpp does not pass the compilation." << endl;
			cout << "Compile success." << endl << endl;
		}
		return 0;
	}


	string path = fs::current_path().string();

	std::vector<fs::path> tc;

	for(const auto &entry : fs::directory_iterator(path)) {
		fs::path tmp = entry;
		string ext = tmp.extension().string();
		if(ext == extIn) tc.push_back(tmp);
	}

	sort(tc.begin(), tc.end(), [&](fs::path x, fs::path y) -> bool {
		return x.string() < y.string();
	});

	cout << "Start testing..." << endl;
	for(auto pth : tc) {
		string ts = pth.string();
		while(ts.back() != '.') ts.pop_back();
		ts.pop_back();

		cout << sep << "Testing test case: " << ts << endl << endl;
		
		u64 t = clock();
#ifdef _WIN32	
		system((fileName + ".exe < " + ts + extIn + " > " + ts + extUsr).c_str());
#else
		system(("./" + fileName + " < " + ts + extIn + " > " + ts + extUsr).c_str());
#endif
		u64 runTime = (clock() - t);
		
#ifdef _WIN32
		if(!system(("fc " + ts + extOut + " " + ts + extUsr + " /w").c_str())) 
			cout << "Accepted, time = " << runTime << "ms." << endl;
		else return cout << "Wrong answer." << endl << sep, 0;
#else
		if(!system(("diff " + ts + extOut + " " + ts + extUsr).c_str())) 
			cout << "Accepted, time = " << runTime << "s." << endl;
		else return cout << "Wrong answer." << endl << sep, 0;
#endif
	}
	cout << sep;

	return 0;
}

// TODO: timeout chekck.
// TODO: memory testing.
// TODO: color support.
