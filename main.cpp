#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<string> meats = {"เนื้อวัว", "เนื้อหมู", "เนื้อไก่"};
vector<string> herbs = {"ใบสะระแหน่", "ผักชี", "ต้นหอม"};
vector<string> spices = {"พริกป่น", "ข้าวคั่ว", "น้ำปลา"};
vector<string> vegetables = {"ผักกาดขาว", "แตงกวา", "หอมแดง"};


vector<string> destinyCards = {
    "ได้ส่วนผสมเพิ่ม 1 ชิ้น", "เสียส่วนผสม 1 ชิ้น", "ขโมยส่วนผสมจากผู้เล่นอื่น",
    "แลกส่วนผสมกับผู้เล่นอื่น", "ได้ทอยลูกเต๋าอีกครั้ง", "เสียตาถัดไป"
};


string drawDestinyCard() {
    int index = rand() % destinyCards.size();
    return destinyCards[index];
}


vector<string> rollDice(int numDice) {
    vector<string> colors = {"แดง", "น้ำตาล", "ส้ม", "เขียว"};
    vector<string> result;
    for (int i = 0; i < numDice; ++i) {
        int index = rand() % colors.size();
        result.push_back(colors[index]);
    }
    return result;
}


bool hasDuplicates(vector<string> diceResult) {
    sort(diceResult.begin(), diceResult.end());
    auto last = unique(diceResult.begin(), diceResult.end());
    return last != diceResult.end();
}


struct Player {
    string name;
    string lastAteLab;
    vector<string> recipe;
    vector<string> ingredients;
};


int main() {
    srand(time(0));

    cout << "1. When starting the game, the person who ate the last Laab in the group will start first.\n";

    cout << "2. When it's their turn, the players roll all 4 dice to choose and pick the ingredients according to the color they rolled.\n";

    cout << "3. Dice roll results\n";

    cout << "-If the result shows 2 or more of the same color, the player must pick 1 event card. Near the picking of the ingredient coin, the event card will show the result immediately after picking.\n\n";

    cout << "4. If the player has received all the ingredients of that color as desired, the player can choose to pick ingredients from other colors instead.\n\n";

    cout << "5. End of the game The player who receives all the ingredients according to the Laab recipe first will be the winner. And you are the\n\n";

    cout << "REAL_gangster\n";

    int numPlayers;
    cout << "เลือกจำนวนผู้เล่น (ไม่เกิน 4 คน): ";

    cin >> numPlayers;


    vector<Player> players(numPlayers);
    for (int i = 0; i < numPlayers; ++i) {
        cout << "ผู้เล่น " << i + 1 << " กรุณาใส่ชื่อของคุณ: ";
        cin >> players[i].name;
        cout << "คุณกินลาบครั้งล่าสุดเมื่อไหร่: ";
        cin >> players[i].lastAteLab;
    }

   
    int currentPlayerIndex = rand() % numPlayers;
    cout << "ผู้เล่นที่เริ่มต้นคือ: " << players[currentPlayerIndex].name << endl;

 
    bool gameOver = false;
    while (!gameOver) {
        Player &currentPlayer = players[currentPlayerIndex];
        cout << "ตาของ " << currentPlayer.name << endl;

        vector<string> diceResult = rollDice(4);
        cout << "ผลลัพธ์ลูกเต๋า: ";
        for (string color : diceResult) {
            cout << color << " ";
        }
        cout << endl;

        if (hasDuplicates(diceResult)) {
            cout << "ได้สีซ้ำกัน ต้องเปิดการ์ดดวง!" << endl;
            string card = drawDestinyCard();
            cout << "การ์ดดวง: " << card << endl;
     
        } else {
            cout << "เลือกส่วนผสมตามสีที่ได้:" << endl;
            for (string color : diceResult) {
                if (color == "แดง") {
                    cout << "เลือกเนื้อ: ";
                    for (int i = 0; i < meats.size(); ++i) {
                        cout << i + 1 << ". " << meats[i] << " ";
                    }
                    int choice;
                    cin >> choice;
                    currentPlayer.ingredients.push_back(meats[choice - 1]);
                } else if (color == "น้ำตาล") {
                    cout << "เลือกสมุนไพร: ";
                    for (int i = 0; i < herbs.size(); ++i) {
                        cout << i + 1 << ". " << herbs[i] << " ";
                    }
                    int choice;
                    cin >> choice;
                    currentPlayer.ingredients.push_back(herbs[choice - 1]);
                } else if (color == "ส้ม") {
                    cout << "เลือกเครื่องเทศ: ";
                    for (int i = 0; i < spices.size(); ++i) {
                        cout << i + 1 << ". " << spices[i] << " ";
                    }
                    int choice;
                    cin >> choice;
                    currentPlayer.ingredients.push_back(spices[choice - 1]);
                } else if (color == "เขียว") {
                    cout << "เลือกผัก: ";
                    for (int i = 0; i < vegetables.size(); ++i) {
                        cout << i + 1 << ". " << vegetables[i] << " ";
                    }
                    int choice;
                    cin >> choice;
                    currentPlayer.ingredients.push_back(vegetables[choice - 1]);
                }
            }
        }
        currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
    }

    return 0;
}