#pragma once

#include <iostream>
#include <climits>

namespace NS_GameCore {

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

    struct Winner
    {
        BoardPosition coordinates[CORE_BOARD_SIZE];
        BasicSignature winnerSign;
        bool isWinner;

        Winner(): isWinner(false) {}
    };

    class GameCore
    {
    public:
        GameCore(BasicSignature bot, BasicSignature player): _botSign(bot), _playerSign(player), _saveWinner(false)
        {
            clearBoard();
        }

        GameCore(BasicSignature player):
            GameCore(((player == BasicSignature::basicSignX) ? BasicSignature::basicSignO : BasicSignature::basicSignX), player) {}
        
        GameCore(): GameCore(BasicSignature::basicSignO, BasicSignature::basicSignX) {}

        int8_t move(BoardPosition position, BasicSignature sign);
        void clearBoard();

        bool movesLeft() const;
        bool isWinner();
        bool isDraw();
        
        const Winner& getWinner() const;
        
        BasicSignature getPlayerSign() const;
        BasicSignature getBotSign() const;
        
        BoardPosition findBestBotMove();

    private:
        int8_t evaluateRow();
        int8_t evaluateColumn();
        int8_t evaluateDiagonals();
        int8_t evaluateBoard();
        
        int8_t minimax(uint8_t depth, bool isMax);

    private:
        char _board[CORE_BOARD_SIZE][CORE_BOARD_SIZE];

        BasicSignature _botSign;
        BasicSignature _playerSign;

        Winner _winner;
        bool _saveWinner;

    private:
        enum Signature: char
        {
            signF = 'F',
            signO = BasicSignature::basicSignO,
            signX = BasicSignature::basicSignX
        };
    };

}