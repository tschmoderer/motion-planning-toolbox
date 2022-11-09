#include <iostream>
#include <fstream>
#include <string>
#include "./assets/json.hpp"

#ifndef BUILD_DIR
    #define BUILD_DIR ""
#endif

#ifndef SOURCE_DIR
    #define SOURCE_DIR ""
#endif

using json = nlohmann::json;
using namespace std;

int nb_run = 0; 

void data_has(json dat, string key) {
    if (!dat.contains(key)) {
        string err = "Experience should have a key : " + key + ".";
        throw runtime_error(err);
    }
}

void check_dynamical_exp_data(json data) {
    assert(data["type"] == "dynamical");
    data_has(data, "name");
    data_has(data, "run");

    if (data["run"]) {
        nb_run++;
    }

    // check general 
    data_has(data["general"], "state_dim");
    data_has(data["general"], "start_time");
    data_has(data["general"], "end_time");
    data_has(data["general"], "x0");

    if (data["general"]["x0"].size() < 1) {
        throw runtime_error("Error: x0 should at least have one vector of data");
    }

    for (uint32_t i = 0; i < data["general"]["x0"].size(); i++) {
        if (data["general"]["x0"][i].size() != data["general"]["state_dim"]) {
            string err = "Error Initial vector x0 does not have proper dimension. ";
            err += "state_dim : "; 
            err += to_string(data["general"]["state_dim"]); 
            err += " and size(x0) : "; 
            err += to_string(data["general"]["x0"][i].size());
            err += ".";
            throw runtime_error(err);
        }
    }
    
    // check discretisation
    data_has(data, "discretisation");
    data_has(data["discretisation"], "trajectory");
    data_has(data, "methods"); 
    data_has(data["methods"], "ode_int");

    // check output 
    data_has(data, "output"); 
    if (data["output"]["file"]["yn"]) {
        data_has(data["output"]["file"], "dir");
        data_has(data["output"]["file"], "subdir");
        data_has(data["output"]["file"], "filename");
    }
}

void check_control_exp_data(json data) {

}

void check_exp_data(json exp_data) {
    int nb_exp = exp_data["experiences"].size();

    if (nb_exp <= 0) {
        throw runtime_error("At least one experience should be parametrised.");
    }

    cout << endl << "Check input data for ";
    if (nb_exp == 1) {
        cout << nb_exp << " experience.";
    } else {
        cout << nb_exp << " experiences.";
    }
    cout << endl; 

    for (int i = 0; i < nb_exp; i++) {
        cout << "Exp. " << i+1 << " / " << nb_exp << "\t---\t";
        if (exp_data["experiences"][i]["type"] == "dynamical") {
            check_dynamical_exp_data(exp_data["experiences"][i]); 
            cout << "Ok" << endl;
        } else if (exp_data["experiences"][i]["type"] == "control") {
            check_control_exp_data(exp_data["experiences"][i]); 
            cout << "Ok" << endl;
        } else {
            throw std::runtime_error("Experience type must be dynamical or control.");
        }
    }

}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 */
json check_input(int argc, char **argv) {
    if (argc < 2) {
        throw std::runtime_error("main.cpp: A .json file must be provided to parametrise the experiment(s).\n");
    }
    
    json exp_data;

    try {
        std::ifstream f(argv[1]);
        exp_data = json::parse(f, 
                        /* callback */ nullptr,
                        /* allow exceptions */ true,
                        /* ignore_comments */ true); 
                        
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("Parsing json data failed.");
    }

    check_exp_data(exp_data);
    
    return exp_data;
}

void write_header( char **argv, json data) {
    string current_dir = argv[0];
    string tmp; 
    current_dir = current_dir.substr(0, current_dir.find_last_of('/'));

    ofstream f(current_dir + "/bin/exp.hpp", ios::trunc); 
    f << "#ifndef EXP_HPP" << endl; 
    f << "#define EXP_HPP" << endl; 

    f << endl;
    tmp = data["type"];
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
    f << "#define EXP_TYPE_" << tmp << endl; 
    f << "#define EXP_TYPE " << data["type"] << endl; 
    f << "#define EXP_NAME " << data["name"] << endl;

    f << endl;

    f << "#define EXP_STATE_DIM " << data["general"]["state_dim"] << endl;
    f << "#define EXP_START_TIME " << data["general"]["start_time"] << endl;
    f << "#define EXP_END_TIME " << data["general"]["end_time"] << endl;
    f << "#define EXP_NB_X0 " << data["general"]["x0"].size() << endl; 

    f << "#define EXP_X0S ";
    for (uint32_t i = 0; i < data["general"]["x0"].size(); i++) {
        for (int j = 0; j < data["general"]["state_dim"]; j++) {
            if (data["general"]["x0"][i][j].type_name() == string("string")) {
                tmp = data["general"]["x0"][i][j]; 
                f << tmp; 
            } else {
                f << data["general"]["x0"][i][j];
            }
            if ((i < data["general"]["x0"].size()-1) || (j < int(data["general"]["state_dim"])-1)) {
                f << ", ";
            }      
        }
    }
    f << ";" << endl << endl;    

    for (auto it = data["dynamics"]["parameters"].begin(); it != data["dynamics"]["parameters"].end(); ++it)  {
        f << "#define " << it.key() << " ";
        if (data["dynamics"]["parameters"][it.key()].type_name() == string("string")) {
            tmp = it.value();
            f << tmp << endl;
        } else {
            f << it.value() << endl;
        }       
    }
    
    f << "#define EXP_DYNAMICS_F "; 
    for (int i = 0; i < int(data["dynamics"]["f"].size()); i++) {
        tmp = data["dynamics"]["f"][i]; 
        //tmp = tmp.substr(0, current_dir.find_last_of('"'));
        f << tmp << " ";
    }
    f << endl;

    f << "#define EXP_DYNAMICS_dFdX "; 
    for (int i = 0; i < int(data["dynamics"]["dfdx"].size()); i++) {
        tmp = data["dynamics"]["dfdx"][i]; 
        f << tmp << " ";
    }
    f << endl << endl;

    f << "#define EXP_DISCRETISATION_TRAJ " << data["discretisation"]["trajectory"] << endl;
    f << endl;

    tmp = data["methods"]["ode_int"]; 
    f << "#define EXP_METHODS_ODE_INT " << tmp << endl; 
    f << endl;

    f << "#define EXP_OUTPUT_CLI " << data["output"]["cli"] << endl; 
    f << "#define EXP_OUTPUT_FILE " << data["output"]["file"]["yn"] << endl; 
    if (data["output"]["file"]["yn"]) {
        f << "#define EXP_OUTPUT_FILE_DIR " << data["output"]["file"]["dir"] << endl;
        f << "#define EXP_OUTPUT_FILE_SUBDIR " << data["output"]["file"]["subdir"] << endl;
        f << "#define EXP_OUTPUT_FILE_FNAME " << data["output"]["file"]["filename"] << endl;
    } else {
        f << "#define EXP_OUTPUT_FILE_DIR " << "\"\"" << endl;
        f << "#define EXP_OUTPUT_FILE_SUBDIR " << "\"\"" << endl;
        f << "#define EXP_OUTPUT_FILE_FNAME " << "\"\"" << endl; 
    }

    f << endl << "#endif";
}

int main(int argc, char **argv) {
    // check and parse data
    json data = check_input(argc, argv);
    cout << "-- " << nb_run << " experiment(s) will be performed. --" << endl;

    int nb_exp = data["experiences"].size(); 

    for (int i = 0; i < nb_exp; i++) {
        if (data["experiences"][i]["run"]) {
            write_header(argv, data["experiences"][i]);
            cout << endl << "\t--\tCOMPILING EXP ";
            cout << i+1;
            cout << "\t--\t" << endl; 

            // compile exp file 
            string tmp = "make -s -f "; 
            tmp += BUILD_DIR;
            tmp += "/app/bin/Makefile exp";
            if (!system(tmp.c_str()))  {
                cout << "\t--\tCOMPILATION SUCCESSFUL\t--\t" << endl; 
            } else {
                throw runtime_error("Main there was an error in the compilation of your experiment.");
            }

            // execute exp file
            cout << endl << "\t--\tEXECUTE EXP ";
            cout << i+1; 
            cout << "\t--\t" << endl; 
            
            tmp = SOURCE_DIR;
            tmp += "/bin/exp";
            system(tmp.c_str());

            cout << endl << "\t--\tENDING EXP ";
            cout << i+1; 
            cout << "\t--\t" << endl; 
        }
    }

    // End code
    return 0;
}