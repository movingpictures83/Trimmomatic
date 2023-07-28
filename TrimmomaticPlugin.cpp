#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "TrimmomaticPlugin.h"

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void TrimmomaticPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string myarg;
   ifile >> myarg;
   arguments.push_back(myarg);
 }
}

void TrimmomaticPlugin::run() {
   
}

void TrimmomaticPlugin::output(std::string file) {
 // alpha_diversity.py -i filtered_otu_table.biom -m observed_species,chao1,shannon,PD_whole_tree -t rep_set.tre -o alpha.txt
   std::string command = "trimmomatic ";
   if (arguments[0] == "PE") {
 for (int i = 0; i < arguments.size(); i++) {
	 if (arguments[i].size() != 0) {
		 if (hasEnding(arguments[i], "fastq") || hasEnding(arguments[i], "fastq.gz")) {
                    arguments[i] = std::string(PluginManager::prefix()) + "/" + arguments[i];
		 }
    command += arguments[i];
    command += " ";
	 }
 }
 command += "-baseout "+file;
 std::cout << command << std::endl;
   }
 else {
	 command += arguments[0] + " ";
	 command +=  std::string(PluginManager::prefix()) + "/" + arguments[1] + " ";
	command += file + " "; 
 for (int i = 2; i < arguments.size(); i++) {
    command += arguments[i];
    command += " ";
	 }

 }
 system(command.c_str());
}

PluginProxy<TrimmomaticPlugin> TrimmomaticPluginProxy = PluginProxy<TrimmomaticPlugin>("Trimmomatic", PluginManager::getInstance());
