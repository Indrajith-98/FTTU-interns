#include <iostream>
#include <fstream>
#include <ostream>
#include <nlohmann/json.hpp>
#include "utils.h"
#include "compare_outputs.h"
#include "test_main.h"

void unit_test(){

    std::string base_dir = "F:/MultiCoreWare/C++ Application/Project_Root/";

    std::ofstream unit_test_log(base_dir + "report/unit_test_log.txt");

    unit_test_log << "Unit Testing Begins" << std::endl;

    unit_test_log << "==================================================" << std::endl;

    std::string json_config_path = "F:/MultiCoreWare/C++ Application/Project_Root/configs/json/layers_config.json";
    nlohmann::json config = load_json_config(json_config_path);

    for (const auto& layer : config["layers"]) {

        if (layer["type"] != "Dropout" && layer["type"] != "Flatten"){
        unit_test_log << "Validating the output of " << layer["layer_name"] << " with python output" << std::endl;
        const std::string cpp_file_path = base_dir + "/data/cpp_layer_outputs/" + std::string(layer["layer_name"]) + ".txt";
        const std::string python_file_path = base_dir + "/data/python_layer_outputs/" + std::string(layer["layer_name"]) + ".txt";

        std::vector<float> cpp_vector = readValuesFromFile(cpp_file_path);
        std::vector<float> python_vector = readValuesFromFile(python_file_path);


        if (compareVectors(cpp_vector, python_vector)) unit_test_log << "Validation Successful"<< std::endl;
        else unit_test_log << "Validation Failed" << std::endl;

        unit_test_log << "==================================================" << std::endl;
        } 
    }

    unit_test_log << "Unit Testing Ends" << std::endl;
}

void model_test() {

    std::string base_dir = "F:/MultiCoreWare/C++ Application/Project_Root/";

    std::ofstream model_test_log(base_dir + "report/model_test_log.txt");

    model_test_log << "Model Testing Begins" << std::endl;

    std::string classes[10] = {"airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"};
    
    std::string json_config_path = "F:/MultiCoreWare/C++ Application/Project_Root/configs/json/layers_config.json";
    nlohmann::json config = load_json_config(json_config_path);

    const std::string cpp_file_path = base_dir + "data/cpp_layer_outputs/" + std::string(config["layers"][config["layers"].size() - 1]["layer_name"]) + ".txt";
    const std::string python_file_path = base_dir + "data/python_layer_outputs/" + std::string(config["layers"][config["layers"].size() - 1]["layer_name"]) + ".txt";

    std::vector<float> cpp_vector = readValuesFromFile(cpp_file_path);
    std::vector<float> python_vector = readValuesFromFile(python_file_path);

    if (compareVectors(cpp_vector, python_vector)) {
        model_test_log << "Final Dense Output of Python = [ ";
        for (int i = 0 ; i < python_vector.size() ; ++i) model_test_log << python_vector[i] << " ";
        model_test_log << "]" << std::endl;

        auto max_elem = std::max_element(python_vector.begin(), python_vector.end());
        int max_index = std::distance(python_vector.begin(), max_elem);

        model_test_log << "Predicted Class of Python = " << classes[max_index] << std::endl;

        model_test_log << "==================================================" << std::endl;

        model_test_log << "Final Dense Output of C++ = [ ";
        for (int i = 0 ; i < cpp_vector.size() ; ++i) model_test_log << cpp_vector[i] << " ";
        model_test_log << "]" << std::endl;

        max_elem = std::max_element(cpp_vector.begin(), cpp_vector.end());
        max_index = std::distance(cpp_vector.begin(), max_elem);

        model_test_log << "Predicted Class of C++ = " << classes[max_index] << std::endl;

        model_test_log << "==================================================" << std::endl;

        model_test_log << "Validation Successful"<< std::endl;

        model_test_log << "==================================================" << std::endl;

        }

        else {model_test_log << "Validation Failed" << std::endl;}

        model_test_log << "Model Testing Ends" << std::endl;
   }
