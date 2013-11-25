#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "Knights.h"

using namespace std;

Knight::Knight(UINT row, UINT col)
{
	m_row = row;
	m_col = col;


	m_link = new grid*[m_row];
	for (UINT i = 0; i < m_row ; i++)
	{
		m_link[i] = new grid[m_col];
	}

	m_bDataOK = load_path();
}

Knight::~Knight()
{
	for (UINT i = 0; i < m_row ; i++)
	{
		delete []m_link[i];
		m_link[i] = NULL;
	}
	delete []m_link;
	m_link = NULL;
}

// load a loop path from a to the grid b.
void Knight::step(UINT row, UINT col, const vector<UINT>& path_data, vector<grid>& b)
{
	//print_path_array(row,col,path_data);

	b.resize(row * col , std::make_pair(0,0));

	if (row <= col)
	{
		for (UINT i = 0; i < row ; i++)
		{
			for (UINT j = 0; j < col ; j++)
			{
				UINT p = path_data[pos(i,j,col)] - 1;
				b[p].first = i;
				b[p].second = j;
			}
		}
	}
	else
	{
		for (UINT i = 0; i < row ; i++)
		{
			for (UINT j = 0; j < col ; j++)
			{
				UINT p = path_data[pos(j,i,col)] - 1;
				b[p].first = i;
				b[p].second = j;
			}
		}
	}

	//print_board(row, col, b);
}
// row, col 是棋盘的大小
// offx, offy是马的初始位置
bool Knight::comp(UINT row, UINT col, UINT offx, UINT offy)
{
	// 过滤不支持的类型
	if ( 0 != row%2 || 0 != col%2
			|| row -col > 2
			|| col - row > 2
			|| row < 6
			|| col < 6 )
	{
		cout << "Invalid/unsupported parameters of the size of the board" << endl;
		return 1;
	}
	if (row < 12 || col < 12 )
	{
		base(row,col,offx,offy); // base solution
		return 0;
	}

	// 将棋盘四分
	UINT row1 = row/2;
	if (row %4 > 0 ) row1--; // 处理不能四等分的情景
	UINT row2 = col - row1;
	UINT col1 = col/2;
	if (col%4 > 0 ) col1--;
	UINT col2 = col - col1;
	// divide，单独计算四个小棋盘
	comp(row1, col1, offx, offy);
	comp(row1, col2, offx, offy+col1);
	comp(row2, col1, offx+row1, offy);
	comp(row2, col2, offx+row1, offy+col1);
	// conquer/ merge
	UINT x[8], y[8];
	x[0] = offx + row1 -1;	y[0] = offy + col1 -3; // 见合并步骤中的图2-17
	x[1] = x[0] - 1;    	y[1] = y[0] + 2;
	x[2] = x[1] - 1;    	y[2] = y[1] + 2;
	x[3] = x[2] + 2;        y[3] = y[2] - 1;
	x[4] = x[3] + 1;    	y[4] = y[3] + 2;
	x[5] = x[4] + 1;    	y[5] = y[4] - 2;
	x[6] = x[5] + 1;        y[6] = y[5] - 2;
	x[7] = x[6] - 2;    	y[7] = y[6] + 1;

	UINT p[8];
	for (UINT i = 0; i < 8; i++)
		p[i] = pos(x[i], y[i],m_col); // 求真实大棋盘中对应的位置编号

	// 真正的合并子结果
	for (UINT i = 1; i < 8; i += 2)
	{
		UINT j1 = (i + 1) % 8;
		UINT j2 = (i + 2) % 8;
		/*UINT p1 = pos(x[i],y[i],m_col);*/
		if (m_link[x[i]][y[i]].first == p[i-1])
			m_link[x[i]][y[i]].first = p[j1];
		else
			m_link[x[i]][y[i]].second = p[j1];

		if (m_link[x[j1]][y[j1]].first == p[j2])
			m_link[x[j1]][y[j1]].first = p[i];
		else
			m_link[x[j1]][y[j1]].second = p[i];
	}

	return 0;
}

void Knight::base(UINT row, UINT col, UINT offx, UINT offy)
{
	if (row == 6 && col == 6) build(row, col, offx, offy, m_col, m_chessboard66);
	if (row == 6 && col == 8) build(row, col, offx, offy, m_col, m_chessboard68);
	if (row == 8 && col == 6) build(row, col, offx, offy, m_col, m_chessboard86);
	if (row == 8 && col == 8) build(row, col, offx, offy, m_col, m_chessboard88);
	if (row == 8 && col == 10) build(row, col, offx, offy, m_col, m_chessboard810);
	if (row == 10 && col == 8) build(row, col, offx, offy, m_col, m_chessboard108);
	if (row == 10 && col == 10) build(row, col, offx, offy, m_col, m_chessboard1010);
	if (row == 10 && col == 12) build(row, col, offx, offy, m_col, m_chessboard1012);
	if (row == 12 && col == 10) build(row, col, offx, offy, m_col, m_chessboard1210);

	//print_links(m_row, m_col, m_link);
}

void Knight::build(UINT m, UINT n, UINT offx, UINT offy, UINT col, const vector<grid>& board)
{
	UINT k = m * n; // k 是棋盘走局board的大小
	for (UINT i = 0; i < k ; i++)
	{
		// first step, 获取小棋盘board上第i步的坐标
		UINT x1 = offx + board[i].first;
		UINT y1 = offy + board[i].second;
		// next step, 第i+1步的坐标
		UINT x2 = offx + board[(i+1)%k].first;
		UINT y2 = offy + board[(i+1)%k].second;

		UINT p = pos(x1, y1, col);// 小棋盘下的坐标对应的大棋盘的第p个位置
		UINT q = pos(x2, y2, col);// 对应第q个位置
		m_link[x1][y1].first = q;
		m_link[x2][y2].second = p;
	}
}


UINT Knight::pos(UINT x, UINT y, UINT col)
{
	return col * x + y;
}

void Knight::output()
{
	//cout << "Before the computing" << endl;
	//print_links(m_row,m_col, m_link);

	if (!m_bDataOK)
        return;

	if (comp(m_row,m_col,0,0))
	{
		cout << "Unable to find a tour. " << endl;
		return;
	}

	//cout << "After the computing" << endl;
	//print_links(m_row,m_col, m_link);

	// 按照马走的顺序，依次打印每一步在棋盘中的x，y坐标，坐标从0开始计数
	UINT **a = new UINT*[m_row];
	for (UINT i = 0; i < m_row; i++)
	{
		a[i] = new UINT[m_col];
	}

	for (UINT i = 0; i < m_row; i++)
	{
		for (UINT j = 0; j < m_col; j++)
		{
			a[i][j] = 0;
		}
	}

	UINT i = 0;
	UINT j = 0;
	UINT k = 2;
	a[0][0] = 1; // 表示第一步，马周游的起点
	cout << "(0,0)" << " ";

	vector<grid> finalboard;
	finalboard.resize(m_row*m_col, make_pair(0,0));

	for (UINT p = 1; p < m_row * m_col; p++)
	{
		UINT x = m_link[i][j].first;
		UINT y = m_link[i][j].second;
		i = x/m_col;
		j = x%m_col;
		if(a[i][j] > 0)
		{
			i = y/m_col;
			j = y%m_col;
		}
		finalboard[k-1] = make_pair(i,j);
		a[i][j] = k++; // 棋盘的位置p是第k步
		cout << "(" << i << "," << j << ") ";
		if ((k-1)%m_col == 0)
			cout << endl;
	}
	cout << endl;

	for (UINT i = 0; i < m_row; i++)
	{
		for (UINT j = 0; j < m_col; j++)
		{
			cout << a[i][j] <<" ";
		}
		cout << endl;
	}

	if(!result_checker(m_row,m_col,finalboard))
    {
        cerr << "Result is wrong" << endl;
    }
    else
    {
        cout << "Corret!" << endl;
    }


	for (UINT i = 0; i < m_row; i++)
	{
		delete []a[i];
		a[i] = NULL;
	}
	delete []a;
	a = NULL;
}



bool Knight::load_path()
{
	UINT iterator1[9] = {6,6,8,8,8,10,10,10,12};
	UINT iterator2[9] = {6,8,6,8,10,8,10,12,10};
	vector<vector<grid>* > grids;
	grids.push_back(&m_chessboard66);
	grids.push_back(&m_chessboard68);
	grids.push_back(&m_chessboard86);
	grids.push_back(&m_chessboard88);
	grids.push_back(&m_chessboard810);
	grids.push_back(&m_chessboard108);
	grids.push_back(&m_chessboard1010);
	grids.push_back(&m_chessboard1012);
	grids.push_back(&m_chessboard1210);

	std::ifstream ifs("board_path.txt");
	if (!ifs.is_open())
	{
		cout << "Unable to load base data from board_path.txt" << endl;
		return false;
	}

	vector<UINT> a;
	a.resize(12*10); // 最大只需要这么多

    bool bOK = true;
	for (UINT i = 0; i < 9; i++)
	{
		if(!load_data(iterator1[i], iterator2[i],a, ifs))
        {
            bOK = false;
            break;
        }
		step(iterator1[i], iterator2[i],a, *grids[i]);
	}
	return bOK;
}

bool Knight::load_data(UINT row, UINT col, vector<UINT>& data, std::ifstream& ifs)
{
	if (row * col > data.size())
	{
		cout << "overflow" << endl;
		return false;
	}
	for (UINT  i = 0; i < row; i++ )
	{
		for (UINT j = 0; j < col; j++)
		{
			ifs >> data[pos(i,j,col)];
		}
	}
	return true;
}


void Knight::print_path_array(UINT row, UINT col, const vector<UINT>& path_data)
{
	if (row * col > path_data.size())
	{
		cout << "overflow" << endl;
		return;
	}
	cout << "Raw data " << row << " * " << col << endl;
	for (UINT i = 0; i < row; i++)
	{
		for (UINT j = 0; j < col; j++)
		{
			cout << path_data[pos(i,j,col)] << " " ;
		}
		cout << endl;
	}
}

void Knight::print_board(UINT row, UINT col, const vector<grid>& board)
{
	if (row * col > board.size())
	{
		cout << "overflow " <<  __FUNCTION__ << endl;
		return;
	}

	cout << "*****" << endl;
	for (UINT i = 0; i < row; i++)
	{
		for (UINT j = 0; j < col; j++)
		{
			cout << "(" << board[pos(i,j,col)].first
				<< "," << board[pos(i,j,col)].second  << "),";
		}
		cout << endl;
	}
}

void Knight::print_links(UINT row, UINT col, grid** links)
{
	for (UINT i = 0; i < row; i++)
	{
		for (UINT j = 0; j < col; j++)
		{
			cout << "(" << links[i][j].first << "," << links[i][j].second << ")" ;
		}
		cout << endl;
	}
}

bool Knight::result_checker(UINT row, UINT col, const vector<grid>& board)
{
    if (board.empty())
        return false;
    if (board.size() == 1)
        return true;

    set<grid> setGrids(board.begin(),board.end());
    if (setGrids.size() != row*col)
        return false;
    vector<grid>::const_iterator itrFirstGrid = board.begin();
    vector<grid>::const_iterator itrSecGrid = itrFirstGrid;

    for(++itrSecGrid; board.end() != itrSecGrid; ++itrFirstGrid, ++itrSecGrid)
    {
        UINT offx = 0;
        UINT offy = 0;
        if(itrFirstGrid->first <= itrSecGrid->first)
            offx = itrSecGrid->first - itrFirstGrid->first;
        else
            offx = itrFirstGrid->first - itrSecGrid->first;

         if(itrFirstGrid->second <= itrSecGrid->second)
            offy = itrSecGrid->second - itrFirstGrid->second;
        else
            offy = itrFirstGrid->second - itrSecGrid->second;

        if (0  == offx || 0 == offy
            || ! ( (1==offx && 2 == offy) || (2 == offx && 1== offy ) ))
        {
            UINT id = distance(board.begin(),itrFirstGrid);
            cerr << id << " and " << id+1
                << "(" << itrFirstGrid->first << "," << itrFirstGrid->second << ") and "
                << "(" << itrSecGrid->first << "," << itrSecGrid->second << " illegal " << endl;
            return false;
        }
    }

    return true;
}
