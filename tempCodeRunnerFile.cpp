#include<bits/stdc++.h>
#include "json.hpp"


using json = nlohmann::json;
using namespace std;


string lowercase(string str) {
    for (char& c : str) c = tolower(c);
    return str;
}

struct Recipe{
    string name;
    vector<string> ingredients;
};

struct MatchResult {
    Recipe recipe;
    int matchedIngredients;
    int totalIngredients;
    double matchPercentage() const {
        return (double)matchedIngredients / totalIngredients;
    }
};


int main(){
        ifstream file("RecipesAndIngredients.json");
    if (!file.is_open()) {
        cerr << "Could not open RecipesAndIngredients.json\n";
        return 1;
    }

    json j;
    file >> j;

    vector<Recipe> recipes;
    for (auto& item : j) {
        Recipe r;
        r.name = item["name"];
        for (auto& ing : item["ingredients"]) {
            string ingStr = ing;
            lowercase(ingStr);
            r.ingredients.push_back(ingStr);
        }
        recipes.push_back(r);
    }
   
    cout<< "Enter your ingredients separated by spaces, then press Enter:";
    unordered_set<string> useringredient;
    string ingredient;
    while(cin>>ingredient){
        ingredient= lowercase(ingredient);
        useringredient.insert(lowercase(ingredient));
        if(cin.peek()=='\n') break;
    }
    vector<MatchResult> matchesList;

for (auto& recipe : recipes) {
    int matches = 0;
    for (auto& ing : recipe.ingredients) {
        if (useringredient.count(ing)) matches++;
    }
    if (matches > 0) {
        matchesList.push_back({recipe, matches, (int)recipe.ingredients.size()});
    }
}

    sort(matchesList.begin(), matchesList.end(), [](const MatchResult& a, const MatchResult& b) {
    if (a.matchPercentage() == b.matchPercentage())
        return a.matchedIngredients > b.matchedIngredients;
    return a.matchPercentage() > b.matchPercentage();
});

      for (const auto& match : matchesList) {
    cout << match.recipe.name 
         << " (" << match.matchedIngredients << "/" << match.totalIngredients 
         << " matched - " << int(match.matchPercentage() * 100) << "%)\n";
}
    return 0;
}