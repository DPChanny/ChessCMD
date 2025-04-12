#ifndef CHESS_H
#define CHESS_H

#include<string>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<stack>

using std::string;
using std::vector;
using std::stack;

#define WHITE_TEAM 0
#define BLACK_TEAM 1

#define XY_MAX 7
#define XY_MIN 0

#define PAWN "PAWN"
#define ROOK "ROOK"
#define KNIGHT "KNIGHT"
#define BISHOP "BISHOP"
#define QUEEN "QUEEN"
#define KING "KING"

#define CHESS_PIECE_COUNT 32
#define FIND_PIECE_FAILURE 0
#define NONE_PIECE 0

#define KING_SIDE_ROOK_INDEX 1
#define QUEEN_SIDE_ROOK_INDEX 0

namespace Chess
{
	class Point;
	class ChessTeam;
	class ChessPiece;
	class Pawn;
	class Rook;
	class Knight;
	class Bishop;
	class Queen;
	class King;
	class ChessBoard;
	class HistoryNode;

	/* ü���ǿ����� ��ǥ
	 * �̶� (0, 0)�� ü���ǿ����� ���ʾƷ� */
	class Point
	{
		int x;
		int y;

	public:
		//x, y ��ġ �Է¿� ���� ������
		Point(int _x, int _y);

		//�⺻ ������
		Point();

		//x ���� �Լ�
		int& X();

		//y ���� �Լ�
		int& Y();

		//������ ���� �ε�
		Point operator+(Point _b);

		Point operator*(int _b);

		Point operator*(Point _b);

		Point operator-(Point _b);

		bool operator==(Point _b);

		bool operator!=(Point _b);

		//x, y ���� XY_MAX�� �Ѵ��� üũ
		bool check_error();

		//_b���� �Ÿ�
		float distance(Point _b);

		//string ������ ���ڿ�
		string to_string();
	};

	class ChessTeam
	{
		int team_index;

	public:
		ChessTeam();

		ChessTeam(int _team_index);

		//������ �����ε�
		bool operator==(ChessTeam _b);

		bool operator!=(ChessTeam _b);

		//team_index ���� �Լ�
		int& Team_Index();

		//���� ���� string�� ����
		string to_string();
	};

	//�⹰ �̵� ����
	class HistoryNode
	{
		//���� ��ġ
		Point last_position;

		//�̵��� �⹰
		ChessPiece* piece;

		//���� is_moved
		bool last_is_moved;

		//�� �̵����� ���� ���� �⹰ ����
		ChessPiece* dead_piece;

	public:
		HistoryNode();

		//���� �Լ� ��
		Point& Last_Position();

		bool& Last_Is_Moved();

		ChessPiece*& Piece();

		ChessPiece*& Dead_Piece();
	};

	// ü���⹰���� ���̽� Ŭ����
	class ChessPiece
	{
	protected:
		//�⹰�� �̸� ROOK, QUEEN, KING, BISHOP ���
		string name;
		//���� �������� �⹰�� �����ҽ� �����ϱ����� index
		int index;
		ChessTeam team;
		//���� ��ġ
		Point position;
		//�̹� ������������ ���� ����
		bool is_moved;
		//�̹� �׾������� ���� ����
		bool is_dead;

	public:
		ChessPiece(string _name, int _index, ChessTeam _team);

		ChessPiece(string _name, int _index, ChessTeam _team, Point _position);

		ChessPiece(string _name, int _index, ChessTeam _team, Point _position, bool _is_moved);

		ChessPiece(string _name, int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//position ���� �Լ�
		Point& Position();

		//name ���� �Լ�
		string Name() const;

		//is_dead ���� �Լ�
		bool& Is_Dead();

		//is_moved ���� �Լ�
		bool& Is_Moved();

		//team ���� �Լ�
		ChessTeam Team() const;

		//index ���� �Լ�
		int Index() const;

		//�̵� ���� ��ǥ
		virtual vector<Point> get_available_position(ChessBoard _chess_board) = 0;

		//�̵� ���� ��ǥ ���
		void print_available_positions(ChessBoard _chess_board);

		//��ǥ �̵� ���� ����
		bool is_position_available(ChessBoard _chess_board, Point position);

		//���� ���
		void print_info();

		//�Ѵ� ���
		void print_all(ChessBoard _chess_board);

		//�̵�
		virtual bool move_to(Point _position, ChessBoard& _chess_board);
	};

	// �� Ŭ����
	class Pawn : public ChessPiece
	{
	public:
		Pawn(int _index, ChessTeam _team);

		Pawn(int _index, ChessTeam _team, Point _position);

		Pawn(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Pawn(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//���� �̵� ���� ��ǥ
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//�� Ŭ����
	class Rook : public ChessPiece
	{
	public:
		Rook(int _index, ChessTeam _team);

		Rook(int _index, ChessTeam _team, Point _position);

		Rook(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Rook(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		void castling(ChessBoard& _chess_board);

		//���� �̵� ���� ��ǥ
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//����Ʈ Ŭ����
	class Knight : public ChessPiece
	{
	public:
		Knight(int _index, ChessTeam _team);

		Knight(int _index, ChessTeam _team, Point _position);

		Knight(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Knight(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//����Ʈ�� �̵� ���� ��ǥ
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//��� Ŭ����
	class Bishop : public ChessPiece
	{
	public:
		Bishop(int _index, ChessTeam _team);

		Bishop(int _index, ChessTeam _team, Point _position);

		Bishop(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Bishop(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//����� �̵� ���� ��ǥ
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//�� Ŭ����
	class Queen : public ChessPiece
	{
	public:
		Queen(int _index, ChessTeam _team);

		Queen(int _index, ChessTeam _team, Point _position);

		Queen(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Queen(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//���� �̵� ���� ��ǥ
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//ŷ Ŭ����
	class King : public ChessPiece
	{
	public:
		King(int _index, ChessTeam _team);

		King(int _index, ChessTeam _team, Point _position);

		King(int _index, ChessTeam _team, Point _position, bool _is_moved);

		King(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//ŷ�� �̵� ���� ��ǥ
		vector<Point> get_available_position(ChessBoard chess_board) override;

		//ŷ�� ���� ������ �Լ�(ĳ���� ����)
		bool move_to(Point _position, ChessBoard& _chess_board) override;
	};

	//������
	class ChessBoard
	{
		//�������� �⹰��
		ChessPiece** pieces;
		//���� ��ϵ� �⹰��
		int current_piece = 0;
		//���� ��
		ChessTeam current_team;
		//���� ���õ� �⹰
		ChessPiece* selected_piece;
		bool is_white_checked;
		bool is_black_checked;
		stack<HistoryNode> history;

		//pieces �޸� ���� �Ҵ� ����
		void delete_pieces();

		//�⹰ �߰�
		void add_chess_piece(ChessPiece* piece);

		void print_chess_board_space(int _x, int _y);

		//_index��° �� �׸���
		void print_chess_board_line(int _y, bool _is_reverse);

	public:
		ChessBoard();

		//current_team ���� �Լ�
		ChessTeam Current_Team();

		//is_white_checked ���� �Լ�
		bool& Is_White_Checked();

		//is_black_checked ���� �Լ�
		bool& Is_Black_Checked();

		//���� ����
		void reset();

		//ü�� �⹰ ����
		void select_piece(Point _position);

		//��� ü�� �⹰ ���� ���
		void print_piece_info();

		//ü�� ���� ���
		void print_chess_board();

		//�� ��ȯ
		void reverse_current_team();

		//���� �⹰ ��������
		vector<ChessPiece*> get_dead_pieces();

		//�⹰ ��������
		ChessPiece* get_piece(string _name, int _index, ChessTeam _team);

		//��ǥ�� �⹰�� �ִ��� Ȯ��
		ChessPiece* find_piece_at(Point _position);

		//ü�� �⹰�� �̵���Ŵ
		void move_piece_to(Point _to_go); 
		void move_piece_to(Point _target_piece_position, Point _to_go);

		//�⹰ �̵� ���� ���ÿ� �߰�
		void push_history_node(HistoryNode _history_node);

		//�ѹ�
		void roll_back();
	};
}

#endif