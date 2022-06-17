#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <limits>
#include <vector>

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

class node{
    public:
    char x;
    char y;
    int v;  //0 empty, 1 own, 2 other
    node(char a, char b, int c){
        x = a;
        y = b;
        v = c;
    }
    node(){
        x = 0;
        y = 0;
        v = 0;
    }
    // node& operator= (const node &other){
    //     x = other.x;
    //     y = other.y;
    //     v = other.v;
    //     return *this;
    // }
};

int player;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

//live5 9,999,999
std::vector<node> live5r{
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 1),
    node(0, 3, 1),
    node(0, 4, 1),
};
std::vector<node> live5c{
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 1),
    node(3, 0, 1),
    node(4, 0, 1)
};
std::vector<node> live5rd{
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 1),
    node(3, 3, 1),
    node(4, 4, 1)
};
std::vector<node> live5ld{
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 1),
    node(3, -3, 1),
    node(4, -4, 1)
};

//live4 1,000,000
std::vector<node> live4r{
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 1),
    node(0, 3, 1),
    node(0, 4, 0),
};
std::vector<node> live4c{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 1),
    node(3, 0, 1),
    node(4, 0, 0)
};
std::vector<node> live4rd{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 1),
    node(3, 3, 1),
    node(4, 4, 0)
};
std::vector<node> live4ld{
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 1),
    node(3, -3, 1),
    node(4, -4, 0)
};
//live3 200
std::vector<node> live3r{
    node(0, -2, 0),
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 1),
    node(0, 3, 0),
    node(0, 4, 0)
};
std::vector<node> live3r1{
    node(0, -2, 2),
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 1),
    node(0, 3, 0),
    node(0, 4, 0)
};
std::vector<node> live3r2{
    node(0, -2, 0),
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 1),
    node(0, 3, 0),
    node(0, 4, 2)
};
std::vector<node> live3c{
    node(-2, 0, 0),
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 1),
    node(3, 0, 0),
    node(4, 0, 0)
};
std::vector<node> live3c1{
    node(-2, 0, 2),
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 1),
    node(3, 0, 0),
    node(4, 0, 0)
};
std::vector<node> live3c2{
    node(-2, 0, 0),
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 1),
    node(3, 0, 0),
    node(4, 0, 2)
};
std::vector<node> live3rd{
    node(-2, -2, 0),
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 1),
    node(3, 3, 0),
    node(4, 4, 0)
};
std::vector<node> live3rd1{
    node(-2, -2, 2),
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 1),
    node(3, 3, 0),
    node(4, 4, 0)
};
std::vector<node> live3rd2{
    node(-2, -2, 0),
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 1),
    node(3, 3, 0),
    node(4, 4, 2)
};
std::vector<node> live3ld{
    node(-2, 2, 0),
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 1),
    node(3, -3, 0),
    node(4, -4, 0)
};
std::vector<node> live3ld1{
    node(-2, 2, 2),
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 1),
    node(3, -3, 0),
    node(4, -4, 0)
};
std::vector<node> live3ld2{
    node(-2, 2, 0),
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 1),
    node(3, -3, 0),
    node(4, -4, 2)
};
//live3j 30
std::vector<node> live312r{
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 0),
    node(0, 2, 1),
    node(0, 3, 1),
    node(0, 4, 0)
};
std::vector<node> live321r{
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 0),
    node(0, 3, 1),
    node(0, 4, 0)
};
std::vector<node> live312c{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 0),
    node(2, 0, 1),
    node(3, 0, 1),
    node(4, 0, 0)
};
std::vector<node> live321c{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0),
    node(3, 0, 1),
    node(4, 0, 0)
};
std::vector<node> live312rd{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 0),
    node(2, 2, 1),
    node(3, 3, 1),
    node(4, 4, 0)
};
std::vector<node> live321rd{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 0),
    node(3, 3, 1),
    node(4, 4, 0)
};
std::vector<node> live312ld{
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 0),
    node(2, -2, 1),
    node(3, -3, 1),
    node(4, -4, 0)
};
std::vector<node> live321ld{
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 0),
    node(3, -3, 1),
    node(4, -4, 0)
};
//live22 40
std::vector<node> live22{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0),
    node(1, -1, 0),
    node(1, 1, 1),  
    node(1, 2, 0)
};
std::vector<node> live221{
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 0),
    node(-1, 1, 0),
    node(1, 1, 1),  
    node(2, 1, 0)
};
std::vector<node> live222{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0),
    node(1, -2, 0),
    node(1, -1, 1),  
    node(1, 1, 0)
};
std::vector<node> live223{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0),
    node(0, -1, 0),
    node(0, 1, 1),  
    node(0, 2, 0)
};
std::vector<node> live224{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 0),
    node(-1, 1, 0),
    node(1, -1, 1),  
    node(2, -2, 0)
};
std::vector<node> live225{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 0),
    node(2, 0, 0),
    node(0, 2, 1),  
    node(-1, 3, 0)
};
std::vector<node> live226{
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 0),
    node(0, -2, 0),
    node(2, 0, 1),  
    node(3, 1, 0)
};
std::vector<node> live227{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 0),
    node(0, 2, 0),
    node(2, 0, 1),  
    node(3, -1, 0)
};
std::vector<node> live228{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0),
    node(-1, -1, 0),
    node(1, 1, 1),  
    node(2, 2, 0)
};
std::vector<node> live229{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 2, 0),
    node(1, -1, 0),
    node(1, 1, 1),  
    node(1, 2, 0)
};
std::vector<node> live2210{
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 0),
    node(-1, -1, 0),
    node(1, 1, 1),  
    node(2, 2, 0)
};
std::vector<node> live2211{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(2, 2, 0),
    node(-1, 1, 0),
    node(1, 1, 1),  
    node(2, 1, 0)
};
std::vector<node> live2212{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0),
    node(-1, 1, 0),
    node(1, -1, 1),  
    node(2, -2, 0)
};
std::vector<node> live2213{
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, -2, 0),
    node(1, -2, 0),
    node(1, -1, 1),  
    node(1, 1, 0)
};
std::vector<node> live2214{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0),
    node(-1, 2, 0),
    node(0, 1, 1),  
    node(2, -1, 0)
};
std::vector<node> live2215{
    node(-1, 2, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, -1, 0),
    node(0, -1, 0),
    node(0, 1, 1),  
    node(0, 2, 0)
};
//live2 20
std::vector<node> live2r{
    node(0, -1, 0),
    node(0, 0, 1),
    node(0, 1, 1),
    node(0, 2, 0)
};
std::vector<node> live2c{
    node(-1, 0, 0),
    node(0, 0, 1),
    node(1, 0, 1),
    node(2, 0, 0)
};
std::vector<node> live2rd{
    node(-1, -1, 0),
    node(0, 0, 1),
    node(1, 1, 1),
    node(2, 2, 0)
};
std::vector<node> live2ld{
    node(-1, 1, 0),
    node(0, 0, 1),
    node(1, -1, 1),
    node(2, -2, 0)
};

std::vector<std::vector<node>> all{
    live5r, live5c, live5rd, live5ld,
    live4r, live4c, live4rd, live4ld,
    live3r, live3c, live3rd, live3ld, live3r1, live3c1, live3rd1, live3ld1, live3r2, live3c2, live3rd2, live3ld2,
    live22, live221, live222, live223, live224, live225, live226, live227, live228, live229, live2210, live2211, live2212, live2213, live2214, live2215,
    live312r, live312c, live312rd, live312ld, live321r, live321c, live321rd, live321ld,
    live2r, live2c, live2rd, live2ld
};

std::vector<int> all_value{
    9999999, 9999999, 9999999, 9999999,
    1000000, 1000000, 1000000, 1000000, 
    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    30, 30, 30, 30, 30, 30, 30, 30, 
    20, 20, 20, 20
};


std::vector<std::vector<int>> record(SIZE, std::vector<int>(SIZE, 0));

int cal_value(int i, int j, node point, int who){
    int x = i+point.x;
    int y = j+point.y;
    if(!(x >= 0 && y >= 0 && x < SIZE && y < SIZE)){ //exceed
        return 2;
    }
    if(board[x][y] == who){ // black or white
        return 1;
    }
    if(board[x][y] == EMPTY){
        return 0;
    }
    return 2;
}

bool set_record(int i, int j, node point){ 
    if(record[i+point.x][j+point.y]){
        return false;    
    }
    record[i+point.x][j+point.y] = 1;
    return true;
}

int evaluation_point(int x, int y, int who){
    int value = 0;
    bool flag1, flag2;
    for(int i = 0; i < (int)all.size(); i++){
        flag1 = 0;
        for(int j = 0; j < (int)all[i].size(); j++){
            if(cal_value(x, y, all[i][j], who) != all[i][j].v){
                flag1 = 1;
                break;
            }
        }
        if(!flag1){
            flag2 = 0;
            for(int j = 0; j < (int)all[i].size(); j++){
                if(all[i][j].v == 1){
                    if(set_record(x, y, all[i][j])){ //check if all point use, if not, calculate in. if yes, no calculate.
                        flag2 = 1;
                    }
                }
            }
            if(flag2) {
                value = all_value[i]; 
                return value;
            }
        }
    }
    return value;
}

int evaluation(int who){
    record.clear();
    record.resize(SIZE, std::vector<int>(SIZE, 0));
    int total_value = 0;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j] == who){
                total_value += evaluation_point(i, j, who);
            }
        }
    }
    return total_value;
}

bool check_empty(int i, int j){
    if(i-1 >= 0){
        if(board[i-1][j]) return true;
        if(j-1 >= 0){
            if(board[i-1][j-1]) return true;
        }
        if(j+1 < SIZE){
            if(board[i-1][j+1]) return true;
        }
    }
    if(j-1 >= 0){
        if(board[i][j-1]) return true;
        if(i+1 < SIZE){
            if(board[i+1][j-1]) return true;
        }
    }
    if(i+1 < SIZE){
        if(board[i+1][j]) return true;
        if(j+1 < SIZE){
            if(board[i+1][j+1]) return true;
        }
    }
    if(j+1 < SIZE){
        if(board[i][j+1]) return true;
    }
    return false;
}

node minmax(int depth, bool maxplayer){
    if(depth <= 0){
        if(player == BLACK)
            return node(0, 0, evaluation(BLACK)-evaluation(WHITE));
        else
            return node(0, 0, evaluation(WHITE)-evaluation(BLACK));
    }
    node temp, value(7, 7, 0);
    if(maxplayer){
        value.v = std::numeric_limits<int>::min();
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(board[i][j] == EMPTY && check_empty(i, j)){
                    board[i][j] = player;
                    temp = minmax(depth-1, false);
                    if(temp.v > value.v){
                        value.v = temp.v;
                        value.x = i;
                        value.y = j;
                    }
                    board[i][j] = EMPTY;
                }
            }
        }
    }else{
        value.v = std::numeric_limits<int>::max();
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(board[i][j] == EMPTY && check_empty(i, j)){
                    if(player == BLACK){
                        board[i][j] = WHITE;
                    }else{
                        board[i][j] = BLACK;
                    }
                    temp = minmax(depth-1, true);
                    if(temp.v < value.v){
                        value.v = temp.v;
                    }
                    board[i][j] = EMPTY;
                }
            }
        }
    }
    return value;
}

void write_valid_spot(std::ofstream& fout) {
    int x, y;
    node temp;
    temp = minmax(2, true);
    x = temp.x;
    y = temp.y;
    if(board[x][y] != EMPTY){ //second
        x++;
        y++;
    }
    fout << x << " " << y << std::endl;
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
