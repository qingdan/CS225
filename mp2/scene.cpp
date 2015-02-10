#include<cstdint>
#include"png.h"
#include"image.h"
#include"rgbapixel.h"
#include "scene.h"

using namespace std;

Scene::Scene(int max)
{
	this->max = max;
	theScene = new Image*[max];
	for (int i = 0; i < max; i++)
	{
		*(theScene + i) = NULL;
	}
	listofX = new int[max];
    	listofY = new int[max];
	for (int i = 0; i < max; i++)
	{
		*(listofX + i) = 0;
		*(listofY + i) = 0;
	}
  	
}

Scene::~Scene(){
    clear();
}

void Scene::clear(){
	 for(int i = 0; i < max; i++)
		{ 
		if (theScene != NULL)
	    		{
			delete *(theScene+i);
			*(theScene + i) = NULL;
			}
		}
        	delete [] theScene;
		theScene = NULL;
		if (listofX != NULL)
		delete [] listofX;
		listofX = NULL;
		if (listofY != NULL)
		delete [] listofY;
		listofY = NULL;
		
}



Scene::Scene (const Scene &source){
	copy(source);
}
void Scene::copy(const Scene &source){
	max = source.max;
	theScene = new Image*[max];
	listofX = new int [max];
	listofY = new int [max];
	for (int i = 0; i < max; i++)
	{
		*(theScene + i) = NULL;
	}
	for (int i = 0; i < max; i++)
	{
		*(listofX + i) = 0;
		*(listofY + i) = 0;
	}
  	
	for(int i = 0; i < max; i++)
		{ 	
		if (source.theScene[i] != NULL)
			{
			theScene[i] = new Image;
			*theScene[i] = *(source.theScene[i]);
			listofX[i] = source.listofX[i];
			listofY[i] = source.listofY[i];
			}
		}
}


const Scene & Scene::operator= (const Scene &source)
{
	if (this != &source)
		{
			clear();
			copy(source);
		}
	return *this;

}

void Scene:: changemaxlayers (int newmax)
{	
	if (newmax < max)
	{
		for(int i = newmax - 1; i < max; i++)
		{
			  if (*(theScene + i) != NULL);
			{
			cout << "invalid newmax" << endl;
			return;
			}
		}
	}

	if (newmax == max)
		return;
	else if (newmax < max)
		{	
			Image** second_theScene = new Image*[newmax];
			int* second_listofX = new int [newmax];
			int* second_listofY = new int [newmax];
			for(int i = 0; i < newmax; i++)
				{
				second_theScene[i] = theScene[i];
				second_listofX[i] = listofX[i];
				second_listofY[i] = listofY[i];
				}
			clear();
			theScene = second_theScene;
			listofX = second_listofX;
			listofY = second_listofY;
			max = newmax;
			/* for(int i = 0; i < max; i++)
				{ 
				if (second_theScene != NULL)
	    				{
					delete *(second_theScene+i);
					*(second_theScene + i) = NULL;
					}
        			delete [] second_theScene;
				second_theScene = NULL;
				if (second_listofX != NULL)
				delete [] second_listofX;
				second_listofX = NULL;
				if (second_listofY != NULL)
				delete [] second_listofY;
				second_listofY = NULL;
				}*/
		}

	else 
		{	
			Image** second_theScene = new Image*[newmax];
			int* second_listofX = new int [newmax];
			int* second_listofY = new int [newmax];
			for(int i = 0; i < newmax; i++)
				{
				second_theScene[i] = theScene[i];
				second_listofX[i] = listofX[i];
				second_listofY[i] = listofY[i];
				}
			for(int i = max - 1; i < newmax; i++)
				{
				second_theScene[i] = NULL;
				}
			clear();
			theScene = second_theScene;
			listofX = second_listofX;
			listofY = second_listofY;
			max = newmax;
		}

}

void Scene:: addpicture (const char *FileName, int index, int x, int y)
{	
        tempImage = new Image();
	string str(FileName);
        tempImage -> readFromFile(str);
		if (index < 0||index >= max)
			{
			cout << "index out of bounds" << endl;
			delete tempImage;
			tempImage = NULL;
			return;
			}
		else 
			{
			theScene[index] = tempImage;
			listofX[index] = x;
			listofY[index] = y;
			}

}

void Scene:: changelayer (int index, int newindex)
{
		if (index < 0||index >= max||newindex < 0||newindex >= max)
			{
			cout << "invalid index" << endl;
			return;
			}
		if (index == newindex)
			{
			return;
			}
		else
			{
				if(theScene[newindex] != NULL)
					{
					delete theScene[newindex];
					theScene[newindex] = NULL;
					}
				theScene[newindex] = theScene[index];
				listofX[newindex] = listofX[index];
				listofY[newindex] = listofY[index];
				//delete theScene[index];
				theScene[index] = NULL;			
			}

}

void Scene:: translate (int index, int xcoord, int ycoord)
{
		if (index < 0||index >= max||theScene[index] == NULL)
			{
			cout << "invalid index" << endl;
			return;
			}
		else
			{
			listofX[index] = xcoord;
			listofY[index] = ycoord;

			}

}

void Scene:: deletepicture (int index)
{
		if (index < 0||index >= max||theScene[index] == NULL)
			{
			cout << "invalid index" << endl;
			return;
			}
		else 
			{
			delete theScene[index];
			theScene[index] = NULL;
			}

}

Image * Scene:: getpicture (int index) const
{
			if (index < 0||index >= max||theScene[index] == NULL)
			{
			cout << "invalid index" << endl;
			return NULL;
			}
			else 
			return theScene[index];

}

Image Scene:: drawscene () const
{
		size_t need_width = 0;
		size_t need_height = 0;
		for(int i = 0; i < max; i++)
			{       if (theScene[i] != NULL)
				{
				size_t single_width =  theScene[i]->width() + (size_t)listofX[i];
				size_t single_height =  theScene[i]->height() + (size_t)listofY[i];
				if (single_width > need_width)
					need_width = single_width;
				if (single_height > need_height)
					need_height = single_height;
				}
			}
		//cout << "cao" <<endl;
		Image myScene(need_width, need_height);
		RGBAPixel * Scene_pixel;
		for(int i = 0; i < max; i++)
			{
			if (theScene[i] != NULL)
				{
				size_t temp_width = theScene[i]->width();
				size_t temp_height = theScene[i]->height();
				size_t x_coord = size_t(listofX[i]);
				size_t y_coord = size_t(listofY[i]);
				for(size_t j = 0; j < temp_width; j++)
					{for(size_t k = 0; k < temp_height; k++)
						{
						Scene_pixel = myScene(j + x_coord, k + y_coord);
						*Scene_pixel = *(*theScene[i])(j,k);
						}
					}
				}
			}
		return myScene;

}











