#include <cstdio>
#include <iostream>
#include <cstring>
#include <stdafx.h>
#include <cstdlib>
#include <NXFunction.h>
#include <NXOpen/UI.hxx>
#include <NXOpen/NXMessageBox.hxx>
using namespace std;
using namespace NXOpen;


void startRunScripte(const char oper[],Json::Value jCoordinate)
{
	Json::FastWriter json_writer;
	//string cmd = "websocket.Invoke('CreateRect', ";
	string cmd = "websocket.Invoke('";
	cmd += oper;
	cmd += "', ";
	cmd += json_writer.write(jCoordinate);
	cmd += ", function(){});";
	RunScript(cmd.c_str());
}

bool isNum(char s)
{
	return (s >= '0' && s <= '9') || (s == '.') || (s == '-');
}

void realizeOperation(char ori[])
{
	UI *myUI = UI::GetUI();
	NXMessageBox *message = myUI->NXMessageBox();
	int length = strlen(ori);

	if (strstr(ori,"CreateSketchOnExtrude"))
	{

		//message->Show("heheheh",NXMessageBox::DialogTypeQuestion,ori);
		char temp[300];
		char str1[100],str2[100];
		int extrudeNum;
		int num = 0;
		char h[3];
		for (int i=0; i<length; i++)
		{
			// 			sprintf(h,"%d",i);
			// 			message->Show("CreateSketchOnExtrude", NXOpen::NXMessageBox::DialogTypeInformation, h);
			if ((ori[i] == ':' || ori[i] == ' ') && (ori[i + 1] != ' '))
			{
				int index = i + 1;
				int start = 0;
				memset(temp,0,sizeof(temp));
				if (isNum(ori[index]))
				{
					while(isNum(ori[index]))
					{

						temp[start++] = ori[index];
						i = index;
						index ++;
					}
				}
				else
				{
					while(ori[index] != '?')
					{
						temp[start++] = ori[index];
						i = index;
						index ++;
					}
				}
				switch(num)
				{
				case 0:
					{
						extrudeNum = atoi(temp);
					}
				case 1:
					{
						strcpy(str1,temp);

					}
				case 2:
					{
						strcpy(str2,temp);

					}
				}
				num ++;
			}
		}
 		//message->Show("CreateSketchOnExtrude", NXOpen::NXMessageBox::DialogTypeInformation, str1);
 		//message->Show("CreateSketchOnExtrude", NXOpen::NXMessageBox::DialogTypeInformation, str2);
		createSketchOnExtrude(extrudeNum,str1,str2);
	}
	if (strstr(ori,"DrawCircle"))
	{
		double x,y,z,r;
		char temp[300];
		int num = 0;
		for (int i=0; i<length; i++)
		{
			if (isNum(ori[i]))
			{
				int index = i;
				int start = 0;
				memset(temp,0,sizeof(temp));
				while(isNum(ori[index]))
				{
					temp[start++] = ori[index];
					index ++;
					i = index;
				}
				switch(num)
				{
				case 0:
					{
						x = atof(temp);
					}
				case 1:
					{
						y = atof(temp);

					}
				case 2:
					{
						z = atof(temp);

					}
				case 3:
					{
						r = atof(temp);

					}
				}
				num ++;
			}
		}
		//message->Show("ReadBlock", NXOpen::NXMessageBox::DialogTypeInformation, "DrawCircle");
		drawCircle(x,y,z,r);

	}
	 if (strstr(ori,"CreateRect"))
	{
		int length = strlen(ori);

		char temp[300];
		double para1,para2,para3,para4,para5;
		int type;
		int num = 0;
		for (int i=0; i<length; i++)
		{
			if (isNum(ori[i]))
			{
				int index = i;
				int start = 0;
				memset(temp,0,sizeof(temp));
				while(isNum(ori[index]))
				{
					temp[start++] = ori[index];
					index ++;
					i = index;
				}
				switch(num)
				{
				case 0:
					{
						para1 = atof(temp);
					}
				case 1:
					{
						para2 = atof(temp);

					}
				case 2:
					{
						para3 = atof(temp);

					}
				case 3:
					{
						para4 = atof(temp);

					}
				case 4:
					{
						para5 = atof(temp);
					}
				case 5:
					{
						type = atoi(temp);
					}
				}
				num ++;
			}
		}
		//message->Show("ReadBlock", NXOpen::NXMessageBox::DialogTypeInformation, "CreateRect");
		if (type == 0)
		{
			createRect(para1,para2,para3,para4,para5);
		}
		else if (type == 1)
		{

			createRect(para1,para2,para3,para4,para5,1);
		}
		else if (type == 2)
		{

			createRect(para1,para2,para3,para4,para5,1,2);
		}
	 }
	if (strstr(ori,"ReverseExtrude"))
	{
		char temp[300];
		char sketchId[100],sketchNum[100],lashenLine[100],target[100];
		int exLength;
		int num = 0;
		for (int i=0; i<length; i++)
		{
			if ((ori[i] == ':' || ori[i] == ' ') && (ori[i + 1] != ' '))
			{
				int index = i + 1;
				int start = 0;
				memset(temp,0,sizeof(temp));
				if (isNum(ori[index]))
				{
					while(isNum(ori[index]))
					{

						temp[start++] = ori[index];
						index ++;
						i = index;
					}
				}
				else
				{
					while(ori[index] != '?')
					{
						temp[start++] = ori[index];
						index ++;
						i = index;
					}
				}
				switch(num)
				{
				case 0:
					{
						strcpy(sketchId,temp);
					}
				case 1:
					{
						strcpy(sketchNum,temp);

					}
				case 2:
					{
						strcpy(lashenLine,temp);

					}
				case 3:
					{
						strcpy(target,temp);

					}
				case 4:
					{
						exLength = atoi(temp);
					}
				}
				num ++;
			}
		}
		//message->Show("ReadBlock", NXOpen::NXMessageBox::DialogTypeInformation, "ReverseExtrude");
		fanxianglashen(sketchId,sketchNum,lashenLine,target,exLength);
	}
	if (strstr(ori,"CreateSketch") && (strlen(ori) < 30))
	{
		createSketch();
		//message->Show("aaaa",NXMessageBox::DialogTypeQuestion,"CreateSketch");
	}
	if (strstr(ori,"Extrude") && strlen(ori) < 40)
	{
		int length = strlen(ori);

		char temp[300];
		int height,lineNum,sketchNum,sketchId;
		int num = 0;
		for (int i=0; i<length; i++)
		{
			if (isNum(ori[i]))
			{
				int index = i;
				int start = 0;
				memset(temp,0,sizeof(temp));
				while(isNum(ori[index]))
				{
					temp[start++] = ori[index];
					index ++;
					i = index;
				}
				switch(num)
				{
				case 0:
					{
						height = atoi(temp);
					}
				case 1:
					{
						lineNum = atoi(temp);

					}
				case 2:
					{
						sketchNum = atoi(temp);

					}
				case 3:
					{
						sketchId = atoi(temp);

					}
				}
				num ++;
			}
		}
		//message->Show("ReadBlock", NXOpen::NXMessageBox::DialogTypeInformation, "Extrude");
		lashen(height,lineNum,sketchNum,sketchId);
	}
}


void createExtrudeOnSket(char ori[])
{
	int length = strlen(ori);

	//if (strstr(ori,"CreateSketchOnExtrude"))
	{

		//message->Show("heheheh",NXMessageBox::DialogTypeQuestion,ori);
		char temp[300];
		char str1[100],str2[100];
		int extrudeNum;
		int num = 0;
		char h[3];
		for (int i=0; i<length; i++)
		{
			// 			sprintf(h,"%d",i);
			// 			message->Show("CreateSketchOnExtrude", NXOpen::NXMessageBox::DialogTypeInformation, h);
			if ((ori[i] == ':' || ori[i] == ' ') && (ori[i + 1] != ' '))
			{
				int index = i + 1;
				int start = 0;
				memset(temp,0,sizeof(temp));
				if (isNum(ori[index]))
				{
					while(isNum(ori[index]))
					{

						temp[start++] = ori[index];
						i = index;
						index ++;
					}
				}
				else
				{
					while(ori[index] != '?')
					{
						temp[start++] = ori[index];
						i = index;
						index ++;
					}
				}
				switch(num)
				{
				case 0:
					{
						extrudeNum = atoi(temp);
					}
				case 1:
					{
						strcpy(str1,temp);

					}
				case 2:
					{
						strcpy(str2,temp);

					}
				}
				num ++;
			}
		}
		//message->Show("CreateSketchOnExtrude", NXOpen::NXMessageBox::DialogTypeInformation, str1);
		//message->Show("CreateSketchOnExtrude", NXOpen::NXMessageBox::DialogTypeInformation, str2);
		//createSketchOnExtrude(extrudeNum,str1,str2);
	}
}