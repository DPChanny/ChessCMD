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

	/* 체스판에서의 좌표
	 * 이때 (0, 0)은 체스판에서의 왼쪽아래 */
	class Point
	{
		int x;
		int y;

	public:
		//x, y 위치 입력에 따른 생성자
		Point(int _x, int _y);

		//기본 생성자
		Point();

		//x 접근 함수
		int& X();

		//y 접근 함수
		int& Y();

		//연산자 오버 로딩
		Point operator+(Point _b);

		Point operator*(int _b);

		Point operator*(Point _b);

		Point operator-(Point _b);

		bool operator==(Point _b);

		bool operator!=(Point _b);

		//x, y 값이 XY_MAX를 넘는지 체크
		bool check_error();

		//_b와의 거리
		float distance(Point _b);

		//string 형태의 문자열
		string to_string();
	};

	class ChessTeam
	{
		int team_index;

	public:
		ChessTeam();

		ChessTeam(int _team_index);

		//연산자 오버로드
		bool operator==(ChessTeam _b);

		bool operator!=(ChessTeam _b);

		//team_index 접근 함수
		int& Team_Index();

		//현재 팀의 string을 리턴
		string to_string();
	};

	//기물 이동 정보
	class HistoryNode
	{
		//원래 위치
		Point last_position;

		//이동한 기물
		ChessPiece* piece;

		//원래 is_moved
		bool last_is_moved;

		//이 이동으로 인해 죽은 기물 정보
		ChessPiece* dead_piece;

	public:
		HistoryNode();

		//접근 함수 들
		Point& Last_Position();

		bool& Last_Is_Moved();

		ChessPiece*& Piece();

		ChessPiece*& Dead_Piece();
	};

	// 체스기물들의 베이스 클래스
	class ChessPiece
	{
	protected:
		//기물의 이름 ROOK, QUEEN, KING, BISHOP 등등
		string name;
		//같은 여러개의 기물이 공존할시 구분하기위한 index
		int index;
		ChessTeam team;
		//현재 위치
		Point position;
		//이미 움직였는지에 대한 여부
		bool is_moved;
		//이미 죽었는지에 대한 여부
		bool is_dead;

	public:
		ChessPiece(string _name, int _index, ChessTeam _team);

		ChessPiece(string _name, int _index, ChessTeam _team, Point _position);

		ChessPiece(string _name, int _index, ChessTeam _team, Point _position, bool _is_moved);

		ChessPiece(string _name, int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//position 접근 함수
		Point& Position();

		//name 접근 함수
		string Name() const;

		//is_dead 접근 함수
		bool& Is_Dead();

		//is_moved 접근 함수
		bool& Is_Moved();

		//team 접근 함수
		ChessTeam Team() const;

		//index 접근 함수
		int Index() const;

		//이동 가능 좌표
		virtual vector<Point> get_available_position(ChessBoard _chess_board) = 0;

		//이동 가능 좌표 출력
		void print_available_positions(ChessBoard _chess_board);

		//좌표 이동 가능 여부
		bool is_position_available(ChessBoard _chess_board, Point position);

		//정보 출력
		void print_info();

		//둘다 출력
		void print_all(ChessBoard _chess_board);

		//이동
		virtual bool move_to(Point _position, ChessBoard& _chess_board);
	};

	// 폰 클래스
	class Pawn : public ChessPiece
	{
	public:
		Pawn(int _index, ChessTeam _team);

		Pawn(int _index, ChessTeam _team, Point _position);

		Pawn(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Pawn(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//폰의 이동 가능 좌표
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//룩 클래스
	class Rook : public ChessPiece
	{
	public:
		Rook(int _index, ChessTeam _team);

		Rook(int _index, ChessTeam _team, Point _position);

		Rook(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Rook(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		void castling(ChessBoard& _chess_board);

		//룩의 이동 가능 좌표
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//나이트 클래스
	class Knight : public ChessPiece
	{
	public:
		Knight(int _index, ChessTeam _team);

		Knight(int _index, ChessTeam _team, Point _position);

		Knight(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Knight(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//나이트의 이동 가능 좌표
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//비숍 클래스
	class Bishop : public ChessPiece
	{
	public:
		Bishop(int _index, ChessTeam _team);

		Bishop(int _index, ChessTeam _team, Point _position);

		Bishop(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Bishop(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//비숍의 이동 가능 좌표
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//퀸 클래스
	class Queen : public ChessPiece
	{
	public:
		Queen(int _index, ChessTeam _team);

		Queen(int _index, ChessTeam _team, Point _position);

		Queen(int _index, ChessTeam _team, Point _position, bool _is_moved);

		Queen(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//퀸의 이동 가능 좌표
		vector<Point> get_available_position(ChessBoard chess_board) override;
	};

	//킹 클래스
	class King : public ChessPiece
	{
	public:
		King(int _index, ChessTeam _team);

		King(int _index, ChessTeam _team, Point _position);

		King(int _index, ChessTeam _team, Point _position, bool _is_moved);

		King(int _index, ChessTeam _team, Point _position, bool _is_moved, bool _is_dead);

		//킹의 이동 가능 좌표
		vector<Point> get_available_position(ChessBoard chess_board) override;

		//킹의 전용 움직임 함수(캐슬링 지원)
		bool move_to(Point _position, ChessBoard& _chess_board) override;
	};

	//보드판
	class ChessBoard
	{
		//보드판의 기물들
		ChessPiece** pieces;
		//현재 등록된 기물들
		int current_piece = 0;
		//현재 팀
		ChessTeam current_team;
		//현재 선택된 기물
		ChessPiece* selected_piece;
		bool is_white_checked;
		bool is_black_checked;
		stack<HistoryNode> history;

		//pieces 메모리 동적 할당 해제
		void delete_pieces();

		//기물 추가
		void add_chess_piece(ChessPiece* piece);

		void print_chess_board_space(int _x, int _y);

		//_index번째 줄 그리기
		void print_chess_board_line(int _y, bool _is_reverse);

	public:
		ChessBoard();

		//current_team 접근 함수
		ChessTeam Current_Team();

		//is_white_checked 접근 함수
		bool& Is_White_Checked();

		//is_black_checked 접근 함수
		bool& Is_Black_Checked();

		//보드 리셋
		void reset();

		//체스 기물 선택
		void select_piece(Point _position);

		//모든 체스 기물 정보 출력
		void print_piece_info();

		//체스 보드 출력
		void print_chess_board();

		//팀 변환
		void reverse_current_team();

		//죽은 기물 가져오기
		vector<ChessPiece*> get_dead_pieces();

		//기물 가져오기
		ChessPiece* get_piece(string _name, int _index, ChessTeam _team);

		//좌표에 기물이 있는지 확인
		ChessPiece* find_piece_at(Point _position);

		//체스 기물을 이동시킴
		void move_piece_to(Point _to_go); 
		void move_piece_to(Point _target_piece_position, Point _to_go);

		//기물 이동 정보 스택에 추가
		void push_history_node(HistoryNode _history_node);

		//롤백
		void roll_back();
	};
}

#endif