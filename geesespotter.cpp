#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim) {
    char *array{new char[xdim * ydim] {0}};
    return array;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
    for (int i{0}; i< ydim; ++i) {
        for (int k{0}; k< xdim; ++k) {
                if ((board[i*xdim + k] & valueMask()) == 9) {
                    if (k > 0) {
                        if ((board[i*xdim + k -1] & valueMask()) != 9) {
                         board[i*xdim + k -1] +=1;
                        }
                        if (i > 0) {
                            if ((board[(i-1)*xdim + k -1] & valueMask()) != 9 ) {
                            board[(i-1)*xdim + k -1] +=1;
                            }
                        }
                        if (i < ydim -1) {
                            if ((board[(i+1)*xdim + k -1] & valueMask()) != 9 ) {
                            board[(i+1)*xdim + k -1] +=1;
                            }
                        }
                }
                if (k < xdim -1) {
                        if ((board[i*xdim + k +1] & valueMask()) != 9) {
                         board[i*xdim + k +1] +=1;
                        }
                        if (i > 0) {
                            if ((board[(i-1)*xdim + k +1] & valueMask()) != 9 ) {
                            board[(i-1)*xdim + k +1] +=1;
                            }
                        }
                        if (i < ydim -1) {
                            if ((board[(i+1)*xdim + k +1] & valueMask()) != 9 ) {
                            board[(i+1)*xdim + k +1] +=1;
                            }
                        }
                }
                if (i > 0) {
                    if ((board[(i-1)*xdim + k] & valueMask()) != 9) {
                        board[(i-1)*xdim + k] +=1;
                    }
                }
                if (i < ydim-1) {
                    if ((board[(i+1)*xdim + k] & valueMask()) != 9) {
                        board[(i+1)*xdim + k] +=1;
                    }
                }
                
            }
        }
    }
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,std::size_t yloc) {
    if ((board[xdim*yloc + xloc]&valueMask()) == 0) {
        if (xloc > 0) {
            if ((board[xdim*yloc + xloc -1] & valueMask()) != 9) {
                board[xdim*yloc + xloc -1] &= valueMask();
            }
            if (yloc > 0) {
                if ((board[xdim*(yloc-1) + xloc-1] & valueMask()) != 9 ) {
                board[xdim*(yloc-1) + xloc-1] &= valueMask();
                }
            }
            if (yloc < ydim -1) {
                if ((board[xdim*(yloc+1) + xloc-1] & valueMask()) != 9 ) {
                board[xdim*(yloc+1) + xloc-1] &= valueMask();
                }
            }
        }
        if (xloc < xdim -1) {
            if ((board[xdim*yloc + xloc +1] & valueMask()) != 9) {
                board[xdim*yloc + xloc +1] &= valueMask();
            }
            if (yloc > 0) {
                if ((board[xdim*(yloc-1) + xloc+1] & valueMask()) != 9 ) {
                board[xdim*(yloc-1) + xloc+1] &= valueMask();
                }
            }
            if (yloc < ydim -1) {
                if ((board[xdim*(yloc+1) + xloc+1] & valueMask()) != 9 ) {
                board[xdim*(yloc+1) + xloc+1] &= valueMask();
                }
            }
        }
        if (yloc > 0) {
            if ((board[xdim*(yloc-1) + xloc] & valueMask()) != 9) {
                board[xdim*(yloc-1) + xloc] &= valueMask();
            }
        }
        if (yloc < ydim -1) {
            if ((board[xdim*(yloc+1) + xloc] & valueMask()) != 9) {
                board[xdim*(yloc+1) + xloc] &= valueMask();
            }
        }
    }
    if ((board[xdim*yloc + xloc] & markedBit()) != 0) {
        board[xdim*yloc + xloc] &= valueMask();
        return 1;
    }
    if ((board[xdim*yloc + xloc] & valueMask()) == 9) {
        board[xdim*yloc + xloc] &= valueMask();
        return 9;
    }
    if (((board[xdim*yloc + xloc] & markedBit()) == 0) && ((board[xdim*yloc + xloc] & hiddenBit()) ==0)) {
        board[xdim*yloc + xloc] &= valueMask();
        return 2;
    }
    else {
        board[xdim*yloc + xloc] &= valueMask();
        return 0;
    }
    return 0;
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i<xdim*ydim; ++i) {  
            board[i] += hiddenBit();
    }
}

void cleanBoard(char *board) {
    delete[]board;
    board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i< xdim*ydim; ++i) {
            if ((board[i] & markedBit()) == markedBit()) {
                std::cout<<"M";
            }
            else if ((board[i] & hiddenBit()) == hiddenBit()) {
                std::cout<<"*";
            }
            else {
                std::cout<< (board[i] & valueMask());
            }
            if ((i+1) % xdim ==0) {   
                std::cout<<std::endl;
            }
        }
    }




int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,std::size_t yloc) {
    if (((board[xdim*yloc + xloc] & hiddenBit()) == 0) && ((board[xdim*yloc + xloc] & markedBit()) == 0)) {
        return 2;
    }
    if ((board[xdim*yloc + xloc] & markedBit()) != 0) {
        board[xdim*yloc + xloc] -=markedBit();
    }
    else if ((board[xdim*yloc + xloc] & markedBit()) == 0) {
        board[xdim*yloc + xloc] +=markedBit();
    }
    
    return 0;
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i<xdim*ydim; ++i) {
        if (((board[i] & valueMask()) != 9) && (((board[i] & hiddenBit()) != 0) || ((board[i] & markedBit()) != 0))) {
            return false;
        }
}
    return true;
}