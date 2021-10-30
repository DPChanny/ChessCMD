#include"Chess.h"
#include"MyIOSTREAM.h"

using MyIOSTREAM::get;
using MyIOSTREAM::print;
using MyIOSTREAM::println;
using MyIOSTREAM::clear;
using MyIOSTREAM::enter;
using MyIOSTREAM::comfirm;
using Chess::ChessBoard;
using Chess::Point;

void move(ChessBoard& chess_board)
{
	Point to_go_position;
	get("x", to_go_position.X());
	get("y", to_go_position.Y());
	chess_board.move_piece_to(to_go_position);
}

void select(ChessBoard& chess_board)
{
	Point target_position;
	get("target x", target_position.X());
	get("target y", target_position.Y());
	chess_board.select_piece(target_position);
}

int main()
{
	ChessBoard chess_board;

	while (true)
	{
		clear();
		chess_board.print_chess_board();

		int selection = 0;

		enter();
		println("What to do?");
		println("1: select");
		println("2: move");
		println("3: skip");
		println("4: roll back");
		println("5: reset");
		println("6: exit");

		get("Answer", selection);

		switch (selection)
		{
		case 1:
			select(chess_board);
			break;
		case 2:
			move(chess_board);
			break;
		case 3:
			chess_board.reverse_current_team();
			break;
		case 4:
			chess_board.roll_back();
			break;
		case 5:
			if (comfirm("Are you sure to reset?"))
			{
				chess_board.reset();
			}
			break;

		}

		if (selection == 6)
		{
			if (comfirm("Are you sure to exit?"))
			{
				break;
			}
		}
	}

	print("bye!");
}

