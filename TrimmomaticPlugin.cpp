#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "TrimmomaticPlugin.h"

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
 for (int i = 0; i < arguments.size(); i++) {
	 if (arguments[i].size() != 0) {
    command += arguments[i];
    command += " ";
	 }
 }
 command += "-baseout "+file;
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<TrimmomaticPlugin> TrimmomaticPluginProxy = PluginProxy<TrimmomaticPlugin>("Trimmomatic", PluginManager::getInstance());
