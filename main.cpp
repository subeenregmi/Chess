#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

/*
 * make chess board
 * made pieces and sprites
 * drag and drop pieces
 * created order of moves white, bvl
 *
 * TODO 
 * moves, valid moves of pieces
 * checks checkmates
 * 
 * engine 
 *
 * */

using namespace std;

struct Move{
	int rowChange;
	int columnChange;
};

class Piece{
	private:
		string type;
		bool isWhite;
		bool hasMovedOnce;
		sf::Sprite* sprite;
	public:
		Move* possibleMoves[100];

		string getType(){
			return type;
		}
		bool getColour(){
			return isWhite;
		}
		sf::Sprite* getSprite(){
			return sprite;
		}
		void setSprite(sf::Sprite* S){
			sprite = S;	
		}
		void addMove(int rowChange, int colChange){
			Move* M = new Move;
			M->rowChange = rowChange;	
			M->columnChange = colChange;	
			possibleMoves[findFreeIndex()] = M;
		}
		int findFreeIndex(){
			for(int i=0; i<100; i++){
				if(possibleMoves[i] == nullptr){
					return i; 
				}
			}
			return -1;
		}
		void freeMoves(){
			int count = 0;
			for(int i=0; i<100; i++){
				if(possibleMoves[i] != nullptr){
					delete possibleMoves[i];
					count++;
				}
			}
			cout << "Deleted " << count << " moves" << endl;
		}
		void setMovedOnce(){
			hasMovedOnce = true;
		}
		void setMoveOnceBack(){
			hasMovedOnce = false;
		}
		bool getMovedOnceState(){
			return hasMovedOnce;
		}

		Piece(string T, bool C){
			type = T;
			isWhite = C;
			hasMovedOnce = false;
			sprite = nullptr;
			for(int i=0; i<100; i++){
				possibleMoves[i] = nullptr;	
			}
		}
};

class Square{
	private:
		bool PieceInSquare;
		Piece* pPiece;
	public:
		bool isSquareOccupied(){
			return PieceInSquare;
		}

		void setPiece(Piece* P){
			pPiece = P;
			if(P == nullptr){
				PieceInSquare = false;
			}
			else{
				PieceInSquare = true;
			}
		}

		Piece* getPieceInSquare(){
			return pPiece;
		}
		void removePiece(){
			pPiece = nullptr;
			PieceInSquare=false;
		}
		Square(){
			PieceInSquare = false;
			pPiece = nullptr;
		}
};

class Game{

	private:
		string whitePieces[8] = {"rook", "knight","bishop","queen","king","bishop","knight","rook"};
		string blackPieces[8] = {"rook", "knight","bishop","queen","king","bishop","knight","rook"};
		int CurrentPlayer;
	public:
		Square Board[8][8];
		
		void makeBoard(){
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					Square S;
					Board[i][j] = S;
				}
			}
			createPieces();
		}
		
		void createPieces(){
			// White Pieces, pawns
			for(int i=0; i<8; i++){
				Piece* P = new Piece("pawn", true);
				Board[i][6].setPiece(P);

				// white pawn move create
				P->addMove(0, -1);
				P->addMove(0, -2);
				P->addMove(1, -1);
				P->addMove(-1, -1);

				Piece* D = new Piece(whitePieces[i], true);
				Board[i][7].setPiece(D);
				
				// rook moves create
				if(whitePieces[i] == "rook"){
					for(int i=-7; i<8; i++){
						D->addMove(i, 0);
						D->addMove(0, i);
					}
				}
				// bishop moves
				if(whitePieces[i] == "bishop"){
					for(int i=-7; i<8; i++){
						D->addMove(i, i);
						D->addMove(i, -i);
						D->addMove(-i, i);
					}
				}

				// knight moves
				if(whitePieces[i] == "knight"){
					D->addMove(2, 1);
					D->addMove(2, -1);
					D->addMove(1, 2);
					D->addMove(1, -2);
					D->addMove(-1, -2);
					D->addMove(-2, 1);
					D->addMove(-2, -1);
					D->addMove(-1, 2);
				}

				// Queen moves
				if(whitePieces[i] == "queen"){
					for(int i=-7; i<8; i++){
						D->addMove(0, i);
						D->addMove(i, 0);
						D->addMove(i, i);
						D->addMove(i, -i);
						D->addMove(-i, i);
					}
				}

				//King moves
				if(whitePieces[i] == "king"){
					D->addMove(1, 0);
					D->addMove(-1, 0);
					D->addMove(0, 1);
					D->addMove(0, -1);
					D->addMove(1, 1);
					D->addMove(1, -1);
					D->addMove(-1, 1);
					D->addMove(-1, -1);
				}

				Piece* Q = new Piece(blackPieces[i], false);
				Board[i][0].setPiece(Q);

				if(blackPieces[i] == "rook"){
					for(int i=-7; i<8; i++){
						Q->addMove(i, 0);
						Q->addMove(0, i);
					}
				}

				// bishop moves
				if(blackPieces[i] == "bishop"){
					for(int i=-7; i<8; i++){
						Q->addMove(i, i);
						Q->addMove(i, -i);
						Q->addMove(-i, i);
					}
				}

				// knight moves
				if(blackPieces[i] == "knight"){
					Q->addMove(2, 1);
					Q->addMove(2, -1);
					Q->addMove(1, 2);
					Q->addMove(1, -2);
					Q->addMove(-1, -2);
					Q->addMove(-2, 1);
					Q->addMove(-2, -1);
					Q->addMove(-1, 2);
				}

				// Queen moves
				if(blackPieces[i] == "queen"){
					for(int i=-7; i<8; i++){
						Q->addMove(0, i);
						Q->addMove(i, 0);
						Q->addMove(i, i);
						Q->addMove(i, -i);
						Q->addMove(-i, i);
					}
				}

				//King moves
				if(blackPieces[i] == "king"){
					Q->addMove(1, 0);
					Q->addMove(-1, 0);
					Q->addMove(0, 1);
					Q->addMove(0, -1);
					Q->addMove(1, 1);
					Q->addMove(1, -1);
					Q->addMove(-1, 1);
					Q->addMove(-1, -1);
				}
				Piece* R = new Piece("pawn", false);
				Board[i][1].setPiece(R);

				// black pawn move create
				R->addMove(0, 1);
				R->addMove(0, 2);
				R->addMove(1, 1);
				R->addMove(-1, 1);
			}
		}

		// Function that take mouse coordinates and turns it into square
		Square* turnMouseCoordsToSquare(int x, int y){
			if(x/116 > 7 || x/116 < 0 || y/116 > 7 || y/116 < 0){
				return nullptr;
			}
			return &Board[x/116][y/116];
		}

		void turnMouseCoordsToBoard(int x, int y){
			cout << x/116 << ", " << y/116 << endl;
		}

		int getCurrentPlayer(){
			return CurrentPlayer;
		}

		void incrimentCurrentPlayer(){
			CurrentPlayer++;
			CurrentPlayer %= 2;
		}

		int findPiece(string type, int colour){
			bool white = false;
			if(colour == 1){
				white = true;	
			}
			int position = -1;
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					if(Board[i][j].getPieceInSquare() == nullptr){
						continue;
					}
					if(Board[i][j].getPieceInSquare()->getType() == type  && Board[i][j].getPieceInSquare()->getColour() == white){
						position = i*10 + j;
						return position;
					}
				}
			}
			return position;	
		}

		bool isInCheck(){
			bool white = false;
			if(CurrentPlayer == 1){
				white = true;
			}
			if(findPiece("king", CurrentPlayer) == -1){
				return false;
			}
			int EnemyKing[2] = {findPiece("king", CurrentPlayer) / 10, findPiece("king", CurrentPlayer) % 10};
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					int CurrentPos[2] = {i, j};
					if(Board[i][j].getPieceInSquare() == nullptr){
						continue;
					}
					if(Board[i][j].getPieceInSquare()->getColour() == white){
						continue;
					}
					if(isValidMove(CurrentPos, EnemyKing, Board[i][j].getPieceInSquare())){
						return true;
					}
				}
			}
			return false;
		}

		bool wouldBeInCheck(int startIndex[2], int finishIndex[2]){
			Piece* P1 = Board[startIndex[0]][startIndex[1]].getPieceInSquare();
			Piece* P2 = Board[finishIndex[0]][finishIndex[1]].getPieceInSquare();

			Board[startIndex[0]][startIndex[1]].setPiece(nullptr);
			Board[finishIndex[0]][finishIndex[1]].setPiece(P1);

			bool Check = isInCheck();

			Board[startIndex[0]][startIndex[1]].setPiece(P1);
			Board[finishIndex[0]][finishIndex[1]].setPiece(P2);

			return Check;
		}

		bool isInCheckMate(){
			bool white = false;
			if(!isInCheck()){
				cout << "R1" << endl;
				return false;	
			}
			if(CurrentPlayer == 1){
				white = true;
			}
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					int startIndex[2] = {i, j};
					if(Board[i][j].getPieceInSquare() == nullptr){
						continue;
					}
					if(Board[i][j].getPieceInSquare()->getColour() != white){
						continue;
					}
					for(int k=0; k<8; k++){
						for(int h=0; h<8; h++){
							int finishIndex[2] = {k, h};
							if(!isValidMove(startIndex, finishIndex, Board[i][j].getPieceInSquare())){
								continue;
							}
							if(!wouldBeInCheck(startIndex, finishIndex)){
								cout << startIndex[0] << startIndex[1] << endl;
								cout << Board[startIndex[0]][startIndex[1]].getPieceInSquare()->getType() << endl;
								cout << finishIndex[0] << finishIndex[1] << endl;
								cout << "R2" << endl;
								return false;
							}
						}
					}
				}
			}
			return true;
		}

		bool isValidMove(int startIndex[2], int finishIndex[2], Piece* P){
			for(int i=0; i<2; i++){
				if(startIndex[i] > 7 || startIndex[i] < 0 || finishIndex[i] > 7 || finishIndex[i] < 0){
					cout << "Out of range" << endl;
					return false;
				}
			}
			
			if (Board[finishIndex[0]][finishIndex[1]].getPieceInSquare() != nullptr){
				if(Board[startIndex[0]][startIndex[1]].getPieceInSquare()->getColour() == Board[finishIndex[0]][finishIndex[1]].getPieceInSquare()->getColour()){
					return false;
				}
			}

			for(int i=0; i<100; i++){
				Move* M = P->possibleMoves[i];
				if(M == nullptr){
					continue;
				}
				if((M->rowChange + startIndex[0] == finishIndex[0]) && M->columnChange + startIndex[1] == finishIndex[1]){
					
					// Pawn Rules 
					if(P->getType() == "pawn"){
						// Pawn double advance rule
						if(M->columnChange == -2 || M->columnChange == 2){
							if(Board[finishIndex[0]][finishIndex[1]].getPieceInSquare() != nullptr){
								return false;
							}
							if(Board[finishIndex[0]][finishIndex[1] - M->columnChange/2].getPieceInSquare() != nullptr){
								return false;	
							}	
							if(!P->getMovedOnceState()){
								if(wouldBeInCheck(startIndex, finishIndex)){
									return false;
								}	
								return true;
							}
							continue;
						}

						// Pawn capture rule
						if(M->rowChange == 1 || M->rowChange == -1){
							if(Board[finishIndex[0]][finishIndex[1]].getPieceInSquare() == nullptr){
								return false;
							}
							else{
								if(wouldBeInCheck(startIndex, finishIndex)){
									return false;
								}	
								return true;	
							}
						}

						if(M->columnChange == 1 || M->columnChange == -1){
							if(Board[finishIndex[0]][finishIndex[1]].getPieceInSquare() != nullptr){
								return false;
							}
							if(wouldBeInCheck(startIndex, finishIndex)){
								return false;
							}	
							return true;
						}
					}

					if(P->getType() == "knight"){
						if(wouldBeInCheck(startIndex, finishIndex)){
							return false;
						}	
						return true;
					}

					int rowC = M->rowChange;
					int colC = M->columnChange;
					int rowMultiplier = 1;
					int colMultiplier = 1;

					if(rowC < 0){
						rowC *= -1;
						rowMultiplier = -1;
					}
					if(colC < 0){
						colC *= -1;
						colMultiplier = -1;
					}

					int CurrentIndex[2] = {startIndex[0], startIndex[1]};
					bool validRouteFound = true;

					for(int i=0; i<rowC-1; i++){
						CurrentIndex[0] += 1 * rowMultiplier;
						if(Board[CurrentIndex[0]][CurrentIndex[1]].getPieceInSquare() != nullptr){
							validRouteFound = false;	
						}
					}

					for(int i=0; i<colC-1; i++){
						CurrentIndex[1] += 1 * colMultiplier;
						if(Board[CurrentIndex[0]][CurrentIndex[1]].getPieceInSquare() != nullptr){
							validRouteFound = false;	
						}
					}
					
					if(P->getType() == "bishop" || P->getType() == "queen" && (rowC == colC)){
						validRouteFound = true;
						CurrentIndex[0] = startIndex[0];
						CurrentIndex[1] = startIndex[1];
						for(int i=0; i<rowC-1; i++){
							CurrentIndex[0] += 1 * rowMultiplier;
							CurrentIndex[1] += 1 * colMultiplier;
							if(Board[CurrentIndex[0]][CurrentIndex[1]].getPieceInSquare() != nullptr){
								validRouteFound = false;	
							}
						}
					}
					if(wouldBeInCheck(startIndex, finishIndex)){
						continue;
					}
					if(validRouteFound){

						return true;
					}
				}
			}
			return false;
		}

		void drawBoard(sf::RenderWindow* window, sf::Texture* TBoard, sf::Texture* TPieces){
			float  sf_S = 1.55f;
			float  sf_P = 0.75f;
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					sf::Sprite BoardSquare;
					BoardSquare.setTexture(*TBoard);
					BoardSquare.setTextureRect(sf::IntRect(648, 114 , 69, 69));
					BoardSquare.scale(sf::Vector2f(sf_S, sf_S));
					BoardSquare.setPosition(sf::Vector2f(75*i*sf_S, 75*j*sf_S));
					if((i+j) % 2 != 0){
						BoardSquare.setColor(sf::Color(255, 255, 255, 175));
					}
					window->draw(BoardSquare);
					drawPieces(window, TBoard, TPieces);
				}
			}
		}
		
		void drawValidMoves(sf::RenderWindow* window, sf::Texture* TCircle, Square* viewedSquare, int Index[2]){
			bool notMovedOnce = false;
			if(viewedSquare != nullptr){
				for(int i=0; i<8; i++){
					for(int j=0; j<8; j++){
						sf::Sprite S;
						S.setTexture(*TCircle);
						S.setScale(sf::Vector2f(0.03f, 0.03f));
						S.setColor(sf::Color(0, 0, 0, 128));
						int D[2] = {i, j};
						if(isValidMove(Index, D, viewedSquare->getPieceInSquare())){
							if(Board[i][j].getPieceInSquare() != nullptr){
								if(Board[i][j].getPieceInSquare()->getColour() == viewedSquare->getPieceInSquare()->getColour()){
									continue;
								}
							}

							if(notMovedOnce){
								viewedSquare->getPieceInSquare()->setMoveOnceBack();
							}

							S.setPosition(sf::Vector2f(117*i +30, 117*j + 40));
							window->draw(S);
						}
					}
				}
			}
		}

		void drawPromotionMenu(sf::RenderWindow* window, sf::Texture* TPieces, sf::Texture* TRectangle){

			int multiplier = 0;
			if(CurrentPlayer == 1){
				multiplier = 1;
			}
			sf::Sprite sprite;
			sprite.setTexture(*TRectangle);	
			sprite.scale(sf::Vector2f(2.5f, 1.0f));
			sprite.setPosition(sf::Vector2f(85.0f, 310.0f));
			sprite.setColor(sf::Color(0, 0, 0, 64));
			window->draw(sprite);
			for(int i=1; i<5; i++){
				sf::Sprite sp;
				sp.setTexture(*TPieces);
				sp.setTextureRect(sf::IntRect(133*i, 133*multiplier, 133, 133));
				sp.setPosition(sf::Vector2f(150*i, 400.0f));
				sp.scale(sf::Vector2f(1.05f, 1.05f));
				window->draw(sp);
			}
		}

		void drawPieces(sf::RenderWindow* window, sf::Texture* TBoard, sf::Texture* TPieces){
			float  sf_S = 1.55f;
			float  sf_P = 0.75f;
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					if(Board[i][j].isSquareOccupied()){
						int colour_sf = 1;
						int multiplier = 0;
						string type = Board[i][j].getPieceInSquare()->getType();
						if(Board[i][j].getPieceInSquare()->getColour()){
							colour_sf = 0;	
						}
						if(type == "king"){
							multiplier = 0;
						}
						if(type == "queen"){
							multiplier = 1;
						}
						if(type == "bishop"){
							multiplier = 2;
						}
						if(type == "knight"){
							multiplier = 3;
						}
						if(type == "rook"){
							multiplier = 4;
						}
						if(type == "pawn"){
							multiplier = 5;
						}
						if(Board[i][j].getPieceInSquare()->getSprite() == nullptr){
							sf::Sprite* Piece = new sf::Sprite;
							Board[i][j].getPieceInSquare()->setSprite(Piece);
							Piece->setTexture(*TPieces);
							Piece->setTextureRect(sf::IntRect(133*multiplier, 133*colour_sf, 133, 133));
							Piece->scale(sf::Vector2f(sf_P, sf_P));
							Piece->setPosition(sf::Vector2f(117*i + 45,117*j + 40));
							Piece->setOrigin(sf::Vector2f(165*sf_P/2, 133*sf_P/2));
							window->draw(*Piece);
						}
						else{
							window->draw(*Board[i][j].getPieceInSquare()->getSprite());
						}
					}
				}
			}
		}

		Game(){
			CurrentPlayer = 1;
		}

		~Game(){
			int count = 0;
			cout << "Deconstructor..." << endl;
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					if(Board[i][j].isSquareOccupied()){
						if(Board[i][j].getPieceInSquare() != nullptr){
							cout << "Removing " << Board[i][j].getPieceInSquare()->getType() << ", and its sprite" << endl;
							Board[i][j].getPieceInSquare()->freeMoves();
							delete Board[i][j].getPieceInSquare()->getSprite();
							delete Board[i][j].getPieceInSquare();
							count++;
						}
					}
				}
			}
			cout << "Deleted, " << count;
		}
};

int main()
{	
	Piece* PieceHeldDown = nullptr;
	Square* SquareStart = nullptr;
	Square* LastPiecePressed = nullptr;
	Square* PromotionSquare = nullptr;
	
	int LastIndex[2] = {-1, -1};
	int Index[2] = {0, 0};

	bool promotionMenu = false;
	bool promotionCapture = false;

	sf::RenderWindow window(sf::VideoMode(800, 1080), "Chess");

	sf::Texture BoardT;
	sf::Texture ChessPiecesT;
	sf::Texture CircleT;
	sf::Texture RectangleT;

	ChessPiecesT.loadFromFile("textures/chess_pieces.png");
	BoardT.loadFromFile("textures/more.png");
	CircleT.loadFromFile("textures/greycircle.png");
	RectangleT.loadFromFile("textures/greyrectangle.png");

	ChessPiecesT.setSmooth(true);
	CircleT.setSmooth(true);
	RectangleT.setSmooth(true);

	sf::SoundBuffer ChessPieceMove;
	sf::SoundBuffer ChessPieceCapture;
	sf::SoundBuffer ChessCheck;
	sf::SoundBuffer Checkmate;
	sf::SoundBuffer Promotion;

	sf::Sound pieceMoveSound;
	sf::Sound pieceCaptureSound;
	sf::Sound kingCheck;
	sf::Sound checkMateSound;
	sf::Sound promotionSound; 

	ChessPieceMove.loadFromFile("audio/move-self.wav");
	ChessPieceCapture.loadFromFile("audio/capture.wav");
	ChessCheck.loadFromFile("audio/move-check.wav");
	Checkmate.loadFromFile("audio/checkmate.wav");
	Promotion.loadFromFile("audio/promotion.wav");

	pieceMoveSound.setBuffer(ChessPieceMove);
	pieceCaptureSound.setBuffer(ChessPieceCapture);
	kingCheck.setBuffer(ChessCheck);
	checkMateSound.setBuffer(Checkmate);
	promotionSound.setBuffer(Promotion);

	Game G;
	G.makeBoard();
	while (window.isOpen()){

		sf::Event event;

		window.clear();

		G.drawBoard(&window, &BoardT, &ChessPiecesT);

		if(promotionMenu){
			G.drawPromotionMenu(&window, &ChessPiecesT, &RectangleT);
		}
		
		G.drawValidMoves(&window, &CircleT, LastPiecePressed, LastIndex);

		window.display();

		while(window.pollEvent(event)){
			
			if(event.type == sf::Event::Closed){
				window.close();
			}

			if(promotionMenu){

				int ColourM = (G.getCurrentPlayer() + 1) % 2;
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

					int x = ((sf::Mouse::getPosition(window).x - 150) / 150 )  % 4;
					Piece* P1 = PromotionSquare->getPieceInSquare();
					P1->freeMoves();
					delete P1->getSprite();
					delete P1;

					if(x == 0){
						Piece* P = new Piece("queen", ColourM);		
						
						for(int i=-7; i<8; i++){
							P->addMove(0, i);
							P->addMove(i, 0);
							P->addMove(i, i);
							P->addMove(i, -i);
							P->addMove(-i, i);
						}
						PromotionSquare->setPiece(P);
					}

					else if(x == 1){
						Piece* P = new Piece("bishop", ColourM);		
						
						for(int i=-7; i<8; i++){
							P->addMove(i, i);
							P->addMove(i, -i);
							P->addMove(-i, i);
						}
						PromotionSquare->setPiece(P);
					}

					else if(x == 2){
						Piece* P = new Piece("knight", ColourM);		

						P->addMove(2, 1);
						P->addMove(2, -1);
						P->addMove(1, 2);
						P->addMove(1, -2);
						P->addMove(-1, -2);
						P->addMove(-2, 1);
						P->addMove(-2, -1);
						P->addMove(-1, 2);
						
						PromotionSquare->setPiece(P);
					}

					else if(x == 3){
						Piece* P = new Piece("rook", ColourM);		

						for(int i=-7; i<8; i++){
							P->addMove(i, 0);
							P->addMove(0, i);
						}

						PromotionSquare->setPiece(P);
					}

					if(G.isInCheckMate()){
						checkMateSound.play();
					}
					else if(G.isInCheck()){
						kingCheck.play();
					}
					else{
						promotionSound.play();
					}

					PromotionSquare = nullptr;
					promotionMenu = false;
				}
	
				continue;
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				if(PieceHeldDown == nullptr){
					Square* S = G.turnMouseCoordsToSquare(x, y);
					if(S == nullptr){
						continue;
					}
					if(S->getPieceInSquare() == nullptr){
						continue;
					}
					//check colour
					if(!((G.getCurrentPlayer() == 1 && S->getPieceInSquare()->getColour() == true) || (G.getCurrentPlayer() == 0 && S->getPieceInSquare()->getColour() == false))){
						continue;
					}

					PieceHeldDown = S->getPieceInSquare();
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(x, y));
					SquareStart = S;
					LastPiecePressed = S;
					LastIndex[0] = x / 116;
					LastIndex[1] = y / 116;
					Index[0] = x;
					Index[1] = y;
				}
				else{
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(x, y));
				}
			}

			if(event.type == sf::Event::MouseButtonReleased){
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				Square* S = G.turnMouseCoordsToSquare(x, y);	
				if(PieceHeldDown == nullptr){
					continue;
				}
				if(SquareStart == nullptr || SquareStart->getPieceInSquare() == nullptr){
					continue;
				}
				if(S == nullptr){
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(Index[0]/116) + 45, 117*(Index[1]/116) + 40));	
					PieceHeldDown = nullptr;
					SquareStart = nullptr;
					Index[0] = 0;
					Index[1] = 0;
					continue;	
				}
				if(PieceHeldDown == S->getPieceInSquare()){
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(Index[0]/116) + 45, 117*(Index[1]/116) + 40));	
					PieceHeldDown = nullptr;
					SquareStart = nullptr;
					Index[0] = 0;
					Index[1] = 0;
					continue;
				}

				int StartIndex[2] = {Index[0]/116, Index[1]/116};
				int FinishIndex[2] = {x/116, y/116};

				if(!G.isValidMove(StartIndex, FinishIndex, PieceHeldDown)){
					cout << "Invalid Move" << endl;
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(Index[0]/116) + 45, 117*(Index[1]/116) + 40));	
					PieceHeldDown = nullptr;
					SquareStart = nullptr;
					Index[0] = 0;
					Index[1] = 0;
					continue;
				}

				bool capture = false;
				if(S->getPieceInSquare() != nullptr){
					cout << "Deleting, " << S->getPieceInSquare()->getType() << endl;
					S->getPieceInSquare()->freeMoves();
					delete S->getPieceInSquare()->getSprite();
					delete S->getPieceInSquare();
					capture = true;
					S->removePiece();
				}

				PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(x/116) + 45, 117*(y/116) + 40));	
				S->setPiece(PieceHeldDown);
				SquareStart->removePiece(); 
				
				//promotion 
				
				if(PieceHeldDown->getType() == "pawn"){
					if(FinishIndex[1] == 0 || FinishIndex[1] == 7){
						promotionMenu = true;
						PromotionSquare = S;
					}
				}

				G.incrimentCurrentPlayer();
				
				if(G.isInCheckMate()){
					checkMateSound.play();
				}
				else if(G.isInCheck()){
					kingCheck.play();
				}
				else if(capture){
					pieceCaptureSound.play();
				}
				else{
					pieceMoveSound.play();	
				}
				if(PieceHeldDown->getType() == "pawn"){
					PieceHeldDown->setMovedOnce();
				}

				PieceHeldDown = nullptr;
				SquareStart = nullptr;
				Index[0] = 0;
				Index[1] = 0;
				LastPiecePressed = nullptr;
				LastIndex[0] = -1;
				LastIndex[1] = -1;
			}
		}
	}
	return 0;
}
