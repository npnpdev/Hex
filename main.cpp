// Autor: Igor Tomkowicz

#include <iostream>
#include "constants.h"

int board_size(string board){
    int fields = 0;

    for(int i=0; i<board.length(); i++){
        if(board[i]=='<'){
            fields++;
        }
    }

    return sqrt(fields);
}

int countPlayerPawns(char board[MAX_SIZE][MAX_SIZE], int size, char player){
    int pawns = 0;

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(board[i][j]==player){
                pawns++;
            }
        }
    }
    return pawns;
}

bool is_board_correct(char board[][MAX_SIZE],int size){
    int player1 = 0;
    int player2 = 0;

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(board[i][j]==redPlayer){
                player1++;
            }

            if(board[i][j]==bluePlayer){
                player2++;
            }
        }
    }

    if(player1==player2){
        return true;
    }

    if(player1==player2+1){
        return true;
    }

    return false;
}

void createBoard(string sBoard, char board[][MAX_SIZE]) {
    int line = 0;
    int field = 0;

    for (int i = 0; i < sBoard.length(); i++) {
        if (sBoard[i] == '\n') {
            field = 0;
            line++;
        }
        if (sBoard[i] == redPlayer || sBoard[i] == bluePlayer) {
            board[line][field] = sBoard[i];
        }
        if(sBoard[i]=='>'){
            field++;
        }
    }
}

void getLeftRedCorner(char board[MAX_SIZE][MAX_SIZE], int size, vector<pair<int, int>>& corner){
    corner.clear();

    for(int i=0; i<size; i++){
        if(board[i][0]==redPlayer){
            corner.emplace_back(i, 0);
        }
    }
}

void getLeftBlueCorner(char board[MAX_SIZE][MAX_SIZE], int size, vector<pair<int, int>>& corner){
    corner.clear();

    for(int i=0; i<size; i++){
        if(board[size-1][i] == bluePlayer){
            corner.emplace_back(size-1, i);
        }
    }
}

void getRightBlueCorner(char board[MAX_SIZE][MAX_SIZE], int size, vector<pair<int, int>>& corner) {
    corner.clear();

    for(int i=0; i<size; i++){
        if(board[0][i]== bluePlayer){
            corner.emplace_back(0, i);
        }
    }
}

void getRightRedCorner(char board[MAX_SIZE][MAX_SIZE], int size, vector<pair<int, int>>& corner) {
    corner.clear();

    for(int i =0; i<size; i++){
        if(board[i][size-1]==redPlayer){
            corner.emplace_back(i, size-1);
        }
    }
}

void createSquareBoard(char squareBoard[][MAX_SIZE], char arrayBoard[][MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i; ++j) {
            squareBoard[i][j] = arrayBoard[i+j][j];
        }
    }

    int offset = 0;

    for(int i=0; i<size; i++){
        for(int j=(size-1)*2; j-i>=size; j--){
            squareBoard[size-1-i][size-1-offset] = arrayBoard[j-i][i];
            offset++;
        }
        offset = 0;
    }
}

bool hasPathBetweenEdges(const vector<pair<int, int>>& edge1, const vector<pair<int, int>>& edge2, char color, const char board[MAX_SIZE][MAX_SIZE]) {
    vector<vector<bool>> visited(MAX_SIZE, vector<bool>(MAX_SIZE, false));

    // Kolejka
    vector<pair<int, int>> q;

    // Sprawdzamy pionki z pierwszej krawędzi (lewej)
    for (const auto& pawn1 : edge1) {
        int x1 = pawn1.first;
        int y1 = pawn1.second;

        q.push_back(pawn1);
        visited[x1][y1] = true;

        // Przeszukiwanie grafu z użyciem BFS
        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.erase(q.begin()); // Usuwamy pierwszy element z kolejki

            int cx = current.first;
            int cy = current.second;

            // Jeśli dotarliśmy do pionka na drugiej krawędzi, zwracamy true
            for (const auto& pawn2 : edge2) {
                if (current == pawn2)
                    return true;
            }

            // Sprawdzamy sąsiednie pionki
            static const int dx[] = {-1, -1, 0, 1, 1, 0};
            static const int dy[] = {-1, 0, 1, 1, 0, -1};

            for (int i = 0; i < 6; ++i) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];

                // Jeśli sąsiedni pionek jest na planszy, nie jest odwiedzony i ma odpowiedni kolor, dodajemy go do kolejki
                if (nx >= 0 && nx < MAX_SIZE && ny >= 0 && ny < MAX_SIZE && !visited[nx][ny] && board[nx][ny] == color) {
                    q.emplace_back(nx, ny);
                    visited[nx][ny] = true;
                }
            }
        }
    }

    // Jeśli nie znaleziono żadnej ścieżki
    return false;
}

int is_game_over(char board[MAX_SIZE][MAX_SIZE], int size) {
    if (is_board_correct(board, size)) {
        vector<pair<int, int>> leftRedCorner, leftBlueCorner, rightBlueCorner, rightRedCorner;

        getLeftRedCorner(board, size, leftRedCorner);
        getLeftBlueCorner(board, size, leftBlueCorner);
        getRightBlueCorner(board, size, rightBlueCorner);
        getRightRedCorner(board, size, rightRedCorner);

        // Warunek sprawdzający wygraną czerwonego
        if (!leftRedCorner.empty() && !rightRedCorner.empty()) {
            if (hasPathBetweenEdges(leftRedCorner, rightRedCorner, redPlayer, board)) {
                return 1;
            }
        }

        // Warunek sprawdzający wygraną niebieskiego
        if (!leftBlueCorner.empty() && !rightBlueCorner.empty()) {
            if (hasPathBetweenEdges(leftBlueCorner, rightBlueCorner, bluePlayer, board)) {
                return 2;
            }
        }
    }
    return 3; // Nikt nie wygrał
}

bool checkPreviousPosition(char board[MAX_SIZE][MAX_SIZE], int size, char player) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == player) {
                board[i][j] = nullPlayer;

                // Gra się nie skończyła
                if(is_game_over(board, size) == 3) {
                    board[i][j] = player;
                    return true;
                }

                board[i][j] = player;
            }
        }
    }
    return false;
}

bool is_board_possible(char board[MAX_SIZE][MAX_SIZE], int size){
    if(is_board_correct(board, size)){

        //Czerwony wygrał
        if(is_game_over(board, size)==1){
            if(countPlayerPawns(board, size, redPlayer)-1== countPlayerPawns(board, size, bluePlayer)){
                if(checkPreviousPosition(board, size, redPlayer)){
                    return true;
                }
            }
        }
        else if(is_game_over(board, size)==2){
            if(countPlayerPawns(board, size,bluePlayer)== countPlayerPawns(board, size, redPlayer)){
                if(checkPreviousPosition(board, size, bluePlayer)){
                    return true;
                }
            }
        }
        else{
            return true;
        }

    }
    return false;
}

void getFreeFields(char board[MAX_SIZE][MAX_SIZE], vector<std::pair<int, int>>& emptyFields, int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(board[i][j]!=redPlayer && board[i][j]!=bluePlayer){
                emptyFields.emplace_back(i,j);
            }
        }
    }
}

void getPawnsFromOppositeCorners(char board[MAX_SIZE][MAX_SIZE], vector<pair<int, int>>& leftCorner, vector<pair<int, int>>& rightCorner, char player, int size){
    if(player==redPlayer){
        getLeftRedCorner(board, size, leftCorner);
        getRightRedCorner(board, size, rightCorner);
    }
    else{
        getLeftBlueCorner(board, size, leftCorner);
        getRightBlueCorner(board, size, rightCorner);
    }
}

char getOpponent(char player){
    if(player==bluePlayer){
        return redPlayer;
    }
    else{
        return bluePlayer;
    }
}

bool canWinInOneMove(char board[MAX_SIZE][MAX_SIZE], int size, char player){
    vector<pair<int, int>> emptyFields, leftCorner, rightCorner;
    getFreeFields(board, emptyFields, size);

    int numOfEmptyFields = emptyFields.size();
    char opponent = getOpponent(player);

    getPawnsFromOppositeCorners(board, leftCorner, rightCorner, player, size);

    if(numOfEmptyFields>0 && !hasPathBetweenEdges(leftCorner, rightCorner, player, board)) {
        for(int i=0; i<emptyFields.size(); i++){
            int x1 = emptyFields[i].first;
            int y1 = emptyFields[i].second;

            board[x1][y1] = player;
            numOfEmptyFields--;

            getPawnsFromOppositeCorners(board, leftCorner, rightCorner, player, size);

            if((hasPathBetweenEdges(leftCorner, rightCorner, player, board) &&
                ((player==redPlayer && countPlayerPawns(board, size, player)-1<=(numOfEmptyFields+countPlayerPawns(board, size, opponent)))
                 ||
                 (player==bluePlayer && countPlayerPawns(board, size, player)<=(numOfEmptyFields+countPlayerPawns(board, size, opponent)))))){
                board[x1][y1] = ' ';
                return true;
            }
            board[x1][y1] = ' ';
            numOfEmptyFields++;
        }
    }
    return false;
}

bool canWinInTwoMoves(char board[MAX_SIZE][MAX_SIZE], int size, char player){
    vector<pair<int, int>> emptyFields, leftCorner, rightCorner;
    getFreeFields(board, emptyFields, size);

    int numOfEmptyFields = emptyFields.size();
    char opponent = getOpponent(player);

    for (int i = 0; i < emptyFields.size(); ++i) {
        for (int j = i + 1; j < emptyFields.size(); ++j) {
            int x1 = emptyFields[j].first;
            int y1 = emptyFields[j].second;
            int x2 = emptyFields[i].first;
            int y2 = emptyFields[i].second;

            board[x1][y1] = player;
            numOfEmptyFields--;

            getPawnsFromOppositeCorners(board, leftCorner, rightCorner, player, size);

            if((hasPathBetweenEdges(leftCorner, rightCorner, player, board) &&
                ((player==redPlayer && countPlayerPawns(board, size, player)-1<=(numOfEmptyFields+countPlayerPawns(board, size, opponent)))
                 ||
                 (player==bluePlayer && countPlayerPawns(board, size, player)<=(numOfEmptyFields+countPlayerPawns(board, size, opponent))))))
            {
                // Sprawdzamy drugi pionek z pary
                board[x1][y1] = ' ';
                board[x2][y2] = player;

                if(numOfEmptyFields>1 && canWinInOneMove(board, size, player)){
                    board[x2][y2] = ' ';
                    return true;
                }
            }
            else{
                board[x2][y2] = player;
                numOfEmptyFields--;

                getPawnsFromOppositeCorners(board, leftCorner, rightCorner, player, size);

                if((hasPathBetweenEdges(leftCorner, rightCorner, player, board) &&
                    ((player==redPlayer && countPlayerPawns(board, size, player)-1<=(numOfEmptyFields+countPlayerPawns(board, size, opponent)))
                     ||
                     (player==bluePlayer && countPlayerPawns(board, size, player)<=(numOfEmptyFields+countPlayerPawns(board, size, opponent)))))) {
                    board[x1][y1] = ' ';
                    board[x2][y2] = ' ';
                    return true;
                }
            }

            if(board[x1][y1]==player && board[x2][y2]==player){ numOfEmptyFields = numOfEmptyFields+2; }
            else{ numOfEmptyFields++;}

            board[x1][y1] = ' ';
            board[x2][y2] = ' ';
        }
    }
    return false;
}

void processNaiveOpponent(char board[][MAX_SIZE], int size){
    if(is_board_correct(board,size) && is_game_over(board, size)==3){
        // Wygrana w jednym czerwonego
        if(canWinInOneMove(board, size, redPlayer)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }

        // Wygrana w jednym niebieskiego
        if(canWinInOneMove(board, size, bluePlayer)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }

        // Wygrana w dwóch czerwonego
        if (canWinInTwoMoves(board, size, redPlayer)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

        // Wygrana w dwóch niebieskiego
        if(canWinInTwoMoves(board, size, bluePlayer)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
    else{
        for(int i=0; i<4; i++){
            cout << "NO" << endl;
        }
    }
}

void handleQuery(const string& query, char board[][MAX_SIZE], int size){
    if (query == "BOARD_SIZE") {
        cout << size << endl;
        cout << endl;
    }
    else if (query == "PAWNS_NUMBER") {
        cout << (countPlayerPawns(board, size, redPlayer) + countPlayerPawns(board, size, bluePlayer)) << endl;
        cout << endl;
    }
    else if (query == "IS_BOARD_CORRECT"){
        if(is_board_correct(board, size)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
        cout << endl;
    }
    else if (query == "IS_GAME_OVER"){
        if(is_game_over(board, size)==1){
            cout << "YES RED" << endl;
        }
        else if(is_game_over(board, size)==2){
            cout << "YES BLUE" << endl;
        }
        else if(is_game_over(board, size)==3) {
            cout << "NO" << endl;
        }
        cout << endl;
    }
    else if(query == "IS_BOARD_POSSIBLE"){
        if(is_board_possible(board, size)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
        cout << endl;
    }
    else if (query.substr(0, 41) == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
        processNaiveOpponent(board, size);
        cout << endl;
    }
}

int main() {
    string input;
    string board;
    bool insideBoard = false; // Flaga wskazująca, czy aktualnie jesteśmy wewnątrz obszaru planszy

    while (getline(cin, input)) {
        // Początek planszy
        if(input.length() >= 3 && input.substr(input.length() - 3) == "---"){
            if(!insideBoard) {
                insideBoard = true;
            } else {
                insideBoard = false;
            }
        }
        else if(insideBoard){
            board += input;
            board += '\n';
        }
        else{
            // Zapytanie
            for(int i=0; i<numOfQueries; i++){
                if(input==queries[i]){
                    int boardSize = board_size(board);
                    char arrayBoard[MAX_SIZE + MAX_SIZE][MAX_SIZE] = {{0}};
                    char squareBoard[MAX_SIZE][MAX_SIZE] = {{0}};

                    createBoard(board, arrayBoard);
                    createSquareBoard(squareBoard, arrayBoard, board_size(board));

                    handleQuery(input, squareBoard, boardSize);
                    board = "";
                }
            }
        }
    }
    return 0;
}