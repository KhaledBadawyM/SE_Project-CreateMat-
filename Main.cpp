#include"CreateMat.h" 

int main()
{

	int flag = 0;

	vector<CreateMat> input;
	ifstream f("sample.txt");
	string line_mat;
	while (getline(f, line_mat))
	{
		try {
			CreateMat a(line_mat, input);
			input.push_back(a);
		}
		catch (char* error)
		{
			if (error == "invalid matrix")
			{
				cout << error; 
			}
		}
	}
	f.close();

	if (flag == 0) {
		for (int k = 0; k < input.size(); k++) {
			cout << input[k].getName() << " =" << endl;
			for (int i = 0; i < input[k].finalMatrix.size(); i++)
			{
				for (int j = 0; j < input[k].finalMatrix[0].size(); j++)
				{
					cout << input[k].finalMatrix[i][j] << "  ";
				}
				cout << endl;
			}
			cout << "__________________________________________________" << endl;
		}

	}
	system("pause");
}