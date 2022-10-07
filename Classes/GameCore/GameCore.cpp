#include "GameCore.h"

namespace NS_GameCore {

    int8_t GameCore::move(BoardPosition position, BasicSignature sign)
    {
        if(_board[position.row][position.col] != Signature::signF)
            return -1;
        
        if(position.row < 0 || position.col < 0)
            return -1;
        
        if(isWinner())
            return 0;
        
        _board[position.row][position.col] = sign;
        
        return 0;
    }

    void GameCore::clearBoard()
    {
        memset(_board, Signature::signF, sizeof(_board));
    }

    bool GameCore::movesLeft() const
    {
        for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
            for(uint8_t j = 0; j < CORE_BOARD_SIZE; j++)
                if(_board[i][j] == Signature::signF)
                    return true;
        
        return false;
    }

    bool GameCore::isWinner()
    {
        _saveWinner = true;

        evaluateBoard();

        _saveWinner = false;
        
        return _winner.isWinner;
    }

    bool GameCore::isDraw()
    {
        if(!movesLeft() && !isWinner())
            return true;
        
        return false;
    }

    const Winner& GameCore::getWinner() const
    {
        return _winner;
    }

    BasicSignature GameCore::getPlayerSign() const
    {
        return _playerSign;
    }

    BasicSignature GameCore::getBotSign() const
    {
        return _botSign;
    }

    int8_t GameCore::evaluateRow()
    {
        for(uint8_t row = 0; row < CORE_BOARD_SIZE; row++)
        {
            if((_board[row][0] == _board[row][1]) && (_board[row][1] == _board[row][2]))
            {
                if((_board[row][0] != Signature::signF) && _saveWinner)
                {
                    for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                    {
                        _winner.coordinates[i].row = row;
                        _winner.coordinates[i].col = i;
                    }
                    
                    _winner.winnerSign = static_cast<Signature>(_board[row][0]);
                }
                
                if(_board[row][0] == _botSign)
                    return 10;
                else if(_board[row][0] == _playerSign)
                    return -10;
            }
        }

        return 0;
    }

    int8_t GameCore::evaluateColumn()
    {
        for(uint8_t col = 0; col < CORE_BOARD_SIZE; col++)
        {
            if((_board[0][col] == _board[1][col]) && (_board[1][col] == _board[2][col]))
            {
                if((_board[0][col] != Signature::signF) && _saveWinner)
                {
                    for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                    {
                        _winner.coordinates[i].row = i;
                        _winner.coordinates[i].col = col;
                    }
                    
                    _winner.winnerSign = static_cast<Signature>(_board[0][col]);
                }
                
                if(_board[0][col] == _botSign)
                    return 10;
                else if(_board[0][col] == _playerSign)
                    return -10;
            }
        }

        return 0;
    }

    int8_t GameCore::evaluateDiagonals()
    {
        if((_board[0][0] == _board[1][1]) && (_board[1][1] == _board[2][2]))
        {
            if((_board[0][0] != Signature::signF) && _saveWinner)
            {
                for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                {
                    _winner.coordinates[i].row = i;
                    _winner.coordinates[i].col = i;
                }
                
                _winner.winnerSign = static_cast<Signature>(_board[0][0]);
            }
            
            if(_board[0][0] == _botSign)
                return 10;
            else if(_board[0][0] == _playerSign)
                return -10;
        }
        
        if((_board[0][2] == _board[1][1]) && (_board[1][1] == _board[2][0]))
        {
            if((_board[0][2] != Signature::signF) && _saveWinner)
            {
                for(uint8_t i = 0, c = (CORE_BOARD_SIZE - 1); i < CORE_BOARD_SIZE; i++, c--)
                {
                    _winner.coordinates[i].row = i;
                    _winner.coordinates[i].col = c;
                }
                
                _winner.winnerSign = static_cast<Signature>(_board[0][2]);
            }
            
            if(_board[0][2] == _botSign)
                return 10;
            else if(_board[0][2] == _playerSign)
                return -10;
        }

        return 0;
    }

    int8_t GameCore::evaluateBoard()
    {
#define EVAL_BOARD_RESULT(F) result = F(); if(result) return result;
        int8_t result;

        EVAL_BOARD_RESULT(evaluateRow);
        EVAL_BOARD_RESULT(evaluateColumn);
        EVAL_BOARD_RESULT(evaluateDiagonals);
        
#undef EVALUATE_BOARD_RESULT
        return result;
    }

    int8_t GameCore::minimax(uint8_t depth, bool isMax)
    {
        int8_t score = evaluateBoard();
        
        if(score == 10 || score == -10)
            return score;
        
        if(!movesLeft())
            return 0;
        
        if(isMax)
        {
            int8_t best = SCHAR_MIN;
            
            for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                for(uint8_t j = 0; j < CORE_BOARD_SIZE; j++)
                    if(_board[i][j] == Signature::signF)
                    {
                        _board[i][j] = _botSign;
                        
                        best = std::max(best, minimax((depth + 1), !isMax));
                        
                        _board[i][j] = Signature::signF;
                    }
            
            return (best - depth);
        }
        else
        {
            int8_t best = SCHAR_MAX;
            
            for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                for(uint8_t j = 0; j < CORE_BOARD_SIZE; j++)
                    if(_board[i][j] == Signature::signF)
                    {
                        _board[i][j] = _playerSign;
                        
                        best = std::min(best, minimax((depth + 1), !isMax));
                        
                        _board[i][j] = Signature::signF;
                    }
            
            return (best + depth);
        }
    }

    BoardPosition GameCore::findBestBotMove()
    {
        int8_t bestVal = SCHAR_MIN;
        BoardPosition bestMove;
        
        for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
            for(uint8_t j = 0; j < CORE_BOARD_SIZE; j++)
                if(_board[i][j] == Signature::signF)
                {
                    _board[i][j] = _botSign;
                    
                    int8_t moveVal = minimax(0, false);
                    
                    _board[i][j] = Signature::signF;
                    
                    if(moveVal > bestVal)
                    {
                        bestMove.row = i;
                        bestMove.col = j;
                        bestVal = moveVal;
                    }
                }
        
        return bestMove;
    }

}