#include "CreateMat.h"



CreateMat::CreateMat(string s, vector<CreateMat>input)
{
	data = input;
	name = s.substr(0, s.find('=') - 1);// wrong: it fetch space in right side 
	body = s.substr(s.find('['));// wrong: it fetch space in befor first bracket " [..." 
	separat_pracket(body);
	concatenate();
}

string CreateMat::getName()
{
	return name;
}

void CreateMat::separat_pracket(string S)
{
	for (int i = 0; i < S.size() - 1; i++)
	{
		if (S[i] == '[')
		{
			brackts.push_back(*new vector<char>);
			indx.push(++n);
		}

		if (S[i] == ';' && (i + 1)<S.size() - 1)
		{
			if (S[i + 1] == '[')
				colon.push(S[i]);
		}
		brackts[indx.top() - 1].push_back(S[i]);

		if (S[i] == ']') indx.pop();

		if (S[i] == ']' && (i + 1) < S.size() - 1)
		{
			if (S[i + 1] == ',')
				i++;
		}
	}

	if (S[1] == '[')
	{
		for (int i = 0; i < brackts.size() - 1; i++)
			brackts[i].swap(brackts[i + 1]);
	}

	if (indx.size() != 0) {
		throw "invalid matrix";  /////////error handling ///////
	}
	else
	{
		for (int i = 0; i < brackts.size(); i++)
		{
			string str(brackts[i].begin(), brackts[i].end());
			subMatrix(str);
		}
	}
}
	
void CreateMat::subMatrix(string subS)
{
	int flag = 0, number_semicolon_brcket = 0, number_rows = 0; string row, col; int flagvec = 0;
	int flag_skip = 0; //to skip first bracket in stack semicolon notation its defenitly compelete bracket
	matConcat.push_back(*new vector<vector<string>>);
	for (int i = 1; i<subS.size(); i++)
	{
		if (subS[i] == ';' || subS[i] == ']')
		{
			number_semicolon_brcket++;
			row = subS.substr(flag + 1, i - flag - 1);
			int num = 0; flag = i;
			for (int i = 1; i<row.size(); i++)  // i from 1 for case like this " 2.1" to prevent num count space befor first item
			{
				if (row[i] == ' ') {
					num++;
				}
			}
			
		 if (row.size())
			{    
				matConcat[count].push_back(*new vector<string>);
				number_rows++;
				int localflag = 0; string s; int flagfloat = 0;
				for (int i = 1; i <= row.size(); i++)   // i from 1 for case like this " 2.1" to prevent num count space befor first item
				{
					if (row[i] == ' ' || i == (row.size())) {
						s = row.substr(localflag, (i - localflag));
						if (s[0] == ' ') s = s.substr(1);
						if (s.size() != 0) {
							matConcat[count][flagvec].push_back(s); /*out of rang here *///suppose s is a number handle if it math operation later
							localflag = i; flagfloat++;				/*in C = [[B [3.4; 2.1; 3.5+9.1]];1.2 3+1.2 15 1.2] at  1.2 3+1.2 15 1.2 */
						}
					}
				}
			}
			if (row.size())flagvec++;
		}
	}
	count++;
	if (number_semicolon_brcket == number_rows) // so its complete matrix
	{
		semicolon_count -= number_semicolon_brcket - 1;/*number_semicolon_brcket its count ] too so we put -1 */

		semicolone_colon_queue.push(',');
	}
	else
		semicolone_colon_queue.push(';');
}

void CreateMat::concatenate()
{
	int flag = 0, flag2 = 0;  if ((body[1] == '[')) semicolone_colon_queue.pop();
	for (int i = 0; i < matConcat.size(); i++)
	{
		match(matConcat[i], flag);
		flag++;
	}

	for (int i = 0; i < finalMatrix.size() - 1; i++) /////////////error handling////
	{
		if (finalMatrix[i].size() != finalMatrix[i + 1].size())
			flag2++;
	}
	if (flag2>0) throw "invalid matrix";
}
void CreateMat::match(vector<vector<string>> a, int flag)
{
	if (flag == 0) // so its a first concatenate 
	{
		for (int i = 0; i<a.size(); i++)
		{
			vector<string>v;
			finalMatrix.push_back(v);
			for (int j = 0; j<a[i].size(); j++)
			{
				/////////////to detect if we have a matrix inside this matrix//////// 
				int localflag = 0;
				for (int k = 0; k<data.size(); k++)
				{
					if (a[i][j] == data[k].name)
					{
						match(data[k].finalMatrix, flag); localflag++;
						finalMatrix.pop_back();
					}
				}
				if (localflag == 0)
					finalMatrix[i].push_back(a[i][j]);
			}
		}
	}
	
	else if (semicolone_colon_queue.front() == ',') // so its a side concatenate 
	{
		int n = finalMatrix.size() - a.size();
		for (int i = 0; i < a.size(); i++)
		{  
			for (int j = 0; j < a[i].size(); j++)
			{
				/////////////to detect if we have a matrix inside this matrix//////// 
				int localflag = 0;
				for (int k = 0; k < data.size(); k++)
				{
					if (a[i][j] == data[k].name)
					{
						match(data[k].finalMatrix, flag); localflag++;
					}
				}
				///////////////////////////////
				if (localflag == 0) {
					finalMatrix[n].push_back(a[i][j]); //are we need to put * because it a pointer ? :)		
					n++;
				}
			}
		}
		semicolone_colon_queue.pop();
	}
	else if (semicolone_colon_queue.front() == ';')
	{
		for (int i = 0; i< a.size(); i++)
		{
			vector<string>v;
			finalMatrix.push_back(v);
			for (int j = 0; j < a[0].size(); j++)
			{
				/////////////to detect if we have a matrix inside this matrix//////// 
				int localflag = 0;
				for (int k = 0; k<data.size(); k++)
				{
					if (a[i][j] == data[k].name)
					{
						match(data[k].finalMatrix, flag); localflag++;
					}
				}
				///////////////////////////////
				if (localflag == 0)
					finalMatrix[finalMatrix.size() - 1].push_back(a[i][j]);
			}
		}

		semicolone_colon_queue.pop(); 
	}
}
