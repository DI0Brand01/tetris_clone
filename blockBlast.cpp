// created on 27-Sep-2024_04-36-31-PM
#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
using namespace std;

enum enDir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
enum enShapes
{
	square,
	bigSquare,
	LShape,
	dot,
	Tshape,
	longPiece,
};
struct stPoint
{
	size_t x;
	size_t y;
	stPoint(size_t x = 0, size_t y = 0)
	{
		this->x = x;
		this->y = y;
	}
};
void resetBoard(short **, stPoint);
void drawBoard(short **, stPoint);
enShapes returnRandomShapeType();
short **saveBoard(short **, short, short);

class Shape
{
public:
	int shapeSize;
	stPoint shapeHead;
	enDir shapeDir;
	vector<stPoint> points;
	enShapes shapeType;
	Shape(size_t initX, size_t initY, enShapes sh)
	{
		shapeDir = enDir::UP;
		shapeHead.x = initX;
		shapeHead.y = initY;
		shapeType = sh;
		points.push_back(stPoint(initX, initY));
		switch (sh)
		{
		case enShapes::square:
		{

			points.push_back(stPoint(initX, initY + 1));
			points.push_back(stPoint(initX + 1, initY));
			points.push_back(stPoint(initX + 1, initY + 1));
		}
		break;
		case enShapes::bigSquare:
		{

			points.push_back(stPoint(initX, initY + 1));
			points.push_back(stPoint(initX, initY + 2));
			points.push_back(stPoint(initX + 1, initY));
			points.push_back(stPoint(initX + 1, initY + 1));
			points.push_back(stPoint(initX + 1, initY + 2));
			points.push_back(stPoint(initX + 2, initY));
			points.push_back(stPoint(initX + 2, initY + 1));
			points.push_back(stPoint(initX + 2, initY + 2));
		}
		break;
		case enShapes::LShape:
		{

			points.push_back(stPoint(initX + 1, initY));
			points.push_back(stPoint(initX + 2, initY));
			points.push_back(stPoint(initX + 2, initY + 1));
		}
		break;
		case enShapes::Tshape:
		{

			points.push_back(stPoint(initX + 1, initY - 1));
			points.push_back(stPoint(initX + 1, initY));
			points.push_back(stPoint(initX + 1, initY + 1));
		}
		break;
		case enShapes::longPiece:
		{

			points.push_back(stPoint(initX + 1, initY));
			points.push_back(stPoint(initX + 2, initY));
			points.push_back(stPoint(initX + 3, initY));
		}
		break;
		default:
			break;
		}
	}
	void move(enDir dir, short **board, stPoint boardSize)
	{
		vector<stPoint> distPos = this->points;
		short xInc{}, yInc{};
		switch (dir)
		{
		case enDir::LEFT:
			xInc = 0;
			yInc = -1;
			break;
		case enDir::RIGHT:
			xInc = 0;
			yInc = 1;
			break;
		case enDir::UP:
			xInc = -1;
			yInc = 0;
			break;
		case enDir::DOWN:
			xInc = 1;
			yInc = 0;
			break;
		default:
			break;
		}
		shapeHead.x += xInc;
		shapeHead.y += yInc;
		for (stPoint &p : this->points)
			board[p.x][p.y] = 0;
		for (stPoint &p : distPos)
		{
			p.x += xInc;
			p.y += yInc;
		}
		if (canBeDrawn(distPos, board, boardSize))
			this->points = distPos;
	}

	static bool canBeDrawn(vector<stPoint> points, short **board, stPoint boardSize)
	{

		for (stPoint &p : points)
		{
			if (p.x < 0 || p.y < 0 || p.x >= boardSize.x || p.y >= boardSize.y || board[p.x][p.y] != 0)
			{
				return false;
			}
		}
		return true;
	}
	static void drawShape(Shape &sh, short **board, stPoint boardSize)
	{
		for (stPoint &p : sh.points)
			board[p.x][p.y] = 1;
		board[5][5] = 6;
	}

	static void rotateShape(Shape &sh)
	{

		switch (sh.shapeDir)
		{
		case enDir::UP:
			sh.shapeDir = enDir::DOWN;

			break;

		case enDir::DOWN:
			/* code */
			sh.shapeDir = enDir::LEFT;
			break;
		case enDir::LEFT:
			sh.shapeDir = enDir::RIGHT;
			/* code */
			break;
		case enDir::RIGHT:
			/* code */
			sh.shapeDir = enDir::UP;
			break;
		}
	}
};

void resetBoard(short **board, stPoint boardSize)
{
	for (int i = 0; i < boardSize.x; i++)
	{
		for (int j = 0; j < boardSize.y; j++)
		{
			board[i][j] = 0;
		}
	}
}

void drawBoard(short **board, stPoint boardSize)
{
	// Define a single space as the filler to make the board look more square
	const string filler = " "; // Filler used for empty cells, narrower to balance

	// Draw top border
	cout << char(201); // ╔
	for (int j = 0; j < boardSize.y; j++)
		cout << char(205) << char(205); // Double width for the border ══
	cout << char(187) << endl;			// ╗

	// Draw board rows with vertical borders
	for (int i = 0; i < boardSize.x; i++)
	{
		cout << char(186); // ║
		for (int j = 0; j < boardSize.y; j++)
		{
			// // Print block if the position matches, otherwise print filler twice to maintain spacing
			// if (i == blockPos[0] && j == blockPos[1])
			// 	cout << 0 << filler; // Block character followed by filler to keep spacing
			// else
			// 	cout << filler << filler; // Two fillers to maintain cell size
			if (board[i][j])
				cout << board[i][j] << filler;
			else
				cout << filler << filler;
		}
		cout << char(186) << endl; // ║
	}

	// Draw bottom border
	cout << char(200); // ╚
	for (int j = 0; j < boardSize.y; j++)
		cout << char(205) << char(205); // Double width for the border ══
	cout << char(188) << endl;			// ╝
}

enShapes returnRandomShapeType()
{
	vector<enShapes> allShapes;
	allShapes.push_back(square);
	allShapes.push_back(bigSquare);
	allShapes.push_back(LShape);
	allShapes.push_back(dot);
	allShapes.push_back(Tshape);
	allShapes.push_back(longPiece);
	return allShapes.at(rand() % allShapes.size());
}

short **saveBoard(short **board, short boardRows, short boardCols)
{
	short **newBoard = new short *[boardRows];
	for (int i = 0; i < boardRows; i++)
	{
		newBoard[i] = new short[boardCols];
	}
	resetBoard(newBoard, stPoint(boardRows, boardCols));
	for (int i = 0; i < boardRows; i++)
	{
		for (int j = 0; j < boardCols; j++)
		{
			newBoard[i][j] = board[i][j];
		}
	}
	return newBoard;
}

int main()
{
	srand(time(0));
	const short boardRows = 20;
	const short boardCols = 20;
	short **board = new short *[boardRows];
	for (int i = 0; i < boardRows; i++)
	{
		board[i] = new short[boardCols];
	}
	resetBoard(board, stPoint(boardRows, boardCols));

	board[5][5] = 6;
	enShapes shapeType = returnRandomShapeType();
	Shape shape(boardRows / 2, boardCols / 2, shapeType);
	enDir dir;
	int ch;
	do
	{

		// ------------------- input ----------------
		ch = _getch();
		if (ch == 0 || ch == 224)
			ch = _getch(); // Get the next character (actual key code)
		system("cls");

		// ------------------- movement ----------------
		if (ch == 72)
		{
			dir = enDir::UP;
		}
		else if (ch == 80) // down
		{
			dir = enDir::DOWN;
		}
		else if (ch == 75)
		{
			dir = enDir::LEFT;
		}
		else if (ch == 77)
		{
			dir = enDir::RIGHT;
		}
		else if (ch == 13)
		{
			board = saveBoard(board, boardRows, boardCols);
			shape = Shape(0, boardCols / 2, returnRandomShapeType());
		}
		// apply position
		shape.move(dir, board, stPoint(boardRows, boardCols));
		Shape::drawShape(shape, board, stPoint(boardRows, boardCols));

		// ------------------- draw ----------------

		drawBoard(board, stPoint(boardRows, boardCols));
		string dirOutput = "";
		switch (dir)
		{
		case UP:
			dirOutput = "Up";
			break;
		case DOWN:
			dirOutput = "Down";
			break;
		case LEFT:
			dirOutput = "Left";
			break;
		case RIGHT:
			dirOutput = "Right";
			break;

		default:
			break;
		}
		cout << "dir = " << dirOutput << endl;
		// for (stPoint &p : shape.points)
		// 	cout << p.x << ", " << p.y << endl;
	} while (ch != 113);
	return 0;
}