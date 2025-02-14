#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Ingredient {
    string name;
    string type;
    int quantity = 4;
};

vector<string> colors = {"Red", "Orange", "Brown", "Green"};
map<string, string> ingredientMap = {
    {"Red", "Meat"},
    {"Orange", "Spices"},
    {"Brown", "Herbs"},
    {"Green", "Vegetables"}
};

vector<Ingredient> meats = {
    {"Beef", "meat", 4},
    {"Pork", "meat", 4},
    {"Beef broth", "meat", 4},
    {"Fried garlic", "meat", 4},
    {"Buffalo", "meat", 4},
    {"Bile", "meat", 4},
    {"Blood", "meat", 4},
    {"Offal", "meat", 4}
};

vector<Ingredient> herbs = {
    {"Makwaen", "herb", 4},
    {"Coriander", "herb", 4},
    {"Nut meg", "herb", 4},
    {"Star Anise", "herb", 4},
    {"black pepper", "herb", 4},
    {"Long pepper", "herb", 4},
    {"Cinnamon", "herb", 4},
    {"Clove", "herb", 4}
};

vector<Ingredient> vegetables = {
    {"Matoom", "vegetable", 4},
    {"KaowTong", "vegetable", 4},
    {"Oreille", "vegetable", 4},
    {"Deeplygung", "vegetable", 4},
    {"Makwen-infused fish sauce", "vegetable", 4},
    {"Dried Fennel Seed", "vegetable", 4},
    {"Phak paem", "vegetable", 4},
    {"Vietnamese Coriander", "vegetable", 4},
    {"Damocles tree", "vegetable", 4},
    {"Parsley", "vegetable", 4},
    {"Para cress", "vegetable", 4},
    {"Olive", "vegetable", 4}
};

vector<Ingredient> spice = {
    {"Makwaen", "spice", 4},
    {"Fragrant", "spice", 4},
    {"Fennel Seed", "spice", 4},
    {"Dried Galangal", "spice", 4},
    {"Cardamom", "spice", 4},
    {"Chili Spur Pepper", "spice", 4},
    {"Caraway", "spice", 4}
};

vector<string> fortuneCards = {"Suan Krua", "Moitgure", "Aoa Mue", "Hom Bun", "Regular Customer", "Moldy Cutting Board", "Hom poy", "Ngan Katin", "The Kitchen", "Rainy Season", "Broken Mortar", "Flipped Tray"};
map<string, int> ingredients = {
    {"Meat", 8 * 4},
    {"Herbs", 8 * 4},
    {"Spices", 7 * 4},
    {"Vegetables", 12 * 4}
};

struct Player {
    string name;
    int lastLarbMonth;
    vector<string> recipe;
    map<string, int> collectedIngredients;
};

vector<Player> players;
int currentPlayer = 0;

void drawFortuneCard() {
    int randomIndex = rand() % fortuneCards.size();
    string selectedCard = fortuneCards[randomIndex];
    
    cout << "Gangster's Fortune Card: " << selectedCard << endl;
}

void rollDice(Player &player) {
    vector<string> diceResults;
    set<string> uniqueColors;
    
    cout << player.name << " is rolling 4 dice...\n";
    for (int i = 0; i < 4; i++) {
        int roll = rand() % colors.size();
        diceResults.push_back(colors[roll]);
        uniqueColors.insert(colors[roll]);
    }
    
    cout << "Dice results: ";
    for (const string& color : diceResults) {
        cout << color << " ";
    }
    cout << endl;
    
    if (uniqueColors.size() == 4) {
        cout << "You got 4 different colors! Pick one ingredient of each color.\n";
        for (const string& color : uniqueColors) {
            if (ingredients[ingredientMap[color]] > 0) {
                player.collectedIngredients[ingredientMap[color]]++;
                ingredients[ingredientMap[color]]--;
            }
        }
    } else {
        cout << "You rolled duplicate colors! Drawing a fortune card...\n";
        drawFortuneCard();
    }
}

void setupGame() {
    int numPlayers;
    do {
        cout << "Enter number of players (max 4): ";
        cin >> numPlayers;
        if (numPlayers > 4) cout << "Too many players! Please enter again.\n";
    } while (numPlayers > 4);
    
    players.resize(numPlayers);
    
    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter name of player " << i + 1 << ": ";
        cin >> players[i].name;
        cout << "Enter months since " << players[i].name << " last ate larb: ";
        cin >> players[i].lastLarbMonth;
    }
    
    sort(players.begin(), players.end(), [](const Player &a, const Player &b) {
        return a.lastLarbMonth < b.lastLarbMonth;
    });
    
    cout << "Turn order: \n";
    for (const auto& player : players) {
        cout << player.name << "\n";
    }
}

void gameLoop() {
    while (true) {
        Player &player = players[currentPlayer];
        rollDice(player);
        
        bool hasWon = true;
        for (const auto &ingredient : player.recipe) {
            if (player.collectedIngredients[ingredient] < 1) {
                hasWon = false;
                break;
            }
        }
        
        if (hasWon) {
            cout << player.name << " has collected all ingredients and won the game!\n";
            break;
        }
        
        currentPlayer = (currentPlayer + 1) % players.size();
    }
}

int main() {
    srand(time(0));
    setupGame();
    gameLoop();
    return 0;
}
