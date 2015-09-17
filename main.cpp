#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

// Stores command values
string command = "";

// Game running? (for exit)
bool game_running = true;

// Your money
int money;

// Stock Positions
struct stock{
  int pos;
  int owned;
  int colour;
  string name;
  string fullName;
}stocks[6];

enum stockNames{
  GOLD,
  SILVER,
  OIL,
  BONDS,
  INDUSTRIAL,
  GRAIN
};

// Windows Stuff for colours
HANDLE  hConsole;

// Random number generator. Use int random(lowest,highest);
int random(int newLowest, int newHighest){
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}

// Init
void init(){
  // New random generator
  srand( time(NULL));

  // Windows stuff
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // Welcome message
  cout << "Welcome to stock ticker!\n\n Use HELP to get started\n";

  // Init stocks
  for( int i = 0; i < 6; i ++){
    stocks[i].pos = 1000;
    stocks[i].owned = 0;

    // Stock colours
    switch (i){
      case GOLD:
        stocks[i].colour = 0x06;
        stocks[i].name = "GLD. ";
        stocks[i].fullName = "Gold";
        break;
      case SILVER:
        stocks[i].colour = 0x0F;
        stocks[i].name = "SLV. ";
        stocks[i].fullName = "Silver";
        break;
      case OIL:
        stocks[i].colour = 0x0C;
        stocks[i].name = "OIL. ";
        stocks[i].fullName = "Oil";
        break;
      case BONDS:
        stocks[i].colour = 0x0A;
        stocks[i].name = "BND. ";
        stocks[i].fullName = "Bonds";
        break;
      case INDUSTRIAL:
        stocks[i].colour = 0x0D;
        stocks[i].name = "IND. ";
        stocks[i].fullName = "Industrial";
        break;
      case GRAIN:
        stocks[i].colour = 0x0E;
        stocks[i].name = "GRN. ";
        stocks[i].fullName = "Grain";
        break;
      default:
        stocks[i].colour = 0x07;
        stocks[i].name = "NNE.";
        stocks[i].fullName = "None";
        break;
    }

  }

  // Start money
  money = 5000;
}

// Roll dice


// Main game
void game(){
  // Get a command
  cin >> command;

  // Check command
  if( command == "HELP"){
    cout << " HELP:displays the help menu\n"
         << " BUY: Buys the specified amount of the specified stock\n"
         << " SELL: Sells the specified amount of the specified stock\n"
         << " STOCKS: Lists available stocks and the values\n"
         << " INV: View all money and stocks you own\n"
         << " BOARD: View game board visual\n"
         << " ROLL: Rolls the dice (ends turn)\n";
  }
  else if( command == "BUY"){
    // Store number
    int command_int = 0;
    int command_int2 = 0;

    cout << " What would you like to buy? (number value) You have $" << money
         << "\n  1.GOLD(" << stocks[0].owned << ") $" << stocks[0].pos
         << "\n  2.SILVER(" << stocks[1].owned << ") $" << stocks[1].pos
         << "\n  3.OIL(" << stocks[2].owned << ") $" << stocks[2].pos
         << "\n  4.BONDS(" << stocks[3].owned << ") $" << stocks[3].pos
         << "\n  5.INDUSTRIAL(" << stocks[4].owned << ") $" << stocks[4].pos
         << "\n  6.GRAIN(" << stocks[5].owned << ") $" << stocks[5].pos << "\n";
    cin >> command_int;

    cout << "Ok, how many shares (in 1000's)?:";
    cin >> command_int2;

    // Check moneys
    command_int --;
    if( stocks[command_int].pos * command_int2 <= money){
      money -= stocks[command_int].pos * command_int2;
      stocks[command_int].owned += command_int2;
      cout << command_int2 * 1000 << " shares bought\n";
    }
    else{
      cout << "Not enought money to buy " << command_int2 * 1000 << " shares.\n";
    }
  }
  else if( command == "SELL"){
    // Store number
    int command_int = 0;
    int command_int2 = 0;

    cout << " What would you like to sell? (number value) You have $" << money
         << "\n  1.GOLD(" << stocks[0].owned << ") $" << stocks[0].pos
         << "\n  2.SILVER(" << stocks[1].owned << ") $" << stocks[1].pos
         << "\n  3.OIL(" << stocks[2].owned << ") $" << stocks[2].pos
         << "\n  4.BONDS(" << stocks[3].owned << ") $" << stocks[3].pos
         << "\n  5.INDUSTRIAL(" << stocks[4].owned << ") $" << stocks[4].pos
         << "\n  6.GRAIN(" << stocks[5].owned << ") $" << stocks[5].pos << "\n";
    cin >> command_int;

    cout << "Ok, how many shares? (in 1000's)";
    cin >> command_int2;

    // Check moneys
    command_int --;
    if( command_int2 <= stocks[command_int].owned){
      money += stocks[command_int].pos * command_int2;
      stocks[command_int].owned -= command_int2;
      cout << command_int2 * 1000 << " shares sold\n";
    }
    else{
      cout << "Not enought stocks to sell " << command_int2 * 1000 << " shares.\n";
    }
  }
  // Stock Prices
  else if( command == "STOCKS"){
    cout << " GOLD: $" << stocks[0].pos << "\n"
         << " SILVER: $" << stocks[1].pos << "\n"
         << " OIL: $" << stocks[2].pos << "\n"
         << " BONDS: $" << stocks[3].pos << "\n"
         << " INDUSTRIAL: $" << stocks[4].pos << "\n"
         << " GRAIN: $" << stocks[5].pos << "\n";
  }
  // Views stocks and money
  else if( command == "INV"){
    cout << " You have $" << money
         << "\n  GOLD: " << stocks[0].owned << " shares"
         << "\n  SILVER: " << stocks[1].owned << " shares"
         << "\n  OIL: " << stocks[2].owned << " shares"
         << "\n  BONDS: " << stocks[3].owned << " shares"
         << "\n  INDUSTRIAL: " << stocks[4].owned << " shares"
         << "\n  GRAIN: " << stocks[5].owned << " shares\n";
  }
  // Basic board layout
  else if( command == "BOARD"){
    // First line
    cout << "     +                                      -\n";
    // Display each position
    for( int i = 0; i < 6; i++){
      for( int t = 40; t > 0; t--){
        // First part of line
        if( t >= 40){
          // Stocks custom colour
          SetConsoleTextAttribute( hConsole, stocks[i].colour );
          // Name
          cout << stocks[i].name;
        }

        // X represents place on board
        if( stocks[i].pos / 50 == t){
          cout << "X";
        }
        else{
          cout << "=";
        }
        // Newline
        if( t <= 1)
          cout << "\n";
      }
    }
    // Back to default colour
    SetConsoleTextAttribute( hConsole, 0x07 );
  }
  // Roll the dice
  else if( command == "ROLL"){
    // Random stock select
    int stockSelected = random( 0, 5);

    // Amount moved
    int movement = random( -4, 4) * 50;

    // Move it
    stocks[stockSelected].pos += movement;

    // What happened?
    cout << stocks[stockSelected].fullName << " moved " << movement << ".\n";
  }
  else if( command == "EXIT"){
    game_running = false;
  }
}

// Init game
int main(){
  // Initilize
  init();

  // Run game
  while( game_running)
      game();

  return 0;
}
