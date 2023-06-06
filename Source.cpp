/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

extern bool onOffSound;

std::string boardFormat(const std::string& r) {
	std::string ret = "";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			ret.push_back(r[i * SIZE + j]);
			ret.push_back(' ');
		}
		ret.push_back('\n');
	}
	return ret;
}

void main()
{
	srand(time_t(NULL));
	onOffSound = true;
	board game = board();

	system("start chessGraphics.exe");
	Sleep(1000);

	Pipe p;
	bool isConnect = p.connect();
	
	string ans;

	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	bool player = false;
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	//strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1"); // just example...
	strcpy_s(msgToGraphics, (game.convertToString()+'0').c_str());
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	std::cout << board::convertPositionType(board::convertPositionType(msgFromGraphics)) << endl;


	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		Point src = board::convertPositionType(msgFromGraphics); //the check for en-passent
		Point dst = board::convertPositionType(std::string() + msgFromGraphics[2] + msgFromGraphics[3]);
		// YOUR CODE
		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation

		/******* JUST FOR EREZ DEBUGGING ******/
		msgToGraphics[0] = (char)(game.canMovePiece(src, dst, player, nullptr) + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/


		if ((msgToGraphics[0] == '0') || (msgToGraphics[0] == '1'))
		{
			player = !player;
			if ((msgToGraphics[0] == '1') && !game.checkIfMovesExist(player)) {
				msgToGraphics[0] = '8';
				playSound(checkMate);
			}
			else if (msgToGraphics[0] == '1') {
				playSound(check);
			}
			std::cout << boardFormat(game.convertToString()) << std::endl;
		}

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		try {
			// get message from graphics
			msgFromGraphics = p.getMessageFromGraphics();
		}
		catch (...) {
			msgFromGraphics = "quit";
		}
	}

	p.close();
}