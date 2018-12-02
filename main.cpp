#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <sstream>
#include <stdlib.h>

const int NUMBER_STOCKS = 6;
const int NUMBER_SPACES = 40;

// Stores command values
std::string command = "";

// Game running? (for exit)
bool game_running = true;

// Your money
int money;

// Stock Positions
struct stock{
  int pos;
  int owned;
  int colour;
  std::string name;
  std::string shortName;
  std::string fullName;
}stocks[6];

// Settinsg
bool showBoard = true;

// Windows Stuff for colours
HANDLE  hConsole;

// Random number generator. Use int random(lowest,highest);
int random(int newLowest, int newHighest){
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}

//Convert int to string
std::string convertIntToString(int number){
  std::stringstream ss;
  ss << number;
  return ss.str();
}

//Convert string to int
int convertStringToInt(std::string newString){
  int result;
  std::stringstream(newString) >> result;
  return result;
}

// Check if string is int
inline bool isInteger(const std::string & s){
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    return false;

  char * p;
  strtol(s.c_str(), &p, 10);

  return (*p == 0);
}

// Init
void init(){
  // New random generator
  srand( time(NULL));

  // Windows stuff
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // Welcome message
  std::cout << "Welcome to stock ticker v1.07!\n\n Use HELP to get started\n";

  // Init stocks
  for( int i = 0; i < NUMBER_STOCKS; i ++){
    stocks[i].pos = 1000;
    stocks[i].owned = 0;

    // Stock colours
    switch (i){
      case 0:
        stocks[i].colour = 0x06;
        stocks[i].name = "GLD. ";
        stocks[i].shortName = "gld";
        stocks[i].fullName = "GOLD";
        break;
      case 1:
        stocks[i].colour = 0x0F;
        stocks[i].name = "SIL. ";
        stocks[i].shortName = "sil";
        stocks[i].fullName = "SILVER";
        break;
      case 2:
        stocks[i].colour = 0x0C;
        stocks[i].shortName = "oil";
        stocks[i].name = "OIL. ";
        stocks[i].fullName = "OIL";
        break;
      case 3:
        stocks[i].colour = 0x0A;
        stocks[i].shortName = "bnd";
        stocks[i].name = "BND. ";
        stocks[i].fullName = "BONDS";
        break;
      case 4:
        stocks[i].colour = 0x0D;
        stocks[i].name = "IND. ";
        stocks[i].shortName = "ind";
        stocks[i].fullName = "INDUSTRIAL";
        break;
      case 5:
        stocks[i].colour = 0x0E;
        stocks[i].name = "GRA. ";
        stocks[i].shortName = "gra";
        stocks[i].fullName = "GRAIN";
        break;
      default:
        stocks[i].colour = 0x07;
        stocks[i].name = "NNE.";
        stocks[i].shortName = "non";
        stocks[i].fullName = "NONE";
        break;
    }

  }

  // Start money
  money = 5000;
}

// Draw board
void draw_board(){
  // First line
  std::cout << "     +                                      -\n";
  // Display each position
  for( int i = 0; i < NUMBER_STOCKS; i++){
    for( int t = NUMBER_SPACES; t > 0; t--){
      // First part of line
      if( t >= NUMBER_SPACES){
        // Stocks custom colour
        SetConsoleTextAttribute( hConsole, stocks[i].colour );
        // Name
        std::cout << stocks[i].name;
      }

      // X represents place on board
      if( stocks[i].pos / 50 == t){
        std::cout << "X";
      }
      else{
        std::cout << "=";
      }
      // Divider
      if( t == NUMBER_SPACES/2 + 1)
        std::cout << "|";
      // Newline
      if( t == 1)
        std::cout << "\n";
    }
  }
  // Back to default colour
  SetConsoleTextAttribute( hConsole, 0x07 );
}

// Main game
void game(){
  // Get a command
  std::cin >> command;

  // Clear console after command
  system("cls");

  // Message every time round
  std::cout << "STOCK TICKER: type HELP for commands\n\n";

  // Check command
  if( command == "HELP" || command == "help"){
    std::cout << "HELP:displays the help menu\n"
              << "BUY: Buys the specified amount of the specified stock\n"
              << "SELL: Sells the specified amount of the specified stock\n"
              << "STOCKS: Lists available stocks and the values\n"
              << "INV: View all money and stocks you own\n"
              << "BOARD: View game board visual\n"
              << "ROLL: Rolls the dice (ends turn)\n"
              << "SETTINGS: Change settings \n\n"
              << "TIP: Use the up arrow to access last command. \n Also, enter commands separated by spaces to enter multiple. \n For example, in they buy menu, when buying 1000 \n shares of gold instead of doing \n BUY [enter] 1 [enter] 1 [enter], \n you can simply do BUY 1 1 [ENTER].\n";
  }
  else if( command == "BUY" || command == "buy"){
    // Store number
    std::string command_int_s = "";
    std::string command_int2_s = "";
    int command_int = 0;
    int command_int2 = 0;

    std::cout << "What would you like to buy? (number value) You have $" << money
              << "\n 1." << stocks[0].fullName << "(" << stocks[0].owned << ") $" << stocks[0].pos
              << "\n 2." << stocks[1].fullName << "(" << stocks[1].owned << ") $" << stocks[1].pos
              << "\n 3." << stocks[2].fullName << "(" << stocks[2].owned << ") $" << stocks[2].pos
              << "\n 4." << stocks[3].fullName << "(" << stocks[3].owned << ") $" << stocks[3].pos
              << "\n 5." << stocks[4].fullName << "(" << stocks[4].owned << ") $" << stocks[4].pos
              << "\n 6." << stocks[5].fullName << "(" << stocks[5].owned << ") $" << stocks[5].pos << "\n";
    std::cin >> command_int_s;

    std::cout << "Ok, how many shares (in 1000's)?:\n";
    std::cin >> command_int2_s;

    // Validate
    if( isInteger(command_int_s) && isInteger(command_int2_s)){
      command_int = convertStringToInt(command_int_s);
      command_int2 = convertStringToInt(command_int2_s);

      // Check moneys
      command_int --;
      if( stocks[command_int].pos * command_int2 <= money){
        money -= stocks[command_int].pos * command_int2;
        stocks[command_int].owned += command_int2;
        std::cout << command_int2 * 1000 << " shares bought\n";
      }
      else{
        std::cout << "\nNot enought money to buy " << command_int2 * 1000 << " shares.\n";
      }
    }
    else{
      std::cout << "Only use numbers.\n";
    }
  }
  else if( command == "SELL" || command == "sell"){
    // Store number
    std::string command_int_s = "";
    std::string command_int2_s = "";
    int command_int = 0;
    int command_int2 = 0;

    std::cout << "What would you like to sell? (number value) You have $" << money
              << "\n 1." << stocks[0].fullName << "(" << stocks[0].owned << ") $" << stocks[0].pos
              << "\n 2." << stocks[1].fullName << "(" << stocks[1].owned << ") $" << stocks[1].pos
              << "\n 3." << stocks[2].fullName << "(" << stocks[2].owned << ") $" << stocks[2].pos
              << "\n 4." << stocks[3].fullName << "(" << stocks[3].owned << ") $" << stocks[3].pos
              << "\n 5." << stocks[4].fullName << "(" << stocks[4].owned << ") $" << stocks[4].pos
              << "\n 6." << stocks[5].fullName << "(" << stocks[5].owned << ") $" << stocks[5].pos << "\n";
    std::cin >> command_int_s;

    std::cout << "Ok, how many shares? (in 1000's):\n";
    std::cin >> command_int2_s;

    // Validate
    if( isInteger(command_int_s) && isInteger(command_int2_s)){
      command_int = convertStringToInt(command_int_s);
      command_int2 = convertStringToInt(command_int2_s);

      // Check moneys
      command_int --;
      if( command_int2 <= stocks[command_int].owned){
        money += stocks[command_int].pos * command_int2;
        stocks[command_int].owned -= command_int2;
        std::cout << command_int2 * 1000 << " shares sold\n";
      }
      else{
        std::cout << "\nNot enought stocks to sell " << command_int2 * 1000 << " shares.\n";
      }
    }
    else{
      std::cout << "Only use numbers.\n";
    }
  }
  // Stock Prices
  else if( command == "STOCKS" || command == "stocks"){
    std::cout << "Prices:\n"
              << " GOLD: $" << stocks[0].pos << "\n"
              << " SILVER: $" << stocks[1].pos << "\n"
              << " OIL: $" << stocks[2].pos << "\n"
              << " BONDS: $" << stocks[3].pos << "\n"
              << " INDUSTRIAL: $" << stocks[4].pos << "\n"
              << " GRAIN: $" << stocks[5].pos << "\n";
  }
  // Views stocks and money
  else if( command == "INV" || command == "inv"){
    std::cout << "You have $" << money
              << "\n GOLD: " << stocks[0].owned << " shares"
              << "\n SILVER: " << stocks[1].owned << " shares"
              << "\n OIL: " << stocks[2].owned << " shares"
              << "\n BONDS: " << stocks[3].owned << " shares"
              << "\n INDUSTRIAL: " << stocks[4].owned << " shares"
              << "\n GRAIN: " << stocks[5].owned << " shares\n";
  }
  // Basic board layout
  else if( command == "BOARD" || command == "board"){
    // We got a seperate function for that
    draw_board();
  }
  // Roll the dice
  else if( command == "ROLL" || command == "roll"){
    // Output string
    std::string rollOutput = "";

    // DIE 1
    // Random stock select
    int dieStock = random( 0, 5);
    rollOutput += stocks[dieStock].fullName;

    // DIE 2
    // Command 0 = div, 1 = up, 2 = down
    int dieCommand = random( 0, 2);

    // DIE 3
    // Number
    int dieAmount = random( 1, 4);

    // Commands
    switch (dieCommand){
      // Pay dividends
      case 0:{
        if( stocks[dieStock].pos > 1000){
          // Calc money made
          int divAmount = (dieAmount * 50) * stocks[dieStock].owned;
          money += divAmount;
          rollOutput += " DIV %" + convertIntToString(dieAmount * 5) + ".\n";
          rollOutput += " $" + convertIntToString(divAmount) + " added to your inventory";
        }
        else{
          rollOutput += " is under par, could not pay dividends.";
        }
        break;
      }
      // Move up
      case 1:
        stocks[dieStock].pos += dieAmount * 50;
        rollOutput += " UP " + convertIntToString(dieAmount * 50);

        // Off track
        if( stocks[dieStock].pos >= 2000){
          stocks[dieStock].pos = 1000;
          rollOutput += " and SPLIT. You get " + convertIntToString(stocks[dieStock].owned) + " free shares :D";
          stocks[dieStock].owned *= 2;
        }
        break;
      // Move down
      case 2:
        stocks[dieStock].pos -= dieAmount * 50;
        rollOutput += " DOWN " + convertIntToString(dieAmount * 50);

        // Off track
        if( stocks[dieStock].pos <= 0){
          stocks[dieStock].pos = 1000;
          rollOutput += " and CRASHES. You lose " + convertIntToString(stocks[dieStock].owned) + " shares :(";
          stocks[dieStock].owned = 0;
        }
        break;
      default:
        break;
    }

    // Show board if needed
    if( showBoard)
      draw_board();

    // What happened?
    std::cout << rollOutput << ".\n";
  }
  // Toggle settings
  else if( command == "SETTINGS" || command == "settings"){
    // Available toggles
    int command_int = 0;

    std::cout << "1. Toggle showing board after each roll (" << showBoard << ")\n";
    std::cin >> command_int;

    // Setting to change
    switch (command_int){
      case 1:
        showBoard = !showBoard;
        std::cout << "Show board toggled!\n";
        break;
      default:
        std::cout << "Not a valid option. Try again.\n";
        break;
    }
  }
  else if( command == "SWAG" || command == "swag"){
    std::cout << "'''''''''''+++@@@@@@+++@@@@@@@++''''''''\n'''''''''''+++@@@@@@+++@@@@@@@++''''''''\n''''''''@@@@@@@+++++++++++++@@@@@@''''''\n''''''@@@@++++++++++++++++++++++@@@@''''\n''''@@@++++++++++++++++++++++++++++@''''\n''''@@@++++++++++++++++++++++++++++@''''\n'''@@@+++++++++++++++++++++++++++++@@@@'\n''@@++++++++++++++++++++++++++++++++++@@\n@@@++++++++++++'++.........'+++++++++++@\n@@@++++++++++++'++.........'+++++++++++@\n@@'++++++++++++.............++++++++++++\n'''+++++++++''................,+####++++\n''++++#++++'..................,+####++++\n''++++#++++'..................,+####++++\n++++++++''''...................+++####++\n++++##++'''....................,++#####+\n++++++++'''.....................+++#####\n++++++++'''.....................+++#####\n++++++++''................#####.+++#####\n##++++++''..............###.....,,++####\n++++++++''.............###.   ..,,++####\n++++++++''.............###.   ..,,++####\n++++++++...#######....,...'@   ...,++++#\n++++++++..##..  ......,...    ....,+++++\n++++++++....''@   ....,,..........,+++++\n++++++++....''@   ....,,..........,+++++\n++++++++....    .......,...........#++++\n++++++++...............,,,.........#++++\n++++++++++..............,,.........#++++\n++++++++++..............,,.........#++++\n++++++++++..............,,,........#++++\n++++++++##............,...,.......,###++\n++++++++##+............,,,........,###++\n++++++++##+............,,,........,###++\n++++++++++#.......................##++++\n++++++++++##..........''''''....,,##++++\n++++++++++##.......'''''........,,##++++\n++++++++++##.......'''''........,,##++++\n++++++++##+###.................,++##++++\n++++++++####++................,;####++++\n++++++++++++##+.............,,;+###+++++\n++++++++++++##+.............,,;+###+++++\n++++++'++++++++:...........,::;+###+++++\n+++++++++++++++;::........,:::++###+++++\n++++++++++++++++..::::::::::##++##+###++\n++++++++++++++++..::::::::::##++##+###++\n++++''++##++++++..........,,,,++###+++++\n++++''++##+++++#...........,,,++++++++++\n++++++++++++++++...........,,,:+++++++++\n++++++++++++++++...........,,,:+++++++++\n++++++++++++++++##.........,,,,+++++++++\n''+++++++++++++###..........,,,:++++++++\n++++++++++++++#####...........,,,,++++++\n++++++++++++++#####...........,,,,++++++\n";
  }
  else if( command == "EXIT" || command == "exit"){
    game_running = false;
  }
  else{
    std::cout << command << " is not a valid command. Use HELP to view available commands.\n";
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
