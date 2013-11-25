#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>

using namespace std;

typedef unsigned int UINT;
typedef std::pair<UINT,UINT> grid;

class Knight
{
    public:
        Knight(UINT row, UINT col);
        virtual ~Knight();
        void output();

    protected:
    private:
        UINT m_row; // 棋盘的行数
        UINT m_col; // 棋盘的列数
        vector<grid> m_chessboard66; // 特定大小棋盘下的一种回路信息，属于分治法中的最小解，不同的最小解合并可达到任意大的解
        vector<grid> m_chessboard68;
        vector<grid> m_chessboard86;
        vector<grid> m_chessboard88;
        vector<grid> m_chessboard810;
        vector<grid> m_chessboard108;
        vector<grid> m_chessboard1010;
        vector<grid> m_chessboard1012;
        vector<grid> m_chessboard1210;
        grid** m_link; // 保存m_row * m_col 棋盘的回路结果,马是从(0,0)开始走，是分治法合并后的解

        bool m_bDataOK; // 标记基础结构化数据是否载入OK

        // 返回棋盘中的编号
        UINT pos(UINT x, UINT y, UINT col);
        void step(UINT m, UINT n, const vector<UINT>& path_data, vector<grid>&);
        void build(UINT m, UINT n, UINT offx, UINT offy, UINT col, const vector<grid>& board);
	// 在66 68 86 88 1010 1012 1210 棋盘下的一个回路结果
        void base(UINT row, UINT col, UINT offx, UINT offy);
        // 计算回路，从m * n 棋盘的位置(offx, offy)开始寻找
        // 返回0表示找到了一条回路，否则未找到回路
        bool comp(UINT m, UINT n, UINT offx, UINT offy);

	// hepler function
	bool load_path();
	bool load_data(UINT row, UINT col, vector<UINT>& path_data, std::ifstream& ifs);
	void print_path_array(UINT row, UINT col, const vector<UINT>& path_data);
	void print_board(UINT row, UINT col, const vector<grid>& board);
    void print_links(UINT row, UINT col, grid** links);

    bool result_checker(UINT row, UINT col, const vector<grid>& board);
};

#endif // KNIGHT_H

