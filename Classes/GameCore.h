#pragma once

#include <iostream>
#include <climits>

namespace TicTacToe {

    #define CORE_BOARD_SIZE 3

    struct BoardPosition
    {
        int8_t row;
        int8_t col;

        BoardPosition(): row(-1), col(-1) {}
        BoardPosition(int8_t r, int8_t c): row(r), col(c) {}
    };

    enum BasicSignature: char
    {
        basicSignO = 'O',
        basicSignX = 'X'
    };

    enum Signature: char
    {
        signF = 'F',
        signO = BasicSignature::basicSignO,
        signX = BasicSignature::basicSignX
    };

    struct Winner
    {
        BoardPosition coordinates[CORE_BOARD_SIZE];
        Signature winnerSign;

        Winner(): winnerSign(Signature::signF) {}
    };

    class GameCore
    {
    public:
        GameCore(BasicSignature bot, BasicSignature player): _botSign(bot), _playerSign(player)
        {
            clearBoard();
        }

        GameCore(BasicSignature player):
            GameCore(((player == BasicSignature::basicSignX) ? BasicSignature::basicSignO : BasicSignature::basicSignX), player) {}
        
        GameCore(): GameCore(BasicSignature::basicSignO, BasicSignature::basicSignX) {}

        char modifyBoard(BoardPosition position, BasicSignature sign);
        void clearBoard();

        bool movesLeft() const;
        bool isWinner();
        bool isDraw();
        
        const Winner& getWinner() const;
        
        BasicSignature getPlayerSign() const;
        BasicSignature getBotSign() const;
        
        BoardPosition findBestBotMove();

        int8_t playerMove(BoardPosition position);
        int8_t botMove(BoardPosition position);

    private:
        int8_t evaluateBoard(bool saveWinner);
        int8_t minimax(uint8_t depth, bool isMax);

    private:
        char _board[CORE_BOARD_SIZE][CORE_BOARD_SIZE];

        BasicSignature _botSign;
        BasicSignature _playerSign;

        Winner _winner;
    };

}