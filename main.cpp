#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include "pliib.hpp"
#include "tinyfa.hpp"
#include "vcfheader.hpp"


using namespace std;
using namespace TFA;

void usage(){
    cerr << "bed2vcf <bedfile> <fasta> > out.vcf" << endl;
}

int main(int argc, char** argv){

    string dummy_base = "A";

    if (argc != 3){
        usage();
        exit(1);
    }

    tiny_faidx_t tf;
    if (!checkFAIndexFileExists(argv[2])){
        createFAIndex(argv[2], tf);
    }
    else{
        // Parses an FAI file when passed a FASTA file name.
        parseFAIndex(argv[2], tf);
    }

    // Handle header
    vcfh::Header h;
    h.set_reference(argv[2]);
    h.set_source("bed2vcf");
    h.set_version("VCF4.2");
    cout << h << endl;

    unordered_map<string, string> seqcache;

    // Parse bed file
    ifstream ifi;
    ifi.open(argv[1], std::fstream::in);
    string line;
    while (std::getline(ifi, line)){
        ostringstream os;
        vector<string> tokens = pliib::split(line, '\t');
        if (seqcache.find(tokens[0]) == seqcache.end()){
            char* seq;
            TFA::getSequence(tf, tokens[0].c_str(), seq);
            string s(seq);
            seqcache[tokens[0]] = s;
            delete [] seq;
        }

        size_t pos = stoull(tokens[1]);
        size_t len = stoull(tokens[2]) - pos + 1;

        os << tokens[0] << '\t' << tokens[1] << '\t' <<
            "." << '\t' <<
            seqcache.at(tokens[0]).substr(pos - 1, len) << '\t' << "N" << '\t' <<
            "99" << '\t' << "PASS" << "";
        os << endl;
        cout << os.str();

    }


    return 0;
};
