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
        UINT m_row; // ���̵�����
        UINT m_col; // ���̵�����
        vector<grid> m_chessboard66; // �ض���С�����µ�һ�ֻ�·��Ϣ�����ڷ��η��е���С�⣬��ͬ����С��ϲ��ɴﵽ�����Ľ�
        vector<grid> m_chessboard68;
        vector<grid> m_chessboard86;
        vector<grid> m_chessboard88;
        vector<grid> m_chessboard810;
        vector<grid> m_chessboard108;
        vector<grid> m_chessboard1010;
        vector<grid> m_chessboard1012;
        vector<grid> m_chessboard1210;
        grid** m_link; // ����m_row * m_col ���̵Ļ�·���,���Ǵ�(0,0)��ʼ�ߣ��Ƿ��η��ϲ���Ľ�

        bool m_bDataOK; // ��ǻ����ṹ�������Ƿ�����OK

        // ���������еı��
        UINT pos(UINT x, UINT y, UINT col);
        void step(UINT m, UINT n, const vector<UINT>& path_data, vector<grid>&);
        void build(UINT m, UINT n, UINT offx, UINT offy, UINT col, const vector<grid>& board);
	// ��66 68 86 88 1010 1012 1210 �����µ�һ����·���
        void base(UINT row, UINT col, UINT offx, UINT offy);
        // �����·����m * n ���̵�λ��(offx, offy)��ʼѰ��
        // ����0��ʾ�ҵ���һ����·������δ�ҵ���·
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

