#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<std::string> read_ingredients(std::string filename){

    std::ifstream file(filename);
    if (not file){
        std::cout << "Virhe tiedoston avaamisessa" << std::endl;
        return {};
    } else {
        std::vector<std::string> ingredients = {};
        std::string line;
        std::string word = "";

        while (getline(file, line)){
            for (unsigned int i = 0; i < line.length(); i++){
                if (line.at(i) == ','){

                    ingredients.push_back(word);
                    word.erase(0);

                } else {
                    if (line.at(i) != ' '){
                        word += toupper(line.at(i));
                    }
                }
            }
            ingredients.push_back(word);
        }
        file.close();
        return ingredients;
    }
}

std::vector<std::string> find_differences(std::vector<std::string> first,
                                             std::vector<std::string> second){

    /*

    std::vector<std::string> first = {};
    std::vector<std::string> second = {};

    if (list1.size() < list2.size()){
        first = list2;
        second = list1;
    } else {
        first = list1;
        second = list2;

    }*/

    std::vector<std::string> uniques = {};
    std::vector<std::string>::iterator it;

    for (unsigned int i = 0; i < first.size() ; i++){

        if (std::find(second.begin(), second.end(), first[i]) == second.end()){
            uniques.push_back(first[i]);
        }
    }

    return uniques;

}

void list_ingredients(std::string product, std::vector<std::string> list){

    sort(list.begin(), list.end());

    std::cout << product << " unique ingredients: " << std::endl;

    if (list.empty()){
        std::cout << "None" << std::endl;
    } else {
        for (unsigned int i = 0; i < list.size(); i++){
            std::cout << list[i] << std::endl;
        }
    }

    std::cout << std::endl;

}

void print_instructions(){
    std::cout << std::endl;
    std::cout << "   C - compare" << std::endl;
    std::cout << "   P - get a list of products" << std::endl;
    std::cout << "   H - help" << std::endl;
    std::cout << "   Q - quit program" << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::cout << "Welcome! Start by typing one of the following commands:" << std::endl;

    print_instructions();

    while(true){
        std::string command = "";
        std::cout << "Type your command: ";
        std::cin >> command;
        command = toupper(command[1]);

        if(command == "C"){
            std::string product1 = "";
            std::cout << "First product: ";
            std::cin >> product1;

            std::string product2 = "";
            std::cout << "Second product: ";
            std::cin >> product2;

            std::cout << std::endl;

            std::vector<std::string> ingr_list1 = {};
            ingr_list1 = read_ingredients(product1 + ".txt");

            std::vector<std::string> ingr_list2 = {};
            ingr_list2 = read_ingredients(product2 + ".txt");

            std::vector<std::string> pr1_list = find_differences(ingr_list1, ingr_list2);
            std::vector<std::string> pr2_list = find_differences(ingr_list2, ingr_list1);

            list_ingredients(product1, pr1_list);

            list_ingredients(product2, pr2_list);
            continue;
        } else if (command == "P"){
            //list_products()
            std::cout << "products here." << std::endl;
            continue;
        } else if (command == "H"){
            print_instructions();
        } else if (command == "Q"){
            break;
        } else {
            std::cout << "Not a valid command." << std::endl;
        }
    }

    return 0;
}
