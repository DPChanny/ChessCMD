#include"MyIOSTREAM.h"
#include"Chess.h"
#include"ConsoleColor.h"

using std::to_string;
using std::abs;
using std::pow;
using std::sqrt;
using MyIOSTREAM::print;
using MyIOSTREAM::println;
using MyIOSTREAM::enter;
using MyIOSTREAM::wait;
using ConsoleColor::set_color;
using ConsoleColor::reset_color;

namespace Chess
{
	//Point

	//x, y ��ġ �Է¿� ���� ������
	Point::Point(int _x, int _y) : x(_x), y(_y)
	{

	}

	//�⺻ ������
	Point::Point() : x(0), y(0)
	{

	}

	//x ���� �Լ�
	int& Point::X()
	{
		return x;
	}

	//y ���� �Լ�
	int& Point::Y()
	{
		return y;
	}

	//������ ���� �ε�
	Point Point::operator+(Point _b)
	{
		return Point(x + _b.x, y + _b.y);
	}

	Point Point::operator*(int _b)
	{
		return Point(x * _b, y * _b);
	}

	Point Point::operator*(Point _b)
	{
		return Point(x * _b.x, y * _b.y);
	}

	Point Point::operator-(Point _b)
	{
		return Point(x - _b.x, y - _b.y);
	}

	bool Point::operator==(Point _b)
	{
		if (x == _b.x && y == _b.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Point::operator!=(Point _b)
	{
		return !(*this == _b);
	} 

	//x, y���� XY_MAX�� �Ѵ��� üũ
	bool Point::check_error()
	{
		if (x > XY_MAX || x < XY_MIN || y > XY_MAX || y < XY_MIN) return true;
		else return false;
	}

	float Point::distance(Point _b)
	{
		int distance_x = abs(x - _b.x);
		int distance_y = abs(y - _b.y);
		
		int a_pow = static_cast<int>(pow(distance_x, 2));
		int b_pow = static_cast<int>(pow(distance_y, 2));
		int c_pow = a_pow + b_pow;

		return static_cast<float>(sqrt(c_pow));
	}

	//string ������ ���ڿ�
	string Point::to_string()
	{
		string result = "(";
		result += std::to_string(x);
		result += ", ";
		result += std::to_string(y);
		result += ")";
		return result;
	}

	//Team

	ChessTeam::ChessTeam(int _team_index) : team_index(_team_index)
	{

	}

	ChessTeam::ChessTeam() : team_index(WHITE_TEAM)
	{

	}

	bool ChessTeam::operator==(ChessTeam _b)
	{
		return (team_index == _b.team_index);
	}

	bool ChessTeam::operator!=(ChessTeam _b)
	{
		return (team_index != _b.team_index);
	}

	int& ChessTeam::Team_Index()
	{
		return team_index;
	}

	string ChessTeam::to_string()
	{
		if (team_index == WHITE_TEAM)
		{
			return "WHITE";
		}
		if (team_index == BLACK_TEAM)
		{
			return "BLACK";
		}
	}

	//ChessPiece

	ChessPiece::ChessPiece(string _name, int _index, ChessTeam _team)
		: name(_name), index(_index), team(_team), position(Point()), is_moved(false), is_dead(false)
	{

	}

	ChessPiece::ChessPiece(string _name, int _index, ChessTeam _team, Point _position)
		: name(_name), index(_index), team(_team), position(_position), is_moved(false), is_dead(false)
	{

	}

	ChessPiece::ChessPiece(string _name, int _index, ChessTeam _team, Point _position, bool _is_moved)
		: name(_name), index(_index), team(_team), position(_position), is_moved(_is_moved), is_dead(false)
	{

	}

	ChessPiece::ChessPiece(string _name, int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead)
		: name(_name), index(_index), team(_team), position(_position), is_moved(_is_moved), is_dead(_is_dead)
	{

	}

	//position ���� �Լ�
	Point& ChessPiece::Position()
	{
		return position;
	}

	//name ���� �Լ�
	string ChessPiece::Name() const
	{
		return name;
	}

	//is_dead ���� �Լ�
	bool& ChessPiece::Is_Dead()
	{
		return is_dead;
	}

	//is_moved ���� �Լ�
	bool& ChessPiece::Is_Moved()
	{
		return is_moved;
	}

	//team ���� �Լ�
	ChessTeam ChessPiece::Team() const
	{
		return team;
	}

	//index ���� �Լ�
	int ChessPiece::Index() const
	{
		return index;
	}

	//�̵� ���� ��ǥ ���
	void ChessPiece::print_available_positions(ChessBoard _chess_board)
	{
		vector<Point> available_points = get_available_position(_chess_board);

		for (int i = 0; i < available_points.size(); i++)
		{
			println(name + "[" + to_string(index) + "] available_points[" + to_string(i) + "]: " + available_points[i].to_string());
		}
	}

	//��ǥ �̵� ���� ����
	bool ChessPiece::is_position_available(ChessBoard _chess_board, Point _position)
	{
		vector<Point> available_positions = get_available_position(_chess_board);
		for (int i = 0; i < available_positions.size(); i++)
		{
			if (available_positions[i] == _position)
			{
				return true;
			}
		}

		return false;
	}

	//���� ���
	void ChessPiece::print_info()
	{
		println(name + "[" + to_string(index) + "] " + team.to_string() + " " + position.to_string() );
		println("is_moved: " + to_string(is_moved));
		println("is_dead: " + to_string(is_dead));
	}

	//�Ѵ� ���
	void ChessPiece::print_all(ChessBoard _chess_board)
	{
		print_info();
		print_available_positions(_chess_board);
	}

	//�̵�
	bool ChessPiece::move_to(Point _position, ChessBoard& _chess_board)
	{
		HistoryNode history_node;
		//��ǥ ������ ���� �ִ���
		if (is_position_available(_chess_board, _position))
		{
			//�⹰ �̵� ���� ����
			history_node.Piece() = this;
			history_node.Last_Position() = Point(position);
			history_node.Last_Is_Moved() = is_moved;

			//��ǥ ������ �� �⹰�� �ִ���
			ChessPiece* _to_go_piece = _chess_board.find_piece_at(_position);
			if (_to_go_piece != FIND_PIECE_FAILURE)
			{
				//��ǥ ������ �⹰�� ���� ������
				if (_to_go_piece->Team() == _chess_board.Current_Team())
				{
					return false;
				}
				_to_go_piece->Is_Dead() = true;

				history_node.Dead_Piece() = _to_go_piece;
			}
			position = _position;
			is_moved = true;

			_chess_board.push_history_node(history_node);

			return true;
		}
		return false;
	}

	//Pawn

	Pawn::Pawn(int _index, ChessTeam _team)
		: ChessPiece(PAWN, _index, _team, Point(), false)
	{

	}

	Pawn::Pawn(int _index, ChessTeam _team, Point _position)
		: ChessPiece(PAWN, _index, _team, _position, false)
	{

	}

	Pawn::Pawn(int _index, ChessTeam _team, Point _position, bool _is_moved)
		: ChessPiece(PAWN, _index, _team, _position, _is_moved)
	{

	}

	Pawn::Pawn(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead)
		: ChessPiece(PAWN, _index, _team, _position, _is_moved, _is_dead)
	{

	}

	//���� �̵� ���� ��ǥ
	vector<Point> Pawn::get_available_position(ChessBoard chess_board)
	{
		int is_reverse = 1;
		if (team.Team_Index())
		{
			is_reverse = -1;
		}
		vector<Point> available_positions;
		Point _position(position.X(), position.Y() + 1 * is_reverse);

		//���� �������� ������
		if (chess_board.find_piece_at(_position) == FIND_PIECE_FAILURE)
		{
			if (!_position.check_error())
			{
				available_positions.push_back(_position);
			}
			if (!is_moved)
			{
				_position = Point(position.X(), position.Y() + 2 * is_reverse);
				if (!position.check_error())
				{
					if (chess_board.find_piece_at(_position) == FIND_PIECE_FAILURE)
					{
						available_positions.push_back(_position);
					}
				}
			}
		}

		ChessPiece* piece_right = chess_board.find_piece_at(position + Point(1, 1 * is_reverse));
		ChessPiece* piece_left = chess_board.find_piece_at(position + Point(-1, 1 * is_reverse));

		//�밢�� �տ� ���� ������ �̵����� ��ġ�� ����
		if (piece_right != FIND_PIECE_FAILURE
			&& piece_right->Team() != team)
		{
			available_positions.push_back(position + Point(1, 1 * is_reverse));
		}
		if (piece_left != FIND_PIECE_FAILURE
			&& piece_left->Team() != team)
		{
			available_positions.push_back(position + Point(-1, 1 * is_reverse));
		}
		return available_positions;
	}

	//Rook

	Rook::Rook(int _index, ChessTeam _team)
		: ChessPiece(ROOK, _index, _team)
	{

	}

	Rook::Rook(int _index, ChessTeam _team, Point _position)
		: ChessPiece(ROOK, _index, _team, _position)
	{

	}

	Rook::Rook(int _index, ChessTeam _team, Point _position, bool _is_moved)
		: ChessPiece(ROOK, _index, _team, _position, _is_moved)
	{

	}

	Rook::Rook(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead)
		: ChessPiece(ROOK, _index, _team, _position, _is_moved, _is_dead)
	{

	}

	void Rook::castling(ChessBoard& _chess_board)
	{
		HistoryNode history_node;

		//�⹰ �̵� ���� ����
		history_node.Piece() = this;
		history_node.Last_Position() = Point(position);
		history_node.Last_Is_Moved() = is_moved;

		if (index == KING_SIDE_ROOK_INDEX)
		{
			position = position + Point(-2, 0);
			is_moved = true;
		}
		if (index == QUEEN_SIDE_ROOK_INDEX)
		{
			position = position + Point(3, 0);
			is_moved = true;
		}

		_chess_board.push_history_node(history_node);
	}

	//���� �̵� ���� ��ǥ
	vector<Point> Rook::get_available_position(ChessBoard _chess_board)
	{
		vector<Point> available_positions;
		//�� ���⿡ ���� 2���� ���� ��
		Point dirs[4] = { Point(1, 0), Point(-1, -0), Point(0, 1), Point(0, -1) };
		for (int i = 0; i < sizeof(dirs) / sizeof(Point); i++)
		{
			for (int j = 0; ; j++)
			{
				Point _position = position + dirs[i] * (j + 1);
				ChessPiece* to_go_piece = _chess_board.find_piece_at(_position);
				if (!_position.check_error())
				{
					if (to_go_piece == FIND_PIECE_FAILURE)
					{
						available_positions.push_back(_position);
					}
					else
					{
						if (to_go_piece->Team() != team)
						{
							available_positions.push_back(_position);
						}
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		return available_positions;
	}

	//Knight

	Knight::Knight(int _index, ChessTeam _team)
		: ChessPiece(KNIGHT, _index, _team, Point(), false)
	{

	}

	Knight::Knight(int _index, ChessTeam _team, Point _position)
		: ChessPiece(KNIGHT, _index, _team, _position, false)
	{

	}

	Knight::Knight(int _index, ChessTeam _team, Point _position, bool _is_moved)
		: ChessPiece(KNIGHT, _index, _team, _position, _is_moved)
	{

	}

	Knight::Knight(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead)
		: ChessPiece(KNIGHT, _index, _team, _position, _is_moved, _is_dead)
	{

	}

	//����Ʈ�� �̵� ���� ��ǥ
	vector<Point> Knight::get_available_position(ChessBoard _chess_board)
	{
		vector<Point> available_positions;
		//�� ���⿡ ���� 2���� ���� ��
		Point dirs[8] = { Point(2, 1), Point(2, -1), Point(-2, 1), Point(-2, -1), Point(1, 2), Point(-1, 2), Point(1, -2), Point(-1, -2) };
		for (int i = 0; i < sizeof(dirs) / sizeof(Point); i++)
		{
			Point _position = position + dirs[i];
			ChessPiece* to_go_piece = _chess_board.find_piece_at(_position);
			if (!_position.check_error())
			{
				if (to_go_piece == FIND_PIECE_FAILURE)
				{
					available_positions.push_back(_position);
				}
				else
				{
					if (to_go_piece->Team() != team)
					{
						available_positions.push_back(_position);
					}
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		return available_positions;
	}

	//Bishop

	Bishop::Bishop(int _index, ChessTeam _team)
		: ChessPiece(BISHOP, _index, _team, Point(), false)
	{

	}

	Bishop::Bishop(int _index, ChessTeam _team, Point _position)
		: ChessPiece(BISHOP, _index, _team, _position, false)
	{

	}

	Bishop::Bishop(int _index, ChessTeam _team, Point _position, bool _is_moved)
		: ChessPiece(BISHOP, _index, _team, _position, _is_moved)
	{

	}

	Bishop::Bishop(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead)
		: ChessPiece(BISHOP, _index, _team, _position, _is_moved, _is_dead)
	{

	}

	//����� �̵� ���� ��ǥ
	vector<Point> Bishop::get_available_position(ChessBoard _chess_board)
	{
		vector<Point> available_positions;
		//�� ���⿡ ���� 2���� ���� ��
		Point dirs[4] = { Point(1, 1), Point(1, -1), Point(-1, 1), Point(-1, -1) };
		for (int i = 0; i < sizeof(dirs) / sizeof(Point); i++)
		{
			for (int j = 0; ; j++)
			{
				Point _position = position + dirs[i] * (j + 1);
				ChessPiece* to_go_piece = _chess_board.find_piece_at(_position);
				if (!_position.check_error())
				{
					if (to_go_piece == FIND_PIECE_FAILURE)
					{
						available_positions.push_back(_position);
					}
					else
					{
						if (to_go_piece->Team() != team)
						{
							available_positions.push_back(_position);
						}
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		return available_positions;
	}

	//Queen

	Queen::Queen(int _index, ChessTeam _team)
		: ChessPiece(QUEEN, _index, _team, Point(), false)
	{

	}

	Queen::Queen(int _index, ChessTeam _team, Point _position)
		: ChessPiece(QUEEN, _index, _team, _position, false)
	{

	}

	Queen::Queen(int _index, ChessTeam _team, Point _position, bool _is_moved)
		: ChessPiece(QUEEN, _index, _team, _position, _is_moved)
	{

	}

	Queen::Queen(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead)
		: ChessPiece(QUEEN, _index, _team, _position, _is_moved, _is_dead)
	{

	}

	//���� �̵� ���� ��ǥ
	vector<Point> Queen::get_available_position(ChessBoard _chess_board)
	{
		vector<Point> available_positions;
		//�� ���⿡ ���� 2���� ���� ��
		Point dirs[8] = { Point(1, 1), Point(1, -1), Point(-1, 1), Point(-1, -1), Point(1, 0), Point(-1, -0), Point(0, 1), Point(0, -1) };
		for (int i = 0; i < sizeof(dirs) / sizeof(Point); i++)
		{
			for (int j = 0; ; j++)
			{
				Point _position = position + dirs[i] * (j + 1);
				ChessPiece* to_go_piece = _chess_board.find_piece_at(_position);
				if (!_position.check_error())
				{
					if (to_go_piece == FIND_PIECE_FAILURE)
					{
						available_positions.push_back(_position);
					}
					else
					{
						if (to_go_piece->Team() != team)
						{
							available_positions.push_back(_position);
						}
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		return available_positions;
	}

	//King	

	King::King(int _index, ChessTeam _team)
		: ChessPiece(KING, _index, _team, Point(), false)
	{

	}

	King::King(int _index, ChessTeam _team, Point _position)
		: ChessPiece(KING, _index, _team, _position, false)
	{

	}

	King::King(int _index, ChessTeam _team, Point _position, bool _is_moved)
		: ChessPiece(KING, _index, _team, _position, _is_moved)
	{

	}

	King::King(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead)
		: ChessPiece(KING, _index, _team, _position, _is_moved, _is_dead)
	{

	}

	//ŷ�� �̵� ���� ��ǥ
	vector<Point> King::get_available_position(ChessBoard _chess_board)
	{
		vector<Point> available_positions;
		//�� ���⿡ ���� 2���� ���� ��
		Point dirs[8] = { Point(1, 1), Point(1, -1), Point(-1, 1), Point(-1, -1), Point(1, 0), Point(-1, -0), Point(0, 1), Point(0, -1) };
		for (int i = 0; i < sizeof(dirs) / sizeof(Point); i++)
		{
			Point _position = position + dirs[i];
			ChessPiece* to_go_piece = _chess_board.find_piece_at(_position);
			if (!_position.check_error())
			{
				if (to_go_piece == FIND_PIECE_FAILURE)
				{
					available_positions.push_back(_position);
				}
				else
				{
					if (to_go_piece->Team() != team)
					{
						available_positions.push_back(_position);
					}
					continue;
				}
			}
			else
			{
				continue;
			}
		}

		//ĳ���� üũ

		Point short_castling[2] = {
			Point(1, 0),
			Point(2, 0),
		};

		Point short_castling_position(2, 0);

		Point long_castling[3] = {
			Point(-1, 0),
			Point(-2, 0),
			Point(-3, 0),
		};

		Point long_castling_position(-2, 0);

		if (is_moved)
		{
			return available_positions;
		}

		if (team == ChessTeam(WHITE_TEAM))
		{
			if (_chess_board.Is_White_Checked())
			{
				return available_positions;
			}
		}
		if (team == ChessTeam(BLACK_TEAM))
		{
			if (_chess_board.Is_Black_Checked())
			{
				return available_positions;
			}
		}

		bool is_short_castling = true;
		bool is_long_castling = true;

		//ŷ���̵� üũ
		for (int i = 0; i < sizeof(short_castling) / sizeof(Point); i++)
		{
			if (_chess_board.find_piece_at(position + short_castling[i]) != FIND_PIECE_FAILURE)
			{
				is_short_castling = false;
				break;
			}
		}

		if (is_short_castling)
		{
			ChessPiece* piece = _chess_board.get_piece(ROOK, KING_SIDE_ROOK_INDEX, team);
			if (piece != FIND_PIECE_FAILURE)
			{
				if (!piece->Is_Moved())
				{
					available_positions.push_back(position + short_castling_position);
				}
			}
		}

		//�����̵� üũ
		for (int i = 0; i < sizeof(long_castling) / sizeof(Point); i++)
		{
			if (_chess_board.find_piece_at(position + long_castling[i]) != FIND_PIECE_FAILURE)
			{
				is_long_castling = false;
				break;
			}
		}

		if (is_long_castling)
		{
			ChessPiece* piece = _chess_board.get_piece(ROOK, QUEEN_SIDE_ROOK_INDEX, team);
			if (piece != FIND_PIECE_FAILURE)
			{
				if (!piece->Is_Moved())
				{
					available_positions.push_back(position + long_castling_position);
				}
			}
		}

		//ĳ���� ��Ģ 4��: ������ ���� ���ݹް� ���� �ʴ� ����

		return available_positions;
	}

	bool King::move_to(Point _position, ChessBoard& _chess_board)
	{
		HistoryNode history_node;
		//��ǥ ������ ���� �ִ���
		if (is_position_available(_chess_board, _position))
		{
			//�⹰ �̵� ���� ����
			history_node.Piece() = this;
			history_node.Last_Position() = Point(position);
			history_node.Last_Is_Moved() = is_moved;

			//��ǥ ������ �� �⹰�� �ִ���
			ChessPiece* _to_go_piece = _chess_board.find_piece_at(_position);
			if (_to_go_piece != FIND_PIECE_FAILURE)
			{
				//��ǥ ������ �⹰�� ���� ������
				if (_to_go_piece->Team() == _chess_board.Current_Team())
				{
					return false;
				}
				_to_go_piece->Is_Dead() = true;

				history_node.Dead_Piece() = _to_go_piece;
			}

			//ĳ������ �ߴٸ�
			if (position.distance(_position) == 2)
			{
				println("castlinged");
				Rook* piece = FIND_PIECE_FAILURE;

				if (position.X() - _position.X() < 0)
				{
					piece = dynamic_cast<Rook*>(_chess_board.get_piece(ROOK, KING_SIDE_ROOK_INDEX, team));
				}
				if (position.X() - _position.X() > 0)
				{
					piece = dynamic_cast<Rook*>(_chess_board.get_piece(ROOK, QUEEN_SIDE_ROOK_INDEX, team));
				}

				if (piece != FIND_PIECE_FAILURE)
				{
					piece->castling(_chess_board);
				}
			}

			position = _position;
			is_moved = true;

			_chess_board.push_history_node(history_node);

			wait();

			return true;
		}
		return false;
	}

	//ChessBoard

	//pieces �޸� ���� �Ҵ� ����
	void ChessBoard::delete_pieces()
	{
		for (int i = 0; i < current_piece; i++)
		{
			delete pieces[i];
		}
		delete[] pieces;
		current_piece = 0;
	}

	//�⹰ �߰�
	void ChessBoard::add_chess_piece(ChessPiece* piece)
	{
		pieces[current_piece] = piece;
		current_piece++;
	}

	//_x, _y ĭ �׸���
	void ChessBoard::print_chess_board_space(int _x, int _y)
	{
		int background_color = CC_ORIGINALBG;
		int color = CC_ORIGINAL;

		if (selected_piece != NONE_PIECE)
		{
			if (selected_piece->Position() == Point(_x, _y))
			{
				background_color = CC_DARKYELLOW;
			}

			if (selected_piece->is_position_available(*this, Point(_x, _y)))
			{
				ChessPiece* piece = find_piece_at(Point(_x, _y));
				if (piece != FIND_PIECE_FAILURE)
				{
					if (piece->Team() != selected_piece->Team())
					{
						background_color = CC_DARKRED;
					}
					else
					{
						background_color = CC_DARKGREEN;
					}
				}
				else
				{
					background_color = CC_DARKGREEN;
				}
			}
		}

		ChessPiece* piece = find_piece_at(Point(_x, _y));
		if (piece != 0)
		{
			string name = piece->Name();
			char first_name = name.front();

			if (piece->Team() == ChessTeam(BLACK_TEAM))
			{
				color = CC_DARKGRAY;
				set_color(color, background_color);
				print(first_name);
			}
			else
			{
				color = CC_WHITE;
				set_color(color, background_color);
				print(first_name);
			}
		}
		else
		{
			set_color(color, background_color);
			print(' ');
		}
		reset_color();
		print(" | ");
	}

	//_y��° �� �׸���
	void ChessBoard::print_chess_board_line(int _y, bool _is_reverse)
	{
		if (_is_reverse)
		{
			print(to_string(_y) + " | ");
			for (int j = XY_MAX; j >= XY_MIN; j--)
			{
				print_chess_board_space(j, _y);
			}
			println(to_string(_y));
			println("   --- --- --- --- --- --- --- --- ");
		}
		else
		{
			print(to_string(_y) + " | ");
			for (int j = XY_MIN; j <= XY_MAX; j++)
			{
				print_chess_board_space(j, _y);
			}
			println(to_string(_y));
			println("   --- --- --- --- --- --- --- --- ");
		}
	}

	ChessBoard::ChessBoard()
	{
		reset();
	}

	//���� ����
	void ChessBoard::reset()
	{
		current_team = ChessTeam(WHITE_TEAM);

		is_white_checked = false;
		is_black_checked = false;

		delete_pieces();

		pieces = new ChessPiece * [CHESS_PIECE_COUNT];

		for (int is_black = 0; is_black < 2; is_black++)
		{
			//�� �ʱ�ȭ
			for (int i = 0; i < 8; i++)
			{
				add_chess_piece(new Pawn(i, ChessTeam(is_black), Point(i, 1 + is_black * 5)));
			}
			//�� �ʱ�ȭ
			for (int i = 0; i < 2; i++)
			{
				add_chess_piece(new Rook(i, ChessTeam(is_black), Point(i * 7, is_black * 7)));
			}
			//����Ʈ �ʱ�ȭ
			for (int i = 0; i < 2; i++)
			{
				add_chess_piece(new Knight(i, ChessTeam(is_black), Point(1 + i * 5, is_black * 7)));
			}
			//��� �ʱ�ȭ
			for (int i = 0; i < 2; i++)
			{
				add_chess_piece(new Bishop(i, ChessTeam(is_black), Point(2 + i * 3, is_black * 7)));
			}
			//�� �ʱ�ȭ
			add_chess_piece(new King(0, ChessTeam(is_black), Point(4, is_black * 7)));
			//ŷ �ʱ�ȭ
			add_chess_piece(new Queen(0, ChessTeam(is_black), Point(3, is_black * 7)));
		}

		while(!history.empty()){
			history.pop();
		}
	}

	//current_team ���� �Լ�
	ChessTeam ChessBoard::Current_Team()
	{
		return current_team;
	}

	//is_white_checked ���� �Լ�
	bool& ChessBoard::Is_White_Checked()
	{
		return is_white_checked;
	}

	//is_black_checked ���� �Լ�
	bool& ChessBoard::Is_Black_Checked()
	{
		return is_black_checked;
	}

	//ü�� �⹰ ����
	void ChessBoard::select_piece(Point _position)
	{
		selected_piece = find_piece_at(_position);;
		if (selected_piece != FIND_PIECE_FAILURE)
		{
			if (selected_piece->Team() != current_team)
			{
				selected_piece = NONE_PIECE;
			}
		}
	}

	//��� ü�� �⹰ ���� ���
	void ChessBoard::print_piece_info()
	{
		for (int i = 0; i < current_piece; i++)
		{
			pieces[i]->print_info();
		}
		wait();
	}

	//ü�� ���� ���
	void ChessBoard::print_chess_board()
	{
		if (current_team == ChessTeam(WHITE_TEAM))
		{
			println("    0   1   2   3   4   5   6   7 ");
			println("   --- --- --- --- --- --- --- --- ");
			for (int i = XY_MAX; i >= XY_MIN; i--)
			{
				print_chess_board_line(i, false);
			}
			println("    0   1   2   3   4   5   6   7 ");
		}
		if (current_team == ChessTeam(BLACK_TEAM))
		{
			println("    7   6   5   4   3   2   1   0 ");
			println("   --- --- --- --- --- --- --- --- ");
			for (int i = XY_MIN; i <= XY_MAX; i++)
			{
				print_chess_board_line(i, true);
			}
			println("    7   6   5   4   3   2   1   0 ");
		}
		enter();
		println("current team: " + current_team.to_string());

		//���� �⹰ ǥ��
		vector<ChessPiece*> dead_pieces = get_dead_pieces();

		enter();
		print("white dead piece: ");

		for (int i = 0; i < dead_pieces.size(); i++)
		{
			if (dead_pieces[i]->Team() == ChessTeam(WHITE_TEAM))
			{
				string name = dead_pieces[i]->Name();
				char first_name = name.front();

				set_color(CC_WHITE, CC_ORIGINALBG);
				print(first_name);
				reset_color();
				print(' ');
			}
			reset_color();
		}

		enter();
		print("black dead piece: ");

		for (int i = 0; i < dead_pieces.size(); i++)
		{
			if (dead_pieces[i]->Team() == ChessTeam(BLACK_TEAM))
			{
				string name = dead_pieces[i]->Name();
				char first_name = name.front();

				set_color(CC_DARKGRAY, CC_ORIGINALBG);
				print(first_name);
				reset_color();
				print(' ');
			}
		}

		enter();
	}

	//�� ��ȯ
	void ChessBoard::reverse_current_team()
	{
		if (current_team == ChessTeam(WHITE_TEAM))
		{
			current_team.Team_Index() = BLACK_TEAM;
		}
		else if (current_team == ChessTeam(BLACK_TEAM))
		{
			current_team.Team_Index() = WHITE_TEAM;
		}
		selected_piece = NONE_PIECE;
	}

	//���� �⹰ ��������
	vector<ChessPiece*> ChessBoard::get_dead_pieces()
	{
		vector<ChessPiece*> dead_pieces;
		
		for (int i = 0; i < current_piece; i++)
		{
			if (pieces[i]->Is_Dead())
			{
				dead_pieces.push_back(pieces[i]);
			}
		}

		return dead_pieces;
	}

	//�⹰ ��������
	ChessPiece* ChessBoard::get_piece(string _name, int _index, ChessTeam _team)
	{
		for (int i = 0; i < current_piece; i++)
		{
			if ((pieces[i]->Name() == _name) && (pieces[i]->Index() == _index) && !(pieces[i]->Is_Dead()) && (pieces[i]->Team() == _team))
			{
				return pieces[i];
			}
		}
		return FIND_PIECE_FAILURE;
	}

	//��ǥ�� �⹰�� �ִ��� Ȯ��
	ChessPiece* ChessBoard::find_piece_at(Point _position)
	{
		for (int i = 0; i < current_piece; i++)
		{
			if (pieces[i]->Position() == _position)
			{
				if (!pieces[i]->Is_Dead())
				{
					return pieces[i];
				}
			}
		}
		return FIND_PIECE_FAILURE;
	}

	//ü�� �⹰�� �̵���Ŵ
	void ChessBoard::move_piece_to(Point _to_go)
	{
		if (selected_piece == NONE_PIECE)
		{
			return;
		}
		//���õ� �⹰�� ���� ���� �⹰����
		if (selected_piece->Team() == current_team)
		{
			if (selected_piece->move_to(_to_go, *this))
			{
				reverse_current_team();
			}
		}
	}

	void ChessBoard::move_piece_to(Point _target_piece_position, Point _to_go)
	{
		ChessPiece* piece = find_piece_at(_target_piece_position);
		if (piece == FIND_PIECE_FAILURE)
		{
			return;
		}

		//���õ� �⹰�� ���� ���� �⹰����
		if (piece->Team() == current_team)
		{
			if (selected_piece->move_to(_to_go, *this))
			{
				reverse_current_team();
			}
		}
	}

	//ü�� �⹰ �̵� ���� �߰�
	void ChessBoard::push_history_node(HistoryNode _history_node)
	{
		history.push(_history_node);
	}

	//�ѹ�
	void ChessBoard::roll_back()
	{
		bool is_castling = false;

		if (history.empty())
		{
			return;
		}

		HistoryNode history_node = history.top();
		history.pop();
		ChessPiece* piece = get_piece(history_node.Piece()->Name(), history_node.Piece()->Index(), history_node.Piece()->Team());

		if (piece->Name() == KING)
		{
			if ((piece->Position()).distance(history_node.Last_Position()) == 2)
			{
				is_castling = true;
			}
		}

		piece->Position() = history_node.Last_Position();
		piece->Is_Moved() = history_node.Last_Is_Moved();

		if (history_node.Dead_Piece() != NULL)
		{
			vector<ChessPiece*> dead_pieces = get_dead_pieces();
			ChessPiece* dead_piece = NULL;
			for (int i = 0; i < dead_pieces.size(); i++)
			{
				if ((dead_pieces[i]->Index() == history_node.Dead_Piece()->Index())
					&& (dead_pieces[i]->Name() == history_node.Dead_Piece()->Name())
					&& (dead_pieces[i]->Team() == history_node.Dead_Piece()->Team()))
				{
					dead_piece = dead_pieces[i];
					break;
				}
			}

			if (dead_piece != NULL)
			{
				dead_piece->Is_Dead() = false;
			}
		}

		if (is_castling)
		{
			roll_back();
		}
		else
		{
			reverse_current_team();
		}
	}

	//HistoryNode

	HistoryNode::HistoryNode() 
		: last_position(Point()),
		last_is_moved(NULL),
		dead_piece(NULL),
		piece(NULL)
	{

	}

	//���� �Լ� ��
	Point& HistoryNode::Last_Position()
	{
		return last_position;
	}

	bool& HistoryNode::Last_Is_Moved()
	{
		return last_is_moved;
	}

	ChessPiece*& HistoryNode::Piece()
	{
		return piece;
	}

	ChessPiece*& HistoryNode::Dead_Piece()
	{
		return dead_piece;
	}
}
