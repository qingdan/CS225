#include "maze.h"

SquareMaze::SquareMaze()
{	
}

void SquareMaze::makeMaze (int width, int height) 
{
	this->width = width;
	this->height = height;
	size = width * height;
	setofcells.addelements(size);
	/*intialize all the walls to be true*/
	for(int i = 0; i < size; i++)
	{
		rightWall.push_back(true);
		downWall.push_back(true);
	}
	/*set x random walls to be false*/
	int numOfRandom = size/2;
	int i = 0;
	int isRight = 0;
	srand (time(NULL));
	while(i < numOfRandom)
	{
		int rowNum = rand() % (height-1);
		int columnNum = rand() % (width-1);
		int isRight = rand() % 2;
		if(isRight)
		{
			/*check if break the wall will create circle*/
			if(rightWall[rowNum*width + columnNum] == true &&
				setofcells.find(rowNum*width + columnNum) != setofcells.find(rowNum*width + columnNum+1))
			{
				rightWall[rowNum*width + columnNum] = false;
				setofcells.setunion (rowNum*width + columnNum, rowNum*width + columnNum+1);
				isRight = 0;
				i++;
			}
			
		}
		else
		{
			/*check if break the wall will create circle*/
			if(downWall[rowNum*width + columnNum] == true &&
				setofcells.find(rowNum*width + columnNum) != setofcells.find((rowNum+1)*width + columnNum))
			{
				downWall[rowNum*width + columnNum] = false;
				setofcells.setunion (rowNum*width + columnNum, (rowNum+1)*width + columnNum);
				isRight = 1;
				i++;
			}			
		}
	}
	int row = 0;
	/*check each wall to see if it can be broken*/
	for(; row < height-1; row++)
	{
		int column = 0;
		for(; column < width-1; column++)
		{
			if(isRight)
			{
				/*first check if the right wall can be broken*/
				if(rightWall[row*width + column] == true &&
					setofcells.find(row*width + column) != setofcells.find(row*width + column+1))
				{
					rightWall[row*width + column] = false;
					setofcells.setunion (row*width + column, row*width + column+1);
				}
				/*then check if the down wall can be broken*/
				if(downWall[row*width + column] == true &&
					setofcells.find(row*width + column) != setofcells.find((row+1)*width + column))
				{
					downWall[row*width + column] = false;
					setofcells.setunion (row*width + column, (row+1)*width + column);
				}
				isRight = 0;
			}
			else
			{
				/*first check if the down wall can be broken*/
				if(downWall[row*width + column] == true &&
					setofcells.find(row*width + column) != setofcells.find((row+1)*width + column))
				{
					downWall[row*width + column] = false;
					setofcells.setunion (row*width + column, (row+1)*width + column);
				}
				/*then check if the right wall can be broken*/
				if(rightWall[row*width + column] == true &&
					setofcells.find(row*width + column) != setofcells.find(row*width + column+1))
				{
					rightWall[row*width + column] = false;
					setofcells.setunion (row*width + column, row*width + column+1);
				}
				isRight = 1;
			}
		}
		/*check the rightmost column for down walls*/
		if(downWall[row*width + column] == true &&
			setofcells.find(row*width + column) != setofcells.find((row+1)*width +column))
			{
				downWall[row*width + column] = false;
				setofcells.setunion (row*width + column, (row+1)*width + column);
			}
	}
	/*check downmost row for right walls*/
	for(int column = 0; column < width-1; column++)
		{
			if(rightWall[row*width + column] == true &&
				setofcells.find(row*width + column) != setofcells.find(row*width + column+1))
			{
				rightWall[row*width + column] = false;
				setofcells.setunion (row*width + column, row*width + column+1);
			}
		}
}	

bool SquareMaze::canTravel (int x, int y, int dir) const
{
	/*check right direction*/
	if(dir == 0&&x != width-1)
		return (rightWall[y*width + x] == false);
	/*check down direction*/
	if(dir == 1&&y != height-1)
		return (downWall[y*width + x] == false);
	/*check left direction*/
	if(dir == 2&&x != 0)
		return (rightWall[y*width + x-1] == false);
	/*check up direction*/
	if(dir == 3&&y != 0)
		return (downWall[(y-1)*width + x] == false);	
	return false;
}
 	
void SquareMaze::setWall (int x, int y, int dir, bool exists)
{
	int index = y*width+x;
	/*set wall for right*/
	if(dir == 0&&x != width-1)
			rightWall[index] = exists? true : false;
	/*set wall for down*/
	if(dir == 1&&y != height-1)
			downWall[index] = exists? true : false;
	return;
}

vector< int > SquareMaze::solveMaze ()
{
	vector< int > path;
	int * lastRow = new int[width];
	solveMaze_helper(0, 0, path, lastRow);
	/*find the only path*/
	int final_dest = 0;
	for(int i = 1; i < width; i++)
	{
		if(lastRow[final_dest] < lastRow[i])
			final_dest = i;
	}
	path.clear();
	solveMaze_second_helper(0, 0, path, final_dest);
	delete [] lastRow;
	return path;

}
 
PNG * SquareMaze::drawMaze () const
{
	PNG * outPNG = new PNG(width*10+1, height*10+1);
	/*first blacken the leftmost column*/
	for(int row = 0; row < height*10; row++)
	{
		(*outPNG)(0, row)->red = 0;	
		(*outPNG)(0, row)->green = 0;	
		(*outPNG)(0, row)->blue = 0;	
	}
	/*then blacken the topmost column*/
	(*outPNG)(0, 0)->red = 0;
	(*outPNG)(0, 0)->green = 0;
	(*outPNG)(0, 0)->blue = 0;
	for(int column = 10; column < width*10; column++)
	{
		(*outPNG)(column, 0)->red = 0;	
		(*outPNG)(column, 0)->green = 0;	
		(*outPNG)(column, 0)->blue = 0;	
	}
	/*go through each maze*/
	for(int i = 0; i < size; i++)
	{
		int mazey = i/width;
		int mazex = i%width;
		if(rightWall[i])
		{
			for(int k = 0; k <= 10; k++)
			{
				(*outPNG)((mazex + 1) * 10, mazey * 10 + k)->red = 0;
				(*outPNG)((mazex + 1) * 10, mazey * 10 + k)->green = 0;
				(*outPNG)((mazex + 1) * 10, mazey * 10 + k)->blue = 0;
			}
		}
		if(downWall[i])
		{
			for(int k = 0; k <= 10; k++)
			{
				(*outPNG)(mazex * 10 + k, (mazey + 1) * 10)->red = 0;
				(*outPNG)(mazex * 10 + k, (mazey + 1) * 10)->green = 0;
				(*outPNG)(mazex * 10 + k, (mazey + 1) * 10)->blue = 0;
			}
		}
		
	}

	return outPNG;
}
 
PNG * SquareMaze::drawMazeWithSolution ()
{
	PNG * outPNG = drawMaze();
	vector< int > path = solveMaze();
	int x = 5;
	int y = 5;
	for(size_t i = 0; i < path.size(); i++)
	{
		
		if(path[i] == 0)
		{
			for(int j = 0; j < 11; j++)
			{
				(*outPNG)(x + j, y)->red = 255;
				(*outPNG)(x + j, y)->green = 0;
				(*outPNG)(x + j, y)->blue = 0;
			}
			x += 10;
		}
		
		else if(path[i] == 1)
		{
			for(int j = 0; j < 11; j++)
			{
				(*outPNG)(x, y + j)->red = 255;
				(*outPNG)(x, y + j)->green = 0;
				(*outPNG)(x, y + j)->blue = 0;
			}			
			y += 10;
		}
		
		else if(path[i] == 2)
		{
			for(int j = 0; j < 11; j++)
			{
				(*outPNG)(x - j, y)->red = 255;
				(*outPNG)(x - j, y)->green = 0;
				(*outPNG)(x - j, y)->blue = 0;				
			}
			x -= 10;
		}
		
		else
		{
			for(int j = 0; j < 11; j++)
			{
				(*outPNG)(x, y - j)->red = 255;
				(*outPNG)(x, y - j)->green = 0;
				(*outPNG)(x, y - j)->blue = 0;	
			}		
			y -= 10;
		}
	}

	/*draw the exit*/
	int mazex = x /10;
	int mazey = height - 1;
	for(int k = 1; k < 10; k++)
	{
		(*outPNG)(mazex * 10 + k, (mazey + 1) * 10)->red = 255;
		(*outPNG)(mazex * 10 + k, (mazey + 1) * 10)->green = 255;
		(*outPNG)(mazex * 10 + k, (mazey + 1) * 10)->blue = 255;
	}

	return outPNG;

}

void SquareMaze::solveMaze_helper(int x, int y, vector<int> & path, int * lastRow)
{
	if(y == height - 1)
		lastRow[x] = path.size();
	if(canTravel(x, y, 0))
	{
		path.push_back(0);
		setWall(x, y, 0, true);
		solveMaze_helper(x + 1, y, path, lastRow);
		path.pop_back();
		setWall(x, y, 0, false);
	}
	
	if(canTravel(x, y, 1))
	{
		path.push_back(1);
		setWall(x, y, 1, true);
		solveMaze_helper(x, y + 1, path, lastRow);
		path.pop_back();
		setWall(x, y, 1, false);
	}
	
	if(canTravel(x, y, 2))
	{		
		path.push_back(2);
		setWall(x - 1, y, 0, true);
		solveMaze_helper(x - 1, y, path, lastRow);
		path.pop_back();
		setWall(x - 1, y, 0, false);
	}
	
	if(canTravel(x, y, 3))
	{
		path.push_back(3);
		setWall(x, y - 1, 1, true);
		solveMaze_helper(x, y - 1, path, lastRow);
		path.pop_back();
		setWall(x, y - 1, 1, false);
	}
	return;
}

bool SquareMaze::solveMaze_second_helper(int x, int y, vector<int> & path, int dest)
{
	if(x == dest&&y == height -1)
		return true;
	if(canTravel(x, y, 0))
	{
		path.push_back(0);
		setWall(x, y, 0, true);
		if(solveMaze_second_helper(x + 1, y, path, dest))
		{
			setWall(x, y, 0, false);
			return true;
		}
		path.pop_back();
		setWall(x, y, 0, false);
	}
	
	if(canTravel(x, y, 1))
	{
		path.push_back(1);
		setWall(x, y, 1, true);
		if(solveMaze_second_helper(x, y + 1, path, dest))
		{
			setWall(x, y, 1, false);
			return true;
		}
		path.pop_back();
		setWall(x, y, 1, false);
	}
	
	if(canTravel(x, y, 2))
	{		
		path.push_back(2);
		setWall(x - 1, y, 0, true);
		if(solveMaze_second_helper(x - 1, y, path, dest))
		{
			setWall(x - 1, y, 0, false);
			return true;
		}
		path.pop_back();
		setWall(x - 1, y, 0, false);
	}
	
	if(canTravel(x, y, 3))
	{
		path.push_back(3);
		setWall(x, y - 1, 1, true);
		if(solveMaze_second_helper(x, y - 1, path, dest))
		{
			setWall(x, y-1, 1, false);
			return true;
		}
		path.pop_back();
		setWall(x, y - 1, 1, false);
	}
	return false;
}
