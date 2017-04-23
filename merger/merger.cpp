#include<iostream>
#include<fstream>
#include<string>
#define algorithm_number 8
#define UE_level 15
#define parameter 24
#define UE_mode_number 2

using namespace std;

int main()
{
	int mode = 0;
	cout << "Input mode number (uniform = 0, hotspot = 1):";
	cin >> mode;
	
	char *mode_name;
	if (mode == 0)
	{
		mode_name = new char[1];
		mode_name = "";
	}
	else
	{
		mode_name = new char[3];
		mode_name = "hs_";
	}

	double result[algorithm_number][UE_level][parameter] = { 0 };
	string algorithm_name[] = { "dso_0","dso_ex_0","dso_1","dso_ex_1","dso_2","dso_ex_2","Capa","SINR" };
	string parameter_name[] = { "outage_UE","avg_T","stdev_T","avg_UE_number","stdev_UE_number","avg_capacity_UE","stdev_capacity_UE ","avg_T_UE","stdev_T_UE",
		"avg_T_LTE","avg_T_WIFI","stdev_T_WIFI","avg_UE_number_LTE","avg_UE_number_WIFI","stdev_UE_number_WIFI",
		"avg_capacity_LTEUE","stdev_capacity_UE_LTE","avg_capacity_WIFIUE","stdev_capacity_UE_WIFI",
		"avg_T_UE_LTE","avg_T_UE_WIFI","stdev_T_UE_WIFI","DB_satisfied","throughput" };
	for (int i = 0; i < algorithm_number; i++)
	{
		char *algorihm_name;
		switch (i)
		{
		case 0:
			algorihm_name = new char[6];
			algorihm_name = "dso_0";
			break;
		case 1:
			algorihm_name = new char[6];
			algorihm_name = "dso_ex_0";
			break;
		case 2:
			algorihm_name = new char[6];
			algorihm_name = "dso_1";
			break;
		case 3:
			algorihm_name = new char[9];
			algorihm_name = "dso_ex_1";
			break;
		case 4:
			algorihm_name = new char[9];
			algorihm_name = "dso_2";
			break;
		case 5:
			algorihm_name = new char[9];
			algorihm_name = "dso_ex_2";
			break;
		case 6:
			algorihm_name = new char[5];
			algorihm_name = "Capa";
			break;
		case 7:
			algorihm_name = new char[5];
			algorihm_name = "SINR";
			break;
		default:
			break;
		}

		for (int j = 0; j < UE_level; j++)
		{
			char filename[50];
			sprintf_s(filename, "%s%s_UE%d_result.csv", mode_name, algorihm_name, (j + 1) * 1000);
			ifstream file;
			file.open(filename, ios::in);
			if (file.fail())
				cout << filename << " 開啟失敗." << endl;
			else
			{
				string in;
				int n = 0;
				while (file >> in)
				{
					n++;
					int size = in.size();
					int begin = 0;
					for (int k = 0; k < parameter; k++)
					{
						int pos = in.find(",", begin);
						if (pos < size)
						{
							string s = in.substr(begin, pos - begin);
							result[i][j][k] += stod(s);
							begin = pos + 1;
						}
					}
				}
				for (int k = 0; k < parameter; k++)
					result[i][j][k] /= n;

			}
			file.close();
		}
	}

	fstream outcome;
	char outcome_name[] = "simulation_result.csv";
	outcome.open(outcome_name, ios::out | ios::trunc);
	if (outcome.fail())
		cout << outcome_name << " 開啟失敗." << endl;
	else
	{
		for (int k = 0; k < parameter; k++)
		{
			outcome << parameter_name[k] << ",";
			for (int n = 0; n < UE_level; n++)
				outcome << (n + 1) * 1000 << ",";
			outcome << endl;
			for (int i = 0; i < algorithm_number; i++)
			{
				outcome << algorithm_name[i] << ",";
				for (int j = 0; j < UE_level; j++)
				{
					if (j != UE_level - 1)
						outcome << result[i][j][k] << ",";
					else
						outcome << result[i][j][k] << endl;
				}
			}
			outcome << endl;
		}
	}
	outcome.close();
	return 0;
}